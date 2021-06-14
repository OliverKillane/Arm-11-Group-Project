#!/bin/python
import cv2
import sys

if len(sys.argv) != 3:
	print("Usage: convert.py <input_image> <indent>")
	exit(1)

img = cv2.imread(sys.argv[1], cv2.IMREAD_UNCHANGED)

indent = "\t"*int(sys.argv[2])

for line in img:
	for pixel in line:
		value = pixel[2] + 2**8 * pixel[1] + 2**16 * pixel[0] + 2**24 * pixel[3]
		print(f"{indent}.long {hex(value)}")

