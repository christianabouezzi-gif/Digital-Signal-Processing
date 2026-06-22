%%


%the 1/2 bandwidth spacing
phi = 15;
%total number of zeros for the comb
m = 360/phi;


%Defining the comb's H1(z)
H1z_numerator = [ 1 zeros(1,m-1) -1];
H1z_denominator =  [ 1 ];


%coding the 2 poles of the resonant filter
w_pass = (pi/3);
p1 = 1 * exp(1i * w_pass);
p2 = 1 * exp(-1i * w_pass);


%defining the resonator's H2(z)
H2z_numerator = [1];
H2z_denominator = [1 -(p1+p2) (p1*p2)];


%defining the overall filter H(z)
Hz_numerator = conv(H1z_numerator, H2z_numerator);
Hz_denominator = conv(H1z_denominator,H2z_denominator);


%Find poles and zeros of H(z)
my_zeros = roots(Hz_numerator);
my_poles = roots(Hz_denominator);




figure
%creating our circle to graphnon
theta = linspace(0, 2*pi);
c = plot(cos(theta), sin(theta));
set(c, 'Color', 'k', 'Linewidth', 2)
hold on

%plotting poles and zeros
p = plot(real(my_poles), imag(my_poles));
set(p, 'marker', 'x', 'Color', 'blue', 'MarkerSize', 10, 'Linewidth', 2, 'LineStyle', 'none');

z = plot(real(my_zeros), imag(my_zeros));
set(z, 'marker', 'o', 'Color', 'red', 'MarkerSize', 15, 'Linewidth', 2, 'LineStyle', 'none');

xlim([-1.3 1.3]);
ylim([-1.3 1.3]);
axis square
grid on
hold off
title('Pole-zero plot of H(z)')
xlabel('Real(z)')
ylabel('Imagnary(z)')

%%
%inputs
fsample = 24;
N0 = 72;
T0 = 3;
f0 = 1/T0;
%input
w0 = 2*pi/N0;

%n domain and time domain
w=0:0.01:2*pi;
f = fsample/2;


%computing the filter impulse response h[n], with length N0
[h, n] = impz(Hz_numerator, Hz_denominator, N0);


%ploting the impusle response to see if we did it right
figure
stem(n, h, 'LineWidth', 2);
xlabel('n (samples)');
ylabel('Amplitude');
title('Impulse Response h[n]');
grid on;
title('Figure 1: h[n] for our total filter')
%%

%getting the DFT of our h[n]
H_k = fft(h);


z = exp(j*w);
m = 24;
numerator = (1-z.^(-m));
denominator = 1./(1-(p1+p2).*z.^(-1) + (p1.*p2).*z.^(-2));
H_ej = numerator.*denominator;

%plotting the dtft
figure

Hw_magplothandle = plot(w, abs(H_ej));
set(Hw_magplothandle, 'Color', 'blue', 'Linewidth', 2);
hold on

%plotting the stem plot onto the dtft
k = 0:N0-1;
w_k = (2*pi*k)/N0;
stem(w_k, abs(H_k), 'Color', 'red', 'MarkerSize', 8);

hold off

xlabel('\omega (n-domain)')
ylabel('|H(e^j^\omega)|')
xlim([0 2*pi]);
ylim([0 15]);

grid on
legend('|H(e^j^w)|', 'h[n]');
title('The DFTF |H(e^j^w)| for the bandpass filter')

%%

%finding gain 
echo on
G = 1/(abs(max(H_k)));
echo off

%%
z = exp(j*w);
m = 24;
numerator = (1-z.^(-m));
denominator = 1./(1-(p1+p2).*z.^(-1) + (p1.*p2).*z.^(-2));
H_ej = numerator.*denominator;

H_ej_adjusted = H_ej * G;

H_k_adjusted = H_k *G;

%%


figure
Hw_magplothandle = plot(w, abs(H_ej_adjusted));
set(Hw_magplothandle, 'Color', 'blue', 'Linewidth', 2);
hold on

title('Figure 3: The DFTF |H(e^j^w)| for the bandpass filter adjusted with gain')

%plotting the stem plot onto the dtft
k = 0:N0-1;
w_k = (2*pi*k)/N0;
stem(w_k, abs(H_k_adjusted), 'Color', 'red', 'MarkerSize', 8);
xlabel('\omega (n-domain)');
ylabel('|H(e^j^\omega)|');
xlim([0 2*pi]);
ylim([0 1]);
legend('|H(e^j^w)|', 'h[n]');
grid on
hold off
