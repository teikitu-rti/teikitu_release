# Get the list of workflow runs
$workflowRuns = Invoke-WebRequest -Uri ('https://api.github.com/repos/teikitu-rti/teikitu_release/actions/runs') -Headers @{Authorization = "Bearer $env:GH_TOKEN"} -Method Get

# Filter active runs (queued or in_progress) and cancel them
$workflowObjects = $workflowRuns.Content | ConvertFrom-Json

# Loop through the runs and print the relevant information
foreach ($run in $workflowObjects.workflow_runs) {
    Write-Host "Run ID: $($run.id)"
    Write-Host "Status: $($run.status)"
    Write-Host "Started at: $($run.started_at)"
    Write-Host "Completed at: $($run.completed_at)"
    Write-Host "Job ID: $($run.job_id)"
    Write-Host "Workflow ID: $($run.workflow_id)"
    Write-Host "----------------------------------------"
}