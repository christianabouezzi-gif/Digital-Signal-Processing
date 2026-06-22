%%
%the calculated time tick mark width
time_tick = time(3)-time(2);
%fsample is just the inverse of the delta t.
fsample = 1/time_tick;
time_tick
fsample
%%

%set up for substitution
syms n
%created the bounds for the m
m = [5 41 101];
%created a vector of a 3rd order trinomial
h = [1 n n.^2 n.^3];
%created cell arrays to store data
matrixes = cell(1,3);
transposed = cell(1,3);
B = cell(1,3);
h_n = cell(1,3);
bound = cell(1,3);

%looped to find h[n] impulse response
for v = 1:length(m)
    %found the bounds using floor, this is our time stamp
    boundy = -floor(m(v)/2):floor(m(v)/2);
    bound{v} = boundy;
    %made it into a column vector, to allow for the creation of a matirx
    matrix = [bound{v}]';
    %substituted the n values in the h vector for values in the bound
    A1 = subs(h,n, matrix);
    %tranasposed the matrix to find our b matrix
    A1_trans = A1';
    %saved the transposed matrix in a cell array
    transposed{v} = A1_trans;
    %saved the matrix in a cell array
    matrixes{v} = A1;
    %created and saved the matrix in a cell array
    B{v} = inv(transposed{v}*matrixes{v})*transposed{v};
    %took the first line of each B matrix to use as our impulse response. 
    h_n{v} = B{v}(1,:);
end
%%
figure
H_n_stem = stem(bound{1},h_n{1});
title('Figure 1a: h[n] for m=5')
xlabel('n')
ylabel('h[n]')
set(H_n_stem, 'marker', 'o', 'Color', 'blue', 'MarkerSize', 12, 'Linewidth', 2);
%%
%defining delta T
deltaT = 1/18;
%evaluating the smapling freq
f_sample = 1/deltaT;
%defining h[n] for the filter
h = double(h_n{1});
%make my h a row vector
h = h(:).';
%defining numerator of H(z) in z^-1 format
Hz_numerator = h;
%defining denomenator
Hz_denominator = 1;

%use tf() function to construct H(z)
Hz = tf(Hz_numerator, Hz_denominator, deltaT);

Hz_zeros = zero(Hz);
Hz_poles = pole(Hz);

disp('there are no poles of H(z) in the Z-domain')

fprintf('The zeros are:');
fprintf(' %f', Hz_zeros);
fprintf('\n');

%code for pole zero graph 

figure
theta = linspace(0, 2*pi);
c = plot(cos(theta), sin(theta));
set(c, 'Color', 'k', 'Linewidth', 2)
hold on
for i = 1:length(Hz_poles)
    p_real = real(Hz_poles);
    p_imag = imag(Hz_poles);
    p = plot(p_real(i), p_imag(i));
    set(p, 'marker', 'x', 'Color', 'blue', 'MarkerSize', 10, 'Linewidth', 2);
end

for i = 1:length(Hz_zeros)
    z_real = real(Hz_zeros);
    z_imag = imag(Hz_zeros);
    z = plot(z_real(i), z_imag(i));
    set(z, 'marker', 'o', 'Color', 'red', 'MarkerSize', 15, 'Linewidth', 2);
end 
xlim([-6 6]);
ylim([-6 6]);
axis square
grid on
hold off
title('Figure 1b: Pole-Zero of H(z) for m = 5')
xlabel('Real(z)')
ylabel('Imaginary(z)')
%%
%code for the expression H(e^jw) for m = 5

w = -pi:0.01:pi;
Hw_denominator = 1;
Hw_numerator = 0;
for l = 1:length(h)
    Hw_numerator = Hw_numerator +h(l).*exp(-1i*(l-1).*w);
end

H_total = Hw_numerator ./ Hw_denominator;


%code for plotting the DTFT
fsample = 18;
f = (w/pi)*0.5*fsample;


% -- Define the corresponding f-axis (Hz) using our conversion formula
% (if we know the sampling frequency f_sample)
f = (w/pi)* 0.5 * fsample;
% -- Create a "fake" 45 degree line on the f-axis
f_45deg = f;
% -- Open a figure
% -- Then define a (1 x 1) tile that fills that figure
figure;
my_tile = tiledlayout(1,1);
% -- Then, create Axes #1 (w-axis layer)
ax1 = axes(my_tile);
% -- Plot DTFT magnitude |H(e^jw)|
Hw_magplothandle = plot(w, abs(H_total));
set(Hw_magplothandle, 'Color', 'blue', 'Linewidth', 2);
% -- Create Axex #2 (f-axis layer)
ax2 = axes(my_tile);
% -- Plot the fake 45 deg line onto Axes #2
f45deg_plothandle = plot(f, f_45deg);
ax2.Color = 'none';
ax2.XAxisLocation = 'top';
ax2.YAxisLocation = 'right';
% -- Axes #1 labels
ax1.XLabel.String = '\omega (n-domain)';
ax1.YLabel.String = '|H(e^j^\omega)|';
% -- Axes #2: x-label
ax2.XLabel.String = 'f (Hz)';
% -- Turn off Axis #2's y-axis ticks
ax2.YTickLabel = '' ;
% -- Add title only to Axes 2 (at the top of the page)
ax2.Title.String = 'DFTF magnitude plot';
% -- Axis #1: force x-limits to be from w = [-pi, pi]
ax1.XLim = [-pi pi];
ax1.YLim = [0 1];
% -- Axis #2: Force x-limits to be from f = [-fsample/2 , fsample/2]
ax2.XLim = [-1/2*fsample 1/2*fsample];
% -- Turn Axes #1 grids on
ax1.XGrid = 'on';
ax1.YGrid = 'on';
ax1;
% -- Create a legend string matrix for Axes #1
my_legend_strings = {'|H(e^j^w)|'};
% -- Plot the legend on Axes #1, and make it look pretty
my_legend_plothandle = legend([Hw_magplothandle], my_legend_strings);
set(my_legend_plothandle, 'FontName', 'Arial', 'FontSize', 9, 'Location', 'northeast');
set(f45deg_plothandle, 'Color', 'none');
ax1;
title('Figure 1c: DTFT magnitude plot (m=5)')
%%
    
% m = 41
figure
H_n_stem = stem(bound{2},h_n{2});
title('Figure 2a: h[n] for m=41')
xlabel('n')
ylabel('h[n]')
%defining delta T
deltaT = 1/18;
%evaluating the smapling freq
f_sample = 1/deltaT;
%defining h[n] for the filter
h = double(h_n{2});
%make my h a row vector
h = h(:).';
%defining numerator of H(z) in z^-1 format
Hz_numerator = h;
%defining denomenator
Hz_denominator = 1;

%use tf() function to construct H(z)
Hz = tf(Hz_numerator, Hz_denominator, deltaT);

Hz_zeros = zero(Hz);
Hz_poles = pole(Hz);

disp('there are no poles of H(z) in the Z-domain')

fprintf('in m = 41 The zeros are:');
fprintf(' %f', Hz_zeros);
fprintf('\n');

%code for pole zero graph 

figure
theta = linspace(0, 2*pi);
c = plot(cos(theta), sin(theta));
set(c, 'Color', 'k', 'Linewidth', 2)
hold on
for i = 1:length(Hz_poles)
    p_real = real(Hz_poles);
    p_imag = imag(Hz_poles);
    p = plot(p_real(i), p_imag(i));
    set(p, 'marker', 'x', 'Color', 'blue', 'MarkerSize', 10, 'Linewidth', 2);
end

for i = 1:length(Hz_zeros)
    z_real = real(Hz_zeros);
    z_imag = imag(Hz_zeros);
    z = plot(z_real(i), z_imag(i));
    set(z, 'marker', 'o', 'Color', 'red', 'MarkerSize', 15, 'Linewidth', 2);
end 
xlim([-1.3 1.3]);
ylim([-1.3 1.3]);
axis square
grid on
hold off
title('Figure 2b: Pole-Zero of H(z) for m = 41')
xlabel('Real(z)')
ylabel('Imagnary(z)')
%%
%code for the expression H(e^jw) for m = 41

w = -pi:0.01:pi;
Hw_denominator = 1;
Hw_numerator = 0;
for l = 1:length(h)
    Hw_numerator = Hw_numerator +h(l).*exp(-1i*(l-1).*w);
end

H_total = Hw_numerator ./ Hw_denominator;


%code for plotting the DTFT
fsample = 18;
f = (w/pi)*0.5*fsample;


% -- Define the corresponding f-axis (Hz) using our conversion formula
% (if we know the sampling frequency f_sample)
f = (w/pi)* 0.5 * fsample;
% -- Create a "fake" 45 degree line on the f-axis
f_45deg = f;
% -- Open a figure
% -- Then define a (1 x 1) tile that fills that figure
figure;
my_tile = tiledlayout(1,1);
% -- Then, create Axes #1 (w-axis layer)
ax1 = axes(my_tile);
% -- Plot DTFT magnitude |H(e^jw)|
Hw_magplothandle = plot(w, abs(H_total));
set(Hw_magplothandle, 'Color', 'blue', 'Linewidth', 2);
% -- Create Axex #2 (f-axis layer)
ax2 = axes(my_tile);
% -- Plot the fake 45 deg line onto Axes #2
f45deg_plothandle = plot(f, f_45deg);
ax2.Color = 'none';
ax2.XAxisLocation = 'top';
ax2.YAxisLocation = 'right';
% -- Axes #1 labels
ax1.XLabel.String = '\omega (n-domain)';
ax1.YLabel.String = '|H(e^j^\omega)|';
% -- Axes #2: x-label
ax2.XLabel.String = 'f (Hz)';
% -- Turn off Axis #2's y-axis ticks
ax2.YTickLabel = '' ;
% -- Add title only to Axes 2 (at the top of the page)
ax2.Title.String = 'DFTF magnitude plot';
% -- Axis #1: force x-limits to be from w = [-pi, pi]
ax1.XLim = [-pi pi];
ax1.YLim = [0 1];
% -- Axis #2: Force x-limits to be from f = [-fsample/2 , fsample/2]
ax2.XLim = [-1/2*fsample 1/2*fsample];
% -- Turn Axes #1 grids on
ax1.XGrid = 'on';
ax1.YGrid = 'on';
ax1;
% -- Create a legend string matrix for Axes #1
my_legend_strings = {'|H(e^j^w)|'};
% -- Plot the legend on Axes #1, and make it look pretty
my_legend_plothandle = legend([Hw_magplothandle], my_legend_strings);
set(my_legend_plothandle, 'FontName', 'Arial', 'FontSize', 9, 'Location', 'northeast');
set(f45deg_plothandle, 'Color', 'none');
ax1;
title('Figure 2c: DTFT magnitude plot (m=41)')
%%



%%
%m = 101
figure
H_n_stem = stem(bound{3},h_n{3});
title('Figure 3a: h[n] for m=101')
xlabel('n')
ylabel('h[n]')
%defining delta T
deltaT = 1/18;
%evaluating the smapling freq
f_sample = 1/deltaT;
%defining h[n] for the filter
h = double(h_n{3});
%make my h a row vector
h = h(:).';
%defining numerator of H(z) in z^-1 format
Hz_numerator = h;
%defining denomenator
Hz_denominator = 1;

%use tf() function to construct H(z)
Hz = tf(Hz_numerator, Hz_denominator, deltaT);

Hz_zeros = zero(Hz);
Hz_poles = pole(Hz);

disp('there are no poles of H(z) in the Z-domain')

fprintf('in m = 101 The zeros are:');
fprintf(' %f', Hz_zeros);
fprintf('\n');

%code for pole zero graph 

figure
theta = linspace(0, 2*pi);
c = plot(cos(theta), sin(theta));
set(c, 'Color', 'k', 'Linewidth', 2)
hold on
for i = 1:length(Hz_poles)
    p_real = real(Hz_poles);
    p_imag = imag(Hz_poles);
    p = plot(p_real(i), p_imag(i));
    set(p, 'marker', 'x', 'Color', 'blue', 'MarkerSize', 10, 'Linewidth', 2);
end

for i = 1:length(Hz_zeros)
    z_real = real(Hz_zeros);
    z_imag = imag(Hz_zeros);
    z = plot(z_real(i), z_imag(i));
    set(z, 'marker', 'o', 'Color', 'red', 'MarkerSize', 15, 'Linewidth', 2);
end 
xlim([-1.3 1.3]);
ylim([-1.3 1.3]);
axis square
grid on
hold off
title('Figure 3b: Pole-Zero of H(z) for m = 101')
xlabel('Real(z)')
ylabel('Imaginary(z)')
%%
%code for the expression H(e^jw) for m = 101

w = -pi:0.01:pi;
Hw_denominator = 1;
Hw_numerator = 0;
for l = 1:length(h)
    Hw_numerator = Hw_numerator +h(l).*exp(-1i*(l-1).*w);
end

H_total = Hw_numerator ./ Hw_denominator;


%code for plotting the DTFT
fsample = 18;
f = (w/pi)*0.5*fsample;


% -- Define the corresponding f-axis (Hz) using our conversion formula
% (if we know the sampling frequency f_sample)
f = (w/pi)* 0.5 * fsample;
% -- Create a "fake" 45 degree line on the f-axis
f_45deg = f;
% -- Open a figure
% -- Then define a (1 x 1) tile that fills that figure
figure;
my_tile = tiledlayout(1,1);
% -- Then, create Axes #1 (w-axis layer)
ax1 = axes(my_tile);
% -- Plot DTFT magnitude |H(e^jw)|
Hw_magplothandle = plot(w, abs(H_total));
set(Hw_magplothandle, 'Color', 'blue', 'Linewidth', 2);
% -- Create Axex #2 (f-axis layer)
ax2 = axes(my_tile);
% -- Plot the fake 45 deg line onto Axes #2
f45deg_plothandle = plot(f, f_45deg);
ax2.Color = 'none';
ax2.XAxisLocation = 'top';
ax2.YAxisLocation = 'right';
% -- Axes #1 labels
ax1.XLabel.String = '\omega (n-domain)';
ax1.YLabel.String = '|H(e^j^\omega)|';
% -- Axes #2: x-label
ax2.XLabel.String = 'f (Hz)';
% -- Turn off Axis #2's y-axis ticks
ax2.YTickLabel = '' ;
% -- Add title only to Axes 2 (at the top of the page)
ax2.Title.String = 'DFTF magnitude plot';
% -- Axis #1: force x-limits to be from w = [-pi, pi]
ax1.XLim = [-pi pi];
ax1.YLim = [0 1];
% -- Axis #2: Force x-limits to be from f = [-fsample/2 , fsample/2]
ax2.XLim = [-1/2*fsample 1/2*fsample];
% -- Turn Axes #1 grids on
ax1.XGrid = 'on';
ax1.YGrid = 'on';
ax1;
% -- Create a legend string matrix for Axes #1
my_legend_strings = {'|H(e^j^w)|'};
% -- Plot the legend on Axes #1, and make it look pretty
my_legend_plothandle = legend([Hw_magplothandle], my_legend_strings);
set(my_legend_plothandle, 'FontName', 'Arial', 'FontSize', 9, 'Location', 'northeast');
set(f45deg_plothandle, 'Color', 'none');
ax1;
title('Figure 3c: DTFT magnitude plot (m=101)')

disp('Looking at the DTFT plots, the signals have low frequencies at about .5 Hz. Anything above that is high frequency that get smoothed out as the window increases, indicating that is noise. The freqeuncy range is about 2-9, bc nyquist formula estimates te range can go to 9 Hz. this alligns with the Savitzky Golay filter for large m. in m=5, we can notice after 2 Hz in the dtft, we see noise, no smoothed areas.')
