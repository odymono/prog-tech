#pragma once
#ifdef __cplusplus
extern "C++" {
#endif
#include <Windows.h>
#ifdef __cplusplus
}
#endif

__declspec(dllimport) void MainWndAddWidgets(HWND hWnd);
__declspec(dllimport) HWND WndEdit(HWND hWnd);