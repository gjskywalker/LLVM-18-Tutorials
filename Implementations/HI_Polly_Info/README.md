# HI Polly Info

The Polly_Info pass is mainlyed tested by LLVM_exp4_polly_info

Polly_Info itself do nothing but it shows how to involve the Polly-series Passes in our own pass. Please note that the Passes, which Polly_Info and PollyhedralInfo depend on, should be added in the front in the application (PM.add(XXX))

Detailed explanation can be found in the source code's comments in `llvm-project/polly`.

Please note that the compilation relies on some parameters and arguments and variable from PollyConfig.cmake,
Please refer to the change in CMakeLists.txt, compared to previous experiment
You can just find the "Polly" in the CMakeLists.txt and notice the modification

In the source code, you need to add all the dependent passes into the pass manager; otherwise, you might get runtime errors such as "Pass 'Unnamed pass: implement Pass::getPassName()' is not initialized." Additionally, it is important to double-check the pass objects before running self-developed passes, such as module passes and function passes. If you want to use PollyhedralInfoPass in your work, please remember that it is a function pass.