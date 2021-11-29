import tensorflow as tf ;
import numpy as np ;
import pickle, gzip ;

B = 100 ;
LS = 500 ;
CLASSES = 10 ;
EPOCHS = 0.1 ;
EPS = 0.01 ;

# model function, takes input matrix X = A^{(0)}
def f(X):
  # first affine layer
  A1 = tf.matmul(X, W1) + b1 ;
  # relu layer
  A2 = tf.nn.relu(A1) ;
  # affine layer
  A3 = tf.matmul(A2, W3) + b3 ;
  # relu layer
  A4 = tf.nn.relu(A3) ;
  # output layer, affine
  Y = tf.matmul(A4, W5) + b5 ;

  # thoeretically: softmax layer
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

  W3 = tf.Variable(tf.random.uniform([LS,LS], -0.01, 0.01)) ;
  b3 = tf.Variable(tf.random.uniform([1,LS], -0.001, 0.001)) ;

  W5 = tf.Variable(tf.random.uniform([LS,CLASSES], -0.001, 0.001)) ;
  b5 = tf.Variable(tf.random.uniform([1,CLASSES], -0.001, 0.001)) ;

  # training loop
  iterationsPerEpoch = nrTrainSamples // B ;

  # create optimizer object
  varList = [W1,b1,W3,b3,W5,b5] ;
  opt = tf.keras.optimizers.Adam(learning_rate = EPS) ;

  it = 0 ;
  for (X,T) in traindTF_batches:
    with tf.GradientTape() as g:
      Y = f(X) ;
      ce = loss(Y,T) ;
    #print (varList)
    gradList = g.gradient(ce,varList) ;

    opt.apply_gradients(zip(gradList, varList)) ;
    print(f"Iteration {it}: train loss = {ce.numpy()}") ;
    it += 1 ;
    if it > EPOCHS*iterationsPerEpoch: break ;


  # ----------- confusion matrix computation ------------------
  # compute confusion matrix on test set
  # in batches, so as not to exceed memory limits
  # pre-allocate CM
  cm = np.zeros([CLASSES,CLASSES]) ;
  it = -1 ;
  iterationsPerEpoch = nrTestSamples // B ;
  for (X,T) in  testdTF_batches:
    it += 1 ;
    Y = f(X) ;
    # scalar model outputs and class labels
    YHat = tf.argmax(Y, axis=1) ;
    THat = tf.argmax(T, axis=1) ;

    # hard to avoid the for here... possible but less clear...
    for (yhat,that) in zip(YHat,THat):
      cm[int(that),int(yhat)] += 1 ;
    # we iterate exatcly one epoch = all test samples
    if it > iterationsPerEpoch: break ;

  print (cm) ;






