# PARAMETER LIST FOR SCRIPT
Param(
    [Parameter(HelpMessage = "REPO")]
    [string]$REPO = "teikitu_release"
)

# GitHub API authentication and repo info
$headers = @{
    Authorization = "Bearer $env:GH_TOKEN"
    Accept = "application/vnd.github.v3+json"
}

# Get all workflows
$workflowsUrl = "https://api.github.com/repos/$env:GH_ORG/$repo/actions/workflows?per_page=100"
$workflows = (Invoke-RestMethod -Uri $workflowsUrl -Headers $headers).workflows

# Run all of the workflows
foreach ($workflow in $workflows) {
    if ($($workflow.state) -ne "active") {
        continue
    }
    gh workflow run $($workflow.id)
}
