#! /bin/bash

VOLUME=$(pactl list sinks | awk '$1=="Volume:" {sub(/%/, "", $5); print $5}')
MUTE=$(pactl list sinks | awk '/Mute:/ {print $2}')

if [[ $MUTE == "yes" ]]
then
	echo 󰝟 $VOLUME%

elif [[ $MUTE == "no" && $VOLUME -eq 0 ]]
then
    echo 󰖁

elif [[ $MUTE == "no" && $VOLUME -lt 30 ]]
then
    echo 󰕿 $VOLUME%
	
elif [[ $MUTE == "no" && $VOLUME -lt 50 ]]
then
    echo 󰖀 $VOLUME%

elif [[ $MUTE == "no" && $VOLUME -le 100 ]]
then
    echo 󰕾 $VOLUME%

elif [[ $MUTE == "no" && $VOLUME -gt 100 ]]
then
    echo 󰝝 $VOLUME%

fi

