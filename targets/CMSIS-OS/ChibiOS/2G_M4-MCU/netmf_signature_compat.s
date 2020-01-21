    .global  EntryPoint


    .section .netmfstart, "xa", %progbits

    .thumb_func
EntryPoint:

@ The first word has several functions:
@ - It is the entry point of the application
@ - it contains a signature word used to identify application blocks
@ - out of reset it contains the initial stack pointer value
@ - it is the first entry of the initial exception handler table
@ The actual word used is 0x2000E00C

    b       Start         @ 0xE00C
    .byte     0x00        @ Booter signature is 0x2000E00C
    .byte     0x20
    .word     Start         @ Reset
    .word     Fault_Handler @ NMI
    .word     Fault_Handler @ Hard Fault
    .word     Fault_Handler @ MMU Fault
    .word     Fault_Handler @ Bus Fault
    .word     Fault_Handler @ Usage Fault

Start:
        b          _crt0_entry


Fault_Handler:
    b       Fault_Handler


    .end
