% Riley Ruckman
% TCES430, Au20
% Project - Simulation vs Implementation

% Nominal component values used in circuit design
R = 10;             % Resistor
C = 470 * 10^(-6);  % Capacitor
L = 1;              % Inductor
Req = 41;           % Inductor resistance

% Read battery voltage, which will act as the step input amplitude for the
% simulations
inputAmp = 1.56;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Open Loop %

% Transfer function of the given circuit.
openLoop = tf([1/(C*L)],[1 (R + Req)/L 1/(C*L)]);

% sys =
% 
%         2128
%   -----------------
%   s^2 + 51 s + 2128

% Time when step input turned on in the implementation
% Found in output from Simulink
openLoopTimeStep = 5.39;

[y,t] = step(openLoop * inputAmp, 1);

figure;
hold on;

plot(t,y);
plot(0:0.01:1,openLoopImplementation(1, openLoopTimeStep*100:openLoopTimeStep*100 + 100), ':');

hold off;

xlabel('Time (s)');
ylabel('Output Voltage (V)');
title('LRC Open Loop Step Response');
legend('Simulation','Implementation','Location','SouthEast');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Closed Loop %

closedLoop = feedback(openLoop,1);

% Time when step input turned on in the implementation
% Found in output from Simulink
closedLoopTimeStep = 5.80;

[y,t] = step(closedLoop * inputAmp, 1);

figure;
hold on;

plot(t,y);
plot(0:0.01:1,closedLoopImplementation(1, closedLoopTimeStep*100:closedLoopTimeStep*100 + 100), ':');

hold off;

xlabel('Time (s)');
ylabel('Output Voltage (V)');
title('LRC Closed Loop Step Response');
legend('Simulation','Implementation','Location','SouthEast');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Open rltool() for PI Controller Design

% rltool(openLoop);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Closed Loop With Controller %

% Using PI controller in the form (Kp*(s + tau))/s,
% where tau = Ki/Kp
% tau and Kp are found using the rltool() tool
tau = 10;
Kp = 2.4;
controller = Kp * tf([1 tau],[1 0]);

% controller =
%  
%   2.4 s + 24
%   ----------
%       s

openLoopWcontroller = tf([openLoop * controller]);

% openLoopWcontroller =
%  
%     5106 s + 5.106e04
%   ---------------------
%   s^3 + 51 s^2 + 2128 s

closedLoopWcontroller = feedback(openLoopWcontroller, 1);

% closedLoopWcontroller =
%  
%          5106 s + 5.106e04
%   --------------------------------
%   s^3 + 51 s^2 + 7234 s + 5.106e04

% Time when step input turned on in the implementation
% Found in output from Simulink
closedLoopWcontrollerTimeStep = 5.42;

[y,t] = step(closedLoopWcontroller * inputAmp, 1);

figure;
hold on;

plot(t,y);
plot(0:0.01:1,closedLoopwithControllerImplementation(1, closedLoopWcontrollerTimeStep*100:closedLoopWcontrollerTimeStep*100 + 100), ':');

hold off;

xlabel('Time (s)');
ylabel('Output Voltage (V)');
title('LRC Closed Loop With Controller Step Response, Kp = 2.4, Ki = 24');
legend('Simulation','Implementation','Location','SouthEast');
