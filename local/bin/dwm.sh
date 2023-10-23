#!/bin/bash

picom &
dwmblocks &
xinput --set-prop 11 'libinput Accel Speed' .45
xinput --set-prop 10 'libinput Accel Speed' .45
xset r rate 450 30
nitrogen --restore
xss-lock -- slock &
#rofi -show drun -show-icons -icon-theme Zafiro-Nord-Black-Blue &
#mpv --no-video /home/maxilla/.local/uwu.wav &
exec dwm
