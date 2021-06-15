


void initialize_globalbuf(void)
{
	int cnt =0;
	IdxBuf=TotalArrayBuff;
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
