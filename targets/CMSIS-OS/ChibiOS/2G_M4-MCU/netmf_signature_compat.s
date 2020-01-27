@
@   This file is used to make nanoCLR compatible with .NET microFramework tinyBooter.
@   The tinybooter checks the signature 0x2000E00C at the beginning of the flash. Hence we have 
@   to make sure, that this is the very first value and then branch to the nanoCLR entry point.
@
@   CSA Engineering AG 2020 (mku)
@

    .global  NETMF_EntryPoint


    .section .netmfstart, "xa", %progbits

    .thumb_func
NETMF_EntryPoint:

@ The first word has several functions:
@ - It is the entry point of the application
@ - it contains a signature word used to identify application blocks
@ - out of reset it contains the initial stack pointer value
@ - it is the first entry of the initial exception handler table
@ The actual word used is 0x2000E00C

    b       NETMF_Start         @ 0xE00C
    .byte     0x00        @ Booter signature is 0x2000E00C
    .byte     0x20
    .word     NETMF_Start         @ Reset
    .word     NETMF_Fault_Handler @ NMI
    .word     NETMF_Fault_Handler @ Hard Fault
    .word     NETMF_Fault_Handler @ MMU Fault
    .word     NETMF_Fault_Handler @ Bus Fault
    .word     NETMF_Fault_Handler @ Usage Fault

NETMF_Start:
    b       _crt0_entry


NETMF_Fault_Handler:
    b       NETMF_Fault_Handler


    .end
