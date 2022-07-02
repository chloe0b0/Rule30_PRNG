import random
import matplotlib.pyplot as plt

with open("out.txt", 'r') as f:
    data = [float(x) for x in f.read().split('\n') if x]
    comp = [random.randint(0, max(data)) for x in range(len(data))]

    plt.title('Rule 30 PRNG')
    plt.xlabel('Iteration')
    plt.ylabel('Occurences')
    plt.hist(data)
    plt.hist(comp)
    plt.show()
