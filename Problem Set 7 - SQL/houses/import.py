from cs50 import SQL
from sys import exit, argv
import csv

# Make database
db = SQL("sqlite:///students.db")

# Check command-line arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Open CSV file:
with open(argv[1], "r") as file:
    reader = csv.DictReader(file)

    # This is useful if your table is wrong, delete all entries, and re-insert
    # db.execute("DELETE FROM students")

    for row in reader:
        # Split the name into three sections if there's a space
        # Note: names for this problem have (first, last) or (first, middle, last)
        name = row["name"].split(" ")

        if len(name) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", name[0], None, name[1], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", name[0], name[1], name[2], row["house"], row["birth"])