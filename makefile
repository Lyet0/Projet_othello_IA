CC := gcc
CFLAGS :=  -Wall -Wextra -g
Ip_Serv := 127.0.0.1 
port:=8080
mdp:=binome1
id:=1
run : jeu.o
	./jeu.o
jeu : jeu_otheloV3.c othselo.h 
	$(CC) $(CFLAGS) -c jeu_otheloV3.c -o jeu.o
clean: 
	rm -f  *.o
user : userSimple.c userNetwork.h
	$(CC) $(CFLAGS) -L. -o userSimple userSimple.c -lothello
connexion : 
	./userSimple binome1 $(Ip_Serv) 1
connexion2 : 
	./userSimple binome2 $(Ip_Serv) 2
auto: joue.c othelo.h userNetwork.h
	$(CC) $(CFLAGS) -L. -o auto joue.c -lothello
import :
	export LD_LIBRARY_PATH=.
go : auto
	./auto $(mdp) $(Ip_Serv) $(id) $(port)
IA : IA.c othelo.h userNetwork.h
	$(CC) $(CFLAGS) -L. -o IA IA.c -lothello