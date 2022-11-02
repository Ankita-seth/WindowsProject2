#include "stdafx.h"
#include "DemoClass.h"



int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)

{
    DemoClass* demo = new DemoClass();
    // create the window
    if (!demo->InitializeWindow(hInstance, nShowCmd, demo->FullScreen))
    {
        MessageBox(0, L"Window Initialization - Failed",
            L"Error", MB_OK);
        return 1;
    }

    // initialize direct3d
    if (!demo->InitD3D())
    {
        MessageBox(0, L"Failed to initialize direct3d 12",
            L"Error", MB_OK);
        demo->Cleanup();
        return 1;
    }

    // start the main loop
    demo->mainloop();

    // we want to wait for the gpu to finish executing the command list before we start releasing everything
    demo->WaitForPreviousFrame();

    // close the fence event
    CloseHandle(demo->fenceEvent);

    // clean up everything
    demo->Cleanup();

    return 0;
}
