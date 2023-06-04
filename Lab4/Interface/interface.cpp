// MyDLL.cpp
#include "pch.h" 

#define DLL_EXPORT1 __declspec(dllexport)
#define DLL_EXPORT2 __declspec(dllexport)
#define DLL_EXPORT3 __declspec(dllexport)

extern "C++" {
	DLL_EXPORT1 HWND WndEditFromChild(HWND hWnd) {
		HWND hEditControl = CreateWindowA("edit", "000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 0, 30, 55, 100, hWnd, NULL, NULL, NULL, NULL);
		return hEditControl;
	}

	DLL_EXPORT2 HWND WndStaticControlChild(HWND hWnd) {
		HWND hStaticControl = CreateWindowA("static", "Введите матрицу размером 6x6", WS_VISIBLE | WS_CHILD, 0, 0, 490, 20, hWnd, NULL, NULL, NULL, NULL);
		return hStaticControl;
	}

	DLL_EXPORT3 void MainWndAddWidgetsChild(HWND hWnd) {
		CreateWindowA("button", "Посчитать", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 140, 100, 30, hWnd, (HMENU)1, NULL, NULL, NULL);
	}
}