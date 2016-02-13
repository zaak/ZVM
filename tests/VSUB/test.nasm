%include "../../vm.inc"

vset r0, 0xffff0000
vset r1, 0x00000007
vset r3, 25
vset r4, 301
vsub r4, r3
vsub r0, r1

voff
