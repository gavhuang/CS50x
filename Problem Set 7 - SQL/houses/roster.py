from cs50 import SQL
from sys import exit, argv

# Check command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py 'House'")
    exit(1)

# Set database connection to db made in import.py
db = SQL("sqlite:///students.db")

# Check db database
list = db.execute("SELECT first, middle, last, house, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# Be careful when using " " on the outside, then the inside needs ' '
for row in list:
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")