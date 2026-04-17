FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        curl \
        grep \
        vim \
        ca-certificates \
        coreutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace/at1

COPY . /workspace/at1

CMD ["/bin/bash"]