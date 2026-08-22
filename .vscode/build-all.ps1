param(
    [Parameter(Mandatory = $true)]
    [string]$SourceFile
)

$ErrorActionPreference = "Stop"

$sourcePath = [System.IO.Path]::GetFullPath($SourceFile)
if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
    throw "Source file does not exist: $sourcePath"
}

if ([System.IO.Path]::GetExtension($sourcePath).ToLowerInvariant() -ne ".cpp") {
    throw "The selected file is not a .cpp file: $sourcePath"
}

$sourceDirectory = Split-Path -Parent $sourcePath
$outputPath = Join-Path $sourceDirectory "current.exe"
$statePath = Join-Path $PSScriptRoot "current.build.json"
$sourceHash = (Get-FileHash -LiteralPath $sourcePath -Algorithm SHA256).Hash
$sourceKey = [System.IO.Path]::GetFullPath($sourcePath)
$shouldBuild = $true

if (Test-Path -LiteralPath $statePath -PathType Leaf) {
    try {
        $state = Get-Content -LiteralPath $statePath -Raw | ConvertFrom-Json
        $shouldBuild = -not (
            $state.source -eq $sourceKey -and
            $state.hash -eq $sourceHash -and
            (Test-Path -LiteralPath $outputPath -PathType Leaf)
        )
    }
    catch {
        $shouldBuild = $true
    }
}

if (-not $shouldBuild) {
    Write-Host "Skipping build: source is unchanged and current.exe exists."
    exit 0
}

Write-Host "Building: $sourcePath"
& g++ -g -Wall -Wextra $sourcePath -o $outputPath
if ($LASTEXITCODE -ne 0) {
    throw "Build failed with exit code: $LASTEXITCODE"
}

@{
    source = $sourceKey
    hash = $sourceHash
} | ConvertTo-Json | Set-Content -LiteralPath $statePath -Encoding UTF8

Write-Host "Build complete: $outputPath"