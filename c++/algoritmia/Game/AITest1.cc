#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Test1
#include <functional>

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

	/*
	struct Conex {
		vector<int> cities;
		vector<int> paths;
		int simple_reward;
		int total_reward;
		int width, height;
	};

	vector<Conex> conexas;
	
	void analyze_graph() {
		// This gets all connected components

		map<int, vector<int> > adj;
		for (int i = 0; i < nb_cities(); i++) {
			adj.insert(make_pair(i, vector<int>()));
		}
		for (int i = 0; i < nb_paths(); i++) {
			Path p = path(i);
			adj[p.first.first].push_back(p.first.second);
			adj[p.first.second].push_back(p.first.first);
		}
		
		vector<bool> visited = vector<bool>(nb_cities(), false);
		vector<vector<int> > connected_comp = vector<vector<int> >();

		function<void(int,int)> DFSUtil;
		DFSUtil = [&](int city_id, int j) {
			visited[city_id] = true;
			connected_comp[j].push_back(city_id);
			
			for (int i = 0; i < adj[city_id].size(); i++) {
				if (not visited[adj.at(city_id)[i]])
					DFSUtil(adj.at(city_id)[i], j);
			}
		};
		
		int j = -1;
		for (int i = 0; i < nb_cities(); i++) {
			if (visited[i] == false) {
				connected_comp.push_back(vector<int>());
				j += 1;
				DFSUtil(i,j);
			}
		}
		cerr << connected_comp.size() << endl;
	}*/

	// Probably uneeded
	// vector<Unit> orks;
	// vector<Unit> enemies;

	vector<Pos> def_fronts;
	vector<Pos> atk_fronts;
	
	// vector<Conex> def;
	// vector<Conex> atk;

	/**
	 * Play method, invoked once per each round.
	 */
	virtual void play () {
		// analyze_graph();
	}
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
