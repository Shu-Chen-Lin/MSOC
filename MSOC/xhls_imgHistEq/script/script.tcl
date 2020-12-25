############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project histEq
set_top top_img_hist_equaliz1
add_files src3/img_hist1.cpp
add_files -tb src3/ap_bmp.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb src3/main_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb src3/ref_img_hist.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb src3/test_data -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution3"
set_part {xc7z020-clg484-1}
create_clock -period 160MHz -name default
config_dataflow -default_channel fifo -fifo_depth 2
config_export -format ip_catalog -rtl verilog
source "./histEq/solution3/directives.tcl"
csim_design -ldflags {-Wl,--stack=268435456} -clean
csynth_design
cosim_design -ldflags {-Wl,--stack=268435456}
export_design -rtl verilog -format ip_catalog
