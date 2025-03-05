#include <iostream>
#include <string>

using namespace std;

// struct untuk menyimpan informasi mengenai data buku yang berisi judul dan tahun terbit buku.
struct buku {  
    string judul;
    int th_terbit;
};

//fungsi untuk menampilkan data buku yang telah disimpan dalam struct buku.
void tampilkanbuku (buku bk[], int n) {
    for(int i=0; i<n; i++) {
        cout << bk[i].judul << " " << "(" << bk[i].th_terbit << ")" << endl;
    }
}

//fungsi untuk mencari data buku secara urut dengan metode bubble sort
void bubblesort(buku bk[], int n) {
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (bk[j].th_terbit > bk[j+1].th_terbit) {
                int temp=bk[j+1].th_terbit;
                bk[j+1].th_terbit=bk[j].th_terbit;
                bk[j].th_terbit=temp;
            }
        }
    }
    //tampilan data buku setelah sorting
    for (int i=0; i<n; i++) {
        cout << i << ". " << bk[i].judul << " " << "(" << bk[i].th_terbit << ")\n";
    }
}

//fungsi untuk mencari data buku secara urut dengan metode quicksort
void quicksort(buku bk[], int awal, int akhir) {
    int low=awal, high=akhir;
    int pivot = bk[(awal + akhir)/2].th_terbit;
    do {
        while (bk[low].th_terbit<pivot)
            low++;
        while (bk[high].th_terbit>pivot)
            high--;
        if (low<=high) {
            swap(bk[low], bk[high]);
            low++;
            high--;
        }
    } while (low<=high);
    if (awal<high)
        quicksort(bk, awal, high);
    if (low<akhir)
        quicksort(bk, low, akhir);
}

//fungsi untuk mencari data buku secara linear
int sequentialSearch(buku bk[], int n, int tahun) {
    for (int i = 0; i < n; i++) {
        if (bk[i].th_terbit==tahun) {
            return i;
        }
    }
    return -1;
}

//fungsi untuk mencari data buku secara linear
int binarySearch(buku bk[], int left, int right, int tahun) {
    while (left<=right) {
        int mid=left+(right-left)/2;
        if (bk[mid].th_terbit==tahun) return mid;
        if (bk[mid].th_terbit<tahun) left=mid+1;
        else right=mid-1;
    }
    return -1;
}

int main() {
    int x, n=0, j, mid, i, awal, akhir;
    buku bk[20];
    string judul;
    bool found;

    do{
        cout << "===================================" << endl;
        cout << "|           DAFTAR MENU           |" << endl;
        cout << "===================================" << endl;
        cout << "|1.| Input data buku              |\n";
        cout << "|2.| Tampilkan daftar buku        |\n";
        cout << "|3.| Bubble sort                  |\n";
        cout << "|4.| Quick sort                   |\n";
        cout << "|5.| Sequential search            |\n";
        cout << "|6.| Binary search                |\n";
        cout << "|0.| Exit                         |\n";
        cout << "===================================" << endl;
        cout << "Plihan Anda : "; cin >> x;
        cin.ignore();

        switch(x) {
            case 0:
                exit(0);
                break;
            case 1: {
                if(n<20) {
                    cout << "\n" << endl;
                    cout << "Judul Buku   : "; getline(cin, bk[n].judul);
                    cout << "Tahun Terbit : "; cin >> bk[n].th_terbit;
                    n++;
                } else {
                    cout << "Ruang tidak cukup!, silahkan coba lagi." << endl;
                }
                break; 
            }
            case 2: {
                cout << "=============================" << endl;
                cout << "| DAFTAR BUKU YANG DI-INPUT |" << endl;
                cout << "=============================" << endl;
                tampilkanbuku(bk,n);
                system("pause");
                break;
            }
            case 3: {
                cout << "=============================" << endl;
                cout << "|DAFTAR BUKU SEBELUM SORTING|" << endl;
                cout << "=============================" << endl;
                tampilkanbuku(bk,n);
                cout << "=============================" << endl;
                cout << "|DAFTAR BUKU SETELAH SORTING|" << endl;
                cout << "=============================" << endl;
                bubblesort(bk, n);
                system("pause");
                break;
            }
            case 4: {
                cout << "=============================" << endl;
                cout << "|DAFTAR BUKU SEBELUM SORTING|" << endl;
                cout << "=============================" << endl;
                tampilkanbuku(bk,n);
                quicksort(bk,0,n-1);
                cout << "=============================" << endl;
                cout << "|DAFTAR BUKU SETELAH SORTING|" << endl;
                cout << "=============================" << endl;
                tampilkanbuku(bk,n);
                system("pause");
                break;
            }
            case 5: {
                cout << "Input tahun terbit : "; cin >> bk[n].th_terbit;
                    {
                        n=0; found=false;
                        while((n<20)&&(!found)) 
                        {
                        if(bk[n].th_terbit==bk[n].th_terbit)
                            found = true;
                        else
                            n = n + 1;
                        }
                        if(found)
                            cout << "BUKU DITEMUKAN/TERSEDIA" << endl;
                        else
                            cout << "BUKU TIDAK DITEMUKAN/TIDAK TERSEDIA" << endl;
                            cout << " " << endl;
                    }
                    system("pause");
                break;
            }
            case 6 : {
                cout << "Input tahun terbit : "; cin >> bk[n].th_terbit;
                n=0;  j=19;  found=false;  //i: index awal, j: index akhir
                while ((!found) & (n<=j))
                { mid=(n+j)/2; // index tengah
                    if (mid==bk[n].th_terbit)
                        found=true;       
                    else
                        if (bk[n].th_terbit<mid)
                        j=mid-1;    
                        else
                        n=mid+1;    
                }
                if(found)
                    cout << "BUKU DITEMUKAN/TERSEDIA" << endl;
                else
                    cout << "BUKU TIDAK DITEMUKAN/TIDAK TERSEDIA" << endl;
                    system("pause");
                break;
            }
            default: {
                cout << "Tidak Valid!, silahkan coba lagi." << endl;
                system("pause");
                break;
            }
        }
    }
    while (x>!6);
    return 0;
}