/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetbrainsMono Nerd Font:size=10", "JoyPixels:pixelsize=12:antialias=true:autohint=true"};
static const char dmenufont[]       = "JetbrainsMono Nerd Font:size=10";
static char normbgcolor[]           = "#2e3440";
static char normbordercolor[]       = "#4c566a";
static char normfgcolor[]           = "#eceff4";
static char selfgcolor[]            = "#2e3440";
static char selbordercolor[]        = "#88c0d0";
static char selbgcolor[]            = "#81a1c1";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "firefox",            NULL,     NULL,           2,         0,          0,          -1,        -1 },
	{ "svkbd-mobile-intl",  NULL,     NULL,           0,         1,          0,          -1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]  = { "alacritty", NULL };

static const char *upvol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "+2%", "&&", "kill", "-44", "$(pidof dwmblocks)", NULL };
static const char *downvol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "-2%", "&&", "kill", "-44", "$(pidof dwmblocks)", NULL };
static const char *mutevol[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", "&&", "kill", "-44", "$(pidof dwmblocks)", NULL };
static const char *brupcmd[] = { "sudo", "brightnessctl", "set", "1%+", NULL };
static const char *brdowncmd[] = { "sudo", "brightnessctl", "set", "1%-", NULL };

static const char *rofi[]     = {"rofi", "-show", "drun", "-width", "27", NULL };
static const char *rofiwifi[]    = {"rofi-wifi-menu", NULL };
/*static const char *rofilinks[]    = {"bash", "/home/maxilla/rofi-links/links.sh", NULL };*/
static const char *rofilinks[]    = {"links", NULL };
static const char *rofishowwindow[]    = {"rofi", "-show", "window", NULL };
static const char *rofipowermenu[]    = {"rofi", "-show", "power-menu", "-width", "12", "-modi", "power-menu:rofi-power-menu --choices=lockscreen/suspend/logout/reboot/shutdown", NULL };
static const char *ff[]    = {"firefox", NULL };
static const char *fileman[] = {"pcmanfm", NULL };
static const char *lock[]    = {"slock", NULL };
static const char *osk[]    = {"svkbd-mobile-intl", "-g", "1000x400+460+674", NULL };

static const char *medplaypausecmd[] = { "playerctl", "play-pause", NULL };
static const char *mednextcmd[] = { "playerctl", "next", NULL };
static const char *medprevcmd[] = { "playerctl", "previous", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },
	{ MODKEY|ShiftMask,             XK_h,      togglebar,      {0} },
	{ MODKEY,                       XK_f,      zoom,           {0} },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = +1 } },
	{ MODKEY,		       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      togglefloating, {0} },
	{ MODKEY|ControlMask|ShiftMask,                       XK_g,      center,         {0} },
	{ MODKEY,                       XK_t,      setlayout,      {0} },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,		       XK_Return, spawn,          {.v = termcmd } },
	//{ MODKEY|ShiftMask,	       XK_Return, spawn,          SHCMD("st") },
	{ MODKEY,		       XK_z,      spawn,          {.v = rofi } },
	{ MODKEY|ShiftMask,	       XK_z,      spawn,          {.v = rofiwifi } },
	{ MODKEY,		       XK_b,      spawn,          {.v = rofilinks } },
	{ MODKEY,		       XK_a,      spawn,          {.v = rofishowwindow } },
	{ MODKEY,		       XK_x,      spawn,          {.v = rofipowermenu } },
	{ ControlMask|ShiftMask,        XK_f,      spawn,          {.v = ff } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = fileman } },
	{ MODKEY|ShiftMask,	       XK_l,      spawn,          {.v = lock } },
	{ MODKEY|ShiftMask,	       XK_k,      spawn,          {.v = osk } },
	{ 0,			       0xff61,    spawn,          SHCMD("flameshot gui") },
	{ 0,			       XF86XK_AudioRaiseVolume,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +2%; kill -44 $(pidof dwmblocks)") },
	{ 0,			       XF86XK_AudioLowerVolume,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -2%; kill -44 $(pidof dwmblocks)") },
	{ 0,			       XF86XK_AudioMute,             spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioPlay,             spawn,          {.v = medplaypausecmd } },
	{ 0,                            XF86XK_AudioNext,             spawn,          {.v = mednextcmd } },
	{ 0,                            XF86XK_AudioPrev,             spawn,          {.v = medprevcmd } },
	{ 0,			       XF86XK_MonBrightnessUp,       spawn,          {.v = brupcmd} },
	{ 0,			       XF86XK_MonBrightnessDown,     spawn,          {.v = brdowncmd} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i =  0 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          SHCMD("gnome-control-center") },
	{ ClkStatusText,        0,              Button3,        spawn,          SHCMD("alacritty -e htop") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

