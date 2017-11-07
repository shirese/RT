#!/bin/bash

./rt $1 &
### Set initial time of file
LTIME=`stat -f "%m" $1`
while ps aux | grep -q "[r]t" 
do
   ATIME=`stat -f "%m" $1`

   if [[ "$ATIME" != "$LTIME" ]]
   then
	   kill $!
       ./rt $1 &
       LTIME=$ATIME
   fi
   sleep 1
done
