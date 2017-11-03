#!/bin/bash

./rtv1 $1 &
### Set initial time of file
LTIME=`stat -f "%m" $1`
while ps aux | grep -q "[r]tv1" 
do
   ATIME=`stat -f "%m" $1`

   if [[ "$ATIME" != "$LTIME" ]]
   then
	   kill $!
       ./rtv1 $1 &
       LTIME=$ATIME
   fi
   sleep 1
done
