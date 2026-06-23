# Digital Signal Processing Portfolio

### Christian Abou-Ezzi

Biomedical Engineering | MATLAB | Digital Signal Processing

---

## Overview

This repository contains a collection of Digital Signal Processing (DSP) projects completed in MATLAB. The projects explore signal filtering, spectral analysis, audio reconstruction, and two-dimensional frequency-domain image processing. Together, they demonstrate practical applications of FIR and IIR filter design, z-domain analysis, FFT-based processing, and digital system implementation.

## Topics Covered

* Savitzky-Golay Filtering
* Notch Filter Design
* Comb Filters
* Resonator Filters
* Bandpass Filter Design
* Butterworth Filters
* Chebyshev Filters
* Audio Signal Recovery
* Spectrogram Analysis
* 2D Frequency-Domain Image Filtering

---

# Project 1: Savitzky-Golay Signal Smoothing

## Objective

Design and analyze a Savitzky-Golay FIR filter for denoising breathing data while preserving waveform characteristics.

## Method

Third-order polynomial fitting was performed over moving windows of varying lengths:

* m = 5
* m = 41
* m = 101

The resulting FIR filter coefficients were derived using least-squares estimation and analyzed in both the time and frequency domains.

## Results

Increasing window size improved noise suppression while preserving the overall breathing trend. The largest window produced the smoothest output signal.

## Figures

### Figure 1 – Raw Breathing Signal

<img width="830" height="518" alt="Screenshot 2026-06-23 at 6 53 48 PM" src="https://github.com/user-attachments/assets/a376002d-2d04-4b8b-829f-daa5317055b4" />


### Figure 2 – Smoothed Signals

m = 5

<img width="837" height="522" alt="610939695-c932f871-ba25-45d7-b368-804a76f07c2b" src="https://github.com/user-attachments/assets/5c1c9370-64cf-4176-9a1d-83085852b97e" />

m = 41

<img width="830" height="518" alt="610939720-cf0aadf5-8dfb-40a0-8487-d86934de953c" src="https://github.com/user-attachments/assets/88659ec7-9a79-4ef9-bce6-8f005d5f0caf" />


m = 101

<img width="837" height="512" alt="610939748-51d51503-3f94-479b-8a5f-bd82953eb136" src="https://github.com/user-attachments/assets/e780f1ae-41ee-4cc7-8443-7c23135044d0" />


### Figure 3 – Impulse Response

<img width="838" height="518" alt="Screenshot 2026-06-21 at 1 31 22 PM" src="https://github.com/user-attachments/assets/f9aa1265-ada6-41b6-950e-807c8fb3c689" />

### Figure 4 - Pole-Zero plot

<img width="558" height="511" alt="Screenshot 2026-06-21 at 1 31 29 PM" src="https://github.com/user-attachments/assets/99b05c9a-8dc3-4b66-b411-a4e49d944fb2" />


### Figure 5 – DTFT Magnitude and Phase Response

<img width="821" height="514" alt="Screenshot 2026-06-21 at 1 31 40 PM" src="https://github.com/user-attachments/assets/5b98b2a7-30d4-4510-af75-4c20dc8ba2b9" />


---

# Project 2: Notch Filter Design

## Objective

Design a narrowband notch filter capable of removing a specific interference frequency while preserving the remaining signal content.

## Method

Zeros were placed directly on the unit circle at the interference frequency while poles were positioned nearby to control notch bandwidth.

## Results

The interference component was successfully removed with minimal distortion to the desired signal.

## Figures

### Figure 1 — Notch Filter Magnitude & Phase Response

<img width="750" height="268" alt="Screenshot 2026-06-21 at 10 12 37 PM" src="https://github.com/user-attachments/assets/8cecdf33-fde5-4c77-9925-a1623eb7ae27" />


### Figure 2 — Notch Filter Impulse Response

<img width="771" height="229" alt="Screenshot 2026-06-21 at 10 12 44 PM" src="https://github.com/user-attachments/assets/198aff6a-0e32-4d72-bed3-5126ec2a7b2e" />



---

# Project 3: Comb + Resonator Bandpass Filter

## Objective

Create a narrowband bandpass filter using a comb filter and second-order resonator.

## Design

Comb Filter:

$$
H_1(z)=1-z^{-24}
$$

Resonator:

$$
H_2(z)=\frac{1}{1-2\cos(\omega_p)z^{-1}+z^{-2}}
$$

where:

$$
\omega_p=\frac{\pi}{3}
$$

Combined Filter:

$$
H(z)=H_1(z)H_2(z)
$$

## Results

The comb filter eliminated periodic frequencies while the resonator amplified the desired passband.

## Figures

### Figure 1 – Pole-Zero Plot

<img width="606" height="523" alt="Screenshot 2026-06-22 at 2 45 01 PM" src="https://github.com/user-attachments/assets/76528f80-4b0a-422f-9a1b-030c0e819139" />


### Figure 2 – Impulse Response of Total Filter

<img width="807" height="524" alt="Screenshot 2026-06-22 at 2 45 16 PM" src="https://github.com/user-attachments/assets/c5f84692-205d-44fe-8b98-440e491f030f" />


### Figure 3 – Bandpass DTFT Response Before Gain Adjustment

<img width="801" height="520" alt="Screenshot 2026-06-22 at 2 45 28 PM" src="https://github.com/user-attachments/assets/cb9bd621-fab3-4e1d-87ff-68a24cb2d8fa" />


### Figure 4 – Bandpass DTFT Response after Gain Adjustment

<img width="807" height="513" alt="Screenshot 2026-06-22 at 2 45 57 PM" src="https://github.com/user-attachments/assets/be0e84ff-5dd3-402d-ae64-206cc486e709" />


---

# Project 4: Comb + Resonator Audio Recovery

## Objective

Recover a desired audio component embedded within multiple frequencies.

## Method

The bandpass filter developed in Project 3 was applied to an audio recording. FFT analysis was used to observe spectral content before and after filtering.

## Results

The target frequency was isolated while surrounding components were attenuated.

## Figures

### Figure 1 – Original Audio Spectrum

<img width="797" height="514" alt="Screenshot 2026-06-22 at 3 12 36 PM" src="https://github.com/user-attachments/assets/cbf0b678-391d-4f1e-9b89-62581d482492" />


### Figure 2 – Input vs Filtered Output

<img width="804" height="516" alt="Screenshot 2026-06-22 at 3 13 38 PM" src="https://github.com/user-attachments/assets/47c3e2cd-03a0-453d-9e7a-f39d00dbdb25" />


### Figure 3 – Filtered Spectrogram

<img width="822" height="518" alt="Screenshot 2026-06-22 at 3 13 54 PM" src="https://github.com/user-attachments/assets/fc4f4269-16b7-4f6f-8155-f742447b272f" />


---

# Project 5: Butterworth Filter Design

## Objective

Design a Butterworth low-pass filter meeting specified passband and stopband requirements.

## Specifications

* Passband Edge: 5 kHz
* Stopband Edge: 8 kHz
* Passband Gain: 0.9
* Stopband Gain: 0.01

## Method

The design procedure included:

1. Frequency prewarping
2. Analog Butterworth prototype generation
3. Pole calculation
4. Bilinear transformation
5. Digital implementation

## Results

The filter achieved a smooth passband with strong stopband attenuation.

## Figures


### Figure 1 – Laplace Pole Plot

<img width="584" height="515" alt="Screenshot 2026-06-22 at 8 24 19 PM" src="https://github.com/user-attachments/assets/634071b1-02e2-4597-8244-02400028c81c" />


### Figure 2 – Digital Pole-Zero Plot

<img width="798" height="519" alt="Screenshot 2026-06-22 at 8 24 28 PM" src="https://github.com/user-attachments/assets/2005a952-ac39-43da-a8ab-30484a0af237" />


### Figure 3 - DTFT Magnitude and Phase

<img width="818" height="517" alt="Screenshot 2026-06-22 at 8 24 47 PM" src="https://github.com/user-attachments/assets/2db82fdf-ba8c-4760-9c73-a32793fb639f" />


### Figure 4 - FDM Output Spectrogram

<img width="829" height="515" alt="Screenshot 2026-06-22 at 8 25 53 PM" src="https://github.com/user-attachments/assets/831ea974-d7bf-4d65-8649-697a3533e37a" />


---

# Project 6: Chebyshev Filter Design

## Objective

Design a Chebyshev low-pass filter with improved transition-band performance.

## Method

A Chebyshev Type-I design was implemented using passband ripple specifications and bilinear transformation.

## Results

Compared to the Butterworth filter, the Chebyshev design achieved a steeper rolloff while introducing controlled passband ripple.

## Figures

### Figure 1 – Ideal Chebyshev Laplace Design

<img width="826" height="516" alt="Screenshot 2026-06-22 at 9 05 38 PM" src="https://github.com/user-attachments/assets/50aed8da-13a5-4ee4-89d4-8d46da45865c" />

### Figure 2 – Chebyshev Laplace Poles

<img width="844" height="522" alt="Screenshot 2026-06-22 at 9 05 51 PM" src="https://github.com/user-attachments/assets/fe2a6ecf-bef1-41ad-9090-290206d2620e" />

### Figure 3 – Digital Pole Zero Plot

<img width="828" height="523" alt="Screenshot 2026-06-22 at 9 06 03 PM" src="https://github.com/user-attachments/assets/9e24e0bc-5bb4-4323-aa49-8514ede207d5" />


### Figure 4 - DTFT Magnitude and Phase

<img width="845" height="523" alt="Screenshot 2026-06-22 at 9 06 29 PM" src="https://github.com/user-attachments/assets/bd666b25-a240-40cc-ac09-b221cecc04ea" />

---

# Project 7: Audio Treasure Hunt

## Objective

Recover hidden audio information embedded within a complex recording.

## Method

FFT analysis and frequency-selective filtering techniques were used to isolate and reconstruct hidden audio content.

## Results

Embedded frequency components were successfully identified and recovered.

## Figures

### Figure - 1 Low Pass Pole Zero Plot

<img width="837" height="517" alt="Screenshot 2026-06-23 at 5 06 26 PM" src="https://github.com/user-attachments/assets/0e9417f1-3b3c-456c-bc5f-6824435629eb" />


### Figure 2 – Chebyshev Bandpass design

<img width="819" height="512" alt="Screenshot 2026-06-23 at 5 07 30 PM" src="https://github.com/user-attachments/assets/273cbd95-fb3a-48fc-9597-abeb40484607" />


### Figure 3 – Bandpass dB response

<img width="807" height="505" alt="Screenshot 2026-06-23 at 5 07 38 PM" src="https://github.com/user-attachments/assets/3cc1ee2c-ec39-4239-aa56-5343c1528073" />


### Figure 4 – Mystery Sound Spectrum

<img width="858" height="517" alt="Screenshot 2026-06-23 at 5 07 59 PM" src="https://github.com/user-attachments/assets/ce8e480a-ea05-447d-8be0-1b86a9f738c0" />


---

# Project 8: Chubby Butterworth 2D Filter

## Objective

Design a two-dimensional Butterworth low-pass filter for image denoising and frequency-domain image enhancement.

## Method

The image was transformed using a 2D FFT. A Butterworth transfer function was applied in the frequency domain before reconstructing the filtered image through an inverse FFT.

## Results

High-frequency noise was suppressed while preserving image structure.

## Figures

### Figure 1 – 2D Butterworth Filter

<img width="655" height="519" alt="Screenshot 2026-06-23 at 5 24 23 PM" src="https://github.com/user-attachments/assets/a98177da-9de8-4e8e-a25e-fc310e63a16f" />


### Figure 2 – 2D Filtred Image Comparison

<img width="1016" height="337" alt="Screenshot 2026-06-23 at 5 24 57 PM" src="https://github.com/user-attachments/assets/4ebfe03d-2ea1-4282-9f62-2d870664a265" />


### Figure 3 – Butterworth Spectrum and Output


<img width="1079" height="472" alt="Screenshot 2026-06-23 at 5 25 30 PM" src="https://github.com/user-attachments/assets/1f5c804e-9ef2-4edd-82bc-5eb0f1fe62c0" />


---

# Software

* MATLAB
* Signal Processing Toolbox
* Image Processing Toolbox

# Skills Demonstrated

* FIR Filter Design
* IIR Filter Design
* Butterworth Design
* Chebyshev Design
* Pole-Zero Analysis
* FFT Analysis
* DTFT Analysis
* Audio Reconstruction
* Spectrogram Processing
* Frequency-Domain Image Filtering
* Digital Signal Analysis

---

## Author

**Christian Abou-Ezzi**

Biomedical Engineering Portfolio

Digital Signal Processing • Audio Analysis • MATLAB Development • Filter Design
