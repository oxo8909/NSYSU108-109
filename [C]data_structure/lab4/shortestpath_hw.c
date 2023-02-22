#include<stdio.h>
#define MAX_VERXTICES 8
#define FALSE 0
#define TRUE 1
#define INT_MAX 9999999

void shortestpath(int v, int cost[][MAX_VERXTICES], int distance[], int n, short int found[]);


void main(){
	//-綟痻皚                    0        1        2        3        4        5        6        7
	int cost[][MAX_VERXTICES] = {{      0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 0
								{    300,       0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 1
								{    600,     100,       0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 2
								{INT_MAX, INT_MAX,     120,       0, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 3
								{INT_MAX, INT_MAX, INT_MAX,    1500,       0,     150, INT_MAX, INT_MAX}, // 4
								{INT_MAX, INT_MAX, INT_MAX,     900, INT_MAX,       0,     700,    1400}, // 5
								{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,       0,     100}, // 6
								{    170, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,       0}};// 7
								
	int n = MAX_VERXTICES; // 竊翴计 
	int v = 4; //癬﹍翴 
	int distance[MAX_VERXTICES]; // 魁程祏禯瞒 
	short int found[MAX_VERXTICES]; // 魁砐竊翴 
					
	shortestpath(v, cost, distance, n, found);
}

// hw1
// void shortestpath(癬﹍翴, adjacency matrix, 程祏禯瞒, 竊翴计, 砐竊翴) 
void shortestpath(int v, int cost[][MAX_VERXTICES], int distance[], int n, short int found[]) {
	// please implement your algorithm here
	int i, u, w;
	
	int passBy[MAX_VERXTICES][MAX_VERXTICES], pass = 0;
	// refresh passBy[][]
	for(w=0; w<MAX_VERXTICES; ++w){
		for(u=0; u<MAX_VERXTICES; ++u){
			passBy[w][u] = -1;
		}
	}
	
	for(i=0; i<n; i++){
		// refresh found[] 
		found[i] = FALSE;
		// sort adjacency paths
		distance[i] = cost[v][i];
	}
	
	// v->v 
	distance[v] = 0;
	found[v] = TRUE;
	
	for(i=0; i<(n-2); i++){ 
		u = choose(distance, n, found); // the least cost of (v, u)
		found[u] = TRUE;
		
		for(w=0; w<n; w++){
			if(!found[w]){
				// distance[u] = cost[v][u]
				if(distance[u] + cost[u][w] < distance[w]){ // if ((v->u->w) < (v->w))
					distance[w] = distance[u] + cost[u][w];
					//path to w = v->u->w
					
					// 2. 硂翴ぇ玡璶竒筁翴 
					int p;
					for(p=0; p<MAX_VERXTICES; ++p){
						if(passBy[u][p]!=-1) passBy[w][pass++] = passBy[u][p];
					}
					// 1. 硂翴禯瞒程祏 
					passBy[w][pass++] = u;
				}
				pass = 0;
			}
		}
	}
	printf("%d to all shortest distances:", v);
	for(i=0; i<MAX_VERXTICES; i++){
		printf(" %d", distance[i]);
	}
	printf("\n");
	
	// print the path
	for(w=0; w<MAX_VERXTICES;++w){
		printf("%d", w);
		for(u=(MAX_VERXTICES-1); u>=0; u--){
			if(passBy[w][u]!=-1) printf(" <- %d", passBy[w][u]);
		}
		printf(" <- %d %d\n",v, distance[w]);
	}
}

int choose(int distance[], int n, short int found[]){
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0; i<n; ++i){
		if(distance[i] < min && !found[i]){
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}
