# Maps design

# Overview
The idea is to create a map object that has a structure that the client and server can communicated based on.

# one way
To create a Map class that manages the map and all the game objects that are in the map. Then to have a Tile class that manages interaction between each tile. The map should be able to easily reference each tile with game world coordinates. Draw the Map onto screen would involve understanding where the player game object is. The map should be able to shift through the map. A coordinate on the map will always be the same releative to the server.