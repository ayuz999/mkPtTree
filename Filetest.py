#!/usr/bin/env python

import ROOT
import os
from ROOT import *

dirs=os.listdir('Finished')
for item in dirs:
    if os.path.isfile('Finished/'+item):
        f = TFile('Finished/'+item)
        if f.IsZombie() != 0:
            print('Zombie found in '+item)
        #else:
        #    print(item+' fine')
