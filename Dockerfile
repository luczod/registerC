FROM ubuntu:latest

RUN apt update -y && \
    apt install cmake g++ wget sqlite3 libsqlite3-dev -y

WORKDIR /registerC

CMD ["tail", "-f", "/dev/null"]