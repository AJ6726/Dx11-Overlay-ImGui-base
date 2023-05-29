#include <Windows.h>
#include <dwmapi.h>

#include <d3d11.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

HWND CreateOverlayWindow(HINSTANCE hIstance); 
void WindowFrameToClientArea(HWND window);
void CreateDeviceAndSwapChain(HWND window);

void SetupMenuStyle();
void SetupMenu(HINSTANCE hInstance, int cmdshow); 
void ShutdownMenu(); 
void SetupMenuFont(); 