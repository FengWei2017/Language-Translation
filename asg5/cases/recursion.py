def f(x):
    if x == 1:
       print 1
       return 0
    else:
       print  x
       return f(x-1) 
print f(4*2)
