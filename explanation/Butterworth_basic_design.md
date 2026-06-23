# Butterworth Low-Pass Filter Design for FDM Audio Recovery

### Christian Abou-Ezzi


---

## Project Overview

This project implements a complete Butterworth low-pass filter design workflow from first principles using MATLAB. The objective was to recover an audio signal embedded within a Frequency Division Multiplexed (FDM) audio file by designing a Butterworth filter that satisfies specified passband and stopband requirements.

The filter was designed in the continuous-time domain, transformed into the discrete-time domain using the bilinear transformation, verified through pole-zero analysis and frequency response plots, and finally applied to recover the desired audio track.

---

## Project Objective

The goal of this project was to:

- Design a Butterworth low-pass filter meeting given frequency specifications.
- Determine the required filter order and cutoff frequency.
- Analyze filter poles in the Laplace domain.
- Convert the design into a digital filter using the bilinear transform.
- Verify filter behavior in the DTFT domain.
- Filter a Frequency Division Multiplexed (FDM) audio recording.
- Recover the desired audio signal while suppressing unwanted high-frequency content.

---

## Design Specifications

| Parameter | Value |
|------------|---------|
| Sampling Frequency | 44,100 Hz |
| Passband Frequency | 5,000 Hz |
| Stopband Frequency | 8,000 Hz |
| Passband Gain | 0.90 |
| Stopband Gain | 0.01 |

The filter was designed to pass audio frequencies below 5 kHz while strongly attenuating frequencies above 8 kHz.

---

## Theory

### Butterworth Filter

A Butterworth filter provides a maximally-flat passband response with no ripple.

The continuous-time magnitude response is

```math
|H(\Omega)|=
\frac{G}
{\sqrt{1+\left(\frac{\Omega}{\Omega_n}\right)^{2N}}}
```

where:

- `N` = filter order
- `Ωn` = cutoff frequency
- `G` = gain adjustment factor

The design process determines:

- Minimum filter order `N`
- Cutoff frequency `Ωn`
- Butterworth pole locations

---

## MATLAB Implementation

### Part A – Continuous-Time Butterworth Design

The script:

1. Converts frequency specifications into digital frequencies.
2. Applies frequency pre-warping.
3. Calculates:

```math
\Omega_p
```

```math
\Omega_s
```

4. Solves for the minimum Butterworth order:

```math
N
```

5. Solves for:

```math
\Omega_n
```

6. Computes gain normalization:

```math
G
```

---

## Figure 1 – CTFT Magnitude Response

<img width="820" height="516" alt="Screenshot 2026-06-22 at 8 23 19 PM" src="https://github.com/user-attachments/assets/ca988706-2c45-43ea-8859-424f99717b5b" />


**Figure 1:** Gain-adjusted CTFT magnitude response.

The plot verifies:

- Passband specification
- Stopband specification
- Butterworth cutoff frequency
- Gain normalization

---

### Butterworth Pole Analysis

The Butterworth poles are calculated using

```math
p_k=
\Omega_n
e^{j\left(
\frac{\pi}{2}
+
\frac{(2k+1)\pi}{2N}
\right)}
```

Only poles in the left-half plane are retained to ensure stability.

---

## Figure 2 – Laplace Pole Plot

<img width="584" height="515" alt="Screenshot 2026-06-22 at 8 24 19 PM" src="https://github.com/user-attachments/assets/947021f0-f441-4f0f-b4f3-f6c7601c6655" />


**Figure 2:** Butterworth poles in the s-plane.

The plot shows:

- Pole locations
- Butterworth pole circle
- 45° reference lines

---

## Part B – Bilinear Transformation

The continuous-time filter is converted into a digital filter using

```math
s=
K
\frac{z-1}{z+1}
```

where

```math
K=\frac{2}{T_d}
```

The transformation generates:

- Digital poles
- Zeros at `z = -1`
- Digital transfer function coefficients

---

## Figure 3 – Pole-Zero Plot

<img width="798" height="519" alt="Screenshot 2026-06-22 at 8 24 28 PM" src="https://github.com/user-attachments/assets/00874a48-e7e7-4c72-89d1-57ef90ceeffb" />


**Figure 3:** Pole-zero plot of the digital Butterworth filter.

The plot shows:

- Butterworth poles
- N zeros at `z = -1`
- Unit circle

---

## Impulse Response

The impulse response is extracted using:

```matlab
[hn,n] = impz(Hz_num_poly, Hz_denom_poly, N0);
```

The resulting sequence is used as the filtering kernel.

---

## Figure 4 – Impulse Response

<img width="831" height="515" alt="Screenshot 2026-06-22 at 8 24 37 PM" src="https://github.com/user-attachments/assets/d8885aec-5045-4efd-a361-65e761f23020" />


**Figure 4:** Butterworth low-pass filter impulse response.

The plot demonstrates:

- Stable decay
- Infinite impulse response behavior
- Digital filter implementation

---

## Part C – DTFT Verification

The digital transfer function is evaluated on the unit circle:

```math
z=e^{j\omega}
```

to obtain

```math
H(e^{j\omega})
```

Verification includes:

- Magnitude response
- Phase response
- Passband performance
- Stopband attenuation

---

## Figure 5 – DTFT Magnitude and Phase

<img width="818" height="517" alt="Screenshot 2026-06-22 at 8 24 47 PM" src="https://github.com/user-attachments/assets/2c705bfb-7392-4166-8377-b8bfbd88105a" />


**Figure 5:** DTFT magnitude and phase response.

### Top Subplot

- Magnitude response
- Passband and stopband verification

### Bottom Subplot

- Phase response
- Nonlinear phase behavior characteristic of IIR filters

---

## Figure 6 – Magnitude Response (dB)

<img width="825" height="513" alt="Screenshot 2026-06-22 at 8 25 39 PM" src="https://github.com/user-attachments/assets/1008a049-62ac-4690-8441-458eda974500" />


**Figure 6:** DTFT magnitude response in decibels.

The plot verifies:

- Passband gain requirement:
  
  ```math
  20\log_{10}(0.9) \approx -0.91\text{ dB}
  ```

- Stopband attenuation requirement:

  ```math
  20\log_{10}(0.01) = -40\text{ dB}
  ```

---

## Part D – Audio Recovery

The FDM audio file is loaded using:

```matlab
[qn, f_sample] = audioread('Problem4_FDM_audio_input.wav');
```

The two audio channels are separated and transformed into the frequency domain:

```matlab
q_ch1_k = fft(q_ch1);
q_ch2_k = fft(q_ch2);
```

The filter is applied using frequency-domain multiplication:

```math
Y[k] = H[k]X[k]
```

The filtered signal is reconstructed using:

```matlab
ifft()
```

and saved as:

```matlab
FDM_lowpass_output.wav
```

---

## Spectrogram Analysis

A short-time Fourier transform approach is used to analyze the filtered audio.

### Spectrogram Settings

- Time slice length: 0.1 seconds
- Hamming window
- DFT magnitude displayed in dB
- Frequency range: 0–20 kHz
- Dynamic range: -80 dB to +20 dB

---

## Figure 7 – Filtered Audio Spectrogram

<img width="829" height="515" alt="Screenshot 2026-06-22 at 8 25 53 PM" src="https://github.com/user-attachments/assets/d6dd2b27-1939-47a5-91fc-748c365d9008" />


**Figure 7:** Spectrogram of the recovered audio signal.

The spectrogram demonstrates:

- Removal of the AM-modulated channel near 10 kHz
- Preservation of the desired baseband audio
- Significant reduction of high-frequency interference

---

## Results

The Butterworth filter successfully:

- Met passband and stopband specifications.
- Produced a stable digital filter.
- Removed the AM up-converted audio channel.
- Recovered the desired audio signal.
- Reduced high-frequency noise visible in the spectrogram.

---

## Possible Improvements

To further improve audio quality:

- Increase stopband attenuation requirements.
- Reduce transition bandwidth.
- Increase filter order.

A higher-order Butterworth filter would introduce additional poles, producing a steeper roll-off and improved rejection of unwanted frequency components.

---

## Skills Demonstrated

- Digital Signal Processing (DSP)
- Butterworth Filter Design
- Laplace Transform Analysis
- Bilinear Transformation
- Pole-Zero Analysis
- DTFT Analysis
- Audio Signal Processing
- Frequency Domain Filtering
- Spectrogram Generation
- MATLAB Programming

---
