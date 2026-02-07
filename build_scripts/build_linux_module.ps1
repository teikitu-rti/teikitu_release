# PARAMETER LIST FOR SCRIPT
Param(
    [Parameter(HelpMessage = "Clean the intermediate and target directories")]
    [switch]$CLEAN,

    [Parameter(HelpMessage = "Run cmake with --fresh")]
    [switch]$FRESH,

    [Parameter(Mandatory=$true, HelpMessage = "Module name")]
    [string]$MODULE
)


# Validate that we are working in the correct path

if (-not (Test-Path .\powershell_functions.ps1 -PathType Leaf))
{
    Write-Host -ForegroundColor Red "Powershell Functions script not found."
    Return
}
if (-not (Test-Path .\cmake_command.ps1 -PathType Leaf))
{
    Write-Host -ForegroundColor Red "Windows Terminal build script for cmake not found."
    Return
}
if (-not (Test-Path ..\teikitu.md -PathType Leaf))
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



# START PROCESS ARGUMENT PARAMETER

$START_PROCESS_ARGUMENT_COMMON=@("$PSScriptRoot\cmake_command.ps1")

If ($PSBoundParameters.verbose)
{
    $START_PROCESS_ARGUMENT_COMMON += "-VERBOSE"
}

If ($PSBoundParameters.debug)
{
    $START_PROCESS_ARGUMENT_COMMON += "-DEBUG"
    $START_PROCESS_ARGUMENT_COMMON += "-CMAKE_LOG_LEVEL:STATUS"
}

If ($CLEAN -or $FRESH)
{
    $START_PROCESS_ARGUMENT_COMMON += "-FRESH"
}

If ($CLEAN)
{
    $START_PROCESS_ARGUMENT_COMMON += "-CLEAN"
}

$START_PROCESS_ARGUMENT_COMMON += "-MODULE:" + $MODULE.ToUpper()
$START_PROCESS_ARGUMENT_COMMON += "-THREAD:POSIX"
$START_PROCESS_ARGUMENT_COMMON += "-OS:POSIX"
$START_PROCESS_ARGUMENT_COMMON += "-DEVICE:DESKTOP"
$START_PROCESS_ARGUMENT_COMMON += "-CPU:C17_X64"



$SCRIPT_COMMAND_LINE = [string]::Concat($START_PROCESS_ARGUMENT_COMMON, " -IDE:NINJA", " -COMPILER:CLANG", " -BUILD_TYPE:DEBUG")
if ($PSBoundParameters.debug) { Write-Host -fore cyan "SCRIPT ARGUMENTS: $SCRIPT_COMMAND_LINE" }
Invoke-Expression $SCRIPT_COMMAND_LINE
if ($LASTEXITCODE -ne 0) { Write-Host -ForegroundColor Red "ERROR EXIT CODE - Issue during build."; Exit $LASTEXITCODE }

Exit 0
