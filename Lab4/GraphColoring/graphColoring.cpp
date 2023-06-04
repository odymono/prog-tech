#include "pch.h"

#define DLL_EXPORT __declspec(dllexport)
extern "C" {
	DLL_EXPORT int graphColoring(int matrix[6][6], int numVertices, int* numColors)
	{
		// Инициализируем все вершины без цвета
		int colors[6];
		memset(colors, -1, sizeof(colors));

		// Окрасим первую вершину первым цветом
		colors[0] = 0;
		*numColors = 1;

		// Окрашиваем оставшиеся вершины, используя жадный алгоритм
		for (int v = 1; v < numVertices; v++) {
			// Найдем доступные цвета для этой вершины
			bool available[6];
			memset(available, true, sizeof(available));
			for (int i = 0; i < numVertices; i++) {
				if (matrix[v][i] && colors[i] != -1) {
					available[colors[i]] = false;
				}
			}

			// Выбираем первый доступный цвет
			int chosenColor;
			for (chosenColor = 0; chosenColor < numVertices; chosenColor++) {
				if (available[chosenColor]) {
					break;
				}
			}

			// Если доступного цвета не найдено, вернем -1 (неверный ввод)
			if (chosenColor == numVertices) {
				return -1;
			}

			// Окрашиваем вершину выбранным цветом
			colors[v] = chosenColor;

			// Обновляем минимальное количество необходимых цветов
			if (chosenColor + 1 > *numColors) {
				*numColors = chosenColor + 1;
			}
		}

		// Возвращаем окрашенный граф
		int result = 0;
		for (int i = 0; i < numVertices; i++) {
			result |= (colors[i] << (i * 3));
		}
		return result;
	}
}