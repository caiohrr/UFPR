import re
import matplotlib.pyplot as plt

x_values = [64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000]

entry_values = []

with open("FLOPS_DP.dat") as file:
    for item in file[::2]:
        match = re.findall(r"[-+]?(?:\d*\.*\d+)", item)
        if match:
            entry_values.append(match[0]) 

