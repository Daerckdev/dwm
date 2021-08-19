/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"
#define BROWSER "brave"
#define BROWCLASS "Brave"

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 10;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "Twemoji:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#770000";
static char selbgcolor[]      = "#005577";
static char *colors[][3]      = {
	/*                   fg              bg              border   */
	[SchemeNorm] = { normfgcolor,    normbgcolor,    normbordercolor },
	[SchemeSel]  = { selfgcolor,     selbgcolor,     selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ BROWCLASS, NULL,     NULL,           2,         0,          0,          -1,        -1 },
	{ TERMCLASS, NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *layoutmenu_cmd = "dwm_layoutmenu.sh";

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "topbar",          	INTEGER, &topbar },
};

#include "shiftview.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_b,      shiftview,      { .i = -1} },
	{ MODKEY,                       XK_n,      shiftview,      { .i = +1} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },

    // spawn stuff
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
    { MODKEY,       		        XK_e,	   spawn,          SHCMD(TERMINAL " -e lf") },
    { MODKEY|ShiftMask,		        XK_w,	   spawn,          SHCMD(TERMINAL " -e sudo nmtui") },
    { ControlMask|ShiftMask,        XK_Escape, spawn,          SHCMD(TERMINAL " -e htop") },

    // Dmenu stuff
	{ MODKEY,                       XK_comma,  spawn,          SHCMD("dmenutodo") },
	{ MODKEY,                       XK_period, spawn,          SHCMD("dmenuunicode") },
	{ MODKEY,                       XK_minus,  spawn,          SHCMD("passmenu") },

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },

    // Layouts
    { MODKEY,           			XK_t,	   setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,     		XK_t,	   setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			            XK_y,	   setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		        XK_y,	   setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			            XK_u,	   setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		        XK_u,	   setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			            XK_i,	   setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		        XK_i,	   setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,       		        XK_f,	   setlayout,	{.v = &layouts[8]} }, /* floating */
	{ MODKEY,                       XK_space,  togglefloating, {0} },

	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_x,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_z,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_x,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_z,      tagmon,         {.i = +1 } },

    // Screenshot (require maim)
	{ 0,                            XK_Print,  spawn,          SHCMD("maim $HOME/Screenshots/full-screenshot-$(date '+%Y%m%d%H%M%S').png; notify-send \"Full screeshot has taken\"") },
	{ ShiftMask,                    XK_Print,  spawn,          SHCMD("maim -s $HOME/Screenshots/selected-screenshot-$(date '+%Y%m%d%H%M%S').png; notify-send \"Selected screenshot has taken\"") },
	{ ControlMask,                  XK_Print,  spawn,          SHCMD("maim -i $(xdotool getactivewindow) $HOME/Screenshots/window-screenshot-$(date '+%Y%m%d%H%M%S').png; notify-send \"Active window screeshot has taken\"") },

    // extra keyboard features
	{ 0,  XF86XK_AudioMute,                    spawn,          SHCMD("pamixer --toggle-mute; pkill -RTMIN+5 dwmblocks") },
	{ 0,  XF86XK_AudioLowerVolume,             spawn,          SHCMD("pamixer --decrease 2; pkill -RTMIN+5 dwmblocks") },
	{ 0,  XF86XK_AudioRaiseVolume,             spawn,          SHCMD("pamixer --increase 2; pkill -RTMIN+5 dwmblocks") },
    
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                        event mask      button          function        argument */
	{ ClkLtSymbol,                  0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,                  0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,                  0,              Button2,        zoom,           {0} },

	{ ClkStatusText,                0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,                0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,                0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,                ShiftMask,      Button1,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,                ShiftMask,      Button2,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,                ShiftMask,      Button3,        sigdwmblocks,   {.i = 6} },

	{ ClkClientWin,                 MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,                 MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,                 MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,                    0,              Button1,        view,           {0} },
	{ ClkTagBar,                    0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,                    MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,                    MODKEY,         Button3,        toggletag,      {0} },
};
