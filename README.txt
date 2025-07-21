This program is a test to showcase saving arbitrary strings (limited to 1024 characters) into an arena of memory.

No string classes are used.

These functions work with a custom struct, called text, and a memory arena to read and write arbitrary character arrays directly into the arena's memory.

The text struct has two values:
1. an unsigned 64-bit integer that holds the number of characters in the character array
2. a void* that holds the address of the first character in the character array

Full debug information is provided to step through with a debugger to see the strings be written directly into memory.



IMPORTANT!!!

- To compile, I used Visual Studio 2022 Developer Command Prompt v17.14.0 on x64 architecture to compile on the command line.

- Once you're ready to compile, make sure to navigate to the directory containing the source code, then just run build_here.bat by using the Developer Command Prompt.
