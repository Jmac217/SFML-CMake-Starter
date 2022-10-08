# SFML-One

### The purpose of this repo is to allow anyone to jump into SFML *with* CMake and play around a little. I also wanted to do this for myself obviously so it's just as finished as I need it to be for my purposes. Feel free to take this and run with it! My SFML Fork is just set to build SFML as a static project for your own personal use cases!
##### Enjoy!
<br/>
<hr/>

Download and install  
* [Git](https://git-scm.com/downloads)
* [CMake](https://cmake.org/download/)

Clone this repo  
> from a Visual Studio Command Prompt (any terminal *should* be fine)
```
git clone https://github.com/Jmac217/SFML-One.git
```

run `setup.bat`
> here are it's contents for the curious
```
@TITLE SFML-Setup

call git submodule update --init --recursive
call cmake -S . -B msvc -G "Visual Studio 17 2022"

pause
```
## Current Starters
> `Main` Branch  
> `git checkout Main`
* [Catching Confetti](https://youtu.be/NGNrAu0GZV0)
![SFML-CMake-Starter - Catching Confetti](https://i3.ytimg.com/vi/NGNrAu0GZV0/hqdefault.jpg "SFML-CMake-Starter - Catching Confetti")  

> `MarbleCollect` Branch  
> `git checkout MarbleCollect`
* [Marble Collect](https://youtu.be/aNrEoSC1PGc)
  ![SFML-CMake-Starter - Marble Collect](https://i3.ytimg.com/vi/aNrEoSC1PGc/hqdefault.jpg "SFML-CMake-Starter - Marble Collect")