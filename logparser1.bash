#!/usr/bin/bash

#Verify that there is at least 1 argument given
if [[ $# -ne 1 ]]
then
        echo "Usage ./logparser.bash <logdir>"
        exit 1

#Verify that the entered directory is valid
elif [[ ! -d $1 ]]
then
        >&2 echo "Error: $1 is not a valid directory name"
        exit 2
fi

#Finding the files in the directory
files=$(ls $1 | grep '.log$')

#Create the headers for the CSV and HTML Files
headerCSV="broadcaster,nummsgs"
headerHTML="<TR><TH>broadcaster</TH><TH>nummsgs</TH>"
totalFiles=0

#Remove the content of the output file
echo -n "" > logdata.csv

#Go through all the valid files 
for file in $files
do
        #Treat the fileName to get the format we want
        processName=`echo $file | sed 's/\./:/; s/.log//;'`

        #Build the headers for the CSV and HTML Files
        headerCSV="$headerCSV,$processName"
        headerHTML="$headerHTML<TH>$processName</TH>"
        totalFiles=$(expr $totalFiles + 1)

        #Get a list of the broadcasted messages and their ids for that file
	bandids=$(grep "Translating to point-to-point messages :" $1/$file | awk 'BEGIN { OFS="," } { print $4,$NF }')

        #Go through this list of ids and do the following for each broadcasted id:
        for bandid in $bandids
        do
                #Go through all the files again to find the received and delivered messages with this id
                for file2 in $files
                do
			broadcastTime=$(echo $bandid | awk -F',' '{ print $1 }')
			id=$(echo $bandid | awk -F',' '{ print $2 }')
                        #Treat the fileName to get the format we want
                        processReceiverName=`echo $file2 | sed 's/\./:/; s/.log//;'`

                        #Extract a list of received times from all processes with this id in this file
                        receivedTime=`grep "Received a message from. message: \[senderProcess:$processName:val:$id\]" $1/$file2 | awk '{ print $4 }'`

                        #Extract the delivered time
                        deliveredTime=`grep "Received :$id from : $processName" $1/$file2 | awk '{ print $4 }'`

                        #Produce an ouput with the treatedFileName, id, treatedReceiverName, broadcastTime, timeReceive, timeDelivery
                        echo "$processName,$id,$processReceiverName,$broadcastTime,$receivedTime,$deliveredTime" >> logdata.csv
                done
        done
done

#Complete the HTML HEADER
headerHTML="$headerHTML</TR>"

#Send the CSV header to the CSV File
echo $headerCSV > stats.csv

#Building the html file
echo "<HTML>" > stats.html
echo "<BODY>" >> stats.html
echo "<H2>GC Efficiency</H2>" >> stats.html
echo "<TABLE>" >> stats.html
echo $headerHTML >> stats.html

#Find the information and build the csv file
for file in $files
do
        #Treat the fileName to get the format we want
        processName=`echo $file | sed 's/\./:/; s/.log//;'`

        # Figure out how many times the name appears in the first colum (if not 0 add its name to content and add the number of times it appeared to the content)
        nummsgs=$(awk -v fileName=$processName -v totalNumberFiles=$totalFiles 'BEGIN{FS=","; nummsgs=0} { if ($1 == fileName) { nummsgs=nummsgs+1 } } END { print nummsgs/totalNumberFiles  }' < logdata.csv)

        if [[ $nummsgs -ne 0  ]]
        then
                percentagesCSV=""
                percentagesHTML=""
                # For looop to go through the names of receivers:
                for file in $files
                do
                        #Treat the fileName to get the format we want
                        processReceivedName=`echo $file | sed 's/\./:/; s/.log//;'`

                        #Count the number of times the first column of table is the processedFilename and the 3d column of the table is the proccessedReceiverName and the last column of the table is not empty
                        totalReceived=$(awk -v fileName=$processName -v proccessedReceiverName=$processReceivedName 'BEGIN{FS=","; totalSent=0} { if ($1 == fileName && $3 == proccessedReceiverName && $NF != "") { totalSent=totalSent+1 } } END { print totalSent  }' < logdata.csv)

                        #Count the number of times the first and 3d columns are the same
                        totalSent=$(awk -v fileName=$processName -v proccessedReceiverName=$processReceivedName 'BEGIN{FS=","; totalSent=0} { if ($1 == fileName && $3 == proccessedReceiverName) { totalSent=totalSent+1 } } END { print totalSent  }' < logdata.csv)

                        #Calculate the percentage
                        percentage=$(awk -v totalValuesReceived=$totalReceived -v totalValuesSent=$totalSent 'BEGIN { print totalValuesReceived/totalValuesSent*100 }')

                        #Make the rest of the output
                        percentagesCSV="$percentagesCSV,$percentage"
                        percentagesHTML="$percentagesHTML<TD>$percentage</TD>"
                done

                #Put the output in the CSV and HTML files according to their format
                echo $processName,$nummsgs$percentagesCSV >> stats.csv
                echo "<TR><TD>$processName</TD><TD>$nummsgs</TD>$percentagesHTML</TR>" >> stats.html
        fi
done

#Complete the HTML File
echo "</TABLE>" >> stats.html
echo "</BODY>" >> stats.html
echo "</HTML>" >> stats.html

exit 0
