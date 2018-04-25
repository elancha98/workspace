#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME PFC_196
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
	tuple<stack<Pos>, int, Pos> a_star(Pos source,
									   function<bool(Pos &)> &is_target,
									   function<int(Pos &)> &heuristic) {
		struct Node {
			Pos pos;
			int parent = -1;
			int f, g = INT_MAX;

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
				int cost = cur.g;
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
						n.f = n.g + heuristic(n.pos);
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
	function<int(Pos &)> manhattan(Pos a) {
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

	function<bool(Pos &)> not_conquer = [&](Pos &a) {
		Cell c = cell(a);
		return (c.city_id != -1 and city_owner(c.city_id) != me()) or
			   (c.path_id != -1 and path_owner(c.path_id) != me());
	};

	function<int(Pos &)> h0 = [](Pos &a) { return 0; };

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

	pair<Pos, int> precompute_man(Pos start) {
		int d = 99;
		Pos target;
		for (int i = 0; i < nb_cities(); i++) {
			if (city_owner(i) != me()) {
				Pos t = city(i)[0];
				double d_ = abs(start.i - t.i) + abs(start.j - t.j);
				if (d_ < d) {
					d = d_;
					target = t;
				}
			}
		}
		return make_pair(target, d);
	}

	bool can_go(Pos a, Pos b) { return abs(a.i - b.i) + abs(a.j - b.j) == 1; }

	int man(Pos a, Pos b) { return abs(a.i - b.i) + abs(a.j - b.j); }

	const Pos cero;

	/**
	 * Real strategy starts here
	 */
	vector<int> my_orks;
	map<int, stack<Pos>> paths;
	map<int, Pos> enemies;

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

		bool jaquetemate = false;

		int other_health = unit(cell(target).unit_id).health;

		if (man(target, u.pos) < 3) {
			jaquetemate = true;
			if (other_health < u.health - go_cost)
				return execute(Command(id, go_to(u.pos, target)));
		}

		// If unit respawned
		if (paths[id].empty()) {
			if (c.type != CITY and c.type != PATH) {
				stack<Pos> path = get<0>(a_star(u.pos, city_path_target, h0));
				paths[id] = path;
			} else {
				pair<Pos, int> t = precompute_man(u.pos);
				if (t.second < 20) {
					auto f = manhattan(t.first);
					stack<Pos> path = get<0>(a_star(u.pos, not_conquer, f));
					paths[id] = path;
				}
			}
		}
		// If unit traveling to city
		Pos d;
		if (!paths[id].empty()) {
			d = paths[id].top();
			paths[id].pop();
		}
		Dir move;
		if (d == cero or (jaquetemate and path_to_enemy.top() == d)) {
			int i = random(0, 2);
			if (go_to(u.pos, path_to_enemy.top()) == Dir(i)) {
				move = Dir(i + 1) == NONE ? Dir(i - 1) : Dir(i + 1);
			} else {
				move = Dir(i);
			}
		} else {
			move = can_go(u.pos, d) ? go_to(u.pos, d) : NONE;
		}
		return execute(Command(id, move));
	}

	/**
	 * Play method, invoked once per each round.
	 */
	virtual void play() {
		my_orks = orks(me());
		for (int i = 0; i < my_orks.size(); i++) {
			move(my_orks[i]);
		}
	}
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
