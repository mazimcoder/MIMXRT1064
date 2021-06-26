/*
 * Globals.cpp
 *
 *  Created on: 23 Jun 2021
 *      Author: mustafaabdelazim
 */



#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "fsl_debug_console.h"
#include "Globals.hpp"





#ifdef __cplusplus
extern "C" {
#endif

void printc(char* p){

	PRINTF("%s",p);
}





#ifdef __cplusplus
}
#endif




GlobalBuf::GlobalBuf(uint32_t bufsize){

	size=bufsize;
	data= (char*)calloc(size,sizeof(char));

	if(data==NULL){
		std::cout<<"Error: GlobalBuf::GlobalBuf()data==NULLl\r\n"<<std::endl;
		initialized = false;
	}
	else
		initialized = true;
};


void* GlobalBuf::access(void){

	if(initialized)
		return data;
	else
		return NULL;

}

void GlobalBuf::freeBuf(void){

	if(initialized && data!=NULL)
		free(data);
	initialized=false;

}

void GlobalBuf::reinitialize(uint32_t bufsize){

	if(initialized)
		freeBuf();
	else
		std::cout<<"Error: GlobalBuf::reinitialize() "<<std::endl;

	size=bufsize;
	data= (char*)calloc(size,sizeof(char));
	initialized=true;
}

