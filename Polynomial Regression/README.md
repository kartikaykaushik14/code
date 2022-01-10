Problem Statement:
Consider the problem of fitting a polynomial function. Assume that we wish to find a one dimensional function that takes a scalar input and outputs a scalar. Develop code that finds the parameters that minimizes the risk on a data-set. 

The dataset includes a matrix x, corresponding to the scalar features and a matrix y, corresponding to the scalar labels, and a matrix y, corresponding to the scalar labels. Fit a polynomial model to the given data for various choices for d, where d is the degree of the polynomial. 

Which values(s) of d seems somewhat more reasonable? Please justify your answer using some empirical measure. 

It is easy to overfit the data when using polynomial regression. As a result, use cross-validation by randomly splitting the data-set into two halves to select the complexity of the model (in this case, the degree of the polynomial). Include a plot showing the training and testing risk across various choices of d, and plot your function overlaid on the data for the best choice of d according to the cross-validation.

Steps to Run:
1. Download the package
2. Run crossfitting.m and crossvalidation.m in MATLAB
3. Observe the graphs and results