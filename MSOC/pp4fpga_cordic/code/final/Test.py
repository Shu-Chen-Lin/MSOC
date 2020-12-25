
# coding: utf-8

# In[ ]:


from __future__ import print_function

import sys
import numpy as np
from time import time
import matplotlib.pyplot as plt 

sys.path.append('/home/xilinx')
from pynq import Overlay
from pynq import allocate

if __name__ == "__main__":
    print("Entry:", sys.argv[0])
    print("System argument(s):", len(sys.argv))

    print("Start of \"" + sys.argv[0] + "\"")

    ol = Overlay("/home/xilinx/f04525034/cordic/design_1.bit")
    ipCordic = ol.cordic_0
    numSamples = 90
    
    
    inBuffer0 = allocate(shape=(numSamples,), dtype=np.float32)
    outBuffer0 = allocate(shape=(numSamples,), dtype=np.float32)
    outBuffer1 = allocate(shape=(numSamples,), dtype=np.float32)
    #fiSamples.seek(0)
    for i in range(1,numSamples):
        inBuffer0[i] = i*np.pi/180
    
    timeKernelStart = time()
    ipCordic.write(0x10, inBuffer0.device_address)
    ipCordic.write(0x18, outBuffer0.device_address)
    ipCordic.write(0x20, outBuffer1.device_address)
    ipCordic.write(0x00, 0x01)
    while (ipCordic.read(0x00) & 0x4) == 0x0:
        continue
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")
    
    Total_err_s = 0;
    Total_err_c = 0;
    for i in range(1,numSamples):
        zs = np.sin(i*np.pi/180)
        zc = np.cos(i*np.pi/180)
        err_sin = ((outBuffer0[i]-zs)/zs)*100
        err_cos = ((outBuffer1[i]-zc)/zc)*100
        Total_err_s += err_sin
        Total_err_c += err_cos
    
    print("Total cos error: {}, Total sin error: {}".format(Total_err_s, Total_err_c))

    print("============================")
    print("Exit process")

