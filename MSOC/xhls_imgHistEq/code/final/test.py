
# coding: utf-8

# In[ ]:


from __future__ import print_function

import sys
import numpy as np
from PIL import Image
from time import time
import matplotlib.pyplot as plt 

sys.path.append('/home/xilinx')
from pynq import Overlay
from pynq import allocate

if __name__ == "__main__":
    print("Entry:", sys.argv[0])
    print("System argument(s):", len(sys.argv))

    print("Start of \"" + sys.argv[0] + "\"")
    
    ol = Overlay("/home/xilinx/f04525034/histogram/design_1.bit")
    ipHist = ol.top_img_hist_equaliz1_0
    
    im = Image.open("/home/xilinx/f04525034/histogram/test_1080p.bmp")
    img = np.array(im).astype(np.uint8)
    
    #Buf = np.zeros(1080,dtype=np.int32)
    #for i in range(3):
    #    print(i*8)
    #    print(img[:,0,i]<<(i*8))
    #    Buf += img[:,0,i]<<(i*8)
    #print(Buf[0])
    
    test = img.transpose(1,0,2).reshape((-1,3))
    print(img.shape)
    plt.title("Original colored image")
    plt.imshow(img)
    plt.show()
    
    plt.title("Original greyscaled image")
    plt.imshow(np.dstack((img[:,:,1],img[:,:,1],img[:,:,1])))
    plt.show()    
    
    cdf = np.loadtxt("/home/xilinx/f04525034/histogram/CDF.txt", dtype=np.int32)
        
    inBuffer0 = allocate(shape=(2073600,), dtype=np.uint8)
    inBuffer1 = allocate(shape=(2073600,), dtype=np.uint8)
    inBuffer2 = allocate(shape=(2073600,), dtype=np.uint8)
    outBuffer0 = allocate(shape=(2073600,), dtype=np.uint8)
    outBuffer1 = allocate(shape=(2073600,), dtype=np.uint8)
    outBuffer2 = allocate(shape=(2073600,), dtype=np.uint8)
    
    inBuffer0[:] = test[:,1]
    inBuffer1[:] = test[:,1]
    inBuffer2[:] = test[:,1]
       
    timeKernelStart = time()
    ipHist.write(0x10, 1920) #Width
    ipHist.write(0x18, 1080) #Height
    
    for i in range(256):
        ipHist.write(0x400+i*4, int(cdf[i]))
        
    ipHist.write(0xc00,inBuffer0.device_address)
    ipHist.write(0xc08,inBuffer1.device_address)
    ipHist.write(0xc10,inBuffer2.device_address)
    
    ipHist.write(0xc18,outBuffer0.device_address)
    ipHist.write(0xc20,outBuffer1.device_address)
    ipHist.write(0xc28,outBuffer2.device_address)
    
    ipHist.write(0x00, 0x01)
    
    while (ipHist.read(0x00) & 0x4) == 0x0:
        continue
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")
    
    Out = np.dstack((outBuffer0,outBuffer1,outBuffer2))
    Out = Out.reshape((-1,1080,3)).transpose(1,0,2)   
    
    plt.title("Equalized image")
    plt.imshow(Out)
    plt.show()
    