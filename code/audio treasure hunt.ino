%%

%specs for filter
f_sample = 44100;
f_c = 10000;
f_p = 3000;
f_s = 3500;

passband_gain= 0.85;
stopband_gain = 0.01;
delta_one = 0.15;
squared_delta = 0.85^2;

echo on
E = sqrt((1/squared_delta)-1);
echo off


%solving for c_n
w_c = 2*pi*(f_c / f_sample);


%solving for the new w_p and w_s
w_p = 2*pi*f_p/f_sample;
w_s = 2*pi*f_s/f_sample;

echo on
%solving for omega_p and omega_s
omega_s = K*tan(w_s/2);
omega_p = K*tan(w_p/2);
echo off

%finding the x domain
omega = linspace(0,2*omega_s,1000);
x = omega/omega_p;
%%


%plotting the H ideal for the new filter
N = 10;

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

title('Figure 1: Laplace low-pass design of H(\Omega)')
xlabel('\Omega')
ylabel('|H_i_d_e_a_l(\Omega)|')
hold off
grid on

xlim([0 1.2])
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
title(['Figure 2: Laplace pole-zero diagram, low pass H(z),  (N = ', num2str(N), ')'])
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
title('Figure 3: Pole-zero plot of the low-pass H(z)')
grid on
hold off
xlabel('Real(s)')
ylabel('Imaginary(s)')

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
plot(w, abs(Hw), 'k', 'LineWidth', 2);
grid on;
hold on

grid on
title('Figure 4: Low-pass design H(e ^j^\omega)');
ylabel('|H(e^j^w|');
yline(0.85, 'r--', 'Passband 0.85')
yline(0.01, 'b--', 'Stopband 0.01')
xline(w_s, 'b--', '\Omega_s')
xline(w_p, 'r--', '\Omega_p')
yline(1, '--k','upper limit');


xlim([0 2*pi]); 
ylim([-0.2 1.2])
%%


%setting up parameters
f_c = 10000;
w_c = 2*pi*f_c/f_sample;

[x, f_sample] = audioread('Problem2_FDM_audio_input.wav');
N0 = length(x);

[hn, n] = impz(Hz_num_poly, Hz_denom_poly, N0);


c_n = cos(w_c*n);

%multiply by two for the gain
h_bp_n = 2*hn.*c_n;

%%

%setting the w bounds
w =  0:0.001: 2*pi;

%the new h_bp
h_bp_w = zeros(size(w));

%calculating the DTFT equation
for k = 1:length(w)
    h_bp_w(k) = sum(h_bp_n(1:10001) .* exp(-1i*w(k) * (0:10000)'));
end

%normalizing it
G_final = 1 / max(abs(h_bp_w));
H_bp_w_norm = h_bp_w * G_final;

figure;
subplot(2,1,1)
plot(w, abs(H_bp_w_norm), 'k', 'LineWidth', 1);
grid on;
title('Figure 5: Chebyshev bandpass design H(e ^j^\omega)');
ylabel('|H_{bp}|');
xlabel('\omega (rad/sample)');

yline(1-delta_one, 'r--', '1-\delta_1')
yline(0.01, 'b--', 'Stopband 0.01')
xline(w_c+w_p, 'r--', '\omega_p + \omega_c')
xline(w_c+w_s, 'b--', '\omega_s + \omega_c')
yline(1, '--k','upper limit');

xlim([0 2*pi])
ylim([0 1.2])

subplot(2,1,2)
plot(w, rad2deg(angle(H_bp_w_norm)), 'r');
grid on;
ylabel('Phase (deg)');
xlabel('\omega (rad/sample)');
%%

% Magnitude (dB)
figure
fsample = 44100;
freq_hz = (w / (2*pi)) * fsample;
plot(freq_hz, 20*log10(abs(H_bp_w_norm)), 'k', 'LineWidth', 2);
grid on;
title('Figure 6: DTFT magnitude H(e^jw), dB mode (f-axis version)');
ylabel('dB');
xlabel('f(Hz)');
ylim([-80 10]); 
xlim([0 0.5*fsample])

%convert to frequency
xline(f_c+f_p, 'r--', 'LineWidth', 2);
xline(f_c+f_s, 'b--','LineWidth', 2);
xline(f_c-f_p, 'r--','LineWidth', 2);
xline(f_c-f_s, 'b--','LineWidth', 2);
yline(20*log10(0.85), 'r:','LineWidth', 2); 
yline(20*log10(0.01), 'b:','LineWidth', 2); 


legend('Filter', 'f_c + f_p', 'f_c + f_s')
%%

[qn, f_sample] = audioread('Problem2_FDM_audio_input.wav');
my_audio_info = audioinfo('Problem2_FDM_audio_input.wav')
x_FDM_1_n = qn(:,1);
x_FDM_2_n = qn(:,2);

L = length(x_FDM_1_n);
Hk = fft(h_bp_n, L);

fft_FDM1 = fft(x_FDM_1_n);
fft_FDM2 = fft(x_FDM_2_n);


Ych1_k = Hk(:) .* fft_FDM1(:);
Ych2_k = Hk(:) .* fft_FDM2(:);

xbp1 = real(ifft(Ych1_k));
xbp2 = real(ifft(Ych2_k));


n_vec = (0:L-1)'; 
w_c = 2*pi*10000/f_sample;
c_n = cos(w_c * n_vec);

xdem1 = xbp1(:) .* c_n;
xdem2 = xbp2(:) .* c_n;

Hk_lp = fft(hn, L); 

xlow1 = real(ifft(Hk_lp(:) .* fft(xdem1)));
xlow2 = real(ifft(Hk_lp(:) .* fft(xdem2)));

combined_data = [xlow1(:); xlow2(:)];
G_final = 1 / max(abs(combined_data));


y_ch1 = G_final * xlow1(:);
y_ch2 = G_final * xlow2(:);

yn_filtered = [ y_ch1, y_ch2 ];

audiowrite('Mystery_audio2_output.wav', yn_filtered, f_sample);
%%

 disp('The mystery song is the pokemon theme song')


 %ploting the output spectro in dB of XK

f_0 = 10;
T_slice = 1/f_0;
N0_1 = T_slice * f_sample;

%hamming window
scale = 0.4 * N0_1;
hfrag = hamming(scale);
left_h = hfrag(1:length(hfrag)/2).';
right_h = hfrag((length(hfrag)/2)+1:end).';
rec_center = ones(1, N0_1 - length(hfrag));
w_n = [left_h rec_center right_h];

num_slices = floor(length(y_ch1) / N0_1);

%creating soectrogram matrix
spectrogram_matrix = zeros(N0_1, num_slices);
for i = 1:num_slices
    idx_start = (i-1)*N0_1 + 1;
    idx_end = i*N0_1;

    y_slice = y_ch1(idx_start:idx_end);
    y_windowed = y_slice(:) .* w_n(:);
    
    
    Y_k_= fft(y_windowed);
    spectrogram_matrix(:, i) = fft(y_windowed).';
end

S_db = 20*log10(abs(spectrogram_matrix));

t_axis = (0:num_slices-1) * T_slice;
f_axis = (0:N0_1-1) * f_0; 


figure
pcolor(t_axis, f_axis, S_db, 'EdgeColor', 'none');
colorbar

xlabel('Time (s)')
ylabel('Frequency (Hz)')
title('Spectrogram for Mystery Sound')

axis([0 60 0 12E3]);
caxis([-80 20]);
