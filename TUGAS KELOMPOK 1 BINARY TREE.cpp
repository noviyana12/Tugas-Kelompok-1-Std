#include <iostream>
#include <conio.h>

using namespace std;

struct Node{
	string nama_barang, merk_barang, tipe_barang;
	int kode_barang, nomor_index_barang, harga_barang, size_barang;
	Node *kiri;
	Node *kanan;
};
Node *pohon = NULL;
Node *baru;

int ditemukan;


void tambah(Node **root, string nama_barang, string merk_barang, string tipe_barang, 
			int kode_barang, int nomor_index, int harga_barang, int size_barang){
		
	if((*root) == NULL){
		baru = new Node;
		baru->kode_barang = kode_barang;
		baru->nama_barang = nama_barang;
		baru->merk_barang = merk_barang;
		baru->tipe_barang = tipe_barang;
		baru->nomor_index_barang = nomor_index;
		baru->harga_barang = harga_barang;
		baru->size_barang = size_barang;
		
		baru->kiri = NULL;
		baru->kanan = NULL;
		
		(*root) = baru;
		(*root)->kiri = NULL;
		(*root)->kanan = NULL;
		
		cout<<"Data telah dimasukkan"<<endl<<endl;
	}
	else if((*root)->kiri == NULL){
		tambah(&(*root)->kiri, nama_barang, merk_barang, tipe_barang, kode_barang, nomor_index, harga_barang, size_barang);
	}
	else if((*root)->kanan == NULL){
		tambah(&(*root)->kanan, nama_barang, merk_barang, tipe_barang, kode_barang, nomor_index, harga_barang, size_barang);
	}
	else{
		tambah(&(*root)->kiri, nama_barang, merk_barang, tipe_barang, kode_barang, nomor_index, harga_barang, size_barang);
	}
}

void preOrder(Node *root){
	if(root != NULL){
		cout<<root->nomor_index_barang<<"\t\t"<<root->kode_barang<<"\t\t"<<root->nama_barang<<"\t\t"<<root->merk_barang
		<<"\t\t"<<root->tipe_barang<<"\t\t"<<root->harga_barang<<"\t\t"<<root->size_barang<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		preOrder(root->kiri);
		preOrder(root->kanan);
	}
}

void inOrder(Node *root){
	if(root != NULL){
		inOrder(root->kiri);
		cout<<root->nomor_index_barang<<"\t\t"<<root->kode_barang<<"\t\t"<<root->nama_barang<<"\t\t"<<root->merk_barang
		<<"\t\t"<<root->tipe_barang<<"\t\t"<<root->harga_barang<<"\t\t"<<root->size_barang<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		inOrder(root->kanan);
	}
}

void postOrder(Node *root){
	if(root != NULL){
		postOrder(root->kiri);
		postOrder(root->kanan);
		cout<<root->nomor_index_barang<<"\t\t"<<root->kode_barang<<"\t\t"<<root->nama_barang<<"\t\t"<<root->merk_barang
		<<"\t\t"<<root->tipe_barang<<"\t\t"<<root->harga_barang<<"\t\t"<<root->size_barang<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
	}
}

void tampil(){
	
	if(pohon!=NULL){
		
		cout<<"PreOrder : "<<endl;
		cout<<"Index\t\t Kode\t\t Nama\t\t Merk\t\t Tipe\t\t Harga\t\t Size"<<endl;
		cout<<"============================================================================================================="<<endl;
		preOrder(pohon);
		cout<<endl<<endl;
		
		cout<<"InOrder : "<<endl;
		cout<<"Index\t\t Kode\t\t Nama\t\t Merk\t\t Tipe\t\t Harga\t\t Size"<<endl;
		cout<<"============================================================================================================="<<endl;
		inOrder(pohon);
		cout<<endl<<endl;
		
		cout<<"PostOrder : "<<endl;
		cout<<"Index\t\t Kode\t\t Nama\t\t Merk\t\t Tipe\t\t Harga\t\t Size"<<endl;
		cout<<"============================================================================================================="<<endl;
		postOrder(pohon);
		cout<<endl<<endl;
		
	} 
	else{
		cout<<"Data masih kosong"<<endl<<endl;
	}

}

int search(Node **root, int cari){
	
	if((*root) != NULL){
		if(cari == (*root)->kode_barang){
			ditemukan = 1;
			cout<<"Data ditemukan"<<endl;
			cout<<"No Index        : "<<(*root)->nomor_index_barang<<endl;
			cout<<"Kode Barang     : "<<(*root)->kode_barang<<endl;
			cout<<"Nama Barang     : "<<(*root)->nama_barang<<endl;
			cout<<"Merk            : "<<(*root)->merk_barang<<endl;
			cout<<"Tipe            : "<<(*root)->tipe_barang<<endl;
			cout<<"Harga           : "<<(*root)->harga_barang<<endl;
			cout<<"Size            : "<<(*root)->size_barang<<endl;
			cout<<endl;
			return 1;
		}
		search(&(*root)->kiri, cari);
		search(&(*root)->kanan, cari);	
		
	}
	
}

int edit(Node **root, int cari, int harga_baru){
	
	if((*root) != NULL){
		if(cari == (*root)->kode_barang){
			(*root)->harga_barang = harga_baru;
			cout<<"Harga dari produk "<<(*root)->nama_barang<<" telah diedit"<<endl<<endl;
			return 1;
		}else{
			edit(&(*root)->kiri, cari, harga_baru);
			edit(&(*root)->kanan, cari, harga_baru);	
		}
		
	}

}

int hapus(Node **root, int del){
	
	if((*root) != NULL){
		if(del == (*root)->kode_barang){
			(*root)=NULL;
			cout<<"data telah dihapus"<<endl<<endl;
			return 1;
		}
		else{
			hapus(&(*root)->kiri, del);
			hapus(&(*root)->kanan, del);	
		}
	}

}

void clear(){
	pohon = NULL;
	cout<<"Semua data telah dihapus"<<endl<<endl;
}


int main() {
	
	int pilihan, kode_cari, kode_hapus;
	char mau_edit;
	string nama, merk, tipe;
	int kode, harga, no_id = 1, size, harga_baru;
	
	Menu:
	cout<<"Menu :"<<endl;
	cout<<"1. Masukkan data"<<endl;
	cout<<"2. Print secara pre order, in order, post order"<<endl;
	cout<<"3. Cari & Edit data"<<endl;
	cout<<"4. Hapus data"<<endl;
	cout<<"5. Insert data baru"<<endl;
	cout<<"6. Clear data"<<endl;
	cout<<"7. Keluar"<<endl;
	cout<<"Masukkan pilihan anda : ";
	cin>>pilihan;
	cout<<endl<<endl;
	
	//Masukkan Data
	if(pilihan == 1){
		cout<<"No Index             : "<<no_id<<endl;
		cout<<"Masukkan kode barang : ";
		cin>>kode;
		cout<<"Masukkan nama barang : ";
		getline(cin>>std::ws, nama);
		cout<<"Masukkan merk barang : ";
		getline(cin>>std::ws, merk);
		cout<<"Masukkan tipe barang : ";
		getline(cin>>std::ws, tipe);
		cout<<"Masukkan harga barang : ";
		cin>>harga;
		cout<<"Masukkan size barang : ";
		cin>>size;
		
		tambah(&pohon, nama, merk, tipe, kode, no_id, harga, size);
		no_id++;
		goto Menu;
	}
	//Tampil Data
	else if(pilihan == 2){
		tampil();
		goto Menu;
	}
	//Cari Data & Edit
	else if(pilihan == 3){
		cout<<"Masukkan kode barang yang akan dicari : ";
		cin>>kode_cari;
		search(&pohon, kode_cari);
		if(ditemukan == 1){
			ditemukan = 0;
			cout<<"Apakah anda ingin mengedit harga [y/n]: ";
			cin>>mau_edit;
			if(mau_edit == 'y' || mau_edit == 'Y'){
				cout<<"Masukkan harga yang baru : ";
				cin>>harga_baru;
				edit(&pohon,kode_cari, harga_baru);
				tampil();
				goto Menu;
			}else{
				goto Menu;
			}
		}else{
			cout<<"Data tidak ada"<<endl;
			goto Menu;
		}
		
	}
	//Hapus Data
	else if(pilihan == 4){
		cout<<"Masukkan kode barang yang akan dihapus : ";
		cin>>kode_hapus;
		hapus(&pohon, kode_hapus);
		tampil();
		goto Menu;
	}
	//Insert Data
	else if(pilihan == 5){
		cout<<"Masukkan kode barang : ";
		cin>>kode;
		cout<<"Masukkan nama barang : ";
		getline(cin>>std::ws, nama);
		cout<<"Masukkan merk barang : ";
		getline(cin>>std::ws, merk);
		cout<<"Masukkan tipe barang : ";
		getline(cin>>std::ws, tipe);
		cout<<"Masukkan harga barang : ";
		cin>>harga;
		cout<<"Masukkan size barang : ";
		cin>>size;
		
		tambah(&pohon, nama, merk, tipe, kode, no_id, harga, size);
		no_id++;
		goto Menu;
	}
	//Clear Data
	else if(pilihan == 6){
		clear();
		goto Menu;
	}
	//Keluar
	else if(pilihan == 7){
		
	}
	else{
		cout<<"Pilihan tidak tersedia"<<endl<<endl;
		goto Menu;
	}
	
	return 0;
}
