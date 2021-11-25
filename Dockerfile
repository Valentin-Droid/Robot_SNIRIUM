
# Image de base pour note conteneur
FROM ev3dev/debian-stretch-cross

# Installation des outils annexes
RUN sudo apt update
RUN sudo apt install -y sshpass
