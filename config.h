/*
     _                                               __ _         _     
  __| |_      ___ __ ___             ___ ___  _ __  / _(_) __ _  | |__  
 / _` \ \ /\ / / '_ ` _ \   _____   / __/ _ \| '_ \| |_| |/ _` | | '_ \ 
| (_| |\ V  V /| | | | | | |_____| | (_| (_) | | | |  _| | (_| |_| | | |
 \__,_| \_/\_/ |_| |_| |_|          \___\___/|_| |_|_| |_|\__, (_)_| |_|

*/

#include <X11/XF86keysym.h>

 /* --- SYSTRAY PATCH CONFIG --- */
 static const unsigned int systraypinning = 0;    /* 0: systray follows selected monitor, >0: pin systray to monitor X */
 static const unsigned int systrayonleft = 0;     /* 0: systray in the right corner, >0: systray on left of status text */
 static const unsigned int systrayspacing = 3;    /* systray spacing */
 static const int systrayiconsize = 0;            /* 0: inherit bar height */
 static int showsystray = 1;                      /* 0 means no systray */

/* appearance */
static unsigned int borderpx        = 2;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar                  = 1;        /* 0 means no bar */
static const int showtitle          = 1;        /* 0 means no title */
static const int showtags           = 1;        /* 0 means no tags */
static const int showlayout         = 1;        /* 0 means no layout indicator */
static const int showstatus         = 1;        /* 0 means no status bar */
static const int showfloating       = 0;        /* 0 means no floating indicator */
static int topbar                   = 1;        /* 0 means bottom bar */
static unsigned int baralpha        = 0x33;	/* hexa-decimal 0x00-0xFF */
static unsigned int borderalpha     = OPAQUE;

static char dmenufont[]             = "JetBrainsMono Nerd Font:size=12";
#include "fonts.h" // set font in font.h

static char normbgcolor[]           = "#1f1f1f"; // dark grey
static char normbordercolor[]       = "#60686C"; // light-grey
static char normfgcolor[]           = "#E0E0E0"; // off-white //"#E5B566"; // gold
static char selfgcolor[]            = "#7DD5CF"; // blue
static char selbordercolor[]        = "#7E8D50"; // green
static char selbgcolor[]            = "#AE4142"; // red

static char *colors[][3] = {
       /*               fg           bg           border   */
		[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
		[SchemeSel]  = { selbgcolor,  selfgcolor,  selbordercolor  },
		/* for bar --> {text, background, null} */
		[SchemeStatus]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* status R */
		[SchemeTagsSel]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* tag L selected */
		[SchemeTagsNorm]  = { selbordercolor, normbgcolor,  normbgcolor  }, /* tag L unselected */
		[SchemeInfoSel]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* info M selected */
		[SchemeInfoNorm]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* info M unselected */
};

// #include "/home/adam/.cache/wal/colors-wal-dwm.h"

/* tagging 				       0    1    2    3    4    5    6    7    8	*/
static const char *tags[] = { "", "", "󰝚", "󰈙", "", "", "", "󰵅", "" };
// static const char *tags[] = { "", "", "", "󰈙", "󰊻", "󰴢", "", "", "" };

static const Rule rules[] = {
    /* xprop(1):
     *    WM_CLASS(STRING) = instance, class
     *    WM_NAME(STRING) = title
     */
	/* class                              instance      title       tags mask  is_centered  is_floating  monitor */
	{"kitty",                              NULL,          "btop",      0,          1,            1,            -1},
	{"Gimp",                               NULL,          NULL,        0,          1,            1,            -1},
	{"galculator",                         NULL,          NULL,        0,          1,            1,            -1},
	{"Galculator",                         NULL,          NULL,        0,          1,            1,            -1},
	{"st",                                 NULL,          NULL,        0,          1,            1,            -1},
	{"pwvucontrol",                        NULL,          NULL,        0,          1,            1,            -1},
	{"copyq",                              NULL,          NULL,        0,          1,            1,            -1},
	{"matplotlib",                         NULL,          NULL,        0,          1,            1,            -1},
	{"kitty",                              "floatkitty",  NULL,        0,          1,            1,            -1},
	{"dolphin",                            NULL,          NULL,        0,          1,            1,            -1},
	{"polkit-kde-authentication-agent-1",  NULL,          NULL,        0,          1,            1,            -1},
	{"Thunar",                             NULL,          NULL,        0,          1,            1,            -1},
	{"firefox",                            NULL,          NULL,        1<<1,       0,            0,            -1},
	{"ncmpcpp",                            NULL,          NULL,        1<<2,       1,            0,            -1},
	{"QMPDClient",                         NULL,          NULL,        1<<2,       1,            0,            -1},
	{"com.github.th_ch.youtube_music",     NULL,          NULL,        1<<2,       1,            0,            -1},
	{"vlc",                                NULL,          NULL,        1<<2,       1,            0,            -1},
	{"obs-studio",                         NULL,          NULL,        1<<2,       1,            0,            -1},
	{NULL,                                 NULL,          "Grayjay",   1<<2,       1,            1,            -1},
	{"okular",                             NULL,          NULL,        1<<3,       0,            0,            -1},
	{"libreoffice",                        NULL,          NULL,        1<<3,       0,            0,            -1},
	{"Libreoffice-calc",                   NULL,          NULL,        1<<3,       0,            0,            -1},
	{"teams-for-linux",                    NULL,          NULL,        1<<4,       0,            0,            -1},
	{"outlook-for-linux",                  NULL,          NULL,        1<<4,       0,            0,             1},
	{"Slack",                              NULL,          NULL,        1<<4,       0,            0,            -1},
	{"Virt-manager",                       NULL,          NULL,        1<<5,       0,            1,            -1},
	{"org.remmina.Remmina",                NULL,          NULL,        1<<5,       0,            1,            -1},
	{"org.remmina.Remmina",                NULL,          "latitude",  1<<5,       0,            0,            -1},
	{"krdc",															 NULL,          NULL,				 1<<5,       0,            0,             1},
	{"kitty",                              "tunkitty",    NULL,        1<<6,       0,            0,            -1},
	{"discord",                            NULL,          NULL,        1<<7,       0,            0,            -1},
	{"vesktop",                            NULL,          NULL,        1<<7,       0,            0,            -1},
	{"Signal",                             NULL,          NULL,        1<<7,       0,            0,            -1},
	{"Caprine",                            NULL,          NULL,        1<<7,       1,            1,            -1},
	{"whatsapp-desktop-client",            NULL,          NULL,        1<<7,       1,            1,            -1},
	{"steam",                              NULL,          NULL,        1<<8,       1,            1,            -1},
	{"steam_app_381210",                   NULL,          NULL,        1<<8,       0,            1,            -1},
};

#include "vanitygaps.c"


/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */


static const Layout layouts[] = { /* alt glyphs: 󱡗 󱏋 */
	/* symbol     arrange function */
	{ "[ 󱙷 ]",      spiral },
	{ "[  ]",      tile },    /* first entry is default */
	{ "[ 󰇥 ]",      NULL },    /* no layout function means floating behavior */
	{ "[  ]",      monocle },
	{ "[ > ]",      dwindle },
};


/* key definitions */
#define MODKEY Mod4Mask // windows key
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	/*{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for launching gtk application */
#define GTKCMD(cmd) { .v = (const char*[]){ "/usr/bin/gtk-launch", cmd, NULL } }

#define STATUSBAR "dwmblocks"
#define BROWSER "firefox"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
// static const char *screenshotcmd[] = { "/bin/sh", "-c", "maim -s | xclip -selection clipboard -t image/png", NULL };
static const char *roficmd[]  = { "rofi", "-show", "drun", "-theme", "~/.config/rofi/config.rasi", NULL };
static const char *kittycmd[]  = { "kitty", NULL };
static const char *kittyfloatcmd[]  = { "kitty", "--class", "floatkitty", NULL };
// static const char *flameshotcmd[]  = { "flameshot gui", NULL };
// static const char *copyqcmd[]  = { "copyq menu", NULL };

static const Arg tagexec[] = { /* spawn application when tag is middle-clicked */
	{ .v = termcmd }, /* 1 */
	{ .v = termcmd }, /* 2 */
	{ .v = termcmd }, /* 3 */
	{ .v = termcmd }, /* 4 */
	{ .v = termcmd }, /* 5 */
	{ .v = termcmd }, /* 6 */
	{ .v = termcmd }, /* 7 */
	{ .v = termcmd }, /* 8 */
	{ .v = termcmd }, /* 9 */
    /* GTKCMD("gtkapplication") */
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = kittyfloatcmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = kittycmd } },
//	{ MODKEY|ShiftMask,             XK_s, 	   spawn,          {.v = flameshotcmd } },
	{ MODKEY|ShiftMask,             XK_s, 	   spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_v,	     spawn,          SHCMD("copyq menu") },

	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } }, /* increase # of master windows */
	{ MODKEY|ControlMask,           XK_i,      incnmaster,     {.i = -1 } }, /* decrease # of master windows */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },


	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },


	{ MODKEY|ControlMask|ShiftMask, XK_q,		quit,			{1} },  /* refresh dwm (restartsig) */
	{ MODKEY|ShiftMask,				XK_BackSpace, quit,			{0} }, /* quit dwm */
	{ MODKEY,						XK_q,		killclient,     {0} }, /* quit window */
	{ MODKEY|ShiftMask,				XK_q,		killclient,     {.ui = 1} },  /* kill all windows besides current */
    /* { MODKEY|ShiftMask|ControlMask,  XK_q,	killclient,     {.ui = 2} }, */
	{ MODKEY|ControlMask,			XK_backslash, xrdb,			{.v = NULL } }, /* refresh xrdb; run this when setting new colors */

	/* layouts 
	{ "[ 󱙷 ]",      spiral },
	{ "[  ]",      tile },    
	{ "[ 󰇥 ]",      NULL },    
	{ "[  ]",      monocle },
	{ "[ > ]",      dwindle }, */
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,						XK_t,	   setlayout,	   {.v = &layouts[1]} }, /* focus fullscreen patch */
	{ MODKEY|ShiftMask,				XK_f,	   togglefullscreen, {0} }, /* focus fullscreen patch */
	{ MODKEY,						XK_f,      setlayout,      {.v = &layouts[2]} }, /* monacle */
	{ MODKEY|ShiftMask,				XK_m,      setlayout,      {.v = &layouts[3]} }, /* spiral */
	{ MODKEY|ShiftMask,				XK_t,      setlayout,      {.v = &layouts[4]} }, /* dwindle */
	{ MODKEY|ControlMask,			XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,				XK_space,  togglefloating, {0} },
	{ MODKEY,						XK_space,  zoom,           {0} },
	{ MODKEY|ControlMask,           XK_space,  focusmaster,    {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_s,      togglesticky,   {0} },


/* multi-monitor control */
	{ MODKEY,		     	XK_bracketright,   focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_bracketright,   tagmon,         {.i = -1 } },
	{ MODKEY,			    XK_bracketleft,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_bracketleft,    tagmon,         {.i = +1 } },

/* gaps control */
	{ MODKEY,					XK_minus,  incrgaps,       {.i = -3 } }, /* all */
	{ MODKEY,					XK_equal,  incrgaps,       {.i = +3 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } }, /* inner */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } }, /* outer */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } }, /* inner horiz */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } }, /* inner vert */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } }, /* outer horiz */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } }, /* outer vert */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_minus,  defaultgaps,    {0} },


/* tag keys */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)


/* toggle statusbar pieces individually */
	{ MODKEY|ControlMask,			XK_t,      togglebartitle, {0} },
	{ MODKEY|ControlMask,			XK_s,      togglebarstatus,{0} },
	{ MODKEY|ControlMask,			XK_t,      togglebartags,  {0} },
    { MODKEY|ControlMask,			XK_e,      togglebarcolor, {0} }, /* swaps fg/bg for tag+win */
	{ MODKEY|ControlMask,			XK_r,      togglebarlt,    {0} },
	{ MODKEY|ControlMask,			XK_f,      togglebarfloat, {0} },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },



/* application bindings */
	{ MODKEY,			XK_m,          spawn,      {.v = (const char*[]){ "st", "-e", "termusic", NULL } } },
	{ MODKEY,			XK_w,          spawn,      {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY,			XK_f,          spawn,      {.v = (const char*[]){ "st", "-e", "fff", NULL } } },
	{ MODKEY,			XK_n,          spawn,      {.v = (const char*[]){ "kitty", "nvim", NULL } } },
	{ MODKEY|ShiftMask,	XK_h,          spawn,      {.v = (const char*[]){ "st", "-e", "htop", NULL } } },
	{ MODKEY,			XK_p,          spawn,      {.v = (const char*[]){ "darktable", NULL } } },
	{ MODKEY,			XK_e,          spawn,      {.v = (const char*[]){ "dolphin", NULL } } },
	


/* script launch bindings */
	{ MODKEY|ShiftMask,		XK_n,      spawn,       {.v = (const char*[]){ "dmenunotes", NULL } } },
	{ MODKEY|ShiftMask,		XK_a,      spawn,       {.v = (const char*[]){ "dmenuvids", NULL } } },
	{ MODKEY|ControlMask,	XK_a,      spawn,       {.v = (const char*[]){ "dmenuaudioswitch", NULL } } },
	{ MODKEY|ShiftMask,		XK_d,      spawn,       {.v = (const char*[]){ "rip", NULL } } },
	{ MODKEY,							XK_r,      spawn,       {.v = (const char*[]){ "rec", NULL } } },
	{ MODKEY|ShiftMask,		XK_grave,  spawn,       {.v = (const char*[]){ "define", NULL } } },
	{ MODKEY|ShiftMask,		XK_w,      spawn,       {.v = (const char*[]){ "change-wallpaper", NULL } } },
	{ MODKEY,							XK_F1,     spawn,       SHCMD("screenshot") },
	{ MODKEY|ShiftMask,		XK_F1,     spawn,       SHCMD("screenshot color") },
	{ MODKEY,							XK_F2,     spawn,       {.v = (const char*[]){ "vb", NULL } } },
	{ MODKEY|ShiftMask,		XK_F2,     spawn,       {.v = (const char*[]){ "dmenutemp", NULL } } },
	{ MODKEY,							XK_F3,     spawn,       {.v = (const char*[]){ "phototransfer", NULL } } },


/* other bindings */
	{ 0,					XF86XK_AudioPlay,					spawn,       SHCMD("playerctl play-pause --player=spotify") },
	{ 0,					XF86XK_AudioNext,   			spawn,       SHCMD("playerctl next --player=spotify") },
	{ 0,					XF86XK_AudioPrev,   			spawn,       SHCMD("playerctl previous --player=spotify") },
	{ 0,					XF86XK_AudioMute,  				spawn,       SHCMD("change-volume-cli mute") },
	{ 0,					XF86XK_AudioRaiseVolume,	spawn,       SHCMD("change-volume-cli up") },
	{ 0,					XF86XK_AudioLowerVolume,	spawn,       SHCMD("change-volume-cli down") },
	{ 0,					XF86XK_MonBrightnessUp,		spawn,       SHCMD("brightnessctl s +10%") },
	{ 0,					XF86XK_MonBrightnessDown,	spawn,       SHCMD("brightnessctl s 10%-") },
	{ ControlMask|Mod1Mask,	XK_Delete,     	spawn,       SHCMD("slock-dpms") },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
// #ifndef __OpenBSD__
	// { ClkWinTitle,          0,			Button2,	zoom,           {0} },
	{ ClkStatusText,        0,				Button1,	sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,				Button2,	sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,				Button3,	sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,				Button4,	sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,				Button5,	sigstatusbar,   {.i = 5} },
	{ ClkStatusText,		ShiftMask,		Button1,	sigstatusbar,	{.i = 6} },
	{ ClkStatusText,        ControlMask,	Button1,	sigstatusbar,   {.i = 7} },
	{ ClkStatusText,        ShiftMask,		Button5,	sigstatusbar,   {.i = 8} },
// #endif

	{ ClkStatusText,        ShiftMask,	Button3,	spawn,          SHCMD("kitty micro ~/suckless/dwmblocks/config.h") },
	{ ClkClientWin,			MODKEY,		Button1,	movemouse,      {0} }, /* left click */
	{ ClkClientWin,			MODKEY,		Button2,	defaultgaps,    {0} }, /* middle click */
	{ ClkClientWin,			MODKEY,		Button3,	resizemouse,    {0} }, /* right click */
	{ ClkClientWin,			MODKEY,		Button4,	incrgaps,       {.i = +1} }, /* scroll up */
	{ ClkClientWin,			MODKEY,		Button5,	incrgaps,       {.i = -1} }, /* scroll down */
	{ ClkTagBar,			0,			Button1,	view,           {0} },
	{ ClkTagBar,			0,			Button3,	toggleview,     {0} },
	{ ClkTagBar,			MODKEY,		Button1,	tag,            {0} },
	{ ClkTagBar,			MODKEY,		Button3,	toggletag,      {0} },
	{ ClkRootWin,			0,			Button2,	togglebar,      {0} }, /* hide bar */
};
