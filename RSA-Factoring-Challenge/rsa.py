import sys

def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True

def factorize_rsa(n):
    for i in range(2, n):
        if n % i == 0 and is_prime(i) and is_prime(n // i):
            return i, n // i

def main():
    if len(sys.argv) != 2:
        print("Usage: rsa <file>")
        sys.exit(1)

    input_file = sys.argv[1]

    with open(input_file, 'r') as file:
        for line in file:
            n = int(line.strip())
            p, q = factorize_rsa(n)
            print(f"{n}={p}*{q}")

if __name__ == "__main__":
    main()
