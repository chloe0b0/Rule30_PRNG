import random
import time
import matplotlib.pyplot as plt
import numpy as np

with open("out.txt", 'r') as f:
    data = [float(x) for x in f.read().split('\n') if x]
    start = time.time()
    comp_np = np.random.randint(low = 0, high = max(data), size = (len(data)), dtype = np.uint64)
    end = time.time() - start
    print(end)
    plt.title("Rule 30 PRNG")
    plt.xlabel("Value")
    plt.ylabel("Occurences")
    plt.hist(data)
    #plt.hist(comp_np)
    plt.show()
