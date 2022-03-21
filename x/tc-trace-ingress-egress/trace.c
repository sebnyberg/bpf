#include <linux/bpf.h>
#include <linux/pkt_cls.h>
#include <stdint.h>
#include <iproute2/bpf_elf.h>

/*
Install with:
tc qdisc add dev eth0 clsact
                          direct action       section from file
                                   V                 V
tc filter add dev eth0 ingress bpf da obj tc-trace.o sec ingress
tc filter show dev eth0 ingress
mount | grep bpf
tee /sys/fs/bpf/
*/

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


// static void *BPF_FUNC(map_lookup_elem, void *map, const void *key);

// struct bpf_elf_map acc_map __section("maps") = {
//     .type           = BPF_MAP_TYPE_ARRAY,
//     .size_key       = sizeof(uint32_t),
//     .size_value     = sizeof(uint32_t),
//     .pinning        = PIN_GLOBAL_NS,
//     .max_elem       = 2,
// };

// static __inline int account_data(struct __sk_buff *skb, uint32_t dir)
// {
//     uint32_t *bytes;

//     bytes = map_lookup_elem(&acc_map, &dir);
//     if (bytes)
//             lock_xadd(bytes, skb->len);

//     return TC_ACT_OK;
// }

__section("ingress")
int tc_ingress(struct __sk_buff *skb)
{
    printk("ingress\n");
    return TC_ACT_OK;
    // return account_data(skb, 0);
}

__section("egress")
int tc_egress(struct __sk_buff *skb)
{
    printk("egress\n");
    return TC_ACT_OK;
    // return account_data(skb, 1);
}

char __license[] __section("license") = "GPL";