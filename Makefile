##
## EPITECH PROJECT, 2025
## BubbleAdventure
## File description:
## Epitech Jam 2025
##

CXX	=	g++

CXXFLAGS	=	-Wall
CXXFLAGS	+=	-Wextra
CXXFLAGS	+=	-Wpedantic
CXXFLAGS	+=	-I src

LDFLAGS		=	-lSDL3
LDFLAGS		+=	-lm

TARGET	=	BubbleAdventure

SRC	=	$(shell find src -name "*.cpp" -not -name "main.cpp" 2>/dev/null)

OBJ	=	$(patsubst src/%.cpp,obj/%.cpp.o,$(SRC))

SRCM	=	src/main.cpp

OBJM	=	$(patsubst src/%.cpp,obj/%.cpp.o,$(SRCM))

all: setup $(TARGET)

setup: obj

obj:
	mkdir -p obj/ecs/systems

$(TARGET): $(OBJ) $(OBJM)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(OBJM) $(TARGET)

re:	clean all

obj/%.cpp.o:	src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY:	re clean all
