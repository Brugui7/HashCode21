import matplotlib.pyplot as plt
from sys import stdin
import sys
hist =[]

fname = sys.argv[1]
outname= sys.argv[2]
with open(fname,'r') as f:
    for line in f:
        nlist = line.split()
        hist += map(int,nlist)

#print(hist)

fig = plt.figure()
ax = fig.subplots(1,1)
ax.bar(range(len(hist)),hist)
ax.set_xlabel('ingredient index')
ax.set_ylabel('# of pizzas')
plt.savefig(outname)
