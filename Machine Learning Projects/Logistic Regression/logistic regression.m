load('data.mat')

eta = 10;
epsilon = 0.005;
[theta, risk, error, count] = gradient(X,Y,eta,epsilon);

fprintf('theta = %f\n',theta);

close all;
x = 0:0.01:1;
y = (-theta(3) -theta(1) .* x)/theta(2);
plot (x,y,'b');

hold on;
plot (X(:,1), X(:,2), '.');
title ('Linear Decision Boundary Graph');
legend('Boundary','Points');
xlabel('x');
ylabel('y');

print('Sol4','-dpng');

x_axis = 0:1:count-2;
figure, plot(x_axis, risk(:,1), x_axis, error(:,1))
title ('Error and Risk Graph');
legend('Risk','Error');
xlabel('Iteration');
ylabel('Error/Risk');

print('error_risk','-dpng');