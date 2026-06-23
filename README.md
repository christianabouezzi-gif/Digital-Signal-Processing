# Digital Signal Processing Portfolio

### Christian Abou-Ezzi
Biomedical Engineer | Signal Processing | MATLAB

---

## Overview

This repository contains a collection of Digital Signal Processing (DSP) projects completed using MATLAB. The projects focus on filter design, spectral analysis, audio processing, and image filtering techniques commonly used in biomedical engineering and signal processing applications.

The portfolio includes:

1. Savitzky-Golay Signal Smoothing Filter
2. Notch Filter Design
3. Comb + Resonator Bandpass Filter
4. Comb + Resonator Audio Recovery
5. Butterworth Filter Design
6. Chebyshev Filter Design
7. Audio Treasure Hunt
8. cheby + Butterworth 2D Image Filter

---

# Project 1 — Savitzky-Golay Signal Smoothing Filter

## Objective

Design and analyze a Savitzky-Golay filter for denoising physiological breathing data while preserving the underlying signal shape.

## Methods

- Third-order polynomial fitting
- Sliding window least-squares approximation
- FIR filter coefficient derivation
- DTFT analysis

Window sizes analyzed:

- m = 5
- m = 41
- m = 101

## Results

- Small windows preserved detail but retained noise.
- Larger windows increased smoothing.
- m = 101 produced the smoothest breathing signal.

## Figures

### Raw Breathing Data

![Raw Signal](images/sg/raw_signal.png)

### Smoothed Signal Comparison

![Smoothed Signals](images/sg/smoothing_comparison.png)

### Impulse Response

![Impulse Response](images/sg/impulse_response.png)

### DTFT Magnitude and Phase

![DTFT Response](images/sg/dtft_response.png)

---

# Project 2 — Notch Filter Design

## Objective

Remove a narrowband interference component using a pole-zero notch filter.

## Methods

- Pole-zero placement
- Unit circle analysis
- Frequency-selective attenuation

Transfer Function:

\[
H(z)=
\frac{(1-e^{j\omega_0}z^{-1})(1-e^{-j\omega_0}z^{-1})}
{(1-re^{j\omega_0}z^{-1})(1-re^{-j\omega_0}z^{-1})}
\]

## Results

- Interference frequency removed.
- Desired signal preserved.
- Stable filter implementation.

## Figures

### Pole-Zero Plot

![Pole Zero Plot](images/notch/pole_zero.png)

### Magnitude Response

![Magnitude Response](images/notch/magnitude.png)

### Phase Response

![Phase Response](images/notch/phase.png)

### Filtered Signal

![Filtered Signal](images/notch/output.png)

---

# Project 3 — Comb + Resonator Bandpass Filter

## Objective

Construct a narrowband bandpass filter using a comb filter and a resonator.

## Design Equations

Comb Filter:

\[
H_1(z)=1-z^{-24}
\]

Resonator:

\[
H_2(z)=
\frac{1}
{1-2\cos(\omega_p)z^{-1}+z^{-2}}
\]

Combined Filter:

\[
H(z)=H_1(z)H_2(z)
\]

where

\[
\omega_p=\frac{\pi}{3}
\]

## Results

- Harmonic frequencies rejected.
- Desired passband amplified.
- High selectivity achieved.

## Figures

### Pole-Zero Plot

![Pole Zero Plot](images/bandpass/pole_zero.png)

### Comb Filter Response

![Comb Response](images/bandpass/comb_response.png)

### Resonator Response

![Resonator Response](images/bandpass/resonator_response.png)

### Combined Response

![Combined Response](images/bandpass/combined_response.png)

---

# Project 4 — Comb + Resonator Audio Recovery

## Objective

Recover a desired audio signal embedded within multiple frequency components.

## Methods

- FFT analysis
- Bandpass filtering
- Audio reconstruction

## Results

- Desired tone isolated.
- Background frequencies attenuated.
- Improved audio clarity.

## Figures

### Original Spectrum

![Original Spectrum](images/audio_recovery/original_fft.png)

### Filter Response

![Filter Response](images/audio_recovery/filter_response.png)

### Filtered Spectrum

![Filtered Spectrum](images/audio_recovery/filtered_fft.png)

### Recovered Audio

![Recovered Audio](images/audio_recovery/recovered_waveform.png)

---

# Project 5 — Butterworth Filter Design

## Objective

Design a digital Butterworth low-pass filter from passband and stopband specifications.

## Specifications

Passband Edge:

\[
f_p=5000\ Hz
\]

Stopband Edge:

\[
f_s=8000\ Hz
\]

Passband Gain:

\[
G_p=0.9
\]

Stopband Gain:

\[
G_s=0.01
\]

## Design Procedure

1. Frequency prewarping
2. Analog prototype design
3. Filter order calculation
4. Pole computation
5. Bilinear transform

## Results

- Flat passband
- Stable implementation
- Strong stopband attenuation

## Figures

### Pole Locations

![Poles](images/butterworth/poles.png)

### Magnitude Response

![Magnitude](images/butterworth/magnitude.png)

### Phase Response

![Phase](images/butterworth/phase.png)

### Audio Comparison

![Audio Comparison](images/butterworth/audio_comparison.png)

---

# Project 6 — Chebyshev Filter Design

## Objective

Design a Chebyshev low-pass filter with a sharper transition region than the Butterworth design.

## Methods

- Passband ripple specification
- Pole calculation
- Bilinear transform implementation

## Results

- Faster rolloff
- Increased selectivity
- Controlled passband ripple

## Figures

### Pole-Zero Plot

![Pole Zero Plot](images/chebyshev/pole_zero.png)

### Magnitude Response

![Magnitude Response](images/chebyshev/magnitude.png)

### Ripple Analysis

![Ripple Analysis](images/chebyshev/ripple.png)

### Butterworth Comparison

![Comparison](images/chebyshev/comparison.png)

---

# Project 7 — Audio Treasure Hunt

## Objective

Recover hidden information embedded within an audio recording using frequency-domain analysis.

## Methods

- FFT analysis
- Frequency identification
- Successive filtering stages
- Signal reconstruction

## Results

- Hidden frequencies identified.
- Embedded audio recovered.
- Successful spectral extraction.

## Figures

### Original Audio

![Original Audio](images/treasure_hunt/original_audio.png)

### FFT Spectrum

![FFT Spectrum](images/treasure_hunt/fft.png)

### Filtered Spectrum

![Filtered Spectrum](images/treasure_hunt/filtered_fft.png)

### Recovered Signal

![Recovered Signal](images/treasure_hunt/recovered_signal.png)

---

# Project 8 — Chubby Butterworth 2D Image Filter

## Objective

Design a two-dimensional Butterworth filter for image denoising and frequency-domain image enhancement.

## Transfer Function

\[
H(\omega_m,\omega_n)=
\frac{1}
{1+\left(
\frac{\sqrt{\omega_m^2+\omega_n^2}}
{\omega_c}
\right)^{2N}}
\]

where:

- \(N\) = Filter Order
- \(\omega_c\) = Cutoff Frequency

## Methods

1. Compute 2D FFT
2. Shift spectrum to center
3. Apply Butterworth filter
4. Perform inverse FFT
5. Reconstruct image

## Results

- High-frequency noise reduced.
- Image details preserved.
- Smooth reconstruction obtained.

## Figures

### Original Image

![Original Image](images/butterworth2d/original.png)

### FFT Spectrum

![FFT Spectrum](images/butterworth2d/spectrum.png)

### Butterworth Surface

![Butterworth Surface](images/butterworth2d/filter_surface.png)

### Filtered Image

![Filtered Image](images/butterworth2d/filtered.png)

---

# MATLAB Skills Demonstrated

## Signal Processing

- FIR Filter Design
- IIR Filter Design
- DTFT Analysis
- FFT Analysis
- Spectrogram Analysis
- Pole-Zero Analysis

## Audio Processing

- Noise Removal
- Frequency Isolation
- Audio Reconstruction
- Hidden Signal Recovery

## Image Processing

- 2D FFT
- Frequency-Domain Filtering
- Image Enhancement
- Butterworth Surface Design

## Mathematical Techniques

- Least Squares Optimization
- Bilinear Transform
- Analog-to-Digital Filter Conversion
- Z-Transform Analysis
- Frequency Response Modeling

---

# Repository Structure

```text
DSP-Portfolio/
│
├── Savitzky_Golay_Filter/
├── Notch_Filter/
├── Comb_Resonator_Bandpass/
├── Audio_Recovery/
├── Butterworth_Filter/
├── Chebyshev_Filter/
├── Audio_Treasure_Hunt/
├── Butterworth_2D_Filter/
│
├── README.md
│
└── images/
```

---

## Software

- MATLAB
- Signal Processing Toolbox
- Audio Processing Toolbox
- FFT Functions
- Image Processing Toolbox

---

## Author

**Christian Abou-Ezzi**

Biomedical Engineering Portfolio

Signal Processing • Audio Analysis • Digital Filter Design • MATLAB Development
