#include <stdio.h>
#include <input.h>

void wait_for_backspace(void (*callback)(void)) __z88dk_fastcall
{
    unsigned char key = 0;

    while (1)
    {
        callback();

        in_wait_key();
        key = in_inkey();
        in_wait_nokey();

        if (key == 13)
        {
            return;
        }
    }
}
