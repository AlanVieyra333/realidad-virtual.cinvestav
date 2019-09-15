FROM debian:stable

USER root

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y qtcreator
RUN apt-get install -y qt5-default
RUN apt-get install qt5-doc qtbase5-examples qtbase5-doc-html

#USER 
