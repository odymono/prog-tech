#pragma once
#include<Windows.h>
#include<string>


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
HWND hNumberAControl;
HWND hNumberBControl;
HWND hWnd;

//������������� ����������� ���������� ����������
int matrix[6][6];
std::string StrMat;
std::string path;

//��������� ������� 
void MainWndAddWidgets(HWND hWnd);
LRESULT CALLBACK SoftwareChildProcedure(HWND childWindow, UINT msg, WPARAM wp, LPARAM lp);


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

int solveGraphColoring(int matrix[6][6], int numVertices, int* numColors)
{
	// �������������� ��� ������� ��� �����
	int colors[6];
	memset(colors, -1, sizeof(colors));

	// ������� ������ ������� ������ ������
	colors[0] = 0;
	*numColors = 1;

	// ���������� ���������� �������, ��������� ������ ��������
	for (int v = 1; v < numVertices; v++) {
		// ������ ��������� ����� ��� ���� �������
		bool available[6];
		memset(available, true, sizeof(available));
		for (int i = 0; i < numVertices; i++) {
			if (matrix[v][i] && colors[i] != -1) {
				available[colors[i]] = false;
			}
		}

		// �������� ������ ��������� ����
		int chosenColor;
		for (chosenColor = 0; chosenColor < numVertices; chosenColor++) {
			if (available[chosenColor]) {
				break;
			}
		}

		// ���� ���������� ����� �� �������, ������ -1 (�������� ����)
		if (chosenColor == numVertices) {
			return -1;
		}

		// ���������� ������� ��������� ������
		colors[v] = chosenColor;

		// ��������� ����������� ���������� ����������� ������
		if (chosenColor + 1 > *numColors) {
			*numColors = chosenColor + 1;
		}
	}

	// ���������� ���������� ����
	int result = 0;
	for (int i = 0; i < numVertices; i++) {
		result |= (colors[i] << (i * 3));
	}
	return result;
}



//��������� ��������� ��������� �������� ���� 
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
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
				int result = solveGraphColoring(matrix, 6, &numColors);
				path = "\nThe minimum number of colors needed is " + std::to_string(numColors) + "\n";
				//��������� �������� ����
				HWND childWindow = CreateWindowEx(
					0, L"ChildWndClass", L"�������� ����", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					300, 300, 300, 150, hWnd, NULL, NULL, NULL
				);
				//�������� �� ������ ���� ���� �������� � ��������� ��������� ����
				if (childWindow == NULL) {
					MessageBox(childWindow, L"�� ������� ������� �������� ����", L"������", MB_OK | MB_ICONERROR);
					return -1;
				}
			}
			break;
		default: break;
		}
		break;
		//��� ��������
	case WM_CREATE:
		//��������� � ��������� ����������� ����������� �������� ���� 
		MainWndAddWidgets(hWnd);
		break;
		//��� �����������
	case WM_DESTROY:
		//���� ��� ���������� � ����, ����� ���� ���������� ��������� 
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
			childText = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE,
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

//��������� �������� ����������� �������� ����
//��������� ���������� ��������� � ����������
//������� ��� ��� ����, ����� � ��������� ��������� �������� ���� ����� ���� 
//������������ �������, ���������� ����, ���� �� �������, 
//������� �������� ������ ��������� � ��� ���������� 
void MainWndAddWidgets(HWND hWnd) {
	hStaticControl = CreateWindowA("static", "������� ������� ���������(6 �� 6)", WS_VISIBLE | WS_CHILD, 0, 0, 490, 20, hWnd, NULL, NULL, NULL, NULL);

	hEditControl = CreateWindowA("edit", "000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER, 10, 40, 55, 100, hWnd, NULL, NULL, NULL, NULL);
	//� ����� ����������� ��� ������ ���������� ��������� �������������� ��� ��������� �������
	//� ������ ������ ��� ������ OnButtonClicked �� ��������� 1
	CreateWindowA("button", "���������", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 140, 100, 30, hWnd, (HMENU)OnButtonClicked, NULL, NULL, NULL);

}
