
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
    
    ol = Overlay("/home/xilinx/f04525034/fp_accum/design_1.bit")
    ipFp = ol.hls_fp_accumulator_0
            
    inBuffer0 = allocate(shape=(128,), dtype=np.float32)
    
    gold = np.float32(0)
    for i in range(128):
        inBuffer0[i] = np.float32(i)/2
        gold += inBuffer0[i]
       
    timeKernelStart = time()        
    ipFp.write(0x10,inBuffer0.device_address)
    
    ipFp.write(0x00, 0x01)
    
    while (ipFp.read(0x00) & 0x4) == 0x0:
        continue
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")
    
    out = ipFp.read(0x18)
    err = (np.float32)(out)/65536-gold
    
    print("Total error: {}".format(err))

    print("============================")
    print("Exit process")
    