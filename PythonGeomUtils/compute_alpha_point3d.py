import os
import sys
import pandas as pd
import numpy as np
from descartes import PolygonPatch
import matplotlib.pyplot as plt
sys.path.insert(0, os.path.dirname(os.getcwd()))
import alphashape

points_3d = [
    (0., 0., 0.), (0., 0., 1.), (0., 1., 0.),
    (1., 0., 0.), (1., 1., 0.), (1., 0., 1.),
    (0., 1., 1.), (1., 1., 1.), (.25, .5, .5),
    (.5, .25, .5), (.5, .5, .25), (.75, .5, .5),
    (.5, .75, .5), (.5, .5, .75)
]
df_3d = pd.DataFrame(points_3d, columns=['x', 'y', 'z'])


fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter(df_3d['x'], df_3d['y'], df_3d['z'])
plt.show()

alpha_shape = alphashape.alphashape(points_3d, 1.1)
alpha_shape.show()
