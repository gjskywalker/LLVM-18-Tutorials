#include "llvm/ADT/APInt.h"
#include <iostream>
#include "llvm/ADT/SmallVector.h"

int main()
{
    // Create a 32-bit APInt with value 42
    llvm::APInt myInt(32, 42);

    // Create another 32-bit APInt with value 10
    llvm::APInt anotherInt(32, 10);

    // Perform addition
    llvm::APInt sum = myInt + anotherInt;
    llvm::SmallVector<char, 10> sumStr;
    sum.toString(sumStr, 10, true);
    std::string sumStrStr(sumStr.begin(), sumStr.end());
    std::cout << "Sum: " << sumStrStr << std::endl;

    // Perform subtraction
    llvm::APInt difference = myInt - anotherInt;
    llvm::SmallVector<char, 10> diffStr;
    difference.toString(diffStr, 10, true);
    std::string diffStrStr(diffStr.begin(), diffStr.end());
    std::cout << "Difference: " << diffStrStr << std::endl;

    // Perform multiplication
    llvm::APInt product = myInt * anotherInt;
    llvm::SmallVector<char, 10> prodStr;
    product.toString(prodStr, 10, true);
    std::string prodStrStr(prodStr.begin(), prodStr.end());
    std::cout << "Product: " << prodStrStr << std::endl;

    // Perform division
    llvm::APInt quotient = myInt.sdiv(anotherInt); // Use signed division
    llvm::SmallVector<char, 10> quotStr;
    quotient.toString(quotStr, 10, true);
    std::string quotStrStr(quotStr.begin(), quotStr.end());
    std::cout << "Quotient: " << quotStrStr << std::endl;

    // Perform bitwise AND
    llvm::APInt bitwiseAnd = myInt & anotherInt;
    llvm::SmallVector<char, 10> andStr;
    bitwiseAnd.toString(andStr, 10, true);
    std::string andStrStr(andStr.begin(), andStr.end());
    std::cout << "Bitwise AND: " << andStrStr << std::endl;

    // Perform bitwise OR
    llvm::APInt bitwiseOr = myInt | anotherInt;
    llvm::SmallVector<char, 10> orStr;
    bitwiseOr.toString(orStr, 10, true);
    std::string orStrStr(orStr.begin(), orStr.end());
    std::cout << "Bitwise OR: " << orStrStr << std::endl;

    // Perform bitwise XOR
    llvm::APInt bitwiseXor = myInt ^ anotherInt;
    llvm::SmallVector<char, 10> xorStr;
    bitwiseXor.toString(xorStr, 10, true);
    std::string xorStrStr(xorStr.begin(), xorStr.end());
    std::cout << "Bitwise XOR: " << xorStrStr << std::endl;

    return 0;
}