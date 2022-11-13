/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"
#define BROWSER "firefox"

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 5;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray  = 1;     /* 0 means no systray */
static unsigned int gappih    = 15;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static       int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "Twemoji:size=10:antialias=true:autohint=true" };
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#770000";
static char selbgcolor[]      = "#005577";
static char seltag[]          = "#fcba03";
static char windowpresent[]   = "#ff2b1c";
static char windowurgpresent[]= "#00ba1f";
static char *colors[][3]      = {
	/*                   fg              bg              border   */
	[SchemeNorm] = { normfgcolor,    normbgcolor,    normbordercolor },
	[SchemeSel]  = { selfgcolor,     selbgcolor,     selbordercolor  },
    [SchemeUpLines] = { seltag },
    [SchemeBottomLines] = { windowpresent, windowurgpresent },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "", "", "", "", "", "", "", "", "" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/
static const unsigned int linetagpad = 6;
static const unsigned int linetagthickness = 2;

static const Rule rules[] = {
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           1 << 3,    0,          0,           0,        -1 },
	{ BROWSER,   NULL,     NULL,           1 << 1,    0,          0,          -1,        -1 },
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
        { "borderpx",           INTEGER, &borderpx },
        { "snap",               INTEGER, &snap },
        { "topbar",             INTEGER, &topbar },
        { "gappih",             INTEGER, &gappih },
        { "gappiv",             INTEGER, &gappiv },
        { "gappoh",             INTEGER, &gappoh },
        { "gappov",             INTEGER, &gappov },
        { "seltag",             STRING, &seltag },
        { "windowpresent",      STRING, &windowpresent },
        { "windowurgpresent",   STRING, &windowurgpresent },

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
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_b,      shiftview,      { .i = -1} },
	{ MODKEY,                       XK_n,      shiftview,      { .i = +1} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },

    // spawn stuff
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
    { MODKEY,       		        XK_e,	   spawn,          SHCMD(TERMINAL " -e lf") },
    { MODKEY|ShiftMask,		        XK_w,	   spawn,          SHCMD(TERMINAL " -e sudo nmtui") },
    { ControlMask|ShiftMask,        XK_Escape, spawn,          SHCMD(TERMINAL " -e htop") },

    // Dmenu stuff
	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_comma,  spawn,          SHCMD("dmenutodo") },
	{ MODKEY,                       XK_period, spawn,          SHCMD("dmenuunicode") },
	{ MODKEY|ShiftMask,             XK_period, spawn,          SHCMD("dmenupackage") },
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
	{ MODKEY|ShiftMask,             XK_Tab,    togglealttag,   {0} },
    { MODKEY,           			XK_t,	   setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,     		XK_t,	   setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			            XK_y,	   setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		        XK_y,	   setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			            XK_u,	   setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		        XK_u,	   setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			            XK_m,	   setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		        XK_m,	   setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
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

    { ShiftMask|MODKEY,             XK_h,      spawn,          SHCMD("farge")},

    // extra keyboard features
	{ 0, XF86XK_AudioMute,                     spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; pkill -RTMIN+5 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%-; pkill -RTMIN+5 dwmblocks") },
	{ 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%+; pkill -RTMIN+5 dwmblocks") },
    { 0, XF86XK_AudioPrev,                     spawn,          SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,                     spawn,          SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,                    spawn,          SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,                     spawn,          SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,                     spawn,          SHCMD("mpc stop") }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                        event mask      button          function        argument */
	// { ClkLtSymbol,                  0,              Button1,        setlayout,      {0} },
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
