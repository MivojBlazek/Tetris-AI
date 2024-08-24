# Tetris AI

This is artificial intelligence to my previous Tetris game which is written in C++.
The main decision-making process is a heuristic-based search with greedy optimization.

Algorithm simulates all possible moves and rotations for falling piece and if there is holding piece, it simulates for that too. Then it evaluates each potential outcome using a heuristic function and chooses the move with highest heuristic score.

>   WARNING:
>
>   It is required to have Tetris from https://github.com/MivojBlazek/Tetris downloaded!
>
>   And it is necessary to have Tetris directory named as `Tetris` and this parent directory as `Tetris-AI`. 

I am free to any suggestions that can make my coding better and cleaner.

## Running game

### Linux

>   Program was tested on Ubuntu 22.04.4 LTS so there can be some issues with different OS.

After downloading and extracting BOTH .zip files from GitHub use Makefile to compile and run the game. Both unzipped repositories must be on the same level in the same directory.

| Commands              | Description |
| --------------------- | ----------- |
| make / make compile   | Uses first target in Makefile that should compile Tetris source files with extension of AI |
| make run              | Runs compiled program (GUI support is required) |
| make all              | Compiles program with extension (like `make compile`) and runs program after that |
| make clean            | Removes build from ./build/Linux/ |
| make compile-as-is    | Only compiles program without extension (basically it will work as common Tetris game) |
| make extension        | Adds extensions to `../Tetris/Tetris.pro` and `../Tetris/src/config.h` to enable AI |
| make remove-extension | Removes AI extensions from `../Tetris/Tetris.pro` and `../Tetris/src/config.h` |

>   To run game with AI extension, you can use simply `make all` command.

### Windows

>   Program was tested just only on Windows 10

For Windows there is already compiled program in `./build/Windows/`. Just go to that directory and find executable file `Tetris.exe` and run it.

## Controls

Game has common controls via keyboard.

At the start of the game you should press Start button but you can do it just pressing `Enter` on keyboard.

Controls to Tetris game is in described `../Tetris/README.md` and there is no other controls to AI.

## Some details

If the game is too slow for you or you want to make the window larger / smaller, you can do it in `config.h`.

>  Remember to compile game after each change in config.h.
