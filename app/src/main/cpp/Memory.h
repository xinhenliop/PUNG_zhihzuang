//
// Created by Administrator on 2020/11/14/014.
//

#ifndef _MEMORY_H
#define _MEMORY_H

#include <sys/syscall.h>
#include <unistd.h>
#include <sys/uio.h>

#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif

ssize_t process_v(pid_t __pid, const struct iovec* __local_iov, unsigned long __local_iov_count,
                  const struct iovec* __remote_iov, unsigned long __remote_iov_count, unsigned long __flags, bool iswrite) {
    return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

bool pvm(int target_pid , void* address, void* buffer, size_t size, bool iswrite) {
    struct iovec local[1];
    struct iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = address;
    remote[0].iov_len = size;

    if (target_pid < 0) {
        return false;
    }

    ssize_t bytes = process_v(target_pid, local, 1, remote, 1, 0, iswrite);
    return bytes == size;
}


#endif //_MEMORY_H
