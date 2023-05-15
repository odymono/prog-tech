.686P
.MODEL FLAT, C

.CODE

solveGraphColoring proc matrix:DWORD, numVertices:DWORD, numColors:DWORD
    push ebp
    mov ebp, esp

    sub esp, 24     ; Allocate space for local variables

    ; Initialize all vertices without color
    mov edi, 6      ; numVertices
    xor ecx, ecx    ; Loop counter
init_colors:
    mov dword ptr [ebp - 24 + ecx * 4], -1    ; colors[ecx] = -1
    inc ecx
    cmp ecx, edi
    jl init_colors

    ; Color the first vertex with the first color
    xor ecx, ecx
    mov dword ptr [ebp - 24 + ecx * 4], 0     ; colors[0] = 0
    mov edi, numColors               ; Store the initial numColors value in edi
    mov dword ptr [eax], 1    ; Store the initial numColors value as 1

    ; Color the remaining vertices using the greedy algorithm
    xor esi, esi    ; v = 1 (loop counter)
next_vertex:
    mov ecx, edi    ; numVertices
    xor ebx, ebx    ; Loop counter
    xor edx, edx    ; available[] initialization value

init_available:
    mov byte ptr [ebp - 4 + ebx], dl    ; available[ebx] = 0
    inc ebx
    cmp ebx, ecx
    jl init_available

    xor eax, eax    ; chosenColor (loop counter)
    xor ebx, ebx    ; chosenColor (flag)
find_color:
    cmp eax, ecx
    jge invalid_input   ; Return -1 if no available color is found

    ; Check if the current color is available
    mov edi, matrix    ; matrix
    mov esi, edx    ; v
    imul esi, 6    ; Multiply index by 6 to get the offset
    add edi, esi
    mov ebx, [edi + eax * 4]    ; matrix[v][i]
    test ebx, ebx
    jnz color_found

    mov edi, [ebp - 24]    ; colors
    mov esi, eax    ; chosenColor
    mov ebx, [edi + esi * 4]    ; colors[chosenColor]
    cmp ebx, -1
    jnz color_found

    inc eax
    jmp find_color



color_found:
    mov edx, 1                       ; available[chosenColor] = true
    mov esi, eax                      ; Store chosenColor in esi
    mov byte ptr [ebp - 4 + esi], dl  ; available[chosenColor] = true

    ; Color the vertex with the chosen color
    mov edi, [ebp - 24]              ; colors
    mov eax, esi                     ; chosenColor
    mov esi, [ebp + 8]               ; numVertices (numColors parameter is at ebp + 8)
    lea edi, [edi + esi * 4]         ; Offset colors by numVertices * 4 bytes
    ;mov dword ptr [edi], eax         ; colors[v] = chosenColor

    ; Update the minimum number of colors needed
    mov edi, [ebp + 8]               ; numColors
    cmp eax, dword ptr [edi]
    jle num_colors_updated
    mov dword ptr [edi], eax

num_colors_updated:
    inc esi
    cmp esi, [ebp + 12]              ; numVertices (numVertices parameter is at ebp + 12)
    jl next_vertex






invalid_input:
    mov eax, -1     ; Return -1 for invalid input

    mov esp, ebp
    pop ebp
    ret

solveGraphColoring ENDP

END
