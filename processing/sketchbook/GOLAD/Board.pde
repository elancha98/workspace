class Board {
  
  private static final float MARGIN_PER = 0.05;
  
  private int height_;
  private int width_;
  
  private float cell_w;
  private float cell_h;
  private float margin_w;
  private float margin_h;
  
  private Cell[][] cells;
  
  public Board(int w, int h) {
    height_ = h;
    width_ = w;
    
    cell_w = (width*(1-MARGIN_PER))/w;
    margin_w = (MARGIN_PER*width)/(w+1);
    
    cell_h = (height*(1-MARGIN_PER))/h;
    margin_h = (MARGIN_PER*height)/(h+1);
    
    cells = new Cell[w][h];
    for (int x = 0; x < width_; x++) {
      for (int y = 0; y < height_; y++) {
        cells[x][y] = new Cell();
      }
    }
  }
  
  public void iterate() {
    
  }
  
  public void show() {
    for (int x = 0; x < width_; x++) {
      for (int y = 0; y < height_; y++) {
        pushMatrix();
        translate(x*cell_w + (x+1)*margin_w, y*cell_h + (y+1)*margin_h);
        cells[x][y].show(cell_w, cell_h);
        popMatrix();
      }
    }
  }
}