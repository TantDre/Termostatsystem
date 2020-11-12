% ------------------------------
%     System identification
%     Verision: 1.0
% ------------------------------

close all
clear
clc

% Data
run data.m
temp = temp(200:end);
time = 0:5:(length(temp)*5-5);

% Model
s = tf("s");
K = 23-temp(1);
T = 6000;
G = (K/(1+s*T)) +temp(1);

% Plot
figure
plot(time, temp, "r")
hold on
step(G)

ylabel("Temperature (°C)")
legend("Data", "Model", 'Location', 'best')