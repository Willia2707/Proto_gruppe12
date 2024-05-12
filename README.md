# Proto gruppe 12

Dette er den tilhørende koden til vårt prosjekt "Spinnvill" i faget TPD4126 Prototyping av fysiske brukeropplevelser <br />
**Gruppe 12:** Felicia Semb, Frida Hval Skiaker, Tale Tannvik Skei, William Stadheim

## Konseptet
Spinnvill er et spill som utforsker konsptet om tid ved å utfordre spillerne til å måle tiden det tar å bevege en brikke rundt en modell av jordkloden. Vår ide var å bruke jorda som referanse og sammenlikne tiden lyset bruker rundt jorda i virkeligheten, med tiden man selv bruker på å føre en brikke rund en liten modell av jorda. I tillegg fokuserte vi på å gjøre modellen visuell spennende og interaksjonen engasjerende. Ved å få oppgitt tiden du bruker på en runde, får du lyst til å prøve igjen for å se hvor fort du klarer det og slå din forrige tid. 

Når spillet starter, begynner tiden å gå, og spilleren må kjappe seg med å føre knappen langs rundt jorden. Etter at alle sensorene er passert i riktig rekkefølge og brikken har kommet i mål, stoppes tiden, og resultatet vises på LCD-skjermen. Spillerens tid sammenlignes med lysets hastighet rundt jorden.

## Sensorer
For å måle posisjonen til brikken har vi brukt hall-effekt sensorer. Selve brikken er en stor magnet som trigger sensorene dersom den passerer de. Tilsammen har vi koblet opp 4 hall-effekt sensorer som fungerer som checkpoints brikken må passere for å fullføre runden. 

Ellers har vi brukt en arkadeknapp med integrert ledlys som start/stoppknapp. Neopixel ledlys for å gi visuell feedback og gjøre interaksjonen spennende samt en 16x2 LCD-skjerm for å kunne printe tekst til spilleren. 

## Koden
I koden bruker vi bibliotekene: <Adafruit_NeoPixel.h>, <FastLED.h> og <LiquidCrystal.h> 

Setup: Koden starter med å definere alle nødvendige komponenter og variabler, inkludert sensorer, LED-stripe og LCD-skjerm.

Hovedløkke: Løkken kjører kontinuerlig og sjekker om knappen er trykket. Hvis knappen er trykket, starter spillet som kjører i en while-løkke.

Spillets gang: Når spillet er startet, registrerer koden passeringen av brikken (magneten) over fire Hall-effektsensorer langs banen. Hver sensor aktiveres i en bestemt rekkefølge, og når alle sensorene er passert i riktig rekkefølge, stoppes tiden.

Tidtaking: Koden bruker arduinonen sin innebygde funksjonen millis() for å måle tiden det tar å fullføre runden. Denne tiden vises på LCD-skjermen sammen med en melding om hvor fort spilleren beveget seg sammenlignet med lysets hastighet.

Avslutning av spillet: Etter at en runde er fullført, går spillet tilbake til startskjermen og venter på at spilleren trykker knappen igjen for å starte en ny runde. Mens spillet ikke er i gang, viser LED-stripen en glidende regnbueeffekt for å tiltrekke oppmerksomhet og skape interesse.




