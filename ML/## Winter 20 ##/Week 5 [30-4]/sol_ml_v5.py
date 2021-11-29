import numpy as np;
import matplotlib.pyplot as plt ;
import gzip, pickle, sys ;
import math ;

if __name__ == "__main__":
  if sys.argv[1][0] == "1":
    with gzip.open("MNIST.pkl.gz") as f:
      data = pickle.load(f) ;
    traind = data['data_train'].reshape(-1,28,28) ;
    trainl = data['labels_train'] ;  













  if sys.argv[1] == "1a":
    means = traind.mean(axis=(1,2))
    plt.scatter(np.arange(0,traind.shape[0]),means);
    plt.show() ;



  if sys.argv[1] == "1b":
    means = traind.mean(axis=(1,2)) ; # (55000,)
    mask = means > 0.3 ; # boolean mask of shape (55000,)
    copy = traind[mask]
    print ("FAT samples: ", copy.shape)
    fig = plt.figure() ;
    fig.add_subplot(1,3,1) ;
    plt.imshow(copy[0])
    fig.add_subplot(1,3,2) ;
    plt.imshow(copy[1])
    fig.add_subplot(1,3,3) ;
    plt.imshow(copy[2])
    plt.show() ;

  if sys.argv[1] == "1c":
    avg = traind.mean(axis=0) ; # 28,28
    plt.imshow(avg,label="Average image") ; 
    plt.show() ;
    
  if sys.argv[1] == "1d":
    scalar_labels = trainl.argmax(axis=1) ; # 55000
    mask = (scalar_labels==5) ;
    avg5 = (traind[mask]).mean(axis=0) ;
    plt.imshow(avg5,label="Average5") ; 
    plt.show() ;

  if sys.argv[1] == "3": 
    def sm(x):
      e = np.exp(x) ;
      return e/e.sum() ;

    x1 = np.array([-1,-1,5]);
    x2 = np.array([1,1,2]);
    print (f"S({x1})=",sm(x1)) ;
    print (f"S({x2})=",sm(x2)) ;

  if sys.argv[1] == "4": 
    def ce(y,t): # y is model output, t is target
      kstar = t.argmax() ;
      return -(np.log(y) * t).sum() ;
      return -math.log(y[kstar]) ;

    t = np.array([0,0,1]);
    x1 = np.array([.1,.1,.8]);
    x2 = np.array([.3,.3,.4]);
    x3 = np.array([.8,.1,.1]);
    print (f"CE({x1})=",ce(x1,t)) ;
    print (f"CE({x2})=",ce(x2,t)) ;
    print (f"CE({x3})=",ce(x3,t)) ;
