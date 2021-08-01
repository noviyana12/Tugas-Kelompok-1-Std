//code by Noviyana
#include<iostream>
#include<conio.h>
#include <list>
#define MAX 15
using namespace std;

//DEKLARASI GLOBAL VARIABLE
int stages,graf[MAX][MAX];
int bobot[MAX],p[MAX],n, jumlah_edge;

//KELAS GRAF UNTUK LIST ADJ (UNTUK TAMPIL PATH)
class Graf_adj{
	int n;
	list<int>* adj; // pointer ke array yang mengandung list adj
	
    void tampilsemua_path2(int, int, bool[], int[], int&);
    
public:
    Graf_adj(int n); // Constructor
    void tambahEdge(int i, int j);
    void tampilsemua_path(int s, int d);    
};

Graf_adj::Graf_adj(int n)
{
    this->n = n;
    adj = new list<int>[n];
}

//FUNGSI UNTUK MENGHITUNG NODE MINIMUM YANG DAPAT DILALUI
int hitung_min(int i,int n)
{
    int min=9999; //merepresentasikan infinity
    int node_min;
    for(int j=0; j<n; j++)
        {
            if(min>(graf[i][j]+bobot[j]))
                {
                    min=graf[i][j]+bobot[j];
                    node_min=j;
                }
        }
    return node_min;
}

//FUNGSI MENGHITUNG JARAK TERPENDEK (DYNAMIC PROGRAMMING)
int hitung_shortestgraph(int n)
{
    int i,j;
    int d[n];
    for(i=0; i<n; i++){
    	bobot[i]=0;//insialisasi nilai awal bobot (cost/panjang jalan)
	}
    for(i=n-2; i>=0; i--){
            j=hitung_min(i,n);
            bobot[i]=graf[i][j]+bobot[j];
            d[i]=j;
    }
    p[0]=0;
    p[stages-1]=n-1;
    for(i=1; i<stages-1; i++)
        p[i]=d[p[i-1]];
        
    return bobot[0];
}

//FUNGSI MEMBUAT MATRIKS GRAF (INPUT NODE LOKASI)
int input_jalur()
{
    int i,j,m,p,jumlah_node=0;
    char jalan; 
	int jumlah_jalan;
	jumlah_edge = 0;
	cout << "Masukkan jumlah node (titik lokasi) : ";
	cin >> jumlah_node;
	cout << endl;

	cout << "Masukkan jumlah stages (tingkatan lokasi) : ";
	cin >> stages;
    cout << endl;
    
    for(i=0; i<jumlah_node; i++)
        for(j=0; j<jumlah_node; j++)
            graf[i][j]=9999; //inisialisasi nilai awal graf
    
    
    pilihan:  
    cout << "Apakah Anda ingin memasukkan jalan (edge) langsung antar lokasi? [y/n] : ";
    cin >> jalan;

    if(jalan == 'y' || jalan == 'Y'){
    	cout << "Berapa jalan yang ingin ditambahkan? : ";
        cin >> jumlah_jalan;
        cout << endl;
        
    	for(int k=0;k<jumlah_jalan;k++){
    		cout << "Masukkan titik lokasi awal (menggunakan angka, ex: A=1): ";
    		cin >> i;

    		cout << "Masukkan titik lokasi akhir : ";
    		cin >> j;
			
    		cout << "Masukkan panjang jalan (bobot) dari titik " << i << " ke " << j << " : ";
    		cin >> graf[i-1][j-1];
    		cout << endl;
		}
		jumlah_edge += jumlah_jalan;
    
    	goto pilihan;
	}
	else if(jalan == 'n' || jalan == 'N'){
		cout << "Ket : jalan sebanyak " << jumlah_edge << " jalan telah ditambahkan dari " << jumlah_node << " titik lokasi!";
		cout << endl;
	}
    return jumlah_node;
}

//FUNGSI TAMPIL JARAK TERPENDEK
void tampil_jarak(int jarak)
{
    int i, node;
    
    cout << endl;
    cout << "Rute terpendek yang dapat dilalui adalah  : ";

    for(i=0; i<stages-1; i++){
    	node = p[i]+1;
    	cout << p[i]+1 << " - ";
	}
	if(node == p[i]+1){
		//jika node yang ditempuh termasuk dalam node tujuan (biasanya jika memerlukan stage yang lebih sedikit)
	}
	else{
		printf(" %d",p[i]+1); //mencetak node tujuan
	}
	
	cout << " dengan jarak sebesar " << jarak << " km" << endl;
    
    
}

//MENGHITUNG BOBOT DARI SUATU EDGE GRAF
int hitung_bobot(){
	int i,j;
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if( graf[i][j]!=9999){
				cout << "Bobot dari titik " << i+1 << " ke " << j+1 << " : ";
				cout << graf[i][j];
				cout << endl;
			}
		}
	}
	cout << endl;
}

//FUNGSI UNTUK MENGHITUNG DEGREE
int hitung_degree(){
	int adj[n][n];
	int indegree1[n]={0},outdegree1[n]={0};
	
	for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				adj[i][j] = graf[i][j];
				if(adj[i][j]!= 9999){
					adj[i][j] = 1;
					outdegree1[i]++;
                    indegree1[j]++;
				}		
		}
	}
	
	cout<<"Node\t\t Indegree\t Outdegree\t Total Degree"<<endl;
	cout<<"=========================================================="<<endl;
	
	for(int i=0;i<n;i++){
    	cout << "Node " << i+1 << "  \t\t" << indegree1[i] << "\t\t" << outdegree1[i] << "\t\t" << indegree1[i]+outdegree1[i] << endl;
    }
    cout << endl;
}

//FUNGSI UNTUK MEMBUAT LIST ADJ UNTUK TAMPIL PATH
void Graf_adj::tambahEdge(int i, int j)
{
    adj[i].push_back(j); // menambahkan j ke list milik i 
}

//FUNGSI UNTUK TAMPIL SEMUA PATH
void Graf_adj::tampilsemua_path(int s, int d)
{
    bool* visited = new bool[n];
 
    int* path = new int[n];
    int path_index = 0;
 
    // inisialisasi semua vertex menjadi belum dikunjungi
    for (int i = 0; i < n; i++)
        visited[i] = false;
 
    // fungsi rekursif pembantu untuk menampilkan semua jalan
    tampilsemua_path2(s, d, visited, path, path_index);
}

//FUNGSI LANJUTAN TAMPIL SEMUA PATH
void Graf_adj::tampilsemua_path2(int s, int d, bool visited[],
                              int path[], int& path_index)
{
	int i;
    visited[s] = true;
    path[path_index] = s;
    path_index++;
 
    // jika vertex sekarang sama dengan titik tujuan, maka cetak
    if (s == d) {
        for (i = 0; i < path_index; i++){
			cout << path[i]+1 << "  ";
		}
        cout << endl;
    }
    else // jika vertex sekarang bukan titik tujuan
    {
        list<int>::iterator i;
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
            if (!visited[*i])
                tampilsemua_path2(*i, d, visited, path, path_index);
    }
    path_index--;
    visited[s] = false;
}

//FUNGSI HITUNG PATH YANG MEMANGGIL FUNGSI TAMPIL SEMUA PATH
int hitung_path(){
	Graf_adj g(n);
	int i,j;
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if( graf[i][j]!=9999){
				g.tambahEdge(i, j);
			}
		}
	}
	
	int s = 0, d = 6;
    cout << "Berikut Path (jalur) yang ditempuh dari titik " << s+1 << " ke titik " << d+1 << " : " << endl;
    g.tampilsemua_path(s, d);
    
    cout << endl;
}

//FUNGSI HITUNG WALK
int hitung_walk(){
	cout << "Info : Karena graf adalah jenis directed graf, maka jumlah walk yang ada sama dengan path pada graf" << endl;
	cout << endl;
	
	Graf_adj g(n);
	int i,j;
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if( graf[i][j]!=9999){
				g.tambahEdge(i, j);
			}
		}
	}
	
	int s = 0, d = 6;
    cout << "Berikut Walk yang ditempuh dari titik " << s+1 << " ke titik " << d+1 << " : " << endl;
    g.tampilsemua_path(s, d);
    
    cout << endl;
}

//FUNGSI PILIHAN KARAKTERISTIK GRAF
int karakteristik_graf(){
	int pilih;
	
	Menu:
	cout << "Pilih karakteristik graf yang ingin dilihat: " << endl;
	cout << "1. Derajat (degree)" << endl;
	cout << "2. Size" << endl;
	cout << "3. Order" << endl;
	cout << "4. Bobot" << endl;
	cout << "5. Path" << endl;
	cout << "6. Walk" << endl;
	cout << endl;
	
	cout << "Kamu memilih nomor : ";
	cin >> pilih;
	cout << endl;
	
	if(pilih == 1){
		hitung_degree();
		goto Menu;
	}
	else if (pilih == 2){
		cout << "Info  : size sama dengan jumlah jarak (edge) pada graf" << endl << endl;
		cout << "Size  : " << jumlah_edge << endl << endl;
		goto Menu;
	}
	else if(pilih == 3){
		cout << "Info  : order sama dengan jumlah titik (node) pada graf" << endl << endl;
		cout << "Order : "  << n << endl << endl;
		goto Menu;
	}
	else if(pilih == 4){
		hitung_bobot();
		goto Menu;
	}
	else if(pilih == 5){
		hitung_path();
		goto Menu;
	}
	else if(pilih == 6){
		hitung_walk();
		goto Menu;
	}
	else{
		cout << "Program telah selesai! " << endl;
	}	
}

//FUNGSI UTAMA
int main()
{
	cout << "==============================================================" << endl;
	cout << "     PROGRAM MENGHITUNG JALUR TERPENDEK GRAF - KELOMPOK 1     " << endl;
	cout << "==============================================================" << endl;
	cout << endl;
	
    int jarak;
    int size = 0;
    char lihat;
    
    //n menampung hasil return yaitu jumlah_node di fungsi input_jalur
    n=input_jalur();
    
    
    jarak = hitung_shortestgraph(n);
    tampil_jarak(jarak);

	cout << "Apa ingin melihat karakteristik graf? [Y/N] ";
	cin >> lihat;
	cout << endl;
	
	if(lihat == 'Y' || lihat == 'y'){
		karakteristik_graf();
	} 
	
    getch();
}
