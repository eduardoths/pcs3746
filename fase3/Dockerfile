FROM ubuntu:latest AS builder

RUN apt-get update && apt-get install -y make gcc

WORKDIR /app
COPY . .
RUN cd thread_test/ && make all

FROM centos:7

RUN yum install sudo -y

# Add a non-root "student" user
RUN useradd -mG wheel student && mkdir -p /etc/sudoers.d && \
  echo '%wheel   ALL=(ALL:ALL) NOPASSWD: ALL' > /etc/sudoers.d/sudo_nopasswd && \
  mkdir -p /home/student/src

COPY ./entrypoint.sh /
COPY ./default_cmd.sh /
COPY --from=builder /app/thread_test/thread_test .

# Packages
RUN yum clean all && yum makecache && yum update -y
RUN yum-config-manager --save --setopt=c7-media.skip_if_unavailable=true
RUN yum install -y systemtap systemtap-runtime
RUN stap-prep

ENTRYPOINT [ "/entrypoint.sh" ]
CMD [ "/default_cmd.sh" ]
