# --------------------------------------------------------
# irsend.sh - IR Code Sender Script
# Version: 2.0
# Author: Simon
# Co-Author: ChatGPT von OpenAI
# Beschreibung: Dieses Skript sendet IR-Codes über ein Netzwerk
#              mithilfe von Netcat. Es unterstützt verschiedene
#              Sender-Makros und Lautstärkeregelung.
# Verwendung: ./irsend.sh [MACRO|KEY_CODE ...]
# 
# Hinweis: Dieses Skript wurde mit Unterstützung von ChatGPT zur Automatisierung und Optimierung der IR-Code-Übertragung erstellt. (•̀ᴗ•́)و ̑̑

# --------------------------------------------------------

#!/bin/bash

# Variablen für IP und Port
IP="192.168.43.77"
PORT=23

# IR-Codes
declare -A CODES=(
    [KEY_POWER]=0xFE50AF
    [KEY_MUTE]=0xFE0AF5
    [KEY_DTV]=0xFE807F
    [KEY_RADIO]=0xFE00FF
    [KEY_USB]=0xFE20DF
    [KEY_DVD]=0xFEA05F
    [KEY_1]=0xFE708F
    [KEY_2]=0xFE609F
    [KEY_3]=0xFEF00F
    [KEY_4]=0xFE48B7
    [KEY_5]=0xFEE01F
    [KEY_6]=0xFEC837
    [KEY_7]=0xFE6897
    [KEY_8]=0xFE40BF
    [KEY_9]=0xFEE817
    [KEY_0]=0xFE58A7
    [KEY_RETURN]=0xFED827
    [KEY_VOLUP]=0xFE7887
    [KEY_VOLDOWN]=0xFEFA05
    [KEY_CHUP]=0xFEF807
    [KEY_CHDOWN]=0xFE3AC5
    [KEY_PMODE]=0xFE906F
    [KEY_SMODE]=0xFEB04F
    [KEY_FAV]=0xFE08F7
    [KEY_MENU]=0xFEEA15
    [KEY_EXIT]=0xFE728D
    [KEY_UP]=0xFE7A85
    [KEY_DOWN]=0xFE6A95
    [KEY_LEFT]=0xFEDA25
    [KEY_RIGHT]=0xFE1AE5
    [KEY_OKAY]=0xFE5AA5
    [KEY_SRC]=0xFECA35
    [KEY_INFO]=0xFED02F
    [KEY_SLEEP]=0xFEB24D
    [KEY_AUDIO]=0xFE32CD
    [KEY_SUBS]=0xFE22DD
    [KEY_TXT]=0xFE2AD5
    [KEY_TXTHOLD]=0xFE9867
    [KEY_TXTZOOM]=0xFEA25D
    [KEY_PICOFF]=0xFE18E7
    [KEY_RECORD]=0xFEAA55
    [KEY_PREV]=0xFEE21D
    [KEY_NEXT]=0xFE629D
    [KEY_STOP]=0xFE30CF
    [KEY_RECLIST]=0xFE9A65
    [KEY_BACK]=0x0
    [KEY_FORE]=0xFE52AD
    [KEY_PLAY]=0xFEF20D
    [KEY_RED]=0x0
    [KEY_GREEN]=0xFE02FD
    [KEY_YELLOW]=0xFE12ED
    [KEY_BLUE]=0xFEBA45
)

# Sender-Makros
declare -A MACROS=(
    [_ARD]="KEY_0 KEY_0 KEY_0 KEY_1"
    [_SWR_FERNSEHEN]="KEY_0 KEY_0 KEY_0 KEY_2"
    [_WDR]="KEY_0 KEY_0 KEY_0 KEY_3"
    [_SR_ALT]="KEY_0 KEY_0 KEY_0 KEY_4"
    [_BR]="KEY_0 KEY_0 KEY_0 KEY_5"
    [_NDR]="KEY_0 KEY_0 KEY_0 KEY_6"
    [_MDR]="KEY_0 KEY_0 KEY_0 KEY_7"
    [_HR_ALT]="KEY_0 KEY_0 KEY_1 KEY_0"
    [_SWR_TOT]="KEY_0 KEY_0 KEY_1 KEY_2"
    [_FLENSBURG]="KEY_0 KEY_0 KEY_1 KEY_5"
    [_123TV]="KEY_0 KEY_0 KEY_3 KEY_4"
    [_BBC_WORLD]="KEY_0 KEY_0 KEY_3 KEY_6"
    [_TV5]="KEY_0 KEY_0 KEY_3 KEY_7"
    [_NITRO]="KEY_0 KEY_0 KEY_3 KEY_8"
    [_TLC]="KEY_0 KEY_0 KEY_3 KEY_9"
    [_TOGGO]="KEY_0 KEY_0 KEY_4 KEY_0"
    [_CHANNEL21]="KEY_0 KEY_0 KEY_4 KEY_1"
    [_SHOPLC]="KEY_0 KEY_0 KEY_4 KEY_2"
    [_HSE]="KEY_0 KEY_0 KEY_4 KEY_3"
    [_HOPETV]="KEY_0 KEY_0 KEY_4 KEY_4"
    [_CNN]="KEY_0 KEY_0 KEY_4 KEY_5"
    [_JUWELOTV]="KEY_0 KEY_0 KEY_4 KEY_6"
    [_DF1_TOT]="KEY_0 KEY_0 KEY_4 KEY_7"
    [_EURONEWS]="KEY_0 KEY_0 KEY_4 KEY_8"
    [_TAGESSCHAU24]="KEY_0 KEY_0 KEY_7 KEY_4"
    [_ARD_ALPHA]="KEY_0 KEY_0 KEY_7 KEY_5"
    [_SR]="KEY_0 KEY_0 KEY_7 KEY_6"
    [_ONE]="KEY_0 KEY_0 KEY_8 KEY_0"
    [_QVCSTYLE]="KEY_0 KEY_0 KEY_8 KEY_2"
    [_123TV_ALT]="KEY_0 KEY_0 KEY_8 KEY_5"
    [_QVC2]="KEY_0 KEY_0 KEY_8 KEY_6"
    [_SONNENKLARTV]="KEY_0 KEY_0 KEY_8 KEY_9"
    [_HSEEXTRA]="KEY_0 KEY_0 KEY_9 KEY_2"
    [_ARTE]="KEY_0 KEY_0 KEY_9 KEY_5"
    [_HR]="KEY_0 KEY_0 KEY_9 KEY_6"
    [_SHOPLC_ALT]="KEY_0 KEY_0 KEY_9 KEY_9"
    [_SIXX]="KEY_0 KEY_1 KEY_1 KEY_4"
    [_TELE_5]="KEY_0 KEY_1 KEY_1 KEY_5"
    [_EUROSPORT]="KEY_0 KEY_1 KEY_1 KEY_6"
    [_PRO_7]="KEY_0 KEY_1 KEY_1 KEY_7"
    [_KABEL_1]="KEY_0 KEY_1 KEY_1 KEY_8"
    [_WELT]="KEY_0 KEY_1 KEY_1 KEY_9"
    [_RBB]="KEY_0 KEY_1 KEY_2 KEY_0"
    [_ZDF]="KEY_0 KEY_1 KEY_2 KEY_1"
    [_ZDFINFO]="KEY_0 KEY_1 KEY_2 KEY_2"
    [_3SAT_ALT]="KEY_0 KEY_1 KEY_2 KEY_4"
    [_KIKA_ALT]="KEY_0 KEY_1 KEY_2 KEY_5"
    [_ZDFNEO_ALT]="KEY_0 KEY_1 KEY_2 KEY_7"
    [_NDR_FS_HH]="KEY_0 KEY_1 KEY_2 KEY_8"
    [_NDR_FS_SH]="KEY_0 KEY_1 KEY_2 KEY_9"
    [_TV2]="KEY_0 KEY_1 KEY_3 KEY_3"
    [_SYLT1]="KEY_0 KEY_1 KEY_3 KEY_4"
    [_DR1]="KEY_0 KEY_1 KEY_3 KEY_5"
    [_ANIXE_HD]="KEY_0 KEY_1 KEY_3 KEY_6"
    [_RTL]="KEY_0 KEY_1 KEY_3 KEY_8"
    [_SAT_1]="KEY_0 KEY_1 KEY_3 KEY_9"
    [_PHOENIX]="KEY_0 KEY_1 KEY_4 KEY_0"
    [_ZDF_NEO]="KEY_0 KEY_1 KEY_4 KEY_1"
    [_KI_KA]="KEY_0 KEY_1 KEY_4 KEY_2"
    [_DF1]="KEY_0 KEY_1 KEY_6 KEY_1"
    [_HSE_NEW]="KEY_0 KEY_1 KEY_6 KEY_2"
    [_QVC]="KEY_0 KEY_1 KEY_6 KEY_3"
    [_HGTV]="KEY_0 KEY_1 KEY_8 KEY_2"
    [_NICKELODEON]="KEY_0 KEY_1 KEY_8 KEY_4"
    [_N24DOKU]="KEY_0 KEY_1 KEY_8 KEY_6"
    [_CGTN]="KEY_0 KEY_1 KEY_8 KEY_7"
    [_K_TV]="KEY_0 KEY_1 KEY_8 KEY_8"
    [_COMEDY_CENTRAL]="KEY_0 KEY_1 KEY_8 KEY_9"
    [_DMAX]="KEY_0 KEY_1 KEY_9 KEY_1"
    [_VOXUP]="KEY_0 KEY_1 KEY_9 KEY_2"
    [_HSE_ALT]="KEY_0 KEY_1 KEY_9 KEY_3"
    [_DISNEY_CHANNEL]="KEY_0 KEY_1 KEY_9 KEY_4"
    [_MTV]="KEY_0 KEY_1 KEY_9 KEY_6"
    [_DOKUSAT]="KEY_0 KEY_1 KEY_9 KEY_7"
    [_RTLUP]="KEY_0 KEY_1 KEY_9 KEY_8"
    [_SCHLAGER_DELUXE]="KEY_0 KEY_1 KEY_9 KEY_9"
    [_BIBEL-TV]="KEY_0 KEY_2 KEY_0 KEY_0"
    [_SUPER_RTL]="KEY_0 KEY_2 KEY_0 KEY_1"
    [_RTL_II]="KEY_0 KEY_2 KEY_0 KEY_2"
    [_VOX]="KEY_0 KEY_2 KEY_0 KEY_3"
    [_NTV]="KEY_0 KEY_2 KEY_0 KEY_4"
    [_SONNENKLAR_LT]="KEY_0 KEY_2 KEY_0 KEY_6"
    [_SPORT1]="KEY_0 KEY_2 KEY_0 KEY_7"
    [_3SAT]="KEY_0 KEY_2 KEY_1 KEY_9"
    [_KABEL1DOKU]="KEY_0 KEY_2 KEY_2 KEY_1"
    [_QVC2_ALT]="KEY_0 KEY_2 KEY_2 KEY_2"
    [_HSE_EXTRA]="KEY_0 KEY_2 KEY_2 KEY_3"
    [_PROSIEBEN_MAXX]="KEY_0 KEY_2 KEY_2 KEY_4"
    [_SONLIFE]="KEY_0 KEY_2 KEY_2 KEY_5"
    [_DMF]="KEY_0 KEY_2 KEY_2 KEY_6"
    [_DELUXE_MUSIC_TV]="KEY_0 KEY_2 KEY_2 KEY_8"
    [_SAT_1GOLD]="KEY_0 KEY_2 KEY_2 KEY_9"
    [_ASTRO_TV]="KEY_0 KEY_2 KEY_3 KEY_0"
    [_CNBC_EUROPE]="KEY_0 KEY_2 KEY_4 KEY_1"
)

# Lautstärke-Makro für parametrisierten Prozentsatz
_VOLUME() {
    local initial_volume_steps=$1
    local increase_volume_steps=$2

    # Zuerst die Lautstärke auf 0 reduzieren
    for ((i=0; i<initial_volume_steps; i++)); do
        echo "irsend ${CODES[KEY_VOLDOWN]}"
    done
    
    # Dann die Lautstärke erhöhen
    for ((i=0; i<increase_volume_steps; i++)); do
        echo "irsend ${CODES[KEY_VOLUP]}"
    done
    
    # Information einblenden
    echo "irsend ${CODES[KEY_INFO]}"
}


# Befehl zum Senden von IR-Codes
{
    for key in "$@"; do
        if [[ $key == "_VOLUME" ]]; then
            if [[ $# -eq 3 ]]; then
                _VOLUME "$2" "$3"
            else
                echo "Fehler: _VOLUME benötigt genau 2 Parameter (initial_steps und increase_steps)."
                exit 1
            fi
        elif [[ $key == _* ]]; then
            macro_sequence=${MACROS[$key]}
            for code in $macro_sequence; do
                echo "irsend ${CODES[$code]}"
            done
        elif [[ -n "${CODES[$key]}" ]]; then
            echo "irsend ${CODES[$key]}"
        fi
    done
    echo "exit"
} | nc $IP $PORT

