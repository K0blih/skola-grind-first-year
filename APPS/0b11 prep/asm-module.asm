;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************

    bits 64

    section .data

    ; variables

    ;global g_some_asm_var
    ;extern g_some_c_var


;***************************************************************************

    section .text

    ; functions

    global bubble
    global strup
    global nejcastejsi
    global prvocislo

bubble:
    ; Parameters:
    ; rdi = pointer to array (tp_int)
    ; rsi = size of array (t_N)
    
    ; Store parameters in safe registers
    mov r8, rdi         ; r8 = pointer to array
    mov r9, rsi         ; r9 = size of array
    
    ; Outer loop - iterate through array
    mov r10, 0          ; r10 = i = 0
outer_loop:
    cmp r10, r9         ; if i >= N, exit outer loop
    jge end_outer_loop
    
    ; Inner loop - compare and swap adjacent elements
    mov rcx, 0          ; rcx = j = 0
inner_loop:
    mov eax, r9d        ; eax = N
    sub eax, 1          ; eax = N - 1
    sub eax, r10d       ; eax = N - 1 - i
    cmp rcx, rax        ; if j >= N - 1 - i, exit inner loop
    jge end_inner_loop
    
    ; Compare adjacent elements
    mov edx, [r8 + rcx*4]       ; edx = array[j]
    mov r11d, [r8 + rcx*4 + 4]  ; r11d = array[j+1]
    
    ; Compare and potentially swap using CMOV
    cmp edx, r11d               ; Compare array[j] with array[j+1]
    mov eax, edx                ; eax = array[j]
    cmovg edx, r11d             ; If array[j] > array[j+1], edx = array[j+1]
    cmovg r11d, eax             ; If array[j] > array[j+1], r11d = array[j]
    
    ; Store the potentially swapped values back
    mov [r8 + rcx*4], edx       ; array[j] = edx
    mov [r8 + rcx*4 + 4], r11d  ; array[j+1] = r11d
    
    inc rcx                     ; j++
    jmp inner_loop
    
end_inner_loop:
    inc r10                     ; i++
    jmp outer_loop
    
end_outer_loop:
    ret

;**************************************************************************

strup:
    ; Parameters:
    ; rdi = pointer to string (t_str)
    
    ; Start processing the string
    mov rcx, 0          ; rcx = index
process_char:
    movzx rax, byte [rdi + rcx] ; rax = current character
    
    ; Check if end of string
    test rax, rax
    jz end_strup
    
    ; Check if lowercase (a-z, ASCII 97-122)
    cmp rax, 'a'
    jl not_lowercase
    cmp rax, 'z'
    jg not_lowercase
    
    ; If we get here, the character is lowercase, convert to uppercase
    sub rax, 32
    mov [rdi + rcx], al
    
not_lowercase:
    inc rcx
    jmp process_char
    
end_strup:
    ret

;**************************************************************************

nejcastejsi:
    ; Parameters:
    ; rdi = pointer to string (t_str)
    
    ; Allocate local array for character counts (256 bytes)
    sub rsp, 256
    
    ; Clear the counts array
    mov rcx, 0
clear_loop:
    mov byte [rsp + rcx], 0
    inc rcx
    cmp rcx, 256
    jl clear_loop
    
    ; Count occurrences of each character
    mov rdx, rdi        ; rdx = pointer to string
    mov rcx, 0          ; rcx = index
count_loop:
    movzx rax, byte [rdx + rcx]  ; rax = current character
    
    ; Check if end of string
    test rax, rax
    jz end_count_loop
    
    ; Increment count for this character
    inc byte [rsp + rax]
    
    inc rcx
    jmp count_loop
    
end_count_loop:
    ; Find character with maximum occurrences
    mov rcx, 0          ; rcx = current character
    mov r8, 0           ; r8 = max occurrences
    mov r9, 0           ; r9 = character with max occurrences
    
find_max_loop:
    movzx rax, byte [rsp + rcx]  ; rax = count of current character
    
    ; Skip zero counts and control characters
    test rax, rax
    jz next_check
    cmp rcx, 32         ; Skip characters below space (control chars)
    jl next_check
    
    ; Use CMOV to update max count and character if current count is higher
    cmp rax, r8
    cmovg r8, rax       ; If count > max_count, update max_count
    cmovg r9, rcx       ; If count > max_count, update max_character
    
next_check:
    inc rcx
    cmp rcx, 256
    jl find_max_loop
    
    ; Return the most frequent character
    mov rax, r9
    
    ; Cleanup stack and return
    add rsp, 256
    ret

;**************************************************************************

prvocislo:
    ; Parameters:
    ; rdi = number to check (t_cislo)
    
    ; Special cases: numbers less than 2 are not prime
    cmp rdi, 2
    jl not_prime
    
    ; 2 is prime
    cmp rdi, 2
    je is_prime
    
    ; Even numbers greater than 2 are not prime
    test rdi, 1
    jz not_prime
    
    ; Check divisibility from 3 to sqrt(n)
    mov rcx, 3          ; rcx = divisor
check_loop:
    mov rax, rcx
    mul rax             ; rax = divisor^2
    
    ; If divisor^2 > n, then n is prime
    cmp rax, rdi
    jg is_prime
    
    ; Check if n is divisible by current divisor
    mov rax, rdi
    xor rdx, rdx
    div rcx             ; rdx = n % divisor
    
    ; If remainder is 0, n is not prime
    test rdx, rdx
    jz not_prime
    
    ; Try next odd divisor
    add rcx, 2
    jmp check_loop
    
is_prime:
    ; Return the original number for prime numbers
    mov rax, rdi
    ret
    
not_prime:
    ; Return -1 for non-prime numbers
    mov rax, -1
    ret