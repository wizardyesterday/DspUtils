% Problem 6.32b
% This MATLAB file generates data for the following functions:
% x(n) = cos(2*pi*n/N), where N = 32,64,128
% xz(n) - A zero-order hold version of x(n), for 2*N = 64,128,256
% xi(n) - A first-order hold version of x(n), for 2*N = 64,128,256
% Note that xz(n), xi(n) are quantized to 8 bits.

%**********************************************************************
% Processing for 32 data points
%**********************************************************************
N = 32; %32 data points
theta =linspace(0,2*pi,N);     %generate argument steps
x = cos(theta);                %construct cosine function
xz(1:2:2*N) = x;               %create zero-order hold vector
xz(2:2:2*N) = xz(1:2:2*N-1);   %and fill it in
xz = xz * 256;                 %quantize to 8 bits
xz = round(xz);                %round off
xz = xz / 256;                 %rescale

% Create first-order hold vector
xi = zeros(1:2*N);             %construct vector
xi(1:2:2*N) = x;            
xi(2*N) = xi(2*N-1)/2;         %set last value
for k = 2:2:2*N-1
xi(k) = (xi(k-1) + xi(k+1))/2; %and fill it in
end
xi = xi * 256;                 %quantize to 8 bits
xi = round(xi);                %round off
xi = xi / 256;                 %rescale

% Compute spectra
XZ = fft(xz);
XI = fft(xi);

% Compute total harmonic distortion
harmonics = XZ;                %get harmonic content
harmonics(2) = 0;              %zero out fundamental contributions
harmonics(2*N) = 0;
powerh = sum(harmonics.*conj(harmonics));
powert = sum(XZ.*conj(XZ));
THD_Z32 = powerh / powert;

harmonics = XI;                %get harmonic content
harmonics(2) = 0;              %zero out fundamental contributions
harmonics(2*N) = 0;
powerh = sum(harmonics.*conj(harmonics));
powert = sum(XI.*conj(XI));
THD_I32 = powerh / powert;

%**********************************************************************
% Processing for 64 data points
%**********************************************************************
N = 64; %64 data points
theta =linspace(0,2*pi,N);     %generate argument steps
x = cos(theta);                %construct cosine function
xz(1:2:2*N) = x;               %create zero-order hold vector
xz(2:2:2*N) = xz(1:2:2*N-1);   %and fill it in
xz = xz * 256;                 %quantize to 8 bits
xz = round(xz);                %round off
xz = xz / 256;                 %rescale

% Create first-order hold vector
xi = zeros(1:2*N);             %construct vector
xi(1:2:2*N) = x;            
xi(2*N) = xi(2*N-1)/2;         %set last value
for k = 2:2:2*N-1
xi(k) = (xi(k-1) + xi(k+1))/2; %and fill it in
end
xi = xi * 256;                 %quantize to 8 bits
xi = round(xi);                %round off
xi = xi / 256;                 %rescale

% Compute spectra
XZ = fft(xz);
XI = fft(xi);

% Compute total harmonic distortion
harmonics = XZ;                %get harmonic content
harmonics(2) = 0;              %zero out fundamental contributions
harmonics(2*N) = 0;
powerh = sum(harmonics.*conj(harmonics));
powert = sum(XZ.*conj(XZ));
THD_Z64 = powerh / powert;

harmonics = XI;                %get harmonic content
harmonics(2) = 0;              %zero out fundamental contributions
harmonics(2*N) = 0;
powerh = sum(harmonics.*conj(harmonics));
powert = sum(XI.*conj(XI));
THD_I64 = powerh / powert;

%**********************************************************************
% Processing for 128 data points
%**********************************************************************
N = 128; %128 data points
theta =linspace(0,2*pi,N);     %generate argument steps
x = cos(theta);                %construct cosine function
xz(1:2:2*N) = x;               %create zero-order hold vector
xz(2:2:2*N) = xz(1:2:2*N-1);   %and fill it in
xz = xz * 256;                 %quantize to 8 bits
xz = round(xz);                %round off
xz = xz / 256;                 %rescale

% Create first-order hold vector
xi = zeros(1:2*N);             %construct vector
xi(1:2:2*N) = x;            
xi(2*N) = xi(2*N-1)/2;         %set last value
for k = 2:2:2*N-1
xi(k) = (xi(k-1) + xi(k+1))/2; %and fill it in
end
xi = xi * 256;                 %quantize to 8 bits
xi = round(xi);                %round off
xi = xi / 256;                 %rescale

% Compute spectra
XZ = fft(xz);
XI = fft(xi);

% Compute total harmonic distortion
harmonics = XZ;                %get harmonic content
harmonics(2) = 0;              %zero out fundamental contributions
harmonics(2*N) = 0;
powerh = sum(harmonics.*conj(harmonics));
powert = sum(XZ.*conj(XZ));
THD_Z128 = powerh / powert;

harmonics = XI;                %get harmonic content
harmonics(2) = 0;              %zero out fundamental contributions
harmonics(2*N) = 0;
powerh = sum(harmonics.*conj(harmonics));
powert = sum(XI.*conj(XI));
THD_I128 = powerh / powert;

