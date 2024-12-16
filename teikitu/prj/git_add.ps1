# PARAMETER LIST FOR SCRIPT
Param(
    [Parameter(HelpMessage = "GPU")]
    [string]$MODULE
)

$MODULE = $MODULE.ToUpper()
if (Test-Path -Path "..\inc\TgS $MODULE")
{
    git add "..\inc\TgS $MODULE"
    git add "..\src\TgS $MODULE"
    git add "..\tst\src\TgS $MODULE"
}
