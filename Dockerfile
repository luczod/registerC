# Stage 1: Build the application
FROM debian:stable-slim AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    cmake g++ libssl-dev sqlite3 build-essential libsqlite3-dev libcivetweb-dev libgtk-3-dev xauth dbus \
    && rm -rf /var/lib/apt/lists/*

# Set working directory inside the container
WORKDIR /app

# Copy the project source code
COPY . /app

RUN useradd -ms /bin/bash default && mkdir -p app && chown -R default:default /app

USER default

# 1. Create the build directory and switch into it
RUN mkdir build
WORKDIR /app/build 
# OR just WORKDIR build (since /app is the current workdir)

# 2. Execute the build commands from the new working directory
RUN cmake .. && make

EXPOSE 8080/tcp

ENTRYPOINT ["/app/build/bin/registerC"]
