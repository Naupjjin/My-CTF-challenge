# SLIME MACHINE
> Author: 堇姬Naup
## description
You can create and look VERY VERY VERY GOOD slime!!! PLAY IT!

## writeup
Just enabling NX

A classic heap challenge. In this task, the free function checks if the chunk has been used, so we can't simply perform a double free. However, when looking at the set function, it doesn't check whether the chunk is being used, leading to a use-after-free (UAF) vulnerability.

If we can overwrite the fd of a tcache free chunk to point to a stack location, and then malloc that stack location, I can write arbitrarily to the stack. Since there's a shell function provided, I can overwrite the return address with the shell function's address and jump to it to get a shell.

## flag
> FSCS{Slimes_are_truly_awesome_YOU_CAN_PLAY_NAUP_SLIME_MACHINE}