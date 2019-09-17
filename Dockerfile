FROM debian:stable

USER root

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y qtcreator
RUN apt-get install -y qt5-default
#RUN apt-get install -y qt5-doc qtbase5-examples qtbase5-doc-html

RUN apt-get install -y \
  freeglut3 \
  freeglut3-dev \
  mesa-common-dev \
  libglu1-mesa-dev \
  libglew-dev libglm-dev

WORKDIR /app

VOLUME /app

ENTRYPOINT ["make", "-f", "Makefile.main"]
