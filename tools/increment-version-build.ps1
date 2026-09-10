param(
	[Parameter(Mandatory = $true)]
	[string]$VersionFile
)

if (-not (Test-Path -LiteralPath $VersionFile)) {
	throw "Version file not found: $VersionFile"
}

$content = Get-Content -LiteralPath $VersionFile -Raw
$pattern = '(?m)^([ \t]*#define[ \t]+VERSION_BUILD[ \t]+)(\d+)([ \t]*)(?:\r?$)'
$match = [regex]::Match($content, $pattern)

if (-not $match.Success) {
	throw "VERSION_BUILD definition not found in $VersionFile"
}

$build = [int64]$match.Groups[2].Value + 1
$content = [regex]::Replace($content, $pattern, {
	param($m)
	$m.Groups[1].Value + $build + $m.Groups[3].Value
}, 1)

[System.IO.File]::WriteAllText($VersionFile, $content, [System.Text.UTF8Encoding]::new($false))
Write-Host "VERSION_BUILD incremented to $build"
