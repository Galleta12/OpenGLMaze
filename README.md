# OpenGLMaze
This is my first opengl 3D application. Is using opengl 3.3

The controls are the following.

Use z and x to zoom the camera
with WASD u can move the camera, it will be relative to where the camera is poiting.
hold shift for reducint the velocity of the camera
you can rotate the camera with the mouse, just hold the left click of the mouse and move the mouse (drag the mouse will holding the ieft click button).
It will rotate the camera.

With 1 and 2 u can change the camera view. It will start with the main camera. but if you press 2 it will change to the camera of the player that is a cube.
The player is control with the arrows keys and the movement is relaitve to where the first view camera is poiting. there is a simple aabb collision checker.
The player can rotate with q and e.

When running it may take a little bit to load since it loading all the textures files and this can take some time. THe texture coordinates, normal position and the vertices
are handle by a big array, that contains all of this data and this will be imported to opengl.

For doing this I am using the vertex buffer object. So the VBO is the vertex buffer object. it will store all the data of a object, such as the texture coordinate, vertices and normals. Then
with the element buffer object I will handle the indices, hence it can be easier to draw objects with opengl by sepecifying the order of the indices. The indices are also stored on another array.
And finally with the vertex array object I can save of all this information. This allow me to specify the data and how is organized the data on the vertex buffer object.

This can be found on the classes VBO(vertex buffer object). EBO(index buffer object) and VAO(vertex array object).

For the lights I use two types of lights, you can active the third one by uncommenting on the frag shader. however The pixels color of using the point and spot light is better in my opinion.

The effects of the lights can be seen better through the orthographic camera view. that will always be active on the right corner of the window.

On the shaders file is the glsl code for my light on the simple.vert and simple.frag are the main ones. whereas the other shaders are just for coloring the light position, this is just for visualization.

I am using an ecs system that I coded, following some resources, and all of the objects on the scene are either an entity or a component. 

The ecs system is the core functionality of this application, since all of the objects are encapsulated on this system. 
For example for the rendering I created a figurecomponent and then you can use this class component to specify vertices for each object. Then with entity object that has a transform component you can attach a figure component, for example a cube.
Then the transform component will allow you to move the object, whereas the figurecomponent is handling the drawings.
For the camera is the same I created a camera component and then I can attach this to any entity and like that easly created cameras with different settings.
Even though this allow me to have more flexibility it can be improved. since it can be hard to debug with the current ecs system.

I would say that the main functionalities are the transform physics camera and figure component. all of the other classes are derived from this main components. 

All of my code is on the src file the shaders on src/shaders and the headers file on include/headers.

You can use my premake5 script for generating a vs solution file. You can open this file that is a .sln and with just press play and the program will run. Please be sure to have c++ installed on your computer.
You can also just run the .exe file that is on the root directory. However this .exe file always needs to be on the root directory to avoid any errors.

![opengGLMaze](https://github.com/Galleta12/OpenGLMaze/assets/79543944/29f4a5ef-405b-4c93-ad43-5f91db6ec765)
