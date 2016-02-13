%include "../../vm.inc"

vset r9, 0xdd
vset r10, 0xee
vset r0, 80
vset r1, 100
vstb r0, r9
vstb r1, r10

voff
