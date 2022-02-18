import tensorflow as tf, numpy as np ;

x_1 = tf.constant([1,2,3],dtype=tf.float64) ;
x_2 = tf.constant([2,0,2],dtype=tf.float64) ;


# 1
print ("EX1") ;

def f(x):
  return tf.reduce_sum(tf.pow(tf.stack([x,x,x,x]), [1.,2.,3.,4.])) ;

print ("1a: ", f(0.),f(1.),f(2.)) ;

# 1b
x = tf.Variable(-1.0) ;
with tf.GradientTape() as gt:
  y = f(x) ;
fprime = gt.gradient(y,x) ;
print ("1b: fprime=",fprime) ;

# 1c
print ("1c: ", fprime**2.) ;

# 2
#2a
def f(x):
  return tf.reduce_sum(x**3) ;

print ("2a: f(x1),f(x2) = ", f(x_1), f(x_2)) ;

# 2b
x = tf.Variable(initial_value=[0,0,0],dtype=tf.float64) ;
x.assign(x_1) ;
with tf.GradientTape() as gt:
  y = f(x) ;
gradf = gt.gradient(y,x) ;
print ("2b: gradf=", gradf.numpy()) ;

# 2c
print ("2c: P.D. w.r.t. x_1=", gradf.numpy()[0]) ;


# 3
W = tf.constant(np.array([1,2,-1,1,0,1.]).reshape(3,2)) ;

def g(x):
  return tf.matmul(W,x) ;

def f(x):
  return tf.reduce_sum(x) ;

# 3a

# commmon trick to write array constants. First create a linear np array, 
# then reshape it. Possible since np stores array row-wise in memory.
x_1 = tf.constant(np.array([1,2.]).reshape(2,1),dtype=tf.float64)
x_2 = tf.constant(np.array([2,0.]).reshape(2,1),dtype=tf.float64)
print ("3a: h(x1) = ", f(g(x_1))) ;
print ("3a: h(x2) = ", f(g(x_2))) ;

# 3b
x = tf.Variable(dtype=tf.float64, initial_value=x_1) ;
with tf.GradientTape() as gt:
  y = f(g(x)) ;
gradf = gt.gradient(y,x) ;
print ("3b: dfdx", gradf.numpy()) ;

# 3c
with tf.GradientTape() as gt:
  gt.watch(W) ; # very important, only variables are automatically tracked
                # so taking grads wrt tensor or constant requires manual watching 
  y = f(g(x)) ;
gradf = gt.gradient(y,W) ;
print("3c: dfdW",gradf.numpy()) ;

 
