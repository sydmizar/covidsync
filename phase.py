#!/usr/bin/env python
# -*- coding: utf-8 -*-

import string
import sys
import numpy as np
from numpy import *
from scipy.fftpack import hilbert

def x2APFx(x):
	x=array(x)
	Hx=-hilbert(x)
	phx=np.arctan2(Hx,x)
        return phx

if __name__=='__main__':
	x=[]
	lines=sys.stdin.readlines()
	for line in lines:
         x.append(float(line))
	phx=x2APFx(x)
        T=len(x)
 	for i in range(0,T):
          print phx[i]

