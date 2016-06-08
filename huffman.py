#!/usr/bin/env python
from os import devnull
from sys import argv
from subprocess import Popen

def decompress(input_file):
    output_file = input_file[:-5]
    proc = Popen(['./hdecode', input_file, output_file])
    proc.wait()

def compress(input_file):
    output_file = input_file + '.huff'
    proc = Popen(['./hencode', input_file, output_file])
    if not proc.wait():
        new_proc = Popen(['./hanalysis', output_file])
        new_proc.wait()

def main():
    if len(argv) == 1:
        print "usage: %s (compress|decompress) file" % (argv[0])
        exit(1)
    if argv[1] == "decompress":
        print "begin decompressing"
        decompress(argv[2])
    elif argv[1] == "compress":
        print "begin compressing"
        compress(argv[2])

if __name__ == '__main__':
    main()