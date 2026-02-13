#!/bin/bash

# Variablen für den seriellen Port
SERIAL_PORT="/dev/ttyUSB0"  # Passe den Port je nach Bedarf an

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
    # Weitere Makros hier...
)

# Seriellen Port konfigurieren
stty -F $SERIAL_PORT 115200 cs8 -cstopb -parenb  # Anpassen je nach Bedarf

# Funktion zum Senden eines IR-Codes über den seriellen Port
send_ir_code() {
    local code=$1
    echo -n $code > $SERIAL_PORT
}

# Funktion zum Senden eines Makros
send_macro() {
    local macro_name=$1
    local macro="${MACROS[$macro_name]}"
    for key in $macro; do
        code=${CODES[$key]}
        if [ "$code" ]; then
            send_ir_code $code
        fi
    done
}

# Hauptlogik
if [ $# -eq 0 ]; then
    echo "Fehler: Keine Eingabe angegeben. Geben Sie IR-Codes oder Makros an."
    exit 1
fi

for arg in "$@"; do
    if [[ ${CODES[$arg]} ]]; then
        send_ir_code ${CODES[$arg]}
    elif [[ ${MACROS[$arg]} ]]; then
        send_macro $arg
    else
        echo "Unbekannter IR-Code oder Makro: $arg"
    fi
done


