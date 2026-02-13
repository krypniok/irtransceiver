/*
 * Sharp TV Modell: 
 * Shutofftime: 1s
 * Powerontime: 16s
*/

#define KEY_POWER   0xFE50AF
#define KEY_MUTE    0xFE0AF5

#define KEY_DTV     0xFE807F
#define KEY_RADIO   0xFE00FF
#define KEY_USB     0xFE20DF
#define KEY_DVD     0xFEA05F

#define KEY_1       0xFE708F
#define KEY_2       0xFE609F
#define KEY_3       0xFEF00F
#define KEY_4       0xFE48B7
#define KEY_5       0xFEE01F
#define KEY_6       0xFEC837
#define KEY_7       0xFE6897
#define KEY_8       0xFE40BF
#define KEY_9       0xFEE817
#define KEY_TVGUIDE 0xFE827D
#define KEY_0       0xFE58A7
#define KEY_RETURN  0xFED827

#define KEY_VOLUP   0xFE7887
#define KEY_VOLDOWN 0xFEFA05

#define KEY_CHUP    0xFEF807
#define KEY_CHDOWN  0xFE3AC5

#define KEY_PMODE   0xFE906F
#define KEY_SMODE   0xFEB04F
#define KEY_FAV     0xFE08F7

#define KEY_MENU    0xFEEA15
#define KEY_EXIT    0xFE728D

#define KEY_UP      0xFE7A85
#define KEY_DOWN    0xFE6A95
#define KEY_LEFT    0xFEDA25
#define KEY_RIGHT   0xFE1AE5
#define KEY_OKAY    0xFE5AA5

#define KEY_SRC     0xFECA35
#define KEY_INFO    0xFED02F

#define KEY_SLEEP   0xFEB24D
#define KEY_AUDIO   0xFE32CD
#define KEY_SUBS    0xFE22DD

#define KEY_TXT     0xFE2AD5
#define KEY_TXTHOLD 0xFE9867
#define KEY_TXTZOOM 0xFEA25D
#define KEY_PICOFF  0xFE18E7

#define KEY_RECORD  0xFEAA55
#define KEY_PREV    0xFEE21D
#define KEY_NEXT    0xFE629D
#define KEY_STOP    0xFE30CF

#define KEY_RECLIST 0xFE9A65
#define KEY_BACK    0x0
#define KEY_FORE    0xFE52AD
#define KEY_PLAY    0xFEF20D

#define KEY_RED     0x0
#define KEY_GREEN   0xFE02FD
#define KEY_YELLOW  0xFE12ED
#define KEY_BLUE    0xFEBA45

/* ------------------------------- */

struct Key {
    uint32_t code;
    const char* name;
};

Key keys[] = {
    {KEY_POWER, "KEY_POWER"},
    {KEY_MUTE, "KEY_MUTE"},
    {KEY_DTV, "KEY_DTV"},
    {KEY_RADIO, "KEY_RADIO"},
    {KEY_USB, "KEY_USB"},
    {KEY_DVD, "KEY_DVD"},
    {KEY_1, "KEY_1"},
    {KEY_2, "KEY_2"},
    {KEY_3, "KEY_3"},
    {KEY_4, "KEY_4"},
    {KEY_5, "KEY_5"},
    {KEY_6, "KEY_6"},
    {KEY_7, "KEY_7"},
    {KEY_8, "KEY_8"},
    {KEY_9, "KEY_9"},
    {KEY_TVGUIDE, "KEY_TVGUIDE"},
    {KEY_0, "KEY_0"},
    {KEY_RETURN, "KEY_RETURN"},
    {KEY_VOLUP, "KEY_VOLUP"},
    {KEY_VOLDOWN, "KEY_VOLDOWN"},
    {KEY_CHUP, "KEY_CHUP"},
    {KEY_CHDOWN, "KEY_CHDOWN"},
    {KEY_PMODE, "KEY_PMODE"},
    {KEY_SMODE, "KEY_SMODE"},
    {KEY_FAV, "KEY_FAV"},
    {KEY_MENU, "KEY_MENU"},
    {KEY_EXIT, "KEY_EXIT"},
    {KEY_UP, "KEY_UP"},
    {KEY_DOWN, "KEY_DOWN"},
    {KEY_LEFT, "KEY_LEFT"},
    {KEY_RIGHT, "KEY_RIGHT"},
    {KEY_OKAY, "KEY_OKAY"},
    {KEY_SRC, "KEY_SRC"},
    {KEY_INFO, "KEY_INFO"},
    {KEY_SLEEP, "KEY_SLEEP"},
    {KEY_AUDIO, "KEY_AUDIO"},
    {KEY_SUBS, "KEY_SUBS"},
    {KEY_TXT, "KEY_TXT"},
    {KEY_TXTHOLD, "KEY_TXTHOLD"},
    {KEY_TXTZOOM, "KEY_TXTZOOM"},
    {KEY_PICOFF, "KEY_PICOFF"},
    {KEY_RECORD, "KEY_RECORD"},
    {KEY_PREV, "KEY_PREV"},
    {KEY_NEXT, "KEY_NEXT"},
    {KEY_STOP, "KEY_STOP"},
    {KEY_RECLIST, "KEY_RECLIST"},
    {KEY_BACK, "KEY_BACK"},
    {KEY_FORE, "KEY_FORE"},
    {KEY_PLAY, "KEY_PLAY"},
    {KEY_RED, "KEY_RED"},
    {KEY_GREEN, "KEY_GREEN"},
    {KEY_YELLOW, "KEY_YELLOW"},
    {KEY_BLUE, "KEY_BLUE"}
};
