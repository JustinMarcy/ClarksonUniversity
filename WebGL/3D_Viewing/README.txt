Justin Marcy

Object Discovered: 
-Moai carved by the Rapa Nui people from rock on the Chilean Polynesian island of Easter Island
-In other words, this object is modeled after a ancient face carving

Camera position: 
-set up using the manual look at method, rotated so I can see the front of the image
-below shows the left, right... etc. specified for symmetric perspective
    var left = -5.0;
    var right = 5.0;
    var top_ = 5.0;
    var bottom = -5.0;
    var near = 50.0;
    var far = 100.0;

Buttons:
-Perspective: initally enabled (default), toggles when button is pressed, has its ow projection matrix, symmetric
-Ortographic: initally disabled, toggles when button is pressed, has its ow projection matrix 
-Specular: initially enabled, toggles specular reflection on both light sources
-Light Mode 1: initially enabled, toggles point source light
-Light Mode 2: initially enabled, toggles spotlight
-all button states are stored in a OrthIsOn, SpecularIsOn, SpotlightIsOn...etc. variable

Lighting:
-each light must has ambient, diffuse, and specular components.
-point light and spolight used (spotlight radius = 0.5)
-point light and spotlight are at diferent positions
-both light sources can be on together, opposite, or both off
-light sources are combined by adding R and R2, and then the result is clampled between 0 and 1

Shading:
-implemented using Gouroad Shading
-lab uses interpolated shading




