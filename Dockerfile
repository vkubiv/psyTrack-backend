# our local base image
FROM ubuntu
 
LABEL description="Container for use with Visual Studio"
 
# install build dependencies
RUN apt-get update && apt-get install -y g++ rsync zip openssh-server make gdb cmake git
 
# configure SSH for communication with Visual Studio
RUN mkdir -p /var/run/sshd
 
RUN echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config && \
   ssh-keygen -A
   
RUN git clone https://github.com/oktal/pistache.git && cd pistache && git submodule update --init && \
	mkdir build && cd build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug .. && make && make install

RUN service ssh start
RUN useradd -m -d /home/dev -s /bin/bash -G sudo dev
RUN echo "dev:dev" | chpasswd
 
# expose port 22
EXPOSE 22
EXPOSE 3000

CMD service ssh start