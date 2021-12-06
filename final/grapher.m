%% timed results when using solver
    % ran program 5 times consecutively 
    m1 = [52,52,52,52,55];
    m2 = [13,14,13,14,14];
    m3 = [15,16,15,16,16];
    m4 = [19,19,19,19,19];
%% timed results when using for loop with O3 complexity
n1 = [245,240,189,211,248]; % 231
n2 = [152,165,135,171,192]; % 163
n3 = [206,244,174,225,252]; % 234
n4 = [206,244,174,225,252]; % 234

%% lets plot the results
figure(1)
hold all; 
y1 = [mean(m1), mean(m2), mean(m3), mean(m4)];
y2 = [mean(n1), mean(n2), mean(n3), mean(n4)];

scatter(1:4,y1, "b", "filled"); 
scatter(1:4,y2, "m", "filled");
xticks([1:4]); xticklabels(["2x2","3x3", "4x3", "6x3"]);
xlabel("Matrix Dimensions"); ylabel("Computation Time [\mus]"); grid on;
legend("HPC Algorithm", "O3-complexity Algorithm");
title("Time Comparison for Matrix Addition with Different Algorithms")
subtitle("Average time of five runtimes for the operation A = B + C")
%% Application 2 - matrix multiplication and vary cut off times - lets plot the results

y1 = [14.2,99.4, 921.6, 546245,  5.55675e+06, 1.04732e+08,...
    3.70456e+08,  5.94778e+08,900923375]; % base data, cut off = 4 
y2 = [29.4, 204.2, 1567.8, 810342, 6.40088e+06,5.10096e+07,...
    1.01859e+08, 3.30917e+08, 402009264]; % recursive data, cut off = 4
y3 = [13,135.2, 1019.2,622889,8.38492e+06,1.10374e+08,...
    3.80525e+08,6.14693e+08,8.82802e+08]; % base data, cut off = 16
y4 = [12.2, 94.4,753.8,387579,3.13889e+06,2.54366e+07,...
    9.00584e+07,1.43033e+08,1.97908e+08 ]; % recursive data, cut off = 16
y5 = [16.6,223.4,1254.8,1.02971e+06,1.0927e+07,...
    1.12199e+08,3.84742e+08,6.13445e+08,8.86154e+08]; % base data, cut off = 64
y6 = [15.2, 163,1372.6,616497, 4.88663e+06,...
    3.89808e+07,1.26052e+08,1.97296e+08, 3.01486e+08]; % base data, cut off = 64

figure (2)
subplot(1,2,1)
plot(1:length(y1),y5, "b*-"); hold on;
subplot(1,2,1)
plot(1:length(y2),y6, "m*-"); hold on;
xticks([1:length(y1)]); xticklabels(["16","32", "64", "512"...
    "1024", "2048", "3072", "3584", "4096"]);
xlabel("Submatrix Dimensions, nxn"); ylabel("Computation Time [\mus]"); grid on;
legend("Base Multiplication", "Recursive Multiplication, cutoff point 64");
title("Time Comparison for Matrix Multiplication with Different Algorithms")
subtitle("Average of five runtimes for the operation A = B*C")

subplot(1,2,2);
cdata = [y5', y6'];
xvalues = {'Base Multiplication','Recursive Multiplication'};
yvalues = ["16","32", "64", "512"...
    "1024", "2048", "3072", "3584", "4096"];
h = heatmap(xvalues,yvalues,cdata);

h.Title = 'Summary of Execution Times';
h.XLabel = 'Algorithm';
h.YLabel = 'Execution Time [\mus]';
%% Summary of Execution times
figure(3);
cdata = [y1', y2', y3', y4', y5', y6'];
xvalues = {'Base, CP 4','Recursive, CP 4', 'Base, CP 16','Recursive, CP 16'...
    'Base, CP 64','Recursive, CP 64'};
yvalues = ["16","32", "64", "512"...
    "1024", "2048", "3072", "3584", "4096"];
h = heatmap(xvalues,yvalues,cdata);

h.Title = 'Summary of Execution Times';
h.XLabel = 'Algorithm';
h.YLabel = 'Execution Time [\mus]';

% probably could go to a higher cut off point 