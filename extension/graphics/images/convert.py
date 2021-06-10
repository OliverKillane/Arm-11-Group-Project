#!/bin/python
import cv2
import sys

if len(sys.argv) != 2:
	print("Usage: convert.py <input_image>")
	exit(1)

img = cv2.imread(sys.argv[1])

for line in img:
	for pixel in line:
		value = pixel[2] + 2**8 * pixel[1] + 2**16 * pixel[0]
		print(f".long {hex(value)}")

