# PARAMETER LIST FOR SCRIPT
Param(
    [Parameter(HelpMessage = "REPO")]
    [string]$REPO = "teikitu_release"
)

# Get the list of workflow runs
$allWorkflowsJson = Invoke-WebRequest -Uri ('https://api.github.com/repos/teikitu-rti/teikitu_release/actions/workflows') -Headers @{Authorization = "Bearer $env:GH_TOKEN"} -Method Get
$allWorkflows = $allWorkflowsJson | ConvertFrom-Json
foreach ($workflow in $allWorkflows.workflows) {
    gh workflow run $workflow.id
}
