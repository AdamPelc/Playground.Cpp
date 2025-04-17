import sys
import pandas as pd
import matplotlib
matplotlib.use('Qt5Agg')
import matplotlib.pyplot as plt

def plot_cpu_frequencies(file_path):
    # Load data from the file
    data = pd.read_csv(file_path)

    # Set the timestamp as the index
    data.set_index('Timestamp', inplace=True)

    # Plot the data
    plt.figure(figsize=(15, 8))
    for column in data.columns:
        plt.plot(data.index, data[column], label=column)

    # Add labels and title
    plt.xlabel('Timestamp')
    plt.ylabel('Frequency (MHz)')
    plt.title('CPU Cores Frequencies Over Time')
    plt.legend(loc='upper right', ncol=4, fontsize='small')
    plt.grid(True)

    # Show the plot
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <path_to_data_file>")
    else:
        plot_cpu_frequencies(sys.argv[1])
