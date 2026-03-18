# merge-f1-to-all-branches.ps1
# 批量将 f1 主分支内容合并到所有 f1 派生分支
# 用法：powershell -ExecutionPolicy Bypass -File .\scripts\merge-f1-to-all-branches.ps1

$ErrorActionPreference = "Stop"
$originalBranch = (git rev-parse --abbrev-ref HEAD).Trim()
Write-Host "Current branch: $originalBranch" -ForegroundColor Cyan

Write-Host "`nFetching remote..." -ForegroundColor Yellow
git fetch origin

$remoteBranches = (git branch -r) | ForEach-Object { $_.Trim() } | Where-Object { $_ -match "^origin/f1-" } | ForEach-Object { $_ -replace "^origin/", "" }

Write-Host "`nBranches to merge:" -ForegroundColor Yellow
$remoteBranches | ForEach-Object { Write-Host "  - $_" }

$successList = [System.Collections.Generic.List[string]]::new()
$failList = [System.Collections.Generic.List[string]]::new()

foreach ($branch in $remoteBranches) {
    Write-Host "`n=======================================" -ForegroundColor DarkGray
    Write-Host "Processing: $branch" -ForegroundColor Green

    try {
        $localBranches = (git branch) | ForEach-Object { $_.Trim() -replace "^\* ", "" }
        $localExists = $localBranches -contains $branch

        if ($localExists) {
            Write-Host "  Checking out local branch..." -ForegroundColor Gray
            git checkout $branch
        } else {
            Write-Host "  Creating tracking branch from remote..." -ForegroundColor Gray
            git checkout -b $branch "origin/$branch"
        }

        Write-Host "  Merging origin/f1..." -ForegroundColor Gray
        git merge origin/f1 --no-edit

        Write-Host "  Pushing..." -ForegroundColor Gray
        git push origin $branch

        $successList.Add($branch)
        Write-Host "  OK" -ForegroundColor Green
    } catch {
        $failList.Add($branch)
        Write-Host "  FAILED: $_" -ForegroundColor Red
        git merge --abort 2>$null
    }
}

Write-Host "`n=======================================" -ForegroundColor DarkGray
Write-Host "Returning to: $originalBranch" -ForegroundColor Cyan
git checkout $originalBranch

Write-Host "`n========== Summary ==========" -ForegroundColor Yellow
if ($successList.Count -gt 0) {
    Write-Host "Success ($($successList.Count)):" -ForegroundColor Green
    $successList | ForEach-Object { Write-Host "  OK $_" -ForegroundColor Green }
}
if ($failList.Count -gt 0) {
    Write-Host "Failed ($($failList.Count)):" -ForegroundColor Red
    $failList | ForEach-Object { Write-Host "  FAIL $_" -ForegroundColor Red }
    Write-Host "`nNote: Failed branches may have merge conflicts. Please resolve manually." -ForegroundColor Yellow
}
