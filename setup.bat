@TITLE SFML-Setup

call git submodule update --init --recursive
call cmake -S . -B msvc -G "Visual Studio 17 2022"

pause