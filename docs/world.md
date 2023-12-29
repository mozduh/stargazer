# Maps design

# Overview
The idea is to create a map object that has a structure that the client and server can communicated based on.

# one way
To create a Map class that manages the map and all the game objects that are in the map. Then to have a Tile class that manages interaction between each tile. The map should be able to easily reference each tile with game world coordinates. Draw the Map onto screen would involve understanding where the player game object is. The map should be able to shift through the map. A coordinate on the map will always be the same releative to the server.

# Map Class
The map class will hold data that pertains to the world layer.

# Tile Class
The tile class will hold data about the idea
example tiles:
- grass tile
- tree tile (boundary tile) (interactive tile, player can cut down tree) (tile will have multiple sprites)
- sane tile

# Map File format
.map files will describe a map to it's full extent and will be loaded using the DataFile Utility .h file.

# Tile File format
.tile files will describe a tile to it's full extent and will be loaded using the DataFile Utility .h file.