//tugas 2 praktikum algoritma
#include <iostream>
#include <string>
using namespace std;

//untuk menyimpan data yang dimiliki buku
struct buku {
    string judul;
    int harga;
    buku* kanan;
    buku* kiri;
};

//linked list kosong
struct buku *buatbuku(string judul, int harga){
    buku *newbuku = new buku;
    newbuku -> judul = judul;
    newbuku -> harga = harga;
    newbuku -> kanan = NULL;
    newbuku -> kiri  = NULL;
    return newbuku;
}

//fungsi untuk menambah buku ke dalam list
void tambahbuku(buku *&head, string judul, int harga){
    buku *newbuku = buatbuku(judul, harga);
    if(head==NULL){
        head = newbuku;
        return;
    }
    buku *temp = head;
    while(temp->kanan != NULL){
        temp = temp->kanan;
    }
    temp    -> kanan = newbuku;
    newbuku -> kiri  = temp;
}

//utuk menambah data buku lebih dari 1
void tambahbanyakbuku(buku *&head) {
    string judul;
    int harga, n;
    cout << "Masukan jumlah buku yang ingin anda tambahkan dalam list ini : "; cin >> n;
    cout << endl;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "Judul buku ke-" << (i + 1) << " : "; getline(cin, judul);
        cout << "Harga buku ke-" << (i + 1) << " : "; cin >> harga;
        cout << endl;
        cin.ignore();
        tambahbuku(head, judul, harga);
    }
}

//fungsi menampilkan list data buku
void tampilkanbuku(buku* head){
    if(head==NULL){
        cout << "list is empty." << endl;
        return;
    }
    buku* temp = head;
    while(temp != NULL){
        cout << temp->judul << " " << "- Rp " << temp->harga << endl;
        temp = temp->kanan;
    }
    cout << endl;
}

//fungsi untuk mencari buku dengan input judul
void caribuku(buku* head, string judul) {
    buku* temp = head;
    while(temp){
        if (temp->judul == judul) {
            cout << "buku ditemukan!" << endl;
            cout << temp->judul << " - Rp " << temp->harga << endl;
            return;
        }
        temp = temp->kanan;
    }
    cout << "Buku dengan judul \"" << judul << "\" tidak ditemukan." << endl;
}

//fungsi sisip di bagian depan
void sisipdepan(buku *&head, string judul, int harga){
    buku *newbuku = buatbuku(judul, harga);
    newbuku->kanan = head;
    if(head != NULL){
        (head)->kiri = newbuku;
    }
    head = newbuku;
}

//fungsi sisip di bagian belakang
void sisipbelakang(buku *&head, string judul, int harga) {
    tambahbuku(head, judul, harga);
}

//fungsi sisip di tengah
void sisiptengah(buku* bukukiri, string judul, int harga){
    if(bukukiri == NULL){
        cout << "tidak ada." << endl;
        return;
    }
    buku* newbuku = buatbuku(judul, harga);
    newbuku -> kanan = bukukiri -> kanan;
    newbuku -> kiri  = bukukiri;
    if(bukukiri->kanan != NULL){
        bukukiri->kanan->kiri = newbuku;
    }
    bukukiri->kanan = newbuku;
}

//hapus dengan input judul
void hapus(buku *&head, string judul){
    if(head==NULL){
        cout << "list is empty." << endl;
        return;
    }
    buku* temp = head;
    while(temp!=NULL && temp->judul!=judul){
        temp = temp->kanan;
    }
    if(temp==NULL){
        cout << "Judul tidak ditemukan." << endl;
        return;
    }
    else{
        cout << "Buku dengan judul " << judul << " berhasil dihapus" << endl;
    }
    if(temp->kiri != NULL){
        temp->kiri->kanan = temp->kanan;
    } 
    else{
        head = temp->kanan;
    }
    if(temp->kanan != NULL){
        temp->kanan->kiri = temp->kiri;
    }
    delete temp;
}

//fungsi untuk menu sisip
void menusisip(buku *&head){
    int x;
    string judul, afterjudul;
    int harga;

    cout << "1. Sisip Depan" << endl;
    cout << "2. Sisip Tengah" << endl;
    cout << "3. Sisip Belakang" << endl;
    cout << "pilih sisip : "; cin >> x;
    cout << endl;
    cin.ignore();

    cout << "Judul Buku : "; getline(cin, judul);
    cout << "Harga Buku : "; cin >> harga;
    cin.ignore();
    
    switch(x){
        case 1 :
        {
            sisipdepan(head, judul, harga);
            break;
        }
        case 2 :
        {
            buku *temp = head;
            while(temp!=NULL && temp->judul!=afterjudul){
                temp = temp->kanan;
            }
            sisiptengah(head, judul, harga); 
            break;
        }
        case 3 :
        {
            sisipbelakang(head, judul, harga);
            break;
        }
        default :
        {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}

//fungsi untuk menu utama
void menu(buku *&head) {
    int y, harga;
    string judul;

    do{
        system("cls");
        cout << "========= MENU =========" << endl;
        cout << "1. Tambahkan Buku" << endl;
        cout << "2. Tampilkan Data Buku" << endl;
        cout << "3. Cari Data Buku" << endl;
        cout << "4. Sisipkan Buku" << endl;
        cout << "5. Hapus Buku" << endl;
        cout << "0. Exit" << endl;
        cout << "pilih menu : "; cin >> y;
        cout << endl;
        cin.ignore();

        switch(y){
            case 0 :
            {
                exit(0);
            }
            case 1 :
            {
                tambahbanyakbuku(head);
                system("pause");
                break;
            }
            case 2 :
            {
                tampilkanbuku(head);
                system("pause");
                break;
            }
            case 3 : 
            {
                cout << "Input data buku yang ingin anda cari : "; getline(cin, judul);
                caribuku(head, judul);
                system("pause");
                break;
            }
            case 4 :
            {
                menusisip(head);
                system("pause");
                break;
            }
            case 5 :
            {
                cout << "Input judul buku yang ingin di hapus : "; getline(cin, judul);
                hapus(head, judul);
                system("pause");
                break;
            }
            default :
            {
                cout << "Pilihan tidak valid." << endl;
                system("pause");
            }
        }  
    } 
    while(true);
}

int main(){
    buku *head = NULL;
    menu(head);
    return 0;
}
