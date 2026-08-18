# vibe-EPD enclosure v0.1

Parametric 3D-printable enclosure concept for the current EPD_S3_Universal v0.15 board and a 4.2-inch Good Display GDEY042T81-class panel.

## Reference geometry

- Enclosure: **104 × 90 × ~16.8 mm** assembled target envelope
- Display outline: **91 × 77 mm**
- Visible window: **86 × 65 mm**
- PCB: **60 × 45 mm**
- PCB mounting holes: M3 board holes at 3.5 mm from each PCB corner

## File

- `vibe_epd_enclosure.scad` — parametric OpenSCAD source; switch `part` between `front`, `back`, and `assembly`, then export STL from OpenSCAD.

## Status

This is a **fit-check prototype**. Confirm your exact display FPC exit, connector orientation, screw hardware, printer shrinkage, battery/accessory dimensions and USB/service opening before production.
