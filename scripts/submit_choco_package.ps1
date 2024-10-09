$apiKey = $env:CHOCO_API_KEY
$package = "uuid.$version.nupkg"

# Submeter o pacote para Chocolatey
choco push $package --api-key=$apiKey --source="https://push.chocolatey.org/"
