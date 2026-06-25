# Cyrano de A&A - Le Jeu

Certains projets sont concernés par les présentes remarques générales, d'autres non : SVP, vérifiez chacune des remarques pour votre projet.

## Remarques générales
> Certains projets sont concernés par les présentes remarques générales, d'autres non : SVP, vérifiez chacune des remarques pour votre projet.

---

## Description du Jeu
**Cyrano de A&A** est un jeu de rôle tactique inspiré de la vie et de l'œuvre de *Cyrano de Bergerac*. Oubliez les combats de RPG classiques où l'épée est la seule solution : ici, le verbe est tout aussi tranchant que l'acier. Vous incarnez Cyrano et devez terrasser divers adversaires en combinant passes d'armes et joutes verbales.

Le système de combat repose sur un "Chifoumi" tactique où il faut affaiblir les faiblesses psychologiques ou physiques de vos ennemis grâce à des mécaniques d'escrime verbale (Éloquence/Debuff) et de maîtrise de l'épée (Force), tout en gérant votre jauge d'inspiration.

### Aperçu du jeu
*(Insérez votre ou vos captures d'écran ici)*
*(Exemple : ![Écran de combat](res/screenshot_fight.png))*

---

## Instructions pour Jouer

Le jeu se joue principalement à la souris et au clavier.

### Phases de Combat (FIGHT)
* **STRENGTH (Attaque physique) :** Déclenche un QTE où un cercle se referme. Appuyez sur **ESPACE** lorsque le cercle en mouvement est le plus proche possible du cercle cible pour infliger un maximum de dégâts.
* **ELOQUENCE (Attaque verbale) :** Permet d'affaiblir l'adversaire (Attaque ou Défense). Vous devrez compléter par écrit une tirade affichée à l'écran en tapant les lettres au clavier.
* **ITEMS (Inventaire) :** Vous pouvez consommer un objet par tour (soin, boost de force, boost d'éloquence) en cliquant sur son icône en haut à droite de l'écran de combat. 
* **Touche ÉCHAP (ESC) :** Permet d'annuler une action en cours de sélection (avant de lancer la QTE).

### Gestion (SHOP et Menus)
* **Achat :** Cliquez sur les boutons **BUY** sous les armes et objets pour dépenser les écus gagnés lors de vos victoires.
* **Pause :** Vous pouvez mettre le jeu en pause à tout moment en cliquant sur le bouton `| |` en haut à droite de la fenêtre.

---

## Instructions de Génération et Compilation

Ce projet utilise **CMake** pour générer les fichiers de build (Makefiles, projets Visual Studio, etc.) et **SFML** pour la gestion graphique.

Pour configurer et compiler le projet, référez-vous au support officiel :
[Documentation Outils CSC4526 (CMake)](https://www-inf.telecom-sudparis.eu/COURS/CSC4526/new_site/Supports/Documents/OutilsCSC4526/outilsCSC4526.html#cmake)

### Étapes rapides (Ligne de commande)

1. Assurez-vous d'avoir un compilateur compatible (ex: GCC, Clang ou MSVC) et CMake installés.
2. Clonez ou placez-vous dans le dossier du projet et créez un dossier de build :
   ```bash
   mkdir build
   cd build
