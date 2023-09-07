import subprocess
import re

# Comando para executar o programa perfEG com LIKWID
comando = "likwid-perfctr -C 0 -g FLOPS_DP -m ./perfEG"

# Executa o comando e captura a saída
saida = subprocess.check_output(comando, shell=True, text=True)

# Procura pela linha que contém a contagem de MFLOP/s
match = re.search(r'MFLOP/s:\s+(\d+\.\d+)', saida)

# Se encontrou a contagem de MFLOP/s, imprime o valor
if match:
    mflops = float(match.group(1))
    print(f"Quantidade de MFLOP/s: {mflops}")
else:
    print("Não foi possível encontrar a contagem de MFLOP/s.")
