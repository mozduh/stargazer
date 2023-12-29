# Game pixel engine 2.0 features to use

# Decals
for rendering graphics with the GPU instead of rendering with CPU. Decals can be transformed, which can be usful to simulate animating a static sprite drawing (load a sprite and transform it to animate it instead of loading multiple sprites and switching between them.). All layers should use Decals Instead of Sprites, but is up for discussion.

# Layers
Use layers to render game. Layer 0 would be the world, Layer 1 would be player and game objects, layer 2 would be interface for inventory, settings, etc.

Layers can be tinted.