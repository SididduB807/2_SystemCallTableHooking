#include <stdio.h>
#include <string.h>

// Simulated system calls
void sys_read() {
    printf("Original read: Reading data...\n");
}

void sys_open() {
    printf("Original open: Opening file...\n");
}

// Simulated system call table
void (*sys_call_table[2])() = { sys_read, sys_open };

// Enum to help access syscalls
enum {
    SYS_READ = 0,
    SYS_OPEN = 1
};

// Our "hooked" version of sys_open
void hooked_sys_open() {
    printf("[HOOKED] open: Access denied!\n");
}

// Simulates calling syscalls
void call_syscall(int num) {
    if (num >= 0 && num < 2) {
        sys_call_table[num]();
    } else {
        printf("Invalid syscall number.\n");
    }
}

int main() {
    printf("== Before Hooking ==\n");
    call_syscall(SYS_READ);
    call_syscall(SYS_OPEN);

    // Hooking sys_open
    sys_call_table[SYS_OPEN] = hooked_sys_open;

    printf("\n== After Hooking ==\n");
    call_syscall(SYS_READ);
    call_syscall(SYS_OPEN);

    // Restore original
    sys_call_table[SYS_OPEN] = sys_open;

    printf("\n== After Restoring ==\n");
    call_syscall(SYS_OPEN);

    return 0;
}

