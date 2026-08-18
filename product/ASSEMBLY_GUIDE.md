# Assembly Guide

1. Inspect the PCB and verify no visible solder bridges around the 0.5 mm FPC connector.
2. Fit the PCB to the four rear-shell bosses without the display connected.
3. Connect 5 V and GND only; verify the 3.3 V rail before continuing.
4. Confirm the exact E-Paper panel pinout matches `hardware/epd-s3-v0.15/reference/fpc24_pinout.csv`.
5. Set the RESE selection for the selected panel/controller before inserting the FPC.
6. Power down, insert the 24-pin FPC fully, close the latch, then power up.
7. Run panel-specific firmware and verify BUSY timing plus the first full refresh.
8. Place the panel in the front-frame locating lip, route the FPC without a sharp fold, then close the rear shell.

Do not assume that every 24-pin E-Paper panel has the same electrical pinout or waveform requirements.
