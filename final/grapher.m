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