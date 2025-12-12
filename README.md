# LLVM-18-Tutorial

This blog serves as a updated version of [LLVM-11-Tutorial](https://github.com/zslwyuan/LLVM-11-Tutorials), at which more detailed explanation of this project can be found. In this blog, I mainly record the difference between **LLVM-11** and **LLVM-18**, the specific changes are explained within each experiment folder. I am happy to discuss and any suggestion will be welcome ^\_^ (jgeab@connect.ust.hk). ~If this blog is useful for you, a STAR will be encouragement to me.

## Before Running Experiments

> **Auxiliary File Settings**: _To avoid potential warnings from VS Code, it is recommended to set the configurations in the `c_cpp_properties.json` file as follows:_:

- includePath:
  - "${workspaceFolder}/\*\*"
  - "/usr/local/include/"
- "cStandard": "c17"
- "cppStandard": "c++17"

> **CMake Path**: _The compilation logic can be complex within these folders. Here is an explanation:_

- The pass source codes can be found within the `Implements` folder.
- The specific experiments testing each pass can be found in the `Tests` folder.
- The compiled libraries can be found in `Tests/LLVM_Learner_Libs` and please remember to include the corresponding passes in the CMake file.
- The `App` folder contains the main pass-debugging benchmarks.
- The `HLS_Data_Lib` provides the timing and resource data needed for Light-HLS’s early-stage QoR estimation.
