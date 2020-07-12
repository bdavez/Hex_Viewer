#!/usr/bin/env python3

#Hex Viewer !!! Opens filez in rb mode, should be able to read any filez... 

name = input("Please enter a filez name: ")

filez = open(name, "rb")
i = 0
buff = []

while filez.read(1):
    i += 1

offset = 000000

filez.seek(0,0)
for z in range(0,i,16):
    print("0000{0:8}".format(hex(offset)[2::]),end="\t")

    for x in range(0,16):
        buff.append(filez.read(1).hex())

    for x in buff:
        if not x:
            print('00',end='')
        print(x,end=' ')
    
    for x in buff:
        if x == '':
            x = "0"
        y = int(x,16)
        if y >= 32 and y <= 126:
            print(chr(y), end='')
        else:
            print(".",end='')
        
    print('')
    buff = []
    offset += 16

print("Total Length is: {}".format(i))