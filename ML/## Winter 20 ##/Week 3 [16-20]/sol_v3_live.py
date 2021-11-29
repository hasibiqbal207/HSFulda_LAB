import numpy as np ;

print ("1a") ;
x = np.arange(0,100,2) ;
x = np.array([i for i in range(0,101,2)]) ;
#x = np.array(range(0,101,2)) ;
print (x) ;

print ("1b") ;
x = np.array([[1,1,1],[2,2,2],[3,3,3]]) ;
print (x) ;
x1 = np.ones([3,3]) ;
v = np.array([1,2,3]).reshape(3,1) ;
x = x1 * v ;  # 3,3 * 3,1
print (x) ;

print ("1c") ;
x = np.ones([3,5])*55 ;
x = np.full([3,5],55) ;
print (x) ;

print ("1d") ;
x = np.random.uniform(0,1,[5,4,3]) ;
#x = np.random.randint(0,10,[5,4,3]) ;
print (x) ;

########################
traind = np.random.uniform(0,255,[2000,20,20]) ;
#2a
print("2a")
x = traind[999] ;
x = traind[999,:] ;
x = traind[999,:,:] ;
print (x.shape) ;

print("2b")
sample1000 = x ;
sample1000[0:5,:] = 0 ;
sample1000[-5: :,:] = 0 ;
print (sample1000)

print("2c")
sample10 = traind[10,:,:] ;
print("minmax=",sample10.min(), sample10.max()) ;

print("2e")
sample10 = traind[10,:,:] ;
x1 = sample10[0::2,:] ;
x1 = sample10[::2,:] ;
x1 = sample10[::2] ;

x2 = sample10[:,0::2] ;
x3 = sample10[::-1,::-1] ;

x4 = sample10[::-2,::-2]
print (x4) ;

print ("2f") ;
traind *= -1 ; # - traind
traind += 1; # - traind + 1 = 1-traind

print ("3a")
print(traind[:,0,0].sum()) ;

print ("3b")
print(traind[:,0,0].mean()) ; 

print ("3c")
print(traind.mean(axis=0)) ; 

print ("3d")
print(traind.max(axis=2)) ; 

print ("3e")
print(traind.mean(axis=2)) ; 

print ("4a")
onerow = np.arange(1,21);
print ("shape is ", onerow.shape) ;
onerow = onerow.reshape(1,1,20) ;
print (onerow.shape) ;
# add 1,1,20 to 2000,20,20
traind4a = traind + onerow ;

print ("4b")
onerow = np.arange(1,21);
print ("shape is ", onerow.shape) ;
onerow = onerow.reshape(1,20,1) ;
print (onerow.shape) ;
# add 1,1,20 to 2000,20,20
traind4b = traind + onerow ;

print ("4c")
sample0 = traind[0] ;
#sample0 = traind[0,:,:] ;
print("sampel0 shape is ",sample0.shape) ;
traind4c = traind + sample0.reshape(1,20,20) ;
# add 1,20,20 to 2000,20,20



#
print("5a")
onerow = np.arange(1,21);
mask = onerow < 10 ; # boolean mask
print("mask is", mask) ;
print(onerow[mask]) ;
# mask and array dimension must agree

print("5c")
onerow = np.arange(1,21);
print("take out 3 elements", onerow[[1,5,19]] ) ;
onerow[[1,5,19]] = 0 ;
print(onerow) ;
