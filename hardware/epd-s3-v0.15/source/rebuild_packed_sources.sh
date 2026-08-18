#!/bin/sh
set -eu

HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
cd "$HERE"

cat packed/pcb-source.zip.b64.* | base64 -d > pcb-source.zip
cat packed/design-json.zip.b64.* | base64 -d > design-json.zip

printf '%s  %s\n' '581265c82e6335641952f2bdd6ffe43f39041710f5eac0ceb59c8f53225aa943' 'pcb-source.zip' | sha256sum -c -
printf '%s  %s\n' 'f144cc8364d630087dcd9a41cf17133e34385bd748825fdf4eb3a6eb68f82b86' 'design-json.zip' | sha256sum -c -

unzip -t pcb-source.zip
unzip -t design-json.zip

echo 'Source archives rebuilt and verified.'
echo '  pcb-source.zip -> EPD_S3_Universal.kicad_pcb'
echo '  design-json.zip -> design.json'
