#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <input.h>

void wait_for_intro_key(void (*callback)(void)) __z88dk_fastcall;

void run_example1(void);
void run_example2(void);
void run_example3(void);
void run_example4(void);
void run_example5(void);
void run_example6(void);

#endif // __COMMON_H__
