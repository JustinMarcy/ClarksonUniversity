// Name: Justin Marcy

var gl;
var numVertices;
var numTriangles;
var orthographicIsOn;
//var orthographicIsOnLocation;
var myShaderProgram;

function initGL(){
    var canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.enable(gl.DEPTH_TEST);
    gl.viewport( 0, 0, 512, 512 );
    gl.clearColor( 0.0, 0.0, 0.0, 1.0 );

    var myShaderProgram = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( myShaderProgram );


    numVertices = 1738;
    numTriangles = 3170;
    vertices = getVertices(); // vertices and faces are defined in object.js
    indexList = getFaces();


    var indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER,indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indexList), gl.STATIC_DRAW);

    var verticesBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, verticesBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW);

    var vertexPosition = gl.getAttribLocation(myShaderProgram,"vertexPosition");
    gl.vertexAttribPointer( vertexPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vertexPosition );

    // Insert your code here

    // Compute vertex normals
    var faceNormals = getFaceNormals(vertices, indexList, numTriangles);
    var vertexNormals = getVertexNormals(vertices, indexList, faceNormals, numVertices, numTriangles);

    // Create buffer for the faceNormals, bind buffer, send data to GPU
    var normalsbuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, normalsbuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(vertexNormals), gl.STATIC_DRAW);

    // Pointer to iterate over the buffer normals, associate with nv myShaderProgram
    // Iterate over x,y,z coords of normal, and then enable
    var vertexNormalPointer = gl.getAttribLocation(myShaderProgram, "nv");
    gl.vertexAttribPointer(vertexNormalPointer, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vertexNormalPointer);

    // Modelview matrix (look at method)
    var e = vec3(30.0, 40.0, 60.0);
    var a = vec3(0.0, 0.0, 0.0);
    var vup = vec3(0.0, 1.0, 0.0);
    var n = normalize(vec3(e[0]-a[0], e[1]-a[1], e[2]-a[2]));
    var u = normalize(cross(vup,n));
    var v = normalize(cross(n,u));
    var modelviewMatrix = [u[0], v[0], n[0], 0.0,
                           u[1], v[1], n[1], 0.0,
                           u[2], v[2], n[2], 0.0,
                          -u[0]*e[0]-u[1]*e[1]-u[2]*e[2],
                          -v[0]*e[0]-v[1]*e[1]-v[2]*e[2],
                          -n[0]*e[0]-n[1]*e[1]-n[2]*e[2], 1.0];
    //Modelview inverse transpose
    var modelviewMatrixInverseTranspose = [u[0], v[0], n[0], e[0],
                                           u[1], v[1], n[1], e[1],
                                           u[2], v[2], n[2], e[2],
                                            0.0,  0.0,  0.0,  1.0];
    var modelviewMatrixLocation = gl.getUniformLocation(myShaderProgram, "M");
    gl.uniformMatrix4fv(modelviewMatrixLocation, false, modelviewMatrix);
    var modelviewMatrixInverseTransposeLocation = gl.getUniformLocation(myShaderProgram, "M_inversetranspose");
    gl.uniformMatrix4fv(modelviewMatrixInverseTransposeLocation, false, modelviewMatrixInverseTranspose);

    //Projection matrix
    // var left = -30.0;
    // var right = 30.0;
    // var top_ = 30.0;
    // var bottom = -30.0;
    // var near = 50.0;
    // var far = 100.0;
    var left = -5.0;
    var right = 5.0;
    var top_ = 5.0;
    var bottom = -5.0;
    var near = 50.0;
    var far = 100.0;

    //Orthographic projection matrix
    var orthographicProjectionMatrix =
    [2.0/(right-left), 0.0, 0.0, 0.0,
    0.0, 2.0/(top_-bottom), 0.0, 0.0,
    0.0, 0.0, -2.0/(far-near), 0.0,
    -(left+right)/(right-left),
    -(top_+bottom)/(top_-bottom),
    -(far+near)/(far-near), 1.0];

    //Perspective projection matrix
    var perspectiveProjectionMatrix =
    [2.0*near/(right-left), 0.0, 0.0, 0.0,
     0.0, 2.0*near/(top_-bottom), 0.0, 0.0,
     (right+left)/(right-left),
     (top_+bottom)/(top_-bottom),
    -(far+near)/(far-near), -1.0,
     0.0, 0.0, -2.0*far*near/(far-near), 0.0];

    //Send the orthographic and perspective matrices as uniforms
    var orthographicProjectionMatrixLocation = gl.getUniformLocation(myShaderProgram, "P_orth");
    gl.uniformMatrix4fv(orthographicProjectionMatrixLocation, false, orthographicProjectionMatrix);
    var perspectiveProjectionMatrixLocation = gl.getUniformLocation(myShaderProgram, "P_persp");
    gl.uniformMatrix4fv(perspectiveProjectionMatrixLocation, false, perspectiveProjectionMatrix);

    //Matrix Select
    orthographicIsOn = 0;
    orthographicIsOnLocation = gl.getUniformLocation(myShaderProgram, "orthIsOn");
    gl.uniform1f(orthographicIsOnLocation, orthographicIsOn);

    //coefficients for drawObject
    var kaloc = gl.getUniformLocation(myShaderProgram, "ka");
    var kdloc = gl.getUniformLocation(myShaderProgram, "kd");
    var ksloc = gl.getUniformLocation(myShaderProgram, "ks");
    gl.uniform3f(kaloc, 0.5, 0.5, 0.5);
    gl.uniform3f(kdloc, 0.5, 0.5, 0.5);
    gl.uniform3f(ksloc, 1.0, 1.0, 1.0);
    var alphaloc = gl.getUniformLocation(myShaderProgram, "alpha");
    gl.uniform1f(alphaloc, 4.0);

    //First point light source location
    var p0loc = gl.getUniformLocation(myShaderProgram, "p0");
    gl.uniform3f(p0loc, 0.0, 0.0, 45.0);

    //values for light components
    var Ialoc = gl.getUniformLocation(myShaderProgram, "Ia");
    var Idloc = gl.getUniformLocation(myShaderProgram, "Id");
    var Isloc = gl.getUniformLocation(myShaderProgram, "Is");
    gl.uniform3f(Ialoc, 0.1, 0.1, 0.1);
    gl.uniform3f(Idloc, 0.8, 0.8, 0.5);
    gl.uniform3f(Isloc, 0.8, 0.8, 0.8);

    drawObject();

};


function drawObject() {
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT );
    gl.drawElements( gl.TRIANGLES, 3 * numTriangles, gl.UNSIGNED_SHORT, 0 );
    requestAnimFrame(drawObject);
}

function orthographic() {
  orthographicIsOn = 1;
  orthographicIsOnLocation = gl.getUniformLocation(myShaderProgram, "orthIsOn");
  gl.uniform1f(orthographicIsOnLocation, orthographicIsOn);
  console.log("orth");
}

function perspective() {
  orthographicIsOn = 0;
  orthographicIsOnLocation = gl.getUniformLocation(myShaderProgram, "orthIsOn");
  gl.uniform1f(orthographicIsOnLocation, orthographicIsOn);
  console.log("persp");

}

function specular() {


}

function LightButton1() {


}

function LightButton2() {

}

function getFaceNormals(vertices, indexList, numTriangles) {
  var faceNormals = [];
  for(var i=0; i<numTriangles; i++) {
    var p0 = vec3(vertices[indexList[3*i]][0],
                  vertices[indexList[3*i]][1],
                  vertices[indexList[3*i]][2]);
    var p1 = vec3(vertices[indexList[3*i+1]][0],
                  vertices[indexList[3*i+1]][1],
                  vertices[indexList[3*i+1]][2]);
    var p2 = vec3(vertices[indexList[3*i+2]][0],
                  vertices[indexList[3*i+2]][1],
                  vertices[indexList[3*i+2]][2]);
    var p1minusp0 = vec3(p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2]);
    var p2minusp0 = vec3(p2[0]-p0[0], p2[1]-p0[1], p2[2]-p0[2]);
    var faceNormal = cross(p1minusp0, p2minusp0);
    faceNormal = normalize(faceNormal);
    faceNormals.push(faceNormal);
  }
  return faceNormals;
}

function getVertexNormals(vertices, indexList, faceNormals, numVertices, numTriangles) {
  var vertexNormals=[];
  for(var j=0; j<numVertices; j++) {
    var vertexNormal = vec3(0,0,0);
      for(var i=0; i<numTriangles; i++) {
        if (indexList[3*i]==j | indexList[3*i+1]==j | indexList[3*i+2] == j) {
          vertexNormal[0] = vertexNormal[0] + faceNormals[i][0];
          vertexNormal[1] = vertexNormal[1] + faceNormals[i][1];
          vertexNormal[2] = vertexNormal[2] + faceNormals[i][2];
        }
      }
      vertexNormal = normalize(vertexNormal);
      vertexNormals.push(vertexNormal);
  }
  return vertexNormals;
}
