############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_dataflow "top_img_hist_equaliz1"
set_directive_pipeline "compute_cdf/CDF_L2"
set_directive_pipeline "yuv2rgb/Lx"
set_directive_pipeline "rgb2yuv/Lx"
set_directive_pipeline "img_hist_equaliz1/Lx"
set_directive_pipeline "update_histogram/L0"

set_directive_dependence -variable hist -type intra -dependent false "img_hist_equaliz1"
