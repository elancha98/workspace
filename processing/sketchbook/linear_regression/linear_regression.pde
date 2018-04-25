ArrayList<PVector> points;
float m;
float n;

void setup() {
  points = new ArrayList<PVector>();
  m = 1;
  n = 0;
  size(640, 480);
}

void draw() {
  background(51);
  stroke(255);
  for (PVector p : points) {
    point(p.x, p.y);
  }
  line(0, n, width, m*width + n);
  linearRegression();
}

void mousePressed() {
  points.add(new PVector(mouseX, mouseY));
}

void linearRegression() {
  float s1 = 0;
  float s2 = 0;
  float s3 = 0;
  float s4 = 0;
  
  for (int i = 0; i < points.size(); i++) {
    s1 += points.get(i).x;
    s2 += points.get(i).x * points.get(i).x;
    s3 += points.get(i).y;
    s4 += points.get(i).x * points.get(i).y;
  }
  
  if (s1 == 0) {
    m = s3 / points.size();
    n = s4 / s2;
  } else {
    float mul = s2/s1;
    float s1_ = s1 - points.size()*mul;
    s4 -= s3*mul;
    
    // s1_ * n_ = s4
    n = s4 / s1_;
    // s1 * m + r * n = s3
    m = (s3 - points.size()*n)/s1;
  }
}