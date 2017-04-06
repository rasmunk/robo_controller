FROM debian:latest
## Asebaclient
## Updates/packages might get timed out by firewall -> keep trying
RUN update=1; while test $update -ne 0; do apt-get update --fix-missing; update=$? ; done \
    && update=1; while test $update -ne 0; do apt-get install --no-install-recommends -y \
    g++ \
    git \
    make \
    libqt4-core \
    libqt4-dbus \
    libqt4-test \
    libqt4-dev \
    curl \
    ca-certificates \
    ssh-client \
    rsync \
    cmake \
    htop \
    nano; \
    update=$? ; done \
    && apt-get clean \
    && rm -r /var/lib/apt/lists/*

## Download and install asebaclient
RUN cd /opt \
    && git clone https://github.com/rasmunk/asebaclient.git \
    && cd asebaclient/build-script \
    && chmod +x generate-debug-release \
    && ./generate-debug-release \
    && rm -r /opt/*

## Emergent Controller
## Setup Required OpenCV Modules
RUN cd /opt \
    && git clone https://github.com/rasmunk/emergent_controller.git \
    && git clone https://github.com/opencv/opencv.git \
    && git clone https://github.com/opencv/opencv_contrib.git \
    && chmod +x /opt/emergent_controller/build-script/* \
    && cd /opt/opencv_contrib && mkdir modules_tmp \
    ## Only keep required modules
    && mv modules/* modules_tmp/ \
    && mv modules_tmp/xfeatures2d modules/ \
    && mv modules_tmp/tracking modules/ \
    && cd /opt/opencv \
    && cp -r ../emergent_controller/build-script . \
    && cd build-script \
    && ./generate-opencv \
    && rm -r /opt/opencv*

## build the emergent controller
RUN cd /opt/emergent_controller/build-script \
    && ./generate-debug-release \
    && echo "/usr/local/lib" >> /etc/ld.so.conf \
    && ldconfig