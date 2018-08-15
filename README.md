# Simple Platformer
A simple game that demonstrates usage of [Tily](https://github.com/GeneralNote/Tily) and [Colly](https://github.com/GeneralNote/Colly).
It uses SFML so make sure you have it installed. This game has couple showcases for Tily and Colly. Tily is used to render the tilemap. In this example we have 2 layers, one is for the blocks that are solid (dont have to be though) and behind the player. The other layer is for the decorations that are in front of the player. Colly is used to handle collision. In this example we handle also some special cases. One case is the collision with coin. Coins use CollisionType::Cross and when we collide with them, we delete them from the map. Spikes also work like coins except we dont delete them we just send player to the spawn position. To handle the tiles that can be destroyed by hitting jumping under them, we just check if velocity is negative (aka going upwards) when the collision happens.  

This game uses textures from [KenML](http://www.kenney.nl/): [link](https://opengameart.org/content/platformer-tiles)

![](https://i.imgur.com/EeUBUQN.png)

## Compile
### Preperation
Before compiling the game you need to have **SFML 2.5** installed. You also have to
place Tily and Colly header and source files in the "libs" directory.

### Building
To compile this program on **Linux**, just type in the following commands:
```
cmake .
make
./SimplePlatformer
```

To compile this program on **Windows**, open up the .sln file with Visual Studio. After that
link to SFML and build the project.