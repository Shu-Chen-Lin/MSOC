############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project solution2
set_top blockmatmul
add_files source/block_mm.h
add_files source/block_mm.cpp
add_files -tb source/block_mm-top.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution2"
set_part {xc7z020-clg484-1}
create_clock -period 10 -name default
source "./solution2/solution2/directives.tcl"
csim_design -ldflags {-Wl,--stack=268435456} -clean
csynth_design
cosim_design -ldflags {-Wl,--stack=268435456}
export_design -format ip_catalog
