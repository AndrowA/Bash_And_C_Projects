#!/usr/bin/bash

#name: Androw Abd El Malak
#department: Software Engineering
#email id: aabdel61@mimi.cs.mcgill.ca

# Verify if argument given is the name of directory
if [[ -d $2 ]]
then
	#Transform the output file format
	file2=$2/$(basename $1)
else
	#Keep the output file as entered by the used
	file2=$2
fi

# Verify That 2 arguments have been entered
if [[ $# -ne 2 ]]
then
	echo "Please enter only 2 arguments!"
        exit 1

# Verify that the input and output dont have path
elif [[ $1 -ef $file2 ]]
then
	echo "Please enter different input and output names!"
        exit 2

# Verify that the input file is readable and exists
elif [[ ! -r $1 ]]
then
	echo "Please select a readable input file!"
        exit 3

# Verify that output path (For file) exists and is a file, otherwise error
elif [[ -e $file2 ]] && [[ ! -f $file2 ]]
then
        echo "Please select an existing output file!"
        exit 4

# Verify that the output file is writtable and exists 

elif [[ -e $file2 ]] && [[ ! -w $file2 ]]
then
	echo "Please enter a writable output file!"
        exit  4
fi

# Run the namefix script with both files 
/home/2013/jdsilv2/206/mini2/namefix $1 $file2
