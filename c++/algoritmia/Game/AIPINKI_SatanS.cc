#include "Player.hh"
#include <queue>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME PINKI_SatanS


// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.

struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  typedef vector<int> VI;
  typedef vector<VI>  VVI;
  typedef vector<bool> VB;
  typedef vector<VB> VVB;



  // Stores the location of orks.
  VVI ork_at;

  // Returns true if winning.
  bool winning() {
    for (int pl = 0; pl < nb_players(); ++pl)
      if (pl != me() and total_score(me()) <= total_score(pl))
        return false;
    return true;
  }

struct camino {
    int sentit;
    Pos pos;
    int dist;
};

struct recorregut {
    int sentit;
    Pos pos;
    int cost = 0;
};

typedef pair<int, camino> PP;

struct Ordre {
    bool operator() (PP const &a, PP const &b) {
        if (a.first != b.first) return (a.first < b.first);
        else return (a.second.dist > b.second.dist);
        }
};




bool colapso(Pos p, int d) {
    Pos npos = p;
    if (pos_ok(npos)) {

        if (d == 0) {
            Dir dirr = Dir(0);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }
            dirr = Dir(1);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }

            dirr = Dir(3);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }


        }
        else if (d == 1) {

            Dir dirr = Dir(1);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }
            dirr = Dir(0);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
               Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }

            dirr = Dir(2);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);

                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }
            nposs = nposs + dirr;

        }
        else if (d == 2) {

            Dir dirr = Dir(2);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }
            dirr = Dir(1);
            nposs = npos + dirr;


            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);

                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }

            dirr = Dir(3);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }
        }
        else if (d == 3) {

            Dir dirr = Dir(3);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }

            dirr = Dir(2);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }

            dirr = Dir(0);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player == me()) return true;
            }
        }
    }
        return false;
}


int huyexciud(Pos p) {
    for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (not amenaza(p,d) and newcell.type == CITY and newcell.unit_id  == -1 and not colapso(newpos, d)) return d;
            else if (not amenaza(p,d) and newcell.type == PATH and newcell.unit_id  == -1 and not colapso(newpos, d)) return d;

        }
    }

    for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (not amenaza(p,d) and newcell.type == CITY and newcell.unit_id  == -1) return d;
            else if (not amenaza(p,d) and newcell.type == PATH and newcell.unit_id  == -1) return d;

        }
    }
    return huye(p);
}

bool noagua(Pos p) {
    for (int d = 0; d <= 3; ++d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (newcell.type == WATER) return false;
        }
    }
    return true;
}

int hastanunki(Pos p) {
    for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos) and not colapso(newpos, d)) {
            Cell newcell = cell(newpos);
            if (newcell.unit_id == -1) return d;
        }
    }

    return 4;
}



int desesperacion(Pos p) {
    Unit u = unit(cell(p).unit_id);
    for (int d = 0; d <= 3; ++d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            Unit e = unit(newcell.unit_id);
            if (newcell.unit_id != -1 and e.player != me() and e.health < u.health) return d;
        }
    }

    Pos npos = p + Dir(2);
    npos = npos + Dir(1);
    Pos nnpos = p + Dir(0);
    nnpos = nnpos + Dir(3);

    if ((pos_ok(npos) and (cell(npos).unit_id) != -1 and unit(cell(npos).unit_id).player != me() and u.health < unit(cell(npos).unit_id).health) and (pos_ok(nnpos) and cell(nnpos).unit_id != -1 and unit(cell(nnpos).unit_id).player != me() and u.health < unit(cell(nnpos).unit_id).health)) return 2;

    npos = p + Dir(2);
    npos = npos + Dir(3);
    nnpos = p + Dir(0);
    nnpos = nnpos + Dir(1);

    if ((pos_ok(npos) and (cell(npos).unit_id) != -1 and unit(cell(npos).unit_id).player != me() and u.health < unit(cell(npos).unit_id).health) and (pos_ok(nnpos) and cell(nnpos).unit_id != -1 and unit(cell(nnpos).unit_id).player != me() and u.health < unit(cell(nnpos).unit_id).health)) return 2;
    return hastanunki(p);
}

int huye(Pos p) {
   for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (not amenaza(p,d) and noagua(newpos)) {
                if (not colapso(newpos, d)) {
                    if (newcell.type == SAND and newcell.unit_id  == -1) return d;
                    else if (newcell.type == FOREST and newcell.unit_id  == -1) return d;
                    else if (newcell.type == GRASS and newcell.unit_id  == -1) return d;
                }
            }
        }
    }

    for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (not amenaza(p,d) and noagua(newpos)) {
                if (newcell.type == SAND and newcell.unit_id  == -1) return d;
                else if (newcell.type == FOREST and newcell.unit_id  == -1) return d;
                else if (newcell.type == GRASS and newcell.unit_id  == -1) return d;
            }
        }
    }

    for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (not amenaza(p,d) and not colapso(newpos, d)) {
                if (newcell.type == SAND and newcell.unit_id  == -1) return d;
                else if (newcell.type == FOREST and newcell.unit_id  == -1) return d;
                else if (newcell.type == GRASS and newcell.unit_id  == -1) return d;
            }
        }
    }

    for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (not amenaza(p,d)) {
                if (newcell.type == SAND and newcell.unit_id  == -1) return d;
                else if (newcell.type == FOREST and newcell.unit_id  == -1) return d;
                else if (newcell.type == GRASS and newcell.unit_id  == -1) return d;
            }
        }
    }

    for (int d = 3; d >= 0; --d) {
        Dir dir = Dir(d);
        Pos newpos = p + dir;
        if (pos_ok(newpos)) {
            Cell newcell = cell(newpos);
            if (not amenaza(p,d)) {
                if (newcell.type != WATER and newcell.unit_id  == -1) return d;
            }
        }
    }

    return desesperacion (p);

}



bool noorc(Pos p, int d) {
    Dir dir = Dir(d);
    Pos npos = p + dir;
    if (cell(npos).unit_id == -1) return true;
    return false;
}

bool totesmeves() {
    for (int i = 0; i < nb_cities(); ++i) {
        if (city_owner(i) != me()) return false;
    }
    return true;
}

bool amenaza(Pos p, int d) {
    Dir dir = Dir(d);
    Pos npos = p + dir;
    if (pos_ok(npos)) {
        Cell ncell = cell(npos);
        Unit u = unit(cell(p).unit_id);
        int c = cost(ncell.type);
        int co;
        if (d == 0) {
            Dir dirr = Dir(0);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                dirr = Dir(1);
                nposs = npos + dirr;

                if (pos_ok(nposs)) {
                    Cell nccell = cell(nposs);
                    co = cost(nccell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true; //c

                    if (cell(nposs).type != WATER) {

                        nposs = nposs + dirr;

                        if (pos_ok(nposs)) {
                            Cell nccell = cell(nposs);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - co >= u.health - c) return true;
                        }
                    }

                    dirr = Dir(3);
                    nposs = npos + dirr;

                    if (pos_ok(nposs)) {
                        Cell nccell = cell(nposs);
                        co = cost(nccell.type);
                        Unit e = unit(nccell.unit_id);
                        if (nccell.unit_id != -1 and e.player != me() and e.health - c>= u.health - c) return true;
                    }
                    if (cell(nposs).type != WATER) {
                        nposs = nposs + dirr;

                        if (pos_ok(nposs)) {
                            Cell nccell = cell(nposs);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health -co >= u.health - c) return true;
                        }
                    }
                }
            }

        }
        else if (d == 1) {

            Dir dirr = Dir(1);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                dirr = Dir(0);
                nposs = npos + dirr;

                if (pos_ok(nposs)) {
                   Cell nccell = cell(nposs);
                    co = cost(nccell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                    if (cell(nposs).type != WATER) {
                        nposs = nposs + dirr;

                        if (pos_ok(nposs)) {
                            Cell nccell = cell(nposs);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - co >= u.health - c) return true;
                        }
                    }
                }

                dirr = Dir(2);
                nposs = npos + dirr;

                if (pos_ok(nposs)) {
                    Cell nccell = cell(nposs);
                    co = cost(nccell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                    if (cell(nposs).type != WATER) {
                        nposs = nposs + dirr;

                        if (pos_ok(nposs)) {
                            Cell nccell = cell(nposs);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - co >= u.health - c) return true;
                        }
                    }
                }
            }

        }
        else if (d == 2) {

            Dir dirr = Dir(2);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                dirr = Dir(1);
                nposs = npos + dirr;


                if (pos_ok(nposs)) {
                    Cell nccell = cell(nposs);
                    co = cost(nccell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                    if (cell(nposs).type != WATER) {
                        nposs = nposs + dirr;

                        if (pos_ok(nposs)) {
                            Cell nccell = cell(nposs);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - co >= u.health - c) return true;
                        }
                    }
                }

                dirr = Dir(3);
                nposs = npos + dirr;

                if (pos_ok(nposs)) {
                    Cell nccell = cell(nposs);
                    co = cost(nccell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                    if (cell(nposs).type != WATER) {
                        nposs = nposs + dirr;

                        if (pos_ok(nposs)) {
                            Cell nccell = cell(nposs);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - co >= u.health - c) return true;
                        }
                    }
                }
            }

        }
        else if (d == 3) {

            Dir dirr = Dir(3);
            Pos nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;
            }
            dirr = Dir(2);
            nposs = npos + dirr;

            if (pos_ok(nposs)) {
                Cell nccell = cell(nposs);
                co = cost(nccell.type);
                Unit e = unit(nccell.unit_id);
                if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                if (cell(nposs).type != WATER) {
                    nposs = nposs + dirr;

                    if (pos_ok(nposs)) {
                        Cell nccell = cell(nposs);
                        Unit e = unit(nccell.unit_id);
                        if (nccell.unit_id != -1 and e.player != me() and e.health - co > u.health - c) return true;
                    }
                }

                dirr = Dir(0);
                nposs = npos + dirr;


                if (pos_ok(nposs)) {
                    Cell nccell = cell(nposs);
                    co = cost(nccell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - c >= u.health - c) return true;

                    if (cell(nposs).type != WATER) {
                        nposs = nposs + dirr;

                        if (pos_ok(nposs)) {
                            Cell nccell = cell(nposs);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - co > u.health - c) return true;
                        }
                    }
                }
            }

        }

        Pos nnpos = npos + dir;


        if (pos_ok(nnpos)) {
            Cell nncell = cell(nnpos);
            if (d == 0) {
                Dir dirr = Dir(0);
                Pos nposs = nnpos + dirr;
                if (pos_ok(nposs) and nncell.type != WATER) {
                    Cell nccell = cell(nposs);
                    int cos = cost(nncell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;

                }
                dirr = Dir(1);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(2)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(2)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }
                dirr = Dir(3);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(2)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(2)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }

            }
            if (d == 1) {
                Dir dirr = Dir(1);
                Pos nposs = nnpos + dirr;
                if (pos_ok(nposs) and nncell.type != WATER) {
                    Cell nccell = cell(nposs);
                    int cos = cost(nncell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;

                }
                dirr = Dir(0);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(3)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(3)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }
                dirr = Dir(2);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(3)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(3)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }

            }
            if (d == 2) {
                Dir dirr = Dir(2);
                Pos nposs = nnpos + dirr;
                if (pos_ok(nposs) and nncell.type != WATER) {
                    Cell nccell = cell(nposs);
                    int cos = cost(nncell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;

                }
                dirr = Dir(1);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(0)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(0)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }
                dirr = Dir(3);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(0)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(0)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }

            }
            if (d == 3) {
                Dir dirr = Dir(3);
                Pos nposs = nnpos + dirr;
                if (pos_ok(nposs) and nncell.type != WATER) {
                    Cell nccell = cell(nposs);
                    int cos = cost(nncell.type);
                    Unit e = unit(nccell.unit_id);
                    if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;

                }
                dirr = Dir(0);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(1)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(1)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }
                dirr = Dir(2);
                nposs = nnpos + dirr;
                if (pos_ok(nposs))  {
                    Cell nccell = cell(nposs);
                    if (nccell.type != WATER) {
                        if (nncell.type != WATER) {
                            int cos = cost(nncell.type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }
                        if (cell(nposs + Dir(1)).type != WATER) {
                            int cos = cost(cell(nposs + Dir(1)).type);
                            Unit e = unit(nccell.unit_id);
                            if (nccell.unit_id != -1 and e.player != me() and e.health - cos >= u.health - c) return true;
                        }

                    }

                }

            }
        }

    }
    return false;
}

bool connectats(Pos p) {
    VVB mirat(rows(), VB(cols(), false));
    queue<recorregut> cua;
    mirat[p.i][p.j] = true;
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos)) {
            Cell ncell = cell(npos);
            if (ncell.unit_id == -1) {
                if (ncell.type == CITY or ncell.type == PATH) {
                    recorregut a;
                    a.sentit = d;
                    a.pos = npos;
                    a.cost = cost(ncell.type);
                    cua.push(a);
                }
                if (ncell.type == CITY and city_owner(ncell.city_id) != me()) {
                    return true;
                }
            }
            mirat[npos.i][npos.j] = true;
        }
    }
    while (not cua.empty()) {
        recorregut x = cua.front(); cua.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    mirat[npos.i][npos.j] = true;
                    Cell ncell = cell(npos);
                    if (ncell.type == CITY or ncell.type == PATH) {
                        recorregut a;
                        a.sentit = x.sentit;
                        a.pos = npos;
                        a.cost = cost(ncell.type) + x.cost;
                        cua.push(a);
                    }
                    if (ncell.type == CITY and city_owner(ncell.city_id) != me()) {
                        return true;
                    }
                }
            }
        }
    }

    return false;

}

bool compconmeva(Pos p) {

}

int aloloco(Pos p) {
    VB noamenaza(4);
    for (int d = 0; d < 4; ++d) {
        if (not amenaza(p, d)) noamenaza[d] = true;

    }
    VVB mirat(rows(), VB(cols(), false));
    queue<recorregut> cua;
    mirat[p.i][p.j] = true;
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos)) {
            Cell ncell = cell(npos);
            if (ncell.unit_id == -1) {
                if (ncell.type != WATER) {
                    recorregut a;
                    a.sentit = d;
                    a.pos = npos;
                    a.cost = cost(ncell.type);
                    cua.push(a);
                }
                if (ncell.type == CITY) {
                    if (city_owner(ncell.city_id) != me() and noamenaza[d]) return d;
                    if (connectats(npos) and noamenaza[d]) return d;
                }
                else if (ncell.type == PATH and connectats(npos) and noamenaza[d]) {
                    return d;
                }
            }
       }
    }
    while (not cua.empty()) {
        recorregut x = cua.front(); cua.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    mirat[npos.i][npos.j] = true;
                    Cell ncell = cell(npos);
                    if (ncell.type != WATER) {
                        recorregut a;
                        a.sentit = x.sentit;
                        a.pos = npos;
                        cua.push(a);
                    }
                    if (ncell.type == CITY) {
                        int h = ncell.city_id;

                        if (city_owner(h) != me() and noamenaza[x.sentit] and noorc(p, x.sentit)) return x.sentit;
                        else if (connectats(npos) and noamenaza[x.sentit] and noorc(p, x.sentit)) return x.sentit;

                    }
                    else if (ncell.type == PATH and connectats(npos) and noamenaza[x.sentit]) {
                        if (noorc(p, x.sentit)) return x.sentit;
                    }
                }
            }
        }
    }
    return huyexciud(p);
}

int ciutatenciutat(Pos p) {
    Unit u = unit(cell(p).unit_id);
    bool puedesmovsincol = false;
    VB noamenaza(4);
    for (int d = 0; d < 4; ++d) {
        if (not amenaza(p, d)) noamenaza[d] = true;

    }
    VVB mirat(rows(), VB(cols(), false));
    queue<recorregut> cua;
    mirat[p.i][p.j] = true;
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos)) {
            Cell ncell = cell(npos);
            if (ncell.unit_id == -1) {
                if ((ncell.type == CITY and not colapso(npos, d)) or (ncell.type == PATH and not colapso(npos, d))) {
                    recorregut a;
                    a.sentit = d;
                    a.pos = npos;
                    cua.push(a);
                    puedesmovsincol = true;
                }

                if (ncell.type == CITY) {
                    int h = ncell.city_id;
                    if (city_owner(h) != me() and noamenaza[d] and not colapso(npos, d)) {
                        return d;
                    }
                }
                if (ncell.type == PATH) {
                    int h = ncell.path_id;
                    if (path_owner(h) != me() and noamenaza[d] and not colapso(npos, d)) {
                        return d;
                    }
                }
            }
        mirat[npos.i][npos.j] = true;
       }
    }

    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos) and not puedesmovsincol) {
            Cell ncell = cell(npos);
            if (ncell.unit_id == -1) {
                if (ncell.type == CITY or ncell.type == PATH) {
                    recorregut a;
                    a.sentit = d;
                    a.pos = npos;
                    cua.push(a);
                    puedesmovsincol = true;
                }
                if (ncell.type == CITY) {
                    int h = ncell.city_id;
                    if (city_owner(h) != me() and noamenaza[d]) {
                        return d;
                    }
                }
                if (ncell.type == PATH) {
                    int h = ncell.path_id;
                    if (path_owner(h) != me() and noamenaza[d]) {
                        return d;
                    }
                }
            }
        }
    }

    while (not cua.empty()) {
        recorregut x = cua.front(); cua.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    mirat[npos.i][npos.j] = true;
                    Cell ncell = cell(npos);

                    if (ncell.type == CITY) {
                        recorregut a;
                        a.sentit = x.sentit;
                        a.pos = npos;
                        a.cost = cost(ncell.type) + x.cost;
                        cua.push(a);
                    }
                    else if (ncell.type == PATH) {
                        if (ncell.unit_id != -1) {
                            Unit e = unit(ncell.unit_id);
                            if (e.player != me() and e.health > u.health) {}
                            else {
                                recorregut a;
                                a.sentit = x.sentit;
                                a.pos = npos;
                                a.cost = cost(ncell.type) + x.cost;
                                cua.push(a);
                            }

                        }
                        else {
                            recorregut a;
                            a.sentit = x.sentit;
                            a.pos = npos;
                            a.cost = cost(ncell.type) + x.cost;
                            cua.push(a);
                        }

                    }
                    if (ncell.type == CITY) {
                        int h = ncell.city_id;
                        if (city_owner(h) != me()) {
                            if (noamenaza[x.sentit] and noorc(p, x.sentit)) {
                                return x.sentit;
                            }
                        }
                    }
                    else if (ncell.type == PATH) {
                        int h = ncell.path_id;
                        if (path_owner(h) != me()) {
                            if (noamenaza[x.sentit] and noorc(p, x.sentit)) {
                                return x.sentit;
                            }
                        }
                    }

                }
            }

        }
    }
    if (not totesmeves()) return ciutprop(p);
    else return 4;
}




int ciutprop(Pos p) {
    VB noamenaza(4);
    for (int d = 0; d < 4; ++d) {
        if (not amenaza(p, d)) noamenaza[d] = true;

    }
    VVB mirat(rows(), VB(cols(), false));
    priority_queue<PP, std::vector<PP>, Ordre> cua;
    mirat[p.i][p.j] = true;
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos)) {
            Cell ncell = cell(npos);
            if (ncell.unit_id == -1) {
                if (ncell.type != WATER and noamenaza[d]) {
                    PP aa;
                    aa.first = -cost(ncell.type);
                    aa.second.sentit = d;
                    aa.second.pos = npos;
                    aa.second.dist = 1;
                    cua.push(aa);
                }
                if (ncell.type == CITY and city_owner(ncell.city_id) != me() and noamenaza[d]) {
                    return d;
                }
            }
        mirat[npos.i][npos.j] = true;
       }
    }

    while (not cua.empty()) {
        PP x = cua.top(); cua.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.second.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    mirat[npos.i][npos.j] = true;
                    Cell ncell = cell(npos);
                    if (ncell.type != WATER) {
                        PP aa;
                        aa.first = -cost(ncell.type) + x.first;
                        aa.second.sentit = x.second.sentit;
                        aa.second.pos = npos;
                        aa.second.dist += 1;
                        cua.push(aa);
                    }
                    int h = ncell.city_id;
                    if (ncell.type == CITY and city_owner(h) != me()) {
                        if (noamenaza[x.second.sentit]) {
                        return x.second.sentit;
                        }

                    }
                }
            }
        }
    }
    return huyexciud(p);
}

bool vorarara(Pos p, int i) {
    for (int d = 0; d <= 3; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (cell(npos).type == CITY) {
            int h = cell(npos).city_id;
            if (h == i) return true;
        }
    }
    return false;
}

bool boraciutatcami(Pos p) {
    for (int d = 0; d <= 3; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (cell(npos).type == CITY or cell(npos).type == PATH) return true;
    }
    return false;
}

int onesorcenemicc(Pos p, Unit u, int c) {
    VB noamenaza(4);
    for (int d = 0; d < 4; ++d) {
        if (not amenaza(p, d)) noamenaza[d] = true;

    }
    VVB mirat(rows(), VB(cols(), false));
    queue<recorregut> cua;
    mirat[p.i][p.j] = true;
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos)) {
            Cell ncell = cell(npos);
            Unit e = unit(ncell.unit_id);
            if (ncell.type == CITY and ncell.unit_id == -1) {
                recorregut a;
                a.sentit = d;
                a.pos = npos;
                a.cost = cost(ncell.type);
                cua.push(a);
            }
            if (ncell.type == CITY) {
                 if (ncell.unit_id != -1 and e.player != me() and u.health > e.health and not amenaza(p, d)) return d;

            }
            else  {
                if (ncell.unit_id != -1 and e.player != me() and u.health - cost(ncell.type) > e.health and not amenaza(p, d)) return d;
            }

       }
    }
    while (not cua.empty()) {
        recorregut x = cua.front(); cua.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    mirat[npos.i][npos.j] = true;
                    Cell ncell = cell(npos);
                    Unit e = unit(ncell.unit_id);
                    if (ncell.type == CITY) {
                        recorregut b;
                        b.sentit = x.sentit;
                        b.pos = npos;
                        b.cost = x.cost + cost(ncell.type);
                        cua.push(b);
                    }
                    if (ncell.unit_id != -1 and e.player != me() and e.health < u.health - cost(ncell.type) and not amenaza(p, x.sentit)) {
                        return x.sentit;
                    }
                }
            }
        }
    }
    return -1;
}

int onesorcenemicp(Pos p, Unit u) {
    VB noamenaza(4);
    for (int d = 0; d < 4; ++d) {
        if (not amenaza(p, d)) noamenaza[d] = true;

    }
    VVB mirat(rows(), VB(cols(), false));
    queue<recorregut> cua;
    mirat[p.i][p.j] = true;
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos)) {
            Cell ncell = cell(npos);
            Unit e = unit(ncell.unit_id);
            if (ncell.type == PATH and ncell.unit_id == -1) {
                recorregut a;
                a.sentit = d;
                a.pos = npos;
                a.cost = cost(ncell.type);
                cua.push(a);
            }
            if (ncell.type == PATH) {
                 if (ncell.unit_id != -1 and e.player != me() and u.health > e.health and not amenaza(p, d)) return d;

            }
            else  {
                if (ncell.unit_id != -1 and e.player != me() and u.health - cost(ncell.type) > e.health and not amenaza(p, d)) return d;
            }

       }
    }
    while (not cua.empty()) {
        recorregut x = cua.front(); cua.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    mirat[npos.i][npos.j] = true;
                    Cell ncell = cell(npos);
                    Unit e = unit(ncell.unit_id);
                    if (ncell.type == PATH) {
                        if (ncell.unit_id != -1 and e.player != me() and e.health > u.health) {}
                        else {
                            recorregut b;
                            b.sentit = x.sentit;
                            b.pos = npos;
                            b.cost = x.cost + cost(ncell.type);
                            cua.push(b);
                        }
                    }
                    if (ncell.unit_id != -1 and e.player != me() and e.health < u.health - cost(ncell.type) and not amenaza(p, x.sentit)) {
                        return x.sentit;
                    }
                }
            }
        }
    }
    return -1;
}



int onesorcenemic(Pos p, Unit u) {
    int costmin = 1E7;
    int dirmin = -1;
    VVB mirat(rows(), VB(cols(), false));
    queue<recorregut> cua;
    mirat[p.i][p.j] = true;
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir dir = Dir(d);
        Pos npos = p + dir;
        if (pos_ok(npos)) {
            mirat[npos.i][npos.j] = true;
            Cell ncell = cell(npos);
            Unit e = unit(ncell.unit_id);
            if (ncell.type != WATER and ncell.unit_id == -1 and not amenaza(p, d)) {
                recorregut a;
                a.sentit = d;
                a.pos = npos;
                a.cost = cost(ncell.type);
                cua.push(a);
            }
            if (ncell.unit_id != -1 and e.player != me() and u.health - cost(ncell.type) > e.health and not amenaza(p, d)) return d;
       }
    }
    queue<recorregut> cua2;
    while (not cua.empty()) {
        recorregut x = cua.front(); cua.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    Cell ncell = cell(npos);
                    Unit e = unit(ncell.unit_id);
                    if (pos_ok(npos) and ncell.unit_id == -1) {
                        recorregut b;
                        b.sentit = x.sentit;
                        b.pos = npos;
                        b.cost = x.cost + cost(ncell.type);
                        cua2.push(b);
                    }
                    if (pos_ok(npos) and ncell.unit_id != -1 and e.player != me() and e.health < (u.health - x.cost - cost(ncell.type)) and costmin >= (x.cost + cost(ncell.type)) and not amenaza(p, x.sentit)) {
                        costmin = x.cost + cost(ncell.type);
                        dirmin = x.sentit;
                    }
                }
            }
        }
    }
    for (int d = 0; d != DIR_SIZE; ++d) {
        Dir direction = Dir(d);
        Pos position = p + direction;
        for (int f = 0; f != DIR_SIZE; ++f) {
            Dir direction2 = Dir(f);
            Pos position2 = position + direction2;
            if (pos_ok(position2)) {
                mirat[position2.i][position2.j] = true;
            }
        }
    }

    while (not cua2.empty()) {
        recorregut x = cua2.front(); cua2.pop();
        for (int d = 0; d != DIR_SIZE; ++d) {
            Pos posx = x.pos;
            Dir dir = Dir(d);
            Pos npos = posx + dir;
            if (pos_ok(npos)) {
                if (mirat[npos.i][npos.j] == false) {
                    Cell ncell = cell(npos);
                    Unit e = unit(ncell.unit_id);
                    if (pos_ok(npos) and ncell.unit_id != -1 and e.player != me() and e.health < (u.health - x.cost - cost(ncell.type)) and costmin > (x.cost + cost(ncell.type)) and not amenaza(p, x.sentit)) {
                        costmin = x.cost + cost(ncell.type);
                        dirmin = x.sentit;
                    }
                }
            }
        }

    }

    if (dirmin != -1) {
        return dirmin;


    }
    else return -1;
}





void move(int id) {
    Unit u = unit(id); // info orco
    Pos pos = u.pos;

    ////////////////////////////le digo a mi orco lo que hacer segÄĹn donde se encuentre/////////////////////
    Cell actual = cell(pos);

     if (u.health < initial_health()/4) {
        int direorc = onesorcenemic(pos, u);
            if (direorc != -1) {
                Dir dirorc = Dir(direorc);
                execute(Command(id, dirorc));
                return;
            }
            else {
                int direorc = huye(pos);
                Dir dirorc = Dir(direorc);
                execute(Command(id, dirorc));
                return;
            }

     }

    if (actual.type == CITY) {
        int c = actual.city_id;
        int direorc = onesorcenemicc(pos, u, c);
        if (direorc != -1) {
            Dir dirorc = Dir(direorc);
            execute(Command(id, dirorc));
            return;
        }
        /*else if (compconmeva(pos)) {
            int ciutat = aloloco(pos);
            Dir dciutat = Dir(ciutat);
            execute(Command(id, dciutat));
            return;
        }*/
        else {
            int ciutat = ciutatenciutat(pos);
            Dir dciutat = Dir(ciutat);
            execute(Command(id, dciutat));
            return;
        }
    }
    else if (actual.type == PATH) {
        int direorc = onesorcenemicp(pos, u);
        if (direorc != -1) {
            Dir dirorc = Dir(direorc);
            execute(Command(id, dirorc));
            return;
        }
        else {
            int ciutat = ciutatenciutat(pos);
            Dir dciutat = Dir(ciutat);
            execute(Command(id, dciutat));
            return;
        }
    }
    else {
        int direorc = onesorcenemic(pos, u);
        if (direorc != -1) {
            Dir dirorc = Dir(direorc);
            execute(Command(id, dirorc));
            return;
        }
        else {
            int ciutat = ciutprop(pos);
            Dir dciutat = Dir(ciutat);
            execute(Command(id, dciutat));
            return;
        }
    }
}




  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {

    // If nearly out of time, do nothing.
    double st = status(me());
    if (st >= 0.93) return;

    if (round() == 0) {
      ork_at = VVI(rows(), VI(cols(), -1));
    }

    else {
      // Compare previous round with current one.
      for (int i = 0; i < rows(); ++i)
        for (int j = 0; j < cols(); ++j) {
          Cell c = cell(i, j);
          if (c.type == CITY                     and   //estamos analizando una ciudad
              ork_at[i][j] != c.unit_id          and   //lo que habia en la posicion analizada no puede ser el orco que hay ahora
              c.unit_id != -1                    and   //en la posicion tien que haber un orco
              unit(c.unit_id).player != me()) {        //el orco no puede ser mio
            cerr << "Enemy ork " << c.unit_id << " moved to CITY position " << Pos(i, j) << " of city " << c.city_id << endl;
          }
        }
      for (int i = 0; i < rows(); ++i)
        for (int j = 0; j < cols(); ++j)
          ork_at[i][j] = cell(i, j).unit_id; // Update for the next round (save all orks' new positions).
    }


      VI my_orks = orks(me()); // Get the id's of my orks.

      VI perm = random_permutation(my_orks.size());
      for (int k = 0; k < int(perm.size()); ++k) move(my_orks[perm[k]]);
    }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
