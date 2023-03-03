/* See LICENSE file for copyright and license details. */

/* Constants */
#define SESSION_FILE "/tmp/dwm-session"
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=11";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "yt", "-g", "120x34", "-e", "yt", NULL };
const char *spcmd3[] = {"st", "-n", "qalc", "-g", "50x20", "-e", "qalc", NULL};
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"yt",		spcmd2},
	{"qalc",	spcmd3},
};

/* tagging */
static const char *tags[] = { "", "", "", "", "",  "", "", "", "", };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance		title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",	NULL,		NULL,		0,		1,	0,		0,	-1 },
	{ TERMCLASS,	NULL,		NULL,		0,		0,	1,		0,	-1 },
	{ NULL,		NULL,		"Event Tester",	0,		0,	0,		1,	-1 }, /* xev */
	{ NULL,		"spterm",	NULL,		SPTAG(0),	1,	1,		0,      -1 },
	{ NULL,		"yt",		NULL,		SPTAG(1),	1,	1,		0,	-1 },
	{ NULL,		"qalc",		NULL,		SPTAG(2),	1,	1,		0,	-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include "shiftview.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	/* { MODKEY|ShiftMask,		XK_Escape,	spawn,		SHCMD("") }, */
	{ MODKEY,			XK_grave,	spawn,		{.v = (const char*[]){ "dmenuunicode", NULL } } },
	{ MODKEY|ShiftMask,		XK_grave,	togglescratch,	{.ui = 2} },
	TAGKEYS(                        XK_1,		0)
	TAGKEYS(                        XK_2,		1)
	TAGKEYS(                        XK_3,		2)
	TAGKEYS(                        XK_4,		3)
	TAGKEYS(                        XK_5,		4)
	TAGKEYS(                        XK_6,		5)
	TAGKEYS(                        XK_7,		6)
	TAGKEYS(                        XK_8,		7)
	TAGKEYS(                        XK_9,		8)
	{ MODKEY,                       XK_0,		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,             XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
	/* { MODKEY,			XK_BackSpace,	spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_BackSpace,	spawn,		SHCMD("") }, */

	{ MODKEY,			XK_Tab,		view,           {0} },
	/* { MODKEY|ShiftMask,		XK_Tab,		spawn,		SHCMD("") }, */
	{ MODKEY,             		XK_q,		killclient,     {0} },
	{ MODKEY|ShiftMask,		XK_q,		spawn,		{.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY,			XK_w,		spawn,		{.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
	{ MODKEY,			XK_e,		spawn,		SHCMD(TERMINAL " -e neomutt; pkill -RTMIN+12 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_e,		spawn,		SHCMD(TERMINAL " -e abook --config ~/.config/abook/abookrc --datafile ~/.local/share/abook/addressbook") },
	{ MODKEY,			XK_r,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
	{ MODKEY|ShiftMask,		XK_r,		spawn,		{.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEY,                       XK_t,		togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_t,		setlayout,      {.v = &layouts[0]} }, /* tile */
	/* { MODKEY,			XK_y,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,          XK_y,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_u,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_u,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_i,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_i,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_o,		incnmaster,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,	{.i = -1 } },
	{ MODKEY,			XK_p,		spawn,		{.v = (const char*[]){ "keepassxc", NULL }} },
	/* { MODKEY|ShiftMask,		XK_p,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_bracketleft,	spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_bracketleft,	spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_bracketright,spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_bracketright,spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_backslash,	spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_backslash,	spawn,		SHCMD("") }, */

	/* { MODKEY,			XK_a,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_a,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_s,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("") }, */
	{ MODKEY,                       XK_d,		spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_d,		spawn,		{.v = (const char*[]){ "passmenu", NULL } } },
	{ MODKEY,			XK_f,		togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,		setlayout,      {.v = &layouts[1]} }, /* free */
	/* { MODKEY,			XK_g,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_g,		spawn,		SHCMD("") }, */
	{ MODKEY,                       XK_h,		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,		setmfact,       {.f = +0.05} },
	/* { MODKEY,			XK_semicolon,	spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_semicolon,	spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_apostrophe,	spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_apostrophe,	spawn,		SHCMD("") }, */
	{ MODKEY,             		XK_Return,	spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.ui = 0} },

	/* { MODKEY,			XK_z,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_z,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_x,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_c,		spawn,		SHCMD("") }, */
	/* { MODKEY|ShiftMask,		XK_c,		spawn,		SHCMD("") }, */
	{ MODKEY,              		XK_b,		shiftview,      { .i = -1 } },
	/* { MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("") }, */
	{ MODKEY,              		XK_n,		shiftview,	{ .i = +1 } },
	/* { MODKEY|ShiftMask,		XK_n,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_m,		togglescratch,	{.ui = 1} },
	{ MODKEY|ShiftMask,             XK_m,		setlayout,      {.v = &layouts[2]} }, /* monocle */
	{ MODKEY,                       XK_comma,  	focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period, 	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, 	tagmon,         {.i = +1 } },

	/* { MODKEY,			XK_F1,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_F2,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_F3,		spawn,		{.v = (const char*[]){ "displayselect", NULL } } },
	{ MODKEY,			XK_F4,		spawn,		SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_F5,     	xrdb,           {.v = NULL } },
	/* { MODKEY,			XK_F6,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_F7,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_F8,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_F9,	   	spawn,		{.v = (const char*[]){ "mounter", NULL } } },
	{ MODKEY,			XK_F10,	   	spawn,		{.v = (const char*[]){ "unmounter", NULL } } },
	{ MODKEY,			XK_F11,		spawn,		{.v = (const char*[]){ "dmenubluetooth", NULL } } },
	/* { MODKEY,			XK_F12,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,             XK_space,  	togglefloating, {0} },

	{ 0,				XK_Print,  	spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,  	spawn,		{.v = (const char*[]){ "maimpick", NULL } } },

	{ 0, XF86XK_AudioMute,		spawn,				SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,				SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,				SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,				{.v = (const char*[]){ "light", "-A", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,	spawn,			   	{.v = (const char*[]){ "light", "-U", "15", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

