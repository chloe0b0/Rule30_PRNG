import random
import numpy as np
from scipy.spatial import distance
import matplotlib.pyplot as plt

with open("out.txt", 'r') as f:
    data = np.array([float(x) for x in f.read().split('\n') if x][:-452])
    box = int(np.sqrt(data.shape[0]))
    data = data.reshape(box, box)
    plt.imshow(data, cmap = "binary")

    plt.show()
