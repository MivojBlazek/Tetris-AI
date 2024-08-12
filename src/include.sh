#! /bin/bash

# Check if it is not already included
sh remove_include.sh

TETRIS_SOURCE_DIR=../../Tetris/src
TETRIS_AI_SOURCE_DIR=../../Tetris-AI/src

cd $TETRIS_SOURCE_DIR

echo "\n###AI### Added by script to run AI" >> Tetris.pro
echo "SOURCES += \\" >> Tetris.pro
echo "    $TETRIS_AI_SOURCE_DIR/gamestate.cpp \\" >> Tetris.pro
echo "    $TETRIS_AI_SOURCE_DIR/artificialintelligence.cpp" >> Tetris.pro
echo "\n"
echo "HEADERS += \\" >> Tetris.pro
echo "    $TETRIS_AI_SOURCE_DIR/gamestate.h \\" >> Tetris.pro
echo "    $TETRIS_AI_SOURCE_DIR/artificialintelligence.h \\" >> Tetris.pro
echo "    $TETRIS_AI_SOURCE_DIR/outcome.h" >> Tetris.pro

echo "\n///AI/// Added by script to run AI" >> config.h
echo "#ifndef AI" >> config.h
echo "#define AI" >> config.h
echo "#endif // AI" >> config.h

cd $TETRIS_AI_SOURCE_DIR