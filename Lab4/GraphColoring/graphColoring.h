#pragma once

extern "C" {
    __declspec(dllimport) int graphColoring(int matrix[6][6], int numVertices, int* numColors);

}