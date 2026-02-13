# IR Transceiver (Serial/TTY Edition)

Dieses Projekt ermöglicht das Senden und Empfangen von Infrarot-Signalen (speziell für Sharp TVs) über einen ESP8266, der per USB-Seriell-Schnittstelle (TTY) mit einem Linux-PC verbunden ist.

## Hardware
*   ESP8266 (z.B. NodeMCU D1 Mini)
*   IR-Sende-LED an Pin **D8**
*   IR-Empfänger an Pin **D6**

## Installation

### 1. Arduino
1.  Öffne `irtransceiver.ino` in der Arduino IDE.
2.  Stelle sicher, dass `sharptv.h` im selben Ordner liegt.
3.  Installiere die Bibliothek `IRremoteESP8266`.
4.  Lade den Sketch auf den ESP8266 hoch.

### 2. Host-PC (Linux)
1.  Stelle sicher, dass das Skript `irsend.sh` ausführbar ist:
    ```bash
    chmod +x irsend.sh
    ```
2.  Prüfe den seriellen Port in `irsend.sh` (Standard: `/dev/ttyUSB0`).
3.  Stelle sicher, dass dein Benutzer Zugriff auf den seriellen Port hat (meist Gruppe `dialout` oder `uucp`).

## Verwendung

### Über das Skript (CLI / xbindkeys)
Das Skript `irsend.sh` sendet Befehle direkt an die serielle Schnittstelle. Es konfiguriert den Port automatisch so, dass kein Reset des Arduinos ausgelöst wird.

```bash
./irsend.sh KEY_POWER
./irsend.sh KEY_VOLUP
./irsend.sh _ARD  # Makro senden
```

### Direkt über Serial Monitor
Verbinde dich mit einem Terminal-Programm (z.B. Arduino Serial Monitor, PuTTY) mit **115200 Baud**.

Verfügbare Befehle:
*   `irsend KEY_NAME` (z.B. `irsend KEY_MUTE` - Namen siehe `sharptv.h`)
*   `irsend 0xHEXCODE` (z.B. `irsend 0xFE0AF5`)
*   `irrecord` (Startet den Empfangsmodus für 5 Sekunden)
*   `setgpio <PIN> <VALUE>` (Setzt einen GPIO Pin auf einen PWM-Wert)

## Integration in xbindkeys
Beispiel für `.xbindkeysrc`:
```
"bash /home/simon/Arduino/irtransceiver/irsend.sh KEY_VOLUP"
  Alt + F12
```

---
*Refactored & Updated by Gemini*