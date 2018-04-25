public class Grid {
  
  // 0   = X' - Y'
  // 60  = X' - Z'
  // 150 = Y' - Z'
  
  // (1,0) = x - y, (1/2, sqrt(3)/2) = x - z, (1/2, -sqrt(3)/2) = z -y
  
  // x/u = (1, 1)
  // y/v = (0, 1)
  // z/w = (0.5, 1 - sqrt(3)/2) = 15º / 2
  
  private int size;
  private float r, r_;
  private color back, line;
  
  public Grid(int size, int r) {
    this.size = size;
    this.r = r;
    r_ = r*sqrt(3)/2;
    back = color(151);
    line = color(200);
  }
  
  public void setBackgroundColor(color c) {
    back = c;
  }
  
  public void setLineColor(color c) {
    line = c;
  }
  
  public void show() {
  
    fill(back);
    stroke(line);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        PVector right = PVector.fromAngle(PI/6);
        PVector left = PVector.fromAngle(5*PI/6);
        
        PVector v = PVector.add(right.mult(i*2*r_), left.mult(j*2*r_));
        drawHexagon(v.x, v.y, r);
      }
    }
  }
  
  private void drawHexagon(float x, float y, float r) {
    drawNgon(x, y, r, 6);
  }
  
  private void drawNgon(float x, float y, float r, int n) {
    float increment = TWO_PI/n;
    beginShape();
    for (float a = 0; a < TWO_PI; a += increment) {
      vertex(x + r*cos(a), y + r*sin(a));
    }
    endShape();
  }
}