#!/bin/bash  

sum=0

arr=(33 532 54 12 87 9)
max=${arr[0]}
min=${arr[0]}

for (( i=0; i<${#arr[@]}; ++i ))
do
	if [ $max -lt ${arr[$i]} ];then
		let max=${arr[$i]}
	fi

	if [ $min -gt ${arr[$i]} ];then
		let min=${arr[$i]}
	fi

	let sum+=${arr[$i]}
done

echo "${arr[@]}"
echo "max = $max"
echo "min = $min"
echo "ibase=10; scale=2; ${sum}/${#arr[@]}" | bc
