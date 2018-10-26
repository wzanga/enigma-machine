DEBUG=yes
CXX=g++
ifeq ($(DEBUG),yes)
	CXXFLAGS= -g -W -Wall -ansi -pedantic
	LDFLAGS=
else
	CXXFLAGS= -W -Wall -ansi -pedantic
	LDFLAGS=
endif

EXEC=enigma
SRC= main.cpp enigma.cpp component.cpp plugboard.cpp rotor.cpp reflector.cpp auxiliaries.cpp
OBJ= $(SRC:.cpp=.o)
ARGUMENTS=plugboards/I.pb reflectors/I.rf rotors/V.rot rotors/IV.rot rotors/III.rot rotors/I.pos

enigma: $(OBJ)
ifeq ($(DEBUG),yes)
		@echo "Debugger ON"
else
		@echo "Debugger OFF"
endif
	$(CXX) -o $@ $(CXXFLAGS) $^

main.o:

enigma.o: enigma.h component.o rotor.o plugboard.o reflector.o

component.o: component.h

plugboard.o: component.cpp plugboard.h component.h

rotor.o: rotor.h component.cpp component.h

reflector.o: component.cpp reflector.h component.h

auxiliaries.o: auxiliaries.h

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

try: $(EXEC)
	./$(EXEC) $(ARGUMENTS)

leak : $(EXEC)
	valgrind --tool=memcheck --leak-check=full ./$(EXEC) $(ARGUMENTS)

debug: $(EXEC)
ifeq ($(DEBUG),yes)
	sudo gdb $(EXEC) $(ARGUMENTS)
else
	@echo "Cannot debug because Debugger is off"
endif

send:
	make clean
	git add *.h *.cpp Makefile
	git commit -m "case_already_mapped() not fully functional as I wanted but give some piece of information"
	git push


.PHONY: clean

clean:
	rm -rf *.o *.dSYM $(EXEC)
	clear
	ls
