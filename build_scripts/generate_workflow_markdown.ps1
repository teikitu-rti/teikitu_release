# GitHub API authentication and repo info
$headers = @{
    Authorization = "Bearer $env:GH_TOKEN"
    Accept = "application/vnd.github.v3+json"
}

function Get-GitHubWorkflowRuns {
    param(
        [string]$owner,
        [string]$repo
    )

    $url = "https://api.github.com/repos/$owner/$repo/actions/runs?per_page=100"
    $allRuns = @()

    while ($url) {
        try {
            $response = Invoke-RestMethod -Uri $url -Headers $headers -Method Get
            $allRuns += $response.workflow_runs

            # Parse Link header for next page
            $linkHeader = $response.Headers.Link
            if ($linkHeader) {
                $links = @{}
                $linkHeader.Split(',') | ForEach-Object {
                    if ($_ -match '<(.+?)>;\s*rel="(.+?)"') {
                        $links[$matches[2]] = $matches[1]
                    }
                }
                $url = $links['next']
            }
            else {
                $url = $null
            }
        }
        catch {
            Write-Error "Error fetching workflow runs: $_"
            break
        }
    }

    return $allRuns
}

# Mardown content for both repositories
$markdown = ""

# Repositiory titles
$repo_titles = @{
    "teikitu" = '### Internal Development Build Status'
    "teikitu_release" = '### Public Release Build Status'
}

@('teikitu','teikitu_release') | ForEach-Object {
    $repo = $_
    $UniqueBuildGroup = [System.Collections.Generic.HashSet[string]]::new()
    $RunDataForMarkdown = @()

    # Get all workflows
    $workflowsUrl = "https://api.github.com/repos/$env:GH_ORG/$repo/actions/workflows?per_page=100"
    $workflows = (Invoke-RestMethod -Uri $workflowsUrl -Headers $headers).workflows

    # Initialize markdown content
    $markdown += "$($repo_titles[$_])`n`n"
    $markdown += "| Build-Compiler-C STD-CPU-Thread-OS-Device-GPU API-Audio | Status |`n"
    $markdown += "|:-:|:-:|`n"

    foreach ($workflow in $workflows) {
        # Get workflow filename from path
        $workflowFile = Split-Path $workflow.path -Leaf
        if (-not $workflowFile.StartsWith("build__")) {
            continue
        }

        # Get latest run for this workflow and the corresponding date in UTC
        $runsUrl = "https://api.github.com/repos/$env:GH_ORG/$repo/actions/workflows/$($workflow.id)/runs?per_page=100"
        $runs = (Invoke-RestMethod -Uri $runsUrl -Headers $headers).workflow_runs

        $lastRun = if ($runs.Count -gt 0) {
            $lastRunDate = [DateTime]::Parse($runs[0].updated_at).ToUniversalTime()
            $lastRunDateString = $lastRunDate.ToString("yyyy/MM/dd HH:mm UTC")
            [uri]::EscapeDataString($lastRunDateString)
        } else {
            continue
        }

        # Get the build group
        $build_group = $workflowFile
        $build_group = [System.IO.Path]::GetFileNameWithoutExtension($build_group)
        $build_group = $build_group.Substring(0, $build_group.LastIndexOf('_'))
        if ($build_group.Substring($build_group.LastIndexOf('_')).StartsWith('_tools')) {
            $build_group = $build_group.Substring(0, $build_group.LastIndexOf('_'))
        }
        $build_group = $build_group.Substring($build_group.IndexOf('_')+1)
        $build_group = $build_group.Substring($build_group.IndexOf('_')+1)
        $build_group = $build_group.Substring($build_group.IndexOf('_')+1)

        #![Static Badge](https://img.shields.io/badge/Debug-Success-2EA043?style=flat-square&logo=github&labelColor=333333)
        $badgeLabel = [uri]::EscapeDataString($($workflow.name))
        if ($runs[0].conclusion -match 'success') {
            $badgeUrl = "https://img.shields.io/badge/$badgeLabel-Success-2EA043?style=flat-square&logo=github&labelColor=333333"
        } elseif ($runs[0].conclusion -match 'failure') {
            $badgeUrl = "https://img.shields.io/badge/$badgeLabel-Failure-E0484D?style=flat-square&logo=github&labelColor=333333"
        } elseif ($runs[0].conclusion -match 'cancelled') {
            $badgeUrl = "https://img.shields.io/badge/$badgeLabel-Cancelled-959DA5?style=flat-square&logo=github&labelColor=333333"
        } else {
            continue
        }

        # ![Static Badge](https://img.shields.io/badge/-$lastRun-blue?style=flat-square)
        $dateUrl = "https://img.shields.io/badge/-$lastRun-blue?style=flat-square"

        # Create markdown line
        $null = $UniqueBuildGroup.Add($build_group)
        $RunDataForMarkdown += [PSCustomObject]@{
            build_group = $build_group
            badgeUrl = $badgeUrl
            dateUrl = $dateUrl
            workflow = $workflow
            label = $($workflow.name)
        }
    }

    foreach ($build_group in $UniqueBuildGroup) {
        $RunDataForLookup = @{}
        foreach ($RunData in $RunDataForMarkdown) {
            if ($RunData.build_group -ne $build_group) {
                continue
            }

            $RunDataForLookup.Add($RunData.label,$RunData)
        }

        $markdown += "| ``$build_group`` | "
        $RunData = $RunDataForLookup['Debug']
        $markdown += "[![]($($RunData.badgeUrl))![]($($RunData.dateUrl))]($($RunData.workflow.html_url))<br>"
        $RunData = $RunDataForLookup['Release']
        $markdown += "[![]($($RunData.badgeUrl))![]($($RunData.dateUrl))]($($RunData.workflow.html_url))<br>"
        $RunData = $RunDataForLookup['Final']
        $markdown += "[![]($($RunData.badgeUrl))![]($($RunData.dateUrl))]($($RunData.workflow.html_url))<br>"
        $RunData = $RunDataForLookup['Tools Debug']
        $markdown += "[![]($($RunData.badgeUrl))![]($($RunData.dateUrl))]($($RunData.workflow.html_url))<br>"
        $RunData = $RunDataForLookup['Tools Release']
        $markdown += "[![]($($RunData.badgeUrl))![]($($RunData.dateUrl))]($($RunData.workflow.html_url))<br>"
        $markdown += "|`n"
    }
    $markdown += "`n"
}

# Write to file
$fileContent = Get-Content -Path '../README.template' -Encoding utf8
$fileContent = $fileContent -replace '<!-- WORKFLOW_STATUS -->', $markdown
$fileContent | Out-File -FilePath "../README.md" -Encoding utf8

Write-Host "Markdown file generated: workflow-status.md"