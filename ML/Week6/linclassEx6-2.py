import numpy as np ;
import requests ;
import os, sys ;
import matplotlib.pyplot as plt ;


# perform conventional gradient descent (GD) for a linear classifier
class LinClass(object):

  ## allocate weight and bias arrays and store ref 2 train data/labels
  def __init__(self, n_in, n_out, X, T):
    self.W = np.ones([n_in,n_out]) * 0.1 ;
    self.b = np.ones([1,n_out])* 0.1 ;
    self.X = X ;
    self.T = T ;
    self.N = X.shape[0] ;

  # softmax, for model function
  def S(self,X):
    e = np.exp(X) ;
    return e/(e.sum(axis=1)).reshape(-1,1) ; # reshape for broadcasting!!

  # the model function of the linear classifier
  def f(self,X):
    return self.S( np.matmul(X,self.W) + self.b ) ;

  # nomal cross-entropy loss. Y is generated by the model function f!
  #def loss(self, Y, T): 
  #  tmp = np.log(Y) * T ;
#    return -np.mean(np.sum(tmp,axis=1)) ;

 # Mean Square Error Calculation
  def loss(self, Y, T): 
    mse = (np.square(Y-T));
    return np.mean(np.sum(mse,axis=1)) ;

  # gradient of loss w.r.t. parameter self.b
  def dLdb(self,Y,T):
    return 2*np.mean((Y-T),axis=0) ;

  # gradient of loss w.r.t. parameter self.W
  def dLdW(self, X, Y, T):
    diff = (Y-T).reshape(-1,1,10) ;  #     N,   1, 10
    x    = X.reshape(-1,784,1) ;     #     N, 784,  1
    return 2*np.mean(diff*x,axis=0) ; # --> broadcasting on  axes 1 and 2!!
    
  # performs a single gradient descent step: updates self.W and self.b ONCE
  # returns the loss computed from f(X) and T
  def train_step(self, X, T, eps):
    Y = self.f(X) ;
    loss = self.loss(Y,T) ;
    dLdb = self.dLdb(Y,T) ;      
    dLdW = self.dLdW(X, Y, T) ;  
    self.b -= eps * dLdb ;       ## b(i+1) = b(i) - eps * gradL
    self.W -= eps * dLdW ;       ## same
    return loss ;

  # perform multiple gradient descent steps and display loss.
  def train(self,max_it,eps):
    for it in range(0,max_it):
      print ("it=", it, "loss=", self.train_step(self.X, self.T, eps)) ;

# -----------------------------------------------------------------------

# perform proper assessment of generalization using test set
class LinClassTest(LinClass):

  def train(self,max_it,eps, X_test, T_test):
    self.train_loss = np.zeros([max_it]) ;
    self.test_loss = np.zeros([max_it]) ;
    for it in range(0,max_it):
      self.train_loss[it] = self.train_step(self.X, self.T,eps) ;
      print ("it=", it, "loss=", self.train_loss[it]) ;
      if it%50 == 0:
        self.test_loss[it] = self.loss_measure(X_test, T_test) ;
        print ("**Test loss", self.test_loss[it]) ;
   
  # convenience function   
  def loss_measure(self, X, T):
    return self.loss(self.f(X), T) ;
    
  # convenience function
  def accuracy_measure(self, X, T):
    Y = self.f(X) ;
    eq = np.argmax(Y, axis=1) == np.argmax(T, axis=1) ;
    return eq.astype("float32").mean() ;

  # plot train and test losses AFTER training
  def plot(self):
    f,ax = plt.subplots(1,1) ;
    max_it = self.train_loss.shape[0] ;
    ax.plot(range(0,max_it),self.train_loss, label="train") ;
    ax.scatter(range(0,max_it),self.test_loss, c="red",s=80, label="test") ;
    ax.set_xlim(0,max_it) ;
    ax.set_ylim(0.1,2.5) ;
    ax.legend(fontsize=20)
    ax.set_xlabel("Iteration", fontsize=25) ;
    ax.set_ylabel("Loss", fontsize=25) ;
    plt.show() ;
   
# -----------------------------------------------------------------------
#

if __name__ == "__main__":
  ## download MNIST if not present in current dir!
  if os.path.exists("./mnist.npz") == False:
    print ("Downloading MNIST...") ;
    fname = 'mnist.npz'
    url = 'http://www.gepperth.net/alexander/downloads/'
    r = requests.get(url+fname)
    open(fname , 'wb').write(r.content)
  
  ## load data into numpy array and reshape appropriately
  data = np.load("mnist.npz")
  traind = data["arr_0"] ;
  testd = data["arr_1"] ;
  trainl = data["arr_2"] ;
  testl = data["arr_3"] ;
  print ("Train data shape: ", traind.shape, "test data shape:", testd.shape) ;
  print ("Train label shape: ", trainl.shape, "test label shape:", testl.shape) ;
  traind = traind.reshape(-1,784)
  testd = testd.reshape(-1,784)


  N = 100
  lc = LinClassTest(784,10, traind[0:N], trainl[0:N]) ;
  lc.train(500, 0.01, testd, testl) ;

  # check for the first 10 samples from traind/trainl whether predictionbs are correct
  print ("Predictions on train set: ") ;
  print(lc.f(traind[0:10]).argmax(axis=1),trainl[0:10].argmax(axis=1))
  lc.plot() ;

  # check for the first 10 samples from testd/testl whether predictionbs are correct
  print ("Predictions on test set: ") ;
  print(lc.f(testd[0:10]).argmax(axis=1),testl[0:10].argmax(axis=1))




