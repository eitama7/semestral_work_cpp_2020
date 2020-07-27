CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb
CLIBS=-std=c++14

all: doc korshmar

korshmar: main.o CApplication.o CInterface.o CNewGame.o CHelp.o CWeapon.o \
	CBang.o CBeer.o CCatBalou.o CGatling.o CMissed.o CDynamite.o
	$(CC) main.o CApplication.o CInterface.o CNewGame.o CHelp.o CWeapon.o \
		CBang.o CBeer.o CCatBalou.o CGatling.o CMissed.o CDynamite.o -o "korshmar" $(CLIBS)

CDynamite.o: src/cards/CDynamite.cpp src/cards/CDynamite.h \
	src/cards/../CCard.h src/cards/../constants.h src/cards/../CInterface.h \
	src/cards/../CCharacter.h src/cards/../CWeapon.h src/cards/../CPlayer.h
	$(CC) $(CFLAGS) -c src/cards/CDynamite.cpp

CMissed.o: src/cards/CMissed.cpp src/cards/CMissed.h src/cards/../CCard.h \
	src/cards/../constants.h src/cards/../CInterface.h \
	src/cards/../CCharacter.h src/cards/../CWeapon.h src/cards/../CPlayer.h
	$(CC) $(CFLAGS) -c src/cards/CMissed.cpp

CGatling.o: src/cards/CGatling.cpp src/cards/CGatling.h \
	src/cards/../CCard.h src/cards/../constants.h src/cards/../CInterface.h \
	src/cards/../CCharacter.h src/cards/../CWeapon.h src/cards/../CPlayer.h
	$(CC) $(CFLAGS) -c src/cards/CGatling.cpp

CCatBalou.o: src/cards/CCatBalou.cpp src/cards/CCatBalou.h \
	src/cards/../CCard.h src/cards/../constants.h src/cards/../CInterface.h \
	src/cards/../CCharacter.h src/cards/../CWeapon.h src/cards/../CPlayer.h
	$(CC) $(CFLAGS) -c src/cards/CCatBalou.cpp

CBeer.o: src/cards/CBeer.cpp src/cards/CBeer.h src/cards/../CCard.h \
	src/cards/../constants.h src/cards/../CInterface.h \
	src/cards/../CCharacter.h src/cards/../CWeapon.h src/cards/../CPlayer.h
	$(CC) $(CFLAGS) -c src/cards/CBeer.cpp

CBang.o: src/cards/CBang.cpp src/cards/CBang.h src/cards/../CCard.h \
	src/cards/../constants.h src/cards/../CInterface.h \
	src/cards/../CCharacter.h src/cards/../CWeapon.h src/cards/../CPlayer.h
	$(CC) $(CFLAGS) -c src/cards/CBang.cpp

CWeapon.o: src/CWeapon.cpp src/CWeapon.h src/constants.h src/CCard.h \
	src/CInterface.h src/CCharacter.h src/CPlayer.h
	$(CC) $(CFLAGS) -c src/CWeapon.cpp

CHelp.o: src/CHelp.cpp src/CHelp.h src/CCommand.h src/CInterface.h \
	src/CCharacter.h src/CCard.h src/CWeapon.h src/constants.h src/CPlayer.h
	$(CC) $(CFLAGS) -c src/CHelp.cpp

CInterface.o: src/CInterface.cpp src/CInterface.h src/CCharacter.h \
	src/CCard.h src/CWeapon.h src/constants.h src/CPlayer.h
	$(CC) $(CFLAGS) -c src/CInterface.cpp

CNewGame.o: src/CNewGame.cpp src/CNewGame.h src/CPlayer.h src/CCard.h \
	src/CCharacter.h src/CWeapon.h src/constants.h src/CInterface.h \
	src/CCommand.h src/cards/CBang.h src/cards/CBeer.h src/cards/CCatBalou.h \
	src/cards/CGatling.h src/cards/CMissed.h src/cards/CDynamite.h
	$(CC) $(CFLAGS) -c src/CNewGame.cpp

CApplication.o: src/CApplication.cpp src/CApplication.h src/CNewGame.h \
	src/CPlayer.h src/CCard.h src/CCharacter.h src/CWeapon.h src/constants.h \
	src/CInterface.h src/CCommand.h src/cards/CBang.h src/cards/CBeer.h \
	src/cards/CCatBalou.h	src/cards/CGatling.h src/cards/CMissed.h \
	src/cards/CDynamite.h src/CHelp.h
	$(CC) $(CFLAGS) -c src/CApplication.cpp

main.o: src/main.cpp src/CApplication.h src/CNewGame.h src/CPlayer.h \
	src/CCard.h src/CCharacter.h src/CWeapon.h src/constants.h \
	src/CInterface.h src/CCommand.h src/cards/CBang.h src/cards/CBeer.h \
	src/cards/CCatBalou.h src/cards/CGatling.h src/cards/CMissed.h \
	src/cards/CDynamite.h	src/CHelp.h
	$(CC) $(CFLAGS) -c src/main.cpp

doc:
	doxygen src/doxygen.conf
	mv doc/html/* doc/
	rm -r doc/html

clean:
	rm -f *.o
	rm -f korshmar
	rm -rf doc
	rm -rf *.dSYM

compile: doc korshmar

run: doc korshmar
	./korshmar
