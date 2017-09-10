FROM debian:latest
## Asebaclient
## Updates/packages might get timed out by firewall -> keep trying
RUN update=1; while test $update -ne 0; do apt-get update --fix-missing; update=$? ; done \
    && update=1; while test $update -ne 0; do apt-get install --no-install-recommends -y \
    g++ \
    git \
    make \
    libqtcore4 \
    libqt4-dbus \
    libqt4-test \
    libqt4-dev \
    libqt4-opengl-dev \
    curl \
    ca-certificates \
    ssh-client \
    rsync \
    cmake \
    htop \
    nano \
    curl \
    tar \
    supervisor; \
    update=$? ; done
    #&& apt-get clean \
    #&& rm -r /var/lib/apt/lists/*

## Download and install asebaclient
RUN cd /opt \
    && git clone https://github.com/rasmunk/asebaclient.git \
    && cd asebaclient/build-script \
    && chmod +x generate-debug-release \
    && ./generate-debug-release \
    && rm -r /opt/*

## Install Asebamedulla
RUN cd /opt \
    && curl -SL https://github.com/enki-community/enki/archive/2.0-pre.20170315.tar.gz | tar xz  \
    && curl -SL https://github.com/aseba-community/dashel/archive/1.3.0.tar.gz | tar xz \
    && curl -SL https://github.com/aseba-community/aseba/archive/1.5.5.tar.gz | tar xz \
    && mv enki-2.0-pre.20170315 enki \
    && mv dashel-1.3.0 dashel \
    && mv aseba-1.5.5 aseba \
    #&& git clone -n https://github.com/enki-community/enki.git \
    #&& git clone -n https://github.com/aseba-community/dashel.git \
    #&& git clone -n https://github.com/aseba-community/aseba.git \
    #&& cd enki && git checkout ac3d2730586efd4012ecb4864cf4f9f38555f51c \
    #&& git submodule update --recursive && cd .. \
    #&& cd dashel && git checkout 7c01db1be735fe48ad0c0bc6bc84aa41c5ab90fe \
    #&& git submodule update --recursive && cd .. \
    #&& cd aseba && git checkout f4f0e5d0a6e53dddec4f6ffa38b36cdb5bb9c31d \
    #&& git submodule update --recursive && cd .. \
    && mkdir -p enki/build \
    && mkdir -p dashel/build \
    && mkdir -p aseba/build \
    #&& mkdir -p robo_server/build \
    && cd enki/build \
    && cmake -DCMAKE_BUILD_TYPE=Release ../ \
    && make install -j8 \
    && cd ../../dashel/build \
    && cmake -DCMAKE_BUILD_TYPE=Release ../ \
    && make install -j8 \
    && cd ../../aseba/build \
    && sed -e s/QtWebKit//g -i ../CMakeLists.txt \
    && cmake -DCMAKE_BUILD_TYPE=Release ../ \
    && make install -j8

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

### build the emergent controller
RUN cd /opt/emergent_controller/build-script \
    && ./generate-debug-release \
    && echo "/usr/local/lib" >> /etc/ld.so.conf \
    && ldconfig

## Prepare supervisord
RUN mkdir -p /var/log/supervisor

## insert supervisord config -> handles the startup procedure for the image
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

CMD ["/usr/bin/supervisord"]