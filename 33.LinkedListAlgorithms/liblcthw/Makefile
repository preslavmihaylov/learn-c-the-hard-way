SRC_DIR=./src
LCTHW_DIR=$(SRC_DIR)/lcthw
BUILD_DIR=./build
TESTS_DIR=./tests

CC=gcc
INCLUDES=-I$(SRC_DIR) -I$(LCTHW_DIR) 
CFLAGS=-g -std=c99 -O2 -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter -rdynamic -DNDEBUG $(INCLUDES) $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TEST_SOURCES=$(wildcard $(TESTS_DIR)/*_tests.c)
TESTS=$(patsubst %.c, %.tst,$(TEST_SOURCES))

SLIB_TARGET=$(BUILD_DIR)/liblcthw.a
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

$(TESTS_DIR)/%.tst: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) -o $@ $(LIBS)

.PHONY: tests
tests: $(TESTS) 
	sh ./tests/runtests.sh

build:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TESTS_DIR)

clean:
	rm -rf $(BUILD_DIR) || true
	rm $(OBJECTS) || true
	rm $(TESTS) || true
	rm tests/tests.log || true
