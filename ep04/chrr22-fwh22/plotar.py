import sys
import re
import matplotlib.pyplot as plt
from matplotlib import style

def generateGraphValues(metric, num_of_tests):
    
    matVetY = []
    matVetOtimizadoY = []
    matMatY = []
    matMatOtimizadoY = []
    entry_values = []

    if metric == "TEMPO":
        matVetY = [0]*num_of_tests
        matVetOtimizadoY = [0]*num_of_tests
        matMatY = [0]*num_of_tests
        matMatOtimizadoY = [0]*num_of_tests
        for m in metrics:
            if m == "TEMPO":
                continue

            with open("./dat/TEMPO_" + m + ".dat") as file:
                    for item in file:
                        entry_values.append(float(item.split(" ")[-1]))


            for v in range(num_of_tests):
                matVetY[v] = entry_values[v * 4]

            for v in range(num_of_tests):
                matVetOtimizadoY[v] = entry_values[v * 4 + 1]
                
            for v in range(num_of_tests):
                matMatY[v] = entry_values[v * 4 + 2]

            for v in range(num_of_tests):
                matMatOtimizadoY[v] = entry_values[v * 4 + 3]

        for i in range(num_of_tests):
            matVetY[i] /= 4
            matVetOtimizadoY[i] /= 4
            matMatY[i] /= 4
            matMatOtimizadoY[i] /= 4

        return (matVetY, matVetOtimizadoY, matMatY, matMatOtimizadoY)


    with open("./dat/" + metric + ".dat") as file:
        for item in file:
            entry_values.append(float(item.split("|")[2]))

    count = 0
    while count < 4 * num_of_tests:
        matVetY.append(entry_values[count])
        matVetOtimizadoY.append(entry_values[count + 1])
        matMatY.append(entry_values[count + 2])
        matMatOtimizadoY.append(entry_values[count + 3])
        count += 4

    return (matVetY, matVetOtimizadoY, matMatY, matMatOtimizadoY)

def plotGraph(metric, matVetY, matVetOtimizadoY, matMatY, matMatOtimizadoY):
    plt.style.use('ggplot')

    fig, (matVet, matMat) = plt.subplots(2, 1)

    matVet.plot(x_values, matVetY, label='matVetY')
    matVet.plot(x_values, matVetOtimizadoY, label='matVetOtimizadoY')

    matMat.plot(x_values, matMatY, label='matMatY')
    matMat.plot(x_values, matMatOtimizadoY, label='matMatOtimizadoY')

    if metric == 'TEMPO':
        ylabel = 'Tempo (ms)'
    elif metric == 'L2CACHE':
        ylabel = 'L2 miss ratio'
    elif metric == 'L3':
        ylabel = 'L3 bandwidth [MBytes/s]'
    elif metric == 'ENERGY':
        ylabel = 'Energy [J]'
    elif metric == 'FLOPS_DP':
        ylabel = 'DP MFLOP/s'

    matVet.legend(loc='lower right')
    matVet.set_title(metric + ' - Matriz-vetor')
    matVet.set_ylabel(ylabel)
    matVet.set_xlabel('N')

    matMat.legend(loc='lower right')
    matMat.set_title(metric + ' - Matriz-matriz')
    matMat.set_ylabel(ylabel)
    matMat.set_xlabel('N')

    plt.tight_layout()
    plt.show()

x_values = [64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000]

metrics = ["TEMPO", "L2CACHE", "L3", "ENERGY", "FLOPS_DP"]
num_of_tests = len(x_values)

if len(sys.argv) < 2:
    for metric in metrics:
        matVetY, matVetOtimizadoY, matMatY, matMatOtimizadoY = generateGraphValues(metric, num_of_tests)
        plotGraph(metric, matVetY, matVetOtimizadoY, matMatY, matMatOtimizadoY)
else:
    metric = sys.argv[1]
    matVetY, matVetOtimizadoY, matMatY, matMatOtimizadoY = generateGraphValues(metric, num_of_tests)
    plotGraph(metric, matVetY, matVetOtimizadoY, matMatY, matMatOtimizadoY)
