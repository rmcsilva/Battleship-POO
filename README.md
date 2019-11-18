# Battleship-POO
Pratical assignment of the class Objected Oriented Programming 2018-2019 using Visual Studio ![platform](https://img.shields.io/badge/platform-win--32%20win--64-lightgrey)

## Introduction
This project is a Battleship style game where you need to survive as long as you can while you manage your ships and ports as well as fight several battles against your fierceful enemy pirates as you explore the sea and conquer uncharted territory.

### Initial Setup
After successfully loading the .sln into Visual Studio you may run the project and start your journey.

![initialConfig](https://user-images.githubusercontent.com/33632491/69053575-a05e4880-0a01-11ea-9d3c-ef2fd7a2169f.png)

Initially you will need a configuration file to setup the map and several game variables, the default one is [initialConfig.txt](https://github.com/rmcsilva/Battleship-POO/blob/master/Battleship/initialConfig.txt) you can use it as you wish or change it to your liking (more info about how to do that in portuguese [here at  part 2 -> section 8 Configuração](https://github.com/rmcsilva/Battleship-POO/blob/master/POO%20-%201819%20-%20Enunciado%20trabalho%20pratico%20(moodle).pdf).

### Game Phase
Now that everything is ready to go you can see the map along with some vital information to the player, like their coins, the ships they have on their ports and which port is the main one.

![gameView](https://user-images.githubusercontent.com/33632491/69054488-8e7da500-0a03-11ea-8b20-c3c20078126f.png)

The map is numered so the player can easily find the position of several itens that are on the map.

#### Color Coded
Each color has a meaning:
* Green represents everything that belongs to the player
* Dark Grey represents the ports that belong to the player along with a green text to enforce that ideia
* Red is used to show that something belongs to the pirates and follows the same logic as the player ports but with a yellow color to represent the ports instead.
* Blue tones represent the sea cells and the asterisk represents if it has fish
* White and Grey represent the cells that are land.

#### Ship Identification
Different letters represent different ships

![ShipsID](https://user-images.githubusercontent.com/33632491/69055013-b8839700-0a04-11ea-8f5e-0fb52fc350d6.png)

* V -> Sailboat
* E -> Schooner
* F -> Frigate
* G -> Galleon
* S -> Special Ghost Ship

Outside of the map you can see wich ships are at the ports along with their id.

#### Ship Combat
If there are combats the interface will let you know how they went, who won and if a ship sinks it will also be removed of the map.

![ShipCombat](https://user-images.githubusercontent.com/33632491/69055232-3b0c5680-0a05-11ea-8558-d1502506e57b.png)

#### Game Events
Sometimes the following events may occur during the game:
* Lull

![LullEvent](https://user-images.githubusercontent.com/33632491/69055514-d7365d80-0a05-11ea-8938-5e2e4cb1aee9.png)

* Riot

![RiotEvent](https://user-images.githubusercontent.com/33632491/69055555-f208d200-0a05-11ea-9928-7891111253a5.png)

* Mermaid

![MermaidEvent](https://user-images.githubusercontent.com/33632491/69055591-0a78ec80-0a06-11ea-800a-d486099b00ba.png)

* Storm

![StormEvent](https://user-images.githubusercontent.com/33632491/69055634-254b6100-0a06-11ea-8375-8ca9829a3d4e.png)


Everytime a event appears the intarface will let you know and it will be identified on the map with the purple color.
Events can affect positions of the map or ships depending on its type.

#### Lost Ship
When a ship has no more soldiers left it is considered to be lost and its identified by a light blue color.
Lost ships can be conquered if another ship finds it nearby and it will take the color of the conquerors ships.

![LostShip](https://user-images.githubusercontent.com/33632491/69055822-9b4fc800-0a06-11ea-8314-c0d777e86984.png)

 ##### Assignment Specifications
 You can find the assignment specifications in portuguese [here](https://github.com/rmcsilva/Battleship-POO/blob/master/POO%20-%201819%20-%20Enunciado%20trabalho%20pratico%20(moodle).pdf) 

