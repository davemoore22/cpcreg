    .globl _detect_128k

_detect_128k:

    ld   a,#0           ; reset external RAM counter
    ld   b,#0
    call #0xBCCE        ; KL INIT BACK -- returns extra banks in HL

    ld   a,h            ; if HL >= 1, we have at least 1×64K = 128K
    or   l
    jr   nz,has128

    xor  a              ; return 0
    ld   l,a
    ret

has128:
    ld   l,#1           ; return 1
    ret
