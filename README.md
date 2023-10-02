# Hex
A hexagonal application launcher.\
An application launcher which has vim like navigation for linux users. Yes fellow i3 lovers, vim like navigation for application launcher !!!\
Not convinced? Perhaps the screenshots will attract your attention

## Screenshots
![2022-12-29-142025_1366x768_scrot](https://user-images.githubusercontent.com/47611483/209930901-322ff594-c5ea-4934-98a8-e7900596cccc.png)
![2022-12-29-142059_1366x768_scrot](https://user-images.githubusercontent.com/47611483/209930922-2ac65f34-382b-4ddd-83c7-9533d54e1bf0.png)
![firefoxLaunch](https://user-images.githubusercontent.com/47611483/209930932-535040a1-7b34-4480-b4c4-7e3af0c7d6ec.jpg)


## Installtion
Check requirements section first
1. git clone this repo
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
2. Visual mode: Main navigation takes place here. In your mind split outer hexagons in two halves, top 3 and bottom 3, then:\
2.1. The keys k and j are used to switch between upper and lower halves\
2.2. The key h will shift the selected hexagon to the left hexagon in the half and key l will shift selected hexagon to right hexagon in the half.\
2.3. Press enter to execute the selected program (works only in visual mode). For example in the 3rd screenshot, pressing enter will launch firefox web browser. Beware it does not executes cli programs like nmtui (poweroff and reboot works though).

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
