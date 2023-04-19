#!/bin/bash

elfloader_path="../app-elfloader/build/app-elfloader_kvm-x86_64"

setup_app()
{
  make -j$(nproc)
}

qemu_root()
{
  setup_app
  qemu-guest -k build/test-symlink_kvm-x86_64 -e fs0
  rm -rf build .config.old
}

qemu_root_debug()
{
  setup_app
  qemu-guest -g 1234 -P -k build/test-symlink_kvm-x86_64 -e fs0
  rm -rf build .config.old
}

static_run()
{
  gcc -static-pie -o test_static main.c
  qemu-guest -m 2048 -k "$elfloader_path" -e fs0/ -i ./test_static
  rm test_static
}

dynamic_run()
{
  gcc -o fs0/test_dynamic main.c
  qemu-guest -m 2048 -k "$elfloader_path" -i /lib64/ld-linux-x86-64.so.2 -e fs0/ -a "--library-path /test_dynamic dummy"
  rm fs0/test_dynamic
}


plain()
{
  gcc -D PLAIN -o test_plain main.c
  ./test_plain
  rm test_plain
}

if test $# -ne 1;
then
  echo "Do not forget to modify the path to the elfloader!"
  echo "Qemu-root run needs musl as a dependency because nolib does not have symlink."
  echo "Usage: $0 <command>" 1>&2
  echo "   command: plain static-run dynamic-run qemu-root qemu-root-debug" 1>&2
  exit 1
fi

command="$1"

case "$command" in

    "qemu-root")
      qemu_root
      ;;

    "qemu-root-debug")
      qemu_root_debug
      ;;

    "plain")
      plain
      ;;

    "static-run")
      static_run
      ;;

    "dynamic-run")
      dynamic_run
      ;;

    *)
        echo "Unknown command"
        exit 1
esac


