#!/usr/bin/env python

import os, mmap,sys

src=mmap.mmap(os.open(sys.argv[1], os.O_RDONLY), 0, prot=mmap.PROT_READ)

trg1=open("610001.list","a")
trg2=open("610011.list","a")
trg3=open("610021.list","a")
trg4=open("610031.list","a")
trg5=open("610041.list","a")
trg6=open("610051.list","a")
remain=open("remain.list","a")

while True:
    line=src.readline()
    if str(line) != '' :
        currRun=int(str(line).split('/')[9])
        if currRun >= 19130078 and currRun <= 19131031:
            trg1.write(str(line))
            continue
        elif currRun >= 19131037 and currRun <= 19140029:
            trg2.write(str(line))
            continue
        elif currRun >= 19140030 and currRun <= 19143019:
            trg3.write(str(line))
            continue
        elif currRun >= 19144012 and currRun <= 19144033:
            trg4.write(str(line))
            continue
        elif currRun >= 19144036 and currRun <= 19145031:
            trg5.write(str(line))
            continue
        elif currRun >= 19145034 and currRun <= 19168040:
            trg6.write(str(line))
            continue
        else:
            remain.write(str(line))
    else:
        break

trg1.close()
trg2.close()
trg3.close()
trg4.close()
trg5.close()
trg6.close()
