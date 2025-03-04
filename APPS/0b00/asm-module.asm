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

    extern g_char_msg
    extern g_char_r
    extern g_char_g
    extern g_char_b
    extern g_int_rgb
    extern g_long_word
    extern g_int_cisla
    extern g_long_cisla
;***************************************************************************

    section .text

    ; functions

    ;global some_asm_function
    ;extern some_c_function

    ;some_asm_function:
    ;ret

    global swap
    global rgb
    global nullIt
    global move

    swap:
        mov al, [g_char_msg + 3]
        mov ah, [g_char_msg + 4]
        mov [g_char_msg + 3], ah
        mov [g_char_msg + 4], al
        ret

    rgb: 
        mov dword [g_int_rgb], 0
        mov al, [g_char_r]
        mov ah, [g_char_g]
        mov bl, [g_char_b]
        mov [g_int_rgb + 2], al
        mov [g_int_rgb + 1], ah
        mov [g_int_rgb + 0], bl
        ret

    nullIt:
        mov al, 0
        mov [g_long_word + 0], al
        mov [g_long_word + 2], al
        mov [g_long_word + 4], al
        mov [g_long_word + 6], al
        ret

    move:
        movsx rax, dword [g_int_cisla + 0]
        movsx rbx, dword [g_int_cisla + 4]
        mov [g_long_cisla + 0], rax
        mov [g_long_cisla + 8], rbx
        ret


