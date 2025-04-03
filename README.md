# pipex

## Description
Le projet **pipex** de l'école 42 consiste à recréer le fonctionnement des pipes dans un environnement Unix. L'objectif est de comprendre les concepts fondamentaux des pipelines, des processus enfants et de l'exécution de commandes, tout en manipulant les redirections d'entrée et de sortie.

---

## Fonctionnalités

### Partie Obligatoire
Le programme permet d'exécuter deux commandes en série, en redirigeant la sortie de la première commande vers l'entrée de la deuxième. Voici un exemple :
```
$> < infile cmd1 | cmd2 > outfile
```
Ce comportement est reproduit avec le programme pipex :
```
$> ./pipex infile “cmd1” “cmd2” outfile
```

Le programme doit gérer :
- Les erreurs liées aux fichiers (permissions, inexistants, etc.).
- Les erreurs liées aux commandes (commandes invalides ou introuvables).

---

### Bonus
Le programme inclut deux fonctionnalités supplémentaires dans la partie bonus :

1. **Gestion de plusieurs pipes** :
   Le programme peut gérer plusieurs commandes en pipeline, comme dans cet exemple :
```
$> < infile cmd1 | cmd2 | cmd3 | … | cmdn > outfile
```
Ce comportement est reproduit avec :
```
$> ./pipex infile “cmd1” “cmd2” “cmd3” … “cmdn” outfile
```

3. **Mode here_doc** :
Le mode `here_doc` remplace le fichier d'entrée par une entrée utilisateur interactive jusqu'à un délimiteur (`LIMITER`). Les lignes saisies par l'utilisateur sont utilisées comme entrée pour les commandes. Voici un exemple :
```
$> cmd1 << LIMITER | cmd2 >> outfile
```
Ce comportement est reproduit avec :
```
$> ./pipex here_doc LIMITER “cmd1” “cmd2” … outfile
```
- Le symbole `>>` permet d'ajouter à la fin du fichier au lieu de le remplacer.
- Le programme lit les lignes depuis l'entrée standard jusqu'à ce que le délimiteur soit saisi.

---

## Installation et Compilation
Clonez le projet depuis GitHub et compilez-le avec `make` :

git clone <URL_du_projet> 

cd pipex 

make

---

## Exemple d'Utilisation

### Partie Obligatoire
Exécution simple avec deux commandes :
```
./pipex infile “grep a1” “wc -w” outfile
```
### Bonus : Plusieurs Pipes
Exécution avec plusieurs commandes en pipeline :
```
./pipex infile “ls -l” “grep .c” “wc -l” outfile
```
### Bonus : Mode here_doc
Exécution avec entrée utilisateur interactive :
```
./pipex here_doc LIMITER “cat” “wc -l” outfile
```
L'utilisateur peut saisir plusieurs lignes jusqu'à taper `LIMITER`.

---

## Ressources Utiles
- Tutoriel vidéo : *Understanding Pipes and Forks in Unix*.
- Documentation sur les fonctions système (`pipe()`, `fork()`, `execve()`).
- Guide interactif sur les redirections d'entrée/sortie.

---

