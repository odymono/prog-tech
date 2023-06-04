#pragma once
#pragma comment(lib, "D:\\Documents\\GitHub\\prog-tech\\Lab4\\Debug\\Interface.lib")

#include<Windows.h>
#include<string>
#include "D:\Documents\GitHub\prog-tech\Lab4\Interface\interface.h";

extern "C" int graphColoring(int matrix[6][6], int numVertices, int* numColors);


//макросы для облегчения работы
#define OnButtonClicked 1
#define TextBufferSize 50
#define DlgIndexNumberA 200
#define DlgIndexNumberB 210


char Buffer[TextBufferSize];
int readChar;
//беззнаковое целое число
unsigned numA;
unsigned numB;

//инициализация оконных переменных для передачи их значений между функциями
HWND childText;
HWND hEditControl;
HWND hStaticControl;
HWND hStaticControlNums;
HWND hWnd;

//инициализация необходимых глобальных переменных
int matrix[6][6];
std::string StrMat;
std::string path;

//конструктор класса главного окна
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

//конструктор класса дочернего окна 
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

//процедура преобразования текстовой матрицы в матрицу типа int 
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

//проверка корректности введенных значений
bool ValidateMatrix() {
	if (StrMat.size() != 36) {
		return false;
	}
	for (int i = 0; i < 36; i++) {
		//если символ не 1 и не 0, то проверка не пройдена
		if (StrMat[i] != 48 && StrMat[i] != 49) { return false; };

	}
	return true;
}


//процедура обработки сообщений главного окна 
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	//typedef int(*func)(int(*)[6], int, int*);
	//HINSTANCE hinstDLL = LoadLibrary(TEXT("graphColoring.dll"));
	//func graphColoring = (func)GetProcAddress(hinstDLL, "graphColoring");


	switch (msg) {
	case WM_COMMAND:
		switch (wp)
		{
			//при нажатии кнопки 
		case OnButtonClicked:
			//получение значений из полей выбора вершин
			readChar = GetWindowTextA(hEditControl, Buffer, TextBufferSize);

			//замена переносов строк в текстовой матрице
			StrMat = Buffer;
			StrMat.erase(std::remove(StrMat.begin(), StrMat.end(), '\r'), StrMat.end());
			StrMat.erase(std::remove(StrMat.begin(), StrMat.end(), '\n'), StrMat.end());

			//запуск проверок корректности ввода
			if (ValidateMatrix()) {
				SetWindowTextA(hStaticControl, "Матрица задана корректно");
				ParseMatrix();
			}
			else {
				SetWindowTextA(hStaticControl, "Матрица задана некорректно!");
			};

			if (ValidateMatrix()) {

				//выключаем главное окно
				//это необходимо, так как дочернее окно должно быть модальным
				EnableWindow(hWnd, FALSE);
				int numColors = 0;
				//if (hinstDLL == NULL) {
				//	MessageBox(hWnd, L"Библиотека graphColoring.dll не найдена!", L"Ошибка!", NULL);
				//	EnableWindow(hWnd, TRUE);
				//}
				//else {
					int numVertices = 6;
					int result = graphColoring(matrix, numVertices, &numColors);

					path = "\nМинимальное кол-во цветов для раскраски графа - " + std::to_string(numColors) + "\n";
					//создается дочернее окно
					HWND childWindow = CreateWindowEx(
						0, L"ChildWndClass", L"Дочернее окно", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						300, 300, 300, 150, hWnd, NULL, NULL, NULL
					);
					//проверка на случай если есть проблемы с созданием дочернего окна
					if (childWindow == NULL) {
						MessageBox(childWindow, L"Не удалось создать дочернее окно", L"Ошибка", MB_OK | MB_ICONERROR);
						return -1;
					//}
				};

			}
			break;
		default: break;
		}
		break;
		//при создании
	case WM_CREATE:
		//процедура с созданием необходимых компонентов главного окна 
		hStaticControl = WndStaticControlChild(hWnd);
		MainWndAddWidgetsChild(hWnd);
		hEditControl = WndEditFromChild(hWnd);
		break;
		//при уничтожении
	case WM_DESTROY:
		//FreeLibrary(hinstDLL);
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

//процедура обработки сообщений дочернего окна 
LRESULT CALLBACK SoftwareChildProcedure(HWND childWindow, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE: {

		//создание статического текста, куда будет записан разультат Дийкстры
		if (!IsWindow(childText)) {
			childText = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE,
				0, 0, 300, 300, childWindow, NULL, NULL, NULL);
		}
		//вывод на дочернее окно ответа

		SetWindowTextA(childText, path.c_str());
		break; }
				  //при закрытии
	case WM_CLOSE:
		//включаем главное окно и удаляем дочернее
		EnableWindow(hWnd, TRUE);
		DestroyWindow(childWindow);
		break;


	default: return DefWindowProc(childWindow, msg, wp, lp);
	}

}