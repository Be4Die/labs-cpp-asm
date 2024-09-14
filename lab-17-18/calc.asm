.686P
.MODEL FLAT, C

.DATA
    seven_const REAL8 7.0
    ten_const REAL8 10.0
    eight_const REAL8 8.0
    twelve_const REAL8 12.0
    two_const REAL8 2.0

.CODE

;;(x^2-7x+10)/(x^2-8x+12)
calc1		PROC
            fld qword ptr [esp+4]   ; st(0)=x
            fmul st(0), st(0)       ; st(0)=x^2
            fld qword ptr [esp+4]   ; st(0)=x, st(1)=x^2
            fld seven_const         ; st(0)=7, st(1)=x, st(2)=x^2
            fmul st(1), st(0)       ; st(0)=7, st(1)=7x, st(2)=x^2
            fstp st(0)              ; st(0)=7x, st(1)=x^2
            fsub st(1), st(0)       ; st(0)=7x, st(1)=x^2 - 7x
            fstp st(0)              ; st(0)=x^2 - 7x
            fld ten_const           ; st(0)=10, st(1)=x^2 - 7x
            fadd st(1), st(0)       ; st(0)=10, st(1)=x^2 - 7x + 10
            fstp st(0)              ; st(0)=x^2 - 7x + 10
            fld qword ptr [esp+4]   ; st(0)=x, st(1)=x^2 - 7x + 10
            fmul st(0), st(0)       ; st(0)=x^2, st(1)=x^2 - 7x + 10
            fld eight_const         ; st(0)=8, st(1)=x^2, st(2)=x^2 - 7x + 10
            fld qword ptr [esp+4]   ; st(0)=x, st(1)=8, st(2)=x^2, st(3)=x^2 - 7x + 10
            fmul st(0), st(1)       ; st(0)=8x, st(1)=8, st(2)=x^2, st(3)=x^2 - 7x + 10
            fstp st(1)              ; st(0)=8x, st(1)=x^2, st(2)=x^2 - 7x + 10
            fsub st(1), st(0)       ; st(0)=8x, st(1)=x^2-8x, st(2)=x^2 - 7x + 10
            fstp st(0)              ; st(0)=x^2-8x, st(1)=x^2 - 7x + 10
            fld twelve_const        ; st(0)=12, st(1)=x^2-8x, st(2)=x^2 - 7x + 10
            fadd st(1), st(0)       ; st(0)=12, st(1)=x^2-8x+12, st(2)=x^2 - 7x + 10
            fstp st(0)              ; st(0)=x^2-8x+12, st(1)=x^2 - 7x + 10
            fdiv st(1), st(0)       ; st(0)=x^2-8x+12, st(1)=(x^2 - 7x + 10)/(x^2-8x+12)
            fstp st(0)
            ret
calc1		ENDP

;;(1-cos(2x)+sin(2x)) / (1+cos(2x)+sin(2x))
calc2		PROC
            fld qword ptr [esp+4]   ; st(0)=x
            fld two_const           ; st(0)=2, st(1)=x
            fmul st(0), st(1)       ; st(0)=2x, st(1)=x
            fstp st(1)              ; st(0)=2x
            fld st(0)               ; st(0)=2x, st(1)=2x
            fsin                    ; st(0)=sin(2x), st(1)=2x
            fld st(1)               ; st(0)=2x, st(1)=sin(2x), st(2)=2x
            fcos                    ; st(0)=cos(2x), st(1)=sin(2x), st(2)=2x
            fstp st(2)              ; st(0)=sin(2x), st(1)=cos(2x)
            fld1                    ; st(0)=1, st(1)=sin(2x), st(2)=cos(2x)
            fsub st(0), st(2)       ; st(0)=1-cos(2x), st(1)=sin(2x), st(2)=cos(2x)
            fadd st(0), st(1)       ; st(0)=1-cos(2x)+sin(2x), st(1)=sin(2x), st(2)=cos(2x)
            fld1                    ; st(0)=1, st(1)=1-cos(2x)+sin(2x), st(2)=sin(2x), st(3)=cos(2x)
            fadd st(0), st(3)       ; st(0)=1+cos(2x), st(1)=1-cos(2x)+sin(2x), st(2)=sin(2x), st(3)=cos(2x)
            fadd st(0), st(2)       ; st(0)=1+cos(2x)+sin(2x), st(1)=1-cos(2x)+sin(2x), st(2)=sin(2x), st(3)=cos(2x)
            ;fstp st(3)              ; st(0)=1+cos(2x)+sin(2x), st(1)=1-cos(2x)+sin(2x), st(2)=sin(2x)
            ;fstp st(2)              ; st(0)=1+cos(2x)+sin(2x), st(1)=1-cos(2x)+sin(2x)
            fdiv st(1), st(0)       ; st(0)=1+cos(2x)+sin(2x), st(1)=(1-cos(2x)+sin(2x)) / (1+cos(2x)+sin(2x))
            fstp st(0)
            ret
calc2		ENDP

;; perimetr
calc31		PROC
            push ebp
            mov ebp, esp

            ; x1 [ebp + 8]
            ; y1 [ebp + 16]
            ; x2 [ebp + 24]
            ; y2 [ebp + 32]
            ; x3 [ebp + 40]
            ; y3 [ebp + 48]

            fld qword ptr [ebp + 24] 
            fld qword ptr [ebp + 8]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0) 
            fmul st(0), st(0)          ; st(0)=(x1-x2)^2

            fld qword ptr [ebp + 32] 
            fld qword ptr [ebp + 16]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0) 
            fmul st(0), st(0)          ; st(0)=(x1-x2)^2 st(1)=(y1-y2)^2

            fadd st(0), st(1)
            fxch st(1)
            fstp st(0)                 ; st(0)=(x1-x2)^2 + (y1-y2)^2
            fsqrt                       ; st(0)=sqrt((x1-x2)^2 + (y1-y2)^2)

            
            fld qword ptr [ebp + 40] 
            fld qword ptr [ebp + 24]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0) 
            fmul st(0), st(0)          ; st(0)=(x2-x3)^2 st(1)=sqrt((x1-x2)^2 + (y1-y2)^2)

            fld qword ptr [ebp + 32]
            fld qword ptr [ebp + 48]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0) 
            fmul st(0), st(0)          ; st(0)=(x2-x3)^2 st(1)=(y3-y2)^2 st(2)=sqrt((x1-x2)^2 + (y1-y2)^2)

            fadd st(0), st(1)
            fxch st(1)
            fstp st(0)                 ; st(0)=(x2-x3)^2 +(y3-y2)^2 st(1)=sqrt((x1-x2)^2 + (y1-y2)^2)
            fsqrt                       ; st(0)=sqrt((x2-x3)^2 +(y3-y2)^2) st(1)=sqrt((x1-x2)^2 + (y1-y2)^2)
            
            fadd st(0), st(1)
            fxch st(1)
            fstp st(0)                 ; st(0)=sqrt((x2-x3)^2 +(y3-y2)^2)+sqrt((x1-x2)^2 + (y1-y2)^2)

            
            fld qword ptr [ebp + 8] 
            fld qword ptr [ebp + 40]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0) 
            fmul st(0), st(0)          ; st(0)=(x3-x1)^2 st(1)=sqrt((x2-x3)^2 +(y3-y2)^2) + sqrt((x1-x2)^2 + (y1-y2)^2)
            
            fld qword ptr [ebp + 16] 
            fld qword ptr [ebp + 48]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0)
            fmul st(0), st(0)          ; st(0)=(y3-y1)^2 st(1)=(x3-x1)^2 st(2)=sqrt((x2-x3)^2 +(y3-y2)^2) + sqrt((x1-x2)^2 + (y1-y2)^2)

            fadd st(0), st(1)          ; st(0)=(y3-y1)^2+(x3-x1)^2 st(1)=sqrt((x2-x3)^2 +(y3-y2)^2) + sqrt((x1-x2)^2 + (y1-y2)^2)
            fxch st(1)
            fstp st(0)
            fsqrt                      ; st(0)=sqrt((y3-y1)^2+(x3-x1)^2) st(1)=sqrt((x2-x3)^2 +(y3-y2)^2) + sqrt((x1-x2)^2 + (y1-y2)^2)

            fadd st(0), st(1)          ; st(0)=sqrt((y3-y1)^2+(x3-x1)^2) + sqrt((x2-x3)^2 +(y3-y2)^2) + sqrt((x1-x2)^2 + (y1-y2)^2)

            ; Восстанавливаем стек и регистры
            mov esp, ebp
            pop ebp
            ret
calc31		ENDP

;; ploshad
calc32		PROC
            push ebp
            mov ebp, esp

            ; x1 [ebp + 8]
            ; y1 [ebp + 16]
            ; x2 [ebp + 24]
            ; y2 [ebp + 32]
            ; x3 [ebp + 40]
            ; y3 [ebp + 48]


            fld qword ptr [ebp + 8] 
            fld qword ptr [ebp + 24]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0)                    ; st(0)=x2-x1


            fld qword ptr [ebp + 16] 
            fld qword ptr [ebp + 48]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0)                    ; st(0)=x2-x1 st(1)=y3-y1

            fmul st(0), st(1)
            fxch st(1)
            fstp st(0)                    ; st(0)=(x2-x1)*(y3-y1)

            fld qword ptr [ebp + 8] 
            fld qword ptr [ebp + 40]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0)                    ; st(0)=x3-x1 st(1)=(x2-x1)*(y3-y1)

            fld qword ptr [ebp + 16] 
            fld qword ptr [ebp + 32]
            fsub st(0), st(1)
            fxch st(1)
            fstp st(0)                    ; st(0)=y2-x1 st(1)=x3-x1 st(2)=(x2-x1)*(y3-y1)

            fmul st(0), st(1)
            fxch st(1)
            fstp st(0)                    ; st(0)=(y2-x1)*(s=x3-x1) st(1)=(x2-x1)*(y3-y1)
            
            fxch st(1)                    ; st(0)=(x2-x1)*(y3-y1) st(1)=(y2-x1)*(s=x3-x1)
            fsub st(0), st(1)             
            fxch st(1)
            fstp st(0)                    ; st(0)=(x2-x1)*(y3-y1)-(y2-x1)*(s=x3-x1)
            fabs                          ; st(0)=|(x2-x1)*(y3-y1)-(y2-x1)*(s=x3-x1)|

            fld two_const
            fxch st(1)
            fdiv st(0), st(1)             ; st(0)=0.5*|(x2-x1)*(y3-y1)-(y2-x1)*(s=x3-x1)|
            fxch st(1)
            fstp st(0)


            ; Восстанавливаем стек и регистры
            mov esp, ebp
            pop ebp
            ret
calc32		ENDP

END