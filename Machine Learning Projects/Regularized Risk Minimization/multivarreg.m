function [errTrain, errTest] = multivarreg(x,y,lambda,xT,yT)

% Finds a factor lambda polynomial fit to the data
%
% function [err,errTest] = polyreg(x,y,lambda,xT,yT)
    
%
% x = vector of input scalars for training
% y = vector of output scalars for training
% lambda = the regression factor of the polynomial being fit
% xT = vector of input scalars for testing
% yT = vector of output scalars for testing
% errTrain = average squared loss on training
% errTest = average squared loss on testing %
% Example Usage: %
% x = 3*(rand(50,1)-0.5);
% y = x.*x.*x-x+rand(size(x));
% [err] = polyreg(x,y,4); %

model = ((x'*x + lambda*eye(size(x'*x)))\x')*y; errTrain = (1/(2*length(x)))*sum((y-x*model).^2);
if (nargin==5)
errTest = (1/(2*length(xT)))*sum((yT-xT*model).^2);
end