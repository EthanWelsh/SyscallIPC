SyscallIPC
==========

Solve the producer/consumer problem by modifying the linux kernel and adding syscalls.


Note: In order to prevent weird printing errors caused by buffering in STDOUT, I printed everything to stderror. Therefore when you print this, if you're going to pipe it into a file, you'll need to do something like this:

./prodcons 2 2 1000 2> text.txt