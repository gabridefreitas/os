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

WORKDIR /workspace/at2

COPY . /workspace/at2

CMD ["/bin/bash"]
