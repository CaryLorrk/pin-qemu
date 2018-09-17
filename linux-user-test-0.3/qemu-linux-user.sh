#!/bin/sh
# QEMU Linux user mode tests
set -e

# set qemu_dir to the directory when qemu was compiled
qemu_dir="../qemu-release"

if test "$1" = "" ; then

# Working architectures (tested on x86 host)
archs="i386 arm armeb sparc sparc32plus ppc ppc64abi32 mips mipsel sh4 sh4eb"

# Almost working 
archs="$archs x86_64"

# Not working architectures. Some of the problems may come from address
# space conflicts between the host and guess.
#archs="$archs alpha ppc64 m68k sparc64"

else
archs="$1"
fi

for arch in $archs ; do 
  arch1=$arch
  prog=""
  case "$arch" in
    sparc32plus)
    arch1="sparc"
  ;;
    ppc64abi32)
    arch1="ppc"
  ;;
    x86_64)
# vsyscalls not supported, so we cannot use gettimeofday, hence no -l
    prog="$arch1/ls dummyfile" 
  ;;
  esac

  qemu="$qemu_dir/$arch-linux-user/qemu-$arch"
  gnemul_dir="./gnemul/qemu-$arch1"
  if test "$prog" = "" ; then 
    prog="$arch1/ls -l dummyfile"
  fi

  echo "[qemu-$arch]"
  echo $qemu -L $gnemul_dir $prog
  $qemu -L $gnemul_dir $prog
done

