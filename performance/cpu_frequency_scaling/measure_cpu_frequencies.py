import time
import psutil
import csv

def get_cpu_frequencies():
    return [freq.current for freq in psutil.cpu_freq(percpu=True)]

def main():
    filename = "cpu_frequencies.csv"
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Timestamp"] + [f"Core {i}" for i in range(psutil.cpu_count())])
        
        try:
            while True:
                timestamp = time.time()
                frequencies = get_cpu_frequencies()
                writer.writerow([timestamp] + frequencies)
                time.sleep(0.1)
        except KeyboardInterrupt:
            print(f"Data collection stopped. Data saved to {filename}")

if __name__ == "__main__":
    main()
