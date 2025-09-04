FROM ubuntu:latest

RUN apt update -y && \
    apt install cmake g++ wget git libssl-dev sqlite3 build-essential libsqlite3-dev libgtk-3-dev xauth dbus -y

RUN git clone https://github.com/civetweb/civetweb.git && \
    cd civetweb && make build && make install && make install-headers && make install-lib && make install-slib

RUN useradd -ms /bin/bash default && mkdir -p registerC && chown -R default:default /registerC

WORKDIR /registerC

USER default

EXPOSE 8080/tcp

CMD ["tail", "-f", "/dev/null"]