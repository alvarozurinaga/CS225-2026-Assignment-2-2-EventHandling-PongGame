$ErrorActionPreference = 'Stop'
$repoPath = Split-Path -Parent $PSScriptRoot
$outputPath = Join-Path $repoPath 'obj\tests'
New-Item -ItemType Directory -Force -Path $outputPath | Out-Null
$sources = @(
    (Join-Path $PSScriptRoot 'pong_tests.cc'),
    (Join-Path $PSScriptRoot 'stubs\engine_stub.cc'),
    (Join-Path $repoPath 'src\Framework\component.cc'),
    (Join-Path $repoPath 'src\Framework\entity.cc')
)
$sources += Get-ChildItem -LiteralPath (Join-Path $repoPath 'src\Components') -Filter '*.cc' | ForEach-Object FullName
$sources += Get-ChildItem -LiteralPath (Join-Path $repoPath 'src\Pong') -Filter '*.cc' | ForEach-Object FullName
$executablePath = Join-Path $outputPath 'pong_tests.exe'
& g++ -std=c++11 -Wall -Wextra -pedantic -Werror ('-I' + (Join-Path $PSScriptRoot 'stubs')) @sources -o $executablePath
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& $executablePath
exit $LASTEXITCODE
