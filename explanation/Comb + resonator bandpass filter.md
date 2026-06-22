# Comb Filter and Resonator Bandpass Filter Design Using MATLAB

## Overview

This project demonstrates the design and analysis of a digital bandpass filter created by cascading a comb filter with a resonator filter. The filter was implemented and analyzed in MATLAB using pole-zero techniques, impulse response analysis, DTFT evaluation, and DFT verification.

The objective was to create a bandpass response centered at:

[
\omega_{pass} = \frac{\pi}{3}
]

with a half-bandwidth spacing of:

[
\phi = 15^\circ
]

The design follows the classical comb-filter plus resonator architecture commonly used in digital signal processing for selective frequency enhancement.

---

## Theory

### Comb Filter

The comb filter creates equally spaced zeros around the unit circle:

[
H_1(z)=1-z^{-m}
]

where

[
m=\frac{360^\circ}{\phi}
]

Using a half-bandwidth spacing of 15°:

[
m=24
]

This produces 24 equally spaced zeros around the unit circle.

---

### Resonator Filter

A resonator was designed to place poles at the desired passband frequency:

[
\omega_{pass}=\frac{\pi}{3}
]

The poles are:

[
p_1=e^{j\omega_{pass}}
]

[
p_2=e^{-j\omega_{pass}}
]

which create resonance at the desired center frequency.

The resonator transfer function is:

[
H_2(z)=
\frac{1}
{1-(p_1+p_2)z^{-1}+(p_1p_2)z^{-2}}
]

---

### Overall Filter

The complete bandpass filter is formed by cascading the comb and resonator sections:

[
H(z)=H_1(z)H_2(z)
]

The resulting pole-zero structure creates a strong passband around:

[
\omega=\frac{\pi}{3}
]

while attenuating other frequencies.

---

## MATLAB Implementation

The project performs the following steps:

### 1. Design the Comb Filter

* Calculate the number of comb zeros
* Generate numerator coefficients
* Construct the comb transfer function

### 2. Design the Resonator

* Calculate pole locations
* Create resonator coefficient vectors
* Build the resonator transfer function

### 3. Construct the Overall Filter

* Combine numerator and denominator polynomials
* Determine all poles and zeros

### 4. Pole-Zero Analysis

The roots of the transfer function are computed and plotted on the complex plane.

The pole-zero plot verifies:

* 24 equally spaced zeros from the comb filter
* Two resonator poles at ±60°
* Pole-zero cancellation near the desired passband

---

### 5. Impulse Response Analysis

Using MATLAB's `impz()` command:

```matlab
[h,n] = impz(Hz_numerator,Hz_denominator,N0);
```

the filter impulse response is generated and plotted.

This provides a time-domain representation of the filter.

---

### 6. Frequency Response Analysis

The DTFT:

[
H(e^{j\omega})
]

is computed directly from the filter equation and compared with the DFT coefficients obtained using:

```matlab
H_k = fft(h);
```

The comparison verifies agreement between:

* Continuous frequency response (DTFT)
* Sampled frequency response (DFT)

---

### 7. Gain Normalization

The filter exhibits a large peak gain due to the resonant poles.

A gain correction factor is calculated:

[
G=\frac{1}{H_{peak}}
]

and applied to both:

* DTFT response
* DFT coefficients

to normalize the maximum gain to unity.

---

## Results

### Figure 0 – Pole-Zero Plot

Shows:

* Comb-filter zeros equally spaced around the unit circle
* Resonator poles at ±60°
* Pole-zero cancellation responsible for the passband

### Figure 1 – Impulse Response

Displays the filter impulse response:

[
h[n]
]

for a 72-sample analysis window.

### Figure 2 – Unnormalized Frequency Response

Shows:

* DTFT magnitude response
* DFT coefficient magnitudes

before gain correction.

### Figure 3 – Gain-Normalized Frequency Response

Shows the final bandpass response after applying the gain adjustment factor.

The maximum gain is reduced to:

[
|H(e^{j\omega})|_{max}=1
]

while preserving the desired passband characteristics.

---

## Key DSP Concepts Demonstrated

* Comb filter design
* Resonator filter design
* Pole-zero analysis
* Bandpass filter synthesis
* Impulse response computation
* Discrete-Time Fourier Transform (DTFT)
* Fast Fourier Transform (FFT)
* Gain normalization
* Frequency-domain filter verification

---

## Software Used

* MATLAB
* Signal Processing Toolbox

---

## Author

Christian Abou-Ezzi

Biomedical Engineering | Digital Signal Processing | MATLAB Development
