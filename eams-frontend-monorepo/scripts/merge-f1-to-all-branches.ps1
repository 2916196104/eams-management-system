# merge-f1-to-all-branches.ps1
# 批量将 f1 主分支内容合并到所有 f1 派生子分支
# 遇到合并冲突时自动中止合并；合并成功但推送失败时会提示手动处理
# 用法：powershell -ExecutionPolicy Bypass -File .\scripts\merge-f1-to-all-branches.ps1

$ErrorActionPreference = "Stop"
$originalBranch = (git rev-parse --abbrev-ref HEAD).Trim()
Write-Host "当前分支：$originalBranch" -ForegroundColor Cyan

Write-Host "`n正在从远程拉取最新引用..." -ForegroundColor Yellow
git fetch origin

# 若本地 f1 存在且不是当前分支，将其快进同步到 origin/f1
$localBranchesInit = (git branch) | ForEach-Object { $_.Trim() -replace "^\* ", "" }
if ($localBranchesInit -contains "f1" -and $originalBranch -ne "f1") {
    Write-Host "正在将本地 f1 快进同步到 origin/f1..." -ForegroundColor Gray
    git branch -f f1 origin/f1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "警告：本地 f1 快进失败（可能本地有额外提交），将跳过本地更新，继续使用 origin/f1。" -ForegroundColor Yellow
    }
}

$remoteBranches = (git branch -r) |
    ForEach-Object { $_.Trim() } |
    Where-Object { $_ -match "^origin/f1-" } |
    ForEach-Object { $_ -replace "^origin/", "" }

Write-Host "`n将把 origin/f1 合并进下列子分支：" -ForegroundColor Yellow
$remoteBranches | ForEach-Object { Write-Host "  - $_" }

$successList = [System.Collections.Generic.List[string]]::new()
$failList    = [System.Collections.Generic.List[string]]::new()

foreach ($branch in $remoteBranches) {
    Write-Host "`n=======================================" -ForegroundColor DarkGray
    Write-Host "处理：$branch" -ForegroundColor Green

    $mergeSucceeded = $false

    try {
        $localBranches = (git branch) | ForEach-Object { $_.Trim() -replace "^\* ", "" }
        $localExists = $localBranches -contains $branch

        if ($localExists) {
            Write-Host "  正在检出本地分支..." -ForegroundColor Gray
            git checkout $branch
            Write-Host "  正在同步 origin/$branch ..." -ForegroundColor Gray
            git pull --no-edit origin $branch
            if ($LASTEXITCODE -ne 0) {
                throw "拉取子分支失败，退出码 $LASTEXITCODE"
            }
        } else {
            Write-Host "  正在从远程创建跟踪分支..." -ForegroundColor Gray
            git checkout -b $branch "origin/$branch"
        }

        Write-Host "  正在合并 origin/f1 ..." -ForegroundColor Gray
        # 采用默认 merge 策略：能 fast-forward 就 fast-forward，避免滥用 --no-ff 产生多余合并节点
        # 同时不使用管道，避免 $ErrorActionPreference=Stop 将 git 钩子的 stderr 信息误判为致命错误
        git merge origin/f1 --no-edit

        if ($LASTEXITCODE -ne 0) {
            throw "合并退出码 $LASTEXITCODE"
        }

        $mergeSucceeded = $true

        Write-Host "  正在推送到远程..." -ForegroundColor Gray
        # 不使用管道，以便 $LASTEXITCODE 反映 git push 的真实结果
        git push origin $branch

        if ($LASTEXITCODE -ne 0) {
            throw "推送失败，退出码 $LASTEXITCODE"
        }

        $successList.Add($branch)
        Write-Host "  成功" -ForegroundColor Green
    } catch {
        $failList.Add($branch)
        Write-Host "  冲突或失败：$_" -ForegroundColor Red

        if ($mergeSucceeded) {
            Write-Host "  说明：合并已在本地完成，但推送失败。可稍后执行：git push origin $branch" -ForegroundColor Yellow
        } else {
            Write-Host "  正在中止合并..." -ForegroundColor Yellow
            git merge --abort 2>$null
        }
    }
}

Write-Host "`n正在切回原分支：$originalBranch" -ForegroundColor Cyan
git checkout $originalBranch

Write-Host "`n========== 执行结果汇总 ==========" -ForegroundColor Yellow

if ($successList.Count -gt 0) {
    Write-Host "已成功合并并推送（共 $($successList.Count) 个）：" -ForegroundColor Green
    $successList | ForEach-Object { Write-Host "  [成功] $_" -ForegroundColor Green }
}

if ($failList.Count -gt 0) {
    Write-Host "合并冲突或失败（共 $($failList.Count) 个）：" -ForegroundColor Red
    $failList | ForEach-Object { Write-Host "  [失败] $_" -ForegroundColor Red }
    Write-Host "`n说明：失败分支可能因合并冲突被中止；若提示推送失败，请在本分支上手动 git push 或处理冲突后重试。" -ForegroundColor Yellow
} else {
    Write-Host "全部子分支均已成功合并 f1 并推送。" -ForegroundColor Green
}
