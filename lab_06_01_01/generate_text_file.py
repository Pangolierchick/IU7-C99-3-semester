from random import randint, choice

LINE_NUMBERS = 1000
NAME = 'text.txt'

def generate_rnd_string(str_len:int):
    a = ''
    alphabet = "qwertyuiopasdfghjklzxcvbnm"
    for i in range(str_len):
        a += choice(alphabet)
    return a

def get_rnd_year():
    return randint(1, 3) * 1000 + randint(0, 999)

def generate_text_file(struct_num:int):
    f = open(NAME, 'w')
    
    for i in range(struct_num):
        title = generate_rnd_string(4)
        name = generate_rnd_string(4)
        year = get_rnd_year()
        f.write(title + '\n' + name + '\n' + str(year) + '\n')

    f.close()

def main():
    lines = 5
    print(f"Generating {lines} lines. File name: {NAME}")
    generate_text_file(lines)
    print("Done.")

if __name__ == "__main__":
    main()
