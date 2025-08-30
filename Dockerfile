FROM ubuntu:latest

RUN apt update -y && \
    apt install cmake g++ wget sqlite3 build-essential libsqlite3-dev libgtk-3-dev xauth dbus -y

RUN useradd -ms /bin/bash default && mkdir -p /registerC && chown -R default:default /registerC

WORKDIR /registerC

USER default

CMD ["tail", "-f", "/dev/null"]