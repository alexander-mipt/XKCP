#!/usr/bin/env python3
import sys
import time
import random
import string

MAX_LEN = 15
ONE_1_HEXES = (1, 2, 4, 8)
ONE_0_HEXES = ('e', 'd', 'b', 7)

BLOCK_COUNT = 100
BLOCK_LEN = 10
MIN_LEN = 10 # in bytes
MAX_LEN = 40 # in bytes

sign = (0b0000)

def bit_256():
    pos = random.randint(0,7)
    return (1 << pos) & 0xff


def generate_random_str(length):
    return list(''.join(random.choices(string.ascii_letters, k=length)))

def change_single_bit(str_list):
    sym_idx = random.randint(0, len(str_list) - 1)
    sym = str_list[sym_idx]
    new_sym = chr(ord(sym) ^ bit_256())
    str_list[sym_idx] = new_sym
    print(ord(new_sym) - ord(sym))
    return str_list 

f = open('avalanche_effect.txt', 'w')
buffer = []
for l in range(1,10):
    s = generate_random_str(l)
    
    buffer += s
    buffer += '\n'

    for _ in range(l):
        s = change_single_bit(s)
        buffer += s
        buffer += '\n'
    
print(''.join(buffer), file=f)
f.close()

