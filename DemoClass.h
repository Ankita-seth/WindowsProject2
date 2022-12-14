#pragma once
#include<iostream>
#include "stdafx.h"
using namespace DirectX; // we will be using the directxmath library

struct Vertex {
    XMFLOAT3 pos;
};
class DemoClass
{
public:
    // Handle to the window
    HWND hwnd = NULL;

    // name of the window (not the title)
    LPCTSTR WindowName = L"BzTutsApp";

    // title of the window
    LPCTSTR WindowTitle = L"Bz Window";

    // width and height of the window
    float Width = 800;
    float Height = 600;

    // is window full screen?
    bool FullScreen = false;

    // we will exit the program when this becomes false
    bool Running = true;

    // create a window
    bool InitializeWindow(HINSTANCE hInstance,
        int ShowWnd,
        bool fullscreen);

    // main application loop
    void mainloop();


    // direct3d stuff
    const static int frameBufferCount = 3; // number of buffers we want, 2 for double buffering, 3 for tripple buffering

    ID3D12Device* device; // direct3d device

    IDXGISwapChain3* swapChain; // swapchain used to switch between render targets

    ID3D12CommandQueue* commandQueue; // container for command lists

    ID3D12DescriptorHeap* rtvDescriptorHeap; // a descriptor heap to hold resources like the render targets

    ID3D12Resource* renderTargets[frameBufferCount]; // number of render targets equal to buffer count

    ID3D12CommandAllocator* commandAllocator[frameBufferCount]; // we want enough allocators for each buffer * number of threads (we only have one thread)

    ID3D12GraphicsCommandList* commandList; // a command list we can record commands into, then execute them to render the frame

    ID3D12Fence* fence[frameBufferCount];    // an object that is locked while our command list is being executed by the gpu. We need as many 
    //as we have allocators (more if we want to know when the gpu is finished with an asset)

    HANDLE fenceEvent; // a handle to an event when our fence is unlocked by the gpu

    UINT64 fenceValue[frameBufferCount]; // this value is incremented each frame. each fence will have its own value

    int frameIndex; // current rtv we are on

    int rtvDescriptorSize; // size of the rtv descriptor on the device (all front and back buffers will be the same size)
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

    ID3D12Resource* vertexBuffer; // a default buffer in GPU memory that we will load vertex data for our triangle into
    ID3D12Resource* indexBuffer; // a default buffer in GPU memory that we will load index data for our triangle into

    D3D12_VERTEX_BUFFER_VIEW vertexBufferView; // a structure containing a pointer to the vertex data in gpu memory
    // the total size of the buffer, and the size of each element (vertex)

    D3D12_INDEX_BUFFER_VIEW indexBufferView; // a structure holding information about the index buffer
};

