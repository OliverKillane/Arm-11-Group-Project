# Attempt to mkae autowriter for binary images:
# takes image filename and colour as arguments.
# every black pixel in the image is set to the colour arg
#
# e.g filename: image.bmp  colourreg: R4

# For a basci test try prepending to the file:
# mov r0, #0x1000
# mov r1, #0x00FF0000
#
# and at the end add:
# loop:
# b loop

from PIL import Image
import sys

VIDEO_POINTER = 0x1000000

def getpixels(filename: str) -> list[tuple[int, int]]:
    # get the image, height width
    image : Image = Image.open(filename)
    
    width, height = image.size

    pixels : list[tuple[int, int]] = list()
    
    for y in range(height):
        for x in range(width):
            if image.getpixel((x,y)) != 255:
                pixels.append((x,y))

    # return the pixels and the screen width
    return pixels, width

def generatedraw(pixels : list[tuple[int, int]], width: str, name: str) -> str:
    # r0 <- where to start writing
    # r1 <- colour to display in select pixels
    
    # calling convention dictates: r0-3 are argument, r4-11 are local variables. r4-11 must be preserved
    result : str = name + ":\n" + "\n".join(["push r" + str(reg)for reg in range(4,12)])

    # setup positions for writing
    lastpos : int= 0
    diff : int = 0

    # r4 will contain the position so starts where frame will be drawn.
    result += "\nmov r4, r0"
    
    for pos in map(lambda pos : (pos[0] + pos[1] * width) * 4, pixels):

        # get difference and update lastpos
        diff = pos - lastpos
        lastpos = pos

        # update r4
        while(diff > 0xff):
            result += "\nadd r4, r4, #0xff"
            diff -= 0xff
        
        #if any remaining:
        if (diff > 0):
            result += "\nadd r4, r4, #" + str(diff)
            
        #alter the pixel
        result += "\nstr r1, [r4]"

    #draw to screen by storing start of buffer in the video pointer
    result += "\nldr r4, =" + str(hex(VIDEO_POINTER))
    result += "\nstr r0, [r4]"

    #put local vars back
    result += "\n" + "\n".join(["pop r" + str(reg)for reg in range(11,3,-1)])

    #return from function
    result += "\nret"

    # return the ARM asm
    return result

def generate():
    if (len(sys.argv) == 2):
        try:
            pixels, width = getpixels(sys.argv[1], "draw" + sys.argv[1].split(".")[0])

            with open(sys.argv[1].split(".")[0] + ".s", "w") as file:
                file.write(generatedraw(pixels, width))
        except FileNotFoundError:
            print("incorrect filename, cannot find!\a")
    else:
        print("incorrect arguments, just one filename please!\a")

# run program
generate()

                
    
    
