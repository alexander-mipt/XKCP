#!/usr/bin/env python3
from os import abort
import sys
import time
import random
import string
import argparse


def main():

    f = open('ascii_table.txt', 'w')
   
    for i in range(256):
        print(chr(i), file=f, end='\n')

    f.close()

if __name__ == '__main__':
    main()