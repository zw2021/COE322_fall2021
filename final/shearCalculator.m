% Plotting acceleration, vorticity, linear strain, and angular strain from 
% given velocity field 
clear all; clc;
% Constants %
h = 1; % diameter of the pipe [m]
P = 1; % pressure constant, normalized to 1 [Pa]
% y = 0.5; % pipe center line [m]
% mu is dynamic viscosity of liquid
% x is location; choosing a super big x to ensure flow is fully devloped
% Velocity components %
syms x y z mu 

u = (1/(2*mu))*P*(y^2-h*y)+x^2*z^3;
v = y^3 + h*y;
w = y^3 + x;

du_dx = diff(u,x);
du_dy = diff(u,y);
du_dz = diff(u,z);
dv_dx = diff(v,x);
dv_dy = diff(v,y);
dv_dz = diff(v,z);
dw_dx = diff(w,x);
dw_dy = diff(w,y);
dw_dz = diff(w,z);
%% compute x-y components of angular strain
exy = 1/2*(dv_dx + du_dy);
ezx = 1/2*(du_dz + dw_dx);
ezy = 1/2*(dw_dy + dv_dz);
%% compute linear strain
exx = du_dx;
eyy = dv_dy;
ezz = dw_dz;
%% get Shear matrix at centerline velocity; y = 0.5
val = 1e-3; % subsitute kinematic visocisity for water 
exx_val = subs(exx, {x, y, z}, {100,0.5, 1});
eyy_val = subs(eyy, {x, y, z}, {100,0.5, 1});
ezz_val = subs(ezz, {x, y, z}, {100,0.5, 1});
exy_val = subs(exy, {x, y, z}, {100,0.5, 1});
ezx_val = subs(ezx, {x, y, z}, {100,0.5, 1});
ezy_val = subs(ezy, {x, y, z}, {100,0.5, 1});
ezz_val = subs(ezz, {x, y, z}, {100,0.5, 1});

S = [double(exx_val), double(exy_val) double(ezx_val); ...
    double(exy_val) double(eyy_val) double(ezy_val);...
    double(ezx_val) double(ezy_val) double(ezz_val)];
S = 2*mu*S;
%% get Shear matrix at centerline velocity; y = 0
val = 1e-3; % subsitute kinematic visocisity for water 
exx_val = subs(exx, {x, y, z}, {100,0, 1});
eyy_val = subs(eyy, {x, y, z}, {100,0, 1});
ezz_val = subs(ezz, {x, y, z}, {100,0, 1});
exy_val = subs(exy, {x, y, z}, {100,0, 1});
ezx_val = subs(ezx, {x, y, z}, {100,0, 1});
ezy_val = subs(ezy, {x, y, z}, {100,0, 1});

S = [(exx_val), (exy_val) (ezx_val); ...
    (exy_val) (eyy_val) (ezy_val);...
    (ezx_val) (ezy_val) (ezz_val)];
S = 2*mu*S;
%% plot shear vector field 
%{
xlabel("x"); ylabel("y");
quiver(X, Y, zeros(21,21,21), eyy_val);
title("\epsilon_y_y in XY Plane")
subplot(1,2,2);
quiver3(X,Y,Z, zeros(21,21,21), eyy_val,zeros(21,21,21)); hold on; axis equal;
title("\epsilon_y_y in XYZ Space"); xlabel("x"); ylabel("y"); zlabel("z");

figure();
subplot(1,2,1);
quiver(X, Y, exx_val, zeros(21,21,21));
xlabel("x"); ylabel("y"); title("\epsilon_x_x in XY Plane");
subplot(1,2,2);
quiver3(X,Y, Z, exx_val, zeros(21,21,21),zeros(21,21,21)); hold on;
title("\epsilon_x_x in XYZ Space"); xlabel("x"); ylabel("y"); zlabel("z");

figure()
subplot(1,2,1);
quiver(X, Y, zeros(21,21,21),exy_val);
xlabel("x"); ylabel("y"); title("\epsilon_x_y in XY Plane");
subplot(1,2,2);
quiver3(X,Y,Z, zeros(21,21,21), exy_val,zeros(21,21,21)); hold on; axis equal;
title("\epsilon_x_y in XYZ Space"); xlabel("x"); ylabel("y"); zlabel("z");
%% plot w as vorticitiy - 3D quiver graph
[X,Y,Z] = meshgrid(xx,yy,zz);
wz_val = subs(wz, {y}, {Y});
figure();
title("Vorticity, \omega in vector field Space")
subplot(1,2,1);
quiver(X,Z,zeros(21,21,21), wz_val); hold on; axis equal; % 2D graph
xlabel("x"); ylabel("z"); title("\omega in XZ Plane");
subplot(1,2,2);
quiver3(X,Y,Z, zeros(21,21,21), zeros(21,21,21), wz_val); hold on;
xlabel("x"); zlabel("z"); ylabel("y");title("\omega in XYZ Space");

%% Vorticity Contour Plot 
figure();
[X,Y] = meshgrid(xx,yy);
Z = -11*Y;  % w
contour(X,Y,Z); colorbar; 
title("Contour Graph of Vorticity, \omega")
xlabel("x"); ylabel("y");
%% Plot Exy, Exx, Exy as contour plots
Z = -12*X; % exx
figure(); contour(X,Y,Z); colorbar; 
title("Contour Graph of Linear Strain, \epsilon_x_x")
xlabel("x"); ylabel("y");

Z = X;  %eyy
figure(); contour(X,Y,Z); colorbar; 
title("Contour Graph of Linear Strain, \epsilon_y_y")
xlabel("x"); ylabel("y");

Z = 13/2*Y; %exy
figure(); contour(X,Y,Z); colorbar; 
title("Contour Graph of Shear Strain, \epsilon_x_y")
xlabel("x"); ylabel("y");
%}
