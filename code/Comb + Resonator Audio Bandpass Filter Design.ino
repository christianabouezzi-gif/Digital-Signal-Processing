%%
%load the song

[x, f_sample] = audioread('mac_farm copy.wav');
%echo the audio info from the song
my_audio_info = audioinfo('mac_farm copy.wav')


f_0 = 10;

T_slice = 1/f_0;

N0_1 = T_slice * f_sample;

N0_total = length(x);

%hamming window
scale = 0.4*N0_1;
hfrag = hamming(scale);
left_h = hfrag(1:(length(hfrag)/2)).';
right_h = hfrag((length(hfrag)/2)+1:end).';
rec_center = ones(1,2646);
w_n = [left_h rec_center right_h];

%creating soectrogram matrix
spectrogram_matrix = zeros(N0_1, floor(N0_total/N0_1));
for i = 1:floor(N0_total/N0_1)
    idx_start = (i-1)*N0_1 + 1;
    idx_end = i*N0_1;
   
    x_n = x(idx_start : idx_end);

    q_n = x_n' .* w_n;

    Q_k = fft(q_n);

    spectrogram_matrix(:, i) = (Q_k);
end

%convert to db
S_db = 20*log10(abs(spectrogram_matrix));

f_axis = (0:N0_1-1)*(f_sample/N0_1);
t_axis = (0:floor(N0_total/N0_1)-1)*T_slice;

figure
pcolor(t_axis, f_axis, S_db);
colorbar;

xlabel('t (seconds)');
ylabel('f(Hz)');
title('Engineers DFT X[k] for Old MacDonald (in dB mode)');


ylim([0 700]);


caxis([-100 80]); 
%%
%filter specifications for this problem
%fpass
f_pass = 400;
f_side = 50;
fsmaple = 44100;
T_0 = 6.5;
N_0 = length(x);
f_0 = 1/T_0;
w_pass = 2*pi*(f_pass/f_sample);
phi = 2*pi*(f_side/f_sample);
%%

%what is N0
echo on
N_0 = length(x)
%the fundamental mode w_0
w_0 = 2*pi/N_0
%%

%m value needed for number of zeros
m = f_sample/50
%finding w_pass
w_pass = 2*pi*(f_pass/f_sample)
%finding locations of the two poles
p1 = 1 * exp(1i * w_pass)
p2 = 1 * exp(-1i * w_pass)
echo off

%%

%the H(ejw equation)
w=0:0.001:2*pi;
z = exp(j*w);
numerator = (1-z.^(-m));
denominator = 1./(1-(p1+p2)*z.^(-1) + (p1.*p2)*z.^(-2));

%creating h
H1z_numerator = [ 1 zeros(1,m-1) -1];
H1z_denominator =  [ 1 ];
H2z_numerator = [1];
H2z_denominator = [1 -(p1+p2) (p1*p2)];

%defining the overall filter H(z)
Hz_numerator = conv(H1z_numerator, H2z_numerator);
Hz_denominator = conv(H1z_denominator,H2z_denominator);

[h, n] = impz(Hz_numerator, Hz_denominator, N_0);

%finding the H_ej
H_ej = numerator.*denominator;

%getting H_k
H_k = fft(h);

echo on
%finding the gain
G = 1/(abs(max(H_k)))
echo off

%%

%plotting the gain adjusted magnitude of the bandpass filter design

H_ej_adjusted = H_ej * G;

H_k_adjusted = H_k *G;

w=0:0.001:2*pi;
f_axis = w*(f_sample/(2*pi));
figure
Hw_magplothandle = plot(f_axis, abs(H_ej_adjusted));
set(Hw_magplothandle, 'Color', 'blue', 'Linewidth', 2);


title('Figure 2: Gain-adjusted bandpass filter');
grid on 
xlim([0, f_sample]);
ylim([0,1]);
ylabel('| H(e^jw)|');
xlabel('f (Hz)');
%%


%plotting the dB mode of the gain adjusted magnitude of the bandpass filter
%design
h_ej_db = 20*log10(abs(H_ej_adjusted));
w=0:0.001:2*pi;
f_axis = w*(f_sample/(2*pi));
figure
Hw_magplothandle = plot(f_axis, h_ej_db);
set(Hw_magplothandle, 'Color', 'blue', 'Linewidth', 2);


title('Figure 3: Gain-adjusted bandpass filter (dB, f = 1000 Hz max)');
grid on 
xlim([0, 1000]);
ylim([-80,20]);
ylabel('20 log | H(e^jw)|');
xlabel('f (Hz)');
%%

%Ussing fft to calculate the engineer DFT coeff fo reach n domain input
x_k = fft(x);
%%

%use impaz to find imulsle response of gain adjusted filter Hz, then use
%fft to get H_k

m = f_sample/50;

%Defining the comb's H1(z)
H1z_numerator = [ 1 zeros(1,m-1) -1];
H1z_denominator =  [ 1 ];

%coding the 2 poles of the resonant filter
w_pass = 2 * pi * (400 / f_sample);
p1 = 1 * exp(1i * w_pass);
p2 = 1 * exp(-1i * w_pass);

%defining the resonator's H2(z)
H2z_numerator = [1];
H2z_denominator = [1 -(p1+p2) (p1*p2)];

%defining the overall filter H(z)
Hz_numerator = conv(H1z_numerator, H2z_numerator);
Hz_denominator = conv(H1z_denominator,H2z_denominator);

[h, n] = impz(Hz_numerator.*G, Hz_denominator, N_0);

H_k = fft(h);
%%

%getting the outpt DFT using direct multiplication

Y_k = H_k .* x_k;

%converting Y_k into n domain for plotting
Y_n = real(ifft(Y_k));

%%

%ploting x_n and y_n

figure
n2 = 0:N_0-1;
stem(n2, x, 'Color', 'red');
hold on
stem(n2, (Y_n), 'Color', 'blue');
title('Figure 3: The input x[n] and filtered output y[n]');
xlabel('n');
ylabel('Amplitude');
legend('x[n]', 'y[n]');
ylim([-1.1, 1.1]);
grid on;
%%

%ploting the output spectro in dB of XK
f_0 = 10;

T_slice = 1/f_0;

N0_1 = T_slice * f_sample;

N0_total = length(Y_n);

%hamming window
scale = 0.4*N0_1;
hfrag = hamming(scale);
left_h = hfrag(1:(length(hfrag)/2)).';
right_h = hfrag((length(hfrag)/2)+1:end).';
rec_center = ones(1,2646);
w_n = [left_h rec_center right_h];

%creating soectrogram matrix
spectrogram_matrix = zeros(N0_1, floor(N0_total/N0_1));
for i = 1:floor(N0_total/N0_1)
    idx_start = (i-1)*N0_1 + 1;
    idx_end = i*N0_1;
   
    y_slice = Y_n(idx_start : idx_end);
    
    y_windowed = y_slice .* w_n'; 
    
    
    Y_k_= fft(y_windowed);
    spectrogram_matrix(:, i) = Y_k_;
end

%convert to db
S_db = 20*log10(abs(spectrogram_matrix));

f_axis = (0:N0_1-1).*(f_sample/N0_1);
t_axis = (0:floor(N0_total/N0_1)-1).*T_slice;

figure
pcolor(t_axis, f_axis, S_db);
colorbar;

xlabel('t (seconds)');
ylabel('f(Hz)');
title('Figure 4: Comb + resonator-filtered output spectrogram (db mode)');


ylim([0 700]);


caxis([-100 80]); 
%%
audiowrite('Mac_comb_resonator_filtered.wav', Y_n, f_sample)

disp("I was able to hear the G4 notes very clearly, but the E4 and D4 sounded a lot lighter. I did see a significant drop in amplitude, but the notes that are about -30 dB are still audible, even though it is quieter.")

disp("The sidebands we see are at about -20 to -40 dbs, outside the main peak. THey are enough to show filtering, where in the spectrograam, those freqeuncies turn blue. -30 dB is not enough to completely remeove a sound, to remove it, we would need to attenuate at aout -60dB.")
%%
