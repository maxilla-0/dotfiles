//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/ /*Command*/							/*Update Interval*/	/*Update Signal*/
	/*{"[ ",	 "echo $(top -b -n 1 | awk '/%Cpu/ {print $2 + $4}' | bc)%]",	2,			1},*/
	{"[󰍛 ",	 "echo $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)]",	1,			1},
	{"[󰤨 ",	 "echo $(iwgetid -r)", 						1,			1},  
	{"|",	 "echo $(iwconfig wlo1 | awk -F'[ =]+' '/Signal level/ {print int($4 * 100 / 70)}')%]", 		1,			1},
	{"[",	 "echo $(volume)", 						1,			1},
	{"|M=",	 "echo $(pactl list sinks | awk '/Mute:/ {print $2}')]", 		1,			1},
	{"[󰁹",	 "echo $(cat /sys/class/power_supply/BAT1/capacity)%]",		120,			1},
	{"[󰃭 ",	 "date '+%a|%b|%d][󰥔 %I:%M%p']",					5,			0},
	/*{"[",	 "echo $(whoami)@lenox]",					999999,			0},*/
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "\0";
static unsigned int delimLen = 5;
