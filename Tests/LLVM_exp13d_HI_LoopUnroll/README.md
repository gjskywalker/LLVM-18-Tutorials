This pass is used to support the #unroll pragma and #array partition pragma:

In the application source, you should add label for the loop which you want to unroll
and define the unrolling in the configuration file in the following format:

loop_unroll label=XXXX factor=XXX

But it seems to have some problemes here based on the output latency results.