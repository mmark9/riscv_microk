#!/bin/python3

import sys


def bits(v, pos, n):
    x = ((((0x1 << n) - 1) << pos) & v) >> pos
    return x


y = 13
z = bits(y, 0, 1)


def try_int(int_val):
    try:
        return int(int_val)
    except:
        return int(int_val, 16)


if __name__ == '__main__':
    if len(sys.argv) == 4:
        val = try_int(sys.argv[1])
        n = try_int(sys.argv[2])
        pos_ = try_int(sys.argv[3])
        val_ = bits(val, pos_, n)
        print('{}   {}'.format(val_, bin(val_)))