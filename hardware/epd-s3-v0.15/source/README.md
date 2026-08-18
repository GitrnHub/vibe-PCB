# Editable / canonical source files

This directory preserves the design sources behind the v0.15 manufacturing package.

## Directly editable schematic

- `EPD_S3_Universal.sch`
- `EPD_S3_Universal-cache.lib`

These are KiCad legacy schematic-format reference files generated from the canonical design data. Treat net labels and `../reference/netlist.csv` as the connectivity reference and run KiCad ERC/DRC before modifying a production design.

## PCB source

The original `EPD_S3_Universal.kicad_pcb` is preserved losslessly inside a packed ZIP. Because the connected repository write route is text-only, the ZIP is stored as ordered Base64 chunks in `packed/` instead of pretending the binary file was directly uploaded.

Rebuild on Linux/macOS/Git Bash:

```sh
./rebuild_packed_sources.sh
```

Rebuild on Windows PowerShell:

```powershell
./rebuild_packed_sources.ps1
```

Expected archive:

- `pcb-source.zip`
- SHA-256: `581265c82e6335641952f2bdd6ffe43f39041710f5eac0ceb59c8f53225aa943`
- contains: `EPD_S3_Universal.kicad_pcb`

## Canonical machine-readable design

The generation workflow's `design.json` is preserved the same way.

- reconstructed archive: `design-json.zip`
- SHA-256: `f144cc8364d630087dcd9a41cf17133e34385bd748825fdf4eb3a6eb68f82b86`
- contains: `design.json`

The reconstruction scripts verify SHA-256 before reporting success.

## Validation boundary

Preserving editable source is not the same as claiming KiCad official DRC was run. See `../reference/VALIDATION_REPORT.txt`: the original generation runtime passed its custom geometry/connectivity checks, but did not have `kicad-cli`/`pcbnew`/an independent CAM renderer. Always rerun ERC/DRC/DFM and inspect the first article before volume manufacturing.
