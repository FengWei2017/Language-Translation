def factorial_rec(n):
  if n == 1:
    return 1
  else: 
    print n*factorial_rec(n-1)
    return n*factorial_rec(n-1)

factorial_rec(4)
