#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "sharptv.h"

// WLAN-Konfiguration
const char* ssid = "gigacube-07815B";
const char* password = "4jTt8t42m5368633";

IRsend irsend(D8);  // Pin für IR-Sende-LED (D8)
const uint16_t RECV_PIN = D6;  // Pin D6 für den IR-Empfänger
IRrecv irrecv(RECV_PIN);
decode_results results;

// Telnet-Server
WiFiServer server(23);

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

    // WLAN verbinden
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Verbinde mit WLAN...");
    }
    Serial.println("WLAN verbunden!");
    Serial.print("IP-Adresse: ");
    Serial.println(WiFi.localIP());

    server.begin();  // Starte den Telnet-Server
}

void loop() {
    WiFiClient client = server.available();  // Überprüfe auf neue Clients

    if (client) {
        Serial.println("Neuer Client verbunden!");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();  // Lese das eingehende Zeichen
                Serial.write(c);

                if (c == '\n') {
                    // Verarbeite den Befehl
                    if (currentLine.startsWith("irsend ")) {
                        String code = currentLine.substring(7);  // Hole den Hex-Code
                        code.trim();  // Leerzeichen entfernen
                        long hexCode = strtol(code.c_str(), NULL, 16);  // Hex-Code konvertieren
                        if (hexCode != 0) {
                            irsend.sendNEC(hexCode, 32);  // Sende den IR-Code
                            client.println("IR-Signal gesendet: 0x" + String(hexCode, HEX)); // Gebe den gesendeten Code zurück
                        } else {
                            client.println("Unerkannter Code.");
                        }
                    } else if (currentLine.startsWith("irrecord")) {
                        client.println("Warte auf IR-Code...");
                        irrecv.enableIRIn();     // Startet IR-Empfänger
                        unsigned long startTime = millis();
                        bool codeReceived = false;

                        while (millis() - startTime < 5000) { // 5 Sekunden warten
                            yield();  
                            if (irrecv.decode(&results)) {
                                if (results.value != 0xFFFFFFFFFFFFFFFF && results.value != 0x0) {
                                    Serial.print("Empfangener Code: 0x");
                                    Serial.println(results.value, HEX);
                                    client.print("Empfangener Code: 0x");
                                    client.println(results.value, HEX);
                                    codeReceived = true;
                                    irrecv.resume();
                                    irrecv.disableIRIn();
                                    break;
                                }
                            }
                            delay(10);
                        }

                        if (!codeReceived) {
                            client.println("Kein IR-Code empfangen oder Timeout erreicht.");
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
                            client.println("GPIO " + String(pin) + " auf " + String(value) + " gesetzt.");
                            Serial.println("GPIO " + String(pin) + " auf " + String(value) + " gesetzt.");
                        } else {
                            client.println("Ungültiges Format. Benutzung: setgpio <pin> <value>");
                        }
                    } else if (currentLine.equals("exit")) {
                        client.println("Server wird beendet.");
                        break;  // Verbindung schließen
                    }
                    currentLine = "";  // Zurücksetzen der Zeile
                
                } else if (c != '\r') {
                    currentLine += c;  // Hänge das Zeichen an die aktuelle Zeile
                }

            }
        }
        client.stop();  // Client-Verbindung beenden
        Serial.println("Client getrennt.");
    }
}
