#ifndef __SM3_IP_H_INCLUDED__
#define __SM3_IP_H_INCLUDED__

#include <assert.h>
#include <stdint.h>


#define SM3_IP_REG(off)     (*(volatile uint32_t*)(XPAR_AXI_SM3_0_BASEADDR+off))
#define SM3_IP_REG_DATA_IN  (0)
#define SM3_IP_REG_STAT     (4)
#define SM3_IP_REG_DATA_OUT (8)
#define SM3_IP_MASK_DONE    (0x100)

void sm3(const uint8_t *pData, size_t len, uint8_t *lpOut);

#endif // __SM3_IP_H_INCLUDED__
