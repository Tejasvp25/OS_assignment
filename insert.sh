#!/bin/bash
echo -e "\nINSERT:"
echo -n "Enter the name: " 
read name
echo -n "Enter the phone number: " 
read phone
echo -e "$name\t$phone" >> contacts.txt

