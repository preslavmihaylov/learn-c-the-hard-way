CC=gcc
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)

SRC_DIR=./src
OBJ_DIR=./objs
BUILD_DIR=./build
TESTS_DIR=./tests

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TEST_SOURCES=$(wildcard $(TESTS_DIR)/*_tests.c)
TESTS=$(patsubst %.c, %,$(TEST_SOURCES))

SLIB_TARGET=$(BUILD_DIR)/libex29.a
DLIB_TARGET=$(patsubst %.a,%.so,$(SLIB_TARGET))

all: target tests

target: build $(SLIB_TARGET) $(DLIB_TARGET)

$(SLIB_TARGET): CFLAGS += -fPIC
$(SLIB_TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(DLIB_TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(TESTS_DIR)/%: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

.PHONY: tests
tests: $(TESTS) 
	sh ./tests/runtests.sh

build:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TESTS_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR) || true
	rm $(OBJECTS) || true
	rm $(TESTS) || true
