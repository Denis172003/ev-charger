# EV-Charger

## Descrierea cerințelor
Trebuie să simulăm o stație de încărcare folosind LED-uri pentru a arăta nivelul de încărcare al bateriei și butoane pentru a porni/opri procesul. Procesul de încărcare începe la apăsarea scurtă a butonului de **start** și se oprește forțat la apăsarea lungă a butonului de **stop**.

- **LED-ul RGB** reprezintă disponibilitatea stației:
  - Verde: stația este liberă.
  - Roșu: stația este ocupată.
  
- **LED-urile simple** simulează nivelul de încărcare al bateriei:
  - L1 (25%), L2 (50%), L3 (75%), L4 (100%).
  
Procesul de încărcare se desfășoară progresiv: fiecare LED se aprinde pe rând, iar LED-ul corespunzător procentului curent de încărcare va clipi, la un interval de **3 secunde**.

## Componentele utilizate
- 4x LED-uri (pentru a simula procentul de încărcare)
- 1x LED RGB (pentru starea de liber sau ocupat)
- 2x Butoane (pentru start încărcare și stop încărcare)
- 8x Rezistoare (6x 220/330ohm, 2x 1K)
- Breadboard
- Linii de legătură

## Setup fizic

![ev_charger](https://github.com/user-attachments/assets/e144ce73-05d9-4b70-a741-7418afd25ab4)

https://github.com/user-attachments/assets/5dee7273-1d25-4851-8661-894aee2dd844

## Descrierea codului

Codul este împărțit în două scenarii principale: **încărcare** și **neîncărcare**.

### 1. Starea inițială
- LED-ul RGB este **verde** (stația este liberă), iar toate celelalte LED-uri sunt **stinse**.

### 2. Pornirea încărcării
- Apăsarea scurtă a butonului de start pornește procesul de încărcare.

```cpp
if (butonInceput == LOW) {
    delay(20); // Debouncing
    incarcare = 1; // Începe încărcarea
    timpAnterior = millis(); // Memorează timpul curent
    digitalWrite(LED_ROSU, HIGH);  // LED-ul roșu (ocupat) se aprinde
    digitalWrite(LED_VERDE, LOW);  // LED-ul verde (liber) se stinge
}
```
### 3. Oprirea încărcării
- Apăsarea lungă a butonului de **stop** (minim 2 secunde) oprește forțat încărcarea.

```cpp
if (butonStop == LOW) {
    if (timpApasareButon == 0) {
        timpApasareButon = millis(); // Memorează momentul apăsării
    }
    if (millis() - timpApasareButon >= 2000) {
        delay(20); // Debouncing
        incarcare = 0; // Oprește încărcarea
    }
} else {
    timpApasareButon = 0; // Resetează timpul de apăsare
}
```
### 4. Indicatorul progresului de încărcare
- LED-urile indică progresul încărcării bateriei:
- LED-ul corespunzător nivelului curent de încărcare va **clipi**, iar LED-urile anterioare rămân aprinse.

```cpp
if (incarcare) {
    int timpCurent = millis();
    if (timpCurent - timpAnterior >= INTERVAL) {
        timpAnterior = timpCurent;
        baterie++; // Crește nivelul de încărcare
        if (baterie > 4) {
            baterie = 0; // Resetează bateria la finalizare
            incarcare = 0; // Termină procesul de încărcare
        }
    }

    // Actualizează LED-urile în funcție de progres
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
            incarcare = 0; // Procesul de încărcare s-a încheiat
            break;
    }
}
```
### 5. Finalizarea încărcării
- Când încărcarea este completă, toate LED-urile clipesc simultan de 3 ori pentru a semnaliza finalizarea procesului.

``` cpp
if (baterie == 4) {
    digitalWrite(LED_ROSU, LOW);
    digitalWrite(LED_VERDE, HIGH); // LED verde aprins (stație liberă)
    
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
    
    incarcare = 0; // Oprește procesul de încărcare
}
```
### 6. Resetarea stației
- Dacă nu este în proces de încărcare, toate LED-urile sunt stinse, iar stația este pregătită pentru o nouă sesiune de încărcare.

```cpp
if (!incarcare) {
    digitalWrite(LED_ROSU, LOW);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
}
```
## Schema electrica
<img width="630" alt="Screenshot 2024-10-19 at 23 26 59" src="https://github.com/user-attachments/assets/e454f7ce-441f-470c-a71a-ded62507982a">
