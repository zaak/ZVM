%include "../../vm.inc"

vset r9, 0xdd
vset r10, 0xee
vset r11, 0xff
vset r0, 80
vset r1, 81
vset r2, 82
vstb r0, r9
vstb r1, r10
vstb r2, r11
vldb r4, r0
vldb r5, r1
vldb r6, r2

voff
