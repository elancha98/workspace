final color RED = color(171, 15, 15);
final color BLUE = color(15, 15, 181);
final color BLACK = color(51);

Board b;

void setup() {
  size(640, 480);
  noStroke();
  rectMode(CENTER);
  b = new Board(5, 5);
}

void draw() {
  background(BLACK);
  b.show();
}