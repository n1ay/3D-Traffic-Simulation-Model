FROM ubuntu:20.04

RUN apt-get update && \
    apt-get install --no-install-recommends -y \
        cmake make gcc g++ \
        libboost-dev libglew-dev libglm-dev

COPY build-script.sh /tmp/
CMD sh /tmp/build-script.sh

