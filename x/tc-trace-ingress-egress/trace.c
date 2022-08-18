#include <linux/bpf.h>
#include <linux/pkt_cls.h>
#include <stdint.h>
#include <iproute2/bpf_elf.h>

#ifndef __section
# define __section(NAME)                  \
  __attribute__((section(NAME), used))
#endif

#ifndef __inline
# define __inline                         \
  inline __attribute__((always_inline))
#endif

#ifndef lock_xadd
# define lock_xadd(ptr, val)              \
  ((void)__sync_fetch_and_add(ptr, val))
#endif

#ifndef BPF_FUNC
# define BPF_FUNC(NAME, ...)              \
  (*NAME)(__VA_ARGS__) = (void *)BPF_FUNC_##NAME
#endif

static void BPF_FUNC(trace_printk, const char *fmt, int fmt_size, ...);

#ifndef printk
# define printk(fmt, ...)                                      \
    ({                                                         \
        char ____fmt[] = fmt;                                  \
        trace_printk(____fmt, sizeof(____fmt), ##__VA_ARGS__); \
    })
#endif

__section("ingress")
int tc_ingress(struct __sk_buff *skb)
{
    printk("ingress");
    return TC_ACT_OK;
}

__section("egress")
int tc_egress(struct __sk_buff *skb)
{
    printk("egress");
    return TC_ACT_OK;
}

char __license[] __section("license") = "GPL";