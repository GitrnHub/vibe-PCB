# EPD_S3_Universal v0.15

Current prototype-candidate electronics used by the vibe-EPD product reference.

## Released deliverables in this repository

- Gerber manufacturing ZIP with drill data
- JLC-style BOM and CPL
- full BOM
- GPIO map
- 24-pin FPC pinout
- complete reference netlist
- generation-workflow validation report
- editable/canonical design preservation under [`source/`](./source)
  - KiCad legacy schematic + cache library directly in Git
  - original `EPD_S3_Universal.kicad_pcb` preserved losslessly in a checksum-verified packed archive
  - canonical `design.json` preserved losslessly in a checksum-verified packed archive
- PlatformIO product bring-up/service-console firmware under `/firmware`
- technical PCB/schematic previews under `/docs/assets`

## Important status

This is a prototype candidate, not a physically validated production release. Review the Gerbers in a CAM/DFM viewer, check CPL rotation in the assembly preview, verify the exact panel pinout and perform a first-article build before volume manufacturing.

The packed-source arrangement exists only because the connected repository write route is text-oriented. On Linux/macOS/Git Bash run `sh source/rebuild_packed_sources.sh`; on Windows run the PowerShell script. Both reconstruct the exact source archives and verify fixed SHA-256 hashes.
