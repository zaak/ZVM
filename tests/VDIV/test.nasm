%include "../../vm.inc"

vset r0, 2
vset r1, 160
vset r3, 3
vset r4, 1337
vset r5, 0
vset r6, 0x0000ffff
vmul r3, r4
vmul r0, r1
vmul r6, r5

voff
