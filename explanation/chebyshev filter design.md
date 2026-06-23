# Chebyshev Type-I Low-Pass Filter Design Using MATLAB

### Christian Abou-Ezzi


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

<img width="816" height="515" alt="Screenshot 2026-06-22 at 9 05 18 PM" src="https://github.com/user-attachments/assets/ee5a2d80-de6a-4a9e-a77f-b3715e33a50a" />

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

$$
\frac{1}{\sqrt{1+\epsilon^2}} = 1-\delta_1
$$

which yielded:

$$
\epsilon =
\sqrt{\frac{1}{(0.85)^2}-1}
$$

---

#### Step 3: Bilinear Frequency Conversion

Digital-domain frequency specifications were converted into the Laplace domain using:

$$
\Omega = K\tan\left(\frac{\omega}{2}\right)
$$

with


K = 2


to obtain:


Omega_p


and


Omega_s


---

#### Step 4: Ideal Chebyshev Response

The theoretical magnitude response was evaluated using:

$$
|H_{ideal}(\Omega)|=
\frac{1}
{\sqrt{1+\epsilon^2
\left[T_N\left(\frac{\Omega}{\Omega_p}\right)\right]^2}}
$$

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

<img width="814" height="516" alt="Screenshot 2026-06-22 at 9 05 30 PM" src="https://github.com/user-attachments/assets/66d207c8-5a7a-4749-a309-a5aab370871c" />


### Figure 3

**Final Chebyshev response (N = 6)**

<img width="826" height="516" alt="Screenshot 2026-06-22 at 9 05 38 PM" src="https://github.com/user-attachments/assets/ec1f3f8c-70c8-4633-a094-5f2491d88aea" />


---

### Step 6: Pole Calculation

Using Chebyshev pole equations:

$$
\beta=
\left(
\frac{\sqrt{1+\epsilon^2}+1}
{\epsilon}
\right)^{1/N}
$$

$$
r_1=
\Omega_p
\frac{\beta^2+1}
{2\beta}
$$

$$
r_2=
\Omega_p
\frac{\beta^2-1}
{2\beta}
$$

Pole locations were computed from:

$$
p_k=x_k+j y_k
$$

and plotted in the Laplace domain.

### Figure 4

**Chebyshev poles in the Laplace domain**

<img width="844" height="522" alt="Screenshot 2026-06-22 at 9 05 51 PM" src="https://github.com/user-attachments/assets/77930a9e-b4cf-4d05-bd5e-bb1415c2bebc" />


---

### Step 7: Gain Normalization

A gain correction factor was applied:

$$
G=
\frac{1}
{\max(H(s))}
$$

to normalize the filter's maximum gain to unity.

---

## Part C — Bilinear Transformation to H(z)

The analog poles were converted into the digital domain using:

$$
z=
\frac{1+s/K}
{1-s/K}
$$

where:


K = 2

The resulting digital filter contains:

* Six poles
* Six zeros located at z = -1

Polynomial coefficients were generated using MATLAB's `conv()` function.

### Figure 5

**Pole-zero plot of H(z)**

<img width="828" height="523" alt="Screenshot 2026-06-22 at 9 06 03 PM" src="https://github.com/user-attachments/assets/f4163d17-f10a-426c-93d7-132797cc0f27" />


---

## Impulse Response Analysis

The impulse response was generated using:

```matlab
[hn,n] = impz(Hz_num_poly,Hz_denom_poly,100);
```

The resulting response demonstrates the behavior of the designed IIR filter in the discrete-time domain.

### Figure 6

**Impulse response h[n]**

<img width="847" height="525" alt="Screenshot 2026-06-22 at 9 06 20 PM" src="https://github.com/user-attachments/assets/dc683e4d-bffd-4b1d-b0d0-b93cf58d10c9" />


---

## Part D — DTFT Verification

The filter was evaluated in the frequency domain using:

$$
H(e^{j\omega})
$$

with:

$$
z=e^{j\omega}
$$

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

<img width="845" height="523" alt="Screenshot 2026-06-22 at 9 06 29 PM" src="https://github.com/user-attachments/assets/7f01564c-9508-45ec-aa60-7aa7629a9241" />


---

## dB Magnitude Verification

The final design was displayed on a frequency axis in Hertz:

$$
f=
\frac{\omega}{2\pi}
f_s
$$

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

<img width="840" height="523" alt="Screenshot 2026-06-22 at 9 06 38 PM" src="https://github.com/user-attachments/assets/30cfe235-3e41-4681-82c8-0f66aeba199f" />


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
