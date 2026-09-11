Add-Type -AssemblyName System.Drawing

$iconDir = "F:\ws\Sui\fui\SpriteFrames\icons"
$size = 18
$white = [System.Drawing.Color]::FromArgb(255, 255, 255, 255)
$pen = New-Object System.Drawing.Pen($white, 1.4)
$pen.StartCap = [System.Drawing.Drawing2D.LineCap]::Round
$pen.EndCap = [System.Drawing.Drawing2D.LineCap]::Round
$pen.LineJoin = [System.Drawing.Drawing2D.LineJoin]::Round

function New-Icon {
    param([string]$Name, [scriptblock]$Draw)

    $bmp = New-Object System.Drawing.Bitmap($size, $size, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
    $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
    $g.Clear([System.Drawing.Color]::Transparent)

    & $Draw $g $pen

    $g.Dispose()
    $path = Join-Path $iconDir "$Name.png"
    $bmp.Save($path, [System.Drawing.Imaging.ImageFormat]::Png)
    $bmp.Dispose()
    $f = Get-Item $path
    Write-Host "OK: $($f.Name) ($($f.Length) bytes)"
}

# 打开图片 - image/picture icon
New-Icon "open_image" {
    param($g, $p)
    $g.DrawRectangle($p, 2.0, 2.0, 14.0, 14.0)
    $g.DrawEllipse($p, 7.4, 5.4, 2.2, 2.2)
    $pts = @(
        (New-Object System.Drawing.PointF(2, 14)),
        (New-Object System.Drawing.PointF(7, 8)),
        (New-Object System.Drawing.PointF(10, 11)),
        (New-Object System.Drawing.PointF(12, 7)),
        (New-Object System.Drawing.PointF(16, 14))
    )
    $g.DrawLines($p, $pts)
}

# 保存 - floppy disk icon
New-Icon "save" {
    param($g, $p)
    $g.DrawRectangle($p, 3.0, 2.0, 12.0, 14.0)
    $g.DrawLine($p, 6.0, 2.0, 6.0, 6.0)
    $g.DrawLine($p, 12.0, 2.0, 12.0, 6.0)
    $g.DrawLine($p, 6.0, 6.0, 12.0, 6.0)
    $g.DrawRectangle($p, 6.5, 9.0, 5.0, 7.0)
}

# 添加动画 - plus in rounded frame icon
New-Icon "add_anim" {
    param($g, $p)
    $g.DrawRectangle($p, 3.0, 3.0, 12.0, 12.0)
    $g.DrawLine($p, 9.0, 5.5, 9.0, 12.5)
    $g.DrawLine($p, 5.5, 9.0, 12.5, 9.0)
}

# 删除动画 - trash can icon
New-Icon "delete_anim" {
    param($g, $p)
    $g.DrawLine($p, 4.0, 5.0, 14.0, 5.0)
    $g.DrawLine($p, 7.0, 5.0, 7.0, 2.5)
    $g.DrawLine($p, 11.0, 5.0, 11.0, 2.5)
    $g.DrawLine($p, 7.0, 2.5, 11.0, 2.5)
    $pts = @(
        (New-Object System.Drawing.PointF(5.0, 7.0)),
        (New-Object System.Drawing.PointF(13.0, 7.0)),
        (New-Object System.Drawing.PointF(12.2, 15.5)),
        (New-Object System.Drawing.PointF(5.8, 15.5))
    )
    $g.DrawLines($p, $pts)
    $g.DrawLine($p, $pts[0], $pts[3])
    $g.DrawLine($p, 7.5, 9.0, 7.5, 13.5)
    $g.DrawLine($p, 10.5, 9.0, 10.5, 13.5)
}