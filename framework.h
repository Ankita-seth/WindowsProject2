
#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

////////////////

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <string>

//Liniking the libraries
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class Color
{
public:
    //Constructor 
    Color()
    {

    }

    //Destructor
    ~Color()
    {
        
    }

    // this will only call release if an object exists (prevents exceptions calling release on non existant objects)
    #define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

// Handle to the window
    HWND hwnd = NULL;

    // name of the window (not the title)
    LPCTSTR WindowName = L"DX12";

    // title of the window
    LPCTSTR WindowTitle = L"Welcome to my first window!";

    // width and height of the window
    int Width = 800;
    int Height = 600;

    // is window full screen?
    bool FullScreen = false;

    // create a window
    bool InitializeWindow(
        HINSTANCE hInstance,
        int ShowWnd,
        bool fullscreen);

    // main application loop
    void mainloop();

    // direct3d stuff
    const static int frameBufferCount = 3; // number of buffers we want, 2 for double buffering, 3 for tripple buffering

    ID3D12Device* device = nullptr; // direct3d device

    IDXGISwapChain3* swapChain = nullptr; // swapchain used to switch between render targets

    ID3D12CommandQueue* commandQueue = nullptr; // container for command lists

    ID3D12DescriptorHeap* rtvDescriptorHeap = nullptr; // a descriptor heap to hold resources like the render targets

    ID3D12Resource* renderTargets[frameBufferCount]; // number of render targets equal to buffer count

    ID3D12CommandAllocator* commandAllocator[frameBufferCount]; // we want enough allocators for each buffer * number of threads (we only have one thread)

    ID3D12GraphicsCommandList* commandList = nullptr; // a command list we can record commands into, then execute them to render the frame

    ID3D12Fence* fence[frameBufferCount];    // an object that is locked while our command list is being executed by the gpu. We need as many 
    //as we have allocators (more if we want to know when the gpu is finished with an asset)

    HANDLE fenceEvent = NULL; // a handle to an event when our fence is unlocked by the gpu

    UINT64 fenceValue[frameBufferCount]; // this value is incremented each frame. each fence will have its own value

    int frameIndex  = NULL; // current rtv we are on

    int rtvDescriptorSize = NULL; // size of the rtv descriptor on the device (all front and back buffers will be the same size)
    // function declarations

    bool InitD3D(); // initializes direct3d 12

    void Update(); // update the game logic

    void UpdatePipeline(); // update the direct3d pipeline (update command lists)

    void Render(); // execute the command list

    void Cleanup(); // release com ojects and clean up memory

    void WaitForPreviousFrame(); // wait until gpu is finished with command list

    ID3D12PipelineState* pipelineStateObject; // pso containing a pipeline state

    ID3D12RootSignature* rootSignature; // root signature defines data shaders will access

    D3D12_VIEWPORT viewport; // area that output from rasterizer will be stretched to.

    D3D12_RECT scissorRect; // the area to draw in. pixels outside that area will not be drawn onto

    ID3D12Resource* indexBuffer = nullptr;
    
    D3D12_INDEX_BUFFER_VIEW indexBufferView;

    ID3D12Resource* vertexBuffer = nullptr; // a default buffer in GPU memory that we will load vertex data for our triangle into

    D3D12_VERTEX_BUFFER_VIEW vertexBufferView; // a structure containing a pointer to the vertex data in gpu memory

    ID3D12Resource* depthStencilBuffer = nullptr;   //memory for depth Buffer

    ID3D12DescriptorHeap* dsDescriptorHeap = nullptr;  //heap for depth/stencil buffer description

    ID3D12DescriptorHeap* mainDescriptorHeap[frameBufferCount];

    ID3D12Resource* constantBufferUploadHeap[frameBufferCount];

    UINT8* cbColorMultiplierGPUAddress[frameBufferCount];
};

// callback function for windows messages
LRESULT CALLBACK WndProc(HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd);
