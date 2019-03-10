def f():
  return 7*2/3%4
def g():
  print 15
  x = 12
  def h():
    def s():
      x = 2
      y = -9
      print x
      return x*(-y)//x**x%3+x-y
    s()
  h()
  return x

print f()
print g()
f()
g()
