$packageName = "uuid"
$version = "1.0.0"
$toolsDir = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"

# Cria o arquivo Nuspec
@"
<package>
  <metadata>
    <id>$packageName</id>
    <version>$version</version>
    <title>uuid for c</title>
    <authors>Danilo Silva</authors>
    <owners>Danilo Silva</owners>
    <summary>Biblioteca de uuid para C</summary>
    <description>Biblioteca de uuid para C.</description>
    <tags>uuid C</tags>
    <projectUrl>https://github.com/kovarike/uuid-for-c</projectUrl>
    <licenseUrl>https://github.com/kovarike/uuid-for-c/blob/main/LICENSE</licenseUrl>
  </metadata>
</package>
"@ | Set-Content "$toolsDir\$packageName.nuspec"

# Cria o script de instalação
$url = "https://github.com/kovarike/uuid-for-c/releases/download/v$version/uuid.zip"
$zipPath = Join-Path $toolsDir "uuid.zip"

Invoke-WebRequest $url -OutFile $zipPath
Expand-Archive -Path $zipPath -DestinationPath $toolsDir

# Empacota para o Chocolatey
choco pack $toolsDir\$packageName.nuspec
