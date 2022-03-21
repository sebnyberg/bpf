#!/usr/bin/env bash
#
# Various epbf commands
#

bpftrace -e 'tracepoint:syscalls:sys_enter_openat { printf("%s %s\n", comm, str(args->filename)); }'

