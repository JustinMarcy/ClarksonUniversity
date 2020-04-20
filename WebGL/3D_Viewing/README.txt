1) You need to set up the camera position using the look at method.
You must position your camera so that you can reveal the identity of your object.
Note: you are NOT permitted to use the lookAt() function provided by the authors in MV.js for this lab.

2) You need to have two buttons, one that creates a camera with orthographic projection called ‘Orthographic’,
and one that creates a camera with perspective projection called ‘Perspective’.
You must use set up projection matrices for each type of projection.
For the projective transformation, you are free to choose either an asymmetric or a symmetric frustum.
For the symmetric frustum, you are free to specify right, top, near, and far planes, or near plane, far plane, aspect ratio, and field of view in y.
Note: you are NOT permitted to use the functions ortho(), frustum(), and perspective() provided by the authors in MV.js for this lab.

3) You need to have two buttons that each switch on and switch off two different lights.
Each light must have ambient, diffuse, and specular components.
You can choose between point light source, spotlight, and directional light source.
One button should switch on or off one kind of light source, and the other should switch on a different kind of light source.
Example: LightButton1 can switch on and switch off a point light source. LightButton2 can switch on and switch off a spotlight source.
If you use a spotlight and a point light source, they should each be at different locations from each other.
Using LightButton1 and LightButton2, I should be able to switch on both lights, or just one of the lights, or switch off all lights.

For this lab, you are not permitted to use ambient light source on its own (if you want, you can use it in conjunction with another light source).

4) You need to have one button that toggles the specular reflection output, called ‘Specular’.
When switched on (i.e., when you press the button an odd number of times), the object should have ambient, diffuse, and specular reflection.
When switched off (i.e., when you press the button an even number of times), the object should have just ambient and diffuse reflection.
When showing specular reflection, your chosen viewpoint should reveal specular highlights on the object.

The object must have interpolated shading, and not flat shading. You can choose whether you interpolate colors or normals, i.e., whether you implement Gouraud shading or whether you implement Phong shading.

5) Your README should discuss your implementation method. Your README should also name the object (i.e., you should provide its identity). If the object is an Eames chair, but you call it a chair because you did not know whether it is an Eames chair, a lawn chair, or a Poang chair, that is fine. But if the object is a chair, and you call it a house, you will lose points. No, the actual object is not a chair, that was just a hypothetical explanation.

6) Please include your name in lab4.js and the README file.
