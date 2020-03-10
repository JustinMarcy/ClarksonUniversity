Justin Marcy
3/9/2020

##Specifications:
-diamond shape (8 faces, 6 vertices)
-each vertex has a different color and each face has interpolated colors 
-keys Q, W, E control rotation for x-axis, y-axis, z-axis respectively
-keys A, S control scaling in x, A for decrease, S for increase
-keys Z, X control scaling in y, Z for decrease, X for increase
-left & right arrow keys control translations in x
-up & down arrow keys control translations in y

##Transformation Composition:
-Order of composition is Rotate X, Rotate Y, Rotate Z, Translation, Scaling
-Roation increment = 0.1
-Translation increment = 0.05
-Scaling increment = 0.05

##Approach & Desciption:
When a key is held down, the key value is stored and then detected in an if condition.
When a key is detected, it increments the assigned transformation variable and then calls
that same transformation. The transformation function will update it's matrix and then call 
the render function. NOTE, the functions translate() and scale() are custom defined
functions and not from the MV.js file.

###Sources (for multiple key presses):
https://stackoverflow.com/questions/29266602/javascript-when-having-pressed-2-keys-simultaneously-down-leaving-one-of-them