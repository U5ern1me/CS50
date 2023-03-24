def main():
    num = int(input("Number : "))
    if checksum(num):
        if num // 10 ** 13 == 34 or num // 10 ** 13 == 37:
            print("AMEX")
        elif num // 10 ** 12 == 4 or num // 10 ** 15 == 4:
            print("VISA")
        elif num // 10 ** 14 in range(51, 56):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")
def checksum(num): # Checks Luhn's Algorithm
    sum_ = 0
    while num > 0:
        dig = num % 100 // 10 * 2
        dig = dig % 10 + dig // 10
        sum_ += dig + num % 10
        num //= 100
    return True if (sum_ % 10 == 0) else False 
if __name__ == "__main__":
    main()
    
