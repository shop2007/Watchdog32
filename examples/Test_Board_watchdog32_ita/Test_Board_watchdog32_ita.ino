#include <Watchdog32.h>   // <<< aggiunta libreria Watchdog32


// Oggetto Watchdog32
Watchdog32 wdog;

#define retrigger_wdog 8  
#define enable_wdog 9   

#define Tracepin3 3
#define Tracepin4 4
#define Tracepin5 5
#define Tracepin6 6

String inputString = "";
bool stringComplete = false;
bool ExitFromMenu = false;
char Cestino;
const long interval = 1000;

unsigned long previousMillis = 0;

void setup() {

  pinMode(Tracepin3, OUTPUT);
  pinMode(Tracepin4, OUTPUT);
  pinMode(Tracepin5, OUTPUT);
  pinMode(Tracepin6, OUTPUT);

  digitalWrite(Tracepin3, LOW);
  digitalWrite(Tracepin4, LOW);
  digitalWrite(Tracepin5, LOW);
  digitalWrite(Tracepin6, LOW);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println();
  Serial.println( F ("|******   SISTEMA RESETTATO  ******|"));
  Serial.println( F (" Sketch build 19092024 "));
  Serial.print( F ("Versione "));Serial.println(__FILE__);
  Serial.println();

  // Inizializzazione Watchdog32
  wdog.begin(retrigger_wdog, enable_wdog);

  wdog.disable();  // Disabilita watchdog all'inizio
}

void(* resetFunc) (void) = 0;

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
  Menu();
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void TypeMenuList(void){
    Serial.println();
    Serial.println( F ("|*******************************************"));
    Serial.println( F ("|             ʘ‿ʘ   Menù   (◡_◡)          "));
    Serial.print( F ("|  Ver. "));Serial.println(__FILE__);
    Serial.println( F ("|  nessuno sta retriggerando il Watchdog32, "));
    Serial.println( F ("|  il led rosso WDOG32 continua a blinkare  "));
    Serial.println( F ("|*******************************************"));
    Serial.println( F ("  0 Reset"));
    Serial.println( F ("  1 retriggera Watchdog32 ogni 100msec"));
    Serial.println( F ("  2 Abilita Watchdog32 senza retriggerare"));
    Serial.println( F ("  3 Abilita, retriggera 5 secondi e poi ferma il retrigger, deve resettare"));
    Serial.println( F ("  4 Abilita, retriggera con tempi crescenti, deve resettare"));
    Serial.println( F (" 99 Torna al loop senza reset"));
}

void Menu() {
  while (!ExitFromMenu) {
    wdog.disable();  // <<< usa libreria
    TypeMenuList();

    while (Serial.available()) {
      Cestino = Serial.read();
    }

    Serial.println();
    while (!Serial.available()) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval/4) {
        previousMillis = currentMillis;
      }
    }

    int CmdMenu = Serial.parseInt();
    Serial.print( F ("ricevuto CmdMenu "));Serial.println(CmdMenu);

    switch (CmdMenu){
      case 0:
        Serial.println( F ("reset tra 1 sec"));
        delay(1000);
        resetFunc();
        delay(100);
        Serial.println( F ("Il reset non ha funzionato"));
      break;

      case 1:
        Azione1();
      break;

      case 2:
        Azione2();
      break;

      case 3:
        Azione3();
      break;

      case 4:
        Azione4();
      break;

      case 99:
        Azione99();
      break;

      default:
        Serial.println( F ("Comando errato! Riprova"));
    }
  }
}

void Azione1(){
  pinMode(retrigger_wdog, OUTPUT);
  Serial.println( F ("  il led rosso della scheda Watchdog32 si deve spegnere"));
  Serial.println( F ("  Arduino non si deve resettare"));
  Serial.println( F ("invia Q quando vuoi per uscire"));
  BlinkretriggerWaitQ(); 
}

void Azione2(){
  Serial.println( F (" il Watchdog32 viene connesso al reset"));
  Serial.println( F (" nessuno retriggera il Watchdog32"));
  Serial.println( F (" il led rosso della scheda Watchdog32 continua a blinkare"));
  Serial.println( F (" togli il jumper W1 e invia Q"));
  BlinkWaitQ();

  delay(1000);
  pinMode(enable_wdog, OUTPUT);
  wdog.enable(); // <<< usa libreria
  Serial.println( F (" inserisci jumper W1, e in un secondo dovrebbe resettarsi Arduino"));
  delay(2000);
  Serial.println( F (" se non si è resettato invia Q"));
  BlinkWaitQ();
  Serial.println( F (" qualcosa non ha funzionato, invia Q per tornare al menu"));
  BlinkWaitQ();
  wdog.disable(); // <<< usa libreria
}

void Azione3(){
  pinMode(retrigger_wdog, OUTPUT);
  Serial.println( F (" il led rosso della scheda Watchdog32 si deve spegnere"));
  Serial.println( F (" inserisci il jumper W1 e poi invia Q per continuare"));
  pinMode(enable_wdog, OUTPUT);
  digitalWrite(Tracepin3, HIGH);

  wdog.enable(); // <<< usa libreria
  BlinkretriggerWaitQ();
  digitalWrite(Tracepin5, LOW);

  Serial.println( F (" tra 5 secondi il retrigger verrà tolto"));
  digitalWrite(Tracepin6, HIGH);
  for(int i = 1; i<6; i++){
    for(int j = 1; j<10; j++){
      wdog.retrigger(); // <<< usa libreria
      delay(100);
      Serial.print(".");
    }
    Serial.print(i);

    if(i==5){
      digitalWrite(Tracepin4, HIGH);
      Serial.println();
      Serial.println( F ("Tra un secondo si deve resettare"));
      Serial.println( F ("Se non resetta invia Q per continuare"));
      digitalWrite(Tracepin6, LOW);
    }
  }

  BlinkWaitQ();
  Serial.println( F (" qualcosa non ha funzionato, invia Q per tornare al menu"));
  BlinkWaitQ();
  wdog.disable(); // <<< usa libreria
  digitalWrite(Tracepin3, LOW);
  digitalWrite(Tracepin4, LOW);
  digitalWrite(Tracepin5, LOW);
  digitalWrite(Tracepin6, LOW);  
}

void Azione4(){
  pinMode(retrigger_wdog, OUTPUT);
  Serial.println( F (" il led rosso della scheda Watchdog32 si deve spegnere"));
  Serial.println( F (" inserisci il jumper W1 e poi invia Q per continuare"));
  
  pinMode(enable_wdog, OUTPUT);
  for(int i = 1; i<10; i++){
    wdog.retrigger(); // <<< usa libreria
    delay(100);
  }

  wdog.enable(); // <<< usa libreria
  BlinkretriggerWaitQ();
  Serial.println( F (" inizio a retriggerare a tempi cresenti,deve resettare"));

  for (int t=250; t<3000; t+=10){
    Serial.println(t);
    wdog.retrigger(); // <<< usa libreria
    wdog.enable();    // <<< usa libreria

    if (t>750) t+=15;
    if (t>1000) t+=50;

    delay(t);

    if (t>1500){
      Serial.println();
      Serial.println("  XXXXXXXXXXXXXXX errore XXXXXXXXXXXXXXX  ");
      Serial.println(" (◡_◡) il tempo ha superato i 1500msec, e non si è generato un Reset");
      Serial.println(" - verifica se è stato inserito il jumper W1");
      Serial.println(" - la scheda non sta funzionando bene");
      Serial.println(" - verifica saldature e montaggio");
      while(1){
        //attesa infinita di un reset
      }
    }
  }

  BlinkWaitQ();
  Serial.println( F (" qualcosa non ha funzionato, invia Q per tornare al menu"));
  BlinkWaitQ();
  wdog.disable(); // <<< usa libreria
}

void Azione99(){
  Serial.println( F ("E' stata scelta l'azione n. 99"));
  delay(2000);
  Serial.println( F ("torno al loop'"));
  delay(2000);
  ExitFromMenu = true;
}

void BlinkWaitQ(void){
  while (1) {
    char inChar = (char)Serial.read();
    if (inChar == 'q' || inChar == 'Q'){
      break;
    }
    delay(500);
  }
}

void BlinkretriggerWaitQ(){
  while (1) {
    digitalWrite(Tracepin5, HIGH);

    wdog.retrigger(); // <<< usa libreria
    char inChar = (char)Serial.read();
    if (inChar == 'q' || inChar == 'Q'){
      break;
    }
    delay(200);
    wdog.retrigger(); // <<< usa libreria
    delay(200);
  }
}
