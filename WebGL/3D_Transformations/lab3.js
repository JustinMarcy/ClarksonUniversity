var gl;
var myShaderProgram;

var alpha, beta, gamma;
var tx, ty, tz;
var sx, sy, sz;
var speedX, speedY, speedZ;
var Mrx, Mry, Mrz;
var Mt;
var Ms;
var Mrxuniform, Mryuniform, Mrzuniform;
var Mtuniform;
var Msuniform;

var keyMap = [];
document.addEventListener("keydown", keyDownHandler, true);
document.addEventListener("keyup", keyUpHandler, true);

function init() {
    var canvas=document.getElementById("gl-canvas");
    gl=WebGLUtils.setupWebGL(canvas);
    if (!gl) { alert( "WebGL is not available" ); }
    gl.viewport( 0, 0, 512, 512);
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );

    //initialize rotation variables (angles)
    alpha = 0.0;
    beta = 0.0;
    gamma = 0.0;

    //initialize translation variables
    tx = 0;
    ty = 0;
    tz = 0;

    //initialize scaling variables
    sx = 1.0;
    sy = 1.0;
    sz = 1.0;

    Mrx = [1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0];
    Mry = [1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0];
    Mrz = [1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0];
    Mt =  [1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0];
    Ms =  [1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0];

    myShaderProgram = initShaders( gl,"vertex-shader", "fragment-shader" );
    gl.useProgram( myShaderProgram );

    Mrxuniform = gl.getUniformLocation(myShaderProgram, "Mrx");
    Mryuniform = gl.getUniformLocation(myShaderProgram, "Mry");
    Mrzuniform = gl.getUniformLocation(myShaderProgram, "Mrz");
    Mtuniform = gl.getUniformLocation(myShaderProgram, "Mt");
    Msuniform = gl.getUniformLocation(myShaderProgram, "Ms");

    gl.uniformMatrix4fv(Mrxuniform, false, flatten(Mrx));
    gl.uniformMatrix4fv(Mryuniform, false, flatten(Mry));
    gl.uniformMatrix4fv(Mrzuniform, false, flatten(Mrz));
    gl.uniformMatrix4fv(Mtuniform, false, flatten(Mt));
    gl.uniformMatrix4fv(Msuniform, false, flatten(Ms));

    // will include depth test to render faces correctly!
    gl.enable( gl.DEPTH_TEST );

    setupPoly();
    render();
}

function setupPoly() {

  // Vertices of Cube
      var vertices = [vec4( 0,  0,  -.4,  1), // p0
                      vec4( -.4, .4,  0,  1), // p1
                      vec4( -.4, -.4, 0,  1), // p2
                      vec4(  .4,  -.4,  0,  1), // p3
                      vec4(  .4,  .4,  0,  1), // p4
                      vec4( 0,  0,  .4,  1)]; // p5

      // Colors at Vertices of Cube
      var vertexColors = [vec4( 0.0, 0.0, 1.0, 1.0), // p0
                          vec4( 0.0, 1.0, 0.0, 1.0), // p1
                          vec4( 1.0, 0.0, 0.0, 1.0), // p2
                          vec4( 1.0, 1.0, 0.0, 1.0), // p3
                          vec4( 1.0, 0.0, 1.0, 1.0), // p4
                          vec4( 0.0, 1.0, 1.0, 1.0)]; // p5
      // Every face on the cube is divided into two triangles,
      // each triangle is described by three indices into
      // the array "vertices"
      var indexList = [0, 1, 2,
                       0, 2, 3,
                       0, 3, 4,
                       0, 4, 1,
                       1, 2, 5,
                       2, 3, 5,
                       3, 4, 5,
                       4, 1, 5];


    // Code here to handle putting above lists into buffers
    var vertexBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vertexBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );

    var myPosition = gl.getAttribLocation( myShaderProgram, "myPosition" );
    gl.vertexAttribPointer(myPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( myPosition );

    var colorBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, colorBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertexColors), gl.STATIC_DRAW );

    var myColor = gl.getAttribLocation( myShaderProgram, "myColor" );
    gl.vertexAttribPointer( myColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( myColor );

    // will populate to create buffer for indices
    var iBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ELEMENT_ARRAY_BUFFER, iBuffer );
    gl.bufferData( gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(indexList), gl.STATIC_DRAW );
}

function rotateAroundX() {
    // will implement this to rotate the cube around the X-axis
    Mrx = [1.0,
          0.0,
          0.0,
          0.0,
          0.0,
          Math.cos(alpha),
          Math.sin(alpha),
          0.0,
          0.0,
          -Math.sin(alpha),
          Math.cos(alpha),
          0.0,
          0.0,
          0.0,
          0.0,
          1.0];

    gl.uniformMatrix4fv(Mrxuniform, false, flatten(Mrx));
    render();
}

function rotateAroundY() {
    // will implement to rotate the cube around the Y-axis
    Mry = [Math.cos(beta),
          0.0,
          -Math.sin(beta),
          0.0,
          0.0,
          1.0,
          0.0,
          0.0,
          Math.sin(beta),
          0.0,
          Math.cos(beta),
          0.0,
          0.0,
          0.0,
          0.0,
          1.0];

    gl.uniformMatrix4fv(Mryuniform, false, flatten(Mry));
    render();
}

function rotateAroundZ() {
    // will implement this to rotate the cube around the X-axis
    Mrz = [Math.cos(gamma),
          Math.sin(gamma),
          0.0,
          0.0,
          -Math.sin(gamma),
          Math.cos(gamma),
          0.0,
          0.0,
          0.0,
          0.0,
          1.0,
          0.0,
          0.0,
          0.0,
          0.0,
          1.0];

    gl.uniformMatrix4fv(Mrzuniform, false, flatten(Mrz));
    render();
}

function translate() {
  Mt = [1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        tx, ty, tz, 1.0];

  gl.uniformMatrix4fv(Mtuniform, false, Mt);
  render();
}

function scale() {
  Ms = [sx, 0.0, 0.0, 0.0,
        0.0, sy, 0.0, 0.0,
        0.0, 0.0, sz, 0.0,
        0.0, 0.0, 0.0, 1.0];

  gl.uniformMatrix4fv(Msuniform, false, Ms);
  render();
}

function render() {
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT );
    var numVertices = 24;
    // will populate to render the cube
    gl.drawElements( gl.TRIANGLES, numVertices, gl.UNSIGNED_BYTE, 0 );

}

function keyDownHandler(event){
    var keyCode = event.keyCode;
    keyMap[keyCode] = true;
    executeMovement();
}
function keyUpHandler(event){
    var keyCode = event.keyCode;
    keyMap[keyCode] = false;
    executeMovement();
}
function executeMovement(){
    if(keyMap[81] == true){
      alpha = alpha + 0.1;
      rotateAroundX();
    }
    if(keyMap[87] == true){
      beta = beta + 0.1;
      rotateAroundY();
    }
    if(keyMap[69] == true){
      gamma = gamma + 0.1;
      rotateAroundZ();
    }
    if(keyMap[65] == true){
      sx = sx - 0.05;
      scale();
    }
    if(keyMap[83] == true){
      sx = sx + 0.05;
      scale();
    }
    if(keyMap[90] == true){
      sy = sy - 0.05;
      scale();
    }
    if(keyMap[88] == true){
      sy = sy + 0.05;
      scale();
    }
    if(keyMap[37] == true){
      tx = tx - 0.05;
      translate();
    }
    if(keyMap[39] == true){
      tx = tx + 0.05;
      translate();
    }
    if(keyMap[38] == true){
      ty = ty + 0.05;
      translate();
    }
    if(keyMap[40] == true){
      ty = ty - 0.05;
      translate();
    }
}
