import numpy as np
import matplotlib.pyplot as plt
import csv

length = 100
color = 'red'
label = "10 Indivíduos"
file = "10.csv"
data = np.genfromtxt(file, delimiter=",", names=["x", "y", "z"] ,comments="#")
mean = [np.mean(data['z'])] * len(data['z'])
plt.plot( data['z'], color=color, label=label)
plt.plot( mean, color=color, linestyle='dotted')
plt.annotate(round(mean[0],3), xy=(length,mean[0]), xytext=(0,0), color=color,
             textcoords="offset points", size=8, va="center", xycoords='data')

length = 100
color = 'green'
label = "50 Indivíduos"
file = "50.csv"
data = np.genfromtxt(file, delimiter=",", names=["x", "y", "z"] ,comments="#")
mean = [np.mean(data['z'])] * len(data['z'])
plt.plot( data['z'], color=color, label=label)
plt.plot( mean, color=color, linestyle='dotted')
plt.annotate(round(mean[0],3), xy=(length,mean[0]), xytext=(0,0), color=color,
             textcoords="offset points", size=8, va="center", xycoords='data')

length = 100
color = 'blue'
label = "200 Indivíduos"
file = "200.csv"
data = np.genfromtxt(file, delimiter=",", names=["x", "y", "z"] ,comments="#")
mean = [np.mean(data['z'])] * len(data['z'])
plt.plot( data['z'], color=color, label=label)
plt.plot( mean, color=color, linestyle='dotted')
plt.annotate(round(mean[0],3), xy=(length,mean[0]), xytext=(0,0), color=color,
             textcoords="offset points", size=8, va="center", xycoords='data')

length = 100
color = 'magenta'
label = "500 Indivíduos"
file = "500.csv"
data = np.genfromtxt(file, delimiter=",", names=["x", "y", "z"] ,comments="#")
mean = [np.mean(data['z'])] * len(data['z'])
plt.plot( data['z'], color=color, label=label)
plt.plot( mean, color=color, linestyle='dotted')
plt.annotate(round(mean[0],3), xy=(length,mean[0]), xytext=(0,0), color=color,
             textcoords="offset points", size=8, va="center", xycoords='data')

length = 100
color = '#ff8509'
label = "1000 Indivíduos"
file = "1000.csv"
data = np.genfromtxt(file, delimiter=",", names=["x", "y", "z"] ,comments="#")
mean = [np.mean(data['z'])] * len(data['z'])
plt.plot( data['z'], color=color, label=label)
plt.plot( mean, color=color, linestyle='dotted')
plt.annotate(round(mean[0],3), xy=(length,mean[0]), xytext=(0,0), color=color,
             textcoords="offset points", size=8, va="center", xycoords='data')

plt.title('Tempo de Execução')
plt.ylabel('Segundos')
plt.xlabel('Iterações')

# plt.savefig("test.png")
# plt.savefig("tight.png", bbox_inches='tight')
plt.legend()
plt.show()
