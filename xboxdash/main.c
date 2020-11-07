#include <windows.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>

void main(void)
{
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
    debugPrint("Please insert an Xbox disc and restart the system...\n");
    while (1) Sleep(1000);
    XReboot();
}
