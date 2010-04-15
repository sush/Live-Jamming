#!/bin/bash

SIZE=15000
ADDRESS=192.168.0.13

while (true) ;do

    head /dev/urandom -c $SIZE | nc -q 0 -u $ADDRESS 5042

done