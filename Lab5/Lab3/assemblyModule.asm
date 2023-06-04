.model flat, C

.data
    colors DWORD 0, 0, 0, 0, 0, 0   ; Внутренний массив для хранения цветов

.code

; eax -> кол-во вершин
; ebx -> указатель на массив matrix[6][6]


GC PROC
	;--------------------- INIT ------------------------------
	push ebp
	mov ebp, esp
	

	mov ebx, [ebp + 8] ; указатель на первый элемент массива matrix
	mov edx, [ebp + 12] ; записали в edx количество вершин
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

			mov esi, ebx ; esi получает указатель на matrix
			mov edi, OFFSET colors ; edi получает указатель на colors

			lea esi, [esi + eax * 4]
			lea esi, [esi + ecx * 4]

			movzx esi, word ptr [esi] ; Загружаем значение matrix[i][j] в регистр esi
			mov edi, [OFFSET colors + ecx * 4] ; Загружаем значение colors[j] в регистр edi

			cmp esi, 1 ; matrix[i][j] == 1
			je step1fine
			jmp hef2

			step1fine:
			cmp edi, [OFFSET colors + ecx * 4] ; colors[i] == colors[j]
			je colorinc
			jmp hef2

			colorinc:
			mov esi, [OFFSET colors + ecx * 4] ; Загрузка значения colors[j] в регистр esi
			inc esi ; Увеличение значения в регистре esi на 1
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

	; Найти максимальное значение в массиве colors
	mov ecx, 6 ; Загружаем количество элементов в массиве colors
	mov ebx, OFFSET colors ; Загружаем указатель на массив colors
	mov eax, [ebx] ; Инициализируем eax значением первого элемента colors

	find_max:
		cmp ecx, 1 ; Сравниваем счетчик с 1
		jle endfindmax ; Если остался только один элемент, переходим к завершению
		add ebx, 4 ; Увеличиваем указатель на 4 байта для доступа к следующему элементу
		cmp eax, dword ptr [ebx] ; Сравниваем текущий максимум с текущим элементом
		jge skip_update ; Если текущий максимум больше или равен текущему элементу, пропускаем обновление
		mov eax, dword ptr [ebx] ; Обновляем текущий максимум
	skip_update:
		loop find_max ; Продолжаем цикл для остальных элементов

	endfindmax:
		; Теперь максимальное значение находится в регистре eax

	;--------------------- FIND MAX ------------------------------



	;--------------------- RETURN ------------------------------
	mov esp, ebp

	pop ebp


	ret
	;--------------------- RETURN ------------------------------


GC ENDP

end