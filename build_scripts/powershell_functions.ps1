If ($DebugPreference -eq "Stop" -or $DebugPreference -eq "Inquire") {
    $DebugPreference = "Continue"
}
$ErrorActionPreference = "Stop"

function DrawConsoleColours {
    [cmdletbinding()]
    $colors = [enum]::GetValues([System.ConsoleColor])
    Foreach ($bgcolor in $colors){
        Foreach ($fgcolor in $colors) { Write-Host "$fgcolor|"  -ForegroundColor $fgcolor -BackgroundColor $bgcolor -NoNewLine }
        Write-Host " on $bgcolor"
    }
}

Function Process_Construct {
    [cmdletbinding()]
    Param (
        [Parameter(Mandatory=$True)]
        [string]$FileName
    )
    $process = New-Object System.Diagnostics.Process
    if ($process -ne $null) {
        $process.StartInfo = New-Object System.Diagnostics.ProcessStartInfo
        $process.StartInfo.FileName = $FileName
        $process.StartInfo.UseShellExecute = $false
        $process.StartInfo.WorkingDirectory = $PSScriptRoot
        $process.StartInfo.RedirectStandardError = $true            # When debugging, comment this out
        $process.StartInfo.RedirectStandardOutput = $true           # When debugging, comment this out
        $process.StartInfo.WindowStyle = "Hidden"                   # When debugging, comment this out
    }
    return $process
}


Function Process_Wait_And_Output_Internal {
    [cmdletbinding()]
    Param (
        [Parameter(Mandatory = $true)][AllowNull()][System.Diagnostics.Process]$process
    )
    if ($null -eq $process) {
        Write-Host -ForegroundColor Red -Message "Process is NULL"
        Return
    }

    while (!$process.HasExited)
    {
        $process.WaitForExit(1000) | Out-Null

        if ($process.StandardOutput -ne $null) {
            $stdout = $process.StandardOutput.ReadToEnd()
        }

        if ($process.StandardError -ne $null) {
            $stderr = $process.StandardError.ReadToEnd()
        }
    }

    if (![string]::IsNullOrEmpty($stderr)) {
        $argument_list = $process.StartInfo.Arguments -join ' '
        if (![string]::IsNullOrEmpty($argument_list)) {
            Write-Host -ForegroundColor Red -Message "Command line: $argument_list"
        }
        Write-Host -ForegroundColor Red -Message "Standard Error from Script`n$stderr"

        if (![string]::IsNullOrEmpty($stdout)) {
            Write-Host -Fore white "Standard Output from Script`n$stdout"
        }
    } elseif ($process.ExitCode -ne 0) {
        $command_line_string = $process.StartInfo.Arguments -join " "
        Write-Host -ForegroundColor Red -Message "Error with Command Line: $command_line_string"
    }
}

Function Process_Wait_And_Output {
    [cmdletbinding()]
    Param (
        [Parameter(Mandatory = $true)][AllowNull()][System.Diagnostics.Process]$process,
        [Parameter()][switch]$print_success
    )

    try {
        Process_Wait_And_Output_Internal -process:$process
        if ($print_success) {
            $command_line_string = $process.StartInfo.Arguments -join " "
            Write-Host -fore green "Command Completed: $command_line_string"
        }
    }
    catch [Microsoft.PowerShell.Commands.WriteErrorException] {
        # Print error messages (without stacktrace)
        Write-Host -ForegroundColor Red $_.Exception.Message
        Return
    }
    catch [System.Management.Automation.RuntimeException] {
        if ($_.Exception -is [Microsoft.PowerShell.Commands.WriteErrorException]) {
            # Print error messages (without stacktrace)
            Write-Host -ForegroundColor Red $_.Exception.Message
            Return
        }

        # A thrown string
        Write-Host -ForegroundColor Red $_.Exception.Message
        Write-Host -ForegroundColor Red $_.ScriptStackTrace
        Return
    }
    catch {
        # Print proper exception message (including stack trace)
        Write-Host -ForegroundColor Red "$($_.Exception.GetType().Name): $($_.Exception.Message)"
        Write-Host -ForegroundColor Red $_.ScriptStackTrace
        Return
    }
    finally {
        $process.Dispose()
    }
}
