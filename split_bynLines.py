#! /usr/bin/env python                                                                                                                                                                  

import os, mmap, math, sys

src=mmap.mmap(os.open(sys.argv[1], os.O_RDONLY), 0, prot=mmap.PROT_READ)
src2=file(sys.argv[1])
os.mkdir('Data', 0755)

row=50.
ndirs=int(math.ceil(len(src2.readlines()) / row))
for i in range(1, ndirs+1):
        os.mkdir('Data/'+str(i), 0755)

n=0
while(True):
    line=src.readline()
    if line != "": 
        m= n / int(row)
        f=open('Data/'+str(m+1)+'/file.list', 'a')
        f.write(line) 
        f.close()
        n+=1    
    else:
        break
