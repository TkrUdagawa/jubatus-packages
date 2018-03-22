#!/bin/bash -uex

cd "$(dirname "${0}")"

apt-get update
apt-get install -y apt-utils debhelper
apt-ftparchive sources binary  | gzip -c9 > binary/Sources.gz
apt-ftparchive packages binary		  > binary/Packages
apt-ftparchive packages binary | gzip -c9 > binary/Packages.gz
apt-ftparchive contents binary | gzip -c9 > binary/Contents-$(dpkg --print-architecture).gz
apt-ftparchive release binary  		  > binary/Release
