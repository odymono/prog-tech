// MyDLL.cpp
#include "pch.h" 

#define DLL_EXPORT1 __declspec(dllexport)
#define DLL_EXPORT2 __declspec(dllexport)

extern "C++" {
    DLL_EXPORT1 void MainWndAddWidgets(HWND hWnd) {
        CreateWindowA("button", "Посчитать",
            WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 140, 100, 30,
            hWnd, (HMENU)1, NULL, NULL, NULL);
        CreateWindow(TEXT("MyWindowClass"), TEXT("Graph Coloring Solver"),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 350, 250, NULL, NULL, NULL, NULL);
    }
    DLL_EXPORT2 HWND WndEdit(HWND hWnd) {
        HWND hEditControl = CreateWindowA("edit", "000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000",
            WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER | WS_BORDER,
            10, 40, 55, 100, hWnd, NULL, NULL, NULL, NULL);
        return hEditControl;
    }
}





