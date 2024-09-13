.686P
.MODEL FLAT, C

.CODE

calc1		PROC
            fadd st(2), st
            fsub st, st(1)
            fdiv st, st(2)
            fstp qword [ebx]
            finit
            ret
calc1		ENDP

END