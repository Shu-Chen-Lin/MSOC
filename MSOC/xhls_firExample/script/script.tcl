############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project firExample
set_top fir_filter
add_files fir.cpp
add_files -tb fir_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb data -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution2"
set_part {xc7z020-clg484-1}
create_clock -period 10 -name default
source "./firExample/solution2/directives.tcl"
csim_design -clean
csynth_design
cosim_design -tool xsim
export_design -format ip_catalog
