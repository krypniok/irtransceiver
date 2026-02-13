#!/bin/bash
if [ "$1" == "hdmi" ]; then
    SINK=$(pactl list short sinks | grep hdmi | awk '{print $1}')
elif [ "$1" == "intern" ]; then
    SINK=$(pactl list short sinks | grep analog | awk '{print $1}')
else
    echo "nutzung: $0 [hdmi|intern]"
    exit 1
fi

if [ -n "$SINK" ]; then
    pactl set-default-sink "$SINK"
    echo "soundausgabe auf $1 umgestellt"
else
    echo "kein passendes ausgabegerät gefunden"
fi

