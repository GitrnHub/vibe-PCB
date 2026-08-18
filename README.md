# vibe-PCB

**AI-assisted open hardware, from PCB to complete product.**

**Live engineering site:** https://gitrnhub.github.io/vibe-PCB/

`vibe-PCB` is a reproducible hardware-product repository. The first reference product, **vibe-EPD**, combines an ESP32-S3 E-Ink controller board with firmware, manufacturing data, a parametric enclosure, product documentation and a technical GitHub Pages site.

> Status: **prototype / first-article stage**. The repository separates released v0.15 hardware facts from roadmap features so that visual polish does not become a false manufacturing claim.

## What is actually in the repo

| Layer | Deliverables |
|---|---|
| Electronics | editable/canonical source preservation, schematic, netlist, pin maps and manufacturing package |
| Manufacturing | Gerber ZIP, drill data inside the package, BOM, CPL |
| Firmware | PlatformIO board support plus SoftAP local web console, status/reset/deep-sleep APIs |
| Mechanical | Parametric OpenSCAD enclosure source |
| Product | specification, architecture, assembly guide, test plan |
| Visualization | product render, exploded view, PCB/schematic/Gerber previews, searchable BOM |
| Traceability | AI-assisted engineering decision log |

## vibe-EPD current reference

- **MCU:** ESP32-S3-WROOM-1-N8R2
- **PCB:** 60 × 45 mm, 2-layer prototype
- **Display interface:** 24-pin, 0.5 mm E-Paper FPC
- **Connectivity:** Wi-Fi / BLE; native USB signals exposed on J1
- **Local device UI:** SoftAP `vibe-EPD-setup` + browser status/control page
- **Reference mechanical target:** 4.2-inch, 91 × 77 mm panel class
- **Enclosure:** 104 × 90 × ~16.8 mm target envelope, parametric OpenSCAD

## Start here

- Live site: <https://gitrnhub.github.io/vibe-PCB/>
- Website source: [`docs/`](./docs)
- Hardware: [`hardware/epd-s3-v0.15/`](./hardware/epd-s3-v0.15)
- Editable/canonical source: [`hardware/epd-s3-v0.15/source/`](./hardware/epd-s3-v0.15/source)
- Firmware: [`firmware/`](./firmware)
- Enclosure: [`mechanical/enclosure-v0.1/`](./mechanical/enclosure-v0.1)
- Product docs: [`product/`](./product)
- Engineering decisions: [`ai-design/DECISIONS.md`](./ai-design/DECISIONS.md)

### Manufacturing

For PCB fabrication, upload **only**:

`hardware/epd-s3-v0.15/manufacturing/EPD_S3_Universal_Gerber.zip`

For SMT assembly, also use the matching BOM/CPL in `hardware/epd-s3-v0.15/assembly/` and verify placement/rotation in the assembler preview.

## GitHub Pages

Pages is configured to deploy the static `docs/` site using `.github/workflows/pages.yml`. The site intentionally has no build dependency: HTML, CSS, JavaScript, SVG and local assets only. Pushes to `main` that touch `docs/**` trigger a fresh deployment.

## Engineering boundary

The current v0.15 board **does not silently claim integrated USB-C charging, battery fuel gauge or RTC**. Those are product-revision targets. The existing board provides the electronics core, 5 V input/native USB signals and E-Paper interface; exact panel initialization and LUT/waveform remain panel-specific.

## License

No license has been selected yet. Add an explicit hardware/software/documentation license before encouraging third-party commercial reuse.
