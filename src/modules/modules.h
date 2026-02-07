#ifndef __MODULES_H__
#define __MODULES_H__

#include <stdio.h>
#include <input.h>

/** INFRASTRUCTURE */
// -----------------------------------------------------------------------------

// Definir un rectangulo que cubre toda la pantalla (32x24 celdas)
extern const struct sp1_Rect game_area;

/** FUNCTIONS */
// -----------------------------------------------------------------------------

void wait_for_intro_key(void (*callback)(void)) __z88dk_fastcall;

void run_module1(void);
void run_module2(void);
void run_module3_1(void);
void run_module3_2(void);
void run_module3_3_1(void);
void run_module3_3_2(void);
void run_module3_4_1(void);
void run_module3_4_2(void);
//  void run_example4(void);
//  void run_example5(void);
//  void run_example6(void);

#endif // __MODULES_H__
