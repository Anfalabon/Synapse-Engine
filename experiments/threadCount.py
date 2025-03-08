import os
import multiprocessing

def get_num_threads():
    num_threads = os.cpu_count()
    return num_threads

if __name__ == "__main__":
    print("Number of threads in your computer:", get_num_threads())
