#include <winapi/windows.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <xboxkrnl/xboxkrnl.h>
#include <nxdk/mount.h>

#define TrayStateHasMedia 0x60

int main(void)
{
    XVideoSetMode(640, 480, 16, REFRESH_DEFAULT);

    if (!nxMountDrive('A', "\\Device\\CdRom0\\")) {
        debugPrint("Unable to mount CdRom!\n");
        Sleep(1000);
        return 1;
    }

    debugPrint("Please insert a disc...\n");

    ULONG state;

    while (1) {
        XVideoWaitForVBlank();

        HalReadSMCTrayState(&state, NULL);

        if (state == TrayStateHasMedia) {
            if ((GetFileAttributesA("A:\\default.xbe")) != INVALID_FILE_ATTRIBUTES) {
                debugPrint("Launching...\n");
                XLaunchXBE("A:\\default.xbe");
            }
        }

    }

    return 1;
}
