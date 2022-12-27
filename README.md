# Hex
A hexagonal application launcher.\
An application launcher which has vim like navigation for linux users. Yes fellow i3 lovers and mouse haters, we dont need mouse anymore!!!\
Not conviced? Perhaps the screenshots will attract your attention

## Screenshots
![2022-12-27-130722_1366x768_scrot](https://user-images.githubusercontent.com/47611483/209641801-ac893155-b805-48eb-9198-e98840da76aa.png)

![2022-12-27-130819_1366x768_scrot](https://user-images.githubusercontent.com/47611483/209641813-e5ced698-6630-4b0f-9d8f-ac2fe1360991.png)

## Installtion
Check requirements section first
1. git clone this repo
2. make
3. sudo make install
4. type Hex in terminal

## Navigation
You can exit program any time by pressing escape\
The program has two modes which can be switched using tab: \
Insert mode ( blue one in screenshots )\
Visual mode ( orange one in screenshots )
1. Insert mode: It allows you to write a string in the centeral hexagon, the program will try to find the application you are looking for and present you the top six matching results in the outer hexagons (6 hexagons surrounding the central hexagons)
2. Visual mode: Main navigation takes place here. In your mind split outer hexagons in two halves, top 3 and bottom 3, then:\
2.1. The keys k and j are used to switch between upper and lower halves\
2.2. The key h will shift the selected hexagon to the left hexagon in the half and key l will shift selected hexagon to right hexagon in the half.\
2.3. Press enter to execute the selected program (works only in visual mode). For example in the screenshots, pressing enter will execute vlc media player. Beware it does not executes cli programs like nmtui (poweroff and reboot works though).

## Requirements
1. This program uses glfw, so make sure you have it in your linux machine. Either download from your package manager or build it from source (visit their official webpage).
2. You will need a compositor for transparency, for example picom.

## Settings
1. Disable shadows for Hex(this program) on your compositor
2. If you are using i3, it applies ugly border to the window, to remove that you will have to add following line in the end of i3config: for_window [class="Hex"] border pixel 0

