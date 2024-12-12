/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 0;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static int gaps                            = 1;  /* 1 means gaps between windows are added */
static const unsigned int gappx            = 10; /* gap pixel between windows */
static const unsigned int borderpx         = 0;  /* border pixel of windows */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"monospace:size=10"};
static const float rootcolor[]             = COLOR(0x000000ff);
static const float unfocuseddim[]            = COLOR(0x0000008c);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xbbbbbbff, 0x222222ff, 0x444444ff },
	[SchemeSel]  = { 0xeeeeeeff, 0x005577ff, 0x005577ff },
	[SchemeUrg]  = { 0,          0,          0x770000ff },
};

/* tagging - TAGCOUNT must be no greater than 31 */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id     title                       tags mask     isfloating   isterm    noswallow neverdim      monitor */
	/* examples: */
	{ "Gimp_EXAMPLE",     NULL,                 0,            1,           0,         0,       0,           -1 }, /* Start on currently visible tags floating, not tiled */
	{ "firefox",          NULL,                 1 << 2,       0,           0,         0,       0,           -1 }, /* Start on ONLY tag "9" */
	{ "librewolf",        NULL,                 1 << 2,       0,           0,         0,       0,           -1 }, /* Start on ONLY tag "9" */
    { NULL,     "Wayland Output Mirror.*",      0,            0,           0,         0,       1,           -1 },
    { "mpv",              NULL,                 0,            0,           0,         0,       1,           -1 },
    { "foot",             NULL,                 0,            0,           1,         0,       0,           -1 },
    { NULL,               ".*floatterm.*",      0,            1,           1,         0,       0,           -1 },
    { NULL,               "Picture-in-Picture", 0,            1,           0,         0,       0,           -1 },
    { "wev",              NULL,                 0,            1,           0,         1,       0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	{ "HDMI-A-2", 0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
    .layout = "real-prog-dvorak",
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_ALT

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    -1, KEY,            remembertagsview,{.i = TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  -1, KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,-1,SKEY,toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = {"footclient", NULL};
static const char *menucmd[] = {"footclient", "-T", "floatterm", "-w", "700x200", "frun", NULL};
static const char *openbm[]  = {"footclient", "-T", "floatterm", "-w", "800x400", "bm-open", NULL};
static const char *openbmf[] = {"footclient", "-T", "floatterm", "-w", "800x400", "bm-open", "-f", NULL};
static const char *openbmk[] = {"footclient", "-T", "floatterm", "-w", "800x400", "bm-open", "-k", NULL};
static const char *shotful[] = {"wshot", NULL};
static const char *shotsel[] = {"wshot", "-s", NULL};
static const char *castful[] = {"wcast", NULL};
static const char *castsel[] = {"wcast", "-s", NULL};
static const char *volincr[] = {"wpctl", "set-volume", "-l", "1.0", "@DEFAULT_AUDIO_SINK@", "2%+", NULL};
static const char *voldecr[] = {"wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "2%-", NULL};
static const char *volmute[] = {"wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL};
static const char *micmute[] = {"wpctl", "set-mute", "@DEFAULT_AUDIO_SOURCE@", "toggle", NULL};
static const char *musprev[] = {"notif-mpc", "prev", NULL};
static const char *musnext[] = {"notif-mpc", "next", NULL};
static const char *mustggl[] = {"notif-mpc", "toggle", NULL};
static const char *mussngl[] = {"notif-mpc", "single", NULL};
static const char *musrept[] = {"notif-mpc", "repeat", NULL};
static const char *musrand[] = {"notif-mpc", "random", NULL};
static const char *musincv[] = {"mpc", "volume", "+5", NULL};
static const char *musdecv[] = {"mpc", "volume", "-5", NULL};
static const char *musstat[] = {"notif-mpc", NULL};
static const char *ntfwifi[] = {"notif-wifi-blth", "wlan", NULL};
static const char *ntfblth[] = {"notif-wifi-blth", "bluetooth", NULL};

#include "shiftview.c"

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                      chain, key                          function        argument */
	{ MODKEY,                           -1, XKB_KEY_p,                    spawn,          {.v = menucmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_Return,               spawn,          {.v = termcmd} },
	{ MODKEY,                           -1, XKB_KEY_b,                    togglebar,      {0} },
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, -1, XKB_KEY_less,             shiftview,      { .i = -1 } },
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, -1, XKB_KEY_greater,          shiftview,      { .i = 1 } },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_p,                    spawn,          {.v = musprev} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_n,                    spawn,          {.v = musnext} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_t,                    spawn,          {.v = mustggl} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_s,                    spawn,          {.v = mussngl} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_r,                    spawn,          {.v = musrept} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_z,                    spawn,          {.v = musrand} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_m,                    spawn,          {.v = musstat} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_plus,                 spawn,          {.v = musincv} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_m, XKB_KEY_minus,                spawn,          {.v = musdecv} },
    { 0,                                -1, XKB_KEY_XF86AudioRaiseVolume, spawn,          {.v = volincr} },
    { 0,                                -1, XKB_KEY_XF86AudioLowerVolume, spawn,          {.v = voldecr} },
    { 0,                                -1, XKB_KEY_XF86AudioMute,        spawn,          {.v = volmute} },
    { 0,                                -1, XKB_KEY_XF86AudioMicMute,     spawn,          {.v = micmute} },
    { 0,                                -1, XKB_KEY_XF86WLAN,             spawn,          {.v = ntfwifi} },
    { 0,                                -1, XKB_KEY_XF86Bluetooth,        spawn,          {.v = ntfblth} },
    { WLR_MODIFIER_LOGO,                -1, XKB_KEY_Print,                spawn,          {.v = shotful} },
    { 0,                                -1, XKB_KEY_Print,                regions,        {.v = shotsel} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_f, XKB_KEY_Print,                spawn,          {.v = castful} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_s, XKB_KEY_Print,                regions,        {.v = castsel} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_b, XKB_KEY_k,                    spawn,          {.v = openbmk} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_b, XKB_KEY_f,                    spawn,          {.v = openbmf} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_b, XKB_KEY_b,                    spawn,          {.v = openbm}  },
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_h,                    focusto,        {.i = 0}  }, // j (m)
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_t,                    focusto,        {.i = 1}  }, // k
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_n,                    focusto,        {.i = 2}  }, // l
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_s,                    focusto,        {.i = -1} }, // ;
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_g,                    swapstack,      {.i = 0}  }, // u (m)
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_c,                    swapstack,      {.i = 1}  }, // i
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_r,                    swapstack,      {.i = 2}  }, // o
    { MODKEY|WLR_MODIFIER_CTRL,         -1, XKB_KEY_l,                    swapstack,      {.i = -1} }, // p
    { MODKEY,                           -1, XKB_KEY_Down,                 focusstack,     {.i = +1} }, // j
    { MODKEY,                           -1, XKB_KEY_Up,                   focusstack,     {.i = -1} }, // k
    { MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_Down,                 relativeswap,   {.i = +1} }, // J
    { MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_Up,                   relativeswap,   {.i = -1} }, // K
	{ MODKEY,                           -1, XKB_KEY_i,                    incnmaster,     {.i = +1} },
	{ MODKEY,                           -1, XKB_KEY_d,                    incnmaster,     {.i = -1} },
	{ MODKEY,                           -1, XKB_KEY_h,                    setmfact,       {.f = -0.05f} },
	{ MODKEY,                           -1, XKB_KEY_l,                    setmfact,       {.f = +0.05f} },
	{ MODKEY,                           -1, XKB_KEY_Return,               zoom,           {0} },
	{ MODKEY,                           -1, XKB_KEY_Tab,                  view,           {0} },
	{ MODKEY,                           -1, XKB_KEY_g,                    togglegaps,     {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_C,                    killclient,     {0} },
	{ MODKEY,                           -1, XKB_KEY_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                           -1, XKB_KEY_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                           -1, XKB_KEY_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                           -1, XKB_KEY_space,                setlayout,      {0} },
	{ MODKEY, 		                    -1, XKB_KEY_apostrophe,           toggledimming,  {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_space,                togglefloating, {0} },
	{ MODKEY,                           -1, XKB_KEY_e,                    togglefullscreen, {0} },
	{ MODKEY,                           -1, XKB_KEY_0,                    view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_parenright,           tag,            {.ui = ~0} },
	{ MODKEY,                           -1, XKB_KEY_comma,                focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                           -1, XKB_KEY_period,               focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_less,                 tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_greater,              tagmon,         {.i = WLR_DIRECTION_RIGHT} },
    { WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_g,                    movetocardinaldir,  {.ui = DIR_NW} }, // u
	{ WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_c,                    movetocardinaldir,  {.ui = DIR_N}  }, // i
    { WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_r,                    movetocardinaldir,  {.ui = DIR_NE} }, // o
    { WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_h,                    movetocardinaldir,  {.ui = DIR_W}  }, // j
    { WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_t,                    movetocardinaldir,  {.ui = DIR_C}  }, // k
	{ WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_n,                    movetocardinaldir,  {.ui = DIR_E}  }, // l
    { WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_m,                    movetocardinaldir,  {.ui = DIR_SW} }, // m
	{ WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_w,                    movetocardinaldir,  {.ui = DIR_S}  }, // ,
    { WLR_MODIFIER_LOGO,         XKB_KEY_w, XKB_KEY_v,                    movetocardinaldir,  {.ui = DIR_SE} }, // .
	TAGKEYS(         XKB_KEY_plus,          XKB_KEY_1,               0),
	TAGKEYS(         XKB_KEY_bracketleft,   XKB_KEY_2,               1),
	TAGKEYS(         XKB_KEY_braceleft,     XKB_KEY_3,               2),
	TAGKEYS(         XKB_KEY_parenleft,     XKB_KEY_4,               3),
	TAGKEYS(         XKB_KEY_ampersand,     XKB_KEY_5,               4),
	TAGKEYS(         XKB_KEY_equal,         XKB_KEY_6,               5),
	TAGKEYS(         XKB_KEY_parenright,    XKB_KEY_7,               6),
	TAGKEYS(         XKB_KEY_braceright,    XKB_KEY_8,               7),
	TAGKEYS(         XKB_KEY_bracketright,  XKB_KEY_9,               8),
	{ MODKEY|WLR_MODIFIER_SHIFT,        -1, XKB_KEY_Q,                    quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,-1,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,-1,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, 0, BTN_MIDDLE, toggledimmingclient, {0} },
};
