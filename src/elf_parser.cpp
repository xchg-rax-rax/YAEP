#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>


// Plan
// ======================================
// open file
// map it into memory
// get Elf header parse and print details
// parse sections and print details
// parse program header and print details
// --------------------------------------
//

void parse_elf_32_header(char* file_image, Elf32_Ehdr* elf_32_header){
    /*
     *    Parse the 32 bit ELF file image provided, print results and return number and offsets
     *    of both sections and program headers.
     */
    printf("ELF File Header\n");
    printf("===============\n");

    // e_dent

    // Magic Number

    printf("Magic Number:              %x %x %x %x", elf_32_header->e_ident[EI_MAG0], 
                                                     elf_32_header->e_ident[EI_MAG1], 
                                                     elf_32_header->e_ident[EI_MAG2], 
                                                     elf_32_header->e_ident[EI_MAG3]);

    if (elf_32_header->e_ident[EI_MAG0] != ELFMAG0 || elf_32_header->e_ident[EI_MAG1] != ELFMAG1 || 
        elf_32_header->e_ident[EI_MAG2] != ELFMAG2 || elf_32_header->e_ident[EI_MAG3] != ELFMAG3) {
        printf(" (Invalid)\n");
    }
    else {
        printf("\n");
    }

    // Binary Architecture
    
    printf("Architecture Class:        ");

    if (elf_32_header->e_ident[EI_CLASS] == ELFCLASS32){
        printf("32 bit\n");
    }
    else if (elf_32_header->e_ident[EI_CLASS] == ELFCLASS64){
        printf("64 bit\n");
    }
    else {
        printf(" Invalid\n");
    }

    // Data Format

    printf("Data Format:               ");

    if (elf_32_header->e_ident[EI_DATA] == ELFDATA2LSB){
        printf("Two's Compliment, Little Endian\n");

    }
    else if (elf_32_header->e_ident[EI_DATA] == ELFDATA2MSB){
        printf("Two's Compliment, Big Endian\n");
    }
    else {
        printf(" Unknown Data Format (Invalid?)\n)");
    }

    // ELF Version
    
    printf("ELF Version:              ");
    if (elf_32_header->e_ident[EI_VERSION] == EV_CURRENT) {
        printf(" Current Version\n");
    }
    else {
        printf(" Invalid\n");
    }

    // Operating System / ABI 
    
    printf("Operating System/ABI:     ");
    switch(elf_32_header->e_ident[EI_OSABI]) {
//        case ELFOSABI_NONE:
        case ELFOSABI_SYSV:
            printf(" Unix System V ABI\n");
            break;
        case ELFOSABI_HPUX:
            printf("HP-UX ABI\n");
            break;
        case ELFOSABI_NETBSD:
            printf("NetBSD ABI\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux ABI\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("Solaris ABI\n");
            break;
        case ELFOSABI_IRIX:
            printf("IRIX ABI\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD ABI\n");
            break;
        case ELFOSABI_TRU64:
            printf("TRU64 Unix ABI\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM Architecture ABI\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Stand-alone (embedded) ABI\n");
            break;
        default:
            printf("Unknown\n");
    }

    // ABI Version

    printf("ABI Version:               %d\n", elf_32_header->e_ident[EI_ABIVERSION]);

    // end of e_ident
     
    // e_type
    
    printf("File Type:                 ");

    switch (elf_32_header->e_type){
        case ET_REL:
            printf("Relocatable File\n");
            break;
        case ET_EXEC:
            printf("Executable File\n");
            break;
        case ET_DYN:
            printf("Shared Object\n");
            break;
        case ET_CORE:
            printf("Core File\n");
            break;
        case ET_NONE:
        default:
            printf("Unknown Type\n");
    }

    // e_machine [If you using some of these I worry which century you are living in...]
    
    printf("Machine:                   ");
    switch (elf_32_header->e_machine) {
        case EM_M32:
            printf("AT&T WE 32100\n");
            break;
        case EM_SPARC:
            printf("Sun Microsystems SPARC\n");
            break;
        case EM_386:
            printf("Intel 80386\n");
            break;
        case EM_68K:
            printf("Motorola 68000\n");
            break;
        case EM_88K:
            printf("Motorola 88000\n");
            break;
        case EM_MIPS:
            printf("MIPS RS3000");
            if (elf_32_header->e_ident[EI_DATA] != ELFDATA2MSB)
                printf(" (Invalid, Big-Endian Only)");
            printf("\n");
            break;
        case EM_PARISC:
            printf("HP/PA\n");
            break;
        case EM_SPARC32PLUS:
            printf("SPARC with Enhanced Instruction Set\n");
            break;
        case EM_PPC:
            printf("PowerPC\n");
            break;
        case EM_PPC64:
            printf("PowerPC 64-bit\n");
            break;
        case EM_S390:
            printf("IBM S/390\n");
            break;
        case EM_ARM:
            printf("Advanced RISC MAchines (ARM)\n");
            break;
        case EM_SH:
            printf("Renesas SuperH\n");
            break;
        case EM_SPARCV9:
            printf("SPARC v9 64-bit\n");
            break;
        case EM_IA_64:
            printf("Intel Itanium\n");
            break;
        case EM_X86_64:
            printf("AMD x86-64\n");
            break;
        case EM_VAX:
            printf("DEC Vax\n");
            break;
        case EM_NONE:
        default:
            printf("Unknown Machine\n");
    } 

    // e_version
   
    printf("File Version:              ");

    if (elf_32_header->e_version == EV_CURRENT){
        printf("Current Version\n");
    }
    else {
        printf("Invalid Version\n");
    }

    // e_flags
    printf("Flags:                     %d\n", elf_32_header->e_flags);

    // e_entry
        
    printf("Entry Point Offset:        ");

    if (elf_32_header->e_entry) {
        printf("%p\n",elf_32_header->e_entry);
    }
    else {
        printf("None\n",elf_32_header->e_entry);
    }

    // e_phoff

    printf("Program Header Offset:     ");
    if (elf_32_header->e_phoff) {
        printf("%p\n",elf_32_header->e_phoff);
    }
    else {
        printf("None\n",elf_32_header->e_phoff);
    }

    // e_shoff

    printf("Section Header Offset:     ");
    if (elf_32_header->e_shoff) {
        printf("%p\n",elf_32_header->e_shoff);
    }
    else {
        printf("None\n",elf_32_header->e_shoff);
    }

    // e_ehsize

    printf("ELF Header Size:           %d bytes\n",elf_32_header->e_ehsize);

    // e_phentsize

    printf("Program Header Size:       %d bytes\n",elf_32_header->e_phentsize);

    // e_phnum

    printf("Number of Program Headers: ",elf_32_header->e_phnum);
    if (elf_32_header->e_phnum != PN_XNUM) {
        printf("%d\n",elf_32_header->e_phnum);
    }
    else {
        printf("%d\n",((Elf32_Shdr*)(file_image+elf_32_header->e_phoff))->sh_info);
    }

    // e_shentsize

    printf("Section Header Size:       %d bytes\n",elf_32_header->e_shentsize);

    // e_shnum

    printf("Number of Section Headers: ",elf_32_header->e_shnum);
    if (elf_32_header->e_shnum != 0) {
        printf("%d\n",elf_32_header->e_shnum);
    }
    else {
        printf("%d\n",((Elf32_Shdr*)(file_image+elf_32_header->e_shoff))->sh_size);
    }

    // e_shstrdx
    
    printf("String Table Index:        ");
    if (elf_32_header->e_shstrndx != SHN_XINDEX) {
        printf("%d\n",elf_32_header->e_shstrndx);
    }
    else {
        printf("%d\n",((Elf32_Shdr*)(file_image+elf_32_header->e_shoff))->sh_link);
    }

    // End of File header
    
    printf("\n");
}

void parse_elf_64_header(char* file_image, Elf64_Ehdr* elf_64_header){
    /*
     *    As 64 bit and 32 bit headers are parse identically we simple call parse_elf_32_header 
     *    casting elf_64_header to a Elf32_Ehdr pointer.
     */
    printf("ELF File Header\n");
    printf("===============\n");

    // e_dent

    // Magic Number

    printf("Magic Number:              %x %x %x %x", elf_64_header->e_ident[EI_MAG0], 
                                                     elf_64_header->e_ident[EI_MAG1], 
                                                     elf_64_header->e_ident[EI_MAG2], 
                                                     elf_64_header->e_ident[EI_MAG3]);

    if (elf_64_header->e_ident[EI_MAG0] != ELFMAG0 || elf_64_header->e_ident[EI_MAG1] != ELFMAG1 || 
        elf_64_header->e_ident[EI_MAG2] != ELFMAG2 || elf_64_header->e_ident[EI_MAG3] != ELFMAG3) {
        printf(" (Invalid)\n");
    }
    else {
        printf("\n");
    }

    // Binary Architecture
    
    printf("Architecture Class:        ");

    if (elf_64_header->e_ident[EI_CLASS] == ELFCLASS32){
        printf("32 bit\n");
    }
    else if (elf_64_header->e_ident[EI_CLASS] == ELFCLASS64){
        printf("64 bit\n");
    }
    else {
        printf(" Invalid\n");
    }

    // Data Format

    printf("Data Format:               ");

    if (elf_64_header->e_ident[EI_DATA] == ELFDATA2LSB){
        printf("Two's Compliment, Little Endian\n");

    }
    else if (elf_64_header->e_ident[EI_DATA] == ELFDATA2MSB){
        printf("Two's Compliment, Big Endian\n");
    }
    else {
        printf(" Unknown Data Format (Invalid?)\n)");
    }

    // ELF Version
    
    printf("ELF Version:              ");
    if (elf_64_header->e_ident[EI_VERSION] == EV_CURRENT) {
        printf(" Current Version\n");
    }
    else {
        printf(" Invalid\n");
    }

    // Operating System / ABI 
    
    printf("Operating System/ABI:     ");
    switch(elf_64_header->e_ident[EI_OSABI]) {
//        case ELFOSABI_NONE:
        case ELFOSABI_SYSV:
            printf(" Unix System V ABI\n");
            break;
        case ELFOSABI_HPUX:
            printf("HP-UX ABI\n");
            break;
        case ELFOSABI_NETBSD:
            printf("NetBSD ABI\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux ABI\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("Solaris ABI\n");
            break;
        case ELFOSABI_IRIX:
            printf("IRIX ABI\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD ABI\n");
            break;
        case ELFOSABI_TRU64:
            printf("TRU64 Unix ABI\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM Architecture ABI\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Stand-alone (embedded) ABI\n");
            break;
        default:
            printf("Unknown\n");
    }

    // ABI Version

    printf("ABI Version:               %d\n", elf_64_header->e_ident[EI_ABIVERSION]);

    // end of e_ident
     
    // e_type
    
    printf("File Type:                 ");

    switch (elf_64_header->e_type){
        case ET_REL:
            printf("Relocatable File\n");
            break;
        case ET_EXEC:
            printf("Executable File\n");
            break;
        case ET_DYN:
            printf("Shared Object\n");
            break;
        case ET_CORE:
            printf("Core File\n");
            break;
        case ET_NONE:
        default:
            printf("Unknown Type\n");
    }

    // e_machine [If you using some of these I worry which century you are living in...]
    
    printf("Machine:                   ");
    switch (elf_64_header->e_machine) {
        case EM_M32:
            printf("AT&T WE 32100\n");
            break;
        case EM_SPARC:
            printf("Sun Microsystems SPARC\n");
            break;
        case EM_386:
            printf("Intel 80386\n");
            break;
        case EM_68K:
            printf("Motorola 68000\n");
            break;
        case EM_88K:
            printf("Motorola 88000\n");
            break;
        case EM_MIPS:
            printf("MIPS RS3000");
            if (elf_64_header->e_ident[EI_DATA] != ELFDATA2MSB)
                printf(" (Invalid, Big-Endian Only)");
            printf("\n");
            break;
        case EM_PARISC:
            printf("HP/PA\n");
            break;
        case EM_SPARC32PLUS:
            printf("SPARC with Enhanced Instruction Set\n");
            break;
        case EM_PPC:
            printf("PowerPC\n");
            break;
        case EM_PPC64:
            printf("PowerPC 64-bit\n");
            break;
        case EM_S390:
            printf("IBM S/390\n");
            break;
        case EM_ARM:
            printf("Advanced RISC MAchines (ARM)\n");
            break;
        case EM_SH:
            printf("Renesas SuperH\n");
            break;
        case EM_SPARCV9:
            printf("SPARC v9 64-bit\n");
            break;
        case EM_IA_64:
            printf("Intel Itanium\n");
            break;
        case EM_X86_64:
            printf("AMD x86-64\n");
            break;
        case EM_VAX:
            printf("DEC Vax\n");
            break;
        case EM_NONE:
        default:
            printf("Unknown Machine\n");
    } 

    // e_version
   
    printf("File Version:              ");

    if (elf_64_header->e_version == EV_CURRENT){
        printf("Current Version\n");
    }
    else {
        printf("Invalid Version\n");
    }

    // e_flags
    printf("Flags:                     %d\n", elf_64_header->e_flags);

    // e_entry
        
    printf("Entry Point Offset:        ");

    if (elf_64_header->e_entry) {
        printf("%p\n",elf_64_header->e_entry);
    }
    else {
        printf("None\n",elf_64_header->e_entry);
    }

    // e_phoff

    printf("Program Header Offset:     ");
    if (elf_64_header->e_phoff) {
        printf("%p\n",elf_64_header->e_phoff);
    }
    else {
        printf("None\n",elf_64_header->e_phoff);
    }

    // e_shoff

    printf("Section Header Offset:     ");
    if (elf_64_header->e_shoff) {
        printf("%p\n",elf_64_header->e_shoff);
    }
    else {
        printf("None\n",elf_64_header->e_shoff);
    }

    // e_ehsize

    printf("ELF Header Size:           %d bytes\n",elf_64_header->e_ehsize);

    // e_phentsize

    printf("Program Header Size:       %d bytes\n",elf_64_header->e_phentsize);

    // e_phnum

    printf("Number of Program Headers: ",elf_64_header->e_phnum);
    if (elf_64_header->e_phnum != PN_XNUM) {
        printf("%d\n",elf_64_header->e_phnum);
    }
    else {
        printf("%d\n",((Elf64_Shdr*)(file_image+elf_64_header->e_phoff))->sh_info);
    }

    // e_shentsize

    printf("Section Header Size:       %d bytes\n",elf_64_header->e_shentsize);

    // e_shnum

    printf("Number of Section Headers: ",elf_64_header->e_shnum);
    if (elf_64_header->e_shnum != 0) {
        printf("%d\n",elf_64_header->e_shnum);
    }
    else {
        printf("%d\n",((Elf64_Shdr*)(file_image+elf_64_header->e_shoff))->sh_size);
    }

    // e_shstrdx
    
    printf("String Table Index:        ");
    if (elf_64_header->e_shstrndx != SHN_XINDEX) {
        printf("%d\n",elf_64_header->e_shstrndx);
    }
    else {
        printf("%d\n",((Elf64_Shdr*)(file_image+elf_64_header->e_shoff))->sh_link);
    }

    // End of File header
    printf("\n");
}

void parse_program_header_32(char* file_image, Elf32_Ehdr* elf_32_header, int index) {
    /* 
     *    Parse a 32 bit program header and print the result.
     */

    if (index >= elf_32_header->e_phnum) {
        printf("[!] Fatal Error. Cannot read program header %d, only %d exist.", 
                index+1, elf_32_header->e_phnum);
        exit(-1);
    }

    // get program header @ index
    Elf32_Phdr* program_header_32 = (Elf32_Phdr*) (file_image + elf_32_header->e_phoff 
                                                    + (elf_32_header->e_phentsize * index));

    // parse program header

    printf("Program Header %i\n", index+1);
    printf("----------------------\n");
    
    printf("Header Type:              ");
    switch (program_header_32->p_type) {
        case PT_NULL:
            printf("Unused\n");
            break;
        case PT_LOAD:
            printf("Loadable Segment\n");
            break;
        case PT_DYNAMIC:
            printf("Dynamic Linking Information\n");
            break;
        case PT_INTERP:
            printf("Interpreter Information\n");
            break;
        case PT_NOTE:
            printf("Auxiliary Information\n");
            break;
        case PT_SHLIB:
            printf("Reserved (Invalid)\n");
            break;
        case PT_PHDR:
            printf("Program Header Table\n");
            break;
        case PT_TLS:
            printf("Thread Local Storage\n");
            break;
        case PT_NUM:
            printf("Number of defined Types\n");
            break;
        case PT_GNU_EH_FRAME:
            printf("GCC .eh_frame_hdr\n");
            break;
        case PT_GNU_STACK:
            printf("Stack Executable\n");
            break;
        case PT_GNU_RELRO:
            printf("Read-Only After Relocation\n");
            break;
        case PT_GNU_PROPERTY:
            printf("GNU property\n");
            break;
        case PT_SUNWBSS:
            printf("Sun Microsystems Specific\n");
            break;
        case PT_SUNWSTACK:
            printf("Sun Microsystems Stack\n");
            break;
        default:
            if (PT_LOOS <= program_header_32->p_type && program_header_32->p_type <= PT_HIOS)
                printf("OS Specific\n");
            else if (PT_LOPROC <= program_header_32->p_type && program_header_32->p_type <= PT_HIPROC)
                printf("Processor Specific\n");
            else if (PT_LOSUNW<= program_header_32->p_type && program_header_32->p_type <= PT_HISUNW)
                printf("Sun Microsystems Specific\n");
            else
                printf("Unknown (Invalid)\n");
    }
    
    // p_offset
    
    printf("Segment File Offset:      0x%x\n", program_header_32->p_offset);

    // p_vaddr

    printf("Segment Virtual Address:  0x%x\n", program_header_32->p_vaddr);


    // p_paddr

    printf("Segment Physical Address: 0x%x\n", program_header_32->p_paddr);
    

    // p_filesz
    
    printf("Segment Size on Disk:     0x%x\n", program_header_32->p_filesz);

    // p_memsz
    
    printf("Segment Size in Memory:   0x%x\n", program_header_32->p_memsz);

    // p_align
    
    printf("Segment Alignment:        ");
    if (program_header_32->p_align == 0 || program_header_32->p_align == 1) {
        printf("None Required\n");
    }
    else {
        printf("0x%x\n", program_header_32->p_align);
    }

    // p_flags
    
    printf("Flags:                    ");
    if (program_header_32->p_flags & PF_R){
        printf("R");
    }
    else {
        printf(" ");
    }
    if (program_header_32->p_flags & PF_W){
        printf("W");
    }
    else {
        printf(" ");
    }
    if (program_header_32->p_flags & PF_X){
        printf("X");
    }
    else {
        printf(" ");
    }
    printf("\n\n");
}
void parse_program_header_64(char* file_image, Elf64_Ehdr* elf_64_header, int index) {
    /* 
     *    Parse a 64 bit program header and print the result.
     */

    if (index >= elf_64_header->e_phnum) {
        printf("[!] Fatal Error. Cannot read program header %d, only %d exist.", 
                index+1, elf_64_header->e_phnum);
        exit(-1);
    }

    // get program header @ index
    Elf64_Phdr* program_header_64 = (Elf64_Phdr*) (file_image + elf_64_header->e_phoff 
                                                    + (elf_64_header->e_phentsize * index));

    // parse program header

    printf("Program Header %i\n", index+1);
    printf("----------------------\n");
    
    printf("Header Type:              ");
    switch (program_header_64->p_type) {
        case PT_NULL:
            printf("Unused\n");
            break;
        case PT_LOAD:
            printf("Loadable Segment\n");
            break;
        case PT_DYNAMIC:
            printf("Dynamic Linking Information\n");
            break;
        case PT_INTERP:
            printf("Interpreter Information\n");
            break;
        case PT_NOTE:
            printf("Auxiliary Information\n");
            break;
        case PT_SHLIB:
            printf("Reserved (Invalid)\n");
            break;
        case PT_PHDR:
            printf("Program Header Table\n");
            break;
        case PT_TLS:
            printf("Thread Local Storage\n");
            break;
        case PT_NUM:
            printf("Number of defined Types\n");
            break;
        case PT_GNU_EH_FRAME:
            printf("GCC .eh_frame_hdr\n");
            break;
        case PT_GNU_STACK:
            printf("Stack Executable\n");
            break;
        case PT_GNU_RELRO:
            printf("Read-Only After Relocation\n");
            break;
        case PT_GNU_PROPERTY:
            printf("GNU property\n");
            break;
        case PT_SUNWBSS:
            printf("Sun Microsystems Specific\n");
            break;
        case PT_SUNWSTACK:
            printf("Sun Microsystems Stack\n");
            break;
        default:
            if (PT_LOOS <= program_header_64->p_type && program_header_64->p_type <= PT_HIOS)
                printf("OS Specific\n");
            else if (PT_LOPROC <= program_header_64->p_type && program_header_64->p_type <= PT_HIPROC)
                printf("Processor Specific\n");
            else if (PT_LOSUNW<= program_header_64->p_type && program_header_64->p_type <= PT_HISUNW)
                printf("Sun Microsystems Specific\n");
            else
                printf("Unknown (Invalid)\n");
    }
    
    // p_offset
    
    printf("Segment File Offset:      0x%x\n", program_header_64->p_offset);

    // p_vaddr

    printf("Segment Virtual Address:  0x%x\n", program_header_64->p_vaddr);


    // p_paddr

    printf("Segment Physical Address: 0x%x\n", program_header_64->p_paddr);
    

    // p_filesz
    
    printf("Segment Size on Disk:     0x%x\n", program_header_64->p_filesz);

    // p_memsz
    
    printf("Segment Size in Memory:   0x%x\n", program_header_64->p_memsz);

    // p_align
    
    printf("Segment Alignment:        ");
    if (program_header_64->p_align == 0 || program_header_64->p_align == 1) {
        printf("None Required\n");
    }
    else {
        printf("0x%x\n", program_header_64->p_align);
    }

    // p_flags
    
    printf("Flags:                    ");
    if (program_header_64->p_flags & PF_R){
        printf("R");
    }
    else {
        printf(" ");
    }
    if (program_header_64->p_flags & PF_W){
        printf("W");
    }
    else {
        printf(" ");
    }
    if (program_header_64->p_flags & PF_X){
        printf("X");
    }
    else {
        printf(" ");
    }
    printf("\n\n");

}

char* get_section_name_32(char* file_image, Elf32_Ehdr* elf_32_header, int index) {
    /*
     *    Get a pointer to the null terminated section name string associated 
     *    with the supplied index.
     */
    uint16_t section_name_header_32_index;
    Elf32_Shdr* section_name_header_32; 
    Elf32_Shdr* inital_section_header_32;
    Elf32_Sym*  name_symbol_table_entry_32;
    
    if (elf_32_header->e_shstrndx == SHN_UNDEF) {
        printf("[!] Attempting to get reference to section name entry but none exists.\n");
        exit(-1);
    }
    else if (elf_32_header->e_shstrndx == SHN_XINDEX) {
        inital_section_header_32 = (Elf32_Shdr*) (file_image + elf_32_header->e_shoff);
        section_name_header_32_index = inital_section_header_32->sh_link;
    }
    else{
        section_name_header_32_index = elf_32_header->e_shstrndx;
    }

    section_name_header_32 = (Elf32_Shdr*) (file_image + elf_32_header->e_shoff 
                                    + (elf_32_header->e_shentsize * section_name_header_32_index));
    name_symbol_table_entry_32 = (Elf32_Sym*) (file_image + section_name_header_32->sh_offset + (section_name_header_32->sh_entsize * index));

    return file_image + name_symbol_table_entry_32->st_value;
}

void parse_section_header_32(char* file_image, Elf32_Ehdr* elf_32_header, int index) {
    /* 
     *    Parse a 32 bit section header and print the result.
     */
    // Deal with reserved indices here
    
    printf("Section Header %d\n", index);
    printf("-----------------------\n");

    // Resolve Index to pointer
    
    Elf32_Shdr* section_header_32 = (Elf32_Shdr*) (file_image + elf_32_header->e_shoff 
                                                + (elf_32_header->e_shentsize * index));

    // sh_name
    //printf("Section Name:      %s", get_section_name_32(file_image,elf_32_header, 
    //                                                    section_header_32->sh_name));
    // Need to resolve name via the string table section header entry
    //printf("Section Name: %s",file_image+elf_32_header->e_b):
    
    // sh_type
    printf("Section Type:      ");
    switch(section_header_32->sh_type){
        case SHT_NULL:
            printf("Inactive\n");
            break;
        case SHT_PROGBITS:
            printf("Program Data\n");
            break;
        case SHT_SYMTAB:
            printf("Symbol Table\n");
            break;
        case SHT_STRTAB: printf("String Table\n"); break; case SHT_RELA:
            printf("Relocation Entries with Explicit Addends\n");
            break;
        case SHT_HASH:
            printf("Symbol Hash Table\n");
            break;
        case SHT_DYNAMIC:
            printf("Dynamic Linking Information\n");
            break;
        case SHT_NOTE:
            printf("Note\n");
            break;
        case SHT_NOBITS:
            printf("Program Space with no data (bss)\n");
            break;
        case SHT_REL:
            printf("Relocation Entries, No Addends\n");
            break;
        case SHT_SHLIB:
            printf("Reserved\n");
            break;
        case SHT_DYNSYM:
            printf("Dynamic Linker Symbol Table\n");
            break;
        case SHT_INIT_ARRAY:
            printf("Array of Constructors\n");
            break;
        case SHT_FINI_ARRAY:
            printf("Array of Destructors\n");
            break;
        case SHT_PREINIT_ARRAY:
            printf("Array of  Pre-Constructors\n");
            break;
        case SHT_GROUP:
            printf("Section Group\n");
            break;
        case SHT_SYMTAB_SHNDX:
            printf("Extended Section Indices\n");
            break;
        case SHT_NUM:
            printf("Number of Defined Types\n");
            break;
        case SHT_GNU_ATTRIBUTES:
            printf("Object Attributes\n");
            break;
        case SHT_GNU_HASH:
            printf("GNU-Style Hash Table\n");
            break;
        case SHT_GNU_LIBLIST:
            printf("Pre-Link Library List\n");
            break;
        case SHT_CHECKSUM:
            printf("Checksum for DSO Content\n");
            break;
        case SHT_SUNW_move:
            printf("Sun Microsystems 'move'\n");
            break;
        case SHT_SUNW_COMDAT:
            printf("Sun Microsystems COMDAT\n");
            break;
        case SHT_SUNW_syminfo:
            printf("Sun Microsystems 'syminfo'\n");
            break;
        case SHT_GNU_verdef:
            printf("Version Definition Section\n");
            break;
        case SHT_GNU_verneed:
            printf("Version Needs Section\n");
            break;
        case SHT_GNU_versym:
            printf("Version Symbol Table\n");
            break;
        default:
            if (SHT_LOSUNW <= section_header_32->sh_type && section_header_32->sh_type <= SHT_HISUNW)  {
                printf("Sun Specific Section (Unknown)\n");
            }
            else if (SHT_LOOS <= section_header_32->sh_type && section_header_32->sh_type <= SHT_HIOS) {
                printf("OS Specific Section (Unknown)\n");
            }
            else if (SHT_LOPROC <= section_header_32->sh_type && section_header_32->sh_type <= SHT_HIPROC) {
                printf("Processor Specific Section (Unknown)\n");
            }
            else if (SHT_LOUSER <= section_header_32->sh_type && section_header_32->sh_type <= SHT_HIUSER) {
                printf("Application Specific Section (Unknown)\n");
            }
            else {
                printf("Unknown (0x%x)\n", section_header_32->sh_type);
            }
    }

    // sh_flags
    //
    printf("Flags:             \n");
    if (section_header_32->sh_flags & SHF_WRITE)
        printf("\tWRITE\n");
    if (section_header_32->sh_flags & SHF_ALLOC)
        printf("\tALLOC\n");
    if (section_header_32->sh_flags & SHF_EXECINSTR)
        printf("\tEXECINSTR\n");
    if (section_header_32->sh_flags & SHF_MERGE)
        printf("\tMASKPROC\n");
    if (section_header_32->sh_flags & SHF_STRINGS)
        printf("\tSTRINGS\n");
    if (section_header_32->sh_flags & SHF_INFO_LINK)
        printf("\tINFO_LINK\n");
    if (section_header_32->sh_flags & SHF_LINK_ORDER)
        printf("\tLINK_ORDERn\n");
    if (section_header_32->sh_flags & SHF_OS_NONCONFORMING)
        printf("\tOS_NONCONFORMING\n");
    if (section_header_32->sh_flags & SHF_GROUP)
        printf("\tSHF_GROUP\n");
    if (section_header_32->sh_flags & SHF_TLS)
        printf("\tTLS\n");
    if (section_header_32->sh_flags & SHF_COMPRESSED)
        printf("\tCOMPRESSED\n");
    if (section_header_32->sh_flags & SHF_MASKOS)
        printf("\tMASKOS\n");
    if (section_header_32->sh_flags & SHF_MASKPROC)
        printf("\tMASKPROC\n");
    if (section_header_32->sh_flags & SHF_GNU_RETAIN)
        printf("\tGNU_RETAIN\n");
    if (section_header_32->sh_flags & SHF_ORDERED)
        printf("\tORDERED\n");
    if (section_header_32->sh_flags & SHF_EXCLUDE)
        printf("\tEXCLUDE\n");
    if (!section_header_32->sh_flags)
        printf("\t(None)\n");

    // sh_addr
    
    printf("Virtual Address:   %p\n", section_header_32->sh_addr);
    
    // sh_offset

    printf("File Offset:       0x%x\n", section_header_32->sh_offset);

    // sh_size

    printf("Size of Section:   %d bytes\n", section_header_32->sh_size);

    // sh_link 
    
    printf("Link Index:        0x%x\n", section_header_32->sh_link);

    // sh_info

    printf("Info:              0x%x\n");

    // sh_addralign
    
    printf("Address Alignment: ");
    if (section_header_32->sh_addralign == 0 || section_header_32->sh_addralign == 1){
        printf("None\n");
    }
    else {
        printf("0x%x\n", section_header_32->sh_addralign);
    }

    // sh_entsize

    printf("Entry Size:        %d bytes",section_header_32->sh_entsize);
    
    // end of section header
    
    printf("\n\n");
}

void parse_section_header_64(char* file_image, Elf64_Ehdr* elf_64_header, int index) {
    /* 
     *    Parse a 64 bit section header and print the result.
     */
    // Deal with reserved indices here
    
    printf("Section Header %d\n", index);
    printf("-----------------------\n");

    // Resolve Index to pointer
    
    Elf64_Shdr* section_header_64 = (Elf64_Shdr*) (file_image + elf_64_header->e_shoff 
                                                + (elf_64_header->e_shentsize * index));

    // sh_name
    // Need to resolve name via the string table section header entry
    //printf("Section Name: %s",file_image+elf_64_header->e_b):
    
    // sh_type
    printf("Section Type:      ");
    switch(section_header_64->sh_type){
        case SHT_NULL:
            printf("Inactive\n");
            break;
        case SHT_PROGBITS:
            printf("Program Data\n");
            break;
        case SHT_SYMTAB:
            printf("Symbol Table\n");
            break;
        case SHT_STRTAB: printf("String Table\n"); break; case SHT_RELA:
            printf("Relocation Entries with Explicit Addends\n");
            break;
        case SHT_HASH:
            printf("Symbol Hash Table\n");
            break;
        case SHT_DYNAMIC:
            printf("Dynamic Linking Information\n");
            break;
        case SHT_NOTE:
            printf("Note\n");
            break;
        case SHT_NOBITS:
            printf("Program Space with no data (bss)\n");
            break;
        case SHT_REL:
            printf("Relocation Entries, No Addends\n");
            break;
        case SHT_SHLIB:
            printf("Reserved\n");
            break;
        case SHT_DYNSYM:
            printf("Dynamic Linker Symbol Table\n");
            break;
        case SHT_INIT_ARRAY:
            printf("Array of Constructors\n");
            break;
        case SHT_FINI_ARRAY:
            printf("Array of Destructors\n");
            break;
        case SHT_PREINIT_ARRAY:
            printf("Array of  Pre-Constructors\n");
            break;
        case SHT_GROUP:
            printf("Section Group\n");
            break;
        case SHT_SYMTAB_SHNDX:
            printf("Extended Section Indices\n");
            break;
        case SHT_NUM:
            printf("Number of Defined Types\n");
            break;
        case SHT_GNU_ATTRIBUTES:
            printf("Object Attributes\n");
            break;
        case SHT_GNU_HASH:
            printf("GNU-Style Hash Table\n");
            break;
        case SHT_GNU_LIBLIST:
            printf("Pre-Link Library List\n");
            break;
        case SHT_CHECKSUM:
            printf("Checksum for DSO Content\n");
            break;
        case SHT_SUNW_move:
            printf("Sun Microsystems 'move'\n");
            break;
        case SHT_SUNW_COMDAT:
            printf("Sun Microsystems COMDAT\n");
            break;
        case SHT_SUNW_syminfo:
            printf("Sun Microsystems 'syminfo'\n");
            break;
        case SHT_GNU_verdef:
            printf("Version Definition Section\n");
            break;
        case SHT_GNU_verneed:
            printf("Version Needs Section\n");
            break;
        case SHT_GNU_versym:
            printf("Version Symbol Table\n");
            break;
        default:
            if (SHT_LOSUNW <= section_header_64->sh_type && section_header_64->sh_type <= SHT_HISUNW)  {
                printf("Sun Specific Section (Unknown)\n");
            }
            else if (SHT_LOOS <= section_header_64->sh_type && section_header_64->sh_type <= SHT_HIOS) {
                printf("OS Specific Section (Unknown)\n");
            }
            else if (SHT_LOPROC <= section_header_64->sh_type && section_header_64->sh_type <= SHT_HIPROC) {
                printf("Processor Specific Section (Unknown)\n");
            }
            else if (SHT_LOUSER <= section_header_64->sh_type && section_header_64->sh_type <= SHT_HIUSER) {
                printf("Application Specific Section (Unknown)\n");
            }
            else {
                printf("Unknown (0x%x)\n", section_header_64->sh_type);
            }
    }

    // sh_flags
    //
    printf("Flags:             \n");
    if (section_header_64->sh_flags & SHF_WRITE)
        printf("\tWRITE\n");
    if (section_header_64->sh_flags & SHF_ALLOC)
        printf("\tALLOC\n");
    if (section_header_64->sh_flags & SHF_EXECINSTR)
        printf("\tEXECINSTR\n");
    if (section_header_64->sh_flags & SHF_MERGE)
        printf("\tMASKPROC\n");
    if (section_header_64->sh_flags & SHF_STRINGS)
        printf("\tSTRINGS\n");
    if (section_header_64->sh_flags & SHF_INFO_LINK)
        printf("\tINFO_LINK\n");
    if (section_header_64->sh_flags & SHF_LINK_ORDER)
        printf("\tLINK_ORDERn\n");
    if (section_header_64->sh_flags & SHF_OS_NONCONFORMING)
        printf("\tOS_NONCONFORMING\n");
    if (section_header_64->sh_flags & SHF_GROUP)
        printf("\tSHF_GROUP\n");
    if (section_header_64->sh_flags & SHF_TLS)
        printf("\tTLS\n");
    if (section_header_64->sh_flags & SHF_COMPRESSED)
        printf("\tCOMPRESSED\n");
    if (section_header_64->sh_flags & SHF_MASKOS)
        printf("\tMASKOS\n");
    if (section_header_64->sh_flags & SHF_MASKPROC)
        printf("\tMASKPROC\n");
    if (section_header_64->sh_flags & SHF_GNU_RETAIN)
        printf("\tGNU_RETAIN\n");
    if (section_header_64->sh_flags & SHF_ORDERED)
        printf("\tORDERED\n");
    if (section_header_64->sh_flags & SHF_EXCLUDE)
        printf("\tEXCLUDE\n");
    if (!section_header_64->sh_flags)
        printf("\t(None)\n");

    // sh_addr
    
    printf("Virtual Address:   %p\n", section_header_64->sh_addr);
    
    // sh_offset

    printf("File Offset:       0x%x\n", section_header_64->sh_offset);

    // sh_size

    printf("Size of Section:   %d bytes\n", section_header_64->sh_size);

    // sh_link 
    
    printf("Link Index:        0x%x\n", section_header_64->sh_link);

    // sh_info

    printf("Info:              0x%x\n");

    // sh_addralign
    
    printf("Address Alignment: ");
    if (section_header_64->sh_addralign == 0 || section_header_64->sh_addralign == 1){
        printf("None\n");
    }
    else {
        printf("0x%x\n", section_header_64->sh_addralign);
    }

    // sh_entsize

    printf("Entry Size:        %d bytes",section_header_64->sh_entsize);
    
    // end of section header
    
    printf("\n\n");
}


char* load_file_image(char* file_name){
    /*
     *    Opens the file to parse, maps it into the process virtual address spaces and returns 
     *    a pointer.
     */
    int fd;
    struct stat file_stat;
    char* file_image;
    //printf("[*] Opening file %s\n",file_name);
    fd = open(file_name, O_RDONLY); 
    //printf("[*] Opened file %s with file descriptor %d\n",file_name, fd);
    fstat(fd, &file_stat);
    //printf("[*] Got file stats. File is of size %d bytes\n", file_stat.st_size);
    file_image = (char*) mmap(0, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    //printf("[*] Mapped file into memory at address %p\n", file_image);
    close(fd);
    return file_image;
}

int main(int argc, char** argv) {
    int i;
    char* file_name;
    char* file_image;
    Elf32_Ehdr* elf_32_header;
    Elf64_Ehdr* elf_64_header;

    if (argc != 2) {
        printf("[!] Improper arguments\n");
        printf("Usage: yaep <filename>\n");
        return -1;
    }
    
    // Add a pretty vanity banner here
   
    // Load file
    
    file_name = argv[1];
    if(!(file_image = load_file_image(file_name))) {
        printf("[!] Could not load file %s\n", file_name);
        return -1;
    }


    if (file_image[4] == 0x01) {
        // get program header
        elf_32_header = (Elf32_Ehdr*) file_image;
        // Parse as a 32 bit ELF
        parse_elf_32_header(file_image, elf_32_header);
        // Parse Program Headers (if any)
        printf("Program Headers\n");
        printf("===============\n\n");
        for (i = 0; i < elf_32_header->e_phnum; i++)
            parse_program_header_32(file_image, elf_32_header, i);

        // Parse Section Headers (if any)
        printf("Section Headers\n");
        printf("===============\n\n");
        for (i = 0; i < elf_32_header->e_shnum; i++)
            parse_section_header_32(file_image, elf_32_header, i);
    }
    else if(file_image[4] == 0x02) {
        // get elf header
        elf_64_header = (Elf64_Ehdr*) file_image;
        // Parse as a 64 bit ELF
        parse_elf_64_header(file_image, elf_64_header);
        // Parse Program Headers (if any)
        printf("Program Headers\n");
        printf("===============\n\n");
        for (i = 0; i < elf_64_header->e_phnum; i++)
            parse_program_header_64(file_image, elf_64_header, i);

        // Parse Section Headers (if any)
        printf("Section Headers\n");
        printf("===============\n\n");
        for (i = 0; i < elf_64_header->e_shnum; i++)
            parse_section_header_64(file_image, elf_64_header, i);
    }
    else {
        printf("[!] Invalid Architecture, Cannot Parse\n");
        return -1;
    }
}
