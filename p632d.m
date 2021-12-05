% Problem 6.32d
% This MATLAB file generates data for the following functions:
% x(n) = cos(2*pi*n/N), where N = 64
% xz(n) - A zero-order hold version of x(n), for 2*N = 128
% xi(n) - A first-order hold version of x(n), for 2*N = 128

N = 64; %64 data points
theta =linspace(0,2*pi,N);     %generate argument steps
x = cos(theta);                %construct cosine function
xz(1:2:2*N) = x;               %create zero-order hold vector
xz(2:2:2*N) = xz(1:2:2*N-1);   %and fill it in

% Create first-order hold vector
xi = zeros(1:2*N);             %construct vector
xi(1:2:2*N) = x;            
xi(2*N) = xi(2*N-1)/2;         %set last value
for k = 2:2:2*N-1
xi(k) = (xi(k-1) + xi(k+1))/2; %and fill it in
end

% Compute spectra
XZ = fft(xz);
XI = fft(xi);

