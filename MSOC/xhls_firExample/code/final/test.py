
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
    
    ol = Overlay("/home/xilinx/f04525034/FIR/design_1.bit")
    ipfir = ol.fir_filter_0
    
    gold = np.loadtxt("/home/xilinx/f04525034/FIR/ref_res.txt", dtype=np.float32)
    coef = np.loadtxt("/home/xilinx/f04525034/FIR/fir_coeff.txt", dtype=np.float32)
    In = np.loadtxt("/home/xilinx/f04525034/FIR/input.txt", dtype=np.float32)
    
    
    inBuffer0 = allocate(shape=(1024,), dtype=np.float32)
    outBuffer0 = allocate(shape=(1024,), dtype=np.float32)
    
    Coef = np.round(coef*2**16).astype(np.int32)
    for i in range(16):
        ipfir.write(0x40+i*4,int(Coef[i]))
    
    for i in range(1024):
        inBuffer0[i] = In[i]
    
    timeKernelStart = time()        
    ipfir.write(0x10,inBuffer0.device_address)    
    ipfir.write(0x80,outBuffer0.device_address)
    
    ipfir.write(0x00, 0x01)
    
    while (ipfir.read(0x00) & 0x4) == 0x0:
        continue
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")
    
    err = 0
    for i in range(1024):
        err = err+(outBuffer0[i]-gold[i])
    
    print("Total error: {}".format(err))

    print("============================")
    print("Exit process")
    