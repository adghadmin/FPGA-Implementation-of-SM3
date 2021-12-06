#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sm3_ip.h"
#include "xil_types.h"
#include "xstatus.h"
#include "Xil_io.h"
// for mmap
#include <fcntl.h>
#include <sys/mman.h>
void sm3(const uint8_t *pData, size_t len, uint8_t *lpOut){
  while(len--){
    SM3_IP_REG(SM3_IP_REG_DATA_IN) = (*pData++) | (len? 0:SM3_IP_MASK_DONE);
  }
  while(!SM3_IP_REG(SM3_IP_REG_STAT));
  for(uint8_t i=0; i<32; ++i){// 256bit output
    *lpOut++ = (uint8_t)SM3_IP_REG(SM3_IP_REG_DATA_OUT);
  }
}



int main(int argc, char *argv[])
{
    // for mmap
    int fd = open("/dev/mem", O_RDWR | O_SYNC);

    unsigned int *_XPAR_AXI_SM3_0_BASEADDR = mmap(NULL, 65536, PROT_READ | PROT_WRITE, MAP_SHARED, fd, XPAR_AXI_SM3_0_BASEADDR);
    if (_XPAR_AXI_SM3_0_BASEADDR == NULL) {
        printf("mmap failed\n");
        exit(0);
    }
    unsigned int XPAR_AXI_SM3_0_BASEADDR = (unsigned int)_XPAR_AXI_SM3_0_BASEADDR;
    uint8_t buf[32];
    sm3((uint8_t*)"abc", 3, buf);//using string "abc" for testing
    for(int i=0; i<32; ++i){
      printf("%02X ", buf[i]);
    }
    return 0;
}

