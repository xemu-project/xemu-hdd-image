#include <windows.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <xboxkrnl/xboxkrnl.h>

void main(void)
{
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
    ULONG status = 0; //thanks to the people helping me in the off-topic channel on the xemu discord server. here we have a very finicky and probably buggy implementation of a dvd autolauncher.
    ULONG oldstatus = 0;
    debugPrint("Please insert a disc...\n");
    for (;;) {
        HalReadSMCTrayState(&status, NULL);
        if (status == 16) { // if the drive status is 0x10, wait for a disc to be inserted.
            debugPrint("Tray is Open. Waiting 5 seconds for a disc.\n", status, oldstatus);
            Sleep(5000);
        }
        if (status == 96) { // we've got a disc, drive status is 0x60, lets try to launch default.xbe
            debugPrint("You've got games on this disc? Attempting to launch...\n", status, oldstatus);
            XLaunchXBE("\\Device\\CdRom0\\default.xbe"); // if the screen keeps flickering with the same text as before, double check that you packed your iso correctly, we cant find default.xbe.
            Sleep(2000);
        }
        Sleep(200);
    }
}
