function [theta_new, average_risk, average_error, count] = gradient(X,Y,eta,epsilon)

count = 1;
theta_old = rand(1,size(X,2));
riskDiff = 0;
average_risk = zeros(size(Y));
average_error = zeros(size(Y));

for i=1:size(X(:,1))
    riskDiffElement = (X(i,:)/(1 + exp((-1)*theta_old * X(i,:)'))) - Y(i,:)*X(i,:);
    riskDiff = riskDiff + riskDiffElement;
end

step = riskDiff/length(Y);

theta_new = theta_old - (eta * step);

while(norm(theta_new - theta_old) >= epsilon)
    theta_old = theta_new;
    riskDiff = 0;
    for i=1:size(X(:,1))
        riskDiffElement = (X(i,:)/(1 + exp((-1)*theta_old * X(i,:)'))) - Y(i,:)*X(i,:);
        riskDiff = riskDiff + riskDiffElement;
    end

    step = riskDiff/length(Y);

    theta_new = theta_old - (eta * step);
    
    risk = 0;
    error = 0;
    
    for i=1:size(X(:,1))
        func = 1/(1+exp((-1)*theta_new*X(i,:)'));
        riskElement = ((Y(i) - 1)*log(1-func)) - ((Y(i))*log(func));
    
        if(isnan(riskElement))
            riskElement = 0;
        end

        risk = risk + riskElement;
        
        if(func < 0.5)
            check = 0;
        else
            check = 1;
        end
        
        if(check ~= Y(i))
            error = error + 1;
        end
    end

    average_risk(count) = risk/length(Y);
    average_error(count) = error/length(Y);
    fprintf('iteration = %d, risk = %f, error %f\n',count, average_risk(count), average_error(count));

    count = count + 1;
end