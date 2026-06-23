# 2D Image Denoising Using Frequency-Domain Low-Pass Filters

### Christian Abou-Ezzi


---

# Project Overview

This project investigates the use of three different two-dimensional low-pass filters for removing periodic diagonal noise from a grayscale image.

The noisy image was transformed into the frequency domain using a two-dimensional Fourier Transform. Three filter designs were implemented and compared:

1. Butterworth Low-Pass Filter
2. Chebyshev Type-I Low-Pass Filter
3. Gaussian Low-Pass Filter

Each filter was applied directly in the DFT domain using zero-phase filtering. The filtered images were reconstructed using the inverse Fourier Transform and visually compared to determine which design provided the best balance between noise suppression and image preservation.

---

# Project Objective

The objective of this project was to:

- Design 2D frequency-domain low-pass filters
- Remove diagonal periodic noise from an image
- Compare Butterworth, Chebyshev, and Gaussian filter performance
- Evaluate the tradeoff between noise reduction and image blurring
- Visualize filtering effects in both the image and frequency domains

---

# Input Image

The noisy grayscale image:

```matlab
Tay_Tay_BW_noisy_diagonal.jpeg
```

contains periodic diagonal interference appearing as stripes across the image.

---

## Figure 1
**Original Noisy Image**

<img width="512" height="512" alt="Tay_Tay_BW_noisy_diagonal copy" src="https://github.com/user-attachments/assets/ca4d38d0-35dd-4cf2-8b79-4c50e8d3b25d" />



The diagonal noise appears as repetitive high-frequency components distributed across the image.

---

# Theory

A two-dimensional low-pass filter suppresses high-frequency content while preserving low-frequency image information.

The frequency-domain radius was defined as

$$
W=\sqrt{\omega_m^2+\omega_n^2}
$$

where:

- ωm = row frequency
- ωn = column frequency

The filter response is then evaluated based on the distance from the frequency-domain origin.

---

# Part A — 2D Butterworth Filter Design

A Butterworth low-pass filter was designed using passband and stopband specifications.

## Design Parameters

| Parameter | Value |
|------------|---------|
| Passband Edge | 0.12π |
| Stopband Edge | 0.20π |
| Passband Gain | 0.85 |
| Stopband Gain | 0.01 |

---

## Butterworth Transfer Function

$$
H(\omega_m,\omega_n)
=
\frac{1}
{\sqrt{1+\left(\frac{W}{\omega_p}\right)^{2N}}}
$$

where

$$
W=\sqrt{\omega_m^2+\omega_n^2}
$$

---

## Figure 2
**2D Butterworth Frequency Response**

<img width="655" height="519" alt="Screenshot 2026-06-23 at 5 24 23 PM" src="https://github.com/user-attachments/assets/96758e9b-cf0c-41f2-9a2a-937b32fb553b" />


The Butterworth filter exhibits:

- Smooth monotonic rolloff
- No passband ripple
- Moderate transition bandwidth

---

# Part A2 — 2D Chebyshev Filter Design

A Chebyshev Type-I filter was designed using the same passband and stopband constraints.

---

## Ripple Parameter

$$
\epsilon
=
\sqrt{\frac{1}{0.85^2}-1}
$$

---

## Chebyshev Response

$$
H(\omega_m,\omega_n)
=
\frac{1}
{\sqrt{
1+\epsilon^2
\left[T_N\left(\frac{W}{\omega_p}\right)\right]^2
}}
$$

---

## Figure 3
**2D Chebyshev Frequency Response**

<img width="619" height="520" alt="Screenshot 2026-06-23 at 5 24 42 PM" src="https://github.com/user-attachments/assets/a480edde-9bc1-4974-a3b4-a3c44f4d113d" />


Characteristics:

- Sharper transition band
- Stronger attenuation
- Passband ripple
- Potential ringing artifacts

---

# Part A3 — 2D Gaussian Filter Design

A Gaussian smoothing filter was implemented using

$$
H(\omega_m,\omega_n)
=
e^{-\left(\frac{W}{\omega_p}\right)^2}
$$

where

$$
\omega_p = 0.12\pi
$$

---

## Figure 4
**2D Gaussian Frequency Response**

<img width="594" height="509" alt="Screenshot 2026-06-23 at 5 24 48 PM" src="https://github.com/user-attachments/assets/376c0c8d-ad56-4cb0-a1fd-fe2c03cce2a1" />


Characteristics:

- Smoothest frequency response
- No ringing
- Strong image smoothing
- Increased blur

---

# Part B — Frequency Domain Filtering

The noisy image was normalized and transformed into the frequency domain using

```matlab
X = fftshift(fft2(x_double));
```

Each filter was applied through direct multiplication:

$$
Y(\omega_m,\omega_n)
=
X(\omega_m,\omega_n)
H(\omega_m,\omega_n)
$$

The filtered image was reconstructed using

```matlab
ifft2(ifftshift(Y))
```

---

# Filtered Image Comparison

## Figure 5
**Filtered Image Results**

<img width="1016" height="337" alt="Screenshot 2026-06-23 at 5 24 57 PM" src="https://github.com/user-attachments/assets/af38e2c4-4630-4d4a-b7e8-85c9888cd8ac" />


### Left
Butterworth Filter

### Center
Chebyshev Filter

### Right
Gaussian Filter

---

### Butterworth Result

Advantages:

- Removes diagonal noise effectively
- Preserves image detail
- Minimal artifacts

Disadvantages:

- Slight blurring

---

### Chebyshev Result

Advantages:

- Strongest noise suppression
- Sharp transition band

Disadvantages:

- Produces faint ghosting artifacts
- Ripple causes ringing effects

---

### Gaussian Result

Advantages:

- Smooth appearance
- No ringing

Disadvantages:

- Significant loss of detail
- Excessive image blur

---

# Part B5 — Magnitude Spectra of Filter Responses

The magnitude response of each filter was visualized across the two-dimensional frequency plane.

---

## Figure 6
**Magnitude Spectra |H(ωm,ωn)|**

<img width="1013" height="296" alt="Screenshot 2026-06-23 at 5 25 12 PM" src="https://github.com/user-attachments/assets/d8ffbda2-c5a8-43da-a29d-930a30267b90" />


This figure illustrates:

- Butterworth gradual rolloff
- Chebyshev sharper cutoff
- Gaussian exponential decay

---

# Part B6 — Filtered Spectra and Image Reconstruction

The filtered spectra

$$
Y(\omega_m,\omega_n)
$$

were displayed alongside the reconstructed images.

---

## Figure 7
**Butterworth Spectrum and Output Image**

<img width="1079" height="472" alt="Screenshot 2026-06-23 at 5 25 30 PM" src="https://github.com/user-attachments/assets/29f46e68-9071-4fd3-808a-fff9a93e4db6" />


---

## Figure 8
**Chebyshev Spectrum and Output Image**

<img width="1031" height="462" alt="Screenshot 2026-06-23 at 5 25 39 PM" src="https://github.com/user-attachments/assets/9aadbb37-d12b-4248-aa75-666d084d7885" />


---

## Figure 9
**Gaussian Spectrum and Output Image**

<img width="1083" height="464" alt="Screenshot 2026-06-23 at 5 25 49 PM" src="https://github.com/user-attachments/assets/415ed6b7-7348-4983-9c07-3b9309602b02" />


---

# Performance Comparison

| Filter | Noise Removal | Detail Preservation | Artifacts |
|----------|----------------|---------------------|------------|
| Butterworth | Excellent | Good | Minimal |
| Chebyshev | Excellent | Moderate | Ghosting |
| Gaussian | Moderate | Poor | None |

---

# Best Performing Filter

The Butterworth filter produced the best overall result.

Reasons:

- Removed nearly all diagonal stripe noise
- Preserved image structure
- Produced minimal artifacts
- Maintained natural image appearance

While the Chebyshev filter removed noise more aggressively, passband ripple introduced visible ghosting. The Gaussian filter avoided artifacts but excessively blurred fine image details.

---

# MATLAB Functions Used

- fft2()
- ifft2()
- fftshift()
- ifftshift()
- meshgrid()
- pcolor()
- chebyshevT()
- tan()
- solve()
- mat2gray()
- imshow()
- log10()

---

# Key Concepts Demonstrated

- Two-Dimensional Fourier Transform
- Frequency-Domain Image Processing
- Butterworth Filter Design
- Chebyshev Filter Design
- Gaussian Filtering
- Zero-Phase Filtering
- Spectral Analysis
- Image Denoising
- Frequency-Domain Visualization
- Spatial-Frequency Interpretation

---

# Results

Three frequency-domain low-pass filters were implemented and evaluated for image denoising.

The Butterworth filter provided the best balance between noise suppression and image preservation. The Chebyshev filter achieved stronger attenuation but introduced artifacts, while the Gaussian filter produced excessive smoothing and loss of detail.

This project demonstrates practical applications of 2D digital filtering and frequency-domain image enhancement techniques commonly used in medical imaging, microscopy, photography, and computer vision systems.
