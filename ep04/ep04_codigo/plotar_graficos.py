import matplotlib.pyplot as plt

# Define the X values (since they are fixed)
x_values = [64, 100, 128, 200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000]

# Initialize an empty list to store the Y values for each graph
graph_data = []

# Read the Y values from the file and separate them into graphs
with open('FLOPS_DP.dat', 'r') as file:
    lines = file.readlines()

    num_graphs = 4  # Assuming you have 4 graphs
    lines_per_graph = len(lines) // num_graphs

    for i in range(num_graphs):
        start = i * lines_per_graph
        end = start + lines_per_graph
        y_values = [float(line.split('|')[1].strip()) for line in lines[start:end] if line.strip()]  # Extract Y values
        graph_data.append(y_values)

# Create and plot each graph
for i, y_values in enumerate(graph_data):
    plt.plot(x_values, y_values, marker='o', linestyle='-', label=f'Graph {i + 1}')

plt.xlabel('X values')
plt.ylabel('Y values')
plt.title('Multiple Graphs')
plt.grid(True)
plt.legend()
plt.show()

