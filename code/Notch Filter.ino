%Question 3 Part B
%number 1
fsample = 3;
w = [-pi:0.01:pi];
Hw = (1*exp(1j*2*w)./((1*exp(1j*2*w))+(0.9*exp(1j*w)+0.81)));
f = (w/pi)*(0.5*fsample);
f45deg = f;

% -- Open a new figure
figure;
% -- Create a (2 x 1) sub-tile array
my_tile = tiledlayout(2,1);
% -- Let's begin on the top subplot !
% Define Axis #1 = w-axis plot
ax1 = axes(my_tile);
%plot magnitude |H(e^jw)| on axis #1 of top plot
Hw_mag_plothandle = plot(w,abs(Hw));
set(Hw_mag_plothandle, 'Color', 'blue', 'Linewidth', 2);
% -- Staying on the top subplot: Define Axis #2 = f-axis plot
ax2 = axes(my_tile);
% -- Plot the dummy 45 deg line on f-axis
f45deg_plothandle = plot(f, f45deg);
% -- Make axes pretty (top = f, bottom = w)
% Make Axis #2 a transparent layer (so we can see down to Axis #1)
ax2.Color = 'none';
ax2.XAxisLocation = 'top';
ax2.YAxisLocation = 'right';
% -- Make sure the axis limits on Axes 1 and 2 are good
ax1.XLim = [min(w) max(w)];
ax2.XLim = [min(f) max(f)];
% -- Horizontal labels on both axes
ax1.XLabel.String = '\omega (n-domain)';
ax2.XLabel.String = 'f (Hz)';
% -- Remove y-label on axis #2 altogether (f-axis)
% -- Then, add title to top subplot using Axis #2
ax2.YTickLabel = '';
ax2.Title.String = 'Figure 1: DFTF magnitude and phase: 2-pole system';
% -- Go back to axis #1 (w-axis): Grid on, and create y-axis label
ax1.XGrid = 'on';
ax1.YGrid = 'on';
ax1.YLabel.String = '|H(e^j^\omega)|';
% -- Finally, make the 45 deg line disappear by removing its color
set(f45deg_plothandle, 'Color', 'none')
nexttile;
% -- Plot your DFTF phase
Hw_phase_plothandle = plot(w, angle(Hw)/pi*180);
set(Hw_phase_plothandle, 'Color', 'blue', 'Linewidth', 2);
%making my grid pretty
grid on;
axis([min(w) max(w) -180 180]);
set(gca, 'YTick', [-180:45:180]);
xlabel('\omega (DFT domain)');
ylabel('|angle(H(e^j^\omega))')
%%
%Question 3 part B number 4
f_sample = 3;
NO = 6;
wo = 2*pi/NO;
T_sample = 1/f_sample;

H1 = tf([1 0 0], [1 0.9 0.81], T_sample);
minreal(H1)

disp('The cleaned-up version of H(z) is')
H_cleaned = minreal(H1);

my_poles1 = pole(H_cleaned);
my_zeroes1 = zero(H_cleaned);
%%
%Question 3 part B number 5, 6, 7

t_final = 2-1/f_sample;
n = 0:5;
h_imp1 = (1/f_sample).* impulse(H_cleaned,t_final);
s = stem(n, h_imp1);
set(s, 'Color', 'blue', 'MarkerFaceColor', 'blue', 'Markersize', 12, 'Linewidth', 2);
title('Figure 2: The filter impulse response h[n]')
xlabel('n = .33')
ylabel('h[n]')
xlim([0 5])
grid on

disp('This filter is a high-pass filter')
%%
%Question 3 Part C
%number 1
clear all
fsample = 3;
w = [-pi:0.01:pi];
Hw = ((1*exp(2*1j*w)+(1*exp(1j*w))+1)./(1*exp(2*1j*w)));
f = (w/pi)*(0.5*fsample);
f45deg = f;

% -- Open a new figure
figure;
% -- Create a (2 x 1) sub-tile array
my_tile = tiledlayout(2,1);
% -- Let's begin on the top subplot !
% Define Axis #1 = w-axis plot
ax1 = axes(my_tile);
%plot magnitude |H(e^jw)| on axis #1 of top plot
Hw_mag_plothandle = plot(w,abs(Hw));
set(Hw_mag_plothandle, 'Color', 'blue', 'Linewidth', 2);
% -- Staying on the top subplot: Define Axis #2 = f-axis plot
ax2 = axes(my_tile);
% -- Plot the dummy 45 deg line on f-axis
f45deg_plothandle = plot(f, f45deg);
% -- Make axes pretty (top = f, bottom = w)
% Make Axis #2 a transparent layer (so we can see down to Axis #1)
ax2.Color = 'none';
ax2.XAxisLocation = 'top';
ax2.YAxisLocation = 'right';
% -- Make sure the axis limits on Axes 1 and 2 are good
ax1.XLim = [min(w) max(w)];
ax2.XLim = [min(f) max(f)];
% -- Horizontal labels on both axes
ax1.XLabel.String = '\omega (n-domain)';
ax2.XLabel.String = 'f (Hz)';
% -- Remove y-label on axis #2 altogether (f-axis)
% -- Then, add title to top subplot using Axis #2
ax2.YTickLabel = '';
ax2.Title.String = 'Figure 3: The dual-subplot, dual-axis DFTF magnitude + phase plots H(e^jw) for the 3-MA filter';
% -- Go back to axis #1 (w-axis): Grid on, and create y-axis label
ax1.XGrid = 'on';
ax1.YGrid = 'on';
ax1.YLabel.String = '|H(e^j^\omega)|';
% -- Finally, make the 45 deg line disappear by removing its color
set(f45deg_plothandle, 'Color', 'none')
nexttile;
% -- Plot your DFTF phase
Hw_phase_plothandle = plot(w, angle(Hw)/pi*180);
set(Hw_phase_plothandle, 'Color', 'blue', 'Linewidth', 2);
%making my grid pretty
grid on;
axis([min(w) max(w) -180 180]);
set(gca, 'YTick', [-180:45:180]);
xlabel('\omega (DFT domain)');
ylabel('|angle(H(e^j^\omega))')
%%
%Question 3 part C number 4
f_sample = 3;
NO = 6;
wo = 2*pi/NO;
T_sample = 1/f_sample;

H1 = tf([1 1 1], [1 0 0], T_sample);
minreal(H1)

disp('The cleaned-up version of H(z) is')
H_cleaned = minreal(H1);

my_poles1 = pole(H_cleaned);
my_zeroes1 = zero(H_cleaned);
%%
%Question 3 part C number 5, 6, 7

t_final = 2-1/f_sample;
n = 0:5;
h_imp1 = (1/f_sample).* impulse(H_cleaned,t_final);
s = stem(n, h_imp1);
set(s, 'Color', 'blue', 'MarkerFaceColor', 'blue', 'Markersize', 12, 'Linewidth', 2);
title('Figure 4: The impulse response for the 3-MA filter h[n]')
xlabel('n = .33')
ylabel('h[n]')
xlim([0 5])
grid on

disp('This filter is a low-pass filter')
%%
%Question 3 Part D
%number 1
clear all
fsample = 3;
w = [-pi:0.01:pi];
Hw = ((1*exp(2*1j*w)+(1*exp(1j*w))+1)./((1*exp(1j*2*w))+(0.9*exp(1j*w)+0.81)));
f = (w/pi)*(0.5*fsample);
f45deg = f;

% -- Open a new figure
figure;
% -- Create a (2 x 1) sub-tile array
my_tile = tiledlayout(2,1);
% -- Let's begin on the top subplot !
% Define Axis #1 = w-axis plot
ax1 = axes(my_tile);
%plot magnitude |H(e^jw)| on axis #1 of top plot
Hw_mag_plothandle = plot(w,abs(Hw));
set(Hw_mag_plothandle, 'Color', 'blue', 'Linewidth', 2);
% -- Staying on the top subplot: Define Axis #2 = f-axis plot
ax2 = axes(my_tile);
% -- Plot the dummy 45 deg line on f-axis
f45deg_plothandle = plot(f, f45deg);
% -- Make axes pretty (top = f, bottom = w)
% Make Axis #2 a transparent layer (so we can see down to Axis #1)
ax2.Color = 'none';
ax2.XAxisLocation = 'top';
ax2.YAxisLocation = 'right';
% -- Make sure the axis limits on Axes 1 and 2 are good
ax1.XLim = [min(w) max(w)];
ax2.XLim = [min(f) max(f)];
% -- Horizontal labels on both axes
ax1.XLabel.String = '\omega (n-domain)';
ax2.XLabel.String = 'f (Hz)';
% -- Remove y-label on axis #2 altogether (f-axis)
% -- Then, add title to top subplot using Axis #2
ax2.YTickLabel = '';
ax2.Title.String = 'Figure 5: The dual-subplot, dual-axis DFTF magnitude + phase plots H(e^jw) for the notch combo filter';
% -- Go back to axis #1 (w-axis): Grid on, and create y-axis label
ax1.XGrid = 'on';
ax1.YGrid = 'on';
ax1.YLabel.String = '|H(e^j^\omega)|';
% -- Finally, make the 45 deg line disappear by removing its color
set(f45deg_plothandle, 'Color', 'none')
nexttile;
% -- Plot your DFTF phase
Hw_phase_plothandle = plot(w, angle(Hw)/pi*180);
set(Hw_phase_plothandle, 'Color', 'blue', 'Linewidth', 2);
%making my grid pretty
grid on;
axis([min(w) max(w) -180 180]);
set(gca, 'YTick', [-180:45:180]);
xlabel('\omega (DFT domain)');
ylabel('|angle(H(e^j^\omega))')
%%
%Question 3 part D number 4
f_sample = 3;
NO = 6;
wo = 2*pi/NO;
T_sample = 1/f_sample;

H1 = tf([1 1 1], [1 0.9 0.81], T_sample);
minreal(H1)

disp('The cleaned-up version of H(z) is')
H_cleaned = minreal(H1);

my_poles1 = pole(H_cleaned);
my_zeroes1 = zero(H_cleaned);
%%
%Question 3 part D number 5, 6, 7

t_final = 2-1/f_sample;
n = 0:5;
h_imp1 = (1/f_sample).* impulse(H_cleaned,t_final);
s = stem(n, h_imp1);
set(s, 'Color', 'blue', 'MarkerFaceColor', 'blue', 'Markersize', 12, 'Linewidth', 2);
title('Figure 6: The impulse response for the notch combo filters h[n]')
xlabel('n = .5')
ylabel('h[n]')
xlim([0 5])
grid on

disp('This filter is a notch filter')
