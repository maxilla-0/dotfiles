#! /bin/bash

ns=$(iwconfig wlo1 | awk -F'[ =]+' '/Signal level/ {print int($4 * 100 / 70)}')

if [[ $ns -eq 0 ]]
then
	echo '󰤯 '

elif [[ $ns -le 25 ]]
then
	echo '󰤟 '

elif [[ $ns -le 50 ]]
then
	echo '󰤢 '

elif [[ $ns -le 75 ]]
then
	echo '󰤥 '

elif [[ $ns -le 100 ]]
then
	echo '󰤨 '

fi
