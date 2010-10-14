#!/bin/bash

SIZE=15000
ADDRESS=127.0.0.1

while (true) ;do

    head /dev/urandom -c $SIZE | nc -q 0 -u $ADDRESS 5042

done