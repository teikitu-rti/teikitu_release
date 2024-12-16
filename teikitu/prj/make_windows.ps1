# PARAMETER LIST FOR SCRIPT
Param(
    [Parameter(HelpMessage = "Clean the intermediate and target directories")]
    [switch]$CLEAN,

    [Parameter(HelpMessage = "Run cmake with --fresh")]
    [switch]$FRESH,

    [Parameter(HelpMessage = "Build directory")]
    [switch]$BUILD,

    [Parameter(HelpMessage = "Debug")]
    [switch]$TRACE,

    [Parameter(HelpMessage = "GPU")]
    [string]$GPU
)

. $PSScriptRoot\powershell_functions.ps1

$TRACE_SWITCH=$false
If ($TRACE)
{
    # Write-Debug "TRACE_SWITCH 1"
    $TRACE_SWITCH=$true
}

If ($CLEAN)
{
    try { remove-item ..\bin -Recurse -Force -ErrorAction Stop } catch [System.Exception] { switch($_.Exception.GetType().FullName) { 'System.Management.Automation.ItemNotFoundException' {} default { throw $error[0] } } }
    try { remove-item ..\lib -Recurse -Force -ErrorAction Stop } catch [System.Exception] { switch($_.Exception.GetType().FullName) { 'System.Management.Automation.ItemNotFoundException' {} default { throw $error[0] } } }
    try { remove-item ..\obj -Recurse -Force -ErrorAction Stop } catch [System.Exception] { switch($_.Exception.GetType().FullName) { 'System.Management.Automation.ItemNotFoundException' {} default { throw $error[0] } } }
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

If ($CLEAN -or $FRESH)
{
    $START_PROCESS_ARGUMENT_COMMON += "-FRESH"
}

If ($GPU)
{
    $START_PROCESS_ARGUMENT_COMMON += "-GPU:$GPU"
}

If ($BUILD)
{
    $START_PROCESS_ARGUMENT_COMMON += "-BUILD"
}

If ($TRACE)
{
    $START_PROCESS_ARGUMENT_COMMON += "-GITHUB"
}

$START_PROCESS_ARGUMENT_COMMON += "-BUILD_TYPE:DEBUG"




$process_list =@()

@('CLANG','MSVC') | ForEach-Object {
    $process = Process_Construct -FileName:"powershell.exe" -GITHUB:$TRACE_SWITCH
    $process_list += $process
    try {
        $process.StartInfo.Arguments = $START_PROCESS_ARGUMENT_COMMON + "-COMPILER:$_","-THREAD:WIN","-OS:WIN","-DEVICE:DESKTOP_X86","-CPU:C11_X64"
        if ($PSBoundParameters.debug) { Write-Host -fore cyan "PS1 PROCESS ARGUMENTS: $($process.StartInfo.Arguments)" }
        $process.Start() | Out-Null
        If ($TRACE_SWITCH)
        {
            try { Process_Wait_And_Output -process:$process -print_success } finally { $process.Dispose() }
        }
    } catch { Write-Host -ForegroundColor Red "FAILED: Script Process failed to execute." }

    $process = Process_Construct -FileName:"powershell.exe" -GITHUB:$TRACE_SWITCH
    $process_list += $process
    try {
        $process.StartInfo.Arguments = $START_PROCESS_ARGUMENT_COMMON + "-COMPILER:$_","-THREAD:WIN","-OS:WIN","-DEVICE:DESKTOP_X86","-CPU:C11_X64", "-OS_WIDE"
        if ($PSBoundParameters.debug) { Write-Host -fore cyan "PS1 PROCESS ARGUMENTS: $($process.StartInfo.Arguments)" }
        $process.Start() | Out-Null
        If ($TRACE_SWITCH)
        {
            try { Process_Wait_And_Output -process:$process -print_success} finally { $process.Dispose() }
        }
    } catch { Write-Host -ForegroundColor Red "FAILED: Script Process failed to execute." }
}




if (!$TRACE_SWITCH)
{
    ForEach ($process in $process_list) {
        Process_Wait_And_Output -process:$process -print_success
    }
}
