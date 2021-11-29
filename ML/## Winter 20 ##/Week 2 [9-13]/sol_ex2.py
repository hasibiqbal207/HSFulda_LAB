#ex1

def fak(x):
  if x == 0:
    return 1 
  else: 
    return x*fak(x-1) 

for i in range(0,7):
  j = fak(i) ;
  print (f"{i}! = {j}");


# ex2

ex1_1 = [i for i in range(0,11) if i%2 == 0] ;
ex1_2 = [i for i in range(0,101) if i%15 == 0] ;
ex1_3 = [i for i in range(15,0,-1) if i%2 == 1] ;
ex1_4 = ["xx" for i in range(0,5)]
ex1_5 = ["string"+str(i) for i in range(5,15)]
ex1_6 = ["1",2, 3.0, 4] ;
ex1_7 = [i for i in range(0,100) if str(i).find("3") != -1] ;

# ex3

numbers = [i for i in range(0,50)]

def extract1(x):
  return x[0],x[1:] ;

def extract2(x):
  return x[0]+x[-1], x[0]-x[-1], x[0]%x[-1] ;

def sumUp(x):
  acc = 0;
  for el in x:
    acc += el ;
  return acc ;

def extractOdd(x):
  return [x[i] for i in range(0,len(x)) if i%2 == 1] ;

def extractInvert(x):
  return x[-1:0:-1] ;

def invert(x):
  return x[-1::-1] ;

def replaceWith1(x):
  return [1 if el%2 == 1 else el for el in x] ;


print(extract1(numbers)) ;
print(extract2(numbers)) ;
print(sumUp(numbers)) ;
print(extractOdd(numbers)) ;
print(extractInvert(numbers)) ;
print(invert(numbers)) ;
print(replaceWith1(numbers)) ;


# ex4

D = {}

#.1
for i in range(1,11):
  D[i] = str(i) ;

#.2
count = 0
for k in D.keys():
    if count==5:
        break
    print (k);
    count+=1

#.3
def dget(D, key):
    return key in D.keys()

#.4
def dget2(D,k):
    if k in D.keys():
        print('True')
    else:
        print('False')

# ex5
def pr(x,i):
  it = x.__iter__() ;
  for i in range(0,i):
    print (it.__next__());

pr(numbers,5)
pr(ex1_1,3) 
pr(ex1_3,3) 