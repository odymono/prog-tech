#include "pch.h"

#define DLL_EXPORT __declspec(dllexport)
extern "C" {
	DLL_EXPORT int graphColoring(int matrix[6][6], int numVertices, int* numColors)
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
}