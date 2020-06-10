import csv
import sys

# Ensure 3 arguments
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

# Open CSV for headers and DNA sequences, read into memory. CSV will close after grabbing the headers.
with open(sys.argv[1], "r") as databases:
    reader = csv.DictReader(databases)
    STR_header = reader.fieldnames

sequences = open(sys.argv[2], "r")
seqRead = sequences.read()

# Make dictionary of STRs
STR = {}

# Iterate over the STRs (header minus name)
# Update dictionary with STR = 0, skipping "name"
# Loop through sequence looking for largest consecutive STR
for i in range(len(STR_header) - 1):
    STR[STR_header[i + 1]] = 0
    STR_max = 0
    found_counter = 0
    N = len(STR_header[i + 1])

    for j in range(len(seqRead)):
        # While you find a match
        # If the STR_max is zero, increase STR counter because you found at least one and update dictionary
        # Note: If it's the FIRST TIME, you'll stay in the loop at that position and move to the else condition
        # Else: Look current set, found_counter += 1, then look at next set, while still true, update max if necessary, look at next set
        # When you're done finding, the found_counter is reset to zero.
        while seqRead[j:(j + N)] == STR_header[i + 1]:
            if STR_max == 0:
                STR_max += 1
                STR[STR_header[i + 1]] = STR_max
            else:
                found_counter += 1
                j += N
                while seqRead[j:(j + N)] == STR_header[i + 1]:
                    found_counter += 1
                    if found_counter > STR_max:
                        STR_max = found_counter
                        STR[STR_header[i + 1]] = STR_max
                    j += N
                found_counter = 0

# Compare STR dictionary to databases
# Reopen dictionary
with open(sys.argv[1], "r") as databases:
    reader = csv.DictReader(databases)

# For row of reader, and each STR in the header,
# See if the DNA is in the row and values match - counter += 1
# If counter == number of STRs in the header, then it's a match
# If found, exit the program.

    for row in reader:

        counter = 0
        # Skip the name (first key-value pair in each dictionary row)
        for DNA in STR_header[1:]:
            if DNA in row:
                # CSV files are read as strings so cast to int()
                if STR[DNA] == int(row[DNA]):
                    counter += 1

        if counter == (len(STR_header) - 1):
            print(row["name"])
            sys.exit(0)

    print("No match.")