#Kompilator och flaggor
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES = -I /c/msys64/mingw64/include
LIBS = -L /c/msys64/mingw64/lib

# Lista över källfiler och objektfiler
SRC = account.cc accounting.cc allyears.cc year.cc context.cc menuState.cc payment.cc \
	   programstate.cc runnable.cc uidata.cc addpayment.cc inputbox.cc

OBJ = $(SRC:.cc=.o) # Skapar en lista av .o-filer från dina .cc-filer

# Namnet på den slutgiltiga exekverbara filen
TARGET = accounting.exe

# Standardregel (anropas när du kör `make`)
all: $(TARGET)

# Regel för att bygga den exekverbara filen
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(INCLUDES) $(LIBS) $(LDFLAGS)

# Regel för att kompilera .cc-filer till .o-filer
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rensning av genererade filer
clean:
	rm -f $(OBJ) $(TARGET)