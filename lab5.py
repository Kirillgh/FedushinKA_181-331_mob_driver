import numpy
from random import choice
import random
import math

alph_cardan = 'абвгдежзийклмнопрстуфхцчшщъыьэюя'

def replace_text_1(text: str) -> str:
    text = text.replace('зпт', ',')
    text = text.replace('тчк', '.')
    text = text.replace('тире', '-')
    text:str = text.replace('прбл', ' ')
    return text

def replace_text_2(text: str) -> str:
    text = text.replace(',', 'зпт')
    text = text.replace('.', 'тчк')
    text = text.replace('-', 'тире')
    text = text.replace(' ', 'прбл')
    return text.lower()

# Функция создания двумерной матрицы
def matrix_double(m: int, n: int) -> list:
    result = []
    for i in range(m):
        temp = []
        for j in range(n):
            temp.append(0)
        result.append(temp)
    return result

# Функция для добавления пробела
def prbl_text(text: str, shift: int) -> str:
    result = ''
    for i in range(len(text)):
        if i % shift != 0:
            result += text[i]
        else:
            if i == 0:
                result += text[i]
            else:
                result += f' {text[i]}'
    return result


# Функция генерации решетки
def generate_key(dimension):
    res_1 = []
    count = 1
    for i in range(dimension):
        temp = []
        for j in range(dimension):
            temp.append(count)
            count += 1
        res_1.append(temp)
    res_2 = rot90(res_1)
    res_3 = rot90(res_2)
    res_4 = rot90(res_3)
    for i in range(1, count):
        rand = random.randint(1, 4)
        if rand == 1:
            for j in range(len(res_1)):
                for k in range(len(res_1[j])):
                    if res_1[j][k] == i:
                        res_1[j][k] = 0
        if rand == 2:
            for j in range(len(res_2)):
                for k in range(len(res_2[j])):
                    if res_2[j][k] == i:
                        res_2[j][k] = 0
        if rand == 3:
            for j in range(len(res_3)):
                for k in range(len(res_3[j])):
                    if res_3[j][k] == i:
                        res_3[j][k] = 0
        if rand == 4:
            for j in range(len(res_4)):
                for k in range(len(res_4[j])):
                    if res_4[j][k] == i:
                        res_4[j][k] = 0
    temp_1 = numpy.concatenate((res_1, res_2), axis=1).tolist()
    temp_2 = numpy.concatenate((res_4, res_3), axis=1).tolist()
    res = numpy.concatenate((temp_1, temp_2), axis=0)
    res[(res > 0)] = 1
    res = res.tolist()
    for i in range(len(res)):
        res[i] = list(map(str, res[i]))
    return res


# Поворот матрицы на 90 градусов
def rot90(matrix):
    return[list(reversed(col)) for col in zip(*matrix)]


# Запись текста в матрицу
def text_in_matrix(text, key_matrix, text_matrix, count):
    for i in range(len(key_matrix)):
        for j in range(len(key_matrix[0])):
            if key_matrix[i][j] == '0':
                if text_matrix[i][j] != 0:
                    print(text_matrix[i][j])
                try:
                    text_matrix[i][j] = text[count]
               # except Exception as e:
                    #print(e)
                except:
                    text_matrix[i][j] = choice(alph_cardan)
                count += 1
    return text_matrix, count


# Создание матрицы для записи текста
def matrix_text(text, key_matrix):
    count = 0
    text_matrix = []
    for i in range(len(key_matrix)):
        temp = []
        for j in range(len(key_matrix[0])):
            temp.append(text[count])
            count += 1
        text_matrix.append(temp)
    return text_matrix


# Извлечение символов из матрицы
def manrix_get_s(text_matrix, key_matrix, result):
    for i in range(len(key_matrix)):
        for j in range(len(key_matrix[0])):
            if key_matrix[i][j] == '0':
                result += text_matrix[i][j]
    return result


def encrypt(text):
    text = replace_text_2(text)

    # Преобразование ключа
    matrix_key = list(generate_key(math.ceil(math.sqrt(len(text))) // 2))
    key_matrix = matrix_key
    count = 0

    # Создание матрицы для записи текста
    text_matrix = matrix_double(len(key_matrix), len(key_matrix[0]))
    # Запись текста в матрицу
    text_matrix, count = text_in_matrix(text, key_matrix, text_matrix, count)
    # Поворот решетки
    key_matrix = rot90(key_matrix)
    # Запись текста в матрицу
    text_matrix, count = text_in_matrix(text, key_matrix, text_matrix, count)
    key_matrix = rot90(key_matrix)
    text_matrix, count = text_in_matrix(text, key_matrix, text_matrix, count)
    key_matrix = rot90(key_matrix)
    text_matrix, count = text_in_matrix(text, key_matrix, text_matrix, count)

    res = ''
    for i in text_matrix:
        for j in i:
            res += str(j)

    # Преобразование матрицы в текст
    key = ''
    for row in matrix_key:
        for item in row:
            key += item
        key += '\n'

    return res, key[:-1]


# Функция расшифрования
def decrypt(text, key_matrix):
    # Преобразование ключа
    key = []
    for row in key_matrix.split('\n'):
        key.append(prbl_text(row, 1).split())
    key_matrix = key
    # Создание матрицы для записи текста
    result = ''
    text_matrix = matrix_text(text, key_matrix)
    # Извлечение букв из матрицы по решетке
    result = manrix_get_s(text_matrix, key_matrix, result)
    # Поворот решетки
    key_matrix = rot90(key_matrix)
    result = manrix_get_s(text_matrix, key_matrix, result)
    key_matrix = rot90(key_matrix)
    result = manrix_get_s(text_matrix, key_matrix, result)
    key_matrix = rot90(key_matrix)
    result = manrix_get_s(text_matrix, key_matrix, result)

    return replace_text_1(result)

