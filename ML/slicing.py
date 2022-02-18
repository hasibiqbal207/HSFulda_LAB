import sys
import random
import numpy as np

traind = np.random.uniform(0, 255, [2000, 20, 20])
if sys.argv[1] == "ex2a":   
    x = traind[999]
    print(np.shape(x))

if sys.argv[1] == "ex2b":
    x = traind[999]
    x[:,0:5] = 0
    x[:,19:14:-1] = 0
    x[:,-5::] = 0
    print(x)   

if sys.argv[1] == "ex2c":
    x = traind[9]
    print("Min is", x.min(), " Max is ", x.max())
    print("Min is", np.min(x), " Max is ", np.max(x))

if sys.argv[1] == "ex2e":
    x = traind[9]
    e1 = x[::2, :]
    e2 = x[:, ::2]
    e3 = x[::-1, ::-1]
    e4 = x[::-2, ::-2]

if sys.argv[1] == "ex2f":
    # in-place means modifiying original values
    x = traind[9]
    x -= 1
    x *= -1

    # Not in-place solution (Here a new list is created)
    x[:,:] = 1-x


    
