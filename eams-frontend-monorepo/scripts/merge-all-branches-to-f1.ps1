# merge-all-branches-to-f1.ps1
# 批量将所有 f1 派生的子分支合并到主分支 f1
# 遇到合并冲突时自动中止，并记录失败分支
# 用法：powershell -ExecutionPolicy Bypass -File .\scripts\merge-all-branches-to-f1.ps1

$ErrorActionPreference = "Stop"
$originalBranch = (git rev-parse --abbrev-ref HEAD).Trim()
Write-Host "当前分支：$originalBranch" -ForegroundColor Cyan

Write-Host "`n正在从远程拉取最新引用..." -ForegroundColor Yellow
git fetch origin

$remoteBranches = (git branch -r) |
    ForEach-Object { $_.Trim() } |
    Where-Object { $_ -match "^origin/f1-" } |
    ForEach-Object { $_ -replace "^origin/", "" }

Write-Host "`n将合并进 f1 的子分支列表：" -ForegroundColor Yellow
$remoteBranches | ForEach-Object { Write-Host "  - $_" }

# 切换到 f1 主分支
Write-Host "`n正在切换到 f1..." -ForegroundColor Cyan
$localBranches = (git branch) | ForEach-Object { $_.Trim() -replace "^\* ", "" }
$f1LocalExists = $localBranches -contains "f1"

if ($f1LocalExists) {
    git checkout f1
    git pull origin f1
} else {
    git checkout -b f1 origin/f1
}

$successList = [System.Collections.Generic.List[string]]::new()
$failList    = [System.Collections.Generic.List[string]]::new()

foreach ($branch in $remoteBranches) {
    Write-Host "`n=======================================" -ForegroundColor DarkGray
    Write-Host "合并：$branch -> f1" -ForegroundColor Green

    $mergeSucceeded = $false

    try {
        Write-Host "  正在合并 origin/$branch ..." -ForegroundColor Gray
        # 采用默认 merge 策略：能 fast-forward 就 fast-forward，避免滥用 --no-ff 产生多余合并节点
        # 同时不使用管道，避免 $ErrorActionPreference=Stop 将 git 钩子的 stderr 信息误判为致命错误
        git merge "origin/$branch" --no-edit

        if ($LASTEXITCODE -ne 0) {
            throw "合并退出码 $LASTEXITCODE"
        }

        $mergeSucceeded = $true

        # 每次合并成功后立即推送 f1（不使用管道，以便 $LASTEXITCODE 反映 git push 的真实结果）
        Write-Host "  正在推送 f1 到远程..." -ForegroundColor Gray
        git push origin f1

        if ($LASTEXITCODE -ne 0) {
            throw "推送失败，退出码 $LASTEXITCODE"
        }

        $successList.Add($branch)
        Write-Host "  成功" -ForegroundColor Green
    } catch {
        $failList.Add($branch)
        Write-Host "  冲突或失败：$_" -ForegroundColor Red

        if ($mergeSucceeded) {
            Write-Host "  说明：合并已在本地完成，但推送失败。可稍后执行：git push origin f1" -ForegroundColor Yellow
        } else {
            Write-Host "  正在中止合并..." -ForegroundColor Yellow
            git merge --abort 2>$null
        }
    }
}

# 回到原分支
Write-Host "`n正在切回原分支：$originalBranch" -ForegroundColor Cyan
git checkout $originalBranch

Write-Host "`n========== 执行结果汇总 ==========" -ForegroundColor Yellow

if ($successList.Count -gt 0) {
    Write-Host "已合并进 f1（共 $($successList.Count) 个）：" -ForegroundColor Green
    $successList | ForEach-Object { Write-Host "  [成功] $_" -ForegroundColor Green }
}

if ($failList.Count -gt 0) {
    Write-Host "合并冲突或失败（共 $($failList.Count) 个）：" -ForegroundColor Red
    $failList | ForEach-Object { Write-Host "  [失败] $_" -ForegroundColor Red }
    Write-Host "`n说明：失败分支可能因合并冲突被中止；若提示推送失败，请手动执行 git push origin f1。" -ForegroundColor Yellow
} elseif ($remoteBranches.Count -eq 0) {
    Write-Host "未找到匹配的 origin/f1-* 子分支，未执行合并。" -ForegroundColor Yellow
} else {
    Write-Host "全部子分支均已成功合并到 f1 并推送。" -ForegroundColor Green
}
