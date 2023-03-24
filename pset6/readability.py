from cs50 import get_string

text = get_string("Text: ")

def main():
    w = words()
    index = 0.0588 * (100.0 * letters() / w) - 0.296 * (100.0 * sentences() / w) - 15.8
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")
        
def letters():
    letter = 0
    for char in text:
        if char.isalpha():
            letter += 1
    return letter
    
def words():
    word = 1
    for char in text:
        if char.isspace():
            word += 1
    return word
    
def sentences():
    sentence = 0
    for char in text:
        if char == "." or char == "?" or char == "!":
            sentence += 1
    return sentence
    
if __name__ == "__main__":
    main()