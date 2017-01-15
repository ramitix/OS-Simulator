# OS-Simulator
The program have two stages of operation, the "sys gen" section, and the "running" section.

During sys gen, the system installer specifies how many devices of each type (printers and disks) are in the system.

The program ask user how much memory the system has. There is only one CPU.

During the running section the system handle system calls issued by the process currently controlling the CPU as well as interrupts that signal various system events.

These calls and interrupts will be indicated by keyboard input. Capital letters will be interrupts, lower case will indicate system calls.

All I/O queues will be FIFO. CPU scheduled using preemptive priority scheduling. All interrupts will be handled "atomically" (one can not interrupt an interrupt handling routine) and will return control to the interrupted process.

An "A" entered on the keyboard indicates the arrival of a process. System asks how much memory this process will need and what is its priority.

Priority is a non-negative integer number and the lower is the number, the higher is the priority.

Allocated memory using "worst-fit" approach. The handling routine should create a PCB for this process, generate a PID, and enqueue the PCB into the Ready Queue.

