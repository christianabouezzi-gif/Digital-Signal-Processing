clear all 
close all
%x axis plotting vector
x = -1.2:0.01:1.2;

%using chebyshevT to plot T2(x), T3, T6 with N = 2, 3, 6

nums = [2 3 6];
figure
for i = 1:length(nums)
    cheb = chebyshevT(nums(i), x);
    plot(x, cheb, 'LineWidth', 2);
    hold on;
end
hold off;
grid on;
title("Figure 1: Warm-up plot for Chebyshev polynomials");
xlim([-1.2 1.2]);
ylim([-1.2 1.2]);
legend('T_2(x)', 'T_3(x)', 'T_6(x)');
xlabel('X');
ylabel('Amplitude');
%%


%Guess a number for the # of poles in the filter
N = 4;



%Calculte the e value for H ideal 

passband_gain= 0.85;
stopband_gain = 0.01;
delta_one = 0.15;
squared_delta = 0.85^2;

echo on
E = sqrt((1/squared_delta)-1);
echo off

%%
%using bilinear transformation, convert n domain/DTFT into Laplace/CTFT

K = 2;

%z-domain/DTFT passband and stop band value
w_p = 0.1*pi;
w_s = 0.16*pi;

echo on
%solving for omega_p and omega_s
omega_s = K*tan(w_s/2);
omega_p = K*tan(w_p/2);
echo off

%finding the x domain
omega = linspace(0,2*omega_s,1000);
x = omega/omega_p;

%solving H ideal
H_ideal = abs((1)./(sqrt(1+E^2*(chebyshevT(N, x)).^2)));

%plottign dashed lines and plotting H_ideal
figure
plot(omega, H_ideal)
hold on
xline(omega_p, '--r', 'wp');
yline(stopband_gain, '--b', '\delta_2');
xline(omega_s, '--b', 'ws');
yline(passband_gain, '--k', '1-\delta_1');
yline(1, '--k','upper limit');

plot(omega_p, 1 - delta_one, 'ro', 'MarkerFaceColor', 'r', 'MarkerSize', 8);
plot(omega_s, stopband_gain, 'bo', 'MarkerFaceColor', 'b', 'MarkerSize', 8);
plot(omega_s, 0.0458, 'ko', 'MarkerFaceColor', 'w', 'MarkerSize', 8);

title('Figure 2: Theoretical, ideal Chebyshev design in Laplace')
xlabel('\Omega')
ylabel('|H_i_d_e_a_l(\Omega)|')
hold off
grid on

xlim([0 2])
ylim([0 1.2])
%%

%repeating step 4B with different N value
echo on
N = 6;
E;
omega_p;
omega_s;
echo off

H_ideal = abs((1)./(sqrt(1+E^2*(chebyshevT(N, x)).^2)));

%plottign dashed lines and plotting H_ideal
figure
plot(omega, H_ideal)
hold on
xline(omega_p, '--r', 'wp');
yline(stopband_gain, '--b', '\delta_2');
xline(omega_s, '--b', 'ws');
yline(passband_gain, '--k', '1-\delta_1');
yline(1, '--k','upper limit');

plot(omega_p, 1 - delta_one, 'ro', 'MarkerFaceColor', 'r', 'MarkerSize', 8);
plot(omega_s, stopband_gain, 'bo', 'MarkerFaceColor', 'b', 'MarkerSize', 8);
plot(omega_s, 1 / sqrt(1 + E^2 * (chebyshevT(N, omega_s/omega_p))^2), 'ko', 'MarkerFaceColor', 'w', 'MarkerSize', 8);

title('Figure 2: Theoretical, ideal Chebyshev design in Laplace')
xlabel('\Omega')
ylabel('|H_i_d_e_a_l(\Omega)|')
hold off
grid on

xlim([0 2])
ylim([-.2 1.2])
%%

%calculating beta
beta = ((sqrt(1+E^2)+1)/E)^(1/N);

%calculating r1 and r2
r1 = omega_p * ((beta^2 + 1)/(2*beta));
r2 = omega_p * ((beta^2 - 1)/(2*beta));

%calculating phi_k, and x y coord of poles, and finding the exactl
%locations
Poles = zeros(N,1);
phi_k = zeros(N,1);
x_k = zeros(N,1);
y_k = zeros(N,1);
for k = 0:N-1
    phi_k(k+1) = pi/2 + ((2*k+1)*pi)/(2*N);
    x_k(k+1) = r2 * cos(phi_k(k+1));
    y_k(k+1) = r1 * sin(phi_k(k+1));
    Poles(k+1) = x_k(k+1) + j*y_k(k+1);
end

echo on
Poles;
echo off


%polting the poles 
figure
theta = linspace(0, 2*pi, 1000);
c = plot(omega_p*(cos(theta)), omega_p*sin(theta));
set(c, 'Color', 'k', 'Linewidth', 2)
hold on

p_real = real(Poles);
p_imag = imag(Poles);
plot(p_real, p_imag, 'bx', 'MarkerSize', 12, 'LineWidth', 2);
grid on 
hold off
axis equal
title(['Figure 3: Chebysehv poles (N = ', num2str(N), ') in the Lapalce domain'])
xlabel('Real(s)')
ylabel('Imaginary(s)')
%%

%calculating H of s from omega_n
omega_n = omega_p/((1/passband_gain^2-1)^(1/(2^N)));
H_s = 1./ sqrt(1+(omega_n./omega_p).^(2*N));

%finding the gain of H to normalize it to one
echo on
G = 1/max(H_s);
echo off
%%

%setting up the bilinear transormation equation
K = 2; 
my_Zpoles = (1 + Poles/K) ./ (1 - Poles/K); 
Hz_denom_poly = 1;

%setting up thedenominator
for count = 1:N
    pk_z = my_Zpoles(count); 
    Hz_denom_poly = conv(Hz_denom_poly, [1, -pk_z]);
end 

%setting up the numerator
Hz_num_poly = 1;
for count = 1:N
    Hz_num_poly = conv(Hz_num_poly, [1, 1]);
end

%fidning the poles and zeros
echo on
my_poles = roots(Hz_denom_poly);
my_zeros = roots(Hz_num_poly);
echo off

%ploting the poles and zeros on a cricle
figure
theta = linspace(0, 2*pi);
c = plot((cos(theta)), sin(theta));
set(c, 'Color', 'k', 'Linewidth', 2)
hold on
for i = 1:length(my_poles)
    p_real = real(my_poles);
    p_imag = imag(my_poles);
    p = plot(p_real(i), p_imag(i));
    set(p, 'marker', 'x', 'Color', 'blue', 'MarkerSize', 10, 'Linewidth', 2);
end


for i = 1:length(my_zeros)
    z_real = real(my_zeros);
    z_imag = imag(my_zeros);
    z = plot(z_real(i), z_imag(i));
    set(z, 'marker', 'o', 'Color', 'red', 'MarkerSize', 10, 'Linewidth', 2);
end

axis equal
grid on
title('Figure 4: Pole-zero plot of H(z)')
grid on
hold off
xlabel('Real(s)')
ylabel('Imaginary(s)')
%%

%plotting the impulse response h[n]
N0 = 100;
[hn, n] = impz(Hz_num_poly, Hz_denom_poly, N0);
hn = hn';

figure
stem(n,real(hn))
xlim([0 100])

title('Figure 5: h[n] = Chebyshev low-pass filter (n-domain)')
xlabel('n')
ylabel('h[n]')
%%

%setting up the z and x axis
K=2;
w = 0:0.001: 2*pi;
z = exp(1i*w);

%finding the hw denomiator
Hw_denom_polynomial = ones(size(z));
 
for count = 1:1:N
    Hw_denom_polynomial = Hw_denom_polynomial .* (1-my_Zpoles(count).*z.^(-1));
end

%setting up the Hw numerator
Hw_num_polynomial = (1 + z.^(-1)).^N;

Hw = Hw_num_polynomial ./ Hw_denom_polynomial;

%fniding the gain and nromalzie hw
G = 1/max(abs(Hw));

Hw = G*Hw;

%ploting the DTFT design of H(e^jw) as well as the phase plot
figure
subplot(2,1,1);
plot(w, abs(Hw), 'k', 'LineWidth', 2);
grid on;
hold on

grid on
title('Figure 6: DTFT magnitude and phase shift for H(e ^j^\omega)');
ylabel('|H(e^j^w|');
yline(0.85, 'r--', 'Passband 0.85')
yline(0.01, 'b--', 'Stopband 0.01')
xline(w_s, 'b--', '\Omega_s')
xline(w_p, 'r--', '\Omega_p')
yline(1, '--k','upper limit');


xlim([0 2*pi]); 
ylim([-0.2 1.2])

%Phase Shift
subplot(2,1,2);
plot(w,rad2deg(angle(Hw)), 'r', 'LineWidth', 2);
grid on;
ylabel('|angle(H(e^j^w))|');
xlabel('\omega (DFT domain)');
xlim([0 2*pi]);
%%

% Magnitude (dB)
figure
fsample = 44100;
freq_hz = (w / (2*pi)) * fsample;
plot(freq_hz, 20*log10(abs(Hw)), 'k', 'LineWidth', 2);
grid on;
title('Figure 7: DTFT magnitude H(e^jw), dB mode (f-axis version)');
ylabel('dB');
xlabel('f(Hz)');
ylim([-80 5]); 
xlim([0 10000])

%convert to frequency
f_p = (w_p / (2*pi)) * fsample; 
f_s = (w_s / (2*pi)) * fsample; 
xline(f_p, 'r--');
xline(f_s, 'b--');
yline(20*log10(0.85), 'r:'); 
yline(20*log10(0.01), 'b:'); 

legend('Filter', ['f_p =', num2str(f_p)], ['f_s =', num2str(f_s)])
%%
