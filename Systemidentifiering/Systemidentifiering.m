% ------------------------------
%     System identification
%     Verision: 1.0
% ------------------------------

close all
clear
clc

% Data
load data.mat
temp = temp(200:end);           % Remove start 
time = 0:5:(length(temp)*5-5);  % 0.2 Hz 

% Model
s = tf("s");
K = temp(end)-temp(1);
T = 9000;
G = (K/(1+s*T)) +temp(1);

% Plot
data_red = 1;      % Reduce data point for plot

figure
plot(time(1:data_red:length(time)), temp(1:data_red:length(temp)), "r")
hold on
step(G)
ylabel("Temperature (°C)")
legend("Data", "Model", 'Location', 'best')
axis([0, 4*10^4, 21, 24])