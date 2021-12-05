% Problem 6.32e
% This MATLAB file generates data for the following functions:
% x(n) = [sin(6*pi)/(6*pi)]^2
% xi(n) - A length 2*N sequence with alternating samples stuffed with zeros
% X(k) = DFT(x(n))
% Hz(z) = 1 + z^-1
% Yz(k) = Hz(k) * Xi(k)
% Hl(z) = (1/2) * (1 + 2*z^-1 + z^-2) / z^-1
% Yl(k) = Hl(k) * Xi(k)

theta = linspace(0.001,12*pi,64);   %generate argument
x = sin(theta)./theta;              %generate sinc function
x = x .* x;                         %and square it
xi(1:2:128) = x;                    %stuff zeros
xi(128) = 0;                        %and take care of the last point
Xi = fft(xi);                       %take DFT of xi(n)

% Construct zero-order system function
b = [1 1];                          %construct numerator
a = [1 0];                          %construct denominator
Hz = fft(b,128) ./ fft(a,128);      %construct system function

% Construct first-order system function
b = [1 2 1];                        %construct numerator
a = [0 2 0];                        %construct denominator
Hl = fft(b,128) ./ fft(a,128);      %construct system function

Yz = Xi .* Hz;                      %compute response for zero-order system
Yl = Xi .* Hl;                      %compute response for first-order system
