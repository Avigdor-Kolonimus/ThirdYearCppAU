# c++ compiler
CXX=g++
# linker
LD=g++

CXXFLAGS= -g --std=c++14 -pedantic -Wall
LDFLAGS= 

# find all source files, derive object and dependency files
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))
DEP=$(patsubst %.cpp, %.d, $(SRC))

# name of executable
EXE=a.out

# default target
all: info $(EXE)

# simple info output
info:
	@echo "** compilation started at " `date`
	@echo " * sources: " $(SRC)
	@echo " * objects: " $(OBJ)
	@echo " * executable: " $(EXE)


# rule for generation of dependency files
%.d: %.cpp
	@echo " * generate dependency file " $@
	@cpp -MM $< > $@

# rule for generation of object files
%.o: %.cpp
	@echo " * compile object file: " $@
	$(CXX) $(CXXFLAGS) -c $< -o $@

# link executable
$(EXE): $(OBJ)
	@echo " * link executable " $(EXE)
	$(LD) $(LDFLAGS) $^ -o $@

	rm -rf $(OBJ)
# clean up all temporal files
clean:
	@echo " * cleaning up"
	rm -rf $(OBJ) $(DEP) $(EXE)

# include generated dependency files
#-include $(DEP)
