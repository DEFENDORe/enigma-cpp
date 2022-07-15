SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

MAIN := main.cpp
EXE := $(BIN_DIR)/enigma-cli
LIBRARY := $(BIN_DIR)/enigma.a
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

WEB_DIR := web
WEB_JS := $(WEB_DIR)/enigma.js
WEB := web.cpp

CC := g++
AR := ar
FLAGS := -Iinclude --std=c++17 -Wall

.PHONY: all clean web

all: $(EXE)

$(EXE): $(LIBRARY)
	$(CC) $(FLAGS) -Ilib $(MAIN) $(LIBRARY) -o $@

$(LIBRARY) : $(OBJ) | $(BIN_DIR)
	$(AR) rcvs $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
