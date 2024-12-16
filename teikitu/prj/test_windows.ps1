# PARAMETER LIST FOR SCRIPT
Param(
    [Parameter(HelpMessage = "Clean directory")]
    [switch]$CLEAN,

    [Parameter(HelpMessage = "Debug")]
    [switch]$TRACE
)

. $PSScriptRoot\powershell_functions.ps1

$TRACE_SWITCH=$false
If ($TRACE)
{
    # Write-Debug "TRACE_SWITCH 1"
    $TRACE_SWITCH=$true
}




# START PROCESS ARGUMENT PARAMETER

$START_PROCESS_ARGUMENT_COMMON=@("-NonInteractive")
$START_PROCESS_ARGUMENT_COMMON+="-File .\windows_terminal_build_cmake_command.ps1"

If ($PSBoundParameters.debug)
{
    $START_PROCESS_ARGUMENT_COMMON += "-Debug"
    $START_PROCESS_ARGUMENT_COMMON += "-LOG_STATUS"
}

If ($PSBoundParameters.verbose)
{
    $START_PROCESS_ARGUMENT_COMMON += "-Verbose"
}

If ($CLEAN)
{
    $START_PROCESS_ARGUMENT_COMMON += "-CLEAN"
}

If ($TRACE)
{
    $START_PROCESS_ARGUMENT_COMMON += "-GITHUB"
}

$START_PROCESS_ARGUMENT_COMMON += "-BUILD"
$START_PROCESS_ARGUMENT_COMMON += "-COMPILER:CLANG"
$START_PROCESS_ARGUMENT_COMMON += "-THREAD:WIN"
$START_PROCESS_ARGUMENT_COMMON += "-OS:WIN"
$START_PROCESS_ARGUMENT_COMMON += "-DEVICE:DESKTOP_X86"
$START_PROCESS_ARGUMENT_COMMON += "-CPU:C11_X64"
$START_PROCESS_ARGUMENT_COMMON += "-IDE:Ninja"




$process_list =@()

@('NONE','REF','DX12') | ForEach-Object {
    $GPU = $_
    @('DEBUG','RELEASE','FINAL','TOOLS') | ForEach-Object {
        $BUILD_TYPE = $_
        $process = Process_Construct -FileName:"powershell.exe" -GITHUB:$TRACE_SWITCH
        $process_list += $process
        try {
            $process.StartInfo.Arguments = $START_PROCESS_ARGUMENT_COMMON + "-BUILD_TYPE:$BUILD_TYPE","-GPU:$GPU"
            if ($PSBoundParameters.debug) { Write-Host -fore cyan "PS1 PROCESS ARGUMENTS: $($process.StartInfo.Arguments)" }
            If ($TRACE_SWITCH)
            {
                # Write-Debug "TRACE_SWITCH 2"
                $process.Start() | Out-Null
                try { Process_Wait_And_Output -process:$process -print_success } finally { $process.Dispose() }
            }
            else
            {
                $process.Start() | Out-Null
            }
        } catch { Write-Output "FAILED: Script Process failed to execute." }
    }
}




if (!$TRACE_SWITCH)
{
    ForEach ($process in $process_list) {
        Process_Wait_And_Output -process:$process -print_success
    }
}
