import numpy as np
import sys
import random

#a
if sys.argv[1] == "ex1a":
    a = np.array([i for i in range(1, 101)])
    a = np.linspace(0, 100, 51)
    a = np.arange(0, 101, 2)
    print(np.shape(a))
    print(a)

#b
if sys.argv[1] == "ex1b":
    b = [[1, 1, 1], [2, 2, 2], [3, 3, 3]]
    print(np.shape(b))

#c
if sys.argv[1] == "ex1c":
    c = np.ones([3,5])*55
    c = np.zeros([3,5])
    c += 55
    print(c)

c = np.full([3, 5], 55)
print(c)

#d
if sys.argv[1] == "ex1d":
    d = np.ones([5,4,3])*random.uniform(0,1)
    d = np.random.uniform(0, 1, (5, 4, 3))
    print(d)
    print(np.shape(d))


