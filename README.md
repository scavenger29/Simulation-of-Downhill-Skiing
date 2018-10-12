# Simulation of Downhill Skiing
This project involves modeling and animation of a skier and associated environment with following features.

a) The modeling of a skier is represented as a hierarchical model with an articulated structure. The model can be seen as a tree.
b) The primitives to model a skier are OpenGL primitves.
c) The models is texture mapped.
d) The hierarchical model defines a heirarchy where a transformation when applied to a node in the tree its sub tree inherits the transformation.
e) The animation module involves defining some key frames of the skier, which form a particular type of motion for the purpose of skiing when interpolated. The parameter of interpolation is correlated with time.
g) Accessories -- the skies, the poles, the inclined plane are also modeled. The skies are anchored at the feet and the poles are acnhored at hands.
h) The path on the plane is defined through a spline curve.
i) The camera has different angles. It can follow the skiier, can be at fixed locations on looking at a zone of the whole scene, and a wide angle camera enabling the view of the entire scene.
j) At some locations a flag with a pole is installed. This flag when is hit by the skier may fall.

# Illustrations and Some Related Links

http://www.cse.iitd.ac.in/~pkalra/col781/COL781-A2.pdf

http://www.cse.iitd.ac.in/~pkalra/col781/ski-animation.mp4
