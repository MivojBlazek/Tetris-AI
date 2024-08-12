#! /bin/bash

FILE=Tetris.pro
CONFIG_H_FILE=config.h
TETRIS_SOURCE_DIR=../../Tetris/src
TETRIS_AI_SOURCE_DIR=../../Tetris-AI/src

cd $TETRIS_SOURCE_DIR

# Removing AI section from Tetris.pro
original_line_count=$(wc -l < "$FILE")
sed '/###AI### Added by script to run AI/,$d' "$FILE" > tmp_file && mv tmp_file "$FILE"
new_line_count=$(wc -l < "$FILE")

# Check if it removed any lines
if [ "$new_line_count" -lt "$original_line_count" ]
then
    head -n -1 "$FILE" > tmp_file && mv tmp_file "$FILE"
fi

# Removing AI section from config.h
original_line_count=$(wc -l < "$CONFIG_H_FILE")
sed '/\/\/\/AI\/\/\/ Added by script to run AI/,$d' "$CONFIG_H_FILE" > tmp_file && mv tmp_file "$CONFIG_H_FILE"
new_line_count=$(wc -l < "$CONFIG_H_FILE")

# Check if it removed any lines
if [ "$new_line_count" -lt "$original_line_count" ]
then
    tail -n 1 "$CONFIG_H_FILE" | grep -q '^$' && sed -i '' -e '$ d' "$CONFIG_H_FILE"
fi

cd $TETRIS_AI_SOURCE_DIR