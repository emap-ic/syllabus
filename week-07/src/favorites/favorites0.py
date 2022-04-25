# Prints all titles in CSV using csv.reader

import csv

# Open CSV file
with open("emap-shows.csv", "r") as file:

    # Create reader
    reader = csv.reader(file)

    # Skip header row
    next(reader)

    # Iterate over CSV file, printing each title
    for row in reader:
        print(f"{row[1]} genero {row[2]}")
