import sys
import re
import matplotlib.pyplot as plt
from matplotlib import style

# (A) Geração do sl
#   Tempo, FLOPS_DP, L3 e L2CACHE - 4 gráficos
# (B) Solução do sl
#   Tempo, FLOPS_DP - 2 gráficos
# (C) Cáluclo do resíduo
#   Tempo, FLOPS_DP, L3 e L2CACHE - 4 gráficos
#

def gerarValores(dir, opcao, num_de_testes):
    
    entry_flops = []
    entry_l3 = []
    entry_l2cache = []
    entry_tempo = []

    with open(dir + "/dat/FLOPS_DP.dat") as file:
        for line in file:
            entry_flops.append(float(line.split("|")[2]))

    with open(dir + "/dat/L3.dat") as file:
        for line in file:
            entry_l3.append(float(line.split("|")[2]))

    with open(dir + "/dat/L2CACHE.dat") as file:
        for line in file:
            entry_l2cache.append(float(line.split("|")[2]))

    with open(dir + "/dat/TEMPO_FLOPS_DP.dat") as file:
        for line in file:
            entry_tempo.append(float(line.split(" ")[-1]))


    if opcao == "A":
        tmp = 0
    elif opcao == "B":
        tmp = 1
    else:
        tmp = 2

    flops = []
    l2cache = []
    l3 = []
    tempo = []

    count = 0
    while count < num_de_testes:
        flops.append(entry_flops[count * 3 + tmp])
        l2cache.append(entry_l2cache[count * 3 + tmp])
        l3.append(entry_l3[count * 3 + tmp])
        tempo.append(entry_tempo[count * 3 + tmp])
        count += 1

    return (flops, l2cache, l3, tempo)

#def plotarGrafico(opcao, flops, l2cache, l3, tempo):
def plotarGrafico(opcao, flops_v1, l2cache_v1, l3_v1, tempo_v1, flops_v2, l2cache_v2, l3_v2, tempo_v2):

    plt.style.use('ggplot')

    if opcao != "B":
        fig, ((FlopsGraph, TempoGraph), (L3Graph, L2cacheGraph)) = plt.subplots(2, 2)
    else:
        fig, ((FlopsGraph, TempoGraph)) = plt.subplots(2, 1)

    if opcao == "A":
        fig.suptitle("Geração do SL", fontsize = 18, fontweight = "bold")
    elif opcao == "B":
        fig.suptitle("Resolução do SL", fontsize = 18, fontweight = "bold")
    elif opcao == "C":
        fig.suptitle("Cálculo do resíduo", fontsize = 18, fontweight = "bold")

    xlabel = "Entrada"

    if opcao != "B":
        L2cacheGraph.plot(x_values, l2cache_v1, label = "v1", marker='.')
        L2cacheGraph.plot(x_values, l2cache_v2, label = "v2", marker='.')
        L2cacheGraph.set_xlabel(xlabel)
        L2cacheGraph.set_ylabel("L2 miss ratio")
        L2cacheGraph.set_xscale("log")
        L2cacheGraph.legend(shadow = True, fancybox = True)

        L3Graph.plot(x_values, l3_v1, label = "v1", marker='.')
        L3Graph.plot(x_values, l3_v2, label = "v2", marker='.')
        L3Graph.set_xlabel(xlabel)
        L3Graph.set_ylabel("L3 bandwidth [MBytes/s]")
        L3Graph.set_xscale("log")
        L3Graph.legend(shadow = True, fancybox = True)

    FlopsGraph.plot(x_values, flops_v1, label = "v1", marker='.')
    FlopsGraph.plot(x_values, flops_v2, label = "v2", marker='.')
    FlopsGraph.set_xlabel(xlabel)
    FlopsGraph.set_ylabel("MFLOPS/s")
    FlopsGraph.set_xscale("log")
    FlopsGraph.legend(shadow = True, fancybox = True)
    
    TempoGraph.plot(x_values, tempo_v1, label = "v1", marker='.')
    TempoGraph.plot(x_values, tempo_v2, label = "v2", marker='.')
    TempoGraph.set_xlabel(xlabel)
    TempoGraph.set_ylabel("Tempo (ms)")
    TempoGraph.set_xscale("log")
    TempoGraph.legend(shadow = True, fancybox = True)

    plt.tight_layout()
    plt.show()

x_values = [64, 128, 200, 256, 512, 600, 800, 1024, 2000, 3000, 4096, 6000, 7000, 10000, 50000, 100000, 1000000, 10000000, 100000000]

metrics = ["TEMPO", "L2CACHE", "L3", "FLOPS_DP"]
num_of_tests = len(x_values)

opcao = input("Insira a opção para testar A (Geração do Sl), B (Resolução do SL) ou C (Cálculo do resíduo): ")
flops_v1, l2cache_v1, l3_v1, tempo_v1 = gerarValores("v1", opcao, num_of_tests)
flops_v2, l2cache_v2, l3_v2, tempo_v2 = gerarValores("v2", opcao, num_of_tests)
plotarGrafico(opcao, flops_v1, l2cache_v1, l3_v1, tempo_v1, flops_v2, l2cache_v2, l3_v2, tempo_v2)
