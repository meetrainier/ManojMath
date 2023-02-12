#Inro: Shows how to compute a fourier series
import math

import sympy as sy
from sympy import fourier_series, pi, cos, sin, sympify, SympifyError, Piecewise , And
from sympy.abc import t
from sympy.functions.special.delta_functions import Heaviside
T = sy.symbols('T')
try:
	s = fourier_series(Piecewise((cos(t), And(-pi < t, t < 0)), (0.0, And(0 < t, t < pi)), (0, True)), (t, -pi, pi))
	print(s.truncate(9))
except SympifyError as err:
    print("error: {0}".format(err))

t = -3.14/4
val = -4*sin(2*t)/(3*pi) - 8*sin(4*t)/(15*pi) - 12*sin(6*t)/(35*pi) - 16*sin(8*t)/(63*pi) - 20*sin(10*t)/(99*pi) - 24*sin(12*t)/(143*pi) - 28*sin(14*t)/(195*pi) - 32*sin(16*t)/(255*pi) + cos(t)/2
print("val=",val)
print("at t = -pi/4,val=",1.04895073161074/3.14+ 0.3536941345836)
print("verify=", 0.3536941345836 - 1.04895073161074/3.14)