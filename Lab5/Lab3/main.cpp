#include "wndMain.h"

//� ������ ���������� ������� ����� ������ ������������� ������ 6 �� 6,
//� ��� �� ���� �������� ������������


//����� ����� ��� ��������� 
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	//������������� ������ �������� ����
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", SoftwareMainProcedure);

	//������������� ���� ��������� 
	WNDCLASS wc = NewWindowChildClass((HBRUSH)GetStockObject(WHITE_BRUSH), NULL, NULL, NULL, L"ChildWndClass", SoftwareChildProcedure);
	if (!RegisterClass(&wc)) {
		MessageBox(hWnd, L"�� ������� ���������������� ����� ��������� ����", L"������", MB_OK | MB_ICONERROR);
		return -1;
	}
	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	//�������� �������� ���� � �������� ������� 
	hWnd = CreateWindowA("MainWndClass", "���� �������", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 350, 220, NULL, NULL, NULL, NULL);

	//���� ��������� ��������� 
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}