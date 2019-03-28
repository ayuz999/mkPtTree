#!/usr/bin/env python

import ROOT
from ROOT import *

import os

n=0
dirs=os.listdir('Data')
for i in dirs:
    if os.path.isfile('Data/'+i+'/auau54.root'):
        f=TFile('Data/'+i+'/auau54.root')
        n+=f.Get('number_of_Events').GetEntries()

print(n)
