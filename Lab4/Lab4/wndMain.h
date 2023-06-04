#pragma once
#pragma comment(lib, "D:\\Documents\\GitHub\\prog-tech\\Lab4\\Debug\\Interface.lib")

#include<Windows.h>
#include<string>
#include "D:\Documents\GitHub\prog-tech\Lab4\Interface\interface.h";

extern "C" int graphColoring(int matrix[6][6], int numVertices, int* numColors);


//������� ��� ���������� ������
#define OnButtonClicked 1
#define TextBufferSize 50
#define DlgIndexNumberA 200
#define DlgIndexNumberB 210


char Buffer[TextBufferSize];
int readChar;
//����������� ����� �����
unsigned numA;
unsigned numB;

//������������� ������� ���������� ��� �������� �� �������� ����� ���������
HWND childText;
HWND hEditControl;
HWND hStaticControl;
HWND hStaticControlNums;
HWND hWnd;

//������������� ����������� ���������� ����������
int matrix[6][6];
std::string StrMat;
std::string path;

//����������� ������ �������� ����
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };
	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;
	return NWC;
}

//����������� ������ ��������� ���� 
WNDCLASS NewWindowChildClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC ProcedureChild) {
	WNDCLASS NWC = { 0 };
	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = ProcedureChild;
	return NWC;
}

//��������� �������������� ��������� ������� � ������� ���� int 
void ParseMatrix()
{
	int k = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (StrMat[k] == '0') { matrix[i][j] = 0; };
			if (StrMat[k] == '1') { matrix[i][j] = 1; };
			k++;
		}
	}
}

//�������� ������������ ��������� ��������
bool ValidateMatrix() {
	if (StrMat.size() != 36) {
		return false;
	}
	for (int i = 0; i < 36; i++) {
		//���� ������ �� 1 � �� 0, �� �������� �� ��������
		if (StrMat[i] != 48 && StrMat[i] != 49) { return false; };

	}
	return true;
}


//��������� ��������� ��������� �������� ���� 
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	//typedef int(*func)(int(*)[6], int, int*);
	//HINSTANCE hinstDLL = LoadLibrary(TEXT("graphColoring.dll"));
	//func graphColoring = (func)GetProcAddress(hinstDLL, "graphColoring");


	switch (msg) {
	case WM_COMMAND:
		switch (wp)
		{
			//��� ������� ������ 
		case OnButtonClicked:
			//��������� �������� �� ����� ������ ������
			readChar = GetWindowTextA(hEditControl, Buffer, TextBufferSize);

			//������ ��������� ����� � ��������� �������
			StrMat = Buffer;
			StrMat.erase(std::remove(StrMat.begin(), StrMat.end(), '\r'), StrMat.end());
			StrMat.erase(std::remove(StrMat.begin(), StrMat.end(), '\n'), StrMat.end());

			//������ �������� ������������ �����
			if (ValidateMatrix()) {
				SetWindowTextA(hStaticControl, "������� ������ ���������");
				ParseMatrix();
			}
			else {
				SetWindowTextA(hStaticControl, "������� ������ �����������!");
			};

			if (ValidateMatrix()) {

				//��������� ������� ����
				//��� ����������, ��� ��� �������� ���� ������ ���� ���������
				EnableWindow(hWnd, FALSE);
				int numColors = 0;
				//if (hinstDLL == NULL) {
				//	MessageBox(hWnd, L"���������� graphColoring.dll �� �������!", L"������!", NULL);
				//	EnableWindow(hWnd, TRUE);
				//}
				//else {
					int numVertices = 6;
					int result = graphColoring(matrix, numVertices, &numColors);

					path = "\n����������� ���-�� ������ ��� ��������� ����� - " + std::to_string(numColors) + "\n";
					//��������� �������� ����
					HWND childWindow = CreateWindowEx(
						0, L"ChildWndClass", L"�������� ����", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						300, 300, 300, 150, hWnd, NULL, NULL, NULL
					);
					//�������� �� ������ ���� ���� �������� � ��������� ��������� ����
					if (childWindow == NULL) {
						MessageBox(childWindow, L"�� ������� ������� �������� ����", L"������", MB_OK | MB_ICONERROR);
						return -1;
					//}
				};

			}
			break;
		default: break;
		}
		break;
		//��� ��������
	case WM_CREATE:
		//��������� � ��������� ����������� ����������� �������� ���� 
		hStaticControl = WndStaticControlChild(hWnd);
		MainWndAddWidgetsChild(hWnd);
		hEditControl = WndEditFromChild(hWnd);
		break;
		//��� �����������
	case WM_DESTROY:
		//FreeLibrary(hinstDLL);
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

//��������� ��������� ��������� ��������� ���� 
LRESULT CALLBACK SoftwareChildProcedure(HWND childWindow, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE: {

		//�������� ������������ ������, ���� ����� ������� ��������� ��������
		if (!IsWindow(childText)) {
			childText = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE,
				0, 0, 300, 300, childWindow, NULL, NULL, NULL);
		}
		//����� �� �������� ���� ������

		SetWindowTextA(childText, path.c_str());
		break; }
				  //��� ��������
	case WM_CLOSE:
		//�������� ������� ���� � ������� ��������
		EnableWindow(hWnd, TRUE);
		DestroyWindow(childWindow);
		break;


	default: return DefWindowProc(childWindow, msg, wp, lp);
	}

}