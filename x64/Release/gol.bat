@echo off
>output.txt (
GameOfLife.exe --load random250_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random500_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random750_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random1000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random1250_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random1500_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random1750_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random2000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random3000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random4000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random5000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random6000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random7000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random8000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random9000_in --generations 250 --save myoutput --measure --mode ocl
echo "\n"
GameOfLife.exe --load random10000_in --generations 250 --save myoutput --measure --mode ocl 
)
