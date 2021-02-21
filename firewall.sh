#!/usr/bin/env bash

>passed.txt

while read one_line;
do
	while read gen_rules; 
	do	
	>tot_num
	>res.txt
	
	line_rules=`echo "$gen_rules"|sed -e 's/#.*//'|tr -d ''`
	
	if [ "$line_rules" != "" ]; then
		
		rules=$(echo $line_rules|tr "," "\n")
	
		for single_rule in "${rules[@]}";
		do
			echo "$one_line" | ./firewall.exe "$single_rule">> res.txt
		done
	
		tot_num=`cat res.txt | wc -l`
		line_rules_num=${#rules[@]}
	
		if [ $tot_num -eq $line_rules_num ]; then
			echo "$one_line" >> passed.txt
		fi
	fi
	done < "$1"
done
rm tot_num
rm res.txt
cat passed.txt|sort|uniq|sed '/^$/d'|tr -d ' '
rm passed.txt
