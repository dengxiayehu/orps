cmake_minimum_required(VERSION 2.6)

SET(TARGET vpx)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-format -Wno-unused-result -m64 -march=x86-64 -O2 -fno-ident -fdata-sections -ffunction-sections -funwind-tables")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/alloccommon.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/blockd.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/copy_c.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/debugmodes.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/dequantize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/entropy.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/entropymode.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/entropymv.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/extend.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/filter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/findnearmv.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/generic/systemdependent.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/idct_blk.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/idctllm.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/loopfilter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/loopfilter_filters.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/mbpitch.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/mfqe.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/modecont.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/postproc.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/quant_common.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/reconinter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/reconintra.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/reconintra4x4.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/rtcd.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/setupintrarecon.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/swapyv12buffer.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/treecoder.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/variance_c.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/filter_x86.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/loopfilter_x86.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/vp8_asm_stubs.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/decoder/dboolhuff.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/decoder/decodeframe.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/decoder/decodemv.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/decoder/detokenize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/decoder/onyxd_if.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/decoder/threading.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/bitstream.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/boolhuff.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/dct.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/denoising.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/encodeframe.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/encodeintra.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/encodemb.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/encodemv.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/ethreading.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/lookahead.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/mcomp.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/modecosts.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/mr_dissim.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/onyx_if.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/pickinter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/picklpf.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/quantize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/ratectrl.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/rdopt.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/segmentation.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/tokenize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/treewriter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/vp8_cx_iface.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/vp8_dx_iface.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_alloccommon.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_blockd.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_common_data.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_convolve.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_debugmodes.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_entropy.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_entropymode.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_entropymv.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_filter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_frame_buffers.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_idct.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_loopfilter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_loopfilter_filters.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_mfqe.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_mvref_common.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_postproc.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_pred_common.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_prob.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_quant_common.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_reconinter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_reconintra.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_rtcd.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_scale.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_scan.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_seg_common.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_thread.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_thread_common.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/vp9_tile_common.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_asm_stubs.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_decodeframe.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_decodemv.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_decoder.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_detokenize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_dsubexp.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_dthread.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_read_bit_buffer.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/decoder/vp9_reader.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_aq_complexity.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_aq_cyclicrefresh.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_aq_variance.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_avg.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_bitstream.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_context_tree.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_cost.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_dct.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_denoiser.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_encodeframe.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_encodemb.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_encodemv.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_encoder.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_ethread.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_extend.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_firstpass.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_lookahead.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_mbgraph.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_mcomp.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_picklpf.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_pickmode.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_quantize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_ratectrl.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_rd.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_rdopt.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_resize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_segmentation.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_skin_detection.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_speed_features.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_subexp.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_svc_layercontext.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_temporal_filter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_tokenize.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_treewriter.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_variance.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_write_bit_buffer.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/vp9_writer.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/vp9_cx_iface.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/vp9_dx_iface.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx/src/vpx_codec.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx/src/vpx_decoder.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx/src/vpx_encoder.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx/src/vpx_image.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx/src/vpx_psnr.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/sad.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/variance.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/vpx_dsp_rtcd.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_mem/vpx_mem.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_scale/generic/gen_scalers.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_scale/generic/vpx_scale.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_scale/generic/yv12config.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_scale/generic/yv12extend.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_scale/vpx_scale_rtcd.c
  ${OUT}/gen/third_party/libvpx/copy_sse2.o
  ${OUT}/gen/third_party/libvpx/copy_sse3.o
  ${OUT}/gen/third_party/libvpx/dequantize_mmx.o
  ${OUT}/gen/third_party/libvpx/idctllm_mmx.o
  ${OUT}/gen/third_party/libvpx/idctllm_sse2.o
  ${OUT}/gen/third_party/libvpx/iwalsh_mmx.o
  ${OUT}/gen/third_party/libvpx/iwalsh_sse2.o
  ${OUT}/gen/third_party/libvpx/loopfilter_block_sse2_x86_64.o
  ${OUT}/gen/third_party/libvpx/loopfilter_mmx.o
  ${OUT}/gen/third_party/libvpx/loopfilter_sse2.o
  ${OUT}/gen/third_party/libvpx/mfqe_sse2.o
  ${OUT}/gen/third_party/libvpx/postproc_mmx.o
  ${OUT}/gen/third_party/libvpx/postproc_sse2.o
  ${OUT}/gen/third_party/libvpx/recon_mmx.o
  ${OUT}/gen/third_party/libvpx/recon_sse2.o
  ${OUT}/gen/third_party/libvpx/subpixel_mmx.o
  ${OUT}/gen/third_party/libvpx/subpixel_sse2.o
  ${OUT}/gen/third_party/libvpx/subpixel_ssse3.o
  ${OUT}/gen/third_party/libvpx/variance_impl_sse2.o
  ${OUT}/gen/third_party/libvpx/variance_impl_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp8_variance_impl_mmx.o
  ${OUT}/gen/third_party/libvpx/dct_mmx.o
  ${OUT}/gen/third_party/libvpx/dct_sse2.o
  ${OUT}/gen/third_party/libvpx/encodeopt.o
  ${OUT}/gen/third_party/libvpx/fwalsh_sse2.o
  ${OUT}/gen/third_party/libvpx/quantize_mmx.o
  ${OUT}/gen/third_party/libvpx/ssim_opt_x86_64.o
  ${OUT}/gen/third_party/libvpx/subtract_mmx.o
  ${OUT}/gen/third_party/libvpx/subtract_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_copy_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_idct_ssse3_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_intrapred_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_intrapred_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp9_loopfilter_mmx.o
  ${OUT}/gen/third_party/libvpx/vp9_mfqe_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_postproc_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_8t_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_8t_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_bilinear_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_bilinear_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp9_dct_mmx.o
  ${OUT}/gen/third_party/libvpx/vp9_dct_ssse3_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_error_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_quantize_ssse3_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_ssim_opt_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_subpel_variance.o
  ${OUT}/gen/third_party/libvpx/vp9_subtract_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_temporal_filter_apply_sse2.o
  ${OUT}/gen/third_party/libvpx/sad4d_sse2.o
  ${OUT}/gen/third_party/libvpx/sad_mmx.o
  ${OUT}/gen/third_party/libvpx/sad_sse2.o
  ${OUT}/gen/third_party/libvpx/sad_sse3.o
  ${OUT}/gen/third_party/libvpx/sad_sse4.o
  ${OUT}/gen/third_party/libvpx/sad_ssse3.o
  ${OUT}/gen/third_party/libvpx/variance_impl_mmx.o
  ${OUT}/gen/third_party/libvpx/emms.o
  ${OUT}/gen/third_party/libvpx/x86_abi_support.o
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  ${WEBRTC_ROOT}/third_party/libvpx/source/config/linux/x64
  ${WEBRTC_ROOT}/third_party/libvpx/source/config
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/decoder
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder
  )

ADD_CUSTOM_COMMAND(OUTPUT
  ${OUT}/gen/third_party/libvpx/copy_sse2.o
  ${OUT}/gen/third_party/libvpx/copy_sse3.o
  ${OUT}/gen/third_party/libvpx/dequantize_mmx.o
  ${OUT}/gen/third_party/libvpx/idctllm_mmx.o
  ${OUT}/gen/third_party/libvpx/idctllm_sse2.o
  ${OUT}/gen/third_party/libvpx/iwalsh_mmx.o
  ${OUT}/gen/third_party/libvpx/iwalsh_sse2.o
  ${OUT}/gen/third_party/libvpx/loopfilter_block_sse2_x86_64.o
  ${OUT}/gen/third_party/libvpx/loopfilter_mmx.o
  ${OUT}/gen/third_party/libvpx/loopfilter_sse2.o
  ${OUT}/gen/third_party/libvpx/mfqe_sse2.o
  ${OUT}/gen/third_party/libvpx/postproc_mmx.o
  ${OUT}/gen/third_party/libvpx/postproc_sse2.o
  ${OUT}/gen/third_party/libvpx/recon_mmx.o
  ${OUT}/gen/third_party/libvpx/recon_sse2.o
  ${OUT}/gen/third_party/libvpx/subpixel_mmx.o
  ${OUT}/gen/third_party/libvpx/subpixel_sse2.o
  ${OUT}/gen/third_party/libvpx/subpixel_ssse3.o
  ${OUT}/gen/third_party/libvpx/variance_impl_sse2.o
  ${OUT}/gen/third_party/libvpx/variance_impl_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp8_variance_impl_mmx.o
  ${OUT}/gen/third_party/libvpx/dct_mmx.o
  ${OUT}/gen/third_party/libvpx/dct_sse2.o
  ${OUT}/gen/third_party/libvpx/encodeopt.o
  ${OUT}/gen/third_party/libvpx/fwalsh_sse2.o
  ${OUT}/gen/third_party/libvpx/quantize_mmx.o
  ${OUT}/gen/third_party/libvpx/ssim_opt_x86_64.o
  ${OUT}/gen/third_party/libvpx/subtract_mmx.o
  ${OUT}/gen/third_party/libvpx/subtract_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_copy_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_idct_ssse3_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_intrapred_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_intrapred_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp9_loopfilter_mmx.o
  ${OUT}/gen/third_party/libvpx/vp9_mfqe_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_postproc_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_8t_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_8t_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_bilinear_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_subpixel_bilinear_ssse3.o
  ${OUT}/gen/third_party/libvpx/vp9_dct_mmx.o
  ${OUT}/gen/third_party/libvpx/vp9_dct_ssse3_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_error_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_quantize_ssse3_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_ssim_opt_x86_64.o
  ${OUT}/gen/third_party/libvpx/vp9_subpel_variance.o
  ${OUT}/gen/third_party/libvpx/vp9_subtract_sse2.o
  ${OUT}/gen/third_party/libvpx/vp9_temporal_filter_apply_sse2.o
  ${OUT}/gen/third_party/libvpx/sad4d_sse2.o
  ${OUT}/gen/third_party/libvpx/sad_mmx.o
  ${OUT}/gen/third_party/libvpx/sad_sse2.o
  ${OUT}/gen/third_party/libvpx/sad_sse3.o
  ${OUT}/gen/third_party/libvpx/sad_sse4.o
  ${OUT}/gen/third_party/libvpx/sad_ssse3.o
  ${OUT}/gen/third_party/libvpx/variance_impl_mmx.o
  ${OUT}/gen/third_party/libvpx/emms.o
  ${OUT}/gen/third_party/libvpx/x86_abi_support.o
  COMMAND mkdir -p ${OUT}/gen/third_party/libvpx
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/copy_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/copy_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/copy_sse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/copy_sse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/dequantize_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/dequantize_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/idctllm_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/idctllm_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/idctllm_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/idctllm_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/iwalsh_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/iwalsh_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/iwalsh_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/iwalsh_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/loopfilter_block_sse2_x86_64.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/loopfilter_block_sse2_x86_64.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/loopfilter_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/loopfilter_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/loopfilter_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/loopfilter_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/mfqe_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/mfqe_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/postproc_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/postproc_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/postproc_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/postproc_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/recon_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/recon_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/recon_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/recon_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/subpixel_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/subpixel_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/subpixel_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/subpixel_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/subpixel_ssse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/subpixel_ssse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/variance_impl_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/variance_impl_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/variance_impl_ssse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/variance_impl_ssse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp8_variance_impl_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/vp8_variance_impl_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/dct_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/dct_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/dct_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/dct_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/encodeopt.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/encodeopt.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/fwalsh_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/fwalsh_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/quantize_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/quantize_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/ssim_opt_x86_64.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/ssim_opt_x86_64.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/subtract_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/subtract_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/subtract_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/subtract_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_copy_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_copy_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_idct_ssse3_x86_64.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_idct_ssse3_x86_64.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_intrapred_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_intrapred_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_intrapred_ssse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_intrapred_ssse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_loopfilter_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_loopfilter_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_mfqe_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_mfqe_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_postproc_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_postproc_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_subpixel_8t_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_subpixel_8t_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_subpixel_8t_ssse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_subpixel_8t_ssse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_subpixel_bilinear_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_subpixel_bilinear_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_subpixel_bilinear_ssse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_subpixel_bilinear_ssse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_dct_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_dct_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_dct_ssse3_x86_64.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_dct_ssse3_x86_64.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_error_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_error_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_quantize_ssse3_x86_64.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_quantize_ssse3_x86_64.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_ssim_opt_x86_64.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_ssim_opt_x86_64.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_subpel_variance.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_subpel_variance.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_subtract_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_subtract_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/vp9_temporal_filter_apply_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_temporal_filter_apply_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/sad4d_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad4d_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/sad_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/sad_sse2.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad_sse2.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/sad_sse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad_sse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/sad_sse4.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad_sse4.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/sad_ssse3.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad_ssse3.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/variance_impl_mmx.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/variance_impl_mmx.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/emms.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_ports/emms.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/x86_abi_support.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_ports/x86_abi_support.asm
  COMMAND ${OUT}/yasm -D CHROMIUM -I source/config/linux/x64 -I source/config -I source/libvpx -DPIC -felf64 -m amd64 -o ${OUT}/gen/third_party/libvpx/x86_abi_support.o ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_ports/x86_abi_support.asm
  DEPENDS yasm
  WORKING_DIRECTORY ${TARGET_ROOT}
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET vpx_intrinsics_avx2)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -mavx2 -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_loopfilter_intrin_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_subpixel_8t_intrin_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_dct_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_error_intrin_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_subpel_variance_impl_intrin_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_variance_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad4d_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/sad_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/variance_avx2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/variance_impl_avx2.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/libvpx/source/config/linux/x64
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET vpx_intrinsics_mmx)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -mmmx -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/idct_blk_mmx.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/vp8_variance_mmx.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/vp8_enc_stubs_mmx.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/variance_mmx.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/libvpx/source/config/linux/x64
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET vpx_intrinsics_sse4_1)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -msse4.1 -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/quantize_sse4.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/libvpx/source/config/linux/x64
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET vpx_intrinsics_ssse3)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -mssse3 -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/variance_ssse3.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/quantize_ssse3.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_subpixel_8t_intrin_ssse3.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_dct_ssse3.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/libvpx/source/config/linux/x64
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET vpx_intrinsics_sse2)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -msse2 -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/idct_blk_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/recon_wrapper_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/common/x86/vp8_variance_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/denoising_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/quantize_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp8/encoder/x86/vp8_enc_stubs_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_idct_intrin_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/common/x86/vp9_loopfilter_intrin_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_avg_intrin_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_dct_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_denoiser_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_quantize_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vp9/encoder/x86/vp9_variance_sse2.c
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx/vpx_dsp/x86/variance_sse2.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/libvpx/source/config/linux/x64
  ${WEBRTC_ROOT}/third_party/libvpx/source/libvpx
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")
