.MODEL flat, STDCALL
.CODE

graphColoring PROC
    ; Arguments:
    ; ECX - matrix (pointer to int[6][6])
    ; EDX - numVertices (int)
    ; EBX - numColors (pointer to int)
    ; Return:
    ; EAX - result (int)

    ; Local variables:
    LOCAL colors[6]:DWORD
    LOCAL available[6]:BYTE

    ; Initialize colors array with -1
    lea edi, colors
    mov ecx, 6
    xor eax, eax
    rep stosd

    ; Color the first vertex with color 0
    mov dword ptr [colors], 0
    mov eax, 1
    mov dword ptr [ebx], eax

    ; Loop through remaining vertices
    mov ecx, 1
    for_v:
        cmp ecx, edx
        jge end_for_v

        ; Initialize available array with true
        lea edi, available
        mov ecx, 6
        mov al, 1
        rep stosb

        ; Find available colors for the current vertex
        xor ebx, ebx
        mov esi, ecx
        mov ecx, edx
        dec ecx
        for_i:
            cmp ebx, edx
            je end_for_i
            mov edx, [ecx + esi * 4]
            test edx, edx
            jz skip_i
            mov edx, [colors + ebx * 4]
            test edx, edx
            jz skip_i
            movzx edx, byte ptr [available + edx]
            test edx, edx
            jnz skip_i
            mov byte ptr [available + edx], 0
        skip_i:
            inc ebx
            jmp for_i
        end_for_i:

        ; Find the first available color
        xor ebx, ebx
        mov esi, ecx
        mov ecx, edx
        dec ecx
        for_color:
            cmp ebx, edx
            je end_for_color
            movzx edx, byte ptr [available + ebx]
            test edx, edx
            jnz found_color
            inc ebx
            jmp for_color
        found_color:
            mov eax, ebx
            jmp after_for_color
        end_for_color:
            mov eax, edx ; No available color found, return -1
        after_for_color:

        cmp eax, edx
        je return_result

        ; Color the current vertex with the chosen color
        mov dword ptr [colors + ecx * 4], eax

        ; Update the number of colors
        add eax, 1
        cmp eax, dword ptr [ebx]
        jle skip_update_numColors
        mov dword ptr [ebx], eax
    skip_update_numColors:

        inc ecx
        jmp for_v
    end_for_v:

    return_result:
        xor eax, eax
        mov ecx, edx
        xor edx, edx
        for_result:
            cmp edx, ecx
            je end_for_result
            mov ebx, [colors + edx * 4]
            shl ebx, cl
            or eax, ebx
            inc edx
            jmp for_result
        end_for_result:

    ret
graphColoring ENDP
END
