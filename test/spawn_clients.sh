#! /bin/bash


I=0

cd ..
while [ $I -lt $1 ] ;do
    ./livejammin_client >/dev/null&
    I=$[ $I+1 ]
done

echo "press <enter> to killall clients"
read a
killall -9 --quiet livejammin_client
