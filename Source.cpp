#include "framework.h"

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)

{
    Color* color = new Color();
    if (color)
    {
        // create the window
        if (!color->InitializeWindow(hInstance, nShowCmd, color->FullScreen))
        {
            MessageBox(0, L"Window Initialization - Failed",
                L"Error", MB_OK);
            return 1;
        }

        // initialize direct3d
        if (!color->InitD3D())
        {
            MessageBox(0, L"Failed to initialize direct3d 12",
                L"Error", MB_OK);
            color->Cleanup();
            return 1;
        }

        // start the main loop
        color->mainloop();

        // we want to wait for the gpu to finish executing the command list before we start releasing everything
        color->WaitForPreviousFrame();

        // close the fence event
        CloseHandle(color->fenceEvent);

        // clean up everything
        color->Cleanup();
    }
    delete color;
    color = NULL;
    return 0;
}