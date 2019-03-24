#/bin/bash

i=0
while true
do
	#python3 gen.py >in
	#./gen >in
	./generators/graph >in
	./c <in >out
	./d <in >ok
	#python3 verif.py
	
	#if [ $? -eq 1 ]; then
	# 	echo $?
	#  	exit 1
	#fi
	
	if ! diff out ok; then
		echo $?
		exit 1
	fi
	
	#if ((i == 1000)); then
	#	exit 0
	#fi

	let i=i+1
	if ((i % 1 == 0)); then
		echo $i
	fi
done
