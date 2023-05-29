#include "ImGui_Setup.h"

ID3D11Device* device{ nullptr };
ID3D11DeviceContext* devicecontext{ nullptr };
IDXGISwapChain* swapchain{ nullptr };
ID3D11RenderTargetView* rendertargetview{ nullptr };
D3D_FEATURE_LEVEL level{};
WNDCLASSEX windowclass = { };
HWND window = { };

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


//IMPORTANT: Multibyte, C++ 17, Additional Dependecies: d3d11.lib

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevhInstance, PWSTR cmdline, int cmdshow)
{
	SetupMenu(hInstance, cmdshow);
	SetupMenuFont();

	bool MenuOpen = false;
	bool runProgram = true;
	while (runProgram)
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				runProgram = false;

		}

		if (!runProgram)
			break;

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (GetAsyncKeyState('K') & 1) {
			MenuOpen = !MenuOpen;
		}

		if (MenuOpen) {
			SetWindowLong(window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED);
			SetForegroundWindow(window);

			ImGui::SetNextWindowSize({ 400, 400 });
			ImGui::Begin("TestWindow");

			ImGui::End();
		}
		else {
			SetWindowLong(window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		}

		ImGui::Render();
		constexpr float color[4]{ 0.f, 0.f, 0.f, 0.f };
		devicecontext->OMSetRenderTargets(1, &rendertargetview, nullptr);
		devicecontext->ClearRenderTargetView(rendertargetview, color);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		swapchain->Present(0, 0);
	}

	ShutdownMenu();
	DestroyWindow(window);
	UnregisterClass(windowclass.lpszClassName, windowclass.hInstance);

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return 0;

	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}


