FROM debian:11

RUN apt-get update && apt-get install -y \
    build-essential \
    openmpi-bin \
    libopenmpi-dev

WORKDIR /usr/src/app

COPY . .

CMD [ "/bin/bash" ]
