# @Makefile
# @brief Compilation croisée pour robot LEGO Mindstorm EV3
# @author David SALLE
# @date 24/03/2017
# @version 0.3
# @licence GPL3


# Variables de compilation et déploiement
IP_ROBOT=192.168.0.184
CC=arm-linux-gnueabi-g++
CFLAGS=-O2 -march=armv5
CCFLAGS=-std=c++11 -D_GLIBCXX_USE_NANOSLEEP
DEPS=ev3dev.h robot.hpp
OBJ=ev3dev.o robot.o
LIBS=-lstdc++ -lpthread
EXEC=demo_leds


# Règles de construction
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CCFLAGS)

$(EXEC): $(OBJ) $(EXEC).o
	$(CC) -o $@ $^ $(CFLAGS) $(CCFLAGS) $(LIBS)


# Règles de nettoyage
clean:
	rm -f *.o

mrproper:	clean
	rm -f $(EXEC)


# Règle pour le téléversement du fichier sur le robot
upload:
	sshpass -p "maker" scp $(EXEC) robot@$(IP_ROBOT):/home/robot/snir2/


# Règle globale
all:	$(EXEC) upload
