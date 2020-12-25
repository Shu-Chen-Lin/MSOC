
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
    
    ol = Overlay("/home/xilinx/f04525034/matmul/design_1.bit")
    ipmm = ol.matrixmul_0
    
    gold = np.loadtxt("/home/xilinx/f04525034/matmul/gold.txt", dtype=np.int32)
        
    inBuffer0 = allocate(shape=(1024,), dtype=np.uint32)
    inBuffer1 = allocate(shape=(1024,), dtype=np.uint32)
    outBuffer0 = allocate(shape=(1024,), dtype=np.uint32)
    
    for i in range(32):
        for j in range(32):
            inBuffer0[i*32+j] = i+j
            inBuffer1[i*32+j] = i+j
       
    timeKernelStart = time()        
    ipmm.write(0x10,inBuffer0.device_address)
    ipmm.write(0x18,inBuffer1.device_address)    
    ipmm.write(0x20,outBuffer0.device_address)
    
    ipmm.write(0x00, 0x01)
    
    while (ipmm.read(0x00) & 0x4) == 0x0:
        continue
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")
    
    err = 0
    for i in range(32):
        for j in range(32): 
            err = err+(outBuffer0[i*32+j]-gold[i*32+j])
    
    print("Total error: {}".format(err))

    print("============================")
    print("Exit process")
    