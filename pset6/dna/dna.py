from csv import reader 
from sys import exit, argv

if len(argv) != 3:
    print("Usage: dna.py <str_counts csv file> <dna_sequence txt file>")
    exit(1)
database = [] # To store the csv database
with open(argv[1], 'r') as file1:
    reader1 = reader(file1)
    fields = next(reader1) # To store field headers in the csv
    for row in reader1:
        database.append(row)
with open(argv[2], 'r') as file2:
    dna = file2.read() # To store the DNA sequencce

def main():
    for i in range(len(database)):
        flag = True # To keep track if each STR value matches with person's data in database
        for j in range(1, len(fields)):
            if int(database[i][j]) != check(fields[j]): # If dna STR values dont match with person's STR values in database
                flag = False
                break
        if flag:
            print(database[i][0])
            break
    if not flag:
        print("No match")
    exit(0)

def check(sequence):
    count = 0 # To store number of consecutive STRs in dna sequence
    max_ = 0 # To store maximum number of consecutive STRs found till now
    l = len(sequence)
    i = 0
    while i <= len(dna) - l:
        if dna[i: i + l] == sequence: # Splices dna sequence to substrings of equal length as STR sequence
            count += 1
            i += l
            if count > max_:    
                max_ = count
        else:
            count = 0 # STR no longer consecutive
            i += 1
    return max_

if __name__ == "__main__":
    main()
                