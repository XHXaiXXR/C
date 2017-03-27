#!/bin/bash

#递归求和

sum=0
function sum()
{
	num=$1

	if [ $num -eq 1 ];then
		echo $num
		return
	fi
	
	let --num
	tmp=$( sum $num )
	let sum=$1+$tmp

	echo ${sum}
}

sum 100

#sum=0
#str=""
#i=0
#while [ ${i} -lt 100 ]
#do
#	str+="${i}+"
#	let sum+=i
#	let i++
#done
#
#str+="$i"
#let sum+=i
#
#echo "${str}=${sum}"

#sum=0
#for (( i=0; i <= 100; i++ ))
#do
#	let sum+=i
#done
#
#echo "$sum"
