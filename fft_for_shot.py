#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Tue Aug  1 09:55:44 2017

@author: sean
"""
import numpy 
import matplotlib.pylab as pt
import scipy
import scipy.fftpack
from matplotlib.ticker import EngFormatter
import matplotlib.ticker as ticker
from matplotlib.ticker import NullFormatter

data=numpy.loadtxt('1003.txt')
tranf=numpy.fft.fft(data[0,:])

#FFT = scipy.fftpack.fftshift(FFT)

FFT_all = abs(scipy.fft(data[0,:]))
FFT_all=FFT_all[0:FFT_all.size/2+1]
freqs = scipy.fftpack.fftfreq(data[0,:].size, 0.00025)
freqs=freqs[0:freqs.size/2+1]

for i in range(1,48):
    FFT = abs(scipy.fft(data[i,:]))
    FFT=FFT[0:FFT.size/2+1]
    FFT_all += FFT
   
FFT_all = FFT_all / 48.0
#FFT_all=numpy.log10(FFT_all)
fig, ax = pt.subplots(figsize=(20,6))
formatter = EngFormatter(unit='Hz')
ax.xaxis.set_major_formatter(formatter)
ax.xaxis.set_major_locator(ticker.MaxNLocator(15))
ax.xaxis.set_minor_locator(ticker.MaxNLocator(150))
ax.yaxis.set_minor_formatter(NullFormatter())

ax.grid(True, zorder=5)

pt.xlabel('Frequency')
pt.ylabel('Amplitude')

ax.plot(freqs,FFT_all,color='navy',linewidth=1.4)
pt.show()
pt.savefig('1003.jpg',format='jpeg', dpi = 1000,bbox_inches='tight')