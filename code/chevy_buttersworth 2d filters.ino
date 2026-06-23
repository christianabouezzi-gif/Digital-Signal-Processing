
%%
w_noise = [-0.125*pi; 0.125*pi];

%%
%hard coing 2D butterworth filter H[wm wn]

%N and omega calculations
T_d = 1;
k = 2/T_d;

wpassband_edge = 0.12*pi;
wstopband_edge = 0.20*pi;
passgain = 0.85;
stopgain = 0.01;

%solving for the omegas
omega_s = k*tan(wstopband_edge/2);
omega_p = k*tan(wpassband_edge/2);

%number of poles in butterworth
N = ceil(log10( ((1/(stopgain)^2) -1)/((1/(passgain)^2)-1)) * (1/(2*log10(omega_s/omega_p))));

syms omega_n
passband_eq = (1/passgain)^2 == 1+((omega_p/omega_n))^(2*N);

omega_n = solve(passband_eq, omega_n, Real=true);
omega_n = double(max(omega_n));

wp = 2*atan(omega_n/2);


%define fundamental spatial frequency
N0 = 512;
wn0 = 2*pi/N0;
wm0 = wn0;

%Define wm and wn axes
wn = [0:1:N0-1]*wn0;
wm = [0:1:N0-1]*wm0;

%subtract pi from both wn and wm to get unwrapped version
wn = wn-pi;
wm = wm-pi;

%generate 2D meshgrid
[WN,WM] = meshgrid(wn,wm);

%defining radius W on wm,wn plane with respect of 0 0 as center
W = sqrt(WM.^2 +WN.^2);

%coding the 2D butterworth filter
my_data(1).Hw = 0;

my_data(1).Hw = 1./sqrt(1+(W/wp).^(2*N));

%plot the pcolor version of the filter
figure;
my_butter_Huv_plothandle = pcolor(WN,WM,my_data(1).Hw);
set(my_butter_Huv_plothandle, 'EdgeColor', 'none');

colorbar
axis square;

xlabel('\omega_n (columns)');
ylabel('\omega_m (rows)');

set(gca, 'YDir', 'reverse');

title('2D Butterworth H[ \omega_m, \omega_n ], un-wrapperd, centered');

%store our 2D buttferwroth filter 
my_data(1).Hw = 1./sqrt( 1 + (W / wp).^(2*N) ) ;

%%
%the hard code of chebyshev design
passband_gain= 0.85;
stopband_gain = 0.01;
delta_one = 0.15;
squared_delta = 0.85^2;

E = sqrt((1/squared_delta)-1);

K = 2;

%z-domain/DTFT passband and stop band value
w_p = 0.15*pi;
w_s = 0.30*pi;

echo on
%solving for omega_p and omega_s
omega_s = K*tan(w_s/2);
omega_p = K*tan(w_p/2);
echo off

%finding the x domain
omega = linspace(0,2*omega_s,1000);
x = W/omega_p;

N = ceil(log10( ((1/(stopband_gain)^2) -1)/((1/(passband_gain)^2)-1)) * (1/(2*log10(omega_s/omega_p))));

%solving H ideal
H_ideal = abs((1)./(sqrt(1+E^2*(chebyshevT(N, x)).^2)));

%define fundamental spatial frequency
N0 = 512;
wn0 = 2*pi/N0;
wm0 = wn0;

%Define wm and wn axes
wn = [0:1:N0-1]*wn0;
wm = [0:1:N0-1]*wm0;

%subtract pi from both wn and wm to get unwrapped version
wn = wn-pi;
wm = wm-pi;

%generate 2D meshgrid
[WN,WM] = meshgrid(wn,wm);

%defining radius W on wm,wn plane with respect of 0 0 as center
W = sqrt(WM.^2 +WN.^2);

%coding the 2D butterworth filter
my_data(2).Hw = 0;

my_data(2).Hw = abs((1)./(sqrt(1+E^2*(chebyshevT(N, x)).^2)));

%plot the pcolor version of the filter
figure;
my_butter_Huv_plothandle = pcolor(WN,WM,my_data(2).Hw);
set(my_butter_Huv_plothandle, 'EdgeColor', 'none');

colorbar
axis square;

xlabel('\omega_n (columns)');
ylabel('\omega_m (rows)');

set(gca, 'YDir', 'reverse');

title('2D Chebyshev H[ \omega_m, \omega_n ], un-wrapperd, centered');

%store our 2D buttferwroth filter 
my_data(2).Hw = abs((1)./(sqrt(1+E^2*(chebyshevT(N, x)).^2)));
%%
%Hard coding 2D Gaussian smoothing filter
wp_gauss = 0.12*pi;

my_data(3).Hw = exp(-(W/wp_gauss).^2);

figure;
my_butter_Huv_plothandle = pcolor(WN,WM,my_data(3).Hw);
set(my_butter_Huv_plothandle, 'EdgeColor', 'none');

colorbar
axis square;

xlabel('\omega_n (columns)');
ylabel('\omega_m (rows)');

set(gca, 'YDir', 'reverse');

title('2D Gaussian H[ \omega_m, \omega_n ], un-wrapperd, centered');

%%
%Calculate Y[wm,wn] for all three filters using zero
%phase, direct multiplication in the DFT domain, plotting all of them
% 2D FFT of image
input_filename = {'Tay_Tay_BW_noisy_diagonal.tif'};
x_raw = imread(char(input_filename));

%Use imread to load the 2D image
x_double = double(x_raw) / 255; 

% 2D FFT of the normalized image
X = fftshift(fft2(x_double));


my_data(1).tones = [0.038356 0.96865];   
my_data(2).tones = [0.049935 0.97458];   
my_data(3).tones = [0.049041 0.91232];   

my_data(1).Yw = X.*abs(my_data(1).Hw);
my_data(2).Yw = X.*abs(my_data(2).Hw);
my_data(3).Yw = X.*abs(my_data(3).Hw);

y1 = ifft2(ifftshift(my_data(1).Yw));
y2 = ifft2(ifftshift(my_data(2).Yw));
y3 = ifft2(ifftshift(my_data(3).Yw));

my_data(1).y2d = real(y1);
my_data(2).y2d = real(y2);
my_data(3).y2d = real(y3);

my_data(1).ygray=mat2gray(my_data(1).y2d, my_data(1).tones);
my_data(2).ygray=mat2gray(my_data(2).y2d, my_data(2).tones);
my_data(3).ygray=mat2gray(my_data(3).y2d, my_data(3).tones);

my_data(1).title = '1. Butterworth';
my_data(2).title = '2. Chebyshev';
my_data(3).title = '3. Gaussian';

figure('position', [50 50 1200 400]);

for k = 1:3
    subplot(1,3,k);
    imshow(my_data(k).ygray);
    title(my_data(k).title);
end
%%
%Plot the 2D DFT magnitude spectra |H[wm,wn]| for all
%three filters

figure('position', [400 50 1200 500])

for count = 1:3
    subplot(1,3,count);

    %plot magnitude from struct
    h_p = pcolor(WN,WM, abs(my_data(count).Hw));

    %format p color
    set(h_p, 'EdgeColor', 'none');
    colorbar;
    axis square

    %point axis downward
    set(gca, 'YDir', 'reverse')

    xlim([-pi, pi])
    ylim([-pi, pi]);

    xlabel('\omega_n (rows)');
    ylabel('\omega_m (columns)');
    
    % Title using the string
    title([my_data(count).title]);
end
%%


for count = 1:3
    figure('position', [50 300 1200 500])
    subplot(1,2,1);

    y_p = pcolor(WN,WM, log10(abs(my_data(count).Yw + eps)));
    set(y_p, 'EdgeColor', 'none');
    colorbar;
    axis square;
    
    % Point the +wm axis downward
    set(gca, 'YDir', 'reverse');
    
    % Zoom near the center (Your choice - usually -pi to pi or tighter)
    xlim([-0.5, 0.5]); 
    ylim([-0.5, 0.5]);
    
    xlabel('\omega_n (columns)');
    ylabel('\omega_m (rows)');
    title(['Filtered Spectra Y[\omega_n, \omega_m]']);

    subplot(1, 2, 2);
    
    % Show the resulting grayscale image
    imshow(my_data(count).ygray);
    
    % Use the same title string as your previous imshow plot
    title([my_data(count).title]);
end
%%

disp('The best performing filter was the Buttersworth. It cleared all the stripes, but is a little blurry.')

disp('I would prefer the Butterworth because it is the most natural looking filter removing the diagonal spikes without blurring the image too much.')

disp(' The Chbyshev filter is killing noise more aggresivly, but as a result causes a little bit of artifact. We can see faint ghost lines. The Gaussain is sub optimal, the image looks very blurry, but fine details are gone because the filter smears them.')
