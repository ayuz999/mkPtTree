#!/bin/bash

curdir=`pwd`
for dir in `ls Data`;do 
    if [ ! -e Data/$dir/job.out ];then
        echo $dir 
        condor_submit Data/$dir/subq.con
    fi
done
