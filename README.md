# Setup Instruction
https://github.com/gpuwangge/Wiki/blob/main/documents/SDL.md  

# Build Instruction
Go to the project dir  
> mkdir build  
> cd build  
> cmake -G "MinGW Makefiles" ..  
> make  

# Issue
In some machines(Windows Laptop), SDL_Log() works but SDL_CreateWindow() will fail without any error message...  
  
# Resource
Some tests need image resource. Manually move the image into the bin/ folder.



