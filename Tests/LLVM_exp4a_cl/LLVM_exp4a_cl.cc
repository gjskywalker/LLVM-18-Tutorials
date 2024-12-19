#include "LLVM_exp4a_cl.h"

using namespace llvm;

// Define a command-line option
cl::opt<std::string> MyOption("my-option", cl::desc("An example string option"), cl::value_desc("value"));

int main(int argc, char **argv)
{
    // Parse command-line options
    cl::ParseCommandLineOptions(argc, argv, "My LLVM Program\n");

    // Access the option value
    std::cout << "MyOption value: " << MyOption << std::endl;

    return 0;
}