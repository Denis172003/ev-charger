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
- Placa **Arduino Uno R3** (ATmega328P)
- 4x **LED-uri** (pentru procentul de încărcare)
- 1x **LED RGB** (pentru starea liber/ocupat)
- 2x **Butoane** (start și stop)
- 9x **Rezistențe** (7x 220/330 ohmi, 2x 1k ohmi)
- Breadboard
- Fire de conexiune

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

