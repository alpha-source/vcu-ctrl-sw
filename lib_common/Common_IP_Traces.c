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

#include "Common_IP_Traces.h"
#include <assert.h>

FILE* safe_fopen(const char* sFileName, const char* sMode)
{
  FILE* pFile = fopen(sFileName, sMode);
  assert(pFile);
  return pFile;
}

void IP_Write32(FILE* pFile, uint32_t uVal)
{
  int i;
  char sTmp[10], * pTmp = sTmp;

  for(i = 28; i >= 0; i -= 4)
  {
    int iDigit = (((uVal) >> i) & 0x0F);
    *pTmp++ = (iDigit >= 10 ? 'A' - 10 : '0') + iDigit;
  }

  sTmp[8] = '\n';
  fwrite(sTmp, 9, 1, pFile);
}

void IP_TraceBuffer(char const* sFileName, char const* sMode, uint8_t const* pBuffer, uint32_t uSize)
{
  FILE* pFile = safe_fopen(sFileName, sMode);

  uint32_t const* pBuf = (uint32_t*)(pBuffer);

  for(uint32_t u = 0; u < uSize; u += sizeof(uint32_t), ++pBuf)
    IP_Write32(pFile, *pBuf);

  fclose(pFile);
}
