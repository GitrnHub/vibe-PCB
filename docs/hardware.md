# Hardware Architecture

## Current v0.15 hardware

- ESP32-S3-WROOM-1-N8R2 controller module
- 60 × 45 mm, 2-layer prototype PCB
- 5 V input plus native USB D-/D+ exposed through J1
- 3.3 V buck-regulated logic rail
- 24-pin, 0.5 mm E-Paper FPC interface
- SPI/control signals plus panel auxiliary/high-voltage networks
- RESE selection provision for panel/driver families
- BOOT and RESET service controls

## System path

```text
5 V input / native USB signals
           |
      3.3 V power
           |
       ESP32-S3
           |
   SPI + control + I2C
           |
  E-Paper interface / HV
           |
     24-pin FPC panel
```

## Product boundary

The current board does **not** claim an integrated USB-C receptacle, Li-ion charger, battery fuel gauge or RTC. Those belong to the next product PCB revision. The website marks them as roadmap items instead of presenting them as finished hardware.

See `hardware/epd-s3-v0.15/reference/` for pin maps, netlist and validation notes, and `hardware/epd-s3-v0.15/manufacturing/` for the fabrication package.
