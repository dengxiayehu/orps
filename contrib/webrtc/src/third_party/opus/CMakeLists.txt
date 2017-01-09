cmake_minimum_required(VERSION 2.6)

SET(TARGET opus)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/opus/src/celt/bands.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/celt.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/celt_decoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/celt_encoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/celt_lpc.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/cwrs.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/entcode.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/entdec.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/entenc.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/kiss_fft.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/laplace.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/mathops.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/mdct.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/modes.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/pitch.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/quant_bands.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/rate.c
  ${WEBRTC_ROOT}/third_party/opus/src/celt/vq.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/A2NLSF.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/ana_filt_bank_1.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/biquad_alt.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/bwexpander.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/bwexpander_32.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/check_control_input.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/CNG.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/code_signs.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/control_audio_bandwidth.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/control_codec.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/control_SNR.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/debug.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/dec_API.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/decode_core.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/decode_frame.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/decode_indices.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/decode_parameters.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/decode_pitch.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/decode_pulses.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/decoder_set_fs.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/enc_API.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/encode_indices.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/encode_pulses.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/gain_quant.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/HP_variable_cutoff.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/init_decoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/init_encoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/inner_prod_aligned.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/interpolate.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/lin2log.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/log2lin.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/LP_variable_cutoff.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/LPC_analysis_filter.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/LPC_inv_pred_gain.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF2A.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF_decode.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF_del_dec_quant.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF_encode.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF_stabilize.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF_unpack.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF_VQ.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NLSF_VQ_weights_laroia.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NSQ.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/NSQ_del_dec.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/pitch_est_tables.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/PLC.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/process_NLSFs.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/quant_LTP_gains.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler_down2.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler_down2_3.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler_private_AR2.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler_private_down_FIR.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler_private_IIR_FIR.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler_private_up2_HQ.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/resampler_rom.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/shell_coder.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/sigm_Q15.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/sort.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/stereo_decode_pred.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/stereo_encode_pred.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/stereo_find_predictor.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/stereo_LR_to_MS.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/stereo_MS_to_LR.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/stereo_quant_pred.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/sum_sqr_shift.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/table_LSF_cos.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/tables_gain.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/tables_LTP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/tables_NLSF_CB_NB_MB.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/tables_NLSF_CB_WB.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/tables_other.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/tables_pitch_lag.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/tables_pulses_per_block.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/VAD.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/VQ_WMat_EC.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/analysis.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/mlp.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/mlp_data.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/opus.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/opus_decoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/opus_encoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/opus_multistream.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/opus_multistream_decoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/opus_multistream_encoder.c
  ${WEBRTC_ROOT}/third_party/opus/src/src/repacketizer.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/apply_sine_window_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/autocorrelation_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/burg_modified_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/bwexpander_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/corrMatrix_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/encode_frame_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/energy_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/find_LPC_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/find_LTP_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/find_pitch_lags_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/find_pred_coefs_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/inner_product_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/k2a_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/levinsondurbin_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/LPC_analysis_filter_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/LPC_inv_pred_gain_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/LTP_analysis_filter_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/LTP_scale_ctrl_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/noise_shape_analysis_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/pitch_analysis_core_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/prefilter_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/process_gains_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/regularize_correlations_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/residual_energy_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/scale_copy_vector_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/scale_vector_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/schur_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/solve_LS_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/sort_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/warped_autocorrelation_FLP.c
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float/wrappers_FLP.c
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
  ${WEBRTC_ROOT}/third_party/opus/src/celt
  ${WEBRTC_ROOT}/third_party/opus/src/include
  ${WEBRTC_ROOT}/third_party/opus/src/silk
  ${WEBRTC_ROOT}/third_party/opus/src/silk/float
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;OPUS_BUILD;OPUS_EXPORT=;HAVE_LRINT;HAVE_LRINTF;VAR_ARRAYS;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")
