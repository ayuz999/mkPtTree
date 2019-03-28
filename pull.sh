#!/bin/bash

n=0
m=0
curdir=`pwd`
for dir in `ls Data`;do
    HELD=`cat Data/$dir/job.log| grep 'return value 0'`
    if [ -n "$HELD" ]; then
      echo $dir
      #echo $HELD
        #echo $dir  #>> LOG/log2
        ((n++))
        cp Data/$dir/auau27.root roots2/${n}.root
        rm -r Data/$dir/
    fi
    #HELD=`grep "return value 0" Data/$dir/job.log | wc -l`
    #if [ -n "$HELD" ]; then
    #    echo task $dir $HELD
    #    if [ $HELD -gt 1 ] ;then
    #      ((m++))
    #    fi
    #    #cp  Data/$dir/auau27.root  Finished_11/${m}.root
    #    #mv  Data/$dir              BackupRuns11
    #fi
done
echo n:  $n
echo m:  $m
#diff LOG/log2 LOG/log3
