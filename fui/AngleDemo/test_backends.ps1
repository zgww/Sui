param()
$exe = "F:\ws\Sui\fui\AngleDemo\x64\Release\AngleDemo.exe"
$combos = @(
    @{backend="default"; es="3"},
    @{backend="d3d11"; es="3"},
    @{backend="d3d11"; es="2"},
    @{backend="gl"; es="3"},
    @{backend="gl"; es="2"},
    @{backend="null"; es="3"},
    @{backend="vulkan"; es="3"},
    @{backend="d3d11on12"; es="3"},
    @{backend="gles"; es="3"}
)
foreach ($c in $combos) {
    $env:ANGLE_DEMO_BACKEND = $c.backend
    $env:ANGLE_DEMO_ES = $c.es
    $p = Start-Process -FilePath $exe -WorkingDirectory "F:\ws\Sui\fui\AngleDemo" -RedirectStandardOutput "$env:TEMP\angle_out.txt" -PassThru -WindowStyle Minimized
    Start-Sleep -Seconds 4
    if (!$p.HasExited) { Stop-Process -Id $p.Id -Force }
    Start-Sleep -Milliseconds 500
    $out = Get-Content "$env:TEMP\angle_out.txt" -ErrorAction SilentlyContinue
    Write-Output "==================== backend=$($c.backend) es=$($c.es) ===================="
    if ($out) { $out | Select-String -Pattern "Requested|EGL |GL_|backend|D3D11On12" | ForEach-Object { $_.Line } }
    else { Write-Output "(no output)" }
}
Remove-Item Env:ANGLE_DEMO_BACKEND -ErrorAction SilentlyContinue
Remove-Item Env:ANGLE_DEMO_ES -ErrorAction SilentlyContinue
