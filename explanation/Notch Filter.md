# Notch Filter Design and Frequency Domain Analysis

## Christian Abou-Ezzi

---

# Project Overview

This project investigated the frequency-domain behavior of digital filters through DTFT analysis, transfer function modeling, pole-zero characterization, and impulse response evaluation. MATLAB was used to analyze three filter systems:

* A second-order two-pole IIR filter
* A three-point moving-average (3-MA) FIR filter
* A combined notch filter formed by cascading the previous two systems

For each filter, the Discrete-Time Fourier Transform (DTFT) magnitude and phase responses were computed and visualized. Transfer functions were implemented using MATLAB's Control System Toolbox, and impulse responses were generated to evaluate time-domain behavior.

---

# Objectives

* Compute DTFT magnitude and phase responses.
* Visualize frequency response using dual frequency axes.
* Construct transfer functions from pole-zero descriptions.
* Generate impulse responses.
* Classify filters based on frequency characteristics.
* Compare FIR and IIR filter behavior.
* Design a notch filter through filter cascading.

---

# Methodology

## Part B: Two-Pole IIR Filter

### DTFT Construction

The transfer function was evaluated directly on the unit circle:

H(e^jω) = e^(j2ω) / (e^(j2ω) + 0.9e^(jω) + 0.81)

The DTFT was computed over:

```matlab
w = -pi:0.01:pi;
```

The frequency axis was converted into physical frequency units:

```matlab
f = (w/pi)*(0.5*fsample);
```

where:

fs = 3 Hz

---

### Figure 1: DTFT Magnitude and Phase Response

INSERT IMAGE HERE

```md
![Figure 1](figures/Figure1.png)
```

The top subplot displays the DTFT magnitude response while the lower subplot shows the phase response.

---

### Transfer Function Analysis

The filter transfer function was implemented as:

```matlab
H1 = tf([1 0 0],[1 0.9 0.81],T_sample);
```

Pole locations were extracted using:

```matlab
pole(H_cleaned)
```

and zeros using:

```matlab
zero(H_cleaned)
```

---

### Figure 2: Impulse Response

INSERT IMAGE HERE

```md
![Figure 2](figures/Figure2.png)
```

The impulse response was generated using:

```matlab
impulse(H_cleaned)
```

### Interpretation

The frequency response attenuates low frequencies while allowing higher frequencies to pass.

Therefore:

**Filter Classification:** High-Pass Filter

---

# Part C: Three-Point Moving Average Filter

## DTFT Construction

The moving-average filter was represented by:

[
H(e^{j\omega})
==============

H(e^jω) = (e^(j2ω) + e^(jω) + 1) / e^(j2ω)
]

This structure contains two zeros on the unit circle and exhibits finite impulse response behavior.

---

### Figure 3: DTFT Magnitude and Phase Response

INSERT IMAGE HERE

```md
![Figure 3](figures/Figure3.png)
```

The magnitude response shows strong attenuation at higher frequencies while preserving low-frequency components.

---

### Transfer Function Analysis

The filter was implemented as:

```matlab
H1 = tf([1 1 1],[1 0 0],T_sample);
```

Because the denominator contains no feedback terms, the system is FIR.

---

### Figure 4: Impulse Response

INSERT IMAGE HERE

```md
![Figure 4](figures/Figure4.png)
```

### Interpretation

The moving-average filter smooths neighboring samples and suppresses rapid signal variations.

Therefore:

**Filter Classification:** Low-Pass Filter

---

# Part D: Notch Filter Design

## Filter Construction

The notch filter was created by combining the moving-average filter with the two-pole filter.

The resulting DTFT becomes:

[
H(e^{j\omega})
==============

H(e^jω) = (e^(j2ω) + e^(jω) + 1) /
          (e^(j2ω) + 0.9e^(jω) + 0.81)
]

This structure combines:

* FIR zero locations from the moving-average filter
* IIR pole locations from the two-pole filter

---

### Figure 5: DTFT Magnitude and Phase Response

INSERT IMAGE HERE

```md
![Figure 5](figures/Figure5.png)
```

Distinct frequency rejection regions appear where zeros and poles interact.

---

### Transfer Function Analysis

The notch filter transfer function was implemented as:

```matlab
H1 = tf([1 1 1],[1 0.9 0.81],T_sample);
```

Pole and zero locations were extracted and compared against previous filter designs.

---

### Figure 6: Impulse Response

INSERT IMAGE HERE

```md
![Figure 6](figures/Figure6.png)
```

The impulse response demonstrates the combined FIR/IIR characteristics of the notch filter.

---

# Results Summary

| Filter          | Classification |
| --------------- | -------------- |
| Two-Pole Filter | High-Pass      |
| 3-MA Filter     | Low-Pass       |
| Combined Filter | Notch Filter   |

---

# Discussion

## Frequency Response Behavior

The two-pole filter exhibited high-pass behavior due to its pole configuration.

The moving-average filter produced low-pass behavior through frequency averaging.

When combined, the resulting notch filter selectively rejected frequencies near the notch location while preserving frequencies outside the rejection band.

---

## Pole-Zero Interpretation

The notch filter demonstrates a fundamental DSP design principle:

* Zeros create attenuation.
* Poles increase selectivity.
* Combining poles and zeros allows targeted frequency suppression.

This principle is widely used in biomedical signal processing applications including:

* Power-line interference removal
* ECG filtering
* EEG artifact suppression
* Respiratory signal processing

---

# MATLAB Concepts Demonstrated

* DTFT Computation
* Frequency Response Analysis
* Phase Response Analysis
* Pole-Zero Analysis
* FIR Filter Design
* IIR Filter Design
* Transfer Functions
* Impulse Response Analysis
* Notch Filter Design
* Biomedical Signal Processing

---

# Files Included

| File                    | Description                              |
| ----------------------- | ---------------------------------------- |
| Notch_Filter_Analysis.m | Main MATLAB script                       |                 |
| Figure1.png             | DTFT Magnitude and Phase (2-Pole Filter) |
| Figure2.png             | Impulse Response (2-Pole Filter)         |
| Figure3.png             | DTFT Magnitude and Phase (3-MA Filter)   |
| Figure4.png             | Impulse Response (3-MA Filter)           |
| Figure5.png             | DTFT Magnitude and Phase (Notch Filter)  |
| Figure6.png             | Impulse Response (Notch Filter)          |

---

# Conclusion

This project explored the relationship between poles, zeros, impulse responses, and frequency-domain behavior in digital filters. Through analysis of a two-pole IIR filter, a three-point moving-average FIR filter, and a cascaded notch filter, the connection between filter structure and frequency selectivity was demonstrated. The resulting notch filter provided targeted frequency suppression and illustrates a common DSP strategy used in biomedical signal processing systems.
