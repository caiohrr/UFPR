import re
import matplotlib.pyplot as plt
from matplotlib import style

#x_values = [64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000]
x_values = [64, 100, 128, 200]

entry_values = []

with open("L2CACHE.dat") as file:
    for item in file:
        entry_values.append(float(item.split("|")[2]))
        #match = re.findall(r"[-+]?(?:\d*\.*\d+)", item)
        #if match:
        #    entry_values.append(match[0]) 

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

print(matVetY)
print(matVetOtimizadoY)
print(matMatY)
print(matMatOtimizadoY)

plt.style.use('ggplot')

fig, (matVet, matMat) = plt.subplots(2, 1)

matVet.plot(x_values, matVetY, label='matVetY')
matVet.plot(x_values, matVetOtimizadoY, label='matVetOtimizadoY')

matMat.plot(x_values, matMatY, label='matMatY')
matMat.plot(x_values, matMatOtimizadoY, label='matMatOtimizadoY')

matVet.legend(loc='lower right')
matVet.set_title('FLOPS_DP, Matriz-vetor')
matVet.set_ylabel('MFLOP/s')
matVet.set_xlabel('N')

matMat.legend(loc='lower right')
matMat.set_title('FLOPS_DP, Matriz-matriz')
matMat.set_ylabel('MFLOP/s')
matMat.set_xlabel('N')

plt.show()
