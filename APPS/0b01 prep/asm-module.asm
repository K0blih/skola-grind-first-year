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

    ;g_some_asm_var dd ?

    extern g_int_soucet
    extern g_int_pole
    extern g_int_pocet
    extern g_long_pole
    extern g_char_pole
    extern g_int_ext
    extern g_char_str
    extern g_int_mezer

;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function
    
    global countPositive
    global countEven
    global charToInt
    global countSpaces

    ;some_asm_function:
    ;ret

    countPositive:
        mov rcx, 10            ; array length
        mov rdi, 0             ; index
        mov rbx, 0             ; counter

    loop_positive:
        mov eax, [g_int_pole + rdi * 4]
        test eax, eax          ; check  if positive
        jle skip_positive      ; if eax <= 0 then jump

        inc rbx

    skip_positive:
        inc rdi
        loop loop_positive     ; decrement rcx and jump if not zero

        mov [g_int_soucet], rbx
        ret

;***************************************************************************

    countEven:
        mov rcx, 10          ; array length
        mov rdi, 0           ; index
        mov rbx, 0           ; counter

    loop_even:
        mov eax, [g_long_pole + rdi * 4]
        test eax, 1          ; check if odd
        jnz skip_even        ; If odd then jump

        inc rbx

    skip_even:
        inc rdi
        loop loop_even       ; decrement rcx and jump if not zero

        mov [g_int_pocet], rbx
        ret

;***************************************************************************

    charToInt:
        mov rcx, 10              ; array length
        mov rdi, 0               ; index
    
    loop_char_to_int:
        mov al, [g_char_pole + rdi]
        movsx eax, al
        mov [g_int_ext + rdi * 4], eax
        
        inc rdi
        loop loop_char_to_int    ; decrement rcx and jump if not zero
    
        ret

;***************************************************************************

    countSpaces:
        mov rdi, 0               ; index
        mov rbx, 0               ; counter

    loop_count_spaces:
        mov al, [g_char_str + rdi]
        test al, al              ; check null terminator
        jz end_count_spaces      ; if null then end loop

        cmp al, ' '              ; cmp element with ' '
        jne skip_space           ; if not space then jump

        inc rbx

    skip_space:
        inc rdi
        jmp loop_count_spaces    ; loop

    end_count_spaces:
        mov [g_int_mezer], rbx   ; Store the count of spaces in g_int_mezer
        ret