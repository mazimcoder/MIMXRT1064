/*
 * Globals.hpp
 *
 *  Created on: 23 Jun 2021
 *      Author: mustafaabdelazim
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_






#ifdef __cplusplus
extern "C" {
#endif


extern void printc(char* p);



#ifdef __cplusplus
}
#endif




class GlobalBuf{

protected:    char *data;
protected: bool initialized;
public: uint32_t size;

public: GlobalBuf(uint32_t bufsize);


void* access(void);

void freeBuf(void);

void reinitialize(uint32_t bufsize);

};







#endif /* GLOBALS_HPP_ */
