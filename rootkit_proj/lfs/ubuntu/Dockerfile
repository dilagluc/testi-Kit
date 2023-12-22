FROM amd64/ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y
RUN apt-get -y install systemd-sysv kmod build-essential bison nano util-linux libncurses5-dev \
libncursesw5-dev binutils flex gcc gzip libelf-dev libssl-dev make openssl x11-xkb-utils

COPY bzImage /boot/vmlinuz


RUN echo "root:root" | chpasswd

RUN useradd -rm -d /home/ubuntu -s /bin/bash -u 1001 ubuntu

RUN echo "ubuntu:ubuntu" | chpasswd


COPY rootkit /home/ubuntu/rootkit


