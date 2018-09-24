# Tutoriel : programmes avancés #

## Attendre un temps donné - Fonction non bloquante ##

![Travail](images/rouage.png) Afin de redonner la main au programme durant les phases d'attentes, proposez une solution pour une attente non bloquante utilisant la fonction :  `millis();`

Indice :  _Exemples > 02.Digital > BlinkWithoutDelay_
***
## Détecter un appui sur le bouton - Méthode _propre_ #

![Travail](images/rouage.png) A l'aide des interruptions, récupérer une information _bouton appuyé_ et _bouton relâché_, sur le terminal série.

```cpp
attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
```

***

## Utilisation d'une bibliothèque externe pour allumer les diodes RGB intelligentes ##

La communauté Arduino étant très active, il existe de nombreuses bibliothèques dont une pour piloter ces diodes.

Ensuite il suffit d'ajouter un objet `leds` de la classe `Adafruit_NeoPixel` dans la zone de déclaration :

```cpp
#include <Adafruit_NeoPixel.h>
#define PIN 4 // le nom de la broche d'accès aux WS2812 sur la Teensy
#define LED_COUNT 2 // le nombre de WS2812 en série

// Create an instance of the Adafruit_NeoPixel class called "leds".
// That'll be what we refer to from here on...
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
```

Dans la `setup()` il faut "démarrer" l'objet _leds_.
```cpp
leds.begin();
```

Enfin dans la `loop()` il est possible d'assigner une valeur différente à chaque LED.

```cpp
leds.setPixelColor(4, 0xFF00FF);    // Set fourth LED to full red, no green, full blue
leds.setPixelColor(4, 0xFF, 0x00, 0xFF);  // Also set fourth LED to full red, no green, full blue
leds.show();
```

![Travail](images/rouage.png) Créez un programme qui fait évoluer la couleur de chaque led WS2812 indépendament et en fonction du temps.

***

## Création d'une machine à états ##

![Travail](images/rouage.png) Vous avez maintenant les connaissances nécessaires pour réaliser une machine à états dont la séquence est la suivante :

  * Un appui simple allume une diode
  * Deux appuis allument deux diodes
  * Trois appuis allument les trois diodes

Dans tous les cas, le potentiomètre gère l'intensité lumineuse des diodes

***
## Pour aller plus loin dans l'affichage sur le moniteur série ##
![Travail](images/rouage.png) Encoder la valeur du potentiomètre de manière à afficher de manière période un motif comme celui-ci :

```cpp
||          *          ||
```

et dont la position du motif central est pilotée par la position du potentiomètre :

```cpp
||       *             ||
||     *               ||
||    *                ||
||    *                ||
||    *                ||
||     *               ||
||        *            ||
||         *           ||
||           *         ||
||            *        ||
||             *       ||
||              *      ||
||            *        ||
||         *           ||
||       *             ||
||       *             ||
||         *           ||
||          *          ||
||         *           ||
||       *             ||
||       *             ||
||       *             ||
||          *          ||

```
## Et si on mettait tout ensemble ? (bis) ##

![Travail](images/rouage.png) À l'aide d'une machine à état, écrire un programme non bloquant qui :

  * change l’état d’une diode (allumée ou éteinte) à chaque appui sur le bouton,
  * fait en sorte que le potentiomètre permette de contrôler l’intensité lumineuse de ladite diode.
  * Utilisez votre imagination pour exploiter au mieux la carte
