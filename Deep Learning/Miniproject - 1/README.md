Our final ResNet model has the following characteristics -

• Training data vs Testing data ratio split = 10:1

• Optimizer: AdamW

• Learning Rate: 0.001

• Weight Decay: 0.0001

• Activation Function: ReLU

• Batch Size: 128

• Residual Layers: N = 2

• Residual blocks in each of the residual layers: B = [8,8]

• Channel width of each residual layer: C = [64, 128]

• Kernel size applied across each residual block across the convolutional network: F = 3

• Kernel size applied across the skip connections of the residual blocks: K = 1

• Average pooling applied between the convolutional layer and the FC layer: P = 4

• Dropout = 0.5

• Random Horizontal Flip: Probability = 0.5

• Random Cropping: Size = 32, Padding = 4

• Normalization with Mean = [0.4914, 0.4822, 0.4465], Variance = [0.2023, 0.1994, 0.2010]

• Number of Parameters = 2,905,792

• Number of Iterations = 50
