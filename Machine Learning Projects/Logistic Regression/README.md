Problem Statement:
Implement a linear logistic regression algorithm for binary classification in Matlab using gradient descent. Your code should accept a dataset {(x1,y1),...,(xN,yN)} where xi ∈ Rd and yi ∈ {0, 1} and find a parameter vector θ ∈ Rd for the classification function (exponential activation function) which minimizes the empirical risk with logistic loss

Since you are using gradient descent, you will have to specify the step size η and the tolerance ε. Pick reasonable values for η and ε to then use your code to learn a classification function for the dataset in "data.mat"

Use the whole data set as training. Show with figures the resulting linear decision boundary on the 2D X data. Show the binary classification error and the empirical risk you obtained throughout the run from random initialization until convergence. Note the number of iterations needed for your choice of η and ε.

Steps to Run:
1. Download the package
2. Run logistic regression.m in MATLAB
3. Observe the graphs and results