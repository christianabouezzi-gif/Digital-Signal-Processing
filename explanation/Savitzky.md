# Savitzky-Golay Filter Analysis and DTFT Characterization

## Christian Abou-Ezzi


---

## Project Overview

This project investigated the behavior of Savitzky-Golay (SG) smoothing filters through impulse response analysis, pole-zero characterization, and frequency-domain evaluation using MATLAB. The objective was to examine how increasing filter window length affects smoothing performance and noise suppression in physiological breathing data.

The analysis was performed for three different window lengths:

- **m = 5**
- **m = 41**
- **m = 101**

For each filter configuration, the impulse response `h[n]`, transfer function `H(z)`, pole-zero plot, and Discrete-Time Fourier Transform (DTFT) magnitude response were computed and visualized.

---

## Objectives

- Calculate the sampling frequency from experimental breathing data.
- Derive Savitzky-Golay filter impulse responses using least-squares polynomial fitting.
- Construct FIR transfer functions from impulse response coefficients.
- Analyze filter poles and zeros in the z-domain.
- Compute DTFT magnitude responses.
- Compare frequency selectivity for different filter window lengths.
- Estimate the frequency range associated with measurement noise.

---

## Methodology

### 1. Sampling Frequency Calculation

The time spacing between adjacent measurements was extracted from the breathing dataset:

```matlab
time_tick = time(3) - time(2);
fsample = 1/time_tick;
```

The sampling frequency was used to convert normalized frequency into physical frequency units (Hz) for DTFT visualization.

---

### 2. Savitzky-Golay Filter Design

A third-order polynomial model was used for local curve fitting:

\[
y(z) = a_0 + a_1z + a_2z^2 + a_3z^3
\]

For each window length, an A-matrix was generated from the local sample indices and used to compute the least-squares solution:

```matlab
B = inv(A'*A)*A';
```

The first row of the resulting matrix corresponds to the effective impulse response:

```matlab
h_n = B(1,:);
```

This procedure was repeated for:

- m = 5
- m = 41
- m = 101

---

### 3. Impulse Response Analysis

The impulse response of each filter was visualized using stem plots:

```matlab
stem(bound,h_n)
```

#### Outputs

- Figure 1a: h[n] for m = 5

<img width="854" height="522" alt="Screenshot 2026-06-21 at 1 30 28 PM" src="https://github.com/user-attachments/assets/d465c306-499b-4c1a-9c6a-a77e1598bcf1" />


- Figure 2a: h[n] for m = 41

<img width="830" height="515" alt="Screenshot 2026-06-21 at 1 30 42 PM" src="https://github.com/user-attachments/assets/6cae4232-a58d-4d26-9dd5-ab76a11b9b6f" />

- Figure 3a: h[n] for m = 101

<img width="838" height="518" alt="Screenshot 2026-06-21 at 1 31 22 PM" src="https://github.com/user-attachments/assets/869ffbbb-1d27-47c8-8769-f1be4f64439c" />


---

### 4. Transfer Function Construction

The impulse response coefficients were used directly as the numerator of the FIR transfer function:

```matlab
Hz = tf(Hz_numerator,1,deltaT);
```

Because Savitzky-Golay filters are finite impulse response (FIR) filters, the denominator remains equal to one.

---

### 5. Pole-Zero Analysis

Pole and zero locations were extracted using:

```matlab
Hz_zeros = zero(Hz);
Hz_poles = pole(Hz);
```

Pole-zero diagrams were generated and compared against the unit circle to evaluate filter characteristics.

#### Outputs

- Figure 1b: Pole-Zero Plot (m = 5)

<img width="543" height="517" alt="Screenshot 2026-06-21 at 1 29 33 PM" src="https://github.com/user-attachments/assets/34043caf-6d4d-4c86-b7e6-404286e0d094" />

- Figure 2b: Pole-Zero Plot (m = 41)

<img width="594" height="512" alt="Screenshot 2026-06-21 at 1 30 53 PM" src="https://github.com/user-attachments/assets/73a15dca-a976-4988-9fff-7f2de9c26402" />

- Figure 3b: Pole-Zero Plot (m = 101)

<img width="558" height="511" alt="Screenshot 2026-06-21 at 1 31 29 PM" src="https://github.com/user-attachments/assets/d95c6ce5-dc62-41d2-ac3d-8089203bb6bb" />


---

### 6. DTFT Computation

The frequency response was computed directly from the impulse response using the DTFT definition:

\[
H(e^{j\omega}) = \sum_{n=0}^{N-1} h[n]e^{-j\omega n}
\]

Implemented in MATLAB as:

```matlab
Hw_numerator = 0;

for l = 1:length(h)
    Hw_numerator = Hw_numerator + ...
        h(l).*exp(-1i*(l-1).*w);
end

H_total = Hw_numerator;
```

---

### 7. Frequency Response Visualization

The DTFT magnitude response was plotted using dual frequency axes:

- Bottom axis: Normalized frequency (ω)
- Top axis: Physical frequency (Hz)

Magnitude was evaluated using:

```matlab
abs(H_total)
```

#### Outputs

- Figure 1c: DTFT Magnitude Plot (m = 5)

<img width="861" height="520" alt="Screenshot 2026-06-21 at 1 29 59 PM" src="https://github.com/user-attachments/assets/706ce736-f15b-4b2a-8af4-852f861e0f1b" />

- Figure 2c: DTFT Magnitude Plot (m = 41)

<img width="799" height="519" alt="Screenshot 2026-06-21 at 1 31 05 PM" src="https://github.com/user-attachments/assets/b4ecf164-5e72-467b-917d-0fbf1630623d" />

- Figure 3c: DTFT Magnitude Plot (m = 101)
<img width="821" height="514" alt="Screenshot 2026-06-21 at 1 31 40 PM" src="https://github.com/user-attachments/assets/2217aaf4-3d5c-482c-a09a-de7d4bf5c2aa" />


---

## Results

### Effect of Window Length

#### m = 5

- Minimal smoothing
- Wide passband
- Preserves most signal content
- Limited noise attenuation

#### m = 41

- Moderate smoothing
- Improved noise rejection
- Sharper frequency response

#### m = 101

- Strong smoothing effect
- Significant high-frequency attenuation
- Narrowest passband
- Highest noise suppression

---

## Discussion

### Impulse Response Behavior

Increasing the window length resulted in:

- Wider impulse responses
- Greater averaging behavior
- Enhanced smoothing performance

### Pole-Zero Characteristics

As the window size increased:

- Additional zeros appeared near the unit circle
- Frequency selectivity improved
- High-frequency attenuation increased

### Frequency Response

The DTFT magnitude plots demonstrated that larger windows increasingly attenuated high-frequency components while preserving low-frequency breathing signals.

---

## Noise Frequency Estimation

Based on analysis of the DTFT magnitude responses:

- Physiological breathing information was concentrated below approximately **0.5 Hz**
- Noticeable attenuation began around **2 Hz**
- Frequencies above approximately **2 Hz** behaved as noise

Given a sampling frequency of approximately **18 Hz**, Nyquist frequency was computed from the sampling rate:

f_N = f_s / 2 = 9 Hz

From the DTFT magnitude response, most physiological breathing energy was concentrated below approximately 2 Hz. Frequencies above this range showed significantly reduced signal content and were treated as measurement noise.

Therefore, the effective noise band was estimated as:

2 Hz ≤ f ≤ 9 Hz

where 9 Hz represents the Nyquist limit of the sampled system.

The larger Savitzky-Golay windows effectively suppressed frequencies within this range while preserving the underlying breathing signal.

---

## MATLAB Concepts Demonstrated

- Matrix Algebra
- Least-Squares Estimation
- FIR Filter Design
- Transfer Function Construction
- Pole-Zero Analysis
- DTFT Computation
- Frequency Response Analysis
- Biomedical Signal Processing
- Data Visualization

---

## Files Included

| File | Description |
|--------|------------|
| `Savitzky_Golay_Filter_Analysis.m` | Main MATLAB script |
| `my_breathing_data_x4.txt` | Breathing signal dataset |
| `Figure1a.png` | Impulse Response (m = 5) |
| `Figure1b.png` | Pole-Zero Plot (m = 5) |
| `Figure1c.png` | DTFT Magnitude Response (m = 5) |
| `Figure2a.png` | Impulse Response (m = 41) |
| `Figure2b.png` | Pole-Zero Plot (m = 41) |
| `Figure2c.png` | DTFT Magnitude Response (m = 41) |
| `Figure3a.png` | Impulse Response (m = 101) |
| `Figure3b.png` | Pole-Zero Plot (m = 101) |
| `Figure3c.png` | DTFT Magnitude Response (m = 101) |

---

## Conclusion

This project explored the behavior of Savitzky-Golay filters through time-domain and frequency-domain analysis. By computing impulse responses, pole-zero locations, and DTFT magnitude responses for multiple window lengths, the relationship between filter size, smoothing performance, and noise suppression was clearly demonstrated. The techniques implemented in this project are directly applicable to biomedical signal processing applications including respiratory monitoring, pulse oximetry, ECG filtering, and physiological data analysis.
