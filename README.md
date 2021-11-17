# Vargs

> Alright, it's time to commit code crimes for the greater good!

What if you did not need to pass an initial parameter to your C++ `...` functions? What if `va_start` just worked, magically, inside of your system? This library seeks to answer that by recruiting fairly tame code to read and understand specific ISA and ABI conventions to read variable arguments as serialized by Microsoft Visual C++, GNU Compiler Collection, and LLVM/Clang software for C and C++ for x86_32 ("x86"), x86_64 ("amd64"), ARM ("ARM32") and ARM64 ("ARM64").

We do not expect this library to last into the future in any way, shape, or form and hope it can be taken care of by Alex Gilding's [N2854 - Relax Requirements for Variadic Parameters](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2854.pdf).
