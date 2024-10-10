$packageName = "winid"
$version = "1.0.0"
$toolsDir = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"

# Cria o arquivo Nuspec
@"
<package>
  <metadata>
    <id>$packageName</id>
    <version>$version</version>
    <title>UUID for C</title>
    <authors>Danilo Silva</authors>
    <owners>Danilo Silva</owners>
    <summary>Windows uuid package for C</summary>
    <description>Windows uuid package for C.</description>
    <tags>uuid</tags>
    <projectUrl>https://github.com/kovarike/win-uuid-for-c</projectUrl>
    <licenseUrl>https://github.com/kovarike/win-uuid-for-c/blob/main/LICENSE</licenseUrl>
  </metadata>
</package>
"@ | Set-Content "$toolsDir\$packageName.nuspec"

# Cria o zip da biblioteca
$zipPath = Join-Path $toolsDir "$packageName.zip"
Compress-Archive -Path "$toolsDir\*" -DestinationPath $zipPath -Force

# Empacota para o Chocolatey
choco pack $toolsDir\$packageName.nuspec

$apiKey = $env:CHOCO_API_KEY
$package = "$toolsDir\$packageName.$version.nupkg"

# Submeter o pacote para Chocolatey
choco push $package --api-key=$apiKey --source="https://push.chocolatey.org/"
