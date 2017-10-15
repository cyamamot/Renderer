Pathtracing Renderer

Supports various antialiasing methods (jittering, shirley weights, supersampling)

uses multithreading to speed up render times

converts .ply files into a series of vertices and triangles and renders the object

lights and objects in scene can be transformed

3 different materials can be applied to objects (Lambert, Metallic, and Ashikhmin)


NEED TO create some way for user to interactively create scene, for now all values need to be
hardcoded into main.cpp (Material, Lights, Object, filepath, etc...)
