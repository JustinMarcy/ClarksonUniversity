//Justin Marcy
var myShaderProgram;
var canvas;
var gl;
var init;
var fColorLocation;

function init() {
  console.log('This is working');
  canvas = document.getElementById('gl-canvas');
  gl = canvas.getContext('webgl');
  if (!gl) { alert( "WebGL is not available" ); }

  gl.viewport(0, 0, 512, 512);
  gl.clearColor(0.0, 0.5, 0.8, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  myShaderProgram = initShaders(gl, "vertex-shader", "fragment-shader");
  gl.useProgram(myShaderProgram);
  fColorLocation = gl.getUniformLocation(myShaderProgram, "fColor");
  drawSquare();
  drawHexagon();
  drawEllipse();
}

function drawSquare(){
var p0 = vec2(0.0, 0.0);
var p1 = vec2(-0.8, 0.0);
var p2 = vec2(-0.8, -0.8);
var p3 = vec2(0.0, -0.8);
var arrayOfPoints = [p0, p1, p2, p3];

var bufferId = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, bufferId);
gl.bufferData(gl.ARRAY_BUFFER, flatten(arrayOfPoints), gl.STATIC_DRAW);

var myPositionAttribute = gl.getAttribLocation(myShaderProgram, "myPosition");
gl.vertexAttribPointer(myPositionAttribute, 2, gl.FLOAT, false, 0, 0);
gl.enableVertexAttribArray(myPositionAttribute);

gl.uniform4f(fColorLocation, 0.2, 0.2, 0.4, 1.0);
gl.drawArrays(gl.TRIANGLE_FAN, 0, 4);
}

function drawHexagon(){
var p0 = vec2(0.2, 0.0);
var p1 = vec2(0.5, 0.2);
var p2 = vec2(0.8, 0.0);
var p3 = vec2(0.8, -0.3);
var p4 = vec2(0.5, -0.5);
var p5 = vec2(0.2,-0.3);
var arrayOfPoints = [p0, p1, p2, p3, p4, p5];

var bufferId = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, bufferId);
gl.bufferData(gl.ARRAY_BUFFER, flatten(arrayOfPoints), gl.STATIC_DRAW);

var myPositionAttribute = gl.getAttribLocation(myShaderProgram, "myPosition");
gl.vertexAttribPointer(myPositionAttribute, 2, gl.FLOAT, false, 0, 0);
gl.enableVertexAttribArray(myPositionAttribute);

gl.uniform4f(fColorLocation, 0.0, 1.0, 0.0, 1.0);
gl.drawArrays(gl.LINE_LOOP, 0, 6);
}

function drawEllipse() {

var arrayOfPointsForCircle=[];
var thetastart = 0;
var thetaend = 2 * Math.PI;
var n=100;
var thetastepsize = (thetaend - thetastart) / n;
var i;
var a = 0;
var b = 0.2;
var c = 0.3
var d = 0.2;
for (i=0; i<n; i++) {
  var theta = thetastart + i * thetastepsize;
  var x = c * Math.cos(theta) + a;
  var y = d * Math.sin(theta) + b;
  var p = vec2(x,y);
  arrayOfPointsForCircle.push(p);
}

var bufferId = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, bufferId);
gl.bufferData(gl.ARRAY_BUFFER, flatten(arrayOfPointsForCircle), gl.STATIC_DRAW);

var myPositionAttribute = gl.getAttribLocation(myShaderProgram, "myPosition");
gl.vertexAttribPointer(myPositionAttribute, 2, gl.FLOAT, false, 0, 0);
gl.enableVertexAttribArray(myPositionAttribute);

gl.uniform4f(fColorLocation, 1.0, 1.0, 0.0, 1.0);
gl.drawArrays(gl.TRIANGLE_FAN, 0, n);
}
