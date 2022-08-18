# tc-trace-ingress-egress

Example of tracing ingress/egress tc messages with trace_printk.

```bash
# Check which interface you want to work with
ip link

# Add classification action qdisc (queueing discipline)
sudo tc qdisc add dev eth0 clsact

# Add direct action (DA) bpf filter on ingress. The section (sec) to execute
# within the bpf object is called "ingress"
sudo tc filter add dev eth0 ingress bpf da obj tc-trace.o sec ingress

# List filters
sudo tc filter show dev eth0 ingress

# Check logs
sudo cat /sys/kernel/debug/tracing/trace_pipe
```
