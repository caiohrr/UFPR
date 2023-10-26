import re
import matplotlib.pyplot as plt

#x_values = [64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000]
x_values = [64, 100, 128, 200]

entry_values = []

with open("FLOPS_DP.dat") as file:
    for item in file:
        match = re.findall(r"[-+]?(?:\d*\.*\d+)", item)
        if match:
            entry_values.append(match[0]) 

matVetY = []
matVetOtimizadoY= []
matMatY = []
matMatOtimizadoY = []

num_of_tests = len(x_values)

count = 0
while count < 4 * num_of_tests:
    matVetY.append(entry_values[count])
    matVetOtimizadoY.append(entry_values[count + 1])
    matMatY.append(entry_values[count + 2])
    matMatOtimizadoY.append(entry_values[count + 3])
    count += 4

plt.subplots(2, 1)

plt.plot(x_values, matVetY, color='r', label='matVetY')
plt.plot(x_values, matVetOtimizadoY, color='b', label='matVetOtimizadoY')
plt.title('matVet')
plt.legend(loc='lower right')
plt.ylabel('MFLOP/s')
plt.xlabel('N')
plt.show()
