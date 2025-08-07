FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++-9 \
    libopencv-dev \
    libgtest-dev \
    pkg-config \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY src/ /app/src/
COPY include/ /app/include/
COPY tests/ /app/tests/
COPY CMakeLists.txt /app/
COPY config/ /app/config/
COPY data/ /app/data/

RUN mkdir -p build && cd build && cmake .. && make

CMD ["./build/video_filter_service"]
