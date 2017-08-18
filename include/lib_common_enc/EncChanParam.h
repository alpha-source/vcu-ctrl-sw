/******************************************************************************
*
* Copyright (C) 2017 Allegro DVT2.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX OR ALLEGRO DVT2 BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of  Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
*
* Except as contained in this notice, the name of Allegro DVT2 shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Allegro DVT2.
*
******************************************************************************/

/****************************************************************************
   -----------------------------------------------------------------------------
 **************************************************************************//*!
   \addtogroup lib_base
   @{
   \file
 *****************************************************************************/

#pragma once

#include "lib_rtos/types.h"
#include "lib_common/SliceConsts.h"

/*************************************************************************//*!
   \brief Picture format enum
*****************************************************************************/
typedef enum __AL_ALIGNED__ (4) AL_e_PictFormat
{
  AL_420_8BITS = 0x0188,
  AL_422_8BITS = 0x0288,
  AL_420_10BITS = 0x01AA,
  AL_422_10BITS = 0x02AA,
} AL_EPicFormat;

#define AL_GET_BITDEPTH_LUMA(PicFmt) ((PicFmt) & 0x000F)
#define AL_GET_BITDEPTH_CHROMA(PicFmt) (((PicFmt) >> 4) & 0x000F)
#define AL_GET_BITDEPTH(PicFmt) (AL_GET_BITDEPTH_LUMA(PicFmt) > AL_GET_BITDEPTH_CHROMA(PicFmt) ? AL_GET_BITDEPTH_LUMA(PicFmt) : AL_GET_BITDEPTH_CHROMA(PicFmt))
#define AL_GET_CHROMA_MODE(PicFmt) ((AL_EChromaMode)((PicFmt) >> 8))

#define AL_SET_BITDEPTH_LUMA(PicFmt, BitDepth) (PicFmt) = (AL_EPicFormat)(((PicFmt) & 0xFFF0) | (BitDepth))
#define AL_SET_BITDEPTH_CHROMA(PicFmt, BitDepth) (PicFmt) = (AL_EPicFormat)(((PicFmt) & 0xFF0F) | ((BitDepth) << 4))
#define AL_SET_BITDEPTH(PicFmt, BitDepth) (PicFmt) = (AL_EPicFormat)(((PicFmt) & 0xFF00) | (BitDepth) | ((BitDepth) << 4))
#define AL_SET_CHROMA_MODE(PicFmt, Mode) (PicFmt) = (AL_EPicFormat)(((PicFmt) & 0x00FF) | ((int)(Mode) << 8))

/*************************************************************************//*!
   \brief Encoding High level syntax enum
*****************************************************************************/
typedef enum __AL_ALIGNED__ (4) AL_e_HlsFlag
{
  AL_SPS_LOG2_MAX_POC_MASK = 0x0000000F,
  AL_SPS_LOG2_MAX_FRAME_NUM_MASK = 0x000000F0,
  AL_SPS_LOG2_NUM_SHORT_TERM_RPS_MASK = 0x00003F00,
  AL_SPS_LOG2_NUM_LONG_TERM_RPS_MASK = 0x000FC000,
  AL_SPS_TEMPORAL_MVP_EN_FLAG = 0x00100000,

  AL_PPS_ENABLE_REORDERING = 0x00000001,
  AL_PPS_CABAC_INIT_PRES_FLAG = 0x00000002,
  AL_PPS_DBF_OVR_EN_FLAG = 0x00000004,
  AL_PPS_SLICE_SEG_EN_FLAG = 0x00000008,
  AL_PPS_NUM_ACT_REF_L0 = 0x000000F0,
  AL_PPS_NUM_ACT_REF_L1 = 0x00000F00,
} AL_EHlsFlag;

#define AL_GET_SPS_LOG2_MAX_POC(HlsParam) ((HlsParam) & AL_SPS_LOG2_MAX_POC_MASK)
#define AL_GET_SPS_LOG2_MAX_FRAME_NUM(HlsParam) (((HlsParam) & AL_SPS_LOG2_MAX_FRAME_NUM_MASK) >> 4)
#define AL_GET_SPS_LOG2_NUM_SHORT_TERM_RPS(HlsParam) (((HlsParam) & AL_SPS_LOG2_NUM_SHORT_TERM_RPS_MASK) >> 8)
#define AL_GET_SPS_LOG2_NUM_LONG_TERM_RPS(HlsParam) (((HlsParam) & AL_SPS_LOG2_NUM_LONG_TERM_RPS_MASK) >> 14)
#define AL_GET_SPS_TEMPORAL_MVP_EN_FLAG(HlsParam) (((HlsParam) & AL_SPS_TEMPORAL_MVP_EN_FLAG) >> 20)

#define AL_GET_PPS_ENABLE_REORDERING(HlsParam) ((HlsParam) & AL_PPS_ENABLE_REORDERING)
#define AL_GET_PPS_DBF_OVR_EN_FLAG(HlsParam) (((HlsParam) & AL_PPS_DBF_OVR_EN_FLAG) >> 2)
#define AL_GET_PPS_SLICE_SEG_EN_FLAG(HlsParam) (((HlsParam) & AL_PPS_SLICE_SEG_EN_FLAG) >> 3)
#define AL_GET_PPS_NUM_ACT_REF_L0(HlsParam) (((HlsParam) & AL_PPS_NUM_ACT_REF_L0) >> 4)
#define AL_GET_PPS_NUM_ACT_REF_L1(HlsParam) (((HlsParam) & AL_PPS_NUM_ACT_REF_L1) >> 8)

#define AL_SET_PPS_NUM_ACT_REF_L0(HlsParam, Num) (HlsParam) = ((HlsParam) & ~AL_PPS_NUM_ACT_REF_L0) | ((Num) << 4)
#define AL_SET_PPS_NUM_ACT_REF_L1(HlsParam, Num) (HlsParam) = ((HlsParam) & ~AL_PPS_NUM_ACT_REF_L1) | ((Num) << 8)

/*************************************************************************//*!
   \brief Encoding option enum
*****************************************************************************/
typedef enum __AL_ALIGNED__ (4) AL_e_ChEncOptions
{
  AL_OPT_WPP = 0x00000001,
  AL_OPT_TILE = 0x00000002,
  AL_OPT_LF = 0x00000004,
  AL_OPT_LF_X_SLICE = 0x00000008,
  AL_OPT_LF_X_TILE = 0x00000010,
  AL_OPT_SCL_LST = 0x00000020,
  AL_OPT_CONST_INTRA_PRED = 0x00000040,
  AL_OPT_QP_TAB_RELATIVE = 0x00000080,
  AL_OPT_FIX_PREDICTOR = 0x00000100,
  AL_OPT_CUSTOM_LDA = 0x00000200,
  AL_OPT_ENABLE_AUTO_QP = 0x00000400,
  AL_OPT_ADAPT_AUTO_QP = 0x00000800,
  AL_OPT_FORCE_REC = 0x00008000,
  AL_OPT_FORCE_MV_OUT = 0x00010000,
  AL_OPT_FORCE_MV_CLIP = 0x00020000,
  AL_OPT_LOWLAT_SYNC = 0x00040000,
  AL_OPT_LOWLAT_INT = 0x00080000,
  AL_OPT_RDO_COST_MODE = 0x00100000,
} AL_EChEncOption;

/*************************************************************************//*!
   \brief Rate Control Mode
*****************************************************************************/
typedef enum __AL_ALIGNED__ (4) AL_e_RateCtrlMode
{
  AL_RC_CONST_QP = 0x00,
  AL_RC_CBR = 0x01,
  AL_RC_VBR = 0x02,
  AL_RC_LOW_LATENCY = 0x03,
  AL_RC_BYPASS = 0x3F,
} AL_ERateCtrlMode;

/*************************************************************************//*!
   \brief Rate Control Options
*****************************************************************************/
typedef enum __AL_ALIGNED__ (4) AL_e_RateCtrlOption
{
  AL_RC_OPT_NONE = 0x00000000,
  AL_RC_OPT_SCN_CHG_RES = 0x00000001,
} AL_ERateCtrlOption;

/*************************************************************************//*!
   \brief Rate Control parameters structure
*****************************************************************************/
typedef struct __AL_ALIGNED__ (4) AL_t_RCParam
{
  AL_ERateCtrlMode eRCMode;
  uint32_t uInitialRemDelay;
  uint32_t uCPBSize;
  uint16_t uFrameRate;
  uint16_t uClkRatio;
  uint32_t uTargetBitRate;
  uint32_t uMaxBitRate;
  int16_t iInitialQP;
  int16_t iMinQP;
  int16_t iMaxQP;
  int16_t uIPDelta;
  int16_t uPBDelta;
  AL_ERateCtrlOption eOptions;
} AL_TRCParam;

#define MAX_LOW_DELAY_B_GOP_LENGTH 4
#define MIN_LOW_DELAY_B_GOP_LENGTH 1
/*************************************************************************//*!
   \brief GOP Control Mode
*****************************************************************************/
typedef enum __AL_ALIGNED__ (4) AL_e_GopCtrlMode
{
  AL_GOP_MODE_DEFAULT = 0x00,
  AL_GOP_MODE_PYRAMIDAL = 0x01,

  AL_GOP_MODE_BYPASS = 0x7F,

  AL_GOP_FLAG_LOW_DELAY = 0x80,
  AL_GOP_MODE_LOW_DELAY_P = AL_GOP_FLAG_LOW_DELAY | 0x00,
  AL_GOP_MODE_LOW_DELAY_B = AL_GOP_FLAG_LOW_DELAY | 0x01,
} AL_EGopCtrlMode;

/*************************************************************************//*!
   \brief Gop parameters structure
*****************************************************************************/
typedef struct AL_t_GopFrm
{
  uint8_t uType;
  uint8_t uTempId;
  uint8_t uIsRef;
  int8_t iQpOffset;
  int16_t iPOC;
  int16_t iRefA;
  int16_t iRefB;
  uint8_t uSrcOrder; // filled by Gop Manager
  int8_t pDPB[5];
}AL_TGopFrm;

/*************************************************************************//*!
   \brief Gop parameters structure
*****************************************************************************/
typedef struct AL_t_GopParam
{
  AL_EGopCtrlMode eMode;
  uint32_t uFreqIDR;
  uint32_t uFreqLT;
  AL_EGdrMode eGdrMode;
  uint16_t uGopLength;
  uint8_t uNumB;
}AL_TGopParam;

/*************************************************************************//*!
   \brief Interpolation Filter
*****************************************************************************/
typedef enum e_MaxBurstSize
{
  AL_BURST_256 = 0,
  AL_BURST_128 = 1,
  AL_BURST_64 = 2,
  AL_BURST_512 = 3,
}AL_EMaxBurstSize;

/*************************************************************************//*!
   \brief Source compression type
*****************************************************************************/
typedef enum e_SrcConvMode // [0] : CompMode | [3:1] : SourceFormat
{
  AL_NVX = 0x0,
  AL_TILE_32x8 = 0x6,
}AL_ESrcConvMode;

#define MASK_SRC_COMP 0x01
#define MASK_SRC_FMT 0x0E

#define AL_GET_COMP_MODE(SrcConvFmt) ((SrcConvFmt) & MASK_SRC_COMP)
#define AL_GET_SRC_FMT(SrcConvFmt) (((SrcConvFmt) & MASK_SRC_FMT) >> 1)

#define AL_SET_COMP_MODE(SrcConvFmt, CompMode) (SrcConvFmt) = ((SrcConvFmt) & ~MASK_SRC_COMP) | ((CompMode) & MASK_SRC_COMP)
#define AL_SET_SRC_FMT(SrcConvFmt, SrcFmt) (SrcConvFmt) = ((SrcConvFmt) & ~MASK_SRC_FMT) | (((SrcFmt) << 1) & MASK_SRC_FMT)

/*************************************************************************//*!
   \brief Channel parameters structure
*****************************************************************************/
typedef struct __AL_ALIGNED__ (4) AL_t_EncChanParam
{
  /* picture resolution */
  uint16_t uWidth;
  uint16_t uHeight;
  AL_EPicFormat ePicFormat;
  AL_EColorSpace eColorSpace;
  AL_ESrcConvMode eSrcConvMode;

  /* encoding profile/level */
  AL_EProfile eProfile;
  uint8_t uLevel;
  uint8_t uTier;

  uint32_t uSpsParam;
  uint32_t uPpsParam;

  /* Encoding tools parameters */
  AL_EChEncOption eOptions;
  int8_t iBetaOffset;
  int8_t iTcOffset;

  int8_t iCbSliceQpOffset;
  int8_t iCrSliceQpOffset;
  int8_t iCbPicQpOffset;
  int8_t iCrPicQpOffset;


  uint8_t uCuQPDeltaDepth;
  uint8_t uCabacInitIdc;

  uint8_t uNumCore;
  uint16_t uSliceSize;
  uint16_t uNumSlices;

  /* L2 prefetch parameters */
  bool bL2PrefetchAuto;
  uint32_t uL2PrefetchMemOffset;
  uint32_t uL2PrefetchMemSize;
  uint16_t uClipHrzRange;
  uint16_t uClipVrtRange;

  /* MV range */
  int16_t pMeRange[2][2];  /*!< Allowed range for motion estimation */

  /* encoding block size */
  uint8_t uMaxCuSize;
  uint8_t uMinCuSize;
  uint8_t uMaxTuSize;
  uint8_t uMinTuSize;
  uint8_t uMaxTransfoDepthIntra;
  uint8_t uMaxTransfoDepthInter;

  // For AVC
  AL_EEntropyMode eEntropyMode;
  AL_EWPMode eWPMode;




  /* Gop & Rate control parameters */
  AL_TRCParam tRCParam;
  AL_TGopParam tGopParam;
  bool bSubframeLatency;
} AL_TEncChanParam;

#define AL_GetWidthInLCU(tChParam) (((tChParam).uWidth + (1 << (tChParam).uMaxCuSize) - 1) >> (tChParam).uMaxCuSize)
#define AL_GetHeightInLCU(tChParam) (((tChParam).uHeight + (1 << (tChParam).uMaxCuSize) - 1) >> (tChParam).uMaxCuSize)

/*@}*/
