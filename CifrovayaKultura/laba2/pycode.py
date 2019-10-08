from PIL import Image
import numpy

DEBUG = 1

# Из RGB в ЧБ и 128x128
image = Image.open("input.png")
image = image.convert('L').resize((128, 128))
image.save("/home/vadim/Desktop/output.png")

# Взятие средней строчки и ее квантование

matrix = numpy.array(image)
# Взятие матрицы пикселей из картинки
array = [((x + 10) // 20) * 20 for x in matrix[matrix.shape[0] // 2]]
# Взятие средней срочки и ее квантование
del matrix
# Удаление матрицы за ненадобностью

# Вычисление частоты появления определенных пикселей
frequency = numpy.zeros(14)
for x in array:
    frequency[x // 20] += 1
if DEBUG: print("Отсортированный по неубыванию массив \
частоты встречаемости символов:\n", sorted(list(enumerate(frequency)), key=lambda x: x[1]))

# Вычисление кол-ва символов алфавита
quantity = 0
for x in frequency:
    if x: quantity += 1
if DEBUG: print("Кол-во символов алфавита", quantity)

# Вычисление энтропии
entropy = 0
for x in frequency:
    if x: entropy -= x / len(array) * numpy.log2(x / len(array))
if DEBUG: print("Энтропия", entropy)

# TODO Найти среднюю минимальную длину двоичного кода

# Генерация двоичного равномерного односимвольного кода
def evenBinaryCode(x, quantity):
    s = ""
    while x:
        s += "1" if x & 1 else "0"
        x //= 2
    while len(s) < numpy.log2(quantity):
        s += "0"
    s = s[::-1]
    return s

EvenBinary = ""
for x in array:
    EvenBinary += evenBinaryCode(x, quantity)

if DEBUG: print("Двоичный равномерный односимвольный код:\n", EvenBinary)
if DEBUG: print("Длина =", len(EvenBinary))

# Генерация кода Шеннона-Фано
Codes = [""] * len(frequency)
def shannonFano(a):
    if len(a) < 2:
        return
    b = []
    c = []
    sumb = 0
    sumc = 0
    for i, x in a:
        if sumb < sumc:
            sumb += x
            b.append((i, x))
            Codes[i] += "0"
        else:
            sumc += x
            c.append((i, x))
            Codes[i] += "1"
    shannonFano(b)
    shannonFano(c)

shannonFano([(i, x) for (i, x) in enumerate(frequency) if x > 0])
if DEBUG: print("Коды Шеннона-Фано:\n", Codes)
ShannonFano = ""
for x in array:
    ShannonFano += Codes[x // 20]
if DEBUG: print("Шеннон-Фано:\n", ShannonFano)
if DEBUG: print("Длина =", len(ShannonFano))

# Генерация кода Хаффмана
HuffmanCodes = [""] * len(frequency)
free = [(x, [i]) for i, x in enumerate(frequency) if x]
def huffman():
    while len(free) > 1:
        min1 = min(free)
        free.remove(min1)
        min2 = min(free)
        free.remove(min2)
        for x in min1[1]:
            HuffmanCodes[x] += "0"
        for x in min2[1]:
            HuffmanCodes[x] += "1"
        free.append((min1[0] + min2[0], min1[1] + min2[1]))

huffman()
if DEBUG: print("Коды Хаффмана:\n", HuffmanCodes)
Huffman = ""
for x in array:
    Huffman += HuffmanCodes[x // 20]
if DEBUG: print("Хаффман:\n", Huffman)
if DEBUG: print("Длина =", len(Huffman))

# Генерация обычного сообщения
message = ""
for x in array:
    message += str(x) + ","
message = message[:-1]
if DEBUG: print("Без сжатия:\n", message)
if DEBUG: print("Длина =", len(message))

# TODO Оценить среднюю длину кодовой комбинации для кодов Хаффмана и Шеннона-Фанно

# Оценивание степени сжатия
if DEBUG: print("Степень сжатия двоичным равномерным", len(EvenBinary) / len(message))
if DEBUG: print("Степень сжатия Шенноном-Фано", len(ShannonFano) / len(message))
if DEBUG: print("Степень сжатия Хаффманом", len(Huffman) / len(message))


# Оценивание избыточночти
if DEBUG: print("Избыточночть Шеннона-Фано", len(ShannonFano) - entropy * len(array), "символов")
if DEBUG: print("Избыточночть Хаффмана", len(Huffman) - entropy * len(array), "символов")
