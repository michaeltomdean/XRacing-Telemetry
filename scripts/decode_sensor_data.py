"""
Author: Michael Dean
University of Exeter 

X-Racing Telemetry Sensor Data decode script.

Data comes in CSV format. With columns defined below.

Col1: Datetime (String)  Col2: Sensor ID (8 bits)    Col3: Sensor Data (32 bits)
"""

import pandas as pd
import datetime
import os

def main():
    example_test_data()

def example_test_data():
    dir = os.path.dirname(__file__)
    filename = os.path.join(dir, "../datasets/simple_example/20240118.csv")
    example_dataset = pd.read_csv(filename)
    print(example_dataset)

if __name__ == "__main__":
    main()