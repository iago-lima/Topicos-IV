#include <bits/stdc++.h>

using namespace std;

typedef struct edge edge;

struct edge{
	int u;
	int v;
	int action;
};

typedef struct vertex vertex;

struct vertex{
	
	list<edge> sons;
	bool terminal;
	int value_utility;
	int level;
	int player;
};

struct S_tree{
	vector<vertex> vertexs;
};

vector<int> players;
vector<int> actions;

S_tree tree;
S_tree tree_zermelo;

void utility_node(int min, int max){
	for(int i = 0; i < tree.vertexs.size(); i++){
		if(tree.vertexs[i].terminal){
			tree.vertexs[i].value_utility = rand() % min + max;
		}
	}
}

void vertex_for_player(){
	for(int i = 0; i < tree.vertexs.size(); i++){
		tree.vertexs[i].player = players[rand() % players.size()];
	}
}

void generate_tree(int idx, int height_tree, int degree_max, int min, int max){

	vertex u = tree.vertexs[idx];

	if(u.level == height_tree){
		return;
	}

	int degree_maxAux = rand() % (degree_max + 1);

	if(!degree_maxAux){
		u.terminal = true;
		u.value_utility = rand() % (min + max);
		tree.vertexs[idx] = u;
	} 

	for(int i = 0; i < degree_maxAux; i++){
		vertex v;
		edge uv;

		v.level = u.level + 1;
		v.terminal = false;
		v.player = players[rand() % players.size()];

		if(v.level == height_tree){
			v.terminal = true;
			v.value_utility = rand() % (min + max);	
				}
		
		tree.vertexs.push_back(v);

		uv.u = idx; 
		uv.v = tree.vertexs.size() - 1;
		uv.action = actions[rand() % actions.size()];

		u.sons.push_back(uv);

		tree.vertexs[idx] = u;

		generate_tree(tree.vertexs.size() - 1, height_tree, degree_max, min, max);
	}
}

bool zermelo(int level){
	for(int i = 0; i < (int) tree_zermelo.vertexs.size(); i++){
		vertex u = tree_zermelo.vertexs[i];
		if(u.level == level){
			u.terminal = true;
			
			if(u.player == 0){
				list<edge>::iterator it;
				for(it = u.sons.begin(); it != u.sons.end(); it++){
					if(tree_zermelo.vertexs[it->v].terminal && tree_zermelo.vertexs[it->v].value_utility == 1){
						u.value_utility = 1;
						break;
					}
				}
			}
			if(u.player == 1){
				list<edge>::iterator it;
				for(it = u.sons.begin(); it != u.sons.end(); it++){
					if(tree_zermelo.vertexs[it->v].terminal && tree_zermelo.vertexs[it->v].value_utility == 0){
						u.value_utility = 0;
						break;
					}
				}	
			}
			tree_zermelo.vertexs[i] = u;
		}
	}

	if(level == 1){
		return tree_zermelo.vertexs[0].value_utility;
	}

	return zermelo(level - 1);
}

void generate_extensive(int n_players, int n_actions, int height_tree, int degree_max, int min, int max){
	for(int i = 0; i < n_players; i++){
		players.push_back(i);
	}

	for(int i = 0; i < n_actions; i++){
		actions.push_back(i);
	}

	vertex raiz;
	raiz.level = 1;
	raiz.terminal = false;
	raiz.player = players[0];

	tree.vertexs.push_back(raiz);
	
	generate_tree(0, height_tree, degree_max, min, max);
}

void print_tree(){
	for(int i = 0; i < tree.vertexs.size(); i++){
		printf("Player: %d - Terminal: %d - Value utility: %d, Level: %d" ,
			tree.vertexs[i].player, 
			tree.vertexs[i].terminal, 
			tree.vertexs[i].value_utility,
			tree.vertexs[i].level); 
		
		list<edge>::iterator it;

		printf("\n*****Sons*****\n");
		for(it = tree.vertexs[i].sons.begin(); it != tree.vertexs[i].sons.end(); it++){
			printf("Player: %d - Terminal: %d - Value utility: %d, Level: %d" ,
				tree.vertexs[it->v].player, 
				tree.vertexs[it->v].terminal, 
				tree.vertexs[it->v].value_utility,
				tree.vertexs[it->v].level); 

			printf("\nAction: %d\n", it->action);
		}
		printf("#####################\n");
	}
}

void print_tree_zermelo(){
	printf("Zermelo's Tree\n\n");
	for(int i = 0; i < tree_zermelo.vertexs.size(); i++){
		printf("Player: %d - Terminal: %d - Value utility: %d, Level: %d" ,
			tree.vertexs[i].player, 
			tree.vertexs[i].terminal, 
			tree.vertexs[i].value_utility,
			tree.vertexs[i].level);
		
		list<edge>::iterator it;

		printf("\n*****Sons*****\n");
		for(it = tree_zermelo.vertexs[i].sons.begin(); it != tree_zermelo.vertexs[i].sons.end(); it++){
		printf("Player: %d - Terminal: %d - Value utility: %d, Level: %d" ,
				tree.vertexs[it->v].player, 
				tree.vertexs[it->v].terminal, 
				tree.vertexs[it->v].value_utility,
				tree.vertexs[it->v].level); 

			printf("\nAction: %d\n", it->action);
		}
		printf("#####################\n");
	}
}



int main(){
	srand(time(NULL));
	
	//num_players, num_actions, height_tree, degree_max, min, max
	generate_extensive(2, 4, 3, 2, 0, 2);

	tree_zermelo = tree;
	print_tree();
	printf("Zermelo: %d\n", zermelo(3));
	printf("\n\n\n\n\n\n");
	print_tree_zermelo();
	return 0;
}