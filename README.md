# Pendu en ligne

## Fonctionnalités Clés

Serveur Réseau : Le jeu utilise des sockets réseau pour se connecter avec les clients. Cela permet de jouer au Pendu en ligne avec d'autres joueurs connectés au même serveur.
Sélection Aléatoire de Mots : La fonction pickRandomWord choisit un mot aléatoire à deviner à partir d'un fichier de mots (mots.txt). Cela assure une variété et un renouvellement constant dans les parties de jeu.
Gestion des Clients : Le serveur peut accepter des connexions de multiples clients, offrant ainsi une expérience multi-joueurs.

## Déroulement du Jeu
À la connexion d'un client, le serveur sélectionne un mot aléatoire et le présente sous forme de tirets (ex : _ _ _ _ pour un mot de quatre lettres).
Le joueur envoie des lettres au serveur pour deviner le mot.
Si la lettre est correcte, elle est révélée dans le mot (ex : _ a _ _ si la lettre 'a' est correcte).
Le jeu continue jusqu'à ce que le joueur devine le mot complet ou se déconnecte.

## Avantages Techniques
Programmation en C : L'usage du C pour le développement de serveurs réseau assure une exécution rapide et une gestion efficace des ressources.
Gestion des Sockets : L'implémentation des sockets en C est robuste et permet une bonne gestion des connexions réseau.
Portabilité : Le jeu peut être compilé et exécuté sur différents systèmes d'exploitation qui supportent le langage C.
Applications Pratiques

Ce projet est idéal pour comprendre les concepts de programmation réseau en C, la gestion des fichiers, et le développement de jeux simples. Il peut également servir de base pour développer des jeux en ligne plus complexes.

En somme, votre projet de Pendu en ligne offre une expérience ludique tout en étant un excellent exemple d'application de programmation réseau en C.






