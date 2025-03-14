#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Tugas {
    char nama[50];
    char kategori[20];
    char deadline[11];
    char status[15] = "Belum Selesai";
}; 
Tugas t;

vector<Tugas> daftarTugas;

//membaca data dari file
void readfile(){
    FILE *workfile = fopen("WorkTracker.dat","rb");
    if(fopen){
        while (fread(&t, sizeof(Tugas), 1, workfile)){
            daftarTugas.push_back(t);
        }
        fclose(workfile);
    }
}

//menyimpan data ke file
void savefile() {
    FILE *workfile = fopen("WorkTracker.dat", "wb");
    if (workfile) {
        for (const auto& t : daftarTugas) {
            fwrite(&t, sizeof(Tugas), 1, workfile);
        }
        fclose(workfile);
    }
}

void tambahtugas(){
    cin.ignore();
    cout << "Input nama tugas             : "; cin.getline(t.nama, 50);

    for (const auto& task : daftarTugas){ //tiap elemen diakses sbg task, tanpa salinan baru
        if (strcmp(task.nama, t.nama)==0){ //bandingkan tugas yg ada & yg baru di input
            cout << "the task has been registered." << endl; //jika sama maka cout ini
            return;
        }
    } 

    cout << "Input kategori               : "; cin.getline(t.kategori, 20);
    cout << "Input deadline (YYYY/MM/DD)  : "; cin.getline(t.deadline, 11);
    daftarTugas.push_back(t); //memasukan inputan baru ke daftarTugas
    savefile(); //save perubahan baru ke file
    cout << "task successfully added." << endl;
}

//fungsi nampilin tugas yang diinput
void tampilkantugas() {
    if (daftarTugas.empty()) {
        cout << "no assignment" << endl;
        return;
    }
    //mengurutkan dl tugas secara descending 
    sort(daftarTugas.begin(), daftarTugas.end(), [](const Tugas &a, const Tugas &b) {
        return strcmp(a.deadline, b.deadline) > 0;
    });
    cout << endl;

    cout << "========DAFTAR TUGAS========\n" << endl;
    for (const auto& t : daftarTugas) {
        cout << "Nama       : " << t.nama << endl;
        cout << "Kategori   : " << t.kategori << endl;
        cout << "Deadline   : " << t.deadline << endl;
        cout << "Status     : " << t.status << endl;
        cout << endl;
    }
}

//search tugas
void caritugas() {
    char kategori[20];
    cin.ignore();
    cout << "Input kategori : "; cin.getline(kategori, 20);
    bool ditemukan=false;

    for (const auto& t : daftarTugas) {
        if (strcmp(t.kategori, kategori)==0) {
            cout << "Nama       : " << t.nama << endl;
            cout << "Deadline   : " << t.deadline << endl; 
            cout << "Status     : " << t.status << endl;
            cout << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) 
        cout << "there are no tasks in this category." << endl;
}

//update status tugas
void updatetugas() {
    char nama[50];
    cin.ignore();
    cout << "Input nama tugas : "; cin.getline(nama, 50);

    for (auto& t : daftarTugas) {
        if (strcmp(t.nama, nama)==0) {
            strcpy(t.status, "finished");
            savefile();
            cout << "status successfully updated." << endl;
            return;
        }
    }
    cout << "task not found." << endl;
}

//hapus tugas yang telah di update
void hapustugas() {
    char nama[50];
    cin.ignore();
    cout << "Input nama tugas yang ingin dihapus : "; cin.getline(nama, 50);

    auto it = remove_if(daftarTugas.begin(), daftarTugas.end(), [&](const Tugas& t) {
        return strcmp(t.nama, nama)==0 && strcmp(t.status, "finished")==0;
    });

    if (it != daftarTugas.end()) {
        daftarTugas.erase(it, daftarTugas.end()); //it => posisi hapus
        savefile();
        cout << "task successfully deleted." << endl;
    } else {
        cout << "task not found or task not completed." << endl;
    }
}

int main() {
    readfile();
    int x;
    do {
        cout << "======= WorkTracker =======" << endl;
        cout << "|1.| Tambah Tugas         |" << endl;
        cout << "|2.| Tampilkan Tugas      |" << endl;
        cout << "|3.| Cari Tugas           |" << endl;
        cout << "|4.| Perbarui Status      |" << endl;
        cout << "|5.| Hapus Tugas          |" << endl;
        cout << "|6.| Keluar               |" << endl;
        cout << "===========================" << endl;
        cout << "Pilih : "; cin >> x;
        
        switch(x){
            case 1: 
                tambahtugas();
                system("pause");
                break;
            case 2: 
                tampilkantugas(); 
                system("pause");
                break;
            case 3: 
                caritugas();
                system("pause"); 
                break;
            case 4: 
                updatetugas(); 
                system("pause");
                break;
            case 5: 
                hapustugas();
                system("pause"); 
                break;
            case 6: 
                cout << "Terima kasih telah menggunakan WorkTracker!" << endl; 
                system("pause");
                break;
            default: 
            cout << "invalid choice." << endl;
        }
    } while (x!=6);
    return 0;
}