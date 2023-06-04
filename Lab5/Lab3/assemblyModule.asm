.model flat, C

.data
    colors DWORD 0, 0, 0, 0, 0, 0   ; ���������� ������ ��� �������� ������

.code

; eax -> ���-�� ������
; ebx -> ��������� �� ������ matrix[6][6]


GC PROC
	;--------------------- INIT ------------------------------
	push ebp
	mov ebp, esp
	

	mov ebx, [ebp + 8] ; ��������� �� ������ ������� ������� matrix
	mov edx, [ebp + 12] ; �������� � edx ���������� ������
	;--------------------- INIT ------------------------------


	;--------------------- NULLING COLORS ------------------------------
	mov eax, 0
	nulling:
	mov esi, dword ptr [OFFSET colors + eax * 4]
	mov dword ptr [OFFSET colors + eax * 4], 0
	inc eax
	cmp eax, 6
	jne nulling
	;--------------------- NULLING COLORS ------------------------------


	;--------------------- MAIN FUNC ------------------------------
	start:

	mov eax, 0 ; eax = 0 ----------------- i
	for1:

		cmp eax, edx
		jge endfor1

		mov ecx, 0 ; ecx = 0 ------------- j
		for2:

			cmp ecx, edx
			jge endfor2

			mov esi, ebx ; esi �������� ��������� �� matrix
			mov edi, OFFSET colors ; edi �������� ��������� �� colors

			lea esi, [esi + eax * 4]
			lea esi, [esi + ecx * 4]

			movzx esi, word ptr [esi] ; ��������� �������� matrix[i][j] � ������� esi
			mov edi, [OFFSET colors + ecx * 4] ; ��������� �������� colors[j] � ������� edi

			cmp esi, 1 ; matrix[i][j] == 1
			je step1fine
			jmp hef2

			step1fine:
			cmp edi, [OFFSET colors + ecx * 4] ; colors[i] == colors[j]
			je colorinc
			jmp hef2

			colorinc:
			mov esi, [OFFSET colors + ecx * 4] ; �������� �������� colors[j] � ������� esi
			inc esi ; ���������� �������� � �������� esi �� 1
			mov [OFFSET colors + ecx * 4], esi ;
			cmp ecx, 0

			hef2:

			inc ecx
			jmp for2

		endfor2:
		inc eax
		jmp for1

	endfor1:

	;--------------------- MAIN FUNC ------------------------------



	;--------------------- FIND MAX ------------------------------

	; ����� ������������ �������� � ������� colors
	mov ecx, 6 ; ��������� ���������� ��������� � ������� colors
	mov ebx, OFFSET colors ; ��������� ��������� �� ������ colors
	mov eax, [ebx] ; �������������� eax ��������� ������� �������� colors

	find_max:
		cmp ecx, 1 ; ���������� ������� � 1
		jle endfindmax ; ���� ������� ������ ���� �������, ��������� � ����������
		add ebx, 4 ; ����������� ��������� �� 4 ����� ��� ������� � ���������� ��������
		cmp eax, dword ptr [ebx] ; ���������� ������� �������� � ������� ���������
		jge skip_update ; ���� ������� �������� ������ ��� ����� �������� ��������, ���������� ����������
		mov eax, dword ptr [ebx] ; ��������� ������� ��������
	skip_update:
		loop find_max ; ���������� ���� ��� ��������� ���������

	endfindmax:
		; ������ ������������ �������� ��������� � �������� eax

	;--------------------- FIND MAX ------------------------------



	;--------------------- RETURN ------------------------------
	mov esp, ebp

	pop ebp


	ret
	;--------------------- RETURN ------------------------------


GC ENDP

end