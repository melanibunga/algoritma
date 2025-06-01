#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Pelaku {
    string nama;
    string posisi;
    int nominal;
};

struct Node {
    Pelaku data;
    Node* left;
    Node* right;
};

Node* root = nullptr;

struct Log {
    string aksi; 
    Pelaku data;
};

stack<Log> undoStack;

Node* newNode(Pelaku data) {
    Node* node = new Node{data, nullptr, nullptr};
    return node;
}

Node* insert(Node* root, Pelaku data) {
    if (!root) return newNode(data);
    if (data.nama < root->data.nama){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << "Nama       : " << root->data.nama << endl;
        cout << "Posisi     : " << root->data.posisi << endl;
        cout << "Nominal    : " << root->data.nominal << endl;
        inorder(root->right);
    }
}

Node* nodepalingkiri(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

Node* deleteNode(Node* root, string nama, Pelaku& deletedData, bool& found) {
    if (!root) return nullptr;
    if (nama < root->data.nama){
        root->left = deleteNode(root->left, nama, deletedData, found);
    }
    else if (nama > root->data.nama){
        root->right = deleteNode(root->right, nama, deletedData, found);
    }
    else {
        found = true;
        deletedData = root->data;
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } 
        else {
            Node* temp = nodepalingkiri(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.nama, deletedData, found);
        }
    }
    return root;
}

void undo() {
    if (undoStack.empty()) {
        cout << "Tidak ada aksi untuk di-undo.\n";
        return;
    }
    Log log = undoStack.top();
    undoStack.pop();
    if (log.aksi == "ADD") {
        bool dummy;
        Pelaku dummyData;
        root = deleteNode(root, log.data.nama, dummyData, dummy);
        cout << "Undo penambahan berhasil.\n";
    } else if (log.aksi == "DELETE") {
        root = insert(root, log.data);
        cout << "Undo penghapusan berhasil.\n";
    }
}

void tambahPelaku() {
    Pelaku p;
    cout << "Nama       : "; cin >> ws; getline(cin, p.nama);
    cout << "Posisi     : "; getline(cin, p.posisi);
    cout << "Nominal    : "; cin >> p.nominal;

    root = insert(root, p);
    undoStack.push({"ADD", p});
    cout << "Pelaku berhasil ditambahkan.\n";
}

void hapusPelaku() {
    string nama;
    cout << "Nama pelaku yang akan dihapus: ";
    cin >> ws; getline(cin, nama);

    Pelaku deletedData;
    bool found = false;
    root = deleteNode(root, nama, deletedData, found);

    if (found) {
        undoStack.push({"DELETE", deletedData});
        cout << "Pelaku berhasil dihapus.\n";
    } else {
        cout << "Pelaku tidak ditemukan.\n";
    }
}

int main() {
    int pilih;
    do {
        system("cls");
        cout << "===== SISTEM PENCATATAN PELAKU =====" << endl;
        cout << "1. Tambah Data Pelaku" << endl;
        cout << "2. Tampilkan Semua Pelaku (A-Z)" << endl;
        cout << "3. Hapus Data Pelaku" << endl;
        cout << "4. Undo Aksi Terakhir" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: "; cin >> pilih;

        switch (pilih) {
            case 1: tambahPelaku(); break;
            case 2: inorder(root); system("pause"); break;
            case 3: hapusPelaku(); system("pause"); break;
            case 4: undo(); system("pause"); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
    return 0;
}
