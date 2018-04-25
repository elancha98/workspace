class Cell {
  
  private static final float CENTER_PER = 0.2;
  
  private boolean alive;
  private boolean red;
  
  private boolean alive_next;
  
  public Cell() {
    alive = true;
    red = false;
    alive_next = false;
  }
  
  public void calculate_next(int n, boolean r) {
    if (n > 3) {
      alive_next = false;
    } else if (n < 2) {
      alive_next = false;
    } else if (!alive && n == 3) {
      alive_next = true;
      red = r;
    }
  }
  
  public void iterate(int n, boolean r) {
    alive = alive_next;
  }
  
  public void show(float size_x, float size_y) {
    if (red) {
      fill(RED);
    } else {
      fill(BLUE);
    }
    if (alive) {
      rect(size_x/2, size_y/2, size_x, size_y);
    }
    if (!alive_next) {
      fill(BLACK);
    }
    rect(size_x/2, size_y/2, size_x*CENTER_PER, size_y*CENTER_PER);
  }
  
  public boolean is_alive_next() {
    return alive_next;
  }
  
  public boolean is_alive() {
    return alive;
  }
  
  public boolean is_red() {
    return red;
  }
}