/* For Function Multimedia keys */
#include <X11/XF86keysym.h>

/* Colour scheme */
#include "themes/gruvbox.h"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int user_bh            = 36;       /* >0 sets bar height */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const int gappx              = 10;       /* padding of windows */
static const char *fonts[]          = { "RobotoMono Nerd Font:size=12" };

/* Tag names */
//static const char *tags[] = { " ﮟ ", "  ", "  ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " ﱘ " };
static const char *tags[] = { " ﮟ ", "  ", "  ", " ﱘ " };

static const Rule rules[] = {
	/* class        instance    title    tags mask isfloating  Centre     monitor */
	{ "Alacritty",  NULL,       NULL,    0,        0,     	   1,		  -1 },
	{ "Gimp",       NULL,       NULL,    0,        1,          0,         -1 },
	{ "Firefox",    NULL,       NULL,    1 << 8,   0,          0,         -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "靖",      tile },    /* first entry is default */
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
#define STATUSBAR "dwmblocks"

/* General Commands */
static char dmenumon[2]             = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]       = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]        = { "alacritty", NULL };
static const char *firefoxcmd[]     = { "firefox", NULL };
static const char *emacscmd[]       = { "emacs", NULL };
static const char *screenshotcmd[]  = { "flameshot", "gui", NULL };

/* Media Control Commands */
static const char *cmdplay[]    = { "playerctl", "-a", "play-pause", NULL };
static const char *cmdnxt[]     = { "playerctl", "-a", "next", NULL };
static const char *cmdprv[]     = { "playerctl", "-a", "previous", NULL };
static Key keys[] = {

/*
 
    ORIGINAL KEYSBINDINGS - for reference when/if i want to use them 

	 modifier                     key        function        argument 
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
*/
	/* modifier                     key                         function        argument */
	{ MODKEY,                       XK_n,                       spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,                       spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_f,                       spawn,          {.v = firefoxcmd } },
	{ MODKEY,                       XK_e,                       spawn,          {.v = emacscmd} },
	{ MODKEY,                       XK_s,                       spawn,          {.v = screenshotcmd} },
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
    { 0,                            XF86XK_AudioMute,           spawn,          SHCMD("amixer set Master togglemute; pkill -RTMIN+11 dwmblocks") },
    { 0,                            XF86XK_AudioPlay,           spawn,          {.v = cmdplay } },
    { 0,                            XF86XK_AudioPrev,           spawn,          {.v = cmdprv } },
    { 0,                            XF86XK_AudioNext,           spawn,          {.v = cmdnxt } },
    { 0,                            XF86XK_MonBrightnessUp,     spawn,          SHCMD("xbacklight -time 0 -inc 10; pkill -RTMIN+12 dwmblocks") },
    { 0,                            XF86XK_MonBrightnessDown,   spawn,          SHCMD("xbacklight -time 0 -dec 10; pkill -RTMIN+12 dwmblocks") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask          button          function        argument */
	{ ClkLtSymbol,          0,                  Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                  Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                  Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                  Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,                  Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,                  Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,                  Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,                  Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,             Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,   Button1,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,             Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                  Button1,        view,           {0} },
	{ ClkTagBar,            0,                  Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,             Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,             Button3,        toggletag,      {0} }, 
};
