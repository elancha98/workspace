#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Test3

struct PLAYER_NAME : public Player {

	/**
	 * Factory: returns a new instance of this class.
	 * Do not modify this function.
	 */
	static Player *factory() { return new PLAYER_NAME; }

	/**
	 * Types and attributes for your player can be defined here.
	 */

	const double CITY_DECAY = 0.8;
	const double PATH_DECAY = 0.8;
	const double CONQUER_CITY_DISCOUNT = 0.85;
	const double CONQUER_PATH_DISCOUNT = 0.85;

	const int CITY_LEVELS = 20;
	const int PATH_LEVELS = 20;
	const int CONQUER_CITY_LEVELS = 10;
	const int TARGET_CITY_LEVELS = 12;
	const int CONQUER_PATH_LEVELS = 10;

	vector<vector<double>> background;
	vector<vector<double>> conquer;
	set<int> conquered_cities;
	set<int> conquered_paths;

	void expand(vector<Pos> &source, double start, double decay, int levels,
				vector<vector<double>> &target) {
		vector<Pos> cur = source;
		vector<Pos> next = vector<Pos>();
		set<Pos> proc;

		for (int i = 0; i < levels; i++) {
			for (Pos p : cur) {
				set<Pos>::iterator it = find(proc.begin(), proc.end(), p);
				if (it == proc.end()) {
					proc.insert(p);
					target[p.i][p.j] += start;
					for (int d = 0; d < NONE; d++) {
						Pos q = p + Dir(d);
						vector<Pos>::iterator it2 =
							find(cur.begin(), cur.end(), q);
						if (it2 == cur.end() and cell(q).type != WATER)
							next.push_back(q);
					}
				}
			}
			start *= decay;
			cur = next;
			next.clear();
		}
		proc.clear();
	}

	void analize_graph() {
		background = vector<vector<double>>(rows(), vector<double>(cols(), 0));
		for (int i = 0; i < nb_cities(); i++) {
			vector<Pos> c = city(i);
			expand(c, c.size() * bonus_per_city_cell(), CITY_DECAY, CITY_LEVELS,
				   background);
		}
		for (int i = 0; i < nb_paths(); i++) {
			vector<Pos> p = path(i).second;
			expand(p, p.size() * bonus_per_path_cell(), PATH_DECAY, PATH_LEVELS,
				   background);
		}
	}

	void analize_conquered() {
		bool recal = false;

		for (int i = 0; i < nb_cities(); i++) {
			if (find(conquered_cities.begin(), conquered_cities.end(), i) ==
				conquered_cities.end()) {
				if (city_owner(i) == me())
					recal = true;
			} else {
				if (city_owner(i) != me())
					recal = true;
			}
		}

		for (int i = 0; i < nb_paths(); i++) {
			if (find(conquered_paths.begin(), conquered_paths.end(), i) ==
				conquered_paths.end()) {
				if (path_owner(i) == me())
					recal = true;
			} else {
				if (path_owner(i) != me())
					recal = true;
			}
		}

		if (not recal) {
			cerr << "NO CHANGES" << endl;
			return;
		}

		conquered_paths.clear();
		conquered_cities.clear();

		conquer = vector<vector<double>>(rows(), vector<double>(cols(), 0));
		for (int i = 0; i < nb_cities(); i++) {
			if (city_owner(i) == me()) {
				conquered_cities.insert(i);
				vector<Pos> c = city(i);
				expand(c, -CONQUER_CITY_DISCOUNT * c.size(), CITY_DECAY,
					   CONQUER_CITY_LEVELS, conquer);
			}
		}
		for (int i = 0; i < nb_paths(); i++) {
			if (path_owner(i) == me()) {
				conquered_paths.insert(i);
				auto p = path(i);
				expand(p.second, -CONQUER_PATH_DISCOUNT * p.second.size(),
					   CONQUER_PATH_LEVELS, PATH_LEVELS, conquer);
				if (city_owner(p.first.first) != me()) {
					vector<Pos> c = city(p.first.first);
					expand(c, c.size() * bonus_per_city_cell(), CITY_DECAY,
						   TARGET_CITY_LEVELS, conquer);
				}
				if (city_owner(p.first.second) != me()) {
					vector<Pos> c = city(p.first.second);
					expand(c, c.size() * bonus_per_city_cell(), CITY_DECAY,
						   TARGET_CITY_LEVELS, conquer);
				}
			}
		}
	}

	void move(int id) {
		Unit u = unit(id);
		Pos p = u.pos;
		double m = -99999999999;
		int i = 5;
		for (int d = 0; d < DIR_SIZE; d++) {
			Pos q = p + Dir(d);
			double h = background[q.i][q.j] + conquer[q.i][q.j];
			if (pos_ok(q) and h > m) {
				m = h;
				i = d;
			} else if (h == m and random(0, 1)) {
				i = d;
			}
		}
		execute(Command(id, Dir(i)));
	}
	/**
	 * Play method, invoked once per each round.
	 */
	virtual void play() {
		if (round() == 0) {
			analize_graph();
			conquer = vector<vector<double>>(rows(), vector<double>(cols(), 0));
		}
		double st = status(me());
		if (st < 0.85)
			analize_conquered();

		vector<int> my_orks = orks(me());
		for (int i = 0; i < my_orks.size(); i++) {
			move(my_orks[i]);
		}
	}
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
