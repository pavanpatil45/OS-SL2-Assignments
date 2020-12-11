//OS1.sh
#! /bin/bash
opt=1
while [ "$opt" -lt 6 ]
do

	printf "1. Create Address Book\n2. View Records\n3 .Insert new Record\n4. Delete a Record\n5. Modify a Record\n6. Exit\n\n"
	
	read opt
	case $opt in

1)
		printf "Enter filename : "
		read fileName
		if [ -e $fileName ] ; then
			rm $fileName
		fi
		cont=1
		printf  "NAME\t\tNUMBER\t\t\tADDRESS\n=====================================================================\n" | cat >> $fileName
		while [ "$cont" -gt 0 ]
		do
			printf "\nEnter Name : "
			read name
			printf "Enter Phone Number of  $name"
			read number
			printf "Enter Address of  $name"
			read address
			printf "$name\t$number\t\t$address\n" | cat >> $fileName
			printf "Enter 0 to Stop, 1 to Enter next :"
			read cont
		done
		;;
2)
		cat $fileName
		;;
	3)
		printf "\nEnter Name : "
		read name
		printf "Enter Phone Number of  $name"
		read number
		printf "Enter Address of  $name"
		read address
		printf "$name\t$number\t\t$address\n" | cat >> $fileName
		;;
	4)
		printf "Delete record\nEnter Name/Phone Number"
		read pattern
		temp="temp"
		grep -v $pattern $fileName | cat >> $temp 
		rm $fileName
		cat $temp | cat >> $fileName
		rm $temp
		;;
	5)
		printf "Modify record\nEnter Name/Phone Number"
		read pattern
		temp="temp"
		grep -v $pattern $fileName | cat >> $temp
		rm $fileName
		cat $temp | cat >> $fileName
		rm $temp
		printf "Enter Name"
		read name
		printf "Enter Phone Number of $name"
		read number
		printf "Enter Address of $name"
		read address
		echo -e "$name\t$number\t\t$address\n" | cat >> $fileName
		;;
	esac
done
