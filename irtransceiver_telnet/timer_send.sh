#!/bin/bash

# Überprüfen, ob die richtigen Argumente übergeben wurden
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <hh:mm> <keycode>"
    exit 1
fi

uhrzeit="$1"
keycode="$2"

# Warten bis zur angegebenen Uhrzeit
while [ "$(date +%H:%M)" != "$uhrzeit" ]; do
    sleep 1
done

# Befehl ausführen
bash /home/simon/Arduino/irtransceiver/irsend.sh "$keycode" KEY_INFO

