import time
from random import randint


def get_nums():
    numbers_count, constraints_num = map(int, input().split())
    constraints = []
    for constraint in range(constraints_num):
        constraints.append(list(map(int, input().split())))
    return numbers_count, constraints


def bitfield(n, number_of_bits):
    num = f'{n:{number_of_bits}b}'
    return [1 if digit == '1' else 0 for digit in num]


def find_exacts(constraints, numbers_count):
    st = time.time()

    if not constraints:
        return [0 for i in range(numbers_count)]
    for constraint in constraints:
        if constraint[1] < constraint[0]:
            (constraint[0], constraint[1]) = (constraint[1], constraint[0])
    constraints.sort(key=lambda x: (x[0], x[1]))
    ax_eq = max(constraints, key=lambda item: item[2])
    max_len = len(bin(ax_eq[2])[2:])  # 30 !!
    n_list = [['x' for j in range(max_len)] for i in range(numbers_count)]  # 10^5
    ans_list = [bitfield(i[2], max_len) for i in constraints]  # 30 * 10^5
    for i in range(2):
        for constraint in range(len(constraints)):
            n1 = constraints[constraint][0]
            n2 = constraints[constraint][1]
            for bit in range(max_len):
                if ans_list[constraint][bit] == 0:
                    n_list[n1 - 1][bit] = 0
                    n_list[n2 - 1][bit] = 0
                if ans_list[constraint][bit] == 1:
                    if n_list[n1 - 1][bit] == 0:
                        n_list[n2 - 1][bit] = 1
                    if n_list[n2 - 1][bit] == 0:
                        n_list[n1 - 1][bit] = 1

    for constraint in range(len(constraints)):
        n1 = constraints[constraint][0]
        n2 = constraints[constraint][1]
        for bit in range(max_len):
            if n1 != n2:
                if n_list[n1 - 1][bit] == 'x' and n_list[n2 - 1][bit] == 'x':
                    n_list[n1 - 1][bit] = 0
                    n_list[n2 - 1][bit] = 1
                elif n_list[n1 - 1][bit] == 'x' and n_list[n2 - 1][bit] == 1:
                    n_list[n1 - 1][bit] = 0
                elif n_list[n1 - 1][bit] == 1 and n_list[n2 - 1][bit] == 'x':
                    n_list[n2 - 1][bit] = 0  # ?????
                elif n_list[n1 - 1][bit] == 0 and n_list[n2 - 1][bit] == 'x':
                    n_list[n2 - 1][bit] = 1
            else:
                if n_list[n1 - 1][bit] == 'x':
                    n_list[n1 - 1][bit] = 1
                    n_list[n2 - 1][bit] = 1
    for i in range(numbers_count):
        if 'x' in n_list[i]:
            n_list[i] = [0]
    lizt = [int(''.join(map(str, li)), 2) for li in n_list]
    # return lizt
    et = time.time()
    return et - st


if __name__ == '__main__':
    # numbers, constraints = get_nums()
    numbers = 10 ** 5
    constraints = [[] for i in range(2 * 10 ** 5)]
    for i in range(2 * 10 ** 5):
        constraints[i] = [randint(1, 10 ** 5), randint(1, 10 ** 5), randint(1, 2 ** 30)]
    print(find_exacts(constraints, numbers))
