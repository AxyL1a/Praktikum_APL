#include "GorStruk.h"

int main() {
    User daftar_pengguna[MAX_DATA];
    Reservasi daftar_reservasi[MAX_DATA];
    Rating daftar_rating[MAX_DATA];
    Lapangan daftar_lapangan[MAX_DATA];

    int jumlah_pengguna = 0, jumlah_reservasi = 0, jumlah_rating = 0, jumlah_lapangan = 0;
    
    daftar_lapangan[0] = {"Vinyl Premium", 60000, "Rubber Vinyl", "Standar BWF", 1, 1};
    daftar_lapangan[1] = {"Karpet Standar", 40000, "Sintetis", "Latihan Pro", 2, 2};
    daftar_lapangan[2] = {"Semen Beton", 25000, "Semen Halus", "Ekonomis", 2, 2};
    jumlah_lapangan = 3;

    daftar_pengguna[0] = {"firman", "000"}; jumlah_pengguna = 1;

    string nama_pengguna_masuk;
    int pilihan_utama;

    while (true) {
        tampilkan_header(daftar_rating, jumlah_rating);
        cout << "1. Masuk\n2. Registrasi\n3. Keluar\nPilih menu: ";
        pilihan_utama = masukan_angka();

        if (pilihan_utama == 1) {
            if (proses_masuk(daftar_pengguna, jumlah_pengguna, nama_pengguna_masuk)) {
                if (nama_pengguna_masuk == "adminGor") 
                    menu_admin(daftar_lapangan, jumlah_lapangan, daftar_rating, jumlah_rating, daftar_reservasi, jumlah_reservasi);
                else 
                    menu_pengguna(nama_pengguna_masuk, daftar_lapangan, jumlah_lapangan, daftar_reservasi, daftar_rating, jumlah_reservasi, jumlah_rating);
            } else cout << "\n[!] Batas percobaan habis.\n";
        } 
        else if (pilihan_utama == 2) proses_registrasi(daftar_pengguna, jumlah_pengguna);
        else if (pilihan_utama == 3) { cout << "\nTerima kasih!\n"; break; }
        else cout << "[!] Pilihan tidak valid.\n";
    }
    return 0;
}