import random
import matplotlib.pyplot as plt

with open("out.txt", 'r') as f:
    data = [float(x) for x in f.read().split('\n') if x]
    plt.title("Rule 30 PRNG")
    plt.xlabel("Value")
    plt.ylabel("Occurences")
    plt.hist(data)
    plt.show()
