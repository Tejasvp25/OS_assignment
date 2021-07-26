#!/bin/bash
echo -n "What person or number are you seeking: " 
read find
# Print the header before the answer 
if grep -qF "$find" contacts.txt; then
echo "Found it"
else
echo "Sorry Record not found"
fi
echo "Name ; Phone number" 
grep -i $find contacts.txt
echo -n "Enter New name: " 
read new_name
sed -i "s/$find/$new_name/g" contacts.txt
