%%
%2 main design specifications

[x, f_sample] = audioread('Problem4_FDM_audio_input.wav');
%echo the audio info from the song
my_audio_info = audioinfo('Problem4_FDM_audio_input.wav')

%passband limits
f_p = 5000;
f_2 = 8000;
f_sample = 44100;

%the gains of each band
passband_g = .9;
stopband_g = .01;

%solving for w_p and w_s
echo on
w_p = 2*pi*(f_p/f_sample)
w_s = 2*pi*(f_2/f_sample)
%%

%N and omega calculations
T_d = 1;
k = 2/T_d;
%solving for the omegas
echo on
omega_s = k*tan(w_s/2)
omega_p = k*tan(w_p/2)

%solving for N
N = ceil(log10( ((1/(stopband_g)^2) -1)/((1/(passband_g)^2)-1)) * (1/(2*log10(omega_s/omega_p))))

echo off

%solving for omega_n
syms omega_n
passband_eq = (1/passband_g)^2 == 1+((omega_p/omega_n))^(2*N)

omega_n = solve(passband_eq, omega_n, Real=true);

echo on
omega_n = double(max(omega_n))
echo off

Omega_range = linspace(0,3,1000);
%%

%solving for the gain adjusted H and solving for G
echo on

H = 1./ sqrt(1+(Omega_range./omega_n).^(2*N));

G = 1/max(H)
echo off

figure
plot(Omega_range, G*H, 'k', 'LineWidth', 2)
hold on

xline(omega_n, '--g', 'LineWidth', 2);
xline(omega_p, '--r', 'LineWidth', 2); 
xline(omega_s, '--b', 'LineWidth', 2);
yline(0.9, '--r', 'LineWidth', 2);
yline(0.01, '--b', 'LineWidth', 2);
yline(1/sqrt(2), '--g', 'LineWidth', 2);

plot(omega_p, passband_g, 'o', 'MarkerSize', 12, 'MarkerFaceColor', 'r','MarkerEdgeColor', 'k');
plot(omega_s, stopband_g, 'o', 'MarkerSize', 12, 'MarkerFaceColor', 'blue', 'MarkerEdgeColor', 'k');
plot(omega_n, 1/sqrt(2), 'o', 'MarkerSize', 12, 'MarkerFaceColor', 'g', 'MarkerEdgeColor', 'k')

hold off

title('Figure 1: Gain-adjusted, CTFT magnitude |H(\Omega)| plot, non-dB');
xlabel('\Omega (radians/sec)');
ylabel('|H(\Omega)|');
grid on;

legend('Filter', ['\Omega_n = ', num2str((omega_n), '%.4f')], ['\Omega_p = ', num2str(omega_p, '%.4f')],['\Omega_s = ', num2str(omega_s, '%.4f')]);
%%
%finding and plotting the poles

%setting a cell array of poles
poles = zeros(N, 1);
echo on
%finding the poles of H
for k = 0:N-1
    poles(k+1) = omega_n * exp(1i*(pi/2 + (2*k+1)*pi/(2*N)));
end
echo off


%plotting the poles with radius omega n
figure
theta = linspace(0, 2*pi, 1000);
c = plot(omega_n*(cos(theta)), omega_n*sin(theta));
set(c, 'Color', 'k', 'Linewidth', 2)
hold on

p_real = real(poles);
p_imag = imag(poles);
plot(p_real, p_imag, 'bx', 'MarkerSize', 12, 'LineWidth', 2);

%creating the 45 degree lines
lims = 1.2 * omega_n;
x_val = linspace(-lims, 0, 200);

plot(x_val, x_val, 'k--');  
plot(x_val, -x_val, 'k--'); 

xlim([-lims lims])
ylim([-lims lims])
axis square
grid on
hold off
title('Figure 2: Laplace Butterworth poles of H(s)')
xlabel('Real(s)')
ylabel('Imaginary(s)')
%%

%using the bilinear equation
K = 2; 
my_Zpoles = (1 + poles/K) ./ (1 - poles/K); 

H_prod = prod(K - poles);
H_real = real(1 / H_prod);

Hz_denom_poly = 1;
for count = 1:N
    pk_z = my_Zpoles(count); 
    Hz_denom_poly = conv(Hz_denom_poly, [1, -pk_z]);
end 

Hz_num_poly = 1;
for count = 1:N
    Hz_num_poly = conv(Hz_num_poly, [1, 1]);
end

echo on
my_poles = roots(Hz_denom_poly)
my_zeros = roots(Hz_num_poly)
echo off

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


title('Figure 3: Pole-zero plot of H(z)')
grid on
hold off
xlabel('Real(s)')
ylabel('Imaginary(s)')

N0 = length(x);
[hn, n] = impz(Hz_num_poly, Hz_denom_poly, N0);
hn = hn';



axis equal


%%
figure
stem(n,real(hn))
xlim([0 100])

title('Figure 4: h[n] = Butterworth low-pass filter (n-domain)')
xlabel('n')
ylabel('h[n]')


%%

K=2;
w = 0:0.001: 2*pi;
z = exp(1i*w);

Hw_denom_polynomial = ones(size(z));
 
for count = 1:1:N
    Hw_denom_polynomial = Hw_denom_polynomial .* (1-my_Zpoles(count).*z.^(-1));
end

Hw_num_polynomial = (1 + z.^(-1)).^N;

Hw = Hw_num_polynomial ./ Hw_denom_polynomial;

G = 1/max(abs(Hw));

Hw = G*Hw;

figure

subplot(2,1,1);
plot(w, abs(Hw), 'k', 'LineWidth', 2);
grid on;
hold on

grid on
title('DTFT magnitude and phase plots for H(e ^j^\omega)');
ylabel('|H(e^j^w|');
yline(0.9, 'r--', 'Passband 0.9')
yline(0.01, 'b--', 'Stopband 0.01')
xline(w_s, 'b--', 'w_s')
xline(w_p, 'r--', 'w_p')
xlim([0 2*pi]); 
ylim([0 1])

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
plot(w, 20*log10(abs(Hw)), 'b', 'LineWidth', 2);
grid on;
title('DTFT magnitude H(e^jw), dB mode (f-axis version)');
ylabel('dB');
ylim([-80 10]); 
xline(w_p, 'r--', 'w_p');
xline(w_s, 'k--', 'w_s');
yline(20*log10(0.9), 'r:', '-0.91 dB'); 
yline(20*log10(0.01), 'k:', '-40 dB'); 

%%



[qn, f_sample] = audioread('Problem4_FDM_audio_input.wav');
%echo the audio info from the song
my_audio_info = audioinfo('Problem4_FDM_audio_input.wav')
q_ch1 = qn(:,1)';
q_ch2 = qn(:,2)';

q_ch1_k = fft(q_ch1);
q_ch2_k = fft(q_ch2);

Hk = fft(hn);

Ych1_k = G*Hk .* q_ch1_k;
Ych2_k = G*Hk .* q_ch2_k;

ych1 = (ifft(Ych1_k));
ych2 = (ifft(Ych2_k));

yn_filtered = [real(ych1) real(ych2)];
audiowrite('FDM_lowpass_output.wav', yn_filtered, f_sample);


%%

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

num_slices = floor(length(ych1) / N0_1);

%creating soectrogram matrix
spectrogram_matrix = zeros(N0_1, num_slices);
for i = 1:num_slices
    idx_start = (i-1)*N0_1 + 1;
    idx_end = i*N0_1;

    y_slice = ych1(idx_start:idx_end);
    y_windowed = y_slice .* w_n;
    
    
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
title('Figure 7: Engineers DFT X[k] for FDM (in dB mode)')

axis([0 60 0 20E3]);
caxis([-80 20]);
%%

disp('To clean up the audio more, i would increase the stopband width. This makes sure any leaked freqeuincies from other channels are even quieter.')

disp('The new Butterworth filter design would have more poles. N would increase. The more poles means that the filter can go from passing the signal to blocking more noise.')
