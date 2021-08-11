/* 			 _____________        [ Original by: ]     					   */
/*			|EEEEEEEEEEEEE|   								   */
/*			|O|  _ \_   _||				Derek Taylor (DistroTube)		   */
/*			|O| | | || |OO|				{					   */
/*			|O| |_| || |OO|					distrotube (youtube)		   */
/*			|O|____/O|_|OO|					dwt1 (gitlab)			   */ 
/*			|DDDDDDDDDDDDD|				}					   */


/* 					[ aaxylotl's ThinkPad flip: ]					   */
/*	   	            ___       ____    _____							   */
/*        /\          /\    \QQ\     /QQRR\  /RRTTT|		Brian Yang (aaxylotl)			   */
/*       /OO\        /AA\    \QQ\   /QQ/\RR\/RR/|TT|		{					   */
/*      /OOOO\      /AAAA\    \QQ\ /QQ/  \RRRR/ |TT|			a-xylotl (github)		   */
/*     /OO/\OO\    /AA/\AA\    >QQXQQ<    >RR/  |TT|			bbbbb#7777 (discord)		   */
/*    /OO/  \OO\  /AA/  \AA\  /QQ/ \QQ\  /RR/   |TT|			bymastermm (deviantart)		   */
/*   /OO/  __\OO\/AA/  __\AA\/QQ/   \QQ\/RR/    |TT|______						   */
/*  /DD/  |EEEEEEEE/  |BBBBBBBB/     \LLLL/     |ZZZZZZZZZ|     }					   */
/*													   */

#include "selfrestart.c"
#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 5;        /* pixel gap between clients */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 7;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Liberation Mono:pixelsize=10", "NotoFontsEmoji:pixelsize=8:antialias=true:autohint=true", "monospace:size=10" };
static const char dmenufont[]       = "Liberation Mono:pixelsize=10";
static const char col_gray1[]       = "#0B2542";
static const char col_gray2[]       = "#111322"; /* border color unfocused windows */
static const char col_gray3[]       = "#96b5b4";
static const char col_gray4[]       = "#c0c5ce";
static const char col_cyan[]        = "#5688C4"; /* border color focused windows and tags */
static const unsigned int baralpha = 0xee;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
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
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "HHH",      grid },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTO
 */
static char *statuscmds[] = { "notify-send Mouse$BUTTON" };
static char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };


static const char *termcmd[]  = { "st", NULL };

static const char *upvol[]    = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *downvol[]  = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mutevol[]  = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle", NULL };	

#include "movestack.c"
static Key keys[] = {
	/* modifier               key              function        argument */
	{ 0,			  XF86XK_AudioRaiseVolume, spawn,  {.v = upvol } },
	{ 0,			  XF86XK_AudioLowerVolume, spawn,  {.v = downvol } },
	{ 0,			  XF86XK_AudioMute, spawn,	   {.v = mutevol } },

	{ MODKEY,                 XK_p, 	   spawn,          {.v = dmenucmd } },
	{ MODKEY,                 XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY,                 XK_b,            togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 }},
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 }},
	{ MODKEY|ShiftMask,       XK_n,            rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,       XK_m,            rotatestack,    {.i = -1 } },
	{ MODKEY,                 XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,                 XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,                 XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,                 XK_d,            incnmaster,     {.i = -1 } },
	{ MODKEY,                 XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,                 XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,       XK_Return,       zoom,           {0} },
	{ MODKEY,                 XK_Tab,          view,           {0} },
	{ MODKEY|ShiftMask,       XK_c,            killclient,     {0} },
	{ MODKEY,                 XK_t,            setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                 XK_f,            setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                 XK_m,            setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                 XK_g,            setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                 XK_u,            setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ControlMask,     XK_comma,        cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,     XK_period,       cyclelayout,    {.i = +1 } },
	{ MODKEY,                 XK_space,        setlayout,      {0} },
	{ MODKEY|ShiftMask,       XK_space,        togglefloating, {0} },
	{ MODKEY,                 XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,       XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                 XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY,                 XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,       XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,       XK_period,       tagmon,         {.i = +1 } },

    	{ MODKEY,                 XK_Print,        spawn,          CMD("deepin-screenshot")  },
	{ MODKEY|ControlMask,       XK_d,          spawn,          CMD("Discord") },
	{ MODKEY|ControlMask,       XK_s,          spawn,          CMD("snap run spotify")   },
	{ MODKEY|ControlMask,       XK_t,          spawn,          CMD("st") },
	{ MODKEY|ControlMask,       XK_c,          spawn,          CMD("chromium") },
	{ MODKEY|ControlMask,       XK_g,          spawn,          CMD("gimp") },
	{ MODKEY|ControlMask,       XK_o,          spawn,          CMD("obs") },

    /* Apps Launched with <SUPER> + <KEYPAD 1-9>  */
	{ MODKEY,                 XK_KP_End,       spawn,          CMD("st -e lynx -cfg=~/.lynx/lynx.cfg -lss=~/.lynx/lynx.lss gopher://distro.tube") },
	{ MODKEY,                 XK_KP_Down,      spawn,          CMD("st -e sh ./scripts/googler-script.sh") },
	{ MODKEY,                 XK_KP_Page_Down, spawn,          CMD("st -e newsboat") },
	{ MODKEY,                 XK_KP_Left,      spawn,          CMD("st -e rtv") },
	{ MODKEY,                 XK_KP_Begin,     spawn,          CMD("st -e neomutt") },
	{ MODKEY,                 XK_KP_Right,     spawn,          CMD("st -e twitch-curses") },
	{ MODKEY,                 XK_KP_Home,      spawn,          CMD("st -e sh ./scripts/haxor-news.sh") },
	{ MODKEY,                 XK_KP_Up,        spawn,          CMD("st -e toot curses") },
	{ MODKEY,                 XK_KP_Page_Up,   spawn,          CMD("st -e sh ./scripts/tig-script.sh") },
	
	
    /* Apps Launched with <SUPER> + <SHIFT> + <KEYPAD 1-9>  */
	{ MODKEY|ShiftMask,       XK_KP_End,       spawn,          CMD("st -e ~/.config/vifm/scripts/vifmrun") },
	{ MODKEY|ShiftMask,       XK_KP_Down,      spawn,          CMD("st -e joplin") },
	{ MODKEY|ShiftMask,       XK_KP_Page_Down, spawn,          CMD("st -e cmus") },
	{ MODKEY|ShiftMask,       XK_KP_Left,      spawn,          CMD("st -e irssi") },
	{ MODKEY|ShiftMask,       XK_KP_Begin,     spawn,          CMD("st -e rtorrent") },
	{ MODKEY|ShiftMask,       XK_KP_Right,     spawn,          CMD("st -e youtube-viewer") },
	{ MODKEY|ShiftMask,       XK_KP_Home,      spawn,          CMD("st -e ncpamixer") },
	{ MODKEY|ShiftMask,       XK_KP_Up,        spawn,          CMD("st -e calcurse") },
	{ MODKEY|ShiftMask,       XK_KP_Page_Up,   spawn,          CMD("st -e vim /home/dt/dwm/config.h") },
	
    /* Apps Launched with <SUPER> + <CONTROL> + <KEYPAD 1-9>  */
	{ MODKEY|ControlMask,     XK_KP_End,       spawn,          CMD("st -e htop") },
	{ MODKEY|ControlMask,     XK_KP_Down,      spawn,          CMD("st -e gtop") },
	{ MODKEY|ControlMask,     XK_KP_Page_Down, spawn,          CMD("st -e nmon") },
	{ MODKEY|ControlMask,     XK_KP_Left,      spawn,          CMD("st -e glances") },
	{ MODKEY|ControlMask,     XK_KP_Begin,     spawn,          CMD("st -e s-tui") },
	{ MODKEY|ControlMask,     XK_KP_Right,     spawn,          CMD("st -e httping -KY --draw-phase localhost") },
	{ MODKEY|ControlMask,     XK_KP_Home,      spawn,          CMD("st -e cmatrix -C cyan") },
	{ MODKEY|ControlMask,     XK_KP_Up,        spawn,          CMD("st -e pianobar") },
	{ MODKEY|ControlMask,     XK_KP_Page_Up,   spawn,          CMD("st -e wopr report.xml") },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,		quit,			{0} },
	{ MODKEY|ShiftMask, 			XK_r, 		self_restart,	{0} },
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

