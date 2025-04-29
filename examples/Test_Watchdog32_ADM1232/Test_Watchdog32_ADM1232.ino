#include <Watchdog32.h>

const int testWdogPin = 7;  // Pin del jumper
const int ledPin = LED_BUILTIN;  // Pin del LED integrato

unsigned long previousMillis = 0;  // Memorizza l'ultimo aggiornamento del LED
unsigned long previousWdogMillis = 0;  // Memorizza l'ultimo retriggering del watchdog

const long intervalSlow = 1000;  // Intervallo di lampeggio lento (1000 ms)
const long intervalFast = 250;   // Intervallo di lampeggio veloce (250 ms)
const long wdogInterval = 250;   // Intervallo di retriggering del watchdog (250 ms)

int retriggerCount = 0;  // Conteggio dei retriggering del watchdog
const int maxRetriggerCount = 20;  // Numero massimo di retriggering

// Pin di controllo del watchdog
const int triggerPin = 8;  // Sostituisci con il pin corretto
const int enablePin = 9;   // Sostituisci con il pin corretto

Watchdog32 watchdog;  // Istanza del watchdog

void setup() {
  pinMode(testWdogPin, INPUT_PULLUP);  // Configura il pin D7 con pull-up
  pinMode(ledPin, OUTPUT);  // Configura il pin del LED come output

  // Inizializza il watchdog con i pin specificati
  watchdog.retrigger();  // Retriggere il watchdog
  watchdog.begin(triggerPin, enablePin);
  watchdog.retrigger();  // Retriggere il watchdog
  watchdog.enable();  // Abilita il watchdog
  watchdog.retrigger();  // Retriggere il watchdog
}

void loop() {
  unsigned long currentMillis = millis();

  // Controlla lo stato del jumper
  int testWdogState = digitalRead(testWdogPin);

  if (testWdogState == HIGH) {
    // Jumper non inserito: lampeggio lento e retriggering continuo
    if (currentMillis - previousMillis >= intervalSlow) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin));  // Inverte lo stato del LED
    }

    if (currentMillis - previousWdogMillis >= wdogInterval) {
      previousWdogMillis = currentMillis;
      watchdog.retrigger();  // Retriggere il watchdog
    }
    retriggerCount = 0;  // Reset del conteggio
  } else {
    // Jumper inserito: lampeggio veloce e retriggering limitato
    if (currentMillis - previousMillis >= intervalFast) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, !digitalRead(ledPin));  // Inverte lo stato del LED
    }

    if (currentMillis - previousWdogMillis >= wdogInterval && retriggerCount < maxRetriggerCount) {
      previousWdogMillis = currentMillis;
      watchdog.retrigger();  // Retriggere il watchdog
      retriggerCount++;
    }
  }
}
