# HI_SeparateConstOffsetFromGEP

HI_SeparateConstOffsetFromGEP pass is tested by LLVM_exp9_HI_SepConstGEP

The pass is modified from the SeparateConstOffsetFromGEP pass, but in this pass, we lower the GEP considering that in HLS, arrays are not aligned by bytes (like DDR), but elements.

Therefore, we do not need to consider how wide (how many bytes/bits) a element is.