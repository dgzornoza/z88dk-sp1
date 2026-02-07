#include <stdio.h>
#include <input.h>
#include "../z88dk_headers.h"

const struct sp1_Rect game_area = {0, 0, 32, 24};

void wait_for_intro_key(void (*callback)(void)) __z88dk_fastcall
{
    unsigned char key = 0;

    while (in_inkey() != 13)
    {
        callback();
    }
}
