/* See LICENSE file for copyright and license details. */

/* For Function Multimedia keys */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const int gappx              = 7;
static const char *fonts[]          = { "RobotoMono Nerd Font:size=12" };
static const char dmenufont[]       = "RobotoMono Nerd Font:size=12";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#282828";
static const char col_gray3[]       = "#ebddb2";
static const char col_gray4[]       = "#ebddb2";
static const char col_cyan[]        = "#d65d0e";
static const char *colors[][3]      = {
	/*               text?    bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_cyan, col_gray1},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* General Commands */
static char dmenumon[2]         = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]    = { "alacritty", NULL };
static const char *firefoxcmd[] = { "firefox", NULL };

/* Media Control Commands */
static const char *cmdmute[]    = { "amixer", "set", "Master", "togglemute", NULL };
static const char *cmdplay[]    = { "playerctl", "-a", "play-pause", NULL };
static const char *cmdnxt[]     = { "playerctl", "-a", "next", NULL };
static const char *cmdprv[]     = { "playerctl", "-a", "previous", NULL };

static Key keys[] = {
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_n,                       spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,                       spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_f,                       spawn,          {.v = firefoxcmd } },
	{ MODKEY,                       XK_q,                       killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	TAGKEYS(                        XK_6,                                       5)
	TAGKEYS(                        XK_7,                                       6)
	TAGKEYS(                        XK_8,                                       7)
	TAGKEYS(                        XK_9,                                       8)
	{ MODKEY|ShiftMask,             XK_q,                       quit,           {0} },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          SHCMD("amixer set Master 5%+; pkill -RTMIN+11 dwmblocks") },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,          SHCMD("amixer set Master 5%-; pkill -RTMIN+11 dwmblocks") },
    { 0,                            XF86XK_AudioMute,           spawn,          {.v = cmdmute } },
    { 0,                            XF86XK_AudioPlay,           spawn,          {.v = cmdplay } },
    { 0,                            XF86XK_AudioPrev,           spawn,          {.v = cmdnxt } },
    { 0,                            XF86XK_AudioNext,           spawn,          {.v = cmdprv } },
    { 0,                            XF86XK_MonBrightnessUp,     spawn,          SHCMD("xbacklight -time 300 -steps 100 -inc 10; pkill -RTMIN+12 dwmblocks") },
    { 0,                            XF86XK_MonBrightnessDown,   spawn,          SHCMD("xbacklight -time 300 -steps 100 -dec 10; pkill -RTMIN+12 dwmblocks") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};