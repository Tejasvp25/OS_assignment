#!/bin/sh
BOOK="address-book.txt"
exit=0

while [ $exit -ne 1 ]
do
    echo "What operation do you want?"
    echo "1.add\n2.list\n3.find\n4.del\n5.update\n6.exit: "
    read answer

    if [ "$answer" = "1" ]
    then
        ./insert.sh
    elif [ "$answer" = "2" ]
    then
        ./disp.sh
    elif [ "$answer" = "3" ]
    then
        ./search.sh
    elif [ "$answer" = "4" ]
    then
        ./del.sh
    elif [ "$answer" = "5" ]
    then
        ./update.sh
    elif [ "$answer" = "6" ]
    then
        exit=1
    else
        echo "I do not understand the command."
    fi
done

exit 0