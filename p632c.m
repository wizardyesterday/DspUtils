% Problem 6.32c
% This MATLAB file calculates the magnitude and phase responses of the
% following system functions:
% Hz(z) = 1 + z^-1
% Hl(z) = (1/2) * (1 + 2*z^-1 + z^-2) / z^-1

% Parameters for zero-order case
b = [1 1];                     %numerator
a = [1 0];                     %denominator
[Hz,wz] = freqz(b,a,128);      %compute frequency response function
magz = abs(Hz);                %calculate magnitude response
phasez = angle(Hz);            %calculate phase response

% Parameters for first-order case
b = [1 2 1];                   %numerator
a = [0 2 0];                   %denominator
[Hl,wl] = freqz(b,a,128);      %compute frequency response function
magl = abs(Hl);                %calculate magnitude response
phasel = angle(Hl);            %calculate phase response
