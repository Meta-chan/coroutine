# Welcome to Microprocess (under construction)!
Microprocess is a secure "bubble", in which the code is executed with no influence on main program or other microprocesses. You want to make **millions of coroutines running quasi-parallel**? You are in the right library!

### Features
Microprocesses use no virtual machines, no additional threads or processes, no interpreters and no system calls \- only fair C++ and little assembler. The main three features:
 - Microprocesses can't call insecure functions (otherwise the compilation will fail)
 - Microprocesses can't access memory beyond user space (otherwise they will be destroyed)
 - Microprocesses can't take control over the thread (otherwise they will be suspended)

### Dependencies
The library depends on [Ironic Library](https://github.com/Meta-chan/ironic_liblary) and Visual Studio compiler.

### Platforms
Currently Windows x86 only. In future will be extended to Linux, other architectures are questionable.

### Documentation
You may use [Doxygen](https://www.doxygen.nl/manual/starting.html) to generate documentation.

###### P.S. My code is not dirty, it is alternatively clean.