# 3D Traffic Simulation Model #
Based on a cellurar automaton model 3D traffic simulation made with C++14.  
3D engine made from scratch with OpenGL.

Build it with `./build_all.sh`. To build it properly you need glm and glew libraries.  
Installation: `sudo apt install libglew-dev libglm-dev`  
Check `pkg-config --cflags glew` and add output of this command as a compiler flag.  
Add linker flags: `-lGLEW -lX11 -lGLU -lGL`

## Usage ##
Run `Debug/Sim`
It uses city model from file map.json and produces frames.json which is a set of frames used by 3D engine to display

Copy frames.json to MISS_Dispnew and run 3D engine
`cd MISS_Dispnew`
`Debug/MISS_Disp`

## JSON city model ##

```
" nodes " : [ {
" id " : 0 ,
" lat " : -1 0 0 . 0 ,
" lon " : 0 . 1 ,
" intersection " : true ,
" connections " : [ {
" from " : " 0 r 0 " ,
" to " : [
"0r0,100"
]
} , {
" from " : " 0 r 1 " ,
" to " : [
"0r1,100"
]
} ],
" roads " : [
0, 1
],
} , ...
```
  * node - a vertex = beginning or end of a road
  * lon - longtitude, lat - latitude (in a simulated world, not real-world),
  * intersection - is this object a crossroad [`true`/`false`]
  * connections - list of roads that connects with such crossroad
  * from - lane which from we driving,
  * to - lane which to we can drive on such crossroad with probability of such action,
  * `0r0,100` - probability of going to lane `0` on a road `0` is `100%`,
  * roads - list of roads which crossroad consist of.
  
```
" ways " : [ {
" id " : 0 ,
" beg " : 0 ,
" end " : 1 ,
" left " : 0 ,
" right " : 2 ,
" length " : 2 0 0 ,
" forbid " : [
{ " from " : " 0 l 0 " , " to " : " 0 l 1 " }
]
} ] , ...
```
  * beg - node id which is beginning of a road,
  * end - node id which is end of a road,
  * left - number of left-side lanes on a road,
  * right - number of right-side lanes on a road,
  * length - length of a road,
  * forbid - list of forbidden lane changes.
 
```
" lights " : [ {
" color " : " red " ,
" time " : 1 4 ,
" red " : 1 6 ,
" green " : 1 6 ,
" lanes " : [
"0l0", "0l1", "2l0", "2l1"
]
} , {
" color " : " green " ,
" time " : 1 4 ,
" red " : 1 6 ,
" green " : 1 6 ,
" lanes " : [
"1l0", "1l1", "3l0", "3l1"
]
} ] , ...
```
  * color - light color at the start of the simulation [`green`/`red`],
  * time - time left to light color to change,
  * red - how long light is red,
  * green - how long light is green,
  * lanes - list of lanes which is controlled by such traffic light.
 
```
" spawner " : [ {
" lane " : "0r0",
" prob " : 15
} , {
" lane " : "0r1",
" prob " : 15
} , ...
```

It is an object that spawn new cars each update. There is said that on lane `0` on road `0` there is probability of `15%` that a car will spawn.

## [Class Diagram](https://github.com/n1ay/3D-Traffic-Simulation-Model/blob/master/SimClassDiagram.pdf) ##
