#!/bin/bash

buf=("|" "/" "-" "//")
i=0
str=""

while [ $i -le 100 ]
do
	printf "[%-100s][%d%%][%c]\r" "$str" "$i" "${buf[i%4]}"
	str+="#"
	let i++
	sleep 0.1;
done

printf "\n"
