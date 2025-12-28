# ===== Compilateur =====
CC      := gcc
CFLAGS  := -Wall -Wextra -g
CPPFLAGS:=
LDFLAGS := -L.
LDLIBS  := -lothello
RPATH   := -Wl,-rpath=.

# ===== Paramètres réseau =====
IP_SERV := 127.0.0.1
PORT    := 8080
MDP     := binome1
ID      := 1

# ===== Fichiers source =====
SRC_JEU  := jeu_otheloV3.c
SRC_USER := userSimple.c
SRC_AUTO := joue.c
SRC_IA   := IA.c

# ===== Fichiers objet =====
OBJ_JEU  := $(SRC_JEU:.c=.o)
OBJ_USER := $(SRC_USER:.c=.o)
OBJ_AUTO := $(SRC_AUTO:.c=.o)
OBJ_IA   := $(SRC_IA:.c=.o)

# ===== Exécutables =====
BIN_JEU  := jeu
BIN_USER := userSimple
BIN_AUTO := auto
BIN_IA   := IA

ALL := $(BIN_JEU) $(BIN_USER) $(BIN_AUTO) 

# ===== Règle par défaut =====
all: $(ALL)

# ===== Règle générique .c -> .o =====
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# ===== Édition de liens =====
$(BIN_JEU): $(OBJ_JEU) function_othelo.o 
	$(CC) $^ -o $@

$(BIN_USER): $(OBJ_USER) 
	$(CC) $^ $(LDFLAGS) $(LDLIBS) $(RPATH) -o $@

$(BIN_AUTO): $(OBJ_AUTO) $(OBJ_IA) function_othelo.o
	$(CC) $^ $(LDFLAGS) $(LDLIBS) $(RPATH) -o $@

$(BIN_IA): $(OBJ_IA) function_othelo.o
	$(CC) $^ $(LDFLAGS) $(LDLIBS) $(RPATH) -o $@

# ===== Exécution =====
run: $(BIN_JEU) 
	./jeu

connexion: $(BIN_USER)
	./userSimple binome1 $(IP_SERV) 1

connexion2: $(BIN_USER)
	./userSimple binome2 $(IP_SERV) 2

go: $(BIN_AUTO)
	./auto $(MDP) $(IP_SERV) $(ID) $(PORT)

# ===== Nettoyage =====
clean:
	rm -f *.o $(ALL)

re: clean all

.PHONY: all clean re run connexion connexion2 go
