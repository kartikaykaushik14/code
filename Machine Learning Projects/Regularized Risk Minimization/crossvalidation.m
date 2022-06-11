load('data.mat');

[index] = crossvalind('Kfold',size(x,1),2);
xTrain = x(index==1);
yTrain = y(index==1);
xTest = x(index==2);
yTest = y(index==2);

errTrainList=zeros(100);
errTestList=zeros(100);
modelList={zeros(100)};

for i=1:100
    [errTrain,model,errTest] = polyreg(xTrain,yTrain,i,xTest,yTest);
    errTrainList(i) = errTrain;
    errTestList(i) = errTest;
    modelList{i} = model;
end

[M,I] = min(errTestList);
fprintf('Most optimum value of d = %i\n', I(:,1));

close all;
x = linspace(1,100,100);
plot(x,errTrainList,x,errTestList);
plot(x,errTrainList,x,errTestList);

hold on
plot(I(:,1),M(:,1),'r*')

title('Training vs Testing Error for different degrees of polynomial');
legend('train error', 'test error');
xlabel('Degree of Polynomial - 1');
ylabel('Average Squared Loss');
print('Train_Vs_Test','-dpng');