#include <Arduino.h>

#define LED1 10
#define LED2 9
#define LED3 8
#define LED4 7
#define LED_ROSU 6   
#define LED_VERDE 5   
#define LED_ALBASTRU 4 
#define INTERVAL 3000
#define BTN_INCEPUT 3  
#define BTN_STOP 2     

int timpAnterior = 0;    
int baterie = 0;         
int incarcare = 0;       
int timpApasareButon = 0; 

void setup() {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED_ROSU, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_ALBASTRU, OUTPUT);
    pinMode(BTN_INCEPUT, INPUT_PULLUP);
    pinMode(BTN_STOP, INPUT_PULLUP);

    
    digitalWrite(LED_ROSU, LOW);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ALBASTRU, LOW);
}

void loop() {
    int butonInceput = digitalRead(BTN_INCEPUT); 
    if (butonInceput == LOW) {
        delay(20); 
        incarcare = 1; 
        timpAnterior = millis(); 

        
        digitalWrite(LED_ROSU, HIGH);
        digitalWrite(LED_VERDE, LOW);
        digitalWrite(LED_ALBASTRU, LOW);
    }

    int butonStop = digitalRead(BTN_STOP); 
    if (butonStop == LOW) {
        if (timpApasareButon == 0) {
            timpApasareButon = millis(); 
        }
        if (millis() - timpApasareButon >= 2000) {
            delay(20); 
            incarcare = 0; 
            timpApasareButon = 0; 
        }
    } else {
        timpApasareButon = 0; 
    }

    
    if (incarcare) {
        int timpCurent = millis();
        if (timpCurent - timpAnterior >= INTERVAL) {
            timpAnterior = timpCurent;
            baterie++; 
            if (baterie > 4) {
                baterie = 0; 
                incarcare = 0; 
            }
        }

        
        switch (baterie) {
            case 0:
                digitalWrite(LED1, LOW);
                delay(200);
                digitalWrite(LED1, HIGH);
                delay(200);
                break;
            case 1:
                digitalWrite(LED1, HIGH);
                digitalWrite(LED2, LOW);
                delay(200);
                digitalWrite(LED2, HIGH);
                delay(200);
                break;
            case 2:
                digitalWrite(LED2, HIGH);
                digitalWrite(LED3, LOW);
                delay(200);
                digitalWrite(LED3, HIGH);
                delay(200);
                break;
            case 3:
                digitalWrite(LED3, HIGH);
                digitalWrite(LED4, LOW);
                delay(200);
                digitalWrite(LED4, HIGH);
                delay(200);
                break;
            case 4:
                digitalWrite(LED_ROSU, LOW);    
                digitalWrite(LED_VERDE, HIGH); 
                
                for (int i = 0; i < 3; i++) {
                    delay(200);
                    digitalWrite(LED1, HIGH);
                    digitalWrite(LED2, HIGH);
                    digitalWrite(LED3, HIGH);
                    digitalWrite(LED4, HIGH);
                    delay(200);
                    digitalWrite(LED1, LOW);
                    digitalWrite(LED2, LOW);
                    digitalWrite(LED3, LOW);
                    digitalWrite(LED4, LOW);
                }
               
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, LOW);
                digitalWrite(LED3, LOW);
                digitalWrite(LED4, LOW);
                incarcare = 0; 
                break;

            default:
                break;
        }
    } else {

        digitalWrite(LED_ROSU, LOW);
        digitalWrite(LED_VERDE, HIGH);
        digitalWrite(LED_ALBASTRU, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        baterie = 0; 
    }
}
