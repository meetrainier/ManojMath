#Inro: Shows how to compute a fourier series
import math

#B =float(input("Input B="))
import sympy as sy
from sympy import fourier_series, pi, cos, sin
from sympy.abc import t
from sympy.functions.special.delta_functions import Heaviside
T = sy.symbols('T')
s = fourier_series(Heaviside(t) - Heaviside(t-1/4), (t, 0, 1))
print(s.truncate(3))
 