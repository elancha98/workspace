#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Ronda_195
#include <functional>
#include <list>

struct PLAYER_NAME : public Player {

	/**
	 * Factory: returns a new instance of this class.
	 * Do not modify this function.
	 */

	static Player *factory() { return new PLAYER_NAME; }

	/**
	 * Types and attributes for your player can be defined here.
	 */

	/**
	 * A* main method of the algorithm
	 */
	int man(Pos a, Pos b) { return abs(a.i - b.i) + abs(a.j + b.j); }

	tuple<stack<Pos>, double, Pos> a_star(Pos source,
										  function<bool(Pos &)> &is_target,
										  function<double(Pos &)> &heuristic) {
		struct Node {
			Pos pos;
			int parent = -1;
			double f, g = 99999999;

			bool operator==(const Node &b) const { return (pos == b.pos); }

			bool operator<(const Node &b) const {
				if (f == b.f)
					return (pos < b.pos);
				return (f < b.f);
			}
		};

		set<Node> open;
		vector<Node> closed;

		auto find_ = [](set<Node>::iterator a, set<Node>::iterator b, Node &n) {
			for (; a != b; a++) {
				if ((*a) == n) {
					return a;
				}
			}
			return b;
		};

		Node s;
		s.pos = source;
		s.g = 0;
		s.f = s.g + heuristic(source);
		s.parent = -1;
		open.insert(s);

		stack<Pos> path;

		Node cur;
		while (not open.empty()) {
			cur = *(open.begin());

			if (is_target(cur.pos)) {
				double cost = cur.g;
				Pos t = cur.pos;
				path.push(cur.pos);
				while (cur.parent > -1) {
					path.push(closed[cur.parent].pos);
					cur = closed[cur.parent];
				}
				path.pop();
				return make_tuple(path, cost, t);
			}

			open.erase(cur);
			closed.push_back(cur);

			for (int d = 0; d < DIR_SIZE - 1; d++) {
				Node n;
				n.pos = cur.pos + Dir(d);

				if (cell(n.pos).type != WATER and
					find(closed.begin(), closed.end(), n) == closed.end()) {
					set<Node>::iterator it = find_(open.begin(), open.end(), n);
					if (it != open.end()) {
						n = (*it);
						open.erase(it);
					}

					int tentative_g = cur.g + cost(cell(n.pos).type);
					if (tentative_g < n.g) {
						n.parent = closed.size() - 1;
						n.g = tentative_g;
						n.f = n.g + heuristic(n.pos) + man(n.pos, source) * 0.6;
					}

					open.insert(n);
				}
			}
		}
		return make_tuple(path, 0, Pos(0, 0));
	}

	/**
	 * Useful methods
	 */
	function<double(Pos &)> manhattan(Pos a) {
		return [a](Pos &b) { return abs(a.i - b.i) + abs(a.j - b.j); };
	}

	function<bool(Pos &)> concrete_target(Pos a) {
		return [a](Pos &b) { return a == b; };
	}

	function<bool(Pos &)> city_path_target = [&](Pos &a) {
		CellType t = cell(a).type;
		return (t == CITY or t == PATH);
	};

	function<bool(Pos &)> enemy_target = [&](Pos &a) {
		Cell c = cell(a);
		return (c.unit_id != -1 and unit(c.unit_id).player != me());
	};

	function<bool(Pos &)> not_conquer(int c_id, int p_id) {
		return [&](Pos &a) {
			Cell c = cell(a);
			return (c.city_id != -1 and c.city_id != c_id and
					city_owner(c.city_id) != me()) or
				   (c.path_id != -1 and c.path_id != p_id and
					path_owner(c.path_id) != me());
		};
	}

	function<double(Pos &)> h0 = [](Pos &a) { return 0; };

	Dir go_to(Pos source, Pos dest) {
		int dy = dest.i - source.i;
		int dx = dest.j - source.j;
		if (dx == 1 and dy == 0)
			return RIGHT;
		if (dx == -1 and dy == 0)
			return LEFT;
		if (dy == 1 and dx == 0)
			return BOTTOM;
		if (dy == -1 and dx == 0)
			return TOP;
		return NONE;
	}

	Dir hide(Pos source, Pos dest) {
		Dir d = go_to(source, dest);
		switch (d) {
		case BOTTOM:
			return TOP;
		case TOP:
			return BOTTOM;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		default:
			return NONE;
		}
	}

	pair<Pos, int> precompute_man(Pos start) {
		int d = 999;
		int sc = cell(start).city_id;
		int sp = cell(start).path_id;
		Pos target;
		for (int i = 0; i < nb_paths(); i++) {
			auto p = path(i);
			if (path_owner(i) != me()) {
				if (city_owner(p.first.first) == me() and
					city_owner(p.first.second) != me()) {
					Pos cand = city(p.first.second)[0];
					if (man(start, cand) < d) {
						d = man(start, cand);
						target = cand;
					}
				}
				if (city_owner(p.first.first) != me() and
					city_owner(p.first.second) == me()) {
					Pos cand = city(p.first.first)[0];
					if (man(start, cand) < d) {
						d = man(start, cand);
						target = cand;
					}
				}
			} else if (city_owner(p.first.first) == me() and
					   city_owner(p.first.first) == me()) {
				vector<Pos> t = path(i).second;
				for (int j = 0; j < t.size(); j += 4) {
					int d_ = man(start, t[j]);
					if (d_ < d) {
						d = d_;
						target = t[j];
					}
				}
			}
		}
		/*
		for (int i = 0; i < nb_paths(); i++) {
			if (path_owner(i) != me() and i != sp) {
				vector<Pos> t = path(i).second;
				for (int j = 0; j < t.size(); j += 4) {
					double d_ = abs(start.i - t[j].i) + abs(start.j - t[j].j);
					if (d_ < d) {
						d = d_;
						target = t[j];
					}
				}
			}
		}*/
		return make_pair(target, d);
	}

	const Pos cero;

	/**
	 * Real strategy starts here
	 */
	vector<int> my_orks;
	// map<int, stack<Pos>> paths;
	map<int, Pos> enemies;
	// vector<int> target_city;

	void move(int id) {
		Unit u = unit(id);
		Cell c = cell(u.pos);

		stack<Pos> path_to_enemy;
		int go_cost;
		Pos target;
		tuple<stack<Pos>, int, Pos> temp;
		if (enemies[id] != cero) {
			auto f = manhattan(enemies[id]);
			temp = a_star(u.pos, enemy_target, f);
		} else {
			temp = a_star(u.pos, enemy_target, h0);
		}
		path_to_enemy = get<0>(temp);
		go_cost = get<1>(temp);
		target = get<2>(temp);
		enemies[id] = target;

		int other_health = unit(cell(target).unit_id).health;

		if (man(target, u.pos) < 4 and other_health >= u.health - go_cost) {
			return execute(Command(id, hide(u.pos, path_to_enemy.top())));
		}

		pair<Pos, int> t = precompute_man(u.pos);
		if (t.second == 999)
			return execute(Command(id, go_to(u.pos, path_to_enemy.top())));

		auto f = manhattan(t.first);
		auto comp = not_conquer(c.city_id, c.path_id);
		auto city_target = a_star(u.pos, comp, f);

		int city_points = city(cell(get<2>(city_target)).city_id).size();

		if (other_health >= u.health - go_cost or
			man(target, u.pos) < city_points / 3.0) {
			return execute(
				Command(id, go_to(u.pos, get<0>(city_target).top())));
		}

		return execute(Command(id, go_to(u.pos, path_to_enemy.top())));

		// Huir
		if (unit(cell(target).unit_id).health >= u.health - go_cost) {
			if (man(u.pos, target) < 3)
				return execute(Command(id, hide(u.pos, path_to_enemy.top())));

			pair<Pos, int> t = precompute_man(u.pos);
			auto f = manhattan(t.first);
			auto comp = not_conquer(c.city_id, c.path_id);
			stack<Pos> path = get<0>(a_star(u.pos, comp, f));
			if (path.top() == path_to_enemy.top() and man(u.pos, target) < 10)
				return execute(Command(id, hide(u.pos, path.top())));
			if (path.size() != 0)
				return execute(Command(id, go_to(u.pos, path.top())));
			return execute(Command(id, TOP));
		} else {
			Pos d = path_to_enemy.top();
			if (round() == 37) {
				cerr << u.pos << " -- " << d << "  " << u.health << " -- "
					 << unit(cell(target).unit_id).health << endl;
			}
			return execute(Command(id, go_to(u.pos, d)));
		}
	}

	/**
	 * Play method, invoked once per each round.
	 */
	virtual void play() {
		my_orks = orks(me());

		if (my_orks.size() == 4 * nb_orks())
			return;

		for (int i = 0; i < my_orks.size(); i++) {
			move(my_orks[i]);
			// if (status(me()) >= 0.9)
			// return;
		}
	}
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
