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
## Fonts are weird in this project!

* The `Game/CMakeLists.txt` file includes a folder called lib/ and what it contains has been copied from SFML's submodule out of the `extlibs/libs-msvc` folder. I copied them, but maybe I should have just left them in place and linked to them further, but that crosses some boundaries too. I don't have a perfect solution.
* There is one commented line in `Game/CMakeLists.txt` that, if for some reason you want to open this project through the context menu, "Open with Visual Studio" to get the CMake stuff rolling. To build with the fonts in that configuration you will need to replace the forementioned comment and place a comment on the trailing line.

```
add_custom_target(copy_assets
                    # Uncomment one to Copy fonts to msvc/ OR out/
                    # unfortunately this is the only way I can get this to work
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Fonts
                    ${CMAKE_CURRENT_BINARY_DIR}/Fonts # Visual Studio Generator
                    #$<TARGET_FILE_DIR:Game>/Fonts # CMake Project
)
```