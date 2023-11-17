CC=g++
SOURCE=backend/model/*.cc
TARGET=tests/*.cc
FLAGS=-Werror -Wall -Wextra -std=c++17
APP_DIR=../app
APP_NAME=SmartCalc_v2_0.app
BUILD_DIR=client/build
TRASH=*.out build qt/build-SmartCalc_v2_0-Desktop_x86_darwin_generic_mach_o_64bit-Debug qt/build docs $(APP_DIR) ../SmartCalc_v2_0.tar.gz

ifeq ($(UNAME), Linux)
    APP_NAME=calc_2
endif

all: run

clean:
	@rm -rf $(TRASH)

run: install
	@sleep 1
	@open $(APP_DIR)/$(APP_NAME)

install: build
	@mkdir -p $(APP_DIR)
	@cp -rf qt/build/SmartCalc_v2_0.app ../app/SmartCalc_v2_0.app

build: clean
	@cmake -DCMAKE_PREFIX_PATH=$(QT_INSTALL_PREFIX) -B qt/build qt/SmartCalc_v2_0
	@make -C qt/build

dvi:
	@doxygen Doxyfile
	@open docs/html/index.html

dist: clean
	@cd .. && tar -zcvf SmartCalc_v2_0.tar.gz src

build_test:
	@cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	@cmake --build build

test: build_test
	@./build/SmartCalc_2_0_tests

leaks: build_test
	@leaks --atExit -- ./build/SmartCalc_2_0_tests

style:
	@clang-format -n -style=google $(SOURCE) backend/*.h backend/model/*.h
