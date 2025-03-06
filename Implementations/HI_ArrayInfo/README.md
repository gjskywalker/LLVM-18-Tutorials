# Array Information

Since after the hi_separateconstoffsetfromgep pass, the gep instruction will be replaced by several instructions,
we need to find the original gep instruction for the array to get some basic information of the array.
To differ with the HI_ArrayInfo which contains the pragma information, we define a new class ArrayInfo to store the
basic information of the array.