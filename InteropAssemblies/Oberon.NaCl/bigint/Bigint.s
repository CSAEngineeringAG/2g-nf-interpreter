;/*
; * Mountaineer Prime NaCl Library
; * Copyright: Oberon microsystems inc.
; * Based on NaCl by D. J. Bernstein
; * and avrnacl by Michael Hutter & Peter Schwabe.
; */

                EXPORT  bigint_add128
				EXPORT  bigint_mul128
                EXPORT  bigint_add256
                EXPORT  bigint_sub256
                EXPORT  bigint_mul256
                EXPORT  bigint_cmov256
				
                EXPORT  crypto_sign_ed25519_ref_fe25519_cmov
                EXPORT  crypto_sign_ed25519_ref_fe25519_add
                EXPORT  crypto_sign_ed25519_ref_fe25519_sub
                EXPORT  crypto_sign_ed25519_ref_fe25519_square
                EXPORT  crypto_sign_ed25519_ref_fe25519_mul
                EXPORT  crypto_sign_ed25519_ref_fe25519_mul121666
                EXPORT  crypto_sign_ed25519_ref_fe25519_freeze
				
                EXPORT  freeze1305
                EXPORT  addmulmod1305
				
                EXPORT  salsa20rounds
                EXPORT  chacha20rounds


                AREA    |.text|, CODE, READONLY
				
				
				GBLL    UseDspMul
				GBLL    UseFpuReg
UseDspMul       SETL    {FALSE}
UseFpuReg       SETL    {FALSE}

				IF      {CPU} = "7E-M"
UseDspMul         SETL    {TRUE}
				ENDIF
				IF      {CPU} = "Cortex-M4"
UseDspMul         SETL    {TRUE}
				ENDIF
				IF      {CPU} = "Cortex-M4.fp"
UseDspMul         SETL    {TRUE}
UseFpuReg         SETL    {TRUE}
				ENDIF
				IF      {FPU} = "FPv4-SP"
UseFpuReg         SETL    {TRUE}
				ENDIF
				
				
; Register Save Macros

; Load Register
				MACRO
				LOAD	$r,$s,$off
				IF      UseFpuReg
				  vmov    $r,$s
				ELSE
				  ldr     $r,[SP,#$off]
				ENDIF
				MEND
				
; Save Register
				MACRO
				SAVE	$r,$s,$off
				IF      UseFpuReg
				  vmov    $s,$r
				ELSE
				  str     $r,[SP,#$off]
				ENDIF
				MEND
				
; Load Double Register
				MACRO
				DLOAD	$ra,$rb,$sa,$sb,$off
				IF      UseFpuReg
				  vmov    $ra,$rb,$sa,$sb
				ELSE
				  ldrd    $ra,$rb,[SP,#$off]
				ENDIF
				MEND
				
; Save Double Register
				MACRO
				DSAVE	$ra,$rb,$sa,$sb,$off
				IF      UseFpuReg
				  vmov    $sa,$sb,$ra,$rb
				ELSE
				  strd    $ra,$rb,[SP,#$off]
				ENDIF
				MEND
				
				
; Multiply Macros

; Long Multiply
; c:p = x * y
				MACRO
				LMUL    $p,$c,$x,$y
				umull   $p,$c,$x,$y
				MEND
				
; Long Multiply and Add
; c:p = p + x * y
				MACRO
				LMULA   $p,$c,$x,$y
				;IF      UseDspMul
				;  mov     $c,#0
				;  umaal   $p,$c,$x,$y
				;ELSE
				  mov     $c,#0
				  umlal   $p,$c,$x,$y
				;ENDIF
				MEND
				
; Long Multiply and Add with Carry Word
; c:p = p + x * y + c
				MACRO
				LMULAC  $p,$c,$x,$y
				IF      UseDspMul
				  umaal   $p,$c,$x,$y
				ELSE
				  adds    $p,$c
				  mov     $c,#0
				  adc     $c,$c
				  umlal   $p,$c,$x,$y
				ENDIF
				MEND
				
; 4 Word Multiply
; p4:p3:p2:p1:p0 = x3:x2:x1:x0 * y
				MACRO
				WMUL    $p0,$p1,$p2,$p3,$p4,$x0,$x1,$x2,$x3,$y
				LMUL    $p0,$p1,$x0,$y   ; p1:p0 = x0 * y
				LMULA   $p1,$p2,$x1,$y   ; p2:p1 = x1 * y + p1
				LMULA   $p2,$p3,$x2,$y   ; p3:p2 = x2 * y + p2
				LMULA   $p3,$p4,$x3,$y   ; p4:p3 = x3 * y + p3
				MEND
				
; 4 Word Multiply extension
; p4:p3:p2:p1:p0 = x3:x2:x1:x0 * y + p0
				MACRO
				WMULX   $p0,$p1,$p2,$p3,$p4,$x0,$x1,$x2,$x3,$y
				LMULA   $p0,$p1,$x0,$y  ; p1:p0 = x0 * y + p0
				LMULA   $p1,$p2,$x1,$y  ; p2:p1 = x1 * y + p1
				LMULA   $p2,$p3,$x2,$y  ; p3:p2 = x2 * y + p2
				LMULA   $p3,$p4,$x3,$y  ; p4:p3 = x3 * y + p3
				MEND
				
; 4 Word Multiply and Add
; c:p3:p2:p1:p0 = p3:p2:p1:p0 + x3:x2:x1:x0 * y
				MACRO
				WMULA   $p0,$p1,$p2,$p3,$c,$x0,$x1,$x2,$x3,$y
				LMULA   $p0,$c,$x0,$y   ; c:p0 += x0 * y
				LMULAC  $p1,$c,$x1,$y   ; c:p1 += x1 * y + c
				LMULAC  $p2,$c,$x2,$y   ; c:p2 += x2 * y + c
				LMULAC  $p3,$c,$x3,$y   ; c:p3 += x3 * y + c
				MEND
				
; 4 Word Multiply and Add extension
; c:p3:p2:p1:p0 = p3:p2:p1:p0 + x3:x2:x1:x0 * y + c
				MACRO
				WMULAC  $p0,$p1,$p2,$p3,$c,$x0,$x1,$x2,$x3,$y
				LMULAC  $p0,$c,$x0,$y   ; c:p0 += x0 * y + c
				LMULAC  $p1,$c,$x1,$y   ; c:p1 += x1 * y + c
				LMULAC  $p2,$c,$x2,$y   ; c:p2 += x2 * y + c
				LMULAC  $p3,$c,$x3,$y   ; c:p3 += x3 * y + c
				MEND
				


; void bigint_add128(uint32 r[4], const uint32 a[4], const uint32 b[4])

bigint_add128   PROC
				push    {r4-r6}
				ldm     r1,{r3-r6}    ; x0-x3

				ldm     r2!,{r1,r12}  ; y0-y1
				adds    r3,r3,r1      ; c:x0 += y0
				adcs    r4,r4,r12     ; c:x1 += y1
				ldm     r2!,{r1,r12}  ; y2-y3
				adcs    r5,r5,r1      ; c:x2 += y2
				adcs    r6,r6,r12     ; c:x3 += y3
				stm     r0,{r3-r6}    ; store result

				pop     {r4-r6}
				bx      lr
                ENDP


; char bigint_add256(uint32 r[8], const uint32 a[8], const uint32 b[8])

bigint_add256   PROC
				push    {r4-r11}
				ldm     r1,{r3-r10}   ; x0-x7

				ldm     r2!,{r11,r12} ; y0-y1
				adds    r3,r3,r11     ; c:x0 += y0
				adcs    r4,r4,r12     ; c:x1 += y1
				ldm     r2!,{r11,r12} ; y2-y3
				adcs    r5,r5,r11     ; c:x2 += y2
				adcs    r6,r6,r12     ; c:x3 += y3
				ldm     r2!,{r11,r12} ; y4-y5
				adcs    r7,r7,r11     ; c:x4 += y4
				adcs    r8,r8,r12     ; c:x5 += y5
				ldm     r2!,{r11,r12} ; y6-y7
				adcs    r9,r9,r11     ; c:x6 += y6
				adcs    r10,r10,r12   ; c:x7 += y7
				stm     r0,{r3-r10}   ; store result

				sbcs    r0,r0         ; c - 1
				adds    r0,#1         ; c
				pop     {r4-r11}
				bx      lr
                ENDP


; char bigint_sub256(uint32 r[8], const uint32 a[8], const uint32 b[8])

bigint_sub256   PROC
				push    {r4-r11}
				ldm     r1,{r3-r10}   ; x0-x7

				ldm     r2!,{r11,r12} ; y0-y1
				subs    r3,r3,r11     ; c:x0 += y0
				sbcs    r4,r4,r12     ; c:x1 += y1
				ldm     r2!,{r11,r12} ; y2-y3
				sbcs    r5,r5,r11     ; c:x2 += y2
				sbcs    r6,r6,r12     ; c:x3 += y3
				ldm     r2!,{r11,r12} ; y4-y5
				sbcs    r7,r7,r11     ; c:x4 += y4
				sbcs    r8,r8,r12     ; c:x5 += y5
				ldm     r2!,{r11,r12} ; y6-y7
				sbcs    r9,r9,r11     ; c:x6 += y6
				sbcs    r10,r10,r12   ; c:x7 += y7
				stm     r0,{r3-r10}   ; store result

				sbcs    r0,r0         ; c - 1
				negs    r0,r0         ; 1 - c = borrow
				pop     {r4-r11}
				bx      lr
                ENDP


; void bigint_mul128(uint32 r[8], const uint32 a[4], const uint32 b[4])

bigint_mul128   PROC
				push    {r4-r10}
				ldm     r1,{r1,r3-r5}  ; x0-x3

				ldr     r6,[r2,#0]     ; y0
				WMUL    r9,r10,r12,r7,r8,r1,r3,r4,r5,r6  ; p4:0 = x3:0 * y0
				str     r9,[r0],#4     ; store p0

				ldr     r6,[r2,#4]     ; y1
				WMULA   r10,r12,r7,r8,r9,r1,r3,r4,r5,r6  ; p5:1 += x3:0 * y1
				str     r10,[r0],#4    ; store p1

				ldr     r6,[r2,#8]     ; y2
				WMULA   r12,r7,r8,r9,r10,r1,r3,r4,r5,r6  ; p6:2 += x3:0 * y2
				str     r12,[r0],#4    ; store p2

				ldr     r6,[r2,#12]    ; y3
				WMULA   r7,r8,r9,r10,r12,r1,r3,r4,r5,r6  ; p7:3 += x3:0 * y2

				stm     r0,{r7-r10,r12}; store p3-p7
				pop     {r4-r10}
				bx      lr
                ENDP
				

; void bigint_mul256(uint32 r[16], const uint32 a[8], const uint32 b[8])

bigint_mul256   PROC
				push    {r4-r11,lr}
				IF      UseFpuReg
				  vmov    s8,s9,r0,r1
				  vldm    r2,{s0-s7}    ; y0-y7
				ELSE
				  ldm     r2,{r4-r11}
				  push    {r0,r1,r4-r11}; r,x,y0-y7
				  sub     sp,#28        ; p0-p6
				ENDIF

				ldm     r1,{r0,r3-r5} ; x0-x3

				LOAD    r1,s0,36      ; y0
				WMUL    r7,r8,r9,r10,r11,r0,r3,r4,r5,r1  ; c:p3:0 = x3:0 * y0
				LOAD    r1,s4,52      ; y4
				WMULX   r11,r12,lr,r2,r6,r0,r3,r4,r5,r1  ; p8:4 = x3:0 * y4 + c
				SAVE    r7,s10,0      ; store p0

				LOAD    r1,s1,40      ; y1
				WMULA   r8,r9,r10,r11,r7,r0,r3,r4,r5,r1  ; c:p4:1 += x3:0 * y1
				LOAD    r1,s5,56      ; y5
				WMULAC  r12,lr,r2,r6,r7,r0,r3,r4,r5,r1   ; p9:5 += x3:0 * y5 + c
				SAVE    r8,s11,4      ; store p1

				LOAD    r1,s2,44      ; y2
				WMULA   r9,r10,r11,r12,r8,r0,r3,r4,r5,r1 ; c:p5:2 += x3:0 * y2
				LOAD    r1,s6,60      ; y6
				WMULAC  lr,r2,r6,r7,r8,r0,r3,r4,r5,r1    ; p10:6 += x3:0 * y6 + c
				SAVE    r9,s12,8      ; store p2

				LOAD    r1,s3,48      ; y3
				WMULA   r10,r11,r12,lr,r9,r0,r3,r4,r5,r1 ; c:p6:3 += x3:0 * y3
				LOAD    r1,s7,64      ; y7
				WMULAC  r2,r6,r7,r8,r9,r0,r3,r4,r5,r1    ; p11:7 = x3:0 * y7 + c
				SAVE    r10,s13,12    ; store p3

				LOAD    r1,s9,32      ; x
				add     r1,#16
				ldm     r1,{r0,r3-r5} ; x4-x7

				LOAD    r1,s0,36      ; y0
				WMULA   r11,r12,lr,r2,r10,r0,r3,r4,r5,r1 ; c:p7:4 += x7:4 * y0
				LOAD    r1,s4,52      ; y4
				WMULAC  r6,r7,r8,r9,r10,r0,r3,r4,r5,r1   ; p12:8 += x7:4 * y4 + c
				SAVE    r11,s14,16    ; store p4

				LOAD    r1,s1,40      ; y1
				WMULA   r12,lr,r2,r6,r11,r0,r3,r4,r5,r1  ; c:p8:5 += x7:4 * y1
				LOAD    r1,s5,56      ; y5
				WMULAC  r7,r8,r9,r10,r11,r0,r3,r4,r5,r1  ; p13:9 += x7:4 * y5 + c
				SAVE    r12,s15,20    ; store p5

				LOAD    r1,s2,44      ; y2
				WMULA   lr,r2,r6,r7,r12,r0,r3,r4,r5,r1   ; c:p9:6 += x7:4 * y2
				LOAD    r1,s6,60      ; y6
				WMULAC  r8,r9,r10,r11,r12,r0,r3,r4,r5,r1 ; p14:10 += x7:4 * y6 + c
				SAVE    lr,s16,24     ; store p6

				LOAD    r1,s3,48      ; y3
				WMULA   r2,r6,r7,r8,lr,r0,r3,r4,r5,r1    ; c:p10:7 += x7:4 * y3
				LOAD    r1,s7,64      ; y7
				WMULAC  r9,r10,r11,r12,lr,r0,r3,r4,r5,r1 ; p15:11 += x7:4 * y7 + c

				IF      UseFpuReg
				  vmov    r0,s8         ; r
				  vstm    r0!,{s10-s16} ; store p0-p6
				  stm     r0,{r2,r6-r12,lr} ; store p7-p15
				ELSE
				  ldr     r0,[sp,#28]   ; r
				  add     r1,r0,#28
				  stm     r1,{r2,r6-r12,lr} ; store p7-p15
				  pop     {r3-r9}
				  stm     r0,{r3-r9}    ; store p0-p6
				  add     sp,#40
				ENDIF
				pop     {r4-r11,pc}
                ENDP
				

; void bigint_cmov256(uint32 r[8], const uint32 x[8], uint32 b)
; void fe25519_cmov(fe25519 *r, const fe25519 *x, unsigned char b)

bigint_cmov256  PROC
crypto_sign_ed25519_ref_fe25519_cmov
				push    {r4-r9}
				neg     r2,r2           ; mask = -b
				ldm     r0,{r3-r6}      ; r0-r3
				ldm     r1!,{r7-r9,r12} ; x0-x3
				
				eor     r7,r3           ; x ^ r
				and     r7,r2           ; (x ^ r) & mask
				eor     r3,r7           ; r ^ ((x ^ r) & mask) == mask ? x : r
				eor     r8,r4
				and     r8,r2
				eor     r4,r8
				eor     r9,r5
				and     r9,r2
				eor     r5,r9
				eor     r12,r6
				and     r12,r2
				eor     r6,r12
				
				stm     r0!,{r3-r6}     ; save r0-r3
				ldm     r0,{r3-r6}      ; r4-r7
				ldm     r1,{r7-r9,r12}  ; x4-x7
				
				eor     r7,r3
				and     r7,r2
				eor     r3,r7
				eor     r8,r4
				and     r8,r2
				eor     r4,r8
				eor     r9,r5
				and     r9,r2
				eor     r5,r9
				eor     r12,r6
				and     r12,r2
				eor     r6,r12
				
				stm     r0!,{r3-r6}     ; save r4-r7
				pop     {r4-r9}
				bx      lr
                ENDP


; void fe25519_add(fe25519 *r, const fe25519 *x, const fe25519 *y)

crypto_sign_ed25519_ref_fe25519_add PROC
				push    {r4-r11}
				ldm     r1,{r3-r10}   ; x0-x7

				ldm     r2!,{r11,r12} ; y0-y1
				adds    r3,r3,r11     ; c:x0 += y0
				adcs    r4,r4,r12     ; c:x1 += y1
				ldm     r2!,{r11,r12} ; y2-y3
				adcs    r5,r5,r11     ; c:x2 += y2
				adcs    r6,r6,r12     ; c:x3 += y3
				ldm     r2!,{r11,r12} ; y4-y5
				adcs    r7,r7,r11     ; c:x4 += y4
				adcs    r8,r8,r12     ; c:x5 += y5
				ldm     r2!,{r11,r12} ; y6-y7
				adcs    r9,r9,r11     ; c:x6 += y6
				adcs    r10,r10,r12   ; c:x7 += y7

				mov     r2,#38        ; 2 * 19
				sbc     r1,r1         ; c - 1
				bic     r1,r2,r1      ; c * 38
				adds    r3,r3,r1      ; c:a0 += c * 38
				adcs    r4,r4,#0      ; c:a1 += c
				adcs    r5,r5,#0      ; c:a2 += c
				adcs    r6,r6,#0      ; c:a3 += c
				adcs    r7,r7,#0      ; c:a4 += c
				adcs    r8,r8,#0      ; c:a5 += c
				adcs    r9,r9,#0      ; c:a6 += c
				adcs    r10,r10,#0    ; c:a7 += c

				sbc     r1,r1         ; c - 1
				bic     r1,r2,r1      ; c * 38
				add     r3,r1         ; a0 += c * 38

				stm     r0,{r3-r10}   ; store result
				pop     {r4-r11}
				bx      lr
                ENDP
				

; void fe25519_sub(fe25519 *r, const fe25519 *x, const fe25519 *y)

crypto_sign_ed25519_ref_fe25519_sub PROC
				push    {r4-r11}
				ldm     r1,{r3-r10}   ; x0-x7

				ldm     r2!,{r11,r12} ; y0-y1
				subs    r3,r3,r11     ; c:x0 -= y0
				sbcs    r4,r4,r12     ; c:x1 -= y1
				ldm     r2!,{r11,r12} ; y2-y3
				sbcs    r5,r5,r11     ; c:x2 -= y2
				sbcs    r6,r6,r12     ; c:x3 -= y3
				ldm     r2!,{r11,r12} ; y4-y5
				sbcs    r7,r7,r11     ; c:x4 -= y4
				sbcs    r8,r8,r12     ; c:x5 -= y5
				ldm     r2!,{r11,r12} ; y6-y7
				sbcs    r9,r9,r11     ; c:x6 -= y6
				sbcs    r10,r10,r12   ; c:x7 -= y7

				mov     r2,#38        ; 2 * 19
				sbc     r1,r1         ; c - 1
				and     r1,r2,r1      ; c * 38
				subs    r3,r3,r1      ; c:a0 -= c * 38
				sbcs    r4,r4,#0      ; c:a1 -= c
				sbcs    r5,r5,#0      ; c:a2 -= c
				sbcs    r6,r6,#0      ; c:a3 -= c
				sbcs    r7,r7,#0      ; c:a4 -= c
				sbcs    r8,r8,#0      ; c:a5 -= c
				sbcs    r9,r9,#0      ; c:a6 -= c
				sbcs    r10,r10,#0    ; c:a7 -= c

				sbc     r1,r1         ; c - 1
				and     r1,r2,r1      ; c * 38
				sub     r3,r1         ; a0 -= c * 38

				stm     r0,{r3-r10}   ; store result
				pop     {r4-r11}
				bx      lr
                ENDP
				

; void fe25519_square(fe25519 *r, const fe25519 *x)
; void fe25519_mul(fe25519 *r, const fe25519 *x, const fe25519 *y)

crypto_sign_ed25519_ref_fe25519_square PROC
				mov     r2,r1         ; fe25519_mul(r,x,x)
crypto_sign_ed25519_ref_fe25519_mul
				push    {r4-r11,lr}
				IF      UseFpuReg
				  vmov    s8,s9,r0,r1
				  vldm    r2,{s0-s7}    ; y0-y7
				ELSE
				  ldm     r2,{r4-r11}
				  push    {r0,r1,r4-r11}; r,x,y0-y7
				  sub     sp,#28        ; p0-p6
				ENDIF

				ldm     r1,{r0,r3-r5} ; x0-x3

				LOAD    r1,s0,36      ; y0
				WMUL    r7,r8,r9,r10,r11,r0,r3,r4,r5,r1  ; c:p3:0 = x3:0 * y0
				LOAD    r1,s4,52      ; y4
				WMULX   r11,r12,lr,r2,r6,r0,r3,r4,r5,r1  ; p8:4 = x3:0 * y4 + c
				SAVE    r7,s10,0      ; store p0

				LOAD    r1,s1,40      ; y1
				WMULA   r8,r9,r10,r11,r7,r0,r3,r4,r5,r1  ; c:p4:1 += x3:0 * y1
				LOAD    r1,s5,56      ; y5
				WMULAC  r12,lr,r2,r6,r7,r0,r3,r4,r5,r1   ; p9:5 += x3:0 * y5 + c
				SAVE    r8,s11,4      ; store p1

				LOAD    r1,s2,44      ; y2
				WMULA   r9,r10,r11,r12,r8,r0,r3,r4,r5,r1 ; c:p5:2 += x3:0 * y2
				LOAD    r1,s6,60      ; y6
				WMULAC  lr,r2,r6,r7,r8,r0,r3,r4,r5,r1    ; p10:6 += x3:0 * y6 + c
				SAVE    r9,s12,8      ; store p2

				LOAD    r1,s3,48      ; y3
				WMULA   r10,r11,r12,lr,r9,r0,r3,r4,r5,r1 ; c:p6:3 += x3:0 * y3
				LOAD    r1,s7,64      ; y7
				WMULAC  r2,r6,r7,r8,r9,r0,r3,r4,r5,r1    ; p11:7 = x3:0 * y7 + c
				SAVE    r10,s13,12    ; store p3

				LOAD    r1,s9,32      ; x
				add     r1,#16
				ldm     r1,{r0,r3-r5} ; x4-x7

				LOAD    r1,s0,36      ; y0
				WMULA   r11,r12,lr,r2,r10,r0,r3,r4,r5,r1 ; c:p7:4 += x7:4 * y0
				LOAD    r1,s4,52      ; y4
				WMULAC  r6,r7,r8,r9,r10,r0,r3,r4,r5,r1   ; p12:8 += x7:4 * y4 + c
				SAVE    r11,s14,16    ; store p4

				LOAD    r1,s1,40      ; y1
				WMULA   r12,lr,r2,r6,r11,r0,r3,r4,r5,r1  ; c:p8:5 += x7:4 * y1
				LOAD    r1,s5,56      ; y5
				WMULAC  r7,r8,r9,r10,r11,r0,r3,r4,r5,r1  ; p13:9 += x7:4 * y5 + c
				SAVE    r12,s15,20    ; store p5

				LOAD    r1,s2,44      ; y2
				WMULA   lr,r2,r6,r7,r12,r0,r3,r4,r5,r1   ; c:p9:6 += x7:4 * y2
				LOAD    r1,s6,60      ; y6
				WMULAC  r8,r9,r10,r11,r12,r0,r3,r4,r5,r1 ; p14:10 += x7:4 * y6 + c
				SAVE    lr,s16,24     ; store p6

				LOAD    r1,s3,48      ; y3
				WMULA   r2,r6,r7,r8,lr,r0,r3,r4,r5,r1    ; c:p10:7 += x7:4 * y3
				LOAD    r1,s7,64      ; y7
				WMULAC  r9,r10,r11,r12,lr,r0,r3,r4,r5,r1 ; p15:11 += x7:4 * y7 + c

				mov     r1,#38        ; 2^256 + 38 = 2*p

				DLOAD   r3,r4,s10,s11,0 ; p0-p1
				LMULA   r3,r0,r6,r1   ; c:p0 += p8 * 38
				LMULAC  r4,r0,r7,r1   ; c:p1 += p9 * 38 + c
				DLOAD   r5,r6,s12,s13,8 ; p2-p3
				LMULAC  r5,r0,r8,r1   ; c:p2 += p10 * 38 + c
				LMULAC  r6,r0,r9,r1   ; c:p3 += p11 * 38 + c
				DLOAD   r8,r9,s14,s15,16 ; p4-p5
				LMULAC  r8,r0,r10,r1  ; c:p4 += p12 * 38 + c
				LMULAC  r9,r0,r11,r1  ; c:p5 += p13 * 38 + c
				LOAD    r10,s16,24    ; p6
				LMULAC  r10,r0,r12,r1 ; c:p6 += p14 * 38 + c
				LMULAC  r2,r0,lr,r1   ; c:p7 += p15 * 38 + c

				mul     r0,r0,r1      ; c *= 38
				adds    r3,r3,r0      ; c:a0 += c
				adcs    r4,r4,#0      ; c:a1 += c
				adcs    r5,r5,#0      ; c:a2 += c
				adcs    r6,r6,#0      ; c:a3 += c
				adcs    r7,r8,#0      ; c:a4 += c
				adcs    r8,r9,#0      ; c:a5 += c
				adcs    r9,r10,#0     ; c:a6 += c
				adcs    r10,r2,#0     ; c:a7 += c

				sbc     r0,r0         ; c - 1
				bic     r0,r1,r0      ; c * 38
				add     r3,r0         ; a0 += c * 38

				LOAD    r0,s8,28
				stm     r0,{r3-r10}   ; store result
				IF      UseFpuReg
				ELSE
				  add     sp,#68
				ENDIF
				pop     {r4-r11,pc}
				ENDP


; void fe25519_mul121666(fe25519 *r, const fe25519 *x)

crypto_sign_ed25519_ref_fe25519_mul121666 PROC
				push    {r4-r10}
				ldm     r1,{r4-r10,r12} ; x0-x7
				mov     r1,#121666/2
				lsl     r1,#1         ; 121666
				
				WMUL    r2,r3,r4,r5,r6,r4,r5,r6,r7,r1     ; c:y3:0 = x3:0 * 121666
				WMULX   r6,r7,r8,r9,r10,r8,r9,r10,r12,r1  ; c:y7:4 = x7:4 * 121666 + c

				mov     r1,#38
				mul     r10,r10,r1    ; c *= 38
				adds    r2,r2,r10     ; c:y0 += c
				adcs    r3,r3,#0      ; c:y1 += c
				adcs    r4,r4,#0      ; c:y2 += c
				adcs    r5,r5,#0      ; c:y3 += c
				adcs    r6,r6,#0      ; c:y4 += c
				adcs    r7,r7,#0      ; c:y5 += c
				adcs    r8,r8,#0      ; c:y6 += c
				adcs    r9,r9,#0      ; c:y7 += c

				sbc     r10,r10       ; c - 1
				bic     r1,r10        ; c * 38
				add     r2,r1         ; y0 += c * 38

				stm     r0,{r2-r9}    ; store result
				pop     {r4-r10}
				bx      lr
                ENDP
				

; /* reduction modulo 2^255-19 */
; void fe25519_freeze (fe25519 *r)

crypto_sign_ed25519_ref_fe25519_freeze PROC
				push    {r4-r9}
				ldm     r0,{r3-r9,r12}
				asr     r2,r12,#31
				and     r2,#19
				bic     r12,#0x80000000
				add     r1,r2,#19
				
				adds    r1,r3,r1      ; c:- = a0 + c
				adcs    r1,r4,#0      ; c:- = a1 + c
				adcs    r1,r5,#0      ; c:- = a2 + c
				adcs    r1,r6,#0      ; c:- = a3 + c
				adcs    r1,r7,#0      ; c:- = a4 + c
				adcs    r1,r8,#0      ; c:- = a5 + c
				adcs    r1,r9,#0      ; c:- = a6 + c
				adcs    r1,r12,#0     ; c = a7 + c
				
				asr     r1,r1,#31
				and     r1,#19
				add     r1,r1,r2
				
				adds    r3,r3,r1      ; c:a0 += c
				adcs    r4,r4,#0      ; c:a1 += c
				adcs    r5,r5,#0      ; c:a2 += c
				adcs    r6,r6,#0      ; c:a3 += c
				adcs    r7,r7,#0      ; c:a4 += c
				adcs    r8,r8,#0      ; c:a5 += c
				adcs    r9,r9,#0      ; c:a6 += c
				adc     r12,r12,#0    ; c:a7 += c
				
				bic     r12,#0x80000000
				stm     r0,{r3-r9,r12}
				pop     {r4-r9}
				bx      lr
                ENDP


; /* reduction modulo 2^130-5 */
; void freeze1305(uint32 h[5])

freeze1305      PROC
				push    {r4-r5}
				ldm     r0,{r2-r5,r12} ; h[0..4]
				
				adds    r1,r2,#5       ; h + 5
				adcs    r1,r3,#0
				adcs    r1,r4,#0
				adcs    r1,r5,#0
				adc     r1,r12,#0
				
				lsr     r1,#2          ; r1 = carry = h >= p
				neg     r1,r1          ; h >= p ? -1 : 0
				and     r1,r1,#5       ; h >= p ? 5 : 0
				
				adds    r2,r2,r1       ; h >= p ? h + 5 : h
				adcs    r3,r3,#0
				adcs    r4,r4,#0
				adcs    r5,r5,#0
				adc    r12,r12,#0
				
				and     r12,#3         ; h >= p ? h - p : h
				stm     r0,{r2-r5,r12}
				pop     {r4-r5}
				bx      lr
                ENDP


; void addmulmod1305(uint32 h[5],const uint32 r[4],const uint32 a[5])
; h = (h + a) * r modulo 2^130-5

addmulmod1305   PROC
				push    {r0,r4-r11,lr}
				ldm     r0,{r3-r7}    ; x0 - x4
				ldm     r2,{r8-r12}   ; a0 - a4
				adds    r3,r8         ; x += a
				adcs    r4,r9
				adcs    r5,r10
				adcs    r6,r11
				adc     r7,r12

				ldr     r2,[r1]       ; y0
				WMUL    r8,r9,r10,r11,r12,r3,r4,r5,r6,r2  ; c:p3:0 = x3:0 * y0
				LMULA   r12,r0,r7,r2  ; p5:p4 += x4 * y0 + c
				push    {r8}

				ldr     r2,[r1,#4]    ; y1
				WMULA   r9,r10,r11,r12,r8,r3,r4,r5,r6,r2  ; c:p4:1 += x3:0 * y1
				LMULAC  r0,r8,r7,r2   ; p6:p5 += x4 * y1 + c
				push    {r9}

				ldr     r2,[r1,#8]    ; y2
				WMULA   r10,r11,r12,r0,r9,r3,r4,r5,r6,r2  ; c:p5:2 += x3:0 * y2
				LMULAC  r8,r9,r7,r2   ; p7:p6 += x4 * y2 + c
				push    {r10}

				ldr     r2,[r1,#12]   ; y3
				WMULA   r11,r12,r0,r8,r10,r3,r4,r5,r6,r2  ; c:p6:3 += x3:0 * y3
				LMULAC  r9,r10,r7,r2  ; p8:p7 += x4 * y3 + c

				pop     {r2,r4,r5}    ; p2,p1,p0
				mov     r6,#0x14000   ; 5 * 2^14
				lsr     r7,r12,#16    ; p4 >> 16
				orr     r7,r7,r0,lsl#16 ; | p5 << 16
				LMULA   r5,r1,r7,r6   ; c:p0 += f * 5 * 2^14
				lsr     r7,r0,#16     ; p5 >> 16
				orr     r7,r7,r8,lsl#16 ; | p6 << 16
				LMULAC  r4,r1,r7,r6   ; c:p1 += f * 5 * 2^14 + c
				lsr     r7,r8,#16     ; p6 >> 16
				orr     r7,r7,r9,lsl#16 ; | p7 << 16
				LMULAC  r2,r1,r7,r6   ; c:p2 += f * 5 * 2^14 + c
				lsr     r7,r9,#16     ; p7 >> 16
				orr     r7,r7,r10,lsl#16 ; | p8 << 16
				LMULAC  r11,r1,r7,r6  ; c:p3 += f * 5 * 2^14 + c
				uxth    r12,r12       ; p4 &= 0xFFFF
				add     r12,r1        ; p4 += c

				lsr     r7,r12,#2     ; p4 >> 2
				and     r12,#3        ; p4 &= 3
				add     r7,r7,r7,lsl#2 ; (p4 >> 2) * 5
				adds    r3,r5,r7      ; c:p0 += (p4 >> 2) * 5
				adcs    r4,r4,#0      ; c:p1 += c
				adcs    r5,r2,#0      ; c:p2 += c
				adcs    r6,r11,#0     ; c:p3 += c
				adc     r7,r12,#0     ; -:p4 += c

				pop     {r0}          ; h
				stm     r0,{r3-r7}    ; *h = p
				pop     {r4-r11,pc}
                ENDP


; void salsa20rounds(uint32 x[16])

; Add-Rotate-Xor macro
; a ^= ROT(b + c, s)
				MACRO
				ARX     $a,$b,$c,$s
				adds    r0,$b,$c
				eor     $a,$a,r0,ror#(32-$s)
				MEND
				
; register mapping
; argument:            x0  x1  x2  x3  x4  x5  x6  x7  x8  x9 x10 x11 x12 x13 x14 x15
; primary register:    r1  r2  r6 r10  r2  r3  r4  r5  r6  r7  r8  r9 r10 r11 r12  lr
; secondary register:      s1  s2  s3  s4              s5              s6
				
salsa20rounds   PROC
				IF      UseFpuReg
				  push    {r0,r4-r11,lr}
				  ldm     r0!,{r1}        ; x0
				  vldm    r0!,{s1-s3}     ; x1-x3
				ELSE
				  push    {r4-r11,lr}
				  ldm     r0!,{r1-r4}     ; x0-x3
				  sub     sp,#16
				  push    {r0,r2-r4}      ; &x4,x1-x3
				ENDIF
				ldm     r0,{r2-r12,lr}  ; x4-x15

				mov     r0,#10
loop			
				SAVE    r0,s0,28
				
				ARX     r2,  r1,r10, 7  ;  x4 ^= ROT( x0+x12, 7)
				ARX     r6,  r2, r1, 9  ;  x8 ^= ROT( x4+ x0, 9)
				ARX     r10, r6, r2,13  ; x12 ^= ROT( x8+ x4,13)
				ARX     r1, r10, r6,18  ;  x0 ^= ROT(x12+ x8,18)
				
				DSAVE   r2,r6,s4,s5,16
				SAVE    r10,s6,24
				DLOAD   r2,r6,s1,s2,4
				LOAD    r10,s3,12
				
				ARX     r7,  r3, r2, 7  ;  x9 ^= ROT( x5+ x1, 7)
				ARX     r11, r7, r3, 9  ; x13 ^= ROT( x9+ x5, 9)
				ARX     r2, r11, r7,13  ;  x1 ^= ROT(x13+ x9,13)
				ARX     r3,  r2,r11,18  ;  x5 ^= ROT( x1+x13,18)
				ARX     r12, r8, r4, 7  ; x14 ^= ROT(x10+ x6, 7)
				ARX     r6, r12, r8, 9  ;  x2 ^= ROT(x14+x10, 9)
				ARX     r4,  r6,r12,13  ;  x6 ^= ROT( x2+x14,13)
				ARX     r8,  r4, r6,18  ; x10 ^= ROT( x6+ x2,18)
				ARX     r10, lr, r9, 7  ;  x3 ^= ROT(x15+x11, 7)
				ARX     r5, r10, lr, 9  ;  x7 ^= ROT( x3+x15, 9)
				ARX     r9,  r5,r10,13  ; x11 ^= ROT( x7+ x3,13)
				ARX     lr,  r9, r5,18  ; x15 ^= ROT(x11+ x7,18)
				ARX     r2,  r1,r10, 7  ;  x1 ^= ROT( x0+ x3, 7)
				ARX     r6,  r2, r1, 9  ;  x2 ^= ROT( x1+ x0, 9)
				ARX     r10, r6, r2,13  ;  x3 ^= ROT( x2+ x1,13)
				ARX     r1, r10, r6,18  ;  x0 ^= ROT( x3+ x2,18)
				
				DSAVE   r2,r6,s1,s2,4
				SAVE    r10,s3,12
				DLOAD   r2,r6,s4,s5,16
				LOAD    r10,s6,24
				
				ARX     r4,  r3, r2, 7  ;  x6 ^= ROT( x5+ x4, 7)
				ARX     r5,  r4, r3, 9  ;  x7 ^= ROT( x6+ x5, 9)
				ARX     r2,  r5, r4,13  ;  x4 ^= ROT( x7+ x6,13)
				ARX     r3,  r2, r5,18  ;  x5 ^= ROT( x4+ x7,18)
				ARX     r9,  r8, r7, 7  ; x11 ^= ROT(x10+ x9, 7)
				ARX     r6,  r9, r8, 9  ;  x8 ^= ROT(x11+x10, 9)
				ARX     r7,  r6, r9,13  ;  x9 ^= ROT( x8+x11,13)
				ARX     r8,  r7, r6,18  ; x10 ^= ROT( x9+ x8,18)
				ARX     r10, lr,r12, 7  ; x12 ^= ROT(x15+x14, 7)
				ARX     r11,r10, lr, 9  ; x13 ^= ROT(x12+x15, 9)
				ARX     r12,r11,r10,13  ; x14 ^= ROT(x13+x12,13)
				ARX     lr, r12,r11,18  ; x15 ^= ROT(x14+x13,18)
				
				LOAD    r0,s0,28
				subs    r0,#1
				bne     loop

				pop     {r0}            ; x
				IF      UseFpuReg
				  stm     r0!,{r1}        ; x0
				  vstm    r0!,{s1-s3}     ; x1-x3
				  stm     r0,{r2-r12,lr}  ; x4-x15
				ELSE
				  stm     r0,{r2-r12,lr}  ; x4-x15
				  sub     r0,#16
				  pop     {r2-r4}         ; x1-x3
				  stm     r0,{r1-r4}      ; x0-x3
				  add     sp,#16
				ENDIF
				pop     {r4-r11,pc}
                ENDP
				

; void chacha20rounds(uint32 x[16])

; Add-Xor-Rotate macro
; a += b; c = ROT(c ^ a, s);
				MACRO
				AXR     $a,$b,$c,$s
				adds    $a,$a,$b
				eors    $c,$c,$a
				rors    $c,$c,$s
				MEND
				
; Quarterround macro
				MACRO
				QRR     $a,$b,$c,$d
				AXR     $a,$b,$d,#16
				AXR     $c,$d,$b,#20
				AXR     $a,$b,$d,#24
				AXR     $c,$d,$b,#25
				MEND

; register mapping
; argument:           x0  x1  x2  x3  x4  x5  x6  x7  x8  x9 x10 x11 x12 x13 x14 x15  i
; primary register:   r1  r2  r3  r4  r5  r6  r7  r8  r9 r10  r9 r10  r0 r11 r12  lr  r0
; secondary register:                                 s4  s5  s1  s2  s3              s6
				
chacha20rounds   PROC
				IF      UseFpuReg
				  push    {r0,r4-r11,lr}
				  ldm     r0!,{r1-r10}    ; x0-x9
				  vldm    r0!,{s1-s3}     ; x10-x12
				ELSE
				  push    {r4-r11,lr}
				  ldm     r0!,{r1-r12,lr} ; x0-x12
				  sub     sp,#12
				  push    {r0,r11,r12,lr} ; &x13,x10-x12
				ENDIF
				ldm     r0!,{r11,r12,lr}  ; x13-x15

				mov     r0,#10
loop1			
				SAVE    r0,s6,24
				LOAD    r0,s3,12
				
				QRR     r1, r5, r9, r0    ; x0,x4,x8,x12
				QRR     r2, r6,r10,r11    ; x1,x5,x9,x13
				
				DSAVE   r9,r10,s4,s5,16
				DLOAD   r9,r10,s1,s2,4
				
				QRR     r3, r7, r9,r12    ; x2,x6,x10,x14
				QRR     r4, r8,r10, lr    ; x3,x7,x11,x15
				QRR     r1, r6, r9, lr    ; x0,x5,x10,x15
				QRR     r2, r7,r10, r0    ; x1,x6,x11,x12
				
				DSAVE   r9,r10,s1,s2,4
				DLOAD   r9,r10,s4,s5,16
				
				QRR     r3, r8, r9,r11    ; x2,x7,x8,x13
				QRR     r4, r5,r10,r12    ; x3,x4,x9,x14
				
				SAVE    r0,s3,12
				LOAD    r0,s6,24
				subs    r0,#1
				bne     loop1

				pop     {r0}              ; x
				IF      UseFpuReg
				  stm     r0!,{r1-r10}    ; x0-x9
				  vstm    r0!,{s1-s3}     ; x10-x12
				  stm     r0!,{r11,r12,lr}; x13-x15
				ELSE
				  stm     r0,{r11,r12,lr} ; x13-x15
				  sub     r0,#52
				  pop     {r11,r12,lr}    ; x10-x12
				  stm     r0,{r1-r12,lr}  ; x0-x12
				  add     sp,#12
				ENDIF
				pop     {r4-r11,pc}
                ENDP
				
				
				END
