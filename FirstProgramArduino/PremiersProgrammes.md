# Tutoriel : Premiers programmes #


Afin de maîtriser toutes les possibilités de la carte vous aller réaliser une série de manipulations de façon progressive.

<span style="color: #fb4141">Rappel : A chaque fois vous pourrez (devrez) trouver un exemple correspondant parmi ceux proposés dans l'IDE.</span>

## Allumer une LED ##

![Travail](images/rouage.png) Allumer une des trois LEDs, puis deux puis les trois à l’aide des instructions précédentes et de la fonction : `digitalWrite(pin,value) ;`

***

## Intermède : Attendre un temps donné - Fonction bloquante ##

![Travail](images/rouage.png) Mettre le programme en pause pour un temps donné à l’aide de la fonction `delay(ms);`

On remarquera que durant ce temps-là, le programme est bloqué.

***
## Détecter un appui sur le bouton - Méthode naïve ##

![Travail](images/rouage.png) Tenter de lire un appui sur le bouton poussoir et d’allumer une des LEDs lorsque celui-ci est appuyé. Pour cela utilisez la fonction :
`digitalRead(pin);`
***



## Communiquer avec le monde extérieur ##

![Travail](images/rouage.png) A l’aide de la classe _Serial_ et de ses prototypes, configurer une communication série avec la carte et afficher un texte sur le moniteur série d'Arduino IDE.


Dans le setup()
```cpp
Serial.begin(baudrate);
```

Dans la loop()
```cpp
Serial.print(val);
```
***

## Lire une valeur analogique ##

![Travail](images/rouage.png)
  * Déterminez la position du potentiomètre à l’aide de la fonction `analogRead(pin);`
  * Utilisez la liaison série pour «afficher» la valeur en pourcentage.

***

## Écrire une valeur _analogique_ sur une sortie ##

Arduino ne permet pas d’imposer des niveaux de tension autres que ’Haut’ (1 logique) et ’Bas’ (0 logique).
Une des solutions pour simuler ceci est l’utilisation de Modulation en Largeur d’Impulsion (MLI) ou Pulse Width Modulation (PWM) en anglais.
Principe : En faisant varier très rapidement une patte entre l’état ’Haut’ et l’état ’Bas’, la tension moyenne de ce signal peut être exprimée comme suit :


```math
V_{moy} = \alpha \times E
```

où :
  * E est l’amplitude du signal,
  * alpha est le rapport cyclique (duty cycle) défini comme le rapport entre le temps à l’état ’Haut’ t et la période du signal T :

```math
\alpha = \frac{t}{T}
```

![PWM](images/pwm.png) ![PWM](images/pwm2.png)

En appliquant un tel signal aux bornes de la diode, il est donc possible de contrôler la tension moyenne perçue par cette dernière, et donc son intensité lumineuse.


![Travail](images/rouage.png) Écrire un programme qui fait allume LED 1, fait varier l’intensité lumineuse de LED 2 et éteint LED 3.

***

## Et si on mettait tout ensemble ? ##

![Travail](images/rouage.png) Écrire un programme :

  * qui fait clignoter la diode LED1 à 1Hz ,
  * qui change l’état de la diode LED2 (allumée ou éteinte) à chaque appui sur le bouton,
  * qui fait en sorte que le potentiomètre permette de contrôler l’intensité lumineuse de ladite diode.

<span style="color: #fb4141">A ce point, vous devriez remarquer qu’il ne vous est pas possible de réaliser plusieurs actions en même temps, comme par exemple attendre une pression sur le bouton et lire la valeur du potentiomètre tout en faisant varier l’intensité lumineuse de la diode.</span>

Il est donc temps de  passer à une [utilisation avancée des fonctions Arduino](ProgrammesAvances.md)
