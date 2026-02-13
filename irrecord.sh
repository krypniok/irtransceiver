#!/bin/bash

# Variablen für IP und Port
IP="192.168.0.213"
PORT=23

# Bekannte Makros
declare -A MACROS=(
    [KEY_POWER]="KEY_POWER"
    [KEY_MUTE]="KEY_MUTE"
    [KEY_DTV]="KEY_DTV"
    [KEY_RADIO]="KEY_RADIO"
    [KEY_USB]="KEY_USB"
    [KEY_DVD]="KEY_DVD"
    [KEY_1]="KEY_1"
    [KEY_2]="KEY_2"
    [KEY_3]="KEY_3"
    [KEY_4]="KEY_4"
    [KEY_5]="KEY_5"
    [KEY_6]="KEY_6"
    [KEY_7]="KEY_7"
    [KEY_8]="KEY_8"
    [KEY_9]="KEY_9"
    [KEY_0]="KEY_0"
    [KEY_RETURN]="KEY_RETURN"
    [KEY_VOLUP]="KEY_VOLUP"
    [KEY_VOLDOWN]="KEY_VOLDOWN"
    [KEY_CHUP]="KEY_CHUP"
    [KEY_CHDOWN]="KEY_CHDOWN"
    [KEY_MENU]="KEY_MENU"
    [KEY_EXIT]="KEY_EXIT"
)

# Datei für die Bash-Variablen
OUTPUT_FILE="ir_codes.sh"

# Erstelle die Bash-Include-Datei
echo "#!/bin/bash" > $OUTPUT_FILE
echo "# IR Codes" >> $OUTPUT_FILE

# Funktion zum Aufnehmen von IR-Codes
record_ir_code() {
    local key=$1
    echo "Warte auf IR-Code für $key..."
    # Sende den irrecord Befehl an den Telnet-Server
    response=$(echo -e "irrecord\nexit" | nc $IP $PORT)

    # Überprüfe die Antwort auf einen empfangenen IR-Code
    if [[ $response == *"0x"* ]]; then
        # Extrahiere den Code und schreibe ihn in die Include-Datei
        ir_code=$(echo "$response" | grep -o "0x[^ ]*")
        echo "Empfangener IR-Code für $key: $ir_code"
        echo "declare -g $key='$ir_code'" >> $OUTPUT_FILE
    else
        echo "Keine Codes empfangen für $key."
    fi
}

# Hauptlogik: alle Makros durchlaufen
for key in "${!MACROS[@]}"; do
    record_ir_code "${MACROS[$key]}"
done

echo "IR-Codes wurden in $OUTPUT_FILE gespeichert."
chmod +x $OUTPUT_FILE

