SRC_DIR=./src
INC_DIR=./include
BUILD_DIR=./build
OBJ_DIR=./obj
BIN_DIR=./bin
LIBS_DIR=./lib
TESTS_DIR=./tests

CC=gcc

INC_SRC=$(patsubst %,-I%,$(dir $(shell find $(SRC_DIR) -name *.h)))
INCLUDES=-I$(SRC_DIR) -I$(INC_DIR) $(INC_SRC)

CFLAGS=-g -std=gnu99 -O2 -Wall -Wextra -Werror -Wno-unused-function \
		  -Wno-unused-parameter -Wno-address -Wno-unused-result -rdynamic -DNDEBUG\
		  $(INCLUDES) $(OPTFLAGS)

LIBS=-ldl -lm -lbsd $(OPTLIBS)
LIBLCTHW=$(LIBS_DIR)/liblcthw.a

SOURCES=$(shell find $(SRC_DIR) -name *.c)

OBJECTS_DIRS=$(subst $(SRC_DIR),$(OBJ_DIR),$(dir $(SOURCES)))
OBJECTS=$(subst $(SRC_DIR),$(OBJ_DIR),$(SOURCES:%.c=%.o))

TEST_SOURCES=$(wildcard $(TESTS_DIR)/*_tests.c)
TESTS=$(patsubst %.c, %.tst,$(TEST_SOURCES))

PROGRAMS_SRC=$(wildcard $(BIN_DIR)/*.c)
PROGRAMS=$(patsubst %.c, %.exe, $(PROGRAMS_SRC))

SLIB_TARGET=$(BUILD_DIR)/statserve.a
DLIB_TARGET=$(patsubst %.a,%.so,$(SLIB_TARGET))

###############
### TARGETS ###
###############

.PHONY: tests build

all: target tests bin

target: build $(SLIB_TARGET) $(DLIB_TARGET)

bin: $(PROGRAMS)

rebuild: clean all

tests: $(TESTS)
	sh ./tests/runtests.sh

###############
#### BUILD ####
###############

$(SLIB_TARGET): CFLAGS += -fPIC
$(SLIB_TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(DLIB_TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BIN_DIR)/%.exe: $(BIN_DIR)/%.c
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) $(LIBLCTHW) -o $@ $(LIBS)

$(TESTS_DIR)/%.tst: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) $(LIBLCTHW) -o $@ $(LIBS)

###############
#### SETUP ####
###############

build:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJECTS_DIRS)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TESTS_DIR)

clean:
	rm -rf $(BUILD_DIR) || true
	rm -rf $(OBJ_DIR) || true
	rm $(TESTS) || true
	rm tests/tests.log || true
	rm -rf $(PROGRAMS)
