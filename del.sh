#!/bin/bash

echo "Please input Name to delete:" 
read name
sed "/$name/d" contacts.txt > contacts_tmp.txt 
rm contacts.txt
mv contacts_tmp.txt contacts.txt 
echo "$name is removed from your contacts"
