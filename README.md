# YAEP - Yet Another ELF Parser

```      ___           ___           ___           ___     
     |\__\         /\  \         /\  \         /\  \    
     |:|  |       /::\  \       /::\  \       /::\  \   
     |:|  |      /:/\:\  \     /:/\:\  \     /:/\:\  \  
     |:|__|__   /::\~\:\  \   /::\~\:\  \   /::\~\:\  \ 
     /::::\__\ /:/\:\ \:\__\ /:/\:\ \:\__\ /:/\:\ \:\__\
    /:/~~/~    \/__\:\/:/  / \:\~\:\ \/__/ \/__\:\/:/  /
   /:/  /           \::/  /   \:\ \:\__\        \::/  / 
   \/__/            /:/  /     \:\ \/__/         \/__/  
                   /:/  /       \:\__\                  
                   \/__/         \/__/
```

YEAP is Yet Another ELF Parser.
The Executable and Linkable Format (ELF) is the primary binary format used by the Linux operating system (among other Unix based systems) and is a fairly complex file format that provides a great deal of information to the loader about the executable it encapsulates.
Ordinarily the information it contains is entirely non human-readable as it is expressed as concisely as possible in binary form primarily for the convince of the systems binary loader.
The information it contains however can be very useful for developers looking to learn more about the binaries they are compiling as well as reverse engineers and malware analysts seeking to uncover the secrets that a foreign binary may contain.
YEAP like many elf parsers before it decodes the binary headers of the elf file format (including the elf header,  section headers and the program headers) and displays the details contained within in a easily readable and grep-able format.
YEAP was mostly made as a pedagogical exercises to help myself learn more about the internal structure of the ELF binary format but it's output syntax is very verbose and might be more friendly to further text based parsing, if it helps you out let me know! 

# Compilation
To compile simply type the following
```{shell}
$ git clone https://github.com/xchg-rax-rax/YAEP
$ cd YAEP
$ make
```
And if you wish to install the binary just do a `make install`
```{shell}
$ sudo make install
```

# To Do
- Get Symbol table parsing working
- Still some 32 vs 64 inconsistencies
- Complete conversion from C to C++ and make syntax more in like with canonical C++ 20
- Further Testing 
