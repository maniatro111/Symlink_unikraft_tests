qemu-system-x86_64 -cpu host -nographic -enable-kvm -m 6144 -fsdev local,security_model=passthrough,id=hvirtio0,path=fs0/ -device virtio-9p-pci,fsdev=hvirtio0,mount_tag=fs0 -kernel build/test-symlink_kvm-x86_64