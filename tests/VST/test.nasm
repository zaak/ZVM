%include "../../vm.inc"

vset r9, 0xdeadbeef
vset r10, 0xdeadbabe
vset r0, 80
vset r1, 100
vst r0, r9
vst r1, r10

voff
