# ESP8266 IR Transceiver mit Telnet-API

## Übersicht/home/simon/Arduino/irtransceiver/looser/irtransceiver.ino
Dieses Projekt ermöglicht es dir, einen ESP8266 als IR-Transceiver zu verwenden. Über eine Telnet-Verbindung kannst du IR-Codes senden und empfangen. Die empfangenen Codes können auf deinem Computer in einer Datei oder Datenbank gespeichert werden.

## Benötigte Komponenten
- **ESP8266** (z. B. NodeMCU oder Wemos D1 Mini)
- **IR-LED** (mit Vorwiderstand)
- **IR-Empfänger** (z. B. TSOP4838)
- **Jumper-Kabel**
- **Breadboard** (optional)

## Schaltung
### IR-LED anschließen
1. Verbinde die **Anode (+)** der IR-LED mit dem Pin **D8** des ESP8266.
2. Verbinde die **Kathode (-)** der IR-LED über einen Vorwiderstand (330Ω) mit dem **GND** des ESP8266.

### IR-Empfänger anschließen
1. Verbinde den **VCC** des IR-Empfängers mit dem **3.3V** des ESP8266.
2. Verbinde den **GND** des IR-Empfängers mit dem **GND** des ESP8266.
3. Verbinde den **OUT** des IR-Empfängers mit dem Pin **D6** des ESP8266.

## Netcat-Befehle

### 1. IR-Code senden
Um einen IR-Code zu senden, benutze den folgenden Befehl in der Konsole:

```bash
echo -e "irsend 0xFE5AA5\nexit" | nc 192.168.0.213 23

### 1. IR-Code senden
Um einen IR-Code zu senden, benutze den folgenden Befehl in der Konsole:

```bash
(echo -e "irrecord\n"; sleep 5) | nc 192.168.0.213 23


