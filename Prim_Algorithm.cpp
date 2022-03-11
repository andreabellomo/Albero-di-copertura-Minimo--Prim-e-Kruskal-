#include <iostream>
#include <ctime>
#include <math.h>
#include <algorithm> 
#include <vector> 

using namespace std;


#define inf len+1

// struttura per rappresentare un nodo 
template <class H> struct nodo{
	H etichetta; // etichetta del nodo
	int stima; // stima distanza
	int p; // predecessore
	bool convergenza; //  andato a convergenza ? si/no
	// overload operatore " < "
	bool operator< (const nodo rhs)
	{
		if( stima < rhs.stima)	return true;
		else return false;
	}
	// overload operatore " > "
		bool operator> ( const nodo rhs)
	{
		if( stima > rhs.stima)	return true;
		else return false;
	}
};

template <class H> class Grafo {
	private:
		int len, n, m;
		nodo<H>* mst; //  un array di struct , un array di tipo nodo , conterra' l mst finale
		/* 	n numero di nodi effettivo, 
			m numero di archi effettivo, 
			len numero massimo di nodi
		*/
		int **M; // matrice di adiacenza
		H **K;  //Contiene gli indici corrispondenti ai vari nodi
		
		// precedura che trova l'indice associato al nodo 
		int findIndex(H x) {
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
		
		
		void initial (){   // procedura che inizializza i nodi . Essa viene chiamata come prima istruzione dell' algoritmo di Prim
		
			for(int i = 0; i<n; i++){  // per ogni nodo 
				nodo<H> vtx;
				vtx.etichetta = *K[i]; // assegna un etichetta
				vtx.p = -2; // imposta il predecessore a -2 
				vtx.convergenza = false; // il nodo non � andato a convergenza
				vtx.stima = INT_MAX; // imposta la stima a infinito
				mst[i] = vtx; // lo aggiunge all' array .
			}
		}
		
		void relax (int index, int minimo){  
			mst[index].p = minimo;  // aggiorna campo predecessore
			mst[index].stima = M[minimo][index]; // aggiorna valore di stima
		}
		
		void scan ( int minimo){
	      // aggiorna il campo 'stima' e 'p' di qualsiasi vertice al minimo , ma che non appartiene all' MST
			for( int i = 0 ; i < n ; i++){
				if(M[minimo][i]  != 0 && mst[i].convergenza == 0 && M[minimo][i] < mst[i].stima){ 
					relax(i, minimo);	
				}
			}
		}
		
		
		void printMST() 
			{ 
    			cout<<"Arco \tPeso \n"; 
    			for (int i = 1; i < n; i++) 
       			cout<<mst[mst[i].p].etichetta<<" - "<<mst[i].etichetta<<" \t "<<mst[i].stima<<" \n"; 
			} 
			
	public:
		Grafo(int len) {
			this->len = len;
			n = m = 0;
			M = new int*[len];
			for(int i=0; i<len; i++) {
				M[i] = new int[len];
				for(int j=0; j<len; j++)
					M[i][j] = 0;
			}
			K = new H*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			
			mst = new nodo<H>[len];
		}

		
		Grafo<H>* addNode(H k) {
			// Aggiunge un nodo al grafo (se non gia'� presente)
			if(n==len)   return this;
			if(findIndex(k)>=0) return this;
			K[n] = new H(k);
			n++;
			return this;
		}

		
		Grafo<H>* addEdge(H x, H y, int peso) {
			// Aggiunge un arco al grafo (se non gia'� presente)
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]) {
				M[i][j] = peso;
				M[j][i] = peso;
				m++;
			}
			return this;
		}
		
		
		int trova_min(){
			// procedura che trova il nodo che ha stima minore non ancora incluso nell' MST (convergenza == 0) 
			int min = INT_MAX;
			int min_index = -1;
			
			int i;
			for( i= 0; i<n; i++){
				if(mst[i].convergenza == 0 && mst[i].stima < min){
					min = mst[i].stima;
					min_index = i;
				}
			}
			return min_index;
			
		}


		void prim (){
			
			this->initial(); // funzione che inizializza
	
			mst[0].p = -1;     // imposta il predecessore a -1 
			mst[0].stima = 0; // imposta la stima a 0 del primo nodo all' interno del vettore per fare in modo che essa venga scelto per primo
			
			for (int c = 0; c < n -1 ; c++){
				
				int minimo = trova_min(); // Prende il nodo con stima minima non ancora incluso nell' MST
				
				if(minimo == -1){
					cout<< " errore ";
					return;
				}
				
				mst[minimo].convergenza = 1; // Imposta convergenza ad 1 
				this->scan(minimo); // chiama la scan sul minimo
				
			}
			
			this->printMST();
			
		}
};		

int main() {

	Grafo<char> *Gr = new Grafo<char>(9);
	Gr->addNode('a')->addNode('b')->addNode('c')->addNode('d');
	Gr->addNode('e');
	
	
	Gr->addEdge('a','b',2);
	Gr->addEdge('b','d',6);
	Gr->addEdge('b','a',2);
	Gr->addEdge('b','c',3);
	Gr->addEdge('b','d',8)->addEdge('b','e',5);
	Gr->addEdge('c','b',3)->addEdge('c','e',7);
	Gr->addEdge('d','a',6);
	Gr->addEdge('d','b',8);
	Gr->addEdge('d','e',9);
	Gr->addEdge('e','b',5);
	Gr->addEdge('e','c',7);
	Gr->addEdge('e','d',9);
	Gr->prim();
	
}
