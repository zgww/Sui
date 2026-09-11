Add-Type -AssemblyName System.Drawing

$iconDir = "E:\ws\Sui\fui\ImageViewer\icons"
$size = 24
$white = [System.Drawing.Color]::FromArgb(255, 255, 255, 255)
$pen = New-Object System.Drawing.Pen($white, 2.0)
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

# 1. Open - folder icon
New-Icon "open" {
    param($g, $p)
    $pts = @(
        (New-Object System.Drawing.PointF(3, 6)),
        (New-Object System.Drawing.PointF(10, 6)),
        (New-Object System.Drawing.PointF(12, 8.5)),
        (New-Object System.Drawing.PointF(21, 8.5)),
        (New-Object System.Drawing.PointF(21, 19)),
        (New-Object System.Drawing.PointF(3, 19))
    )
    $g.DrawLines($p, $pts)
    $g.DrawLine($p, $pts[0], $pts[5])
}

# 2. Zoom In - magnifier with plus
New-Icon "zoom-in" {
    param($g, $p)
    $g.DrawEllipse($p, 3.0, 3.0, 13.0, 13.0)
    $g.DrawLine($p, 14.5, 14.5, 20.5, 20.5)
    $g.DrawLine($p, 9.5, 6.5, 9.5, 12.5)
    $g.DrawLine($p, 6.5, 9.5, 12.5, 9.5)
}

# 3. Zoom Out - magnifier with minus
New-Icon "zoom-out" {
    param($g, $p)
    $g.DrawEllipse($p, 3.0, 3.0, 13.0, 13.0)
    $g.DrawLine($p, 14.5, 14.5, 20.5, 20.5)
    $g.DrawLine($p, 6.5, 9.5, 12.5, 9.5)
}

# 4. Fit - corner brackets
New-Icon "fit" {
    param($g, $p)
    # top-left
    $g.DrawLine($p, 5, 4, 4, 4)
    $g.DrawLine($p, 4, 4, 4, 9)
    # top-right
    $g.DrawLine($p, 15, 4, 20, 4)
    $g.DrawLine($p, 20, 4, 20, 9)
    # bottom-left
    $g.DrawLine($p, 4, 15, 4, 20)
    $g.DrawLine($p, 4, 20, 9, 20)
    # bottom-right
    $g.DrawLine($p, 15, 20, 20, 20)
    $g.DrawLine($p, 20, 15, 20, 20)
}

# 5. Rotate - circular arrow
New-Icon "rotate" {
    param($g, $p)
    $rect = New-Object System.Drawing.RectangleF(4, 4, 16, 16)
    $g.DrawArc($p, $rect, -55, 300)
    # arrow head
    $g.DrawLine($p, 19, 4, 19, 9)
    $g.DrawLine($p, 19, 4, 14, 4)
}

# 6. Register - link icon
New-Icon "register" {
    param($g, $p)
    # top curve
    $g.DrawArc($p, 4, 6, 16, 12, 200, 140)
    # bottom curve
    $g.DrawArc($p, 4, 6, 16, 12, 20, 140)
    # left ends
    $g.DrawLine($p, 6, 8, 9, 8)
    $g.DrawLine($p, 6, 16, 9, 16)
}
