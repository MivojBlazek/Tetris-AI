# 
# Tetris-AI
#
# File: Makefile
#
# Description: Makefile to compile and run program on Linux.
# 
# Author: Michal Blažek
#

PROJECT_NAME=Tetris
AI_EXTENSION_DIR=src/
BUILD_DIR=build/Linux/
TETRIS_SOURCE_DIR=../Tetris/src/
TETRIS_PROJECT=$(TETRIS_SOURCE_DIR)$(PROJECT_NAME)
BINARY=$(BUILD_DIR)$(PROJECT_NAME)

compile: extension 
	qmake $(TETRIS_PROJECT).pro -o $(BUILD_DIR)Makefile
	$(MAKE) -C $(BUILD_DIR)

compile-as-is: 
	qmake $(TETRIS_PROJECT).pro -o $(BUILD_DIR)Makefile
	$(MAKE) -C $(BUILD_DIR)

all: compile run

run:
	$(BINARY)

clean: remove-extension
	rm -rf $(BUILD_DIR)obj $(BUILD_DIR)Makefile $(BUILD_DIR)moc_* $(BUILD_DIR).qmake* $(BINARY) $(BUILD_DIR)ui_*

extension:
	cd $(AI_EXTENSION_DIR) && \
	sh include.sh && \
	cd ../

remove-extension:
	cd $(AI_EXTENSION_DIR) && \
	sh remove_include.sh && \
	cd ../