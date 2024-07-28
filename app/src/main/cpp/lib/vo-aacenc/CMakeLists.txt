cmake_minimum_required(VERSION 3.4.1)

set(vo_aacenc_path .)
set(VO_COMMON ./common)
set(ENC_SRC ./aacenc/src)

message("enter vo-aacenc")


add_library(vo-aacenc
        SHARED
        ${VO_COMMON}/cmnMemory.c
    aacenc/basic_op/basicop2.c
    aacenc/basic_op/oper_32b.c
    ${ENC_SRC}/aac_rom.c
    ${ENC_SRC}/aacenc.c
    ${ENC_SRC}/aacenc_core.c
    ${ENC_SRC}/adj_thr.c
    ${ENC_SRC}/band_nrg.c
    ${ENC_SRC}/bit_cnt.c
    ${ENC_SRC}/bitbuffer.c
    ${ENC_SRC}/bitenc.c
    ${ENC_SRC}/block_switch.c
    ${ENC_SRC}/channel_map.c
    ${ENC_SRC}/dyn_bits.c
    ${ENC_SRC}/grp_data.c
    ${ENC_SRC}/interface.c
    ${ENC_SRC}/line_pe.c
    ${ENC_SRC}/memalign.c
    ${ENC_SRC}/ms_stereo.c
    ${ENC_SRC}/pre_echo_control.c
    ${ENC_SRC}/psy_configuration.c
    ${ENC_SRC}/psy_main.c
    ${ENC_SRC}/qc_main.c
    ${ENC_SRC}/quantize.c
    ${ENC_SRC}/sf_estim.c
    ${ENC_SRC}/spreading.c
    ${ENC_SRC}/stat_bits.c
    ${ENC_SRC}/tns.c
    ${ENC_SRC}/transform.c
  )

target_include_directories(vo-aacenc
  PRIVATE
        ${vo_aacenc_path}/aacenc/inc
        ${vo_aacenc_path}/aacenc/basic_op
        ${vo_aacenc_path}/common/include
  )
