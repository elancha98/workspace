Grid g;
void setup(){
  size(640, 480);
  g = new Grid(7, 10);
}


void draw() {
  background(0);
  translate(320, 240);
  g.show();
}