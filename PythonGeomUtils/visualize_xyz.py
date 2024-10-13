import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Read the XYZ file
points = []
xyz_path = "\\Users\\manoj\\Manoj\\Repos\\data\\cgal_point_set_processing\\jet_smoothing_out.xyz"
#with open('points.xyz', 'r') as f:
with open(xyz_path, 'r') as f:
    for line in f:
        x, y, z = line.strip().split()
        points.append((float(x), float(y), float(z)))

# Convert the points to arrays
x = [p[0] for p in points]
y = [p[1] for p in points]
z = [p[2] for p in points]

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the points and connect them with line segments
for i in range(len(points)-1):
    ax.plot([x[i], x[i+1]], [y[i], y[i+1]], [z[i], z[i+1]], color='blue')

# Show the plot
plt.show()
