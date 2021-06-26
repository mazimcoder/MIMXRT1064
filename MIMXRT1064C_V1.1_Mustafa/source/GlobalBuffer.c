
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "Globals.h"
#include "GlobalBuffer.h"

void initialize_globalbuf(void)
{
	int cnt =0;
	IdxBuf=globalbufferArrayCapacity;
	do{
		  if(BufPtr[cnt]==NULL){
			  BufPtr[cnt] = (char*)calloc(BufSize,sizeof(char));
			  if(BufPtr[cnt]==NULL)
				  PRINTF("GlobalBufError: %d \r\n",cnt);
		  }
		  else if(BufPtr[cnt]>0){
			  free(BufPtr[cnt]);
			  BufPtr[cnt] = (char*)calloc(BufSize,sizeof(char));
		  }
		  cnt++;
	}while(cnt<IdxBuf);

}
