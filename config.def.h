/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char buttonbar[]       = "";
#define ICONSIZE (bh - 10)   /* icon size */
#define ICONSPACING 10 /* space between icon and title */
static const char *fonts[]          = { "NotoSans Nerd Font:size=11:style=Medium",
										"JetBrainsMono Nerd Font:size=9:style=ExtraBold" };
static const char col_gray1[]       = "#1e1e2e";
static const char col_gray2[]       = "#45475e";
static const char col_gray3[]       = "#bac2de";
static const char col_gray4[]       = "#cdd6f4";
static const char col_yellow[]		= "#f9e2af";
static const char col_green[]		= "#a6e3a1";
static const char col_blue[]		= "#89b4fa";
static const char col_magenta[]		= "#cba6f7";
static const char col_sel[]         = "#004466";
static const char *colors[][3]      = {
	[SchemeNorm]		= { col_gray3, 		col_gray1, 	col_gray2 },
	[SchemeSel]			= { col_gray4, 		col_sel,  	col_blue },
	[SchemeFloat]		= { col_gray3, 		col_gray1, 	col_green },
	[SchemeStatus]		= { col_green, 		col_gray1, 	col_green },
	[SchemeStButton]	= { col_blue, 		col_gray1, 	col_green },
	[SchemeTagsEmpty]	= { col_gray2, 		col_gray1, 	col_gray1 },
	[SchemeTagsOcc]		= { col_magenta,	col_gray1,	col_gray1 },
	[SchemeTagsSel]		= { col_gray4,		col_sel,	col_gray1 },
	[SchemeLtSym]		= { col_yellow,		col_gray1,	col_gray1 },
};

static const unsigned int baralpha = 0xc0;
static const unsigned int borderalpha = OPAQUE;

static const unsigned int alphas[][3]      = {
	[SchemeNorm]		= { OPAQUE, baralpha, borderalpha },
	[SchemeSel]			= { OPAQUE, baralpha, borderalpha },
	[SchemeFloat]		= { OPAQUE, baralpha, borderalpha },
	[SchemeStatus]		= { OPAQUE, baralpha, borderalpha },
	[SchemeStButton]	= { OPAQUE, baralpha, borderalpha },
	[SchemeTagsEmpty]	= { OPAQUE, baralpha, borderalpha },
	[SchemeTagsOcc]		= { OPAQUE, baralpha, borderalpha },
	[SchemeTagsSel]		= { OPAQUE, baralpha, borderalpha },
	[SchemeLtSym]		= { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Lxappearance", .isfloating = 1 },
	{ .class = "Firefox", .tags = 1 << 1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachmode         = 2;        /* 0 master (default), 1 = above, 2 = aside, 3 = below, 4 = bottom */
static int floatposgrid_x           = 5;        /* float grid columns */
static int floatposgrid_y           = 5;        /* float grid rows */
static const char *toggle_float_pos      = "50% 50% 80% 80%"; // default floating position when triggering togglefloating

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ ":::",      gaplessgrid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

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
	{ MODKEY,                       XK_bracketright,      incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,      incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	{ MODKEY|ControlMask,           XK_g,      defaultgaps,    {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ ALTKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ ALTKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ ALTKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ ALTKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ ALTKEY|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[4]} },
	{ ALTKEY,                       XK_d,      setlayout,      {.v = &layouts[5]} },
	{ ALTKEY,                       XK_b,      setlayout,      {.v = &layouts[6]} },
	{ ALTKEY|ShiftMask,             XK_b,      setlayout,      {.v = &layouts[7]} },
	{ ALTKEY,                       XK_g,      setlayout,      {.v = &layouts[8]} },
	{ ALTKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[9]} },
	{ ALTKEY,                       XK_n,      setlayout,      {.v = &layouts[10]} },
	{ ALTKEY,                       XK_n,      setlayout,      {.v = &layouts[11]} },
	{ ALTKEY,                       XK_c,      setlayout,      {.v = &layouts[12]} },
	{ ALTKEY|ShiftMask,             XK_c,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY,	                	XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY,                       XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
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


static const char *roficmd[]  = { "rofi", "-show", "drun", NULL };

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,			0,				Button1,		spawn,			{.v = roficmd } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

