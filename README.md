# Instructions

## Mise en place
1. Brancher le WISEFU en USB au PC
2. Brancher le WISEFU en ISP à la cible

## Fonctionnement
1. Démarrer RealTerm pour communiquer avec le port série (USB)
2. Une première commande "A" est envoyée par l’Utilisateur pour demander à s'authentifier
3. Le WISEFU génère un défi d'authentification et l'envoie à l'Utilisateur
4. L'Utilisateur relève le challenge (grâce au JAR WISEFU_Auth_Challenge.jar) et transmet la preuve au WISEFU via RealTerm (un entier par char). Si l'authentification réussit, le WISEFU autorise l'envoi de nouvelles commandes
5. L'Utilisateur envoie une commande "U" pour initier le protocole de transfert des binaires du micrologiciel
6. Le WISEFU se met alors en attente des données binaires à recevoir (fichier de démo Demo1 ou Demo2)
7. Les binaires sont transférés (via RealTerm en binaire) et stockés au fur et à mesure sur la carte SD (jusqu'à détection d’un caractère de fin de transmission)
8. L'Utilisateur envoie ensuite une commande "M(numFichier)" pour démarrer le processus de mise à jour de la Cible
