%include "../../vm.inc"

vset r9, 0xdeadbeef
vset r10, 0xdeadbabe
vmov r12, r9
vmov r13, r10

voff
