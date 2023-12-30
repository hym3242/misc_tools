# misc_tools
Misc tools i write for personal interesting uses.

- tiocsti.c is to TIOCSTI the tty to remote control them. Use case: forcefully query status bash (or any -icanon process) and optionally print kernel stack if you have the sysctl `kern.tty_info_kstacks` set. Like `stty -f /dev/pts/0 icanon ; ./tioscsti /dev/pts/0 ^T; stty -f /dev/pts/0 -icanon` (^T entered with ^V (stty lnext))
- ceol.c and dceol.c are to color even odd lines. Very useful. very simple. Especially useful for `lsof` output.
