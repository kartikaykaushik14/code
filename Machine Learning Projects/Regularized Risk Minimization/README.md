Problem Statement:
Develop code that learns a multi-variate regression function. 

The dataset includes a matrix x, corresponding to the scalar features and a matrix y, corresponding to the scalar labels, and a matrix y, corresponding to the scalar labels. 

Use an l2 loss function to penalize the complexity of the model, e.g. minimize the risk 

Use two-fold cross validation to find the best value for λ. Include a plot showing training and testing risk across various choices of λ. A reasonable range for this data set would be from λ = 0 to λ = 1000. Also, mark the λ which minimizes the testing error on the data set.

What do you notice about the training and testing error?

Steps to Run:
1. Download the package
2. Run crossvalidation.m in MATLAB
3. Observe the graphs and results