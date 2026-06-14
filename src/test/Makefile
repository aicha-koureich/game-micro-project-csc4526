# compiler compiler compiler 
CXX = g++
CXXFLAGS = -std=c++17 -I../core

# On va chercher UNIQUEMENT les fichiers nécessaires pour les items, le joueur et les armes
# On exclut le dossier "Others" et le main.cpp global pour ne pas faire de conflit
SOURCES = itemTest.cpp $(shell find ../core -name "*.cpp" ! -name "main.cpp" ! -path "../core/Others/*")

all: build run

build:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o itemTestExe

run:
	./itemTestExe

clean:
	rm -f itemTestExe