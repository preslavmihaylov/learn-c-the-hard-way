SRC_DIR=./src
BUILD_DIR=./build
BIN_DIR=./bin
TESTS_DIR=./tests

CC=gcc
INCLUDES=-I$(SRC_DIR)
CFLAGS=-g -std=gnu99 -O2 -Wall -Wextra -Werror -Wno-unused-function \
		  -Wno-unused-parameter -Wno-address -Wno-unused-result -rdynamic -DNDEBUG\
		  $(INCLUDES) $(OPTFLAGS)

LIBS=-ldl -lm -lbsd $(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TEST_SOURCES=$(wildcard $(TESTS_DIR)/*_tests.c)
TESTS=$(patsubst %.c, %.tst,$(TEST_SOURCES))

PROGRAMS_SRC=$(wildcard $(BIN_DIR)/*.c)
PROGRAMS=$(patsubst %.c, %.exe, $(PROGRAMS_SRC))

SLIB_TARGET=$(BUILD_DIR)/statserve.a
DLIB_TARGET=$(patsubst %.a,%.so,$(SLIB_TARGET))

all: target tests bin

target: build $(SLIB_TARGET) $(DLIB_TARGET)

bin: $(PROGRAMS)

rebuild: clean all

$(SLIB_TARGET): CFLAGS += -fPIC
$(SLIB_TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(DLIB_TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BIN_DIR)/%.exe: $(BIN_DIR)/%.c
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) -o $@

$(TESTS_DIR)/%.tst: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) -o $@ $(LIBS)

.PHONY: tests
tests: $(TESTS)
	sh ./tests/runtests.sh

build:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TESTS_DIR)

clean:
	rm -rf $(BUILD_DIR) || true
	rm $(OBJECTS) || true
	rm $(TESTS) || true
	rm tests/tests.log || true
	rm -rf $(PROGRAMS)
