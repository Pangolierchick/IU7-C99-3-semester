import random as rnd
from tqdm import tqdm

TOP_LIMIT = 100
LOW_LIMIT = -100

def gen_file(f, size:int):
    for i in tqdm(range(size)):
        num = rnd.randint(LOW_LIMIT, TOP_LIMIT)
        f.write(f"{num}\n")

def main():
    filename = input('Input filename: ')
    size = int(input('Input file len: '))

    dst_file = open(filename, "w")

    gen_file(dst_file, size)
    print("Done.")


if __name__ == '__main__':
    main()
