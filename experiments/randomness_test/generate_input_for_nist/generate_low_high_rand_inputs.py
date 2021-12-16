import sys
import time
import random
import string

MAX_LEN = 4
ONE_1_HEXES = (1, 2, 4, 8)
ONE_0_HEXES = ('e', 'd', 'b', 7)
MIN_STR_LEN = 10 # in bytes
MAX_STR_LEN = 100 # in bytes

sys.setrecursionlimit(10000)

def insert_num(s0, idx, num):
    l = list(s0)
    l[idx] = str(num)
    return ''.join(l)

def insert_all_n_times(s0, n, nums, strings=None):
    # flag = False
    # if strings is None:
    #     flag = True
    strings = strings or set()
    # print('len', len(strings))
    strings.add(s0)
    if n == 0:
        return strings
    for i in range(len(s0)):
        for num in nums:
            s = insert_num(s0, i, num)
            insert_all_n_times(s, n-1, nums, strings)
            # if flag:
            #     print(i, num, 'finished')
    
    return strings

def generate_random_str(length):
    if length % 2 == 1:
        length += 1
    return ''.join(random.choices(string.hexdigits[:-6], k=length))





f = open('low.txt', 'w')

for i in range(1, MAX_LEN + 1):
    t = time.process_time()
    
    insertion_count = i // 5 + 1
    s0 = '00' * i
    strings = insert_all_n_times(s0, insertion_count, ONE_1_HEXES)
    for line in sorted(list(strings)):
        print(line, file=f)

    elapsed_time = time.process_time() - t
    print(i, 'finished', 'time =', elapsed_time, 's')

f.close()
print('##### low finished')


f = open('high.txt', 'w')

for i in range(1, MAX_LEN + 1):
    t = time.process_time()
    
    insertion_count = i // 5 + 1
    s0 = 'ff' * i
    strings = insert_all_n_times(s0, insertion_count, ONE_0_HEXES)
    for line in sorted(list(strings)):
        print(line, file=f)

    elapsed_time = time.process_time() - t
    print(i, 'finished', 'time =', elapsed_time, 's')

f.close()
print('##### high finished')



f = open('rand.txt', 'w')

all_strings = set()
for _ in range(707): # count of strings in low and high
# for _ in range(707974): # count of strings in low and high
    length = random.choice(range(MIN_STR_LEN, MAX_STR_LEN))
    s = generate_random_str(length)
    while s in all_strings:
        length = random.choice(range(MIN_STR_LEN, MAX_STR_LEN))
        s = generate_random_str(length)
    all_strings.add(s)
    print(s, file=f)

f.close()
print('##### rand finished')