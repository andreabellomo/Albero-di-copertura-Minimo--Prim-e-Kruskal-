#include <iostream>
using namespace std;
// struttura per rappresentare un arco 
struct  arco {    
		int sorg;  // nodo sorgente
		int dest; // nodo destinazione
		int peso; // peso relativo ad un arco
};

class  albero {

	private : 
		
		int radice; // padre del gruppo
		int altezza; // grandezza del gruppo
	
	public : 
	// Le funzioni get e set implementano la protezione dei dati evitando l' accesso diretto alla variabili
		void set_altezza(int x){
		
			altezza = x;
		}
	
		int get_altezza() {	return altezza;	}
	
		void set_radice(int x){
		
			radice = x;
		}
	
		int get_radice() { return radice;}
};

template <class T> class Grafo {  // struttura per rappresentare un grafo connesso Non orientato e pesato ( grafo di array di archi)
	
	private :
	
		int V, E; // numero di nodi e archi massimo
		arco* archi; 
		T **K; // Contiene gli indici corrispondenti ai vari nodi
		int len, n , m ;
		
		int findIndex(T x) {
		// Trova l'indice associato al nodo 
			for(int i=0; i<n; i++)
				if(*K[i] == x) return i;
			return -1;
		}
		
		albero *alberi;
		
		int find_root(int x)  // procedura per trovare il rappresentante dell' albero che contiene x
		{
			if (alberi[x].get_radice() == x) return x; // se il nodo è la radice di un albero torno il nodo stesso
			else return find_root(alberi[x].get_radice()); // altrimenti chiamo la procedura ricorsivamente 
		}
		
		
		void Union(int x, int y)  // procedura per unire due alberi disgiunti dati due nodi 
		{
			int root_x = find_root(x); // trova la root dell albero contenente x
			int root_y = find_root(y); // trova la root dell albero contenente y

			if (alberi[root_x].get_altezza() < alberi[root_y].get_altezza())          // unisce l' albero di altezza piu piccola sotto
				alberi[root_x].set_radice(root_y);                                   // l abero di altezza piu grande
			else if (alberi[root_x].get_altezza() > alberi[root_y].get_altezza())
					alberi[root_y].set_radice(root_x);
			else {
				// Se l altezza � la stessa uno dei due diventa radice e la sua altezza viene incrementata di un' unit�
				alberi[root_y].set_radice(root_x);
				alberi[root_x].set_altezza(alberi[root_x].get_altezza() + 1);
			}
        }	
        
		void printMST(arco* mst) {
			cout<< "Minimum Spanning Tree \n";
			int totale;
				for (int i = 0; i < V-1; i++)   
			{
				cout << mst[i].sorg << " -- " << mst[i].dest << " peso : " << mst[i].peso;
				cout<< endl;
				totale = totale + mst[i].peso;
			}
			
			cout<< "Peso totale del percorso : " << totale ;
		}	
			// procedura che affettua lo scambio tra due archi
		void scambia (arco& a, arco& b){  
			
			int temp_s,temp_d, temp_w;
			
			temp_s = a.sorg;
			temp_d = a.dest;
			temp_w = a.peso;
			
			a.sorg = b.sorg;
			a.dest = b.dest;
			a.peso = b.peso;
			
			b.sorg = temp_s;
			b.dest = temp_d;
			b.peso = temp_w;
			 
			 
		}   
		
      	// precedura che riordina gli archi in senso non decrescente per peso
		void Ordinamento ()
		{
			int i,j; 
			for (i=0;i<E;i++) 	
				for (j=i+1; j<E; j++) 
						if (archi[i].peso > archi[j].peso)
							scambia(archi[i],archi[j]);
		}	

	public :		
	
		Grafo(int V, int E)
		{

			n = m = 0;
			K = new T*[len];
			for(int i=0; i<len; i++) K[i] = NULL;
			
			this->V = V; // num nodi
			this->E = E; // num archi
			
			this->alberi = new albero[E]; // crea un array di tipo albero di cardinalita E
			this->archi = new arco[E]; // crea un array di tipo arco di caridnalita E
		}
  		
		
		Grafo<T>* addNode(T k) {
		// Aggiunge un nodo al grafo (se non gia� presente)
			if(n==V) return this;
			if(findIndex(k)>=0) return this;
			K[n] = new T(k);
			n++;
			return this;
		}
		
		
  		Grafo<T>* addEdge(T x, T y, int peso) {
		// Aggiunge un arco al grafo (se non gia� presente)
			int i = findIndex(x);
			int j = findIndex(y);
			if(i<0 || j<0) return this;
			if (m < E){
				
				archi[m].sorg = i;
				archi[m].dest = j;
				archi[m].peso = peso;
				m++;
				
			}
			return this;
		}
		
	

		void Kruskal_algorithm(){
			
			this->Ordinamento(); // ordina gli archi per peso  in ordine non decrescente
			
			for (int i = 0; i < V; i++) {     //  Creo V albero con un solo nodo.
				
				alberi[i].set_radice(i);     // imposta la radice come il nodo stesso
				alberi[i].set_altezza(0);    // imposta l altezza pari a 0
			}
			 
			arco *mst = new arco[V];  // array di struttura di tipo arco che conterrà l' MST finale
			
			for(int v = 0 , i = 0 ; i < E && v < V-1 ; i++ ){  // il ciclo verifica , per ogni arco (u,z) se le estremita' (u) e (z) appartengono allo stesso albero. In caso affermativo scarta l arco, altrimenti l arco (u,z) viene aggiunto al mst
				
				int u = find_root(archi[i].sorg); // trovare il rappresentante dell' albero che contiene u
				int z = find_root(archi[i].dest); // trovare il rappresentante dell' albero che contiene z
				
				if (u != z){  // se i due vertici(u,z) non fanno parte dello stesso albero l arco (u,z) viene aggiunto al mst 
					mst[v].sorg = archi[i].sorg;
					mst[v].dest = archi[i].dest;
					mst[v].peso = archi[i].peso;
					this->Union(u, z);  // i vertici  dei due alberi vengono fusi 
					v++;
					
				}
			}
			
			this->printMST(mst); 
		}	
		
	

};


int main(){
	
	Grafo<char> *Gr = new Grafo<char>(9, 13);
	
	
	Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
	Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
	Gr->addNode('8');
	
	Gr->addEdge('0','8',10)->addEdge('0','1',3);
	Gr->addEdge('1','8',9);
	Gr->addEdge('2','4',4);
	Gr->addEdge('3','5',6)->addEdge('3','6',1)->addEdge('3','7',2);
	Gr->addEdge('4','3',4)->addEdge('4','0',9);
	Gr->addEdge('5','6',3)->addEdge('5','3',7);
	Gr->addEdge('6','5',6);
	Gr->addEdge('8','2',8);
	
	Gr->Kruskal_algorithm();
	
}
