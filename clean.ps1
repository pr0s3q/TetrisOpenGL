$param = $args[0]

$path = ".\x64\$param"
if (Test-Path $path)
{
    Remove-Item -Path $path -Force -Recurse
}