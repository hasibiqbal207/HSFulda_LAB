import numpy as np
import imageio ;
import sys, os ;

import matplotlib.pyplot as plt ;

"""
# TRICKS & USEFUL STUFF:
# access cmd liner parameters
DIR = "./DATA" ;
DIR = sys.argv[1] ;
print ("Cmd line arg 1 was ", sys.argv[1]) ;

# query for all files in a directory
print (os.listdir(DIR)) ;
allFiles = os.listdir(sys.argv[1]) ;
pngFiles = [f for f in allFiles if f.find(".png") != -1] ;

# determine data dimensions
nrPics = len(pngFiles) ;
imgSize = imageio.imread(DIR+"/"+pngFiles[0]).shape ;
rowLen = np.prod(imgSize) ;
print (f"nrPics={nrPics}, rowLen={rowLen}") ;

# extract class
# a) extract 1st character from name
name = pngFiles[10] ;
class_char = name[0] ;
class_int = int(class_char) ;
# b) use split()
name = pngFiles[10] ;
class_str = name.split("-")[0] ; # returns a list of strings, select el 0
class_int = int(class_str) ;

# subsample/shorten pngFiles list
pngFiles = pngFiles [0::10] ;

exit() ;
"""

# takes name of directory and returns X,T as numpy arrays
def read_files(path):

  # list of ALL files in directory 'path'
  files = os.listdir(path) ;

  # keep only files with .png in their name
  pngFiles = [ f for f in files if f.find(".png") != -1] ;

  # HACK, comment out!!
  pngFiles = pngFiles[0::10] ;

  # nr of samples = nr of files
  nrPics = len(pngFiles);

  # extract list/array of scalar classes for all png files
  scalarClasses_list = [int (s.split("-")[0]) for s in pngFiles ]
  scalarClasses = np.array(scalarClasses_list) ;
  nrClasses = scalarClasses.max() + 1 ;

  testimg = imageio.imread(path+"/"+pngFiles[0]).ravel() ;
  rowSizeX = testimg.shape[0] ;

  # pre-allocate to be more efficient
  X = np.zeros([nrPics,rowSizeX]) ;
  T = np.zeros([nrPics, nrClasses]) ;

  # fancy indexing
  # axis 0 --> 0 1 2 3 4 5 6 7 8 9
  # axis 1 --> 5 1 0 9 8 4 5 3 3 1
  T [range(0,nrPics),scalarClasses] = 1 ;
  # NOT the same as T [:,scalarClasses] = 1 ;  

  #index = 0 ;
  #for f in pngFiles:
  #  arr = imageio.imread(path+"/"+f).ravel() ;
  #  X[index, :] = arr ;
  #  index += 1 ;

  for index,f in enumerate(pngFiles):
    arr = imageio.imread(path+"/"+f).ravel() ;
    X[index, :] = arr ;
  
  return X,T ;

if __name__ == "__main__":
  X,T = read_files(sys.argv[1]) ;
  print (f"Shapes: {X.shape}, {T.shape}") ;
  print (f"Minmax: {X.min()}, {X.max()}") ;
  
  # 1 compute min and max per pixel
  # assume image is 28x28
  X [:,15*28 + 15] *= 100 ;
  mins = X.min(axis=0) ; # 1D np vector
  maxes = X.max(axis=0) ; # 1D np vector
  ranges = maxes-mins ;
  plt.imshow(ranges.reshape(28,28)) ;
  plt.show() ;

  # 1, bonus. Detect whether some image have aberrant ranges
  minsPerImage = X.min(axis=1) ; # ~ 50000
  maxesPerImage = X.max(axis=1) ; # ~ 50000
  rangesPerImage = maxesPerImage - minsPerImage ;
  # how many images have a range < 100?
  print ((rangesPerImage < 100).sum()) ;

  # 2 compute occurrences for each class
  print (T.sum(axis=0)) ;

  # 3 print scalar classes
  print (T.argmax(axis=1)) ;

  # shuffle data, just for fun
  indices = np.arange(0,X.shape[0]) ;
  np.random.shuffle(indices) ;
  X = X[indices,:] ;
  T = T[indices,:] ;





    

