#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "sharptv.h"

IRsend irsend(D8);  // Pin für IR-Sende-LED (D8)
const uint16_t RECV_PIN = D6;  // Pin D6 für den IR-Empfänger
IRrecv irrecv(RECV_PIN);
decode_results results;

const int numKeys = sizeof(keys) / sizeof(keys[0]);

const char* getKeyName(uint32_t code) {
    for (int i = 0; i < numKeys; i++) {
        if (keys[i].code == code) {
            return keys[i].name; // Rückgabe des Namens, wenn der Code übereinstimmt
        }
    }
    return "UNKNOWN"; // Rückgabe für nicht erkannte Codes
}

void setup() {
    Serial.begin(115200);
    irsend.begin();          // Startet IR-Sender
    pinMode(D8, OUTPUT);
    pinMode(RECV_PIN, INPUT);

    Serial.println("Bereit. Warte auf Befehle...");
}

String currentLine = "";

void loop() {
    if (Serial.available()) {
        char c = Serial.read();

        if (c == '\n') {
            // Verarbeite den Befehl
            if (currentLine.startsWith("irsend ")) {
                String arg = currentLine.substring(7);  // Argument holen
                arg.trim();
                
                uint32_t hexCode = 0;

                // 1. Suche nach Key-Namen (z.B. KEY_MUTE)
                for (int i = 0; i < numKeys; i++) {
                    if (String(keys[i].name).equalsIgnoreCase(arg)) {
                        hexCode = keys[i].code;
                        break;
                    }
                }

                // 2. Fallback: Hex-Code parsen (z.B. 0xFE0AF5)
                if (hexCode == 0) {
                    hexCode = strtoul(arg.c_str(), NULL, 16);
                }

                if (hexCode != 0) {
                    irsend.sendNEC(hexCode, 32);  // Sende den IR-Code
                    Serial.println("IR-Signal gesendet: 0x" + String(hexCode, HEX)); // Gebe den gesendeten Code zurück
                } else {
                    Serial.println("Unerkannter Code oder Key.");
                }
            } else if (currentLine.startsWith("irrecord")) {
                Serial.println("Warte auf IR-Code...");
                irrecv.enableIRIn();     // Startet IR-Empfänger
                unsigned long startTime = millis();
                bool codeReceived = false;

                while (millis() - startTime < 5000) { // 5 Sekunden warten
                    yield();  
                    if (irrecv.decode(&results)) {
                        if (results.value != 0xFFFFFFFFFFFFFFFF && results.value != 0x0) {
                            Serial.print("Empfangener Code: 0x");
                            Serial.println(results.value, HEX);
                            codeReceived = true;
                            irrecv.resume();
                            irrecv.disableIRIn();
                            break;
                        }
                    }
                    delay(10);
                }

                if (!codeReceived) {
                    Serial.println("Kein IR-Code empfangen oder Timeout erreicht.");
                    irrecv.disableIRIn();
                }

            } else if (currentLine.startsWith("setgpio ")) {
                String args = currentLine.substring(8);
                int secondSpace = args.indexOf(' ');
                if (secondSpace != -1) {
                    String pinStr = args.substring(0, secondSpace);
                    String valueStr = args.substring(secondSpace + 1);
                    int pin = pinStr.toInt();
                    int value = valueStr.toInt();

                    pinMode(pin, OUTPUT); // Default to OUTPUT
                    analogWrite(pin, value);
                    Serial.println("GPIO " + String(pin) + " auf " + String(value) + " gesetzt.");
                } else {
                    Serial.println("Ungültiges Format. Benutzung: setgpio <pin> <value>");
                }
            }
            currentLine = "";  // Zurücksetzen der Zeile
        
        } else if (c != '\r') {
            currentLine += c;  // Hänge das Zeichen an die aktuelle Zeile
        }
    }
}
