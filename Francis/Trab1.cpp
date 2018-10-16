/*
* @Author: pedrotorres
* @Date:   2018-06-19 18:59:45
* @Last Modified by:   pedrotorres
* @Last Modified time: 2018-06-24 19:43:45
*/

#include <bits/stdc++.h>

#define ii pair<int, int>

using namespace std;

typedef struct aresta aresta;
typedef struct vertice vertice;

struct vertice{
	//f_j
	int jogador;
	bool terminal;
	//mu_i
	int valor_utilidade;
	int nivel;
	list<aresta> filhos;
};

struct aresta{
	int u;
	int v;
	//f_a
	int acao;
};


struct T{
	vector<vertice> vertices;
};

vector<int> jogadores;
vector<int> acoes;
T arvore;
T arvore_ze;

// para cada vertice da árvore será associado um jogador aleatoriamente
void f_j_aleatorio(){
	for(int i = 0; i < arvore.vertices.size(); i++){
		arvore.vertices[i].jogador = jogadores[rand() % jogadores.size()];
	}
}

// para cada nó terminal é associado um valor de utilidade para o jogador daquele nó, aleatoriamente [min,max]
void mu_i_aleatorio(int valor_min, int valor_max){
	for(int i = 0; i < arvore.vertices.size(); i++){
		if(arvore.vertices[i].terminal){
			arvore.vertices[i].valor_utilidade = rand() % valor_min + valor_max;
		}
	}
}

void build_tree(int idx, int altura_arvore, int grau_maximo, int valor_min, int valor_max){

	vertice u = arvore.vertices[idx];

	if(u.nivel == altura_arvore){
		return;
	}

	int gm	 = rand() % (grau_maximo + 1);

	if(!gm){
		u.terminal = true;
		u.valor_utilidade = rand() % (valor_min + valor_max);
		arvore.vertices[idx] = u;
	} 

	for(int i = 0; i < gm; i++){
		vertice v;
		aresta uv;

		v.nivel = u.nivel + 1;
		v.terminal = false;
		v.jogador = jogadores[rand() % jogadores.size()];

		if(v.nivel == altura_arvore){
			v.terminal = true;
			v.valor_utilidade = rand() % (valor_min + valor_max);	
				}
		
		arvore.vertices.push_back(v);

		uv.u = idx; 
		uv.v = arvore.vertices.size() - 1;
		uv.acao = acoes[rand() % acoes.size()];

		u.filhos.push_back(uv);

		arvore.vertices[idx] = u;

		build_tree(arvore.vertices.size() - 1, altura_arvore, grau_maximo, valor_min, valor_max);
	}
}

void criar_jogo_extensivo(int n_jogadores, int n_acoes, int altura_arvore, int grau_maximo, int valor_min, int valor_max){
	for(int i = 0; i < n_jogadores; i++){
		jogadores.push_back(i);
	}

	for(int i = 0; i < n_acoes; i++){
		acoes.push_back(i);
	}

	vertice raiz;
	raiz.nivel = 1;
	raiz.terminal = false;
	raiz.jogador = jogadores[0];

	arvore.vertices.push_back(raiz);
	
	build_tree(0, altura_arvore, grau_maximo, valor_min, valor_max);
}	

void print_tree(){
	for(int i = 0; i < arvore.vertices.size(); i++){
		printf("Jogador: %d - Nivel: %d - Terminal: %d, Valor: %d" ,
			arvore.vertices[i].jogador, 
			arvore.vertices[i].nivel, 
			arvore.vertices[i].terminal, 
			arvore.vertices[i].valor_utilidade);
		
		list<aresta>::iterator it;

		printf("\n********************\n");
		for(it = arvore.vertices[i].filhos.begin(); it != arvore.vertices[i].filhos.end(); it++){
			printf("Jogador: %d - Nivel: %d - Terminal: %d, Valor: %d" ,
				arvore.vertices[it->v].jogador, 
				arvore.vertices[it->v].nivel, 
				arvore.vertices[it->v].terminal, 
				arvore.vertices[it->v].valor_utilidade);

			printf("\nAcao: %d\n", it->acao);
		}
		printf("#####################\n");
	}
}

void print_tree_ze(){
	for(int i = 0; i < arvore_ze.vertices.size(); i++){
		printf("Jogador: %d - Nivel: %d - Terminal: %d, Valor: %d" ,
			arvore_ze.vertices[i].jogador, 
			arvore_ze.vertices[i].nivel, 
			arvore_ze.vertices[i].terminal, 
			arvore_ze.vertices[i].valor_utilidade);
		
		list<aresta>::iterator it;

		printf("\n********************\n");
		for(it = arvore_ze.vertices[i].filhos.begin(); it != arvore_ze.vertices[i].filhos.end(); it++){
			printf("Jogador: %d - Nivel: %d - Terminal: %d, Valor: %d" ,
				arvore_ze.vertices[it->v].jogador, 
				arvore_ze.vertices[it->v].nivel, 
				arvore_ze.vertices[it->v].terminal, 
				arvore_ze.vertices[it->v].valor_utilidade);

			printf("\nAcao: %d\n", it->acao);
		}
		printf("#####################\n");
	}
}

bool jose_melo(int nivel){
	for(int i = 0; i < (int) arvore_ze.vertices.size(); i++){
		vertice u = arvore_ze.vertices[i];
		if(u.nivel == nivel){
			u.terminal = true;
			
			if(u.jogador == 0){
				list<aresta>::iterator it;
				for(it = u.filhos.begin(); it != u.filhos.end(); it++){
					if(arvore_ze.vertices[it->v].terminal && arvore_ze.vertices[it->v].valor_utilidade == 1){
						u.valor_utilidade = 1;
						break;
					}
				}
			}
			if(u.jogador == 1){
				list<aresta>::iterator it;
				for(it = u.filhos.begin(); it != u.filhos.end(); it++){
					if(arvore_ze.vertices[it->v].terminal && arvore_ze.vertices[it->v].valor_utilidade == 0){
						u.valor_utilidade = 0;
						break;
					}
				}	
			}
			arvore_ze.vertices[i] = u;
		}
	}

	if(nivel == 1){
		return arvore_ze.vertices[0].valor_utilidade;
	}

	return jose_melo(nivel - 1);
}

int main(){
	srand(time(NULL));

	//Exemplo José Melo.
	int n_jogadores = 2;
	int n_acoes = 4;
	int altura_arvore = 3;
	int grau_maximo = 2;
	int valor_min = 0;
	int valor_max = 2;

	criar_jogo_extensivo(n_jogadores, n_acoes, altura_arvore, grau_maximo, valor_min, valor_max);

	arvore_ze = arvore;
	bool a = jose_melo(3);	

	printf("Jose Melo: %d\n", a);

	return 0;
}