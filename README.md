![SFML-CMake-Starter](https://raw.githubusercontent.com/Jmac217/SFML-CMake-Starter/BlankStarter/Resources/CMakeSFMLStarter.png "SFML-CMake-Starter")

# SFML-CMake-Starter

### The purpose of this repo is to allow anyone to jump into SFML *with* CMake and play around a little. I also wanted to do this for myself obviously so it's just as finished as I need it to be for my purposes. Feel free to take this and run with it! My SFML Fork is just set to build SFML as a static project for your own personal use cases!

### This Project started as a repo to follow along with [Suraj Sharma](https://www.youtube.com/playlist?list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up) with the simple addition of CMake. Now that I'm at the end of that tutorial series the repo is growing to host each of the game samples I make through my studies. Keeping them in the same repo on seperate branches allows me to cherry pick each feature added but comes with its own headaches.

##### Enjoy!

<hr/>

Download and install  
* [Git](https://git-scm.com/downloads)
* [CMake](https://cmake.org/download/)

Clone this repo
```
git clone https://github.com/Jmac217/SFML-CMake-Starter.git
```

> `SpaceShooter` Branch  
> `git checkout SpaceShooter`  
* [Shape Shooter](https://youtu.be/V2PyRu0lt9U)  

![SFML-CMake-Starter - Shape Shooter](https://i3.ytimg.com/vi/V2PyRu0lt9U/hqdefault.jpg "SFML-CMake-Starter - Shape Shooter")

<hr/>

call `cmake -S . -B build`  
*or*  
run `setup.bat`
> here are it's contents for the curious
```
@TITLE CMake-SFML-Starter-Setup

call git submodule update --init --recursive
call cmake -S . -B msvc -G "Visual Studio 17 2022"

pause
```
## Current Starters

> ### Default Branch
> `BlankStarter` Branch  
> `git checkout BlankStarter`

<hr/>

> `Platformer` Branch  
> `git checkout Platformer`
* [Platformer](https://youtu.be/v4phNDx_Jdo)  

![SFML-CMake-Starter - Platformer](https://i3.ytimg.com/vi/v4phNDx_Jdo/maxresdefault.jpg "SFML-CMake-Starter - Platformer")

<hr/>

> `CatchingConfetti` Branch  
> `git checkout CatchingConfetti`
* [Catching Confetti](https://youtu.be/NGNrAu0GZV0)  

![SFML-CMake-Starter - Catching Confetti](https://i3.ytimg.com/vi/NGNrAu0GZV0/hqdefault.jpg "SFML-CMake-Starter - Catching Confetti")  

<hr/>

> `MarbleCollect` Branch  
> `git checkout MarbleCollect`
* [Marble Collect](https://youtu.be/aNrEoSC1PGc)  

![SFML-CMake-Starter - Marble Collect](https://i3.ytimg.com/vi/aNrEoSC1PGc/hqdefault.jpg "SFML-CMake-Starter - Marble Collect")