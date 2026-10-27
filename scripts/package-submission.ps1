param(
    [Parameter(Mandatory = $true)]
    [ValidatePattern('^[a-zA-Z0-9][a-zA-Z0-9._-]*$')]
    [string]$Username
)

$ErrorActionPreference = 'Stop'
$repoPath = Split-Path -Parent $PSScriptRoot
$outputPath = Join-Path $repoPath 'submission'
New-Item -ItemType Directory -Force -Path $outputPath | Out-Null
$archivePath = Join-Path $outputPath ('cs225fa26_' + $Username + '_2-2.zip')
$items = @(
    'src',
    'AECore',
    'tests',
    'scripts',
    'README.md',
    'EventHandling-PongGame.sln',
    'EventHandling-PongGame.vcxproj',
    'EventHandling-PongGame.vcxproj.filters'
)
$sourcePaths = $items | ForEach-Object { Join-Path $repoPath $_ }
Compress-Archive -LiteralPath $sourcePaths -DestinationPath $archivePath -Force
Write-Output $archivePath
