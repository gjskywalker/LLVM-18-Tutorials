# Experiment 4a

Experiment 4a is used to demonstrate how to use CL. In LLVM, `cl` is a namespace used for command-line option parsing. It is part of the LLVM Support Library and provides a way to define and handle command-line options in a structured manner.

> Here is a brief overview of how it works:

* **Define Command-Line Options:** You define command-line options using the `cl::opt` template. These options can be of various types like integers, strings, booleans, etc.
* **Register Options:** The options are registered automatically when they are defined. This is done using static initialization.
* **Parse Command-Line Arguments:** The `cl::ParseCommandLineOptions` function is used to parse the command-line arrguments and populate the defined options.
* **Access Options:** After parsing, you can access the values of the options directly.

This code can be run as follows:

```
OVERVIEW: My LLVM Program

USAGE: LLVM_exp4_cl [options]

OPTIONS:

Color Options:
  --color             - Use colors in output (default=autodetect)

General options:
  --my-option=<value> - An example integer option

Generic Options:
  --help              - Display available options (--help-hidden for more)
  --help-list         - Display list of available options (--help-list-hidden for more)
  --version           - Display the version of this program
```

Example command:

```
./LLVM_exp4_cl --my-option=1
```

