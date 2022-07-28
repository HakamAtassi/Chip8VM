# Chip8VM
A virtualized Chip8 emulator 


```
g++ display.cpp ../../RAM.cpp ../../CPU.cpp ../../Chip8.cpp `pkg-config --cflags --libs sdl2`
```


![image](https://user-images.githubusercontent.com/83780720/181401261-6da41061-50d0-46c6-a3c8-1fcd15b2477b.png)



- Officially working. 


TODO: 
* Improve performance


## PERFORMANCE

Initial "IBM" rendering time: 4.000 seconds

Improved "IBM" rendering time: 1.000 second => following changes to SDL2 rendering
