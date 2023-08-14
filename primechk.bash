#!/usr/bin/bash

#name: Androw Abd El Malak
#department: Software Engineering
#email id: aabdel61@mimi.cs.mcgill.ca

# If statement for the "-f filename" case 
if [[ $# -eq 2 ]]
then
	if [[ "$1" = "-f" ]] && [[ "$2" != "-f" ]] && [[ "$2" != "-l" ]];
	then
        	file=$2
        	l=false
	else
		echo "Incorrect function usage!"
		exit 1
	fi
elif [[ $# -eq 3 ]]
then
       #If statement for the "-f filename -l" case	
	if [[ "$1" = "-f" ]] && [[ "$2" != "-f" ]] && [[ "$2" != "-l" ]] && [[ "$3" = "-l" ]];
	then
	        file=$2
       		l=true
	#If statement for the "-l -f filename" case
	elif [[ "$2" = "-f" ]] && [[ "$3" != "-f" ]] && [[ "$3" != "-l" ]] && [[ "$1" = "-l" ]];
	then
                file=$3
                l=true
	else
		echo "Incorrect function usage!"
		exit 1
	fi
else
	echo "Incorrect function usage!"
	exit 1
fi

# Making sure we are inputing a valid file
if [[ !  -f $file ]]
then
        echo "The input is not a valid file!"
        exit 2
fi

# Create a variable to store all the integers in the file 
lines=$(grep -s -x -E '[0-9]+' $file)

# Create a variable to track the largest element
largest=0

# For loop to go through the lines and print them 
for line in $lines
do      
	# Case where we do not have -l
	if [[ "$l" = "false" ]]
	then

        	if [[ $line -gt 1 ]] && [[ $line -lt 1000000000000000000 ]]
        	then
			if [[ "$(/home/2013/jdsilv2/206/mini2/primechk $line)" = "The number is a prime number." ]]
			then
				echo $line
			fi
		fi
	# Case where we have -l
    	else
		if [[ $line -gt 1 ]] && [[ $line -lt 1000000000000000000 ]]
                then
                        if [[ "$(/home/2013/jdsilv2/206/mini2/primechk $line)" = "The number is a prime number." ]]
                        then
				if [[ $line -gt $largest ]]
				then
					largest=$line
				fi
                        fi
                fi
	fi

done

#In the -l case echo the largest value at the end 
if [[ "$l" = "true" ]]
then
	if [[ $largest -ne 0 ]]
	then
		echo $largest
	else
		echo "No prime number found!"
		exit 3
	fi
fi

exit 0 
