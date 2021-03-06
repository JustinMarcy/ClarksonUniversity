Justin Marcy
4/27

Shape used from lab3: Diamond (8 faces, 6 vertices)
NOTE: I used a web server to run my program to avoid cross-origin resources issue.
Texture Image: brick.jpg, successfully applied to all faces

For lab 5, I re-created my vertices for the diamond as follows:
p0, p1, p2 //first face, Bottom
p0, p2, p3 //second face, Bottom
p0, p3, p4 //third face, Bottom
p0, p4, p1 //fourth face, Bottom
p5, p1, p2 //fifth face, Top
p5, p2, p3 //sixth face, Top
p5, p3, p4 //seventh face, Top
p5, p4, p1 //eighth face, Top

New number of vertices = 24

I kept the controls and transformations the same as in lab 3,
but I implemented the necessary texture components from the class example.
Control (from lab3)
-diamond shape (8 faces, 6 vertices)
-each vertex has a different color and each face has interpolated colors 
-keys Q, W, E control rotation for x-axis, y-axis, z-axis respectively
-keys A, S control scaling in x, A for decrease, S for increase
-keys Z, X control scaling in y, Z for decrease, X for increase
-left & right arrow keys control translations in x
-up & down arrow keys control translations in y

Transformation Composition (from lab3):
-Order of composition is Rotate X, Rotate Y, Rotate Z, Translation, Scaling
-Roation increment = 0.1
-Translation increment = 0.05
-Scaling increment = 0.05

Conclusion:
When I initially tried the texture mapping described in the lecture, my shape
did not render correctly. After hours of double checking, I thought maybe I
might need to use barycentric coordinates, but this was not the case. The
example method worked, but I messed up my index list. I was confused by the
square example, so I modeled my index list as 0,1,2...0,2,3...etc. I thought the
index list reflected how each face was drawn. I then realized that each point
should have its own unique index and no repeats since my shape faces
are already triangles. I definitely over-thought the problem due to this mistake.
