# Comb + Resonator Audio Bandpass Filter Design in MATLAB

## Overview

This project demonstrates the design and implementation of a **comb filter combined with a resonator filter** to create a narrow bandpass filter for audio processing. The filter is applied to the song **"Old MacDonald Had a Farm"** to selectively preserve frequencies near **400 Hz (G4)** while attenuating neighboring musical notes.

The project explores several fundamental Digital Signal Processing (DSP) concepts:

* Spectrogram generation using windowed FFT analysis
* Comb filter design using strategically placed zeros
* Resonator filter design using complex-conjugate poles
* DTFT and frequency response analysis
* Frequency-domain filtering using FFT multiplication
* Audio reconstruction using inverse FFT
* Evaluation of filter performance through spectrograms and listening tests

---

## Learning Objectives

The primary goals of this project were:

1. Analyze the spectral content of an audio signal using a spectrogram.
2. Design a comb-resonator bandpass filter centered at 400 Hz.
3. Determine filter parameters from frequency-domain specifications.
4. Apply filtering in the DFT domain.
5. Compare input and output spectra.
6. Evaluate how attenuation levels affect perceived audio quality.

---

## Input Audio Signal

The audio file:

```matlab
[x, f_sample] = audioread('mac_farm copy.wav');
```

contains a recording of **Old MacDonald Had a Farm** sampled at:

```matlab
f_sample = 44100 Hz
```

The audio metadata is retrieved using:

```matlab
audioinfo('mac_farm copy.wav')
```

---

## Part 1: Spectrogram Generation


A spectrogram is created by dividing the audio into short time slices and computing the FFT of each slice.

### Windowing Method

To reduce spectral leakage, a custom window is constructed using:

* Left Hamming taper
* Rectangular center section
* Right Hamming taper

```matlab
w_n = [left_h rec_center right_h];
```

Each time segment is multiplied by the window before computing its FFT.

### Spectrogram Calculation

For every time slice:

```matlab
Q_k = fft(q_n);
```

The resulting FFT coefficients are stored in a matrix and converted to dB:

```matlab
S_db = 20*log10(abs(spectrogram_matrix));
```

### Output Figure

**Engineer's DFT Spectrogram of Old MacDonald**

<img width="797" height="514" alt="Screenshot 2026-06-22 at 3 12 36 PM" src="https://github.com/user-attachments/assets/1843900f-b931-4cba-a07e-e088f7832c6a" />


Shows:

* Frequency content versus time
* Musical note transitions
* Spectral leakage effects
* Harmonic structure of the song

---

## Part 2: Bandpass Filter Design

### Filter Specifications

| Parameter       | Value     |
| --------------- | --------- |
| Passband Center | 400 Hz    |
| Sideband Width  | 50 Hz     |
| Sampling Rate   | 44,100 Hz |

The filter is designed to isolate frequencies near the G4 musical note.

---

## Comb Filter Design

The comb filter transfer function is:

```math
H_1(z)=1-z^{-m}
```

where:

```matlab
m = f_sample / 50;
```

The spacing of comb filter zeros determines the sidelobe width.

### Comb Filter Coefficients

```matlab
H1z_numerator = [1 zeros(1,m-1) -1];
```

The comb filter introduces regularly spaced zeros across the frequency spectrum.

---

## Resonator Design

To create a passband centered at 400 Hz, two complex-conjugate poles are placed at:

```matlab
p1 = exp(j*w_pass);
p2 = exp(-j*w_pass);
```

where:

```matlab
w_pass = 2*pi*(400/f_sample);
```

### Resonator Transfer Function

```math
H_2(z)=\frac{1}
{1-(p_1+p_2)z^{-1}+(p_1p_2)z^{-2}}
```

The resonator amplifies frequencies near the desired center frequency.

---

## Overall Filter

The complete filter is formed by cascading the comb and resonator sections:

```math
H(z)=H_1(z)H_2(z)
```

using:

```matlab
Hz_numerator = conv(H1z_numerator,H2z_numerator);
Hz_denominator = conv(H1z_denominator,H2z_denominator);
```

---

## Impulse Response and Frequency Response

The impulse response is obtained using:

```matlab
[h,n] = impz(Hz_numerator,Hz_denominator,N_0);
```

The frequency response is computed with:

```matlab
H_k = fft(h);
```

---

## Gain Adjustment

To prevent excessive amplification, the filter is normalized using:

```matlab
G = 1/(abs(max(H_k)));
```

The gain-adjusted response becomes:

```matlab
H_k_adjusted = H_k * G;
```

This ensures the peak magnitude equals approximately 1.

---

## Filter Response Visualization

### Linear Magnitude Plot

The gain-adjusted magnitude response:

```matlab
abs(H(e^jw))
```

is plotted across the full frequency range.

<img width="801" height="519" alt="Screenshot 2026-06-22 at 3 13 00 PM" src="https://github.com/user-attachments/assets/1c12aa9a-6e42-4e8c-9c61-e0edba65b271" />


This plot verifies:

* Passband location
* Comb structure
* Overall filter stability

### dB Magnitude Plot

The response is also displayed in decibel form:

```matlab
20*log10(abs(H(e^jw)))
```

<img width="838" height="520" alt="Screenshot 2026-06-22 at 3 13 11 PM" src="https://github.com/user-attachments/assets/70a635a2-301a-41a9-a7a9-3fe2306b5fed" />


This view reveals:

* Attenuation levels
* Sideband suppression
* Filter selectivity

---

## Part 3: Frequency-Domain Audio Filtering

### Input DFT

The audio signal is transformed into the frequency domain:

```matlab
X_k = fft(x);
```

### Filter DFT

The filter impulse response is transformed:

```matlab
H_k = fft(h);
```

### Frequency-Domain Multiplication

Filtering is performed using:

```matlab
Y_k = H_k .* X_k;
```

which implements:

```math
Y[k]=H[k]X[k]
```

---

## Output Signal Reconstruction

The filtered signal is returned to the time domain:

```matlab
Y_n = real(ifft(Y_k));
```

The output signal contains primarily frequency components near 400 Hz.

---

## Input vs Output Comparison

<img width="804" height="516" alt="Screenshot 2026-06-22 at 3 13 38 PM" src="https://github.com/user-attachments/assets/2db36c67-f33f-47eb-b642-61f5b8e11e21" />


A stem plot compares:

* Original audio signal
* Filtered audio signal

```matlab
stem(n2,x)
stem(n2,Y_n)
```

This visualization highlights the attenuation introduced by the filter.

---

## Output Spectrogram Analysis

The filtered signal is processed using the same spectrogram parameters as the original audio.


<img width="822" height="518" alt="Screenshot 2026-06-22 at 3 13 54 PM" src="https://github.com/user-attachments/assets/ef38b275-7c17-4e02-acd5-185a7d360450" />


The resulting dB-scale spectrogram reveals:

* Preservation of frequencies near 400 Hz
* Reduction of D4 and E4 note energy
* Lower sideband amplitudes
* Increased blue regions indicating attenuation

---

## Audio Export

The filtered output is written to a WAV file:

```matlab
audiowrite('Mac_comb_resonator_filtered.wav',Y_n,f_sample)
```

This allows subjective evaluation through listening.

---

## Results

### Observations

The filter successfully isolated the G4 note near 400 Hz.

Listening tests showed:

* G4 notes remained clearly audible.
* D4 and E4 notes were significantly reduced.
* Overall signal amplitude decreased after filtering.
* Some unwanted notes remained audible despite attenuation.

### Spectral Findings

The most common sidelobe attenuation levels were approximately:

```text
-20 dB to -40 dB
```

While this attenuation visibly reduces unwanted frequencies, it is insufficient for complete removal.

DSP literature commonly recommends:

```text
Attenuation < -60 dB
```

for effective suppression of unwanted audio components.

---

## Key DSP Concepts Demonstrated

* Spectrogram generation
* Windowing techniques
* Hamming windows
* FFT analysis
* Comb filter design
* Resonator filter design
* Pole-zero placement
* Gain normalization
* Frequency-domain filtering
* Audio reconstruction
* Spectral leakage analysis
* dB-scale frequency response interpretation

---

## Conclusion

This project demonstrates how a comb filter and resonator can be combined to create a narrow bandpass filter capable of isolating specific musical notes within an audio recording. Through FFT-based filtering, spectrogram analysis, and listening evaluation, the project illustrates the relationship between pole-zero placement, frequency selectivity, and perceived audio quality. Although the filter successfully emphasizes frequencies near 400 Hz, the remaining sideband levels reveal why stronger attenuation is often required in practical audio DSP applications.
