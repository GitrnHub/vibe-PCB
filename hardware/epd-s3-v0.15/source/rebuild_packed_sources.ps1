$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $here

function Join-Base64Parts($pattern, $output) {
  $text = (Get-ChildItem $pattern | Sort-Object Name | ForEach-Object { Get-Content $_.FullName -Raw }) -join ''
  [IO.File]::WriteAllBytes($output, [Convert]::FromBase64String($text))
}

Join-Base64Parts 'packed/pcb-source.zip.b64.*' 'pcb-source.zip'
Join-Base64Parts 'packed/design-json.zip.b64.*' 'design-json.zip'

$pcb = (Get-FileHash 'pcb-source.zip' -Algorithm SHA256).Hash.ToLower()
$design = (Get-FileHash 'design-json.zip' -Algorithm SHA256).Hash.ToLower()
if ($pcb -ne '581265c82e6335641952f2bdd6ffe43f39041710f5eac0ceb59c8f53225aa943') { throw 'PCB source checksum mismatch' }
if ($design -ne 'f144cc8364d630087dcd9a41cf17133e34385bd748825fdf4eb3a6eb68f82b86') { throw 'design.json checksum mismatch' }

Write-Host 'Source archives rebuilt and SHA-256 verified.'
Write-Host '  pcb-source.zip -> EPD_S3_Universal.kicad_pcb'
Write-Host '  design-json.zip -> design.json'
