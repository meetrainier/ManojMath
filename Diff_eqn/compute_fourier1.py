#Inro: Shows how to compute a fourier series
import math

import sympy as sy
from sympy import fourier_series, pi, cos, sin, sympify, SympifyError, Piecewise , And
from sympy.abc import t
from sympy.functions.special.delta_functions import Heaviside
T = sy.symbols('T')
try:
	s = fourier_series(Piecewise((-2 * t, And(-2 < t, t < 0)), (2 * t, And(0 < t, t < 2)), (0, True)), (t, -2, 2))
	print(s.truncate(5))
except SympifyError as err:
    print("error: {0}".format(err))
