############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_array_partition -type complete -dim 1 "fir_filter" shift_reg
set_directive_interface -mode s_axilite "fir_filter"
set_directive_stream -dim 1 "fir_filter" In
set_directive_stream -dim 1 "fir_filter" y
set_directive_pipeline -II 1 "fir_filter/fir_filter_label1"
set_directive_interface -mode m_axi -depth 1024 -offset slave "fir_filter" y
set_directive_interface -mode m_axi -depth 1024 -offset slave "fir_filter" In
set_directive_interface -mode s_axilite -depth 16 "fir_filter" coef
