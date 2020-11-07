#include <hal/debug.h>
#include <hal/video.h>
#include <windows.h>
#include <pbkit/pbkit.h>
#include <hal/xbox.h>
#include "stdio.h"

void main(void)
{
    int i;
    
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
    
    if (pb_init()) {
        Sleep(2000);
        XReboot();
        return;
    }

    pb_show_debug_screen();
    debugPrint("Please insert an Xbox disc...\n");
    while(1) {
        Sleep(1000);
    }
    pb_kill();
    XReboot();
}
