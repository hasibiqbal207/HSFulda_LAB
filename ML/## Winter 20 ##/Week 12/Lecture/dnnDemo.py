import tensorflow as tf ;
import numpy as np ;
import pickle, gzip ;

B = 100 ;
LS = 500 ;
CLASSES = 10 ;
EPOCHS = 10 ;
EPS = 0.01 ;


def f(X):
  A1 = tf.nn.relu(tf.matmul(X, W1) + b1) ;
  A2 = tf.nn.relu(tf.matmul(A1, W2) + b2) ;
  Y = tf.matmul(A2, W3) + b3 ;
  
  return Y ;

def loss(Y,T):
  return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=Y, labels=T)) ;


if __name__=="__main__":
  with gzip.open("./datasets/MNIST.pkl.gz") as df:
    data = pickle.load(df)
  
  samples = data["data_train"] ;
  dataShape = samples.shape ;
  labels = data["labels_train"] ;
  print ("Data shape is ", dataShape) ;

  # creation; shuffling
  nrSamples = dataShape[0]
  allDataTF = tf.data.Dataset.from_tensor_slices((samples, labels)).shuffle(nrSamples) ;
  print (dir(allDataTF))

  # train/test split
  nrTrainSamples = int(nrSamples*0.7) ;
  nrTestSamples = int(nrSamples*0.3) ;
  traindTF = allDataTF.take(nrTrainSamples) ;
  testdTF = allDataTF.skip(nrTrainSamples) ;

  # batching
  traindTF_batches = traindTF.batch(batch_size=B, drop_remainder=True).repeat() ;
  testdTF_batches = testdTF.batch(batch_size=B, drop_remainder=True).repeat() ;

  # create model variables
  Z0 = int(np.prod(dataShape[1:])) ;
  W1 = tf.Variable(tf.random.uniform([Z0,LS], -0.001,0.001)) ;
  b1 = tf.Variable(tf.random.uniform([1,LS], -0.001,0.001)) ;

  W2 = tf.Variable(tf.random.uniform([LS,LS], -0.01, 0.01)) ;
  b2 = tf.Variable(tf.random.uniform([1,LS], -0.001, 0.001)) ;

  W3 = tf.Variable(tf.random.uniform([LS,CLASSES], -0.001, 0.001)) ;
  b3 = tf.Variable(tf.random.uniform([1,CLASSES], -0.001, 0.001)) ;

  # training loop
  iterationsPerEpoch = nrTrainSamples // B ;

  # create optimizer object
  varList = [W1,b1,W2,b2,W3,b3] ;
  opt = tf.keras.optimizers.Adam(learning_rate = EPS) ;

  it = 0 ;
  for (X,T) in traindTF_batches:
    with tf.GradientTape() as g:
      Y = f(X) ;
      ce = loss(Y,T) ;
    gradList = g.gradient(ce,varList) ;

    opt.apply_gradients(zip(gradList, varList)) ;
    print(f"Iteration {it}: train loss = {ce.numpy()}") ;
    it += 1 ;
    if it > EPOCHS*iterationsPerEpoch: break ;


  



