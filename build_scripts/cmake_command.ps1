# PARAMETER LIST FOR SCRIPT
Param(
# --------------------------------------------------------------------------------------------------------------
    [Parameter(HelpMessage = "Text used to invoke CMake")]
    [string]$CMAKE_CMD,

    [Parameter(HelpMessage = "Clean directory")]
    [switch]$CLEAN,

    [Parameter(HelpMessage = "Run cmake with --fresh")]
    [switch]$FRESH,

    [Parameter(HelpMessage = "Build the target")]
    [switch]$BUILD,

    [Parameter(HelpMessage = "CMake Log Level")]
    [ValidateSet("TRACE", "DEBUG", "VERBOSE", "STATUS", "WARNING", "ERROR", "FATAL")]
    [string]$CMAKE_LOG_LEVEL="WARNING",

    [Parameter(HelpMessage = "CICD Builds - Github Workflows or CircleCI")]
    [switch]$CICD_BUILD,

    [Parameter(HelpMessage = "Disable the use of multi-process")]
    [switch]$NO_PROCESS,

# --------------------------------------------------------------------------------------------------------------

    [Parameter(HelpMessage = "Build only those projects required for Teikitu")]
    [switch]$TEIKITU,

# --------------------------------------------------------------------------------------------------------------
    [Parameter(HelpMessage = "Select CMAKE Generator")]
    [ValidateSet("MSVC17", "XCODE", "NINJA", "UNIX")]
    [string]$IDE="NINJA",

    [Parameter(HelpMessage = "Select compiler")]
    [ValidateSet("CLANG", "MSVC")]
    [string]$COMPILER="CLANG",

    [Parameter(Mandatory=$true, HelpMessage = "Select target cpu: C11_X64, C11_A64")]
    [ValidateSet("C17_X64", "C17_A64")]
    [string]$CPU,

    [Parameter(Mandatory=$true, HelpMessage = "Select target threading library: WIN POSIX")]
    [ValidateSet("WINDOWS", "POSIX")]
    [string]$THREAD,

    [Parameter(Mandatory=$true)]
    [ValidateSet("WINDOWS", "POSIX", "ANDROID")]
    [string]$OS,

    [Parameter(Mandatory=$true, HelpMessage = "Select target device: DESKTOP_X86")]
    [ValidateSet("DESKTOP")]
    [string]$DEVICE,

    [Parameter(HelpMessage = "Select target gpu: REF, DX12")]
    [ValidateSet("NONE", "REF", "DX12", "VULKAN", "METAL")]
    [string]$GPU="NONE",

    [Parameter(HelpMessage = "Select target gpu: REF, DX12")]
    [ValidateSet("NONE", "REF", "XAUDIO")]
    [string]$AUDIO="NONE",

# --------------------------------------------------------------------------------------------------------------
    [Parameter(HelpMessage = "Module name")]
    [string]$MODULE,

    [Parameter(Mandatory=$true, HelpMessage = "Select a build type: DEBUG, RELEASE, FINAL, TOOLS_DEBUG, TOOLS_RELEASE")]
    [ValidateSet("DEBUG", "RELEASE", "FINAL", "TOOLS_DEBUG", "TOOLS_RELEASE")]
    [string]$BUILD_TYPE

# --------------------------------------------------------------------------------------------------------------
)



# Powershell host operating system check

if (-not $PSVersionTable.Platform -eq "Unix" -and -not $PSVersionTable.Platform -eq "Win32NT")
{
    Write-Host -ForegroundColor Red "Powershell executing on unsupported host operating system."
    Return
}



# Validate that we are working in the correct path

if (-not (Test-Path .\powershell_functions.ps1))
{
    Write-Host -ForegroundColor Red "Powershell Functions script not found."
    Return
}
if (-not (Test-Path ..\teikitu.md))
{
    Write-Host -ForegroundColor Red "Teikitu Markdown file marking the depot root not found."
    Return
}
$depotHash = Get-FileHash ..\teikitu.md
if ($depotHash.Hash -ne "D4933F9808773FB621C79ECB07F0087B149AA4CCCA359815884024361DB928F5")
{
    Write-Host -ForegroundColor Red "Teikitu Markdown file hash not as expected."
    Return
}



. $PSScriptRoot\powershell_functions.ps1



# IDE AND COMPILER MATCH CHECK
if ($IDE -match "MSVC17")
{
    If (-not $COMPILER -match "MSVC")
    {
        Write-Host -ForegroundColor Red "MSVC IDE is only supported with the MSVC Compiler."
        Return
    }
}
elseif ($IDE -match "NINJA")
{
    if (-not $COMPILER -match "CLANG")
    {
        Write-Host -ForegroundColor Red "Unsupported compiler option for Ninja."
        Return
    }
}
elseif ($IDE -match "XCODE")
{
    $COMPILER = 'CLANG'
}
elseif ($IDE -match "UNIX")
{
    if (-not $COMPILER -match "CLANG")
    {
        Write-Host -ForegroundColor Red "Unsupported compiler option for Ninja."
        Return
    }
}



# BUILD PATH

if ($IDE -match "MSVC17")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
elseif ($IDE -match "NINJA")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
elseif ($IDE -match "XCODE")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
elseif ($IDE -match "UNIX")
{
    $CMAKE_BUILD_PATH = $IDE.ToLower()
}
$CMAKE_BUILD_PATH += "_" + $COMPILER.ToLower()
$CMAKE_BUILD_PATH += "_" + $CPU.ToLower()
$CMAKE_BUILD_PATH += "_" + $THREAD.ToLower()
$CMAKE_BUILD_PATH += "_" + $OS.ToLower()
$CMAKE_BUILD_PATH += "_" + $DEVICE.ToLower()
$CMAKE_BUILD_PATH += "_" + $GPU.ToLower()
$CMAKE_BUILD_PATH += "_" + $AUDIO.ToLower()
if ($IDE -match "NINJA" -or $IDE -match "UNIX")
{
    $CMAKE_BUILD_PATH += "_" + $BUILD_TYPE.ToLower()
}

if ($PSBoundParameters.debug -and $PSBoundParameters.verbose) { Write-Host -fore DarkYellow "BUILD PATH: $CMAKE_BUILD_PATH" }




# Build Directory Validations and Teikitu External
If ($CLEAN -and (Test-Path -Path "..\build\$CMAKE_BUILD_PATH"))
{
    try { remove-item "..\build\$CMAKE_BUILD_PATH" -Recurse -Force -ErrorAction Stop } catch { Write-Host -Fore red "FAILED: CLEAN remove directory and files."; Exit 1 }
}




# BUILD COMMON COMMAND LINE
$CMAKE_BUILD_COMMON_CMD=@() # Empty Array

If ($CMAKE_CMD)
{
    $CMAKE_BUILD_COMMON_CMD += $CMAKE_CMD
}
else
{
    if ($PSVersionTable.Platform -eq "Unix")
    {
        $CMAKE_BUILD_COMMON_CMD += "cmake"
        $CMAKE_CMD = "cmake"
    }
    elseif ($PSVersionTable.Platform -eq "Win32NT")
    {
        $CMAKE_BUILD_COMMON_CMD += "cmake.exe"
        $CMAKE_CMD = "cmake.exe"
    }
}

$CMAKE_BUILD_COMMON_CMD += "-DCMAKE_MESSAGE_LOG_LEVEL=$CMAKE_LOG_LEVEL"

If ($FRESH)
{
    $CMAKE_BUILD_COMMON_CMD += "--fresh"
}

if ($IDE -match "MSVC17")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Visual Studio 17 2022"' 

    If ($CPU -match "C17_X64")
    {
        $CMAKE_BUILD_COMMON_CMD += "-A x64"
    }
}
elseif ($IDE -match "NINJA")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Ninja"'
}
elseif ($IDE -match "XCODE")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Xcode"'
}
elseif ($IDE -match "UNIX")
{
    $CMAKE_BUILD_COMMON_CMD += '-G "Unix Makefiles"'
}

$CMAKE_BUILD_COMMON_CMD += "-DCMAKE_BUILD_TYPE=" + $BUILD_TYPE.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__TARGET_HARDWARE=" + $CPU.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__THREAD=" + $THREAD.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__OS=" + $OS.ToUpper()
if ($OS -match "ANDROID")
{
    $CMAKE_BUILD_COMMON_CMD += '-UANDROID_NDK_TOOLCHAIN_INCLUDED'
    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_TOOLCHAIN_FILE="' + $env:ANDROID_NDK_HOME + '/build/cmake/android.toolchain.cmake"'
    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_ANDROID_NDK="' + $env:ANDROID_NDK_HOME + '"'

    # Configuration for android-legacy.toolchain.cmakle
    $CMAKE_BUILD_COMMON_CMD += '-DANDROID_TOOLCHAIN=clang'
    $CMAKE_BUILD_COMMON_CMD += '-DANDROID_ABI=arm64-v8a'
    $CMAKE_BUILD_COMMON_CMD += '-DANDROID_PLATFORM=latest'
    $CMAKE_BUILD_COMMON_CMD += '-DANDROID_STL=c++_shared'
    $CMAKE_BUILD_COMMON_CMD += '-DANDROID_ARM_MODE=arm'

    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER'
    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY'
    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY'
    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ONLY'

    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY'
}
else
{
    if ($IDE -match "NINJA")
    {
        $CMAKE_BUILD_COMMON_CMD += '-G "Ninja"'
    
        if ($COMPILER -match "CLANG")
        {
            if ($PSVersionTable.Platform -eq "Unix")
            {
                if (Test-Path -Path "/usr/lib/llvm-19/bin/clang") {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_C_COMPILER:PATH="/usr/lib/llvm-19/bin/clang"'
                } elseif (Test-Path -Path "/opt/homebrew/opt/llvm/bin/clang") {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_C_COMPILER:PATH="/opt/homebrew/opt/llvm/bin/clang"'
                } else {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_C_COMPILER:PATH="/usr/bin/clang"'
                }
    
                if (Test-Path -Path "/usr/lib/llvm-19/bin/clang++") {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER:PATH="/usr/lib/llvm-19/bin/clang++"'
                } elseif (Test-Path -Path "/opt/homebrew/opt/llvm/bin/clang++") {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER:PATH="/opt/homebrew/opt/llvm/bin/clang++"'
                } else {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER:PATH="/usr/bin/clang++"'
                }
    
                if (Test-Path -Path "/usr/lib/llvm-19/bin/clang-scan-deps") {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER_CLANG_SCAN_DEPS:PATH="/usr/lib/llvm-19/bin/clang-scan-deps"'
                } elseif (Test-Path -Path "/opt/homebrew/opt/llvm/bin/clang-scan-deps") {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER_CLANG_SCAN_DEPS:PATH="/opt/homebrew/opt/llvm/bin/clang-scan-deps"'
                } else {
                    $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER_CLANG_SCAN_DEPS:PATH="/usr/bin/clang-scan-deps"'
                }
            }
            elseif ($PSVersionTable.Platform -eq "Win32NT")
            {
                $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_C_COMPILER:PATH="C:\Program Files\LLVM\bin\clang.exe"'
                $CMAKE_BUILD_COMMON_CMD += '-DCMAKE_CXX_COMPILER:PATH="C:\Program Files\LLVM\bin\clang++.exe"'
            }
        }
    }
}
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__DEVICE=" + $DEVICE.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__OS_TEXT_WIDE=1"
$CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__GRAPHICS=" + $GPU.ToUpper()
$CMAKE_BUILD_COMMON_CMD += "-DMK_FEATURE__AUDIO=" + $AUDIO.ToUpper()

if ($CICD_BUILD)
{
    # $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__AUTOMATION=CICD_BUILD"
    $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__LOG_TO_FILE=0"
}
else
{
    # $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__AUTOMATION=NONE"
    $CMAKE_BUILD_COMMON_CMD += "-DMK_BUILD__LOG_TO_FILE=1"
}

if ($MODULE)
{
    $CMAKE_BUILD_COMMON_CMD += '-DMK_BUILD__LIST=' + $MODULE.ToUpper()
}
else
{
    if ($CICD_BUILD -or $TEIKITU)
    {
        $CMAKE_BUILD_COMMON_CMD += '-DMK_BUILD__LIST="TEIKITU"'
    }
    else
    {
        $CMAKE_BUILD_COMMON_CMD += '-DMK_BUILD__LIST="ALL"'
    }
}

if ($PSBoundParameters.debug -and $PSBoundParameters.verbose) { Write-Host -fore DarkYellow "CMAKE COMMON: $CMAKE_BUILD_COMMON_CMD" }




# BANNER -------------------------------------------------------------------------------------------------------
function Write-HostCenter { param($Message) Write-Host ("{0}{1}" -f (' ' * (([Math]::Max(0, $Host.UI.RawUI.BufferSize.Width / 2) - [Math]::Floor($Message.Length / 2)))), $Message) }

Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)
Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)
Write-Host -ForegroundColor DarkCyan  "----  Target Hardware:" $CPU.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----   Thread Support:" $THREAD.ToUpper()
Write-Host -ForegroundColor DarkCyan  "---- Operating System:" $OS.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----    Target Device:" $DEVICE.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----     Graphics API:" $GPU.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----        Audio API:" $AUDIO.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----       Build Type:" $BUILD_TYPE.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----         Compiler:" $COMPILER.ToUpper()
Write-Host -ForegroundColor DarkCyan  "----    Build Manager:" $IDE.ToUpper()
Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)
Write-Host -ForegroundColor DarkCyan  $("-" * $Host.UI.RawUI.BufferSize.Width)

# BUILD TEIKITU EXTERNAL COMMAND LINE --------------------------------------------------------------------------

# CMAKE COMMAND LINE
$CMAKE_CONFIGURE_COMMAND_LINE = [string]::Concat(${CMAKE_BUILD_COMMON_CMD}, ' -S .. -B "..\build\', ${CMAKE_BUILD_PATH}, '"')
if ($PSBoundParameters.debug -or $PSBoundParameters.verbose) { Write-Host -fore cyan "CMAKE PROJECT ARGUMENTS: $CMAKE_CONFIGURE_COMMAND_LINE" }
Invoke-Expression $CMAKE_CONFIGURE_COMMAND_LINE
if ($LASTEXITCODE -ne 0)
{
    Write-Host -ForegroundColor Red "ERROR EXIT CODE - Issue during build.";
    Exit $LASTEXITCODE
}

# BUILD COMMAND
$CMAKE_BUILD_COMMAND_LINE = [string]::Concat(${CMAKE_CMD}, ' --build "..\build\', ${CMAKE_BUILD_PATH}, '"', ' --config ', $BUILD_TYPE.ToUpper())
if ($PSBoundParameters.debug -or $PSBoundParameters.verbose) { $CMAKE_BUILD_COMMAND_LINE += " --verbose" }
if ($IDE -match "MSVC17")
{
    $CMAKE_BUILD_COMMAND_LINE += " --"
    $CMAKE_BUILD_COMMAND_LINE += " /nologo"
    $CMAKE_BUILD_COMMAND_LINE += " /detailedSummary:True" # Show detailed information at the end of the build log about the configurations that were built and how they were scheduled to nodes.
    $CMAKE_BUILD_COMMAND_LINE += " /maxCpuCount" # The default value is 1. If you include this switch without specifying a value, MSBuild will use up to the number of processors.

    If ($PSBoundParameters.verbose)
    {
        $CMAKE_BUILD_COMMAND_LINE += " /verbosity:detailed"
    }
    
    If ($PSBoundParameters.debug)
    {
        $CMAKE_BUILD_COMMAND_LINE += " /bl"
    }    
}
if ($PSBoundParameters.debug -or $PSBoundParameters.verbose) { Write-Host -fore cyan "$CMAKE_BUILD_COMMAND_LINE" }
Invoke-Expression $CMAKE_BUILD_COMMAND_LINE
if ($LASTEXITCODE -ne 0)
{
    Write-Host -ForegroundColor Red "ERROR EXIT CODE - Issue during build.";
    Exit $LASTEXITCODE
}
