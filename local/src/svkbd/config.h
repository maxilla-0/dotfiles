static const Bool wmborder = True;
static int fontsize = 20;
/* overlay delay in seconds */
static double overlay_delay = 0.50;
/* repeat delay in seconds, will not work on keys with overlays */
static double repeat_delay = 0.75;
/* scan rate in microseconds, affects key repetition rate */
static int scan_rate = 50;
/* one row of keys takes up 1/x of the screen height */
static int heightfactor = 14;
static int xspacing = 5;
static int yspacing = 5;
static const char *defaultfonts[] = {
	"JetbrainsMono Nerd Font:size=20"
};
static const char *defaultcolors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#d8dee9", "#2e3440" },
	[SchemeNormShift] = { "#81a1c1", "#2e3440" },
	[SchemeNormABC] = { "#eceff4", "#2e3440" },
	[SchemeNormABCShift] = { "#81a1c1", "#2e3440" },
	[SchemePress] = { "#2e3440", "#a3be8c" },
	[SchemePressShift] = { "#2e3440", "#a3be8c" },
	[SchemeHighlight] = { "#2e3440", "#5e81ac" },
	[SchemeHighlightShift] = { "#2e3440", "#5e81ac" },
	[SchemeOverlay] = { "#e5e9f0", "#4c566a" },
	[SchemeOverlayShift] = { "#e5e9f0", "#4c566a" },
	[SchemeWindow] = { "#bbbbbb", "#2e3440" },
};

