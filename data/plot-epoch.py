import numpy as np
import matplotlib.pyplot as plt
import csv

length = 500
color = ['red', 'green', 'blue', 'magenta', '#ff8509' ]
label = [ "10", "50", "200", "500", "1000" ]
file = [ "10.csv", "50.csv", "200.csv", "500.csv", "1000.csv" ]


for i in range(4,5):
    data = np.genfromtxt(file[i], delimiter=",", names=["x", "y", "z"] ,comments="#")
    mean = [np.mean(data['y'])] * len(data['z'])
    plt.plot( data['y'], color=color[i], label=label[i] + " Indivíduos")
    plt.plot( mean, color=color[i], linestyle='dotted')
    plt.annotate(mean[0], xy=(length,mean[0]), xytext=(0,0), color=color[i],
                 textcoords="offset points", size=8, va="center", xycoords='data')

plt.title('Epocas')
plt.ylabel('Numero de Epocas')
plt.xlabel('Iterações')

# plt.savefig("test.png")
# plt.savefig("tight.png", bbox_inches='tight')
plt.legend()
plt.show()
