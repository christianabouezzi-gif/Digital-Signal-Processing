# Chebyshev Type-I Low-Pass Filter Design Using MATLAB

### Christian Abou-Ezzi

Digital Signal Processing (DSP) Portfolio Project

---

## Project Overview

This project implements the complete design procedure for a Type-I Chebyshev Infinite Impulse Response (IIR) low-pass filter using MATLAB. The filter is designed from first principles by deriving the analog prototype in the Laplace domain, converting it into the digital domain through bilinear transformation, and verifying performance through pole-zero analysis, impulse response evaluation, and frequency-domain analysis.

Unlike a Butterworth filter, the Chebyshev design introduces controlled passband ripple in exchange for a steeper transition band and improved stopband attenuation.

---

## Design Specifications

| Parameter               | Value                 |
| ----------------------- | --------------------- |
| Passband Edge Frequency | ωₚ = 0.1π rad/sample  |
| Stopband Frequency      | ωₛ = 0.16π rad/sample |
| Passband Gain           | 0.85                  |
| Passband Ripple         | δ₁ = 0.15             |
| Stopband Gain           | 0.01 (-40 dB)         |
| Sampling Frequency      | 44,100 Hz             |

---

## Design Procedure

### Part A — Chebyshev Polynomial Analysis

The project begins by exploring MATLAB's built-in `chebyshevT()` function to visualize Chebyshev polynomials.

The following polynomials were plotted:

* T₂(x)
* T₃(x)
* T₆(x)

for:

```matlab
x = -1.2:0.01:1.2;
```

These functions demonstrate the oscillatory behavior responsible for the passband ripple observed in Chebyshev filters.

### Figure 1

**Warm-up plot for Chebyshev polynomials**

*Insert Figure 1 here*

---

### Part B — Analog Chebyshev Filter Design

#### Step 1: Initial Pole Guess

An initial estimate of:

```matlab
N = 4
```

was selected.

#### Step 2: Ripple Factor Calculation

The Chebyshev ripple parameter ε was determined from:

[
\frac{1}{\sqrt{1+\epsilon^2}} = 1-\delta_1
]

which yielded:

[
\epsilon =
\sqrt{\frac{1}{(0.85)^2}-1}
]

---

#### Step 3: Bilinear Frequency Conversion

Digital-domain frequency specifications were converted into the Laplace domain using:

[
\Omega = K\tan\left(\frac{\omega}{2}\right)
]

with

[
K = 2
]

to obtain:

[
\Omega_p
]

and

[
\Omega_s
]

---

#### Step 4: Ideal Chebyshev Response

The theoretical magnitude response was evaluated using:

[
|H_{ideal}(\Omega)|=
\frac{1}
{\sqrt{1+\epsilon^2
\left[T_N\left(\frac{\Omega}{\Omega_p}\right)\right]^2}}
]

The initial design failed to satisfy the stopband attenuation requirement.

---

#### Step 5: Filter Order Iteration

The filter order was increased until the stopband specification was satisfied.

Final design:

```matlab
N = 6
```

This order provided sufficient attenuation at the stopband edge frequency.

### Figure 2

**Theoretical Chebyshev response (N = 4)**

*Insert Figure 2 (first plot) here*

### Figure 3

**Final Chebyshev response (N = 6)**

*Insert Figure 2 (second plot after redesign) here*

---

### Step 6: Pole Calculation

Using Chebyshev pole equations:

[
\beta=
\left(
\frac{\sqrt{1+\epsilon^2}+1}
{\epsilon}
\right)^{1/N}
]

[
r_1=
\Omega_p
\frac{\beta^2+1}
{2\beta}
]

[
r_2=
\Omega_p
\frac{\beta^2-1}
{2\beta}
]

Pole locations were computed from:

[
p_k=x_k+j y_k
]

and plotted in the Laplace domain.

### Figure 4

**Chebyshev poles in the Laplace domain**

*Insert Figure 3 here*

---

### Step 7: Gain Normalization

A gain correction factor was applied:

[
G=
\frac{1}
{\max(H(s))}
]

to normalize the filter's maximum gain to unity.

---

## Part C — Bilinear Transformation to H(z)

The analog poles were converted into the digital domain using:

[
z=
\frac{1+s/K}
{1-s/K}
]

where:

[
K = 2
]

The resulting digital filter contains:

* Six poles
* Six zeros located at z = -1

Polynomial coefficients were generated using MATLAB's `conv()` function.

### Figure 5

**Pole-zero plot of H(z)**

*Insert Figure 4 here*

---

## Impulse Response Analysis

The impulse response was generated using:

```matlab
[hn,n] = impz(Hz_num_poly,Hz_denom_poly,100);
```

The resulting response demonstrates the behavior of the designed IIR filter in the discrete-time domain.

### Figure 6

**Impulse response h[n]**

*Insert Figure 5 here*

---

## Part D — DTFT Verification

The filter was evaluated in the frequency domain using:

[
H(e^{j\omega})
]

with:

[
z=e^{j\omega}
]

---

### Magnitude Response

The non-dB magnitude response verifies:

* Passband ripple requirements
* Passband corner frequency
* Stopband attenuation

### Phase Response

The phase plot illustrates the nonlinear phase characteristics typical of IIR filters.

### Figure 7

**DTFT magnitude and phase response**

*Insert Figure 6 here*

---

## dB Magnitude Verification

The final design was displayed on a frequency axis in Hertz:

[
f=
\frac{\omega}{2\pi}
f_s
]

with:

```matlab
f_sample = 44100 Hz
```

This plot verifies compliance with:

| Requirement     | Value    |
| --------------- | -------- |
| Passband Gain   | -1.41 dB |
| Stopband Gain   | -40 dB   |
| Frequency Range | 0–10 kHz |

### Figure 8

**DTFT magnitude response in dB**

*Insert Figure 7 here*

---

## MATLAB Functions Used

* `chebyshevT()`
* `tan()`
* `conv()`
* `roots()`
* `impz()`
* `plot()`
* `stem()`
* `xline()`
* `yline()`
* `legend()`
* `rad2deg()`

---

## Key Concepts Demonstrated

* Chebyshev polynomial behavior
* Passband ripple design
* Analog filter synthesis
* Bilinear transformation
* Laplace-domain pole placement
* Digital IIR filter realization
* Pole-zero analysis
* Impulse response generation
* DTFT verification
* Frequency response analysis in dB

---

## Results

A sixth-order Chebyshev Type-I low-pass filter was successfully designed to satisfy:

* Passband edge frequency of 0.1π
* Stopband frequency of 0.16π
* Passband gain of 0.85
* Stopband attenuation of -40 dB

The final design met all specified requirements while demonstrating the sharper transition band characteristic of Chebyshev filters compared to equivalent Butterworth designs.
