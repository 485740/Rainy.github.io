#include "pch.h"

#include "MyImGui.h"

#include "MyMenu.h"

#include "Features.h"

#include "Dev.h"

// 必须添加的ImGui后端实现头文件
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

// 确保链接器能找到这些实现
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

extern bool bAlive;

bool MyImGui::CreateDeviceD3D(HWND hWnd)
{
    // 设置窗口初始大小为 600x600
    const int DEFAULT_WIDTH = 600;
    const int DEFAULT_HEIGHT = 600;

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = DEFAULT_WIDTH;
    sd.BufferDesc.Height = DEFAULT_HEIGHT;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    
    if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 
           createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, 
           &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext)))
    {
        return false;
    }

    CreateRenderTarget();
    return true;
}

void MyImGui::CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void MyImGui::CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void MyImGui::CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI MyImGui::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam);
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

bool MyImGui::Initialize()
{
    // 设置窗口初始大小和标题
    const int INITIAL_WIDTH = 375;
    const int INITIAL_HEIGHT = 470;
    const wchar_t* WINDOW_TITLE = L"Grand Theft Auto V Enhanced";

    wc = { 
        sizeof(wc), 
        CS_CLASSDC, 
        WndProc, 
        0L, 
        0L, 
        GetModuleHandle(nullptr), 
        nullptr, 
        nullptr, 
        nullptr, 
        nullptr, 
        WINDOW_TITLE, 
        nullptr 
    };
    
    ::RegisterClassExW(&wc);
    hwnd = ::CreateWindowW(
        wc.lpszClassName, 
        WINDOW_TITLE, 
        WS_OVERLAPPEDWINDOW,
        100, 100, 
        INITIAL_WIDTH, INITIAL_HEIGHT, 
        nullptr, nullptr, 
        wc.hInstance, 
        nullptr
    );

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return false;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // 初始化ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    // 设置中文字体
    io.Fonts->AddFontFromFileTTF(
        "C:/Windows/Fonts/msyh.ttc", 
        16.0f, 
        nullptr, 
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
    );

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    return true;
}

bool MyImGui::Close()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return true;
}

bool MyImGui::OnFrame()
{
    MSG msg;
    while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
            bAlive = false;
    }
    
    if (!bAlive)
        return false;

    if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
    {
        ::Sleep(10);
        return true;
    }
    g_SwapChainOccluded = false;

    // 处理窗口大小变化
    if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
    {
        CleanupRenderTarget();
        g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
        g_ResizeWidth = g_ResizeHeight = 0;
        CreateRenderTarget();
    }

    // 开始新帧
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // 只渲染主菜单和启用的功能窗口
    MyMenu::Render();
    //Dev::Render();//隐藏Dev
    if (WeaponInspector::bEnable)
        WeaponInspector::Render();

    if (Teleport::bEnable)
        Teleport::Render();

    // 渲染
    ImGui::Render();
    const float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    g_pSwapChain->Present(1, 0);
    return true;
}