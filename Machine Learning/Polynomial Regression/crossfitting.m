load('data.mat')

error_list = zeros(10,1);

for i=1:10
    [err,model] = polyreg(x,y,i);
    error_list(i) = err;
    title(sprintf('d = %d', i)) ;
    xlabel('x');
    ylabel('y');
    filename = sprintf('crossfitting_d_%d.png', i);
    print(filename,'-dpng');
end

[M,I] = min(error_list);
fprintf('Most optimum degree of polynomial = %i\n', I);

close all;

z = linspace(1,10,10);
plot(z,error_list);
xlabel('Degree of Polynomial - 1');
ylabel('Average Squared Loss');
title('Error Graph');
print('Error_Graph','-dpng');