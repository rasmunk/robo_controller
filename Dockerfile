FROM debian:latest
## Asebaclient
RUN apt-get update && apt-get install -y g++ git make libqt4-core libqt4-dbus libqt4-test libqt4-dev curl ca-certificates ssh-client rsync nano --no-install-recommends && apt-get clean && rm -r /var/lib/apt/lists/*
RUN cd /opt && curl -O https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.sh && chmod +x cmake-3.7.2-Linux-x86_64.sh && (echo y) | ./cmake-3.7.2-Linux-x86_64.sh && rsync -a /opt/cmake-3.7.2-Linux-x86_64/ /usr/local/ && rm -r /opt/*
RUN cd /opt && git clone https://github.com/rasmunk/asebaclient.git && cd asebaclient/build-script && chmod +x generate-debug-release && ./generate-debug-release && cd ../build/release && make install -j 4 && rm -r /opt/*
## Emergent Controller
RUN cd /opt && git clone https://github.com/rasmunk/emergent_controller.git && git clone https://github.com/opencv/opencv.git && git clone https://github.com/opencv/opencv_contrib.git && chmod +x emergent_controller/build-script/*
RUN cd /opt/opencv && cp -r ../emergent_controller/build-script && cd build-script && ./generate-opencv
#&& ./generate-debug-release && cd ../build/release && make install -j 4 && rm -r /opt/*