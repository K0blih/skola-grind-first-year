;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
;***************************************************************************

    bits 64

    section .data

    extern g_int_pole
    extern g_int_N
    extern g_int_pocet
    extern g_char_str
    extern g_int_mezer

;***************************************************************************

    section .text

    global checkSumMSB
    global countNotMultiple
    global countSpacesSeq

;***************************************************************************

checkSumMSB:
    mov rcx, 10            ; Array length
    mov rdi, 0             ; Index

loop_checksum:
    mov eax, [g_int_pole + rdi * 4]   ; Load current array element
    mov ebx, eax
    shr ebx, 24           ; Get upper byte (MSB)

    mov edx, eax
    and edx, 0xFFFFFF      ; Mask lower 3 bytes

    mov r8d, edx
    and r8d, 0xFF          ; Get byte 1
    mov r9d, edx
    shr r9d, 8
    and r9d, 0xFF          ; Get byte 2
    mov r10d, edx
    shr r10d, 16
    and r10d, 0xFF         ; Get byte 3

    add r8d, r9d
    add r8d, r10d          ; Sum lower 3 bytes

    cmp r8d, ebx
    je skip_zero           ; If sum equals MSB, skip setting to 0

    mov dword [g_int_pole + rdi * 4], 0 ; Set element to 0

skip_zero:
    inc rdi
    loop loop_checksum
    ret

;***************************************************************************

countNotMultiple:
    mov rcx, 10          ; Array length
    mov rdi, 0           ; Index
    mov rbx, 0           ; Counter
    mov r8d, [g_int_N]   ; Load 2N into r8d
    shl r8d, 1           ; Multiply N by 2

loop_not_multiple:
    mov eax, [g_int_pole + rdi * 4]
    test eax, r8d        ; Test if not divisible by 2N
    jz skip_not_multiple ; If divisible, skip increment

    inc rbx

skip_not_multiple:
    inc rdi
    loop loop_not_multiple

    mov [g_int_pocet], rbx
    ret

;***************************************************************************

countSpacesSeq:
    mov rcx, g_char_str    ; Load address
    mov rdi, 0             ; Index
    mov rbx, 0             ; Space sequence counter
    mov r8, 0              ; In-sequence flag

loop_spaces_seq:
    mov al, [rcx + rdi]
    test al, al            ; Check null terminator
    jz end_spaces_seq      ; End if null terminator

    cmp al, ' '            ; Compare with space
    jne end_space_seq      ; If not space, reset flag

    cmp r8, 0              ; Check if already in sequence
    jne skip_space_inc
    inc rbx                ; New sequence found
    mov r8, 1              ; Set in-sequence flag

skip_space_inc:
    jmp continue_space_seq

end_space_seq:
    mov r8, 0              ; Reset in-sequence flag

continue_space_seq:
    inc rdi
    jmp loop_spaces_seq

end_spaces_seq:
    mov [g_int_mezer], rbx
    ret
