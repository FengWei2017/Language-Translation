x=3
y=-6
def f():
  x=10
  y=x
  y=x*y-x/y
  print x
  print y
  return y**x
  def g():
    x=-3
    x=x+1
    print x
    return 99
  g()

f()
f()
print x
print y
