for x in 1 2 3
do
	for y in 1 2 3 4 5 6
	do
		z="${x}-${y}.txt"
		#echo "$z"
		python3 modeling.py $z
	done
done	      
