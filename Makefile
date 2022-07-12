# project name
TARGET=repsta

# user way install
PRF_USERWAY=/usr/local/bin

# project compiler
CC=clang++

# cpp standart version
DEFINES=-std=c++17

# project flags release
CXXRFLAGS= $(DEFINES) -O2 -fPIC -march=native

# project flags debug
CXXFLAGS= $(DEFINES) -Wall -Werror -Wextra -Wpedantic -fPIC -march=native -g

# directory with source code
PRF_SRC=./src/

# directory with object files
PRF_OBJ=./obj/

# libs
LDLIBS=-lfmt -lboost_program_options
LIBINCLUDE=/usr/lib64/libfmt.so /usr/lib64/libboost_program_options.so

# list source files
SRC=$(wildcard $(PRF_SRC)*.cpp)
OBJ=$(patsubst $(PRF_SRC)%.cpp, $(PRF_OBJ)%.o, $(SRC))

# all targets
.PHONY : all release debug clear install uninstall

# default make
all : release

# target program debug
debug : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ${LIBINCLUDE} ${LDLIBS} -o $(TARGET)

# target program release
release : $(OBJ)
	$(CC) $(CXXRFLAGS) $(OBJ) ${LIBINCLUDE} ${LDLIBS} -o $(TARGET)

# generate doc
doxygen :
	doxygen Doxyfile

# generate .o files
$(PRF_OBJ)%.o : $(PRF_SRC)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# clean object and binary files
clean :
	rm -rf $(PRF_OBJ)*.o $(TARGET) doc/*

# install on system unix
install :
	install $(TARGET) $(PREFIX)

# uninstall on system unix
uninstall :
	rm -rf $(PREFIX)/$(TARGET)

