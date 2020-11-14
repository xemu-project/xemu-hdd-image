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
        switch (status)//Using a switch now, i think this just looks cooler. if statements work fine i guess idk.
        {
        case 16 : //if satus is 16, we know the tray is open
            if (oldstatus != status)
            {
                debugPrint("Tray is Open. Waiting for a disc.\n", status, oldstatus);
                oldstatus = status; // very stupid solution do a problem that is probably very easy to fix but my pea-sized brain cant figure it out.
            }
            break;
        case 96 : //if status is 96, we've got something in the tray and are going to try and launch it, 3 times. If it fails launching, then no default.xbe was found.
            debugPrint("We've got a disc, attempting to launch!\n");
            for (int i = 0; i < 3; i++)
            {
                if (oldstatus != status)
                {
                    XLaunchXBE("\\Device\\CdRom0\\default.xbe"); // if the screen keeps flickering with the same text as before, double check that you packed your iso correctly, we cant find default.xbe.
                    if (i == 3)
                    {
                        debugPrint("Could not launch default.xbe! Please check if your disc is scratched, or packed incorrectly.");
                        oldstatus = status;
                    }
                    break;
                }
            }
        }
        Sleep(200);
    }
}
