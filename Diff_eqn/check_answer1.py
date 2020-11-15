#Intro: Solving a differential equation of the form u'' + 4u=f(t)
#       f(t) is periodic. f(t) = 2t, when 0 t < 2
# 


import math
from math import cos, pi, pow
t=float(input("Enter t="))
#Calculate value of the function. Then calculate value of the function according to fourier series. 
#Notice if the difference between the values is satisfactory. 
##Compute the value using function. 
def f(t):
	if -2.0<t<0.0:
		return -2.0*t
	elif 0.0<t<2.0:
		return 2.0*t

print("Expected value=",f(t))
##Compute the value using Fourier. The Fourier series was computed using sympy package.   
## This was done using Diff_eqn\compute_fourier1.py. Mainly these lines were used 
## s = fourier_series(Piecewise((-2 * t, And(-2 < t, t < 0)), (2 * t, And(0 < t, ##t < 2)), (0, True)), (t, -2, 2))
## print(s.truncate(3))

print("Sympy computed value=",-16*cos(pi*t/2)/pi**2 - 16*cos(3*pi*t/2)/(9*pi**2) + 2)

#Solve the equation manually to find the function. 
# Calculate the left side of the equation using the function and its derivatives. 
def fun_x(n,t):
	numerator = 32*(pow(-1,n)-1)*cos((n*pi*t)/2.0)
	denominator = ((n*pi)**2)*(16-(n*pi)**2)
	return numerator/denominator

#print("x when n=1",fun_x(1,t))
four_x=4.0*(fun_x(1,t)+ fun_x(3,t)+fun_x(5,t)+fun_x(7,t)+fun_x(9,t)+.5);
print("four_x",four_x)

#due_to_2 = 4*0.5
#calculate the derivative of the derivative of the found function
def x_prime_prime(n,t):
	numerator = -8*(pow(-1,n)-1)*cos((n*pi*t)/2.0)
	#denominator = (4-(n*pi)**2)
	denominator = (16-(n*pi)**2) 
	return numerator/denominator

x_p_p=(x_prime_prime(1,t)+ x_prime_prime(3,t)+x_prime_prime(5,t)+x_prime_prime(7,t)+x_prime_prime(9,t));
print("x_p_p=",x_p_p)
print("Left hand side=",x_p_p+four_x )


