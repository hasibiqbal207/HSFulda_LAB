import numpy as np;
import matplotlib.pyplot as plt ;
import gzip, pickle, sys ;

if __name__ == "__main__":
  with gzip.open("MNIST.pkl.gz") as f:
    data = pickle.load(f) ;
  traind = data['data_train'] ;
  trainl = data['labels_train'] ;
  
  
  
  
 
  
  

  if sys.argv[1] == "1ab":
      print ("Shape of train data is ",traind.shape) ;
      print ("Shape of train labels is ",trainl.shape) ;
      print ("Nr samples: ", traind.shape[0]) ;
      print ("Nr labels: ", trainl.shape[0]) ;
      print ("Numbers per sample: ", traind.shape[1]) ;
      print ("1b")
      print ("Class of sample 1000", trainl[999].argmax()) ;
      sample1000 = traind[999, :,:] ;
      plt.imshow(sample1000.reshape(28,28)) 
      plt.show() ;




  if sys.argv[1] == "1c":
      plt.hist(trainl.argmax(axis=1),label="histogram") ;
      plt.legend()
      plt.show() ;

  if sys.argv[1] == "1d":
      scalar_labels = trainl.argmax(axis=1) ; # 55000
      print("Samples of class 5",(scalar_labels==5).astype("int32").sum()) ;
      # or
      print("Samples of cl 5",trainl.sum(axis=0)[5]) ;
      # or
      print ("# class 5", trainl[:,5].sum()) ;


  if sys.argv[1]=="1e":
    x = np.arange(0,100) ; # 100 elements
    y = trainl.argmax(axis=1)[0:100] ; # 100 elements
    plt.bar(x,y,label="Bar plot of labels") ;
    plt.legend() ;
    plt.show() ;

  if sys.argv[1] == "1f":
      sample10 = traind[9].reshape(28,28) ;
      sample10_flipped_hor = sample10[:,::-1] ;
      sample10_flipped_ver = sample10[::-1,:] ;
        
      fig = plt.figure() ;
      
      fig.add_subplot(1,3,1,title="Original") ;
      plt.imshow(sample10) ;
      
      fig.add_subplot(1,3,2,title="Horizontal") ;
      plt.imshow(sample10_flipped_hor) ;
      
      fig.add_subplot(1,3,3,title="Vertical") ;
      plt.imshow(sample10_flipped_ver) ;
      plt.show() ;

  if sys.argv[1] == "1g":
    scalar_labels = trainl.argmax(axis=1) ;
    mask4 = (scalar_labels == 4) ;
    samples_class4 = traind[mask4] ;
    
    fig = plt.figure() ;
    for i in range(0,4):
      fig.add_subplot(1,4,i+1,title=f"sample {-i}") ;
      plt.imshow(samples_class4[-i-1].reshape(28,28)) ;
    plt.show() ;






  if sys.argv[1] == "1h": 
    random_indices = np.random.randint(0,100,[100]) ;
    random_samples = traind[random_indices] ;

    fig = plt.figure() ;
    for i in range(0,5):
      fig.add_subplot(1,5,i+1,title=f"sample {i}") ;
      plt.imshow(random_samples[i].reshape(28,28)) ;
    plt.show() ;


  if sys.argv[1]== "2ab": 
      x = np.arange(-5,5,0.1) ;
      print (x)
      y = np.sin(x) ;
      plt.plot(x,y,label="sine") ;
      plt.legend() ;
      plt.show() ;

      print ("2b") ;
      x = np.arange(-5,5,0.1) ;
      y = np.sin(x) ;
      plt.scatter(x,y,label="scatter plot of sine") ;
      plt.legend()
      plt.show() ;
      
  if sys.argv[1]== "2c": 
      print ("2c") ;
      x = np.arange(-5,5,0.1) ;
      y = np.sin(x) ;
      plt.bar(x,y,label="bar plot of sine") ;
      plt.legend()
      plt.show() ;

  if sys.argv[1]== "2d": 
      print ("2d") ;
      x = np.arange(-5,5,0.1) ;
      y_sin = np.sin(x) ;
      y_cos = np.cos(x) ;
      plt.plot(x,y_sin,label="sine") ;
      plt.plot(x,y_cos,label="cosine") ;
      plt.legend()
      plt.show() ;

