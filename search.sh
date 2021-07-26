#!/bin/bash
echo -e "\nSEARCH:"
echo -n "Enter the name to search: " 
read query
retval=$(grep -i "$query" contacts.txt)
if [ -n "$retval" ]; then
echo -e "\n$retval\n"
else
echo "Sorry, $query not found."
fi
