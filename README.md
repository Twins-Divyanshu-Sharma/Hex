# Hex
A hexagonal application launcher which has vim like navigation for linux users. 

## Video
https://github.com/Twins-Diwakar-Sharma/Hex/assets/47611483/0f74f865-ead8-4bc0-9fda-f84199651284


## Screenshot
![2024-03-23-152706_1366x768_scrot](https://github.com/Twins-Divyanshu-Sharma/Hex/assets/47611597/f8b287f9-87f5-402a-8ced-ebb89bb9de6e)


## Installtion
Check requirements section first
1. git clone this repo![2024-03-23-152706_1366x768_scrot](https://github.com/Twins-Divyanshu-Sharma/Hex/assets/47611597/afe1aa0e-f7d6-4081-aaea-783b69ca4b7d)

2. make
3. sudo make install
4. copy config file from res/config to ~/.config/Hex/ with same name i.e. config
5. type Hex in terminal

## Uninstall
1. cd to your cloned repo
2. sudo make purge

## Navigation
You can exit program any time by pressing escape\
The program has two modes which can be switched using tab: \
Insert mode ( blue one in screenshots )\
Visual mode ( orange one in screenshots )
1. Insert mode: It allows you to write a string in the centeral hexagon, the program will try to find the application you are looking for and present you the top six matching results in the outer hexagons (6 hexagons surrounding the central hexagons)
2.   Visual mode: Main navigation takes place here. In your mind split outer hexagons in two halves, top 3 and bottom 3, then:\
2.1.   The keys k and j are used to switch between upper and lower halves\
2.2.   The key h will shift the selected hexagon to the left hexagon in the half and key l will shift selected hexagon to right hexagon in the half.\
2.3.   Press enter to execute the selected program (works only in visual mode). For example in the 3rd screenshot, pressing enter will launch firefox web browser. Beware it does not executes cli programs like nmtui (poweroff and reboot works though).\
2.4.   You can also use arrow keys for navigation.

## Config File
Copy config file in res folder of git repo to $HOME/.config/Hex/config (name should remain config).
The config enables you to customize colors in Hex. The pattern is as follows:\
variableName = r g b\
where spaces are neccessary and r g b are color values of red green and blue respectively ranging between 0 and 255
The following variables can be edited:
1.  visualColor: It is the color of the outer rings in visual mode.
2.  insertColor: It is the color of inner ring in insert mode.
3.  disabledColor: It is color of disabled rings (ie outer rings in insert mode and inner ring in visual mode).
4.  textColor: It is the color of text while you are typing and of suggestions being displayed in outer ring.
5.  selectedTextColor: It is the color of text which is selected in visual mode.
6.  icon: It can only have one of three values:\
   6.1.    none: It's the default, setting it will show no icons.\
   6.2.    color: Original icons are displayed with their original colors.\
   6.3.    neon: Changes icons to look like neon signs. The color of the neon icon is the value textColor when not selected and selectedTextColor when selected.

## Requirements
1. This program uses glfw, so make sure you have it in your linux machine. Either download from your package manager or build it from source (visit their official webpage).
2. You will need a compositor for transparency, for example picom.

## Settings
1. Disable shadows for Hex(this program) on your compositor
2. If you are using i3, it applies ugly border to the window, to remove that you will have to add following line in the end of i3config: for_window [class="Hex"] border pixel 0


## I need my own fonts
Follow these steps in your cloned repo to install your own fonts.
1. edit source/Engine.cpp
2. inside the function void Engine::init() find the line: fontAtlas.setAtlas("circuitFontAtlas") comment int out
3. in place of this line add the line: fontAtlas.setAtlas("your_fonts") : where your_fonts is a png file of your font atlas kept in res/textures/ folder of your cloned repo, note: donot write .png in the arguements
4. To create your own fontAtlas, just use gimp or photoshop and make sure you draw letters exactly on top of circuitFontAtlas.png in res/textures/, that is letters should have same width and height and spacing between them. Put it in res/textures/your_fonts.png then change line: fontAtlas.setAtlas("your_fonts") note donot write .png
5. redo the instructions for Install above and you are done


