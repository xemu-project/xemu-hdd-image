#include <winapi/windows.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <xboxkrnl/xboxkrnl.h>

ULONG status = 0;
ULONG oldstatus = 0;

void dvdStat16(void)
{
    while (oldstatus != status)
    {
        debugPrint("Tray is Open. Waiting for a disc.\n", status, oldstatus);
        oldstatus = status; // very stupid solution do a problem that is probably very easy to fix but my pea-sized brain cant figure it out.
    }
}
void dvdStat96(void)
{
    debugPrint("We've got a disc, attempting to launch!\n");
    debugPrint("\nIf this text begins to flicker after insterting a disc,\ndefault.xbe could not be found.\n");
    debugPrint("\nPlease check your disc for scratches and reinsert it.\nIf you're using XEMU, please do not use REDUMP style isos as\nthey are not supported yet.\n");
    debugPrint("\nCheck if your ISO was packed correctly and try again.\n");
    Sleep(5000);
    if (oldstatus != status)
    {
        XLaunchXBE("\\Device\\CdRom0\\default.xbe"); // Dude this just ends up looping forever and wont execute any code I put after it.
        oldstatus = status; // this doesnt do anything since XLaunchXBE just ends up looping.
    }
    else
    {
        debugPrint("If you're seeing this, tell me about it on Discord. I need to know how you got this to show up.\n");
    }
}

void checkDrvStat(void) //thanks to the people helping me in the off-topic channel on the xemu discord server. here we have a very finicky and probably buggy implementation of a dvd autolauncher.
{
    HalReadSMCTrayState(&status, NULL);
    switch (status)//Using a switch now, I think this just looks cooler. if statements work fine I guess idk.
    {
    case 16: //if satus is 16, we know the tray is open.
        dvdStat16();
        Sleep(1000);
        break;        
    case 96: // if status is 96, we've got media inserted. hopefully its media with a game in it. jump to the function to see.
        dvdStat96();
        Sleep(1000);
        break;
    }
}

void main(void)
{
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
    debugPrint("Please insert a disc...\n");
    for (;;) 
    {
        checkDrvStat();
    }
}
