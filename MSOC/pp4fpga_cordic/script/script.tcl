############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project solution2
set_top cordic
add_files source/cordic_fixed.cpp
add_files source/cordic_fixed.h
add_files -tb source/cordic-top.cpp
open_solution "solution2"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./solution2/solution2/directives.tcl"
csim_design
csynth_design
cosim_design -tool xsim
export_design -format ip_catalog
