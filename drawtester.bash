#!/bin/bash

if [[ ! -f asciidraw.c ]]
then
	echo "Error cannot locate asciidraw.c"
	exit 1
fi

# Modify this to whatever is your compilation statement is (subject to the restrictions in the assignment PDF)
gcc -o asciidraw asciidraw.c -lm
rc=$?

if [[ $rc -ne 0 ]]
then
	echo "There were errors/warnings from gcc. rc = $rc"
	exit $rc
fi

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 1: Creating the Grid and Validating the Command --- "
echo '
./asciidraw <<ENDOFCMDS
wrong input
CIRCLE 0,0 10
GRID 20 20
DISPLAY
GRID 500 50
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
wrong input
CIRCLE 0,0 10
GRID 20 20
DISPLAY
GRID 500 50
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 2: Changing the drawing character --- "
echo '
./asciidraw <<ENDOFCMDS
CHAR ~
GRID 20 20
LINE 10,10 20,10
DISPLAY
CHAR @
LINE 10,14 20,14
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
CHAR ~
GRID 20 20
LINE 10,10 20,10
DISPLAY
CHAR @
LINE 10,14 20,14
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 3: Drawing rectangles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 10,20 20,10
CHAR -
RECTANGLE 5,30 15,25
CHAR @
RECTANGLE 30,30 50,10
DISPLAY
END
ENDOFCMDS
'

./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 10,20 20,10
CHAR -
RECTANGLE 5,30 15,25
CHAR @
RECTANGLE 30,30 50,10
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 4: Draw horizontal lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 30 30
LINE 10,20 20,20
CHAR @
LINE 20,10 10,10
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 30 30
LINE 10,20 20,20
CHAR @
LINE 20,10 10,10
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 5: Draw vertical lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,10 10,30
CHAR +
LINE 20,30 20,10
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,10 10,30
CHAR +
LINE 20,30 20,10
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 6: Draw diagonal lines --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 20,20 30,35
CHAR +
LINE 10,20 20,10
CHAR @
LINE 30,39 20,24
CHAR -
LINE 20,14 10,24
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 20,20 30,35
CHAR +
LINE 10,20 20,10
CHAR @
LINE 30,39 20,24
CHAR -
LINE 20,14 10,24
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 7: Case to draw circles --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
CIRCLE 25,25 10
CHAR %
CIRCLE 0,0 6
CHAR @
CIRCLE 39,39 8
CHAR ~
CIRCLE 0,39 8
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 40
CIRCLE 25,25 10
CHAR %
CIRCLE 0,0 6
CHAR @
CIRCLE 39,39 8
CHAR ~
CIRCLE 0,39 8
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 8: Truncate Shapes --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,30 20,50
CHAR +
RECTANGLE 30,60 50,20
CHAR @
CIRCLE 40,2 10
CHAR -
LINE 0,60 10,30
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 50
LINE 10,30 20,50
CHAR +
RECTANGLE 30,60 50,20
CHAR @
CIRCLE 40,2 10
CHAR -
LINE 0,60 10,30
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 9: Overlap Shapes --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 5,30 20,10
CHAR @
CIRCLE 20,20 6
CHAR -
LINE 0,0 40,40
CHAR ~
LINE 0,40 40,0
DISPLAY
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 40
RECTANGLE 5,30 20,10
CHAR @
CIRCLE 20,20 6
CHAR -
LINE 0,0 40,40
CHAR ~
LINE 0,40 40,0
DISPLAY
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "

echo " --- Test case 10: Return Error With Invalid Commands --- "
echo '
./asciidraw <<ENDOFCMDS
GRID 40 50
This is not a correct command
CIRCL 6,6 8
RECTGL 7,10 10,6
END
ENDOFCMDS
'
./asciidraw <<ENDOFCMDS
GRID 40 50
This is not a correct command
CIRCL 6,6 8
RECTGL 7,10 10,6
END
ENDOFCMDS

echo " "
echo " --------------------------------------------------- "
echo " "
echo "End Of Tests." > /dev/tty
