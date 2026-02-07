#!/usr/bin/env pwsh

param(
    [switch]$WhatIf,
    [switch]$Verbose
)

# Function to detect line ending style
function Get-LineEnding {
    param([string]$Content)
    
    if ($Content -match "`r`n") {
        return "`r`n"  # CRLF
    } elseif ($Content -match "`n") {
        return "`n"    # LF
    } else {
        return "`n"    # Default to LF
    }
}

# Function to check if a file should be skipped entirely
function Should-SkipFile {
    param([string]$FilePath)
    
    $filename = [System.IO.Path]::GetFileName($FilePath)
    
    # Skip files that contain "[INC]" in the filename
    if ($filename -match '\[INC\]') {
        return @{ ShouldSkip = $true; Reason = "Contains [INC] in filename" }
    }

    # Skip files that contain "[INC]" in the filename
    if ($filename -match '.hlsl.h') {
        return @{ ShouldSkip = $true; Reason = "Compiled HLSL header file" }
    }

    # Skip empty files or files with only whitespace
    try {
        $fileInfo = Get-Item -LiteralPath $FilePath -ErrorAction Stop
        if ($fileInfo.Length -eq 0) {
            return @{ ShouldSkip = $true; Reason = "File is empty (0 bytes)" }
        }
        
        # Check if file contains only whitespace
        $content = Get-Content -LiteralPath $FilePath -Raw -ErrorAction Stop
        if ([string]::IsNullOrWhiteSpace($content)) {
            return @{ ShouldSkip = $true; Reason = "File contains only whitespace" }
        }
    }
    catch {
        # If we can't read the file, skip it
        return @{ ShouldSkip = $true; Reason = "Cannot read file: $($_.Exception.Message)" }
    }
    
    # Files that should be skipped entirely (specific filenames)
    $skipFiles = @(
        # Add specific files here if needed
    )
    
    if ($filename -in $skipFiles) {
        return @{ ShouldSkip = $true; Reason = "File is in skip list" }
    }
    
    return @{ ShouldSkip = $false; Reason = "" }
}

# Function to transform filename to expected include guard
function Get-ExpectedIncludeGuard {
    param([string]$FilePath)
    
    # Get just the filename without extension
    $filename = [System.IO.Path]::GetFileNameWithoutExtension($FilePath)
    $extension = [System.IO.Path]::GetExtension($FilePath).ToLower()
    
    # Apply transformations based on the pattern observed in codebase:
    # 1. Convert to uppercase
    # 2. Replace spaces with underscores
    # 3. Remove parentheses ()
    # 4. Remove square brackets []
    # 5. Replace single hyphens with underscores
    # 6. Replace double hyphens -- with double underscores __
    # 7. Add _H suffix for .h files, _INL suffix for .inl files
    
    $guard = $filename.ToUpper()
    $guard = $guard -replace ' - ', '_'        # Replace single hyphens with underscores
    $guard = $guard -replace '\.', '_'         # Replace single hyphens with underscores
    $guard = $guard -replace '\+', 'X'         # Replace single hyphens with underscores
    $guard = $guard -replace '\s+', '_'        # Replace spaces with underscores
    $guard = $guard -replace '[()]', ''        # Remove parentheses
    $guard = $guard -replace '[\[\]]', ''      # Remove square brackets
    $guard = $guard -replace '--', '__'        # Replace double hyphens with double underscores
    $guard = $guard -replace '-', '_'          # Replace single hyphens with underscores
    
    # Add appropriate suffix based on file extension
    if ($extension -eq '.h') {
        $guard = $guard + '_H'
    } elseif ($extension -eq '.inl') {
        $guard = $guard + '_INL'
    } elseif ($extension -eq '.C') {
        $guard = $guard + '_C'
    }
    
    return $guard
}

# Function to extract include guard from file content
function Get-ActualIncludeGuard {
    param([string]$FilePath)
    
    try {
        $content = Get-Content -LiteralPath $FilePath -Raw -ErrorAction Stop
        
        # Look for pattern: #if !defined(GUARD_NAME)
        if ($content -match '#if\s+!defined\((\w+)\)') {
            return $matches[1]
        }
        
        # Alternative pattern: #ifndef GUARD_NAME
        if ($content -match '#ifndef\s+(\w+)') {
            return $matches[1]
        }
        
        return $null
    }
    catch {
        Write-Warning "Could not read file: $FilePath"
        return $null
    }
}

# Function to check if include guard should be preserved
function Should-PreserveIncludeGuard {
    param([string]$GuardName)
    
    # Special guards that should be preserved as-is
    $specialGuards = @(
        "__PARENT_FILE__",
        "RENDER_INPUT_LAYOUT_START_FIRST"
    )
    
    return $GuardName -in $specialGuards
}

# Function to fix include guard in a file
function Fix-IncludeGuard {
    param(
        [string]$FilePath,
        [string]$ExpectedGuard,
        [string]$ActualGuard
    )
    
    try {
        $content = Get-Content -LiteralPath $FilePath -Raw -ErrorAction Stop
        $originalContent = $content
        
        # Detect original line ending style
        $lineEnding = Get-LineEnding $content
        
        if ($ActualGuard -eq $null) {
            # Add missing include guard
            $guardStart = "#if !defined($ExpectedGuard)$lineEnding#define $ExpectedGuard$lineEnding"
            $guardEnd = "$lineEnding#endif"
            
            # Find the copyright header end (look for the last */ or similar pattern)
            if ($content -match "(?s)^(.*?\*/$lineEnding)(.*)$") {
                $header = $matches[1]
                $body = $matches[2]
                $newContent = $header + $guardStart + $lineEnding + $body + $guardEnd
            } else {
                # No copyright header found, just wrap everything
                $newContent = $guardStart + $lineEnding + $content + $guardEnd
            }
        } else {
            # Fix existing include guard
            # Replace #if !defined(OLD_GUARD) with #if !defined(NEW_GUARD)
            $content = $content -replace "#if\s+!defined\($ActualGuard\)", "#if !defined($ExpectedGuard)"
            
            # Replace #ifndef OLD_GUARD with #ifndef NEW_GUARD
            $content = $content -replace "#ifndef\s+$ActualGuard", "#ifndef $ExpectedGuard"
            
            # Replace #define OLD_GUARD with #define NEW_GUARD
            $content = $content -replace "#define\s+$ActualGuard", "#define $ExpectedGuard"
            
            $newContent = $content
        }
        
        # Only write if content changed
        if ($newContent -ne $originalContent) {
            # Write with proper line endings
            if ($lineEnding -eq "`n") {
                # Force LF line endings
                $newContent = $newContent -replace "`r`n", "`n"
                [System.IO.File]::WriteAllText($FilePath, $newContent, [System.Text.UTF8Encoding]::new($false))
            } else {
                # Use PowerShell default (CRLF on Windows)
                Set-Content -LiteralPath $FilePath -Value $newContent -ErrorAction Stop
            }
            return $true
        }
        
        return $false
    }
    catch {
        Write-Error "Failed to fix include guard in $FilePath`: $($_.Exception.Message)"
        return $false
    }
}

# Main script
Write-Host "Checking and fixing include guards in .h and .inl files..." -ForegroundColor Green
Write-Host "=" * 60

if ($WhatIf) {
    Write-Host "Running in WHAT-IF mode - no changes will be made`n" -ForegroundColor Yellow
}

$headerFiles = Get-ChildItem -Path "." -Include "*.h", "*.inl" -Recurse | Where-Object { 
    # Exclude build directories and external dependencies
    $_.FullName -notmatch '\\build\\' -and 
    $_.FullName -notmatch '\\_install\\' -and
    $_.FullName -notmatch '\\external\\' -and
    $_.FullName -notmatch '\\.git\\' 
}

$totalFiles = $headerFiles.Count
$correctCount = 0
$fixedCount = 0
$failedCount = 0
$preservedCount = 0
$skippedCount = 0

Write-Host "Found $totalFiles header/inline files to check`n" -ForegroundColor Cyan

foreach ($file in $headerFiles) {
    $relativePath = $file.FullName.Replace((Get-Location).Path, "").TrimStart('\')
    
    # Check if this file should be skipped
    $skipResult = Should-SkipFile $file.FullName
    if ($skipResult.ShouldSkip) {
        Write-Host "⏭️  SKIPPED: $relativePath" -ForegroundColor DarkGray
        Write-Host "   Reason: $($skipResult.Reason)" -ForegroundColor DarkGray
        if ($Verbose) {
            Write-Host ""
        }
        $skippedCount++
        continue
    }
    
    $expectedGuard = Get-ExpectedIncludeGuard $file.FullName
    $actualGuard = Get-ActualIncludeGuard $file.FullName
    
    if ($actualGuard -eq $null) {
        Write-Host "❌ MISSING: $relativePath" -ForegroundColor Red
        Write-Host "   Expected: $expectedGuard" -ForegroundColor Yellow
        
        if (-not $WhatIf) {
            $success = Fix-IncludeGuard -FilePath $file.FullName -ExpectedGuard $expectedGuard -ActualGuard $actualGuard
            if ($success) {
                Write-Host "   ✅ FIXED: Added missing include guard" -ForegroundColor Green
                $fixedCount++
            } else {
                Write-Host "   ❌ FAILED: Could not add include guard" -ForegroundColor Red
                $failedCount++
            }
        } else {
            Write-Host "   🔄 WOULD ADD: Missing include guard" -ForegroundColor Cyan
        }
        Write-Host ""
    }
    elseif ($actualGuard -eq $expectedGuard) {
        if ($Verbose) {
            Write-Host "✅ CORRECT: $relativePath" -ForegroundColor Green
        }
        $correctCount++
    }
    elseif (Should-PreserveIncludeGuard $actualGuard) {
        Write-Host "🔒 PRESERVED: $relativePath" -ForegroundColor Cyan
        Write-Host "   Guard: $actualGuard (special guard - preserved)" -ForegroundColor Cyan
        if ($Verbose) {
            Write-Host ""
        }
        $preservedCount++
    }
    else {
        Write-Host "❌ MISMATCH: $relativePath" -ForegroundColor Red
        Write-Host "   Expected: $expectedGuard" -ForegroundColor Yellow
        Write-Host "   Actual:   $actualGuard" -ForegroundColor Magenta
        
        if (-not $WhatIf) {
            $success = Fix-IncludeGuard -FilePath $file.FullName -ExpectedGuard $expectedGuard -ActualGuard $actualGuard
            if ($success) {
                Write-Host "   ✅ FIXED: Updated include guard" -ForegroundColor Green
                $fixedCount++
            } else {
                Write-Host "   ❌ FAILED: Could not update include guard" -ForegroundColor Red
                $failedCount++
            }
        } else {
            Write-Host "   🔄 WOULD FIX: Update include guard" -ForegroundColor Cyan
        }
        Write-Host ""
    }
}

Write-Host "`n" + "=" * 60
Write-Host "SUMMARY:" -ForegroundColor Cyan
Write-Host "  Total files:     $totalFiles" -ForegroundColor White
Write-Host "  Skipped files:   $skippedCount" -ForegroundColor DarkGray
Write-Host "  Processed files: $($totalFiles - $skippedCount)" -ForegroundColor White
Write-Host "  Correct guards:  $correctCount" -ForegroundColor Green
Write-Host "  Preserved guards: $preservedCount" -ForegroundColor Cyan

if ($WhatIf) {
    $incorrectCount = $totalFiles - $correctCount - $preservedCount - $skippedCount
    Write-Host "  Would fix:       $incorrectCount" -ForegroundColor Yellow
    Write-Host "`n🔄 Re-run without -WhatIf to apply changes." -ForegroundColor Yellow
} else {
    Write-Host "  Fixed guards:    $fixedCount" -ForegroundColor Green
    Write-Host "  Failed to fix:   $failedCount" -ForegroundColor Red
    
    if ($fixedCount -gt 0) {
        Write-Host "`n🎉 Successfully fixed $fixedCount include guard(s)!" -ForegroundColor Green
    }
    
    if ($preservedCount -gt 0) {
        Write-Host "🔒 Preserved $preservedCount special include guard(s)." -ForegroundColor Cyan
    }
    
    if ($skippedCount -gt 0) {
        Write-Host "⏭️  Skipped $skippedCount file(s)." -ForegroundColor DarkGray
    }
    
    if ($failedCount -gt 0) {
        Write-Host "`n⚠️  Failed to fix $failedCount file(s). Check the errors above." -ForegroundColor Red
        exit 1
    } elseif ($fixedCount -eq 0 -and ($correctCount + $preservedCount) -eq ($totalFiles - $skippedCount)) {
        Write-Host "`n🎉 All include guards are correct!" -ForegroundColor Green
        exit 0
    } else {
        exit 0
    }
} 