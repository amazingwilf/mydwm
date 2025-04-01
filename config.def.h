/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx	= 3;
static const unsigned int snap		= 32;

static const unsigned int gappih	= 10; 
static const unsigned int gappiv	= 10;
static const unsigned int gappoh	= 20;
static const unsigned int gappov	= 20;
static int smartgaps				= 1; 

static const int showbar			= 1; 
static const int topbar				= 1;
static const int user_bh			= 6;

#define ICONSIZE (bh - 12)
#define ICONSPACING 10

static const char *fonts[]			= { "NotoSans Nerd Font:size=12",
										"JetBrainsMono Nerd Font:size=10:style=ExtraBold" };

#include "termcolors.h"

static char c000000[]				= "#000000";

static char normfgcolor[]			= "#bbbbbb";
static char normbgcolor[]			= "#222222";
static char normbordercolor[]		= "#444444";

static char selfgcolor[]			= "#eeeeee";
static char selbgcolor[]			= "#005577";
static char selbordercolor[]		= "#005577";

static char floatfgcolor[]			= "#bbbbbb";
static char floatbgcolor[]			= "#222222";
static char floatbordercolor[]		= "#005577";

static char scratchfgcolor[]		= "#bbbbbb";
static char scratchbgcolor[]		= "#222222";
static char scratchbordercolor[]	= "#eeeeee";

static char tagsnormfgcolor[]		= "#bbbbbb";
static char tagsnormbgcolor[]		= "#222222";

static char tagsselfgcolor[]		= "#eeeeee";
static char tagsselbgcolor[]		= "#005577";

static char ltsymbolfgcolor[]		= "#eeeeee";
static char ltsymbolbgcolor[]		= "#222222";


static char *colors[][3] = {
       [SchemeNorm]		= { normfgcolor,		normbgcolor,		normbordercolor },
       [SchemeSel]		= { selfgcolor,			selbgcolor,			selbordercolor },
       [SchemeFloat]	= { floatfgcolor,		floatbgcolor,		floatbordercolor },
       [SchemeScratch]	= { scratchfgcolor,		scratchbgcolor,		scratchbordercolor },
       [SchemeTagsNorm]	= { tagsnormfgcolor,	tagsnormbgcolor,	c000000 },
       [SchemeTagsSel]	= { tagsselfgcolor,		tagsselbgcolor,		c000000 },
       [SchemeLtSymbol]	= { ltsymbolfgcolor,	ltsymbolbgcolor,	c000000 },
};

static const char *const autostart[] = {
	"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"nitrogen", "--restore", NULL,
	"sxhkd", "-c", "/home/david/.config/dwm/sxhkdrc", NULL,
	"dunst", NULL,
	"picom", "-b", NULL,
	"dwmblocks", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Lxappearance", .isfloating = 1, .iscentered = 1 },
	{ .class = "pavucontrol", .isfloating = 1, .floatpos = "50% 50% 60% 80%" },
	{ .class = "firefox", .tags = 1 << 1 },
	{ .class = "Thunar", .tags = 1 << 2 },
	{ .class = "Chromium", .tags = 1 << 3 },
	{ .class = "com.mitchellh.ghostty", .isterminal = 1 },
	{ .title = "Event Tester", .noswallow = 1 },
	{ .instance = "floaterm", .isfloating = 1, .floatpos = "50% 50% 90% 90%" },
	{ .instance = "spterm", .scratchkey = 't', .isfloating = 1, .floatpos = "50% 50% 85% 85%" },
};

/* layout(s) */
static const float mfact			= 0.50; 
static const int nmaster			= 1; 
static const int resizehints		= 0;
static const int lockfullscreen 	= 1;
static const int swallowfloating	= 0;   
static const int swterminheritfs	= 1;   
static int floatposgrid_x			= 5;
static int floatposgrid_y			= 5;

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[]	= {
	{ "[]=",	tile },    /* first entry is default */
	{ "><>",	NULL },    /* no layout function means floating behavior */
	{ "[M]",	monocle },
	{ "[@]",	spiral },
	{ "[\\]",	dwindle },
	{ "D[]",	deck },
	{ "TTT",	bstack },
	{ "===",	bstackhoriz },
	{ "HHH",	grid },
	{ "###",	nrowgrid },
	{ "---",	horizgrid },
	{ ":::",	gaplessgrid },
	{ "|M|",	centeredmaster },
	{ ">M>",	centeredfloatingmaster },
	{ NULL,		NULL },
};

#define STATUSBAR "dwmblocks"

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SCRATCHKEYS(KEY,CMD) \
	{ MODKEY,				KEY,		togglescratch,		{.v = CMD} }, \
	{ MODKEY|ShiftMask,		KEY,		removescratch,		{.v = CMD} }, \
	{ MODKEY|ControlMask,	KEY,		setscratch,			{.v = CMD} },

static const char *sptermcmd[] = { "t", "ghostty", "--x11-instance-name=spterm", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },

	{ MODKEY,                       XK_period, incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_comma,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_g,      defaultgaps,    {0} },

	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY|ControlMask,			XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_x,      xrdb,           {.v = NULL } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },

	SCRATCHKEYS(					XK_grave,                  sptermcmd)

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
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

