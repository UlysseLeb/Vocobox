# Vocobox

An Audio Unit (v2) LPC vocoder for modern macOS with full Apple Silicon support.

## What it does

Vocobox is a high-resolution vocoder based on Linear Predictive Coding (LPC). It takes two audio inputs:
- **Modulator** — typically a voice signal that drives the filter
- **Carrier** — a synthesizer or other pitched source that gets shaped

The LPC algorithm extracts the spectral envelope of the modulator, then applies it to the carrier to produce the characteristic "talking synth" effect.

## Features

- Universal Binary: runs natively on Apple Silicon (arm64) and Intel (x86_64)
- Audio Unit v2 compatible with Logic Pro, GarageBand, and other AU hosts
- Two-input effect with configurable wet/dry mix, quality, and input swap
- Fixed several memory safety issues present in older LPC vocoder implementations

## Apple Silicon compatibility fixes

Older LPC vocoder codebases were written for PowerPC and later compiled for Intel, where the call stack tends to be pre-zeroed by the allocator. On Apple Silicon (ARM64), the stack contains arbitrary data, which exposed several latent bugs:

**Uninitialized LPC arrays** — the `lpc()` function declared stack arrays `z[]`, `r[]`, `k[]` of size `ORD_MAX` (50) but only initialized indices `0..o`. On Intel this was benign; on ARM64 the garbage values corrupted the lattice filter, causing the output gain to collapse and producing a muffled, attenuated sound. Fixed by zeroing all elements before use.

**LPC order bounds** — the order `O` computed from the Quality parameter was never clamped, allowing values above `ORD_MAX` and causing out-of-bounds writes into the fixed-size arrays. Added explicit clamping to `[4, ORD_MAX]`.

**Decimation counter desync** — when `O` changed mid-stream, the decimation counter `K` was not reset, leading to phase misalignment. Fixed by resetting `K` whenever `O` changes.

**Window initialization** — `N` was initialized to `1` instead of `0`, causing the Hanning window to be computed with a wrong size on the first `Process()` call.

## Requirements

- macOS 11.0 or later
- Xcode Command Line Tools
- CMake 3.19+

## Build

```bash
git clone https://github.com/UlysseLeb/Vocobox.git
cd Vocobox
./build.sh
```

This compiles a Universal Binary and installs `Vocobox.component` to `~/Library/Audio/Plug-Ins/Components/`. Restart your DAW after installation.

## Manual build

```bash
cmake .
make
cp -R Vocobox.component ~/Library/Audio/Plug-Ins/Components/
```

## Parameters

| Parameter | Range | Description |
|-----------|-------|-------------|
| Wet | 0–100% | Level of the vocoded signal |
| Dry | 0–100% | Level of the unprocessed modulator |
| Quality | 10–100% | LPC order — higher = more frequency detail, more CPU |
| Input Swap | on/off | Swap modulator and carrier inputs |

## Usage in Logic Pro

1. Insert Vocobox on a stereo track
2. Route your carrier (synth) to the plugin's first input bus
3. Route your modulator (voice) to the second input bus
4. Adjust Quality and Wet to taste

## License

GPL-2.0 — see [gpl-2.0.txt](gpl-2.0.txt)
