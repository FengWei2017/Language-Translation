def f(x,y=99,z=100):
    print x
    print y
    print z
    def g():
        y=100000
        print y
    g()
    
      
f(1,2)
f(1)
print f(3)
