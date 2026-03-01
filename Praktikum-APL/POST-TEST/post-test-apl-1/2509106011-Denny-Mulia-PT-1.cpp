#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    string nama_input, password_input;
    string nama_tersimpan = "Denny Mulia";
    string password_tersimpan = "011";
    int batas_percobaan = 0;
    bool status_login = false;

    while (batas_percobaan < 3) {
        cout << ">>> SILAHKAN LOGIN <<<" << endl;
        cout << "Nama     : ";
        getline(cin, nama_input);
        cout << "Password : ";
        cin >> password_input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (nama_input == nama_tersimpan && password_input == password_tersimpan) {
            status_login = true;
            cout << "\nLogin Berhasil! Selamat datang, " << nama_tersimpan << endl;
            break;
        } else {
            batas_percobaan++;
            cout << "Login Gagal! Sisa kesempatan: " << (3 - batas_percobaan) << endl << endl;
        }
    }

    if (!status_login) {
        cout << "Login Gagal! Keluar dari program" << endl;
        return 0;
    }

    int pilihan_user;
    double nilai_waktu;

    do {
        cout << ">>> MENU KONVERSI WAKTU <<<" << endl;
        cout << "1. Jam   -> Menit dan Detik" << endl;
        cout << "2. Menit -> Jam dan Detik" << endl;
        cout << "3. Detik -> Jam dan Menit" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih Menu (1-4): ";
        cin >> pilihan_user;


        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak  tersedia" << endl;
            continue; 
        }

        if (pilihan_user >= 1 && pilihan_user <= 3) {
            cout << "Masukkan nilai waktu: ";
            cin >> nilai_waktu;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan angka yang valid" << endl;
                continue;
            }

            if (pilihan_user == 1) {
                cout << "Hasil: " << nilai_waktu << " Jam = " << (nilai_waktu * 60) << " Menit dan " << (nilai_waktu * 3600) << " Detik" << endl;
            } else if (pilihan_user == 2) {
                cout << "Hasil: " << nilai_waktu << " Menit = " << (nilai_waktu / 60) << " Jam dan " << (nilai_waktu * 60) << " Detik" << endl;
            } else if (pilihan_user == 3) {
                cout << "Hasil: " << nilai_waktu << " Detik = " << (nilai_waktu / 3600) << " Jam dan " << (nilai_waktu / 60) << " Menit" << endl;
            }
        } else if (pilihan_user == 4) {
            cout << "Keluar dari program" << endl;
        } else {
            cout << "Pilihan tidak tersedia" << endl;
        }
    } while (pilihan_user != 4);
    return 0;
}