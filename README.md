# Chip8VM
A virtualized Chip8 emulator 


### Showcase


![image](https://user-images.githubusercontent.com/83780720/181791224-bad2599e-554a-4bc7-9c21-8511434cc4ea.png)

![image](https://user-images.githubusercontent.com/83780720/181401261-6da41061-50d0-46c6-a3c8-1fcd15b2477b.png)



### PERFORMANCE

Initial "IBM" rendering time: 4.000 seconds

Improved "IBM" rendering time: 1.000 second => following changes to SDL2 rendering


### Building and running 


- Install SDL2 libraries with 
```
sudo apt-get install libsdl2-dev
```
- Then clone and CD into the project repo using 

```
cd
git clone https://github.com/HakamAtassi/Chip8VM
cd Chip8VM
```
- Then build and run using 
```
g++ main.cpp RAM.cpp CPU.cpp Chip8.cpp `pkg-config --cflags --libs sdl2` && ./a.out
```
