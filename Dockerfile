FROM ubuntu:latest
LABEL MAINTAINER Tiago Koji Castro Shibata

# Packages
RUN apt-get update && apt-get install --no-install-recommends -y bc binutils-arm-linux-gnueabi \
  build-essential cpio gcc-arm-linux-gnueabi gdb-arm-none-eabi libc6-dev-armel-cross \
  libelf-dev locales qemu-system-arm bison flex sudo libncurses5 && \
  rm -rf /var/lib/apt/lists/*

COPY ./gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 /
RUN tar -xjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 -C /usr/share/

RUN ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc /usr/bin/arm-none-eabi-gcc && \
  ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-g++ /usr/bin/arm-none-eabi-g++ && \
  ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gdb /usr/bin/arm-none-eabi-gdb && \
  ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-size /usr/bin/arm-none-eabi-size && \
  ln -s /usr/share/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-objcopy /usr/bin/arm-none-eabi-objcopy

# Environment
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV MAKEFLAGS -j4

# Non-root "student" user
RUN useradd -mG sudo student && mkdir -p /etc/sudoers.d && \
  echo '%sudo   ALL=(ALL:ALL) NOPASSWD: ALL' > /etc/sudoers.d/sudo_nopasswd && \
  mkdir -p /home/student/src && \
  echo "alias gdb=\"arm-none-eabi-gdb -ex 'target remote:1234' /home/student/src/linux/vmlinux\"" >> /home/student/.bashrc

COPY ./entrypoint.sh /
COPY ./default_cmd.sh /
ENTRYPOINT ["/entrypoint.sh"]
CMD ["/default_cmd.sh"]
