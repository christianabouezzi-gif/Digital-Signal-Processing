# Chebyshev Bandpass Filter Design and AM Demodulation of FDM Audio

### Christian Abou-Ezzi


---

# Project Overview

This project demonstrates the complete recovery of a hidden audio track embedded within a Frequency Division Multiplexed (FDM) signal using Chebyshev Type-I filtering and amplitude modulation (AM) demodulation techniques.

The project begins by designing a Chebyshev low-pass filter in the Laplace domain. The filter is then transformed into the digital domain through bilinear transformation and converted into a bandpass filter centered at 10 kHz using AM up-conversion.

The resulting bandpass filter isolates Audio Track #2 from the FDM signal. After filtering, AM down-conversion and low-pass recovery are performed to reconstruct the original hidden audio signal.

The recovered mystery soundtrack was identified as:

**Pokemon Theme Song**

---

# Design Specifications

| Parameter          | Value            |
| ------------------ | ---------------- |
| Sampling Frequency | 44.1 kHz         |
| Carrier Frequency  | 10 kHz           |
| Passband Frequency | 3 kHz            |
| Stopband Frequency | 3.5 kHz          |
| Passband Gain      | 0.85             |
| Stopband Gain      | 0.01             |
| Filter Type        | Chebyshev Type-I |
| Filter Order       | N = 10           |

---

# Part A — Low-Pass Chebyshev Filter Design

The low-pass prototype filter was designed first and used as the basis for the final bandpass filter.

## Ripple Factor

The Chebyshev ripple parameter was calculated as

$$
\epsilon =
\sqrt{\frac{1}{(0.85)^2}-1}
$$

## Bilinear Frequency Mapping

Digital frequency specifications were converted into the Laplace domain using

$$
\Omega =
K\tan\left(\frac{\omega}{2}\right)
$$

## Ideal Chebyshev Response

$$
|H_{ideal}(\Omega)|=
\frac{1}
{\sqrt{1+\epsilon^2
\left[T_N\left(\frac{\Omega}{\Omega_p}\right)\right]^2}}
$$

A tenth-order filter was selected to satisfy both passband and stopband requirements.

---

## Figure 1

**Laplace-domain low-pass Chebyshev magnitude response**

<img width="833" height="519" alt="Screenshot 2026-06-23 at 5 06 00 PM" src="https://github.com/user-attachments/assets/e7ccb620-62b2-49b7-b7aa-a6e87561b5ad" />


Shows:

* Passband edge Ωp
* Stopband edge Ωs
* Passband gain = 0.85
* Stopband gain = 0.01

---

## Figure 2

**Laplace-domain pole plot**

<img width="838" height="518" alt="Screenshot 2026-06-23 at 5 06 11 PM" src="https://github.com/user-attachments/assets/057d0d3c-911c-47f3-8edd-fb6b1bea2e44" />


The poles lie on the Chebyshev ellipse inside the Ωp reference circle.

---

# Part B — Bilinear Transformation and Verification

The analog prototype was transformed into a digital IIR filter using

$$
z=
\frac{1+s/K}
{1-s/K}
$$

All poles were verified to lie inside the unit circle.

---

## Figure 3

**Pole-zero plot of low-pass H(z)**

<img width="837" height="517" alt="Screenshot 2026-06-23 at 5 06 26 PM" src="https://github.com/user-attachments/assets/39051e9f-4088-40d3-a88e-838d66dd2b3d" />


Features:

* Unit circle
* Digital poles
* N zeros clustered at z = -1

---

## Figure 4

**DTFT magnitude response of low-pass filter**

<img width="831" height="516" alt="Screenshot 2026-06-23 at 5 06 37 PM" src="https://github.com/user-attachments/assets/277aba26-2496-41c9-a8aa-55f9ae5c5ac4" />


Verification of:

* Passband ripple specification
* Stopband attenuation specification
* Proper bilinear transformation

---

# Part C — Bandpass Filter Synthesis

The low-pass filter was converted into a bandpass filter through AM up-conversion.

## Carrier Frequency

$$
f_c = 10,000\ Hz
$$

Carrier:

$$
c[n]=\cos(\omega_c n)
$$

where

$$
\omega_c =
2\pi \frac{f_c}{f_s}
$$

The bandpass impulse response was generated using

$$
h_{bp}[n]=2h[n]c[n]
$$

The factor of 2 compensates for the attenuation introduced during frequency translation.

---

## Figure 5

**Bandpass magnitude and phase response**

<img width="819" height="512" alt="Screenshot 2026-06-23 at 5 07 30 PM" src="https://github.com/user-attachments/assets/18df6b1f-11ac-48d2-922c-3b1b8fb17157" />


### Top subplot

Bandpass magnitude

$$
|H_{bp}(e^{j\omega})|
$$

showing:

* Passband limits
* Stopband limits
* Center frequency

### Bottom subplot

Phase response

$$
\angle H_{bp}(e^{j\omega})
$$

demonstrating the nonlinear phase behavior of the Chebyshev IIR filter.

---

## Figure 6

**Bandpass magnitude response in dB**

<img width="807" height="505" alt="Screenshot 2026-06-23 at 5 07 38 PM" src="https://github.com/user-attachments/assets/ca292220-39ef-4e36-9c37-a94bbe3bb375" />


This plot verifies:

* Passband gain ≈ -1.41 dB
* Stopband attenuation ≈ -40 dB
* Center frequency = 10 kHz

Band edges:

| Frequency | Value    |
| --------- | -------- |
| fc − fp   | 7000 Hz  |
| fc + fp   | 13000 Hz |
| fc − fs   | 6500 Hz  |
| fc + fs   | 13500 Hz |

---

# Part D — FDM Audio Recovery

After designing the bandpass filter, the hidden audio track was recovered.

## Step 1: Bandpass Filtering

The stereo FDM signal was separated into left and right channels.

Using FFT-based filtering:

$$
X_{bp}(k)=H_{bp}(k)X_{FDM}(k)
$$

the 10 kHz audio channel was isolated.

---

## Step 2: AM Down-Conversion

The filtered signal was translated back to baseband using

$$
x_{dem}[n]

$$

$$
x_{bp}[n]
\cos(\omega_c n)
$$

---

## Step 3: Low-Pass Recovery

The original low-pass Chebyshev filter was applied to remove high-frequency mixing products.

The recovered signals were

$$
y_{ch1}[n]
$$

and

$$
y_{ch2}[n]
$$

A final gain correction factor was applied to compensate for losses introduced throughout the demodulation process.

---

## Output Audio File

```matlab
audiowrite('Mystery_audio2_output.wav', yn_filtered, f_sample)
```

Recovered stereo audio:

* Channel 1 recovered
* Channel 2 recovered
* Saved as Mystery_audio2_output.wav

---

# Part E — Spectrogram Verification

A spectrogram was generated using:

* Slice duration = 0.1 seconds
* Hamming window
* 20% taper
* dB magnitude scale

The recovered audio spectrum confirms:

* Removal of Audio Track #1 at DC
* Successful isolation of Audio Track #2
* Correct AM demodulation
* Proper low-pass recovery

---

## Figure 7

**Recovered audio spectrogram**

<img width="858" height="517" alt="Screenshot 2026-06-23 at 5 07 59 PM" src="https://github.com/user-attachments/assets/97cf6f2d-9111-4412-bc01-616b5a1b023b" />


The spectrogram clearly shows the recovered Pokemon theme song occupying the expected baseband frequencies after demodulation.

---

# MATLAB Functions Used

* chebyshevT()
* tan()
* conv()
* roots()
* fft()
* ifft()
* impz()
* audioread()
* audiowrite()
* pcolor()
* hamming()
* angle()
* rad2deg()

---

# Key Concepts Demonstrated

* Chebyshev Type-I Filter Design
* Laplace-Domain Pole Placement
* Bilinear Transformation
* Pole-Zero Analysis
* DTFT Verification
* Bandpass Filter Synthesis
* Amplitude Modulation
* Frequency Division Multiplexing
* AM Demodulation
* FFT-Based Filtering
* Spectrogram Analysis
* Audio Signal Recovery

---

# Results

A tenth-order Chebyshev Type-I filter was successfully designed and converted into a bandpass filter centered at 10 kHz.

The filter isolated Audio Track #2 from an FDM audio signal and recovered the hidden soundtrack through AM demodulation and low-pass reconstruction.

The recovered mystery audio was successfully identified as:

**Pokemon Theme Song**

This project demonstrates the practical application of digital filter design, communication systems, spectral analysis, and audio signal recovery techniques commonly used in modern DSP systems.
