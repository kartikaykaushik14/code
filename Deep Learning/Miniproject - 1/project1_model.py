import torch
import torch.nn as nn
import torch.nn.functional as F

para_sum = 0

class BasicBlock(nn.Module):

    def __init__(self, in_planes, planes, stride=1):
        super(BasicBlock, self).__init__()
        self.conv1 = nn.Conv2d(
            in_planes, planes, kernel_size=3, stride=stride, padding=1, bias=False)
        
        
        self.drop = nn.Dropout(0.5)
        
        global para_sum
        print("_____BasicBlock parameters " + str(3*3*planes*in_planes)) #testprint
        para_sum += 3*3*planes*in_planes #parameter sum

        self.bn1 = nn.BatchNorm2d(planes)
        self.conv2 = nn.Conv2d(planes, planes, kernel_size=3,
                               stride=1, padding=1, bias=False)
        
        print("_____BasicBlock parameters " + str(3*3*planes*planes)) #testprint
        para_sum += 3*3*planes*planes #parameter sum

        self.bn2 = nn.BatchNorm2d(planes)

        self.shortcut = nn.Sequential()
        if stride != 1 or in_planes != planes:
            self.shortcut = nn.Sequential(
                nn.Conv2d(in_planes, planes,
                          kernel_size=1, stride=stride, bias=False),
                nn.BatchNorm2d(planes)
            )
            print("_____SkipBlock parameters " + str(1*1*in_planes*planes)) #testprint
            para_sum += 1*1*planes*in_planes #parameter sum

    def forward(self, x):
        out = F.relu(self.bn1(self.conv1(x)))

        out = self.drop(out)

        out = self.bn2(self.conv2(out))
        out += self.shortcut(x)
        out = F.relu(out)
        return out



class ResNet(nn.Module):
    def __init__(self, block, num_blocks, num_classes=10):
        super(ResNet, self).__init__()

        self.in_planes = 64
        print("Input Channels " + str(self.in_planes))

        self.conv1 = nn.Conv2d(3, self.in_planes, kernel_size=3,
                               stride=1, padding=1, bias=False)
        
        global para_sum
        print("_____InputLayer parameters " + str(3*3*self.in_planes*3)) 
        para_sum += 3*3*self.in_planes*3 

        self.bn1 = nn.BatchNorm2d(self.in_planes)
        self.layer1 = self._make_layer(block, 64, num_blocks[0], stride=1)
        self.layer2 = self._make_layer(block, 128, num_blocks[1], stride=2)

        self.linear = nn.Linear(2048, num_classes)

        print("_____LinearLayer parameters " + str(2048*num_classes)) 
        para_sum += (2048*num_classes) 
        print("_____TOTAL PARASUM  " + str(para_sum))



    def _make_layer(self, block, planes, num_blocks, stride):
        strides = [stride] + [1]*(num_blocks-1)
        layers = []
        for stride in strides:
            layers.append(block(self.in_planes, planes, stride))
            self.in_planes = planes
        return nn.Sequential(*layers)

    def forward(self, x):
        out = F.relu(self.bn1(self.conv1(x)))
        out = self.layer1(out)
        out = self.layer2(out)
        out = F.avg_pool2d(out, 4)
        out = out.view(out.size(0), -1)
        out = self.linear(out)
        return out

import numpy as np
import torchvision

normalize_transform = torchvision.transforms.Compose([
    torchvision.transforms.ToTensor(),
    torchvision.transforms.Normalize([0,0,0], [1,1,1])
])

orgtrainingdata = torchvision.datasets.CIFAR10(root = 'data/', train = True, download = True, transform = normalize_transform)

train_transform = torchvision.transforms.Compose([
    torchvision.transforms.RandomHorizontalFlip(p=0.5),
    torchvision.transforms.RandomCrop(32, padding=4),
    torchvision.transforms.ToTensor(),
    torchvision.transforms.Normalize([0,0,0], [1,1,1], inplace=True)
])


modtrainingdata = torchvision.datasets.CIFAR10(root = 'data/', train = True, download = True, transform = train_transform)

trainingdata = torch.utils.data.ConcatDataset([modtrainingdata, orgtrainingdata])

testdata = torchvision.datasets.CIFAR10(root = 'data/', train = False, download = True, transform = normalize_transform)
print(len(testdata))
print(len(trainingdata))

trainDataLoader = torch.utils.data.DataLoader(trainingdata, batch_size=128, shuffle=True)
testDataLoader = torch.utils.data.DataLoader(testdata, batch_size=128, shuffle=False )

myConfig = [8, 8]
print("Layers: " + str(myConfig))
model = ResNet(BasicBlock, myConfig).cuda()
Loss = torch.nn.CrossEntropyLoss()

LR = 0.001
print("Learning Rate = " + str(LR))
WD = 0.0001
print("Weight Decay = " + str(WD))
optimizer = torch.optim.AdamW(model.parameters(), lr=LR, weight_decay=WD)

para_sum = 0

train_loss_history = []
test_loss_history = []

epochs = 60
max_val = 0
max_idx = 0

for epoch in range (epochs):
  train_loss = 0.0
  test_loss = 0.0
  test_accuracy = 0.0

  for i, data in enumerate(trainDataLoader):
    images, labels = data
    images = images.cuda()
    labels = labels.cuda()
    optimizer.zero_grad()
    predicted_output = model(images)
    fit = Loss(predicted_output,labels)
    fit.backward()
    optimizer.step()
    train_loss += fit.item()
  
  for i, data in enumerate(testDataLoader):
    with torch.no_grad():
      images, labels = data
      images = images.cuda()
      labels = labels.cuda()
      predicted_output = model(images)
      fit = Loss(predicted_output, labels)
      test_loss += fit.item()
      test_accuracy += (torch.eq(torch.max(predicted_output, 1)[1],labels).sum()).data.cpu().numpy()

  train_loss = train_loss/len(trainDataLoader)
  test_loss = test_loss/len(testDataLoader)
  test_accuracy = 100 * (test_accuracy/10000)

  if (test_accuracy > max_val):
    max_val = test_accuracy
    max_idx = epoch
    torch.save(model.state_dict(), './project1_model.pt')
  
  print('Epoch %d, Train loss %.4f, Test loss %.4f, test_accuracy %.4f'%(epoch, train_loss, test_loss, test_accuracy))

  train_loss_history.append(train_loss)
  test_loss_history.append(test_loss)

print("________________________")
print("Max accuracy = %.4f in epoch = %d"%(max_val, max_idx))
print("_________Training Loss_______________")
print(train_loss_history)
print("_________Testing Loss_______________")
print(test_loss_history)