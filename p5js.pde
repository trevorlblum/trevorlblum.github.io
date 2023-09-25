/**
 * This example can be found in the Processing examples package
 * that comes with the Processing PDE.v
 * Processing > Examples > Basics > Form > Bezier
 * Adapted by Evelyn Eastmond
 */

boolean pressed=false;

void setup() {           // **change** void setup() to function setup()
  size(640, 360);    // **change** size() to createCanvas()
  stroke(255);strokeWeight(10);
  stroke(255);               // stroke() is the same
  noFill();                  // noFill() is the same
  println("try println");
  background(0);
}

void draw() {                         // **change** void draw() to function draw()
  if(pressed)background(255,0,0);else background(0);                          // background() is the same
  for (int i = 0; i < 200; i += 20) {     // **change** int i to var i
    bezier(mouseX-(i/2.0), 40+i, 410, 20, 440, 300, 240-(i/16.0), 300+(i/8.0)); // bezier() is the same
    textSize(20);rect(20,20,50,50);text("Running p5js.pde",200,200);  
   }
}

void mousePressed(){
if(!pressed)pressed=true;else pressed=false;
}
