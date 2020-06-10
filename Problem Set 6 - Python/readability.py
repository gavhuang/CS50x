from cs50 import get_string

# Prompt user for text
text = get_string("Text: ")

# Counter for letters, words, and sentences
letters = 0
words = 0
sentences = 0

# Count letters
for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
        
# Count words
# Count the first word too
if text[0].isalpha():
    words += 1
    
for j in range(len(text)):
    if text[j].isspace() and text[j + 1].isalpha():
        words += 1

# Count sentences
for k in range(len(text)):
    if text[k] == '!' or text[k] == '.' or text[k] == '?' or text[k] == ':':
        sentences += 1

# Coleman-Liau Index - round up to get the correct grade
L = letters / (words / 100)
S = sentences / (words / 100)
ColemanLiau = round((0.0588 * L) - (0.296 * S) - 15.8)

if ColemanLiau < 1:
    print("Before Grade 1")
elif ColemanLiau >= 1 and ColemanLiau <= 16:
    print(f"Grade {ColemanLiau}")
elif ColemanLiau > 16:
    print("Grade 16+")