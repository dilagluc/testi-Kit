#!/bin/bash

set -e

UID_HOST=$1
GID_HOST=$2
VM_DISK_SIZE_MB=$3

apt-get -y update
apt-get install -y fdisk extlinux qemu-utils
echo -e "[Create disk image]"
[ -z "${VM_DISK_SIZE_MB}" ] && VM_DISK_SIZE_MB=1024
VM_DISK_SIZE_SECTOR=$(expr $VM_DISK_SIZE_MB \* 1024 \* 1024 / 512)
dd if=/dev/zero of=/os/${DISTR}.img bs=${VM_DISK_SIZE_SECTOR} count=512

echo -e "[Make partition, type 83]"
echo "type=83,bootable" | sfdisk /os/${DISTR}.img

echo -e "\n[Format to ext4 partition]"
losetup -D
LOOPDEVICE=$(losetup -f)
echo -e "\n[Using ${LOOPDEVICE} loop device]"
losetup -o $(expr 512 \* 2048) ${LOOPDEVICE} /os/${DISTR}.img
mkfs.ext4 ${LOOPDEVICE}

echo -e "[Copy ${DISTR} docker directory structure to partition]"
mkdir -p /os/mnt
mount -t auto ${LOOPDEVICE} /os/mnt/
cp -a /os/${DISTR}.dir/. /os/mnt/

echo -e "[Setup syslinux]"
extlinux --install /os/mnt/boot/
cp /os/${DISTR}/syslinux.cfg /os/mnt/boot/syslinux.cfg
rm /os/mnt/.dockerenv

echo -e "[Unmount]"
umount /os/mnt
losetup -D

echo -e "[Write syslinux MBR]"
dd if=/usr/lib/syslinux/mbr/mbr.bin of=/os/${DISTR}.img bs=440 count=1 conv=notrunc

echo -e "[Convert to qcow2]"
qemu-img convert -c /os/${DISTR}.img -O qcow2 /os/${DISTR}.qcow2

[ "${UID_HOST}" -a "${GID_HOST}" ] && chown ${UID_HOST}:${GID_HOST} /os/${DISTR}.img /os/${DISTR}.qcow2

rm -r /os/${DISTR}.dir
