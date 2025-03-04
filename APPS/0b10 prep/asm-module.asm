;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Implementation of the four required functions
;
;***************************************************************************

    bits 64

    section .data

    ; variables
    extern t1_pole
    extern t1_N
    extern t2_pole
    extern t2_N
    extern t1_str
    extern t2_str
    extern t_nahradni_znak

;***************************************************************************

    section .text

    ; functions
    global uprav_pole
    global hledej_max_msb
    global pocet_cislic
    global nahrada_mezer

;***************************************************************************

uprav_pole:
    ; rdi = pointer to array t_pole
    ; esi = t_N (number of elements)
    
    xor rcx, rcx            ; Initialize counter to 0
    
loop_uprav:
    cmp rcx, rsi            ; Compare counter with number of elements
    jge end_uprav           ; If counter >= t_N, end loop
    
    mov eax, [rdi + rcx*4]  ; Load current array element
    cmp eax, 0              ; Test if positive or negative
    jl negative_number      ; Jump if lower
    
    ; For positive numbers, set lowest bit to 1 (make odd)
    and eax, 0xFFFFFFFE     ; Clear bit 0
    jmp update_element      ; Jump to update the element
    
negative_number:
    ; For negative numbers, set lowest bit to 0 (make even)
    or eax, 1               ; Set bit 0 to 1
    
update_element:
    mov [rdi + rcx*4], eax  ; Store updated value back to array
    inc rcx                 ; Increment counter
    jmp loop_uprav          ; Continue loop
    
end_uprav:
    ret                     ; Return

;***************************************************************************

hledej_max_msb:
    ; rdi = pointer to array t_pole
    ; esi = t_N (number of elements)
    
    xor rcx, rcx            ; Initialize counter to 0
    xor rdx, rdx            ; Position of maximum
    xor r8, r8              ; Maximum MSB value found
    
loop_msb:
    cmp ecx, esi            ; Compare counter with number of elements
    jge end_msb             ; If counter >= t_N, end loop
    
    ; mov rax, [rdi + rcx*8]  ; Load current array element (64-bit long)
    ; shr rax, 56             ; Shift right by 56 bits to get MSB
    ; and rax, 0xFF           ; Mask to ensure only lowest byte remains
    mov al, [rdi + rcx*8 + 7] ; Access the most significant byte directly
    
    cmp al, r8b             ; Compare current MSB with max found
    jbe not_greater         ; If not greater, skip update
    
    mov r8b, al             ; Update maximum MSB value
    mov rdx, rcx            ; Update position of maximum
    
not_greater:
    inc rcx                 ; Increment counter
    jmp loop_msb            ; Continue loop
    
end_msb:
    mov rax, rdx            ; Move result position to return value
    ret                     ; Return

;***************************************************************************

pocet_cislic:
    ; rdi = pointer to string t_str
    
    xor rcx, rcx            ; Initialize counter to 0 (string index)
    xor rax, rax            ; Initialize digit count to 0
    
loop_count:
    mov dl, [rdi + rcx]     ; Load current character
    test dl, dl             ; Check for null terminator
    jz end_count            ; If found null terminator, end loop
    
    cmp dl, '0'             ; Compare with '0'
    jl not_digit            ; If less than '0', not a digit
    cmp dl, '9'             ; Compare with '9'
    jg not_digit            ; If greater than '9', not a digit
    
    ; Character is a digit
    inc rax                 ; Increment digit count
    
not_digit:
    inc rcx                 ; Move to next character
    jmp loop_count          ; Continue loop
    
end_count:
    ret                     ; Return

;***************************************************************************

nahrada_mezer:
    ; rdi = pointer to string t_str
    ; sil = replacement character
    
    xor rcx, rcx            ; Initialize counter to 0 (string index)
    
loop_replace:
    mov dl, [rdi + rcx]     ; Load current character
    test dl, dl             ; Check for null terminator
    jz end_replace          ; If found null terminator, end loop
    
    cmp dl, ' '             ; Compare with space
    jne not_space           ; If not space, skip replacement
    
    ; Character is a space
    mov [rdi + rcx], sil    ; Replace with t_nahradni_znak
    
not_space:
    inc rcx                 ; Move to next character
    jmp loop_replace        ; Continue loop
    
end_replace:
    ret                     ; Return