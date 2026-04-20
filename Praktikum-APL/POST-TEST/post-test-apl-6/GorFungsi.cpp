#include "GorStruk.h"

void tampilkan_pesan(string pesan) { 
    cout << "\n>>> " << pesan << " <<<" << endl; 
}

void tampilkan_pesan(string pesan, int nilai) { 
    cout << "\n[!] " << pesan << ": " << nilai << endl; 
}

void bersihkan_masukan() { 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

int masukan_angka() {
    int angka;
    if (!(cin >> angka)) { 
        cin.clear(); 
        bersihkan_masukan(); 
        return -1; 
    }
    return angka;
}

float hitung_total_bintang_rekursif(Rating* daftar_rating, int jumlah) {
    if (jumlah <= 0) return 0;
    return (*(daftar_rating + jumlah - 1)).bintang + hitung_total_bintang_rekursif(daftar_rating, jumlah - 1);
}

void tampilkan_header(Rating* daftar_rating, int jumlah_rating) {
    cout << "\n======================================" << endl;
    cout << "       GOR BADMINTON SANJAYA          " << endl;
    cout << "======================================" << endl;

    if (jumlah_rating > 0) {
        float total_bintang = hitung_total_bintang_rekursif(daftar_rating, jumlah_rating);
        cout << "Rating GOR: " << fixed << setprecision(1) << (total_bintang/jumlah_rating) << "/5.0 stars" << endl;
        cout << "Ulasan terbaru oleh [" << (*(daftar_rating + jumlah_rating - 1)).namaUser << "]:" << endl;
        cout << "\"" << (*(daftar_rating + jumlah_rating - 1)).ulasan << "\" (" << (*(daftar_rating + jumlah_rating - 1)).bintang << "/5)" << endl;
        cout << "--------------------------------------" << endl;
    } else {
        cout << "Rating: Belum ada ulasan dari pelanggan\n--------------------------------------" << endl;
    }
}

void tampilkan_detail_lapangan(Lapangan* daftar_lapangan, int jumlah_lapangan) {
    cout << "\n" << setfill('=') << setw(85) << "" << endl;
    cout << setfill(' ') << left << setw(18) << "NAMA" << setw(13) << "HARGA/JAM" << setw(18) << "BAHAN" << setw(12) << "TERSEDIA" << "DESKRIPSI" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    for(int indeks=0; indeks<jumlah_lapangan; indeks++) {
        cout << left << setw(18) << (*(daftar_lapangan + indeks)).nama << "Rp" << setw(10) << (*(daftar_lapangan + indeks)).harga
             << setw(18) << (*(daftar_lapangan + indeks)).bahan << setw(12) << (*(daftar_lapangan + indeks)).tersedia << (*(daftar_lapangan + indeks)).deskripsi << endl;
    }
}

void tampilkan_daftar_lapangan_admin(Lapangan* daftar_lapangan, int jumlah_lapangan) {
    cout << "\n" << left << setw(5) << "NO" << setw(20) << "NAMA" << setw(12) << "HARGA" << setw(15) << "BAHAN" << setw(10) << "KAPASITAS" << "DESKRIPSI" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
    for(int indeks=0; indeks<jumlah_lapangan; indeks++) {
        cout << left << setw(5) << indeks+1 << setw(20) << (*(daftar_lapangan + indeks)).nama << "Rp" << setw(9) << (*(daftar_lapangan + indeks)).harga 
             << setw(15) << (*(daftar_lapangan + indeks)).bahan << setw(10) << (*(daftar_lapangan + indeks)).kapasitasAwal << (*(daftar_lapangan + indeks)).deskripsi << endl;
    }
}

void proses_registrasi(User* daftar_pengguna, int& jumlah_pengguna) {
    if (jumlah_pengguna >= MAX_DATA) { 
        cout << "\n[!] Kapasitas pengguna penuh.\n"; 
        return; 
    }
    cout << "\nNama Pengguna Baru : "; 
    cin >> (*(daftar_pengguna + jumlah_pengguna)).username;
    cout << "Kata Sandi Baru : "; 
    cin >> (*(daftar_pengguna + jumlah_pengguna)).password;
    jumlah_pengguna++; 
    tampilkan_pesan("REGISTRASI BERHASIL! Silakan Masuk.");
}

bool proses_masuk(User* daftar_pengguna, int jumlah_pengguna, string& nama_pengguna_keluar) {
    string nama_pengguna, kata_sandi; 
    int batas_gagal = 0;
    
    while (batas_gagal < 3) {
        cout << "\nNama Pengguna : "; cin >> nama_pengguna; cout << "Kata Sandi : "; cin >> kata_sandi;
        if (nama_pengguna == "adminGor" && kata_sandi == "sanjayaclub990") { nama_pengguna_keluar = "adminGor"; return true; }
        for (int indeks = 0; indeks < jumlah_pengguna; indeks++) {
            if ((*(daftar_pengguna + indeks)).username == nama_pengguna && (*(daftar_pengguna + indeks)).password == kata_sandi) { nama_pengguna_keluar = nama_pengguna; return true; }
        }
        batas_gagal++;
        cout << "\n[!] MASUK GAGAL! Nama Pengguna atau Kata Sandi salah." << endl;
        if (batas_gagal < 3) cout << "[!] Sisa percobaan: " << 3 - batas_gagal << " kali." << endl;
    }
    return false;
}

void tambah_lapangan(Lapangan* daftar_lapangan, int& jumlah_lapangan) {
    if (jumlah_lapangan >= MAX_DATA) { cout << "\n[!] Kapasitas data lapangan penuh.\n"; return; }
    cout << "\n--- TAMBAH LAPANGAN BARU ---" << endl;
    bersihkan_masukan();
    cout << "Nama Lapangan   : "; getline(cin, (*(daftar_lapangan + jumlah_lapangan)).nama);
    cout << "Harga per Jam   : "; (*(daftar_lapangan + jumlah_lapangan)).harga = masukan_angka();
    bersihkan_masukan();
    cout << "Bahan           : "; getline(cin, (*(daftar_lapangan + jumlah_lapangan)).bahan);
    cout << "Deskripsi       : "; getline(cin, (*(daftar_lapangan + jumlah_lapangan)).deskripsi);
    cout << "Kapasitas Awal  : "; (*(daftar_lapangan + jumlah_lapangan)).kapasitasAwal = masukan_angka();
    (*(daftar_lapangan + jumlah_lapangan)).tersedia = (*(daftar_lapangan + jumlah_lapangan)).kapasitasAwal;
    jumlah_lapangan++;
    tampilkan_pesan("Lapangan berhasil ditambahkan.");
}

void hapus_lapangan(Lapangan* daftar_lapangan, int& jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi) {
    if (jumlah_lapangan <= 0) { cout << "\n[!] Tidak ada lapangan untuk dihapus.\n"; return; }
    tampilkan_daftar_lapangan_admin(daftar_lapangan, jumlah_lapangan);
    cout << "\nPilih nomor lapangan untuk dihapus (0 batal): "; int pilihan = masukan_angka();
    if (pilihan < 1 || pilihan > jumlah_lapangan) { cout << "[!] Batal menghapus.\n"; return; }
    int indeks = pilihan - 1;
    string nama_lapangan = (*(daftar_lapangan + indeks)).nama;
    for(int indeks_res = 0; indeks_res < jumlah_reservasi; indeks_res++) {
        if (daftar_reservasi[indeks_res].namaLapangan == nama_lapangan) {
            cout << "[!] Tidak bisa hapus: masih ada reservasi aktif untuk lapangan ini.\n";
            return;
        }
    }
    for(int indeks_geser = indeks; indeks_geser < jumlah_lapangan - 1; indeks_geser++) {
        *(daftar_lapangan + indeks_geser) = *(daftar_lapangan + indeks_geser + 1);
    }
    jumlah_lapangan--;
    tampilkan_pesan("Lapangan berhasil dihapus.");
}

void edit_lapangan(Lapangan* daftar_lapangan, int jumlah_lapangan) {
    if (jumlah_lapangan <= 0) { cout << "\n[!] Tidak ada lapangan untuk diedit.\n"; return; }
    tampilkan_daftar_lapangan_admin(daftar_lapangan, jumlah_lapangan);
    cout << "\nPilih nomor lapangan untuk diedit (0 batal): "; int pilihan = masukan_angka();
    if (pilihan < 1 || pilihan > jumlah_lapangan) { cout << "[!] Batal mengedit.\n"; return; }
    int indeks = pilihan - 1;
    cout << "\n--- EDIT LAPANGAN [" << (*(daftar_lapangan + indeks)).nama << "] ---" << endl;
    bersihkan_masukan();
    string input_baru;
    cout << "Nama Baru       : "; getline(cin, input_baru);
    if (!input_baru.empty()) (*(daftar_lapangan + indeks)).nama = input_baru;
    cout << "Harga Baru      : "; getline(cin, input_baru);
    if (!input_baru.empty()) (*(daftar_lapangan + indeks)).harga = stoi(input_baru);
    cout << "Bahan Baru      : "; getline(cin, input_baru);
    if (!input_baru.empty()) (*(daftar_lapangan + indeks)).bahan = input_baru;
    cout << "Deskripsi Baru  : "; getline(cin, input_baru);
    if (!input_baru.empty()) (*(daftar_lapangan + indeks)).deskripsi = input_baru;
    cout << "Kapasitas Baru  : "; getline(cin, input_baru);
    if (!input_baru.empty()) {
        (*(daftar_lapangan + indeks)).kapasitasAwal = stoi(input_baru);
        (*(daftar_lapangan + indeks)).tersedia = (*(daftar_lapangan + indeks)).kapasitasAwal;
    }
    tampilkan_pesan("Data lapangan berhasil diperbarui.");
}

void bubble_sort_nama_lapangan(Lapangan* daftar_lapangan, int jumlah_lapangan) {
    for (int i = 0; i < jumlah_lapangan - 1; i++) {
        for (int j = 0; j < jumlah_lapangan - i - 1; j++) {
            if ((*(daftar_lapangan + j)).nama > (*(daftar_lapangan + j + 1)).nama) {
                Lapangan temp = *(daftar_lapangan + j);
                *(daftar_lapangan + j) = *(daftar_lapangan + j + 1);
                *(daftar_lapangan + j + 1) = temp;
            }
        }
    }
}

void bubble_sort_nama_lapangan_user(Lapangan* daftar_lapangan, int jumlah_lapangan) {
    bubble_sort_nama_lapangan(daftar_lapangan, jumlah_lapangan);
    cout << "\n========================================" << endl;
    cout << "SORTING: Bubble Sort" << endl;
    cout << "DATA: Nama Lapangan" << endl;
    cout << "URUTAN: Ascending (A-Z)" << endl;
    cout << "========================================" << endl;
    tampilkan_daftar_lapangan_admin(daftar_lapangan, jumlah_lapangan);
}

int partition_tagihan_reservasi(Reservasi* daftar, int low, int high) {
    int pivot = (*(daftar + high)).totalTagihan;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if ((*(daftar + j)).totalTagihan >= pivot) {
            i++;
            Reservasi temp = *(daftar + i);
            *(daftar + i) = *(daftar + j);
            *(daftar + j) = temp;
        }
    }
    Reservasi temp = *(daftar + i + 1);
    *(daftar + i + 1) = *(daftar + high);
    *(daftar + high) = temp;
    return i + 1;
}

void quick_sort_tagihan_reservasi(Reservasi* daftar, int low, int high) {
    if (low < high) {
        int pi = partition_tagihan_reservasi(daftar, low, high);
        quick_sort_tagihan_reservasi(daftar, low, pi - 1);
        quick_sort_tagihan_reservasi(daftar, pi + 1, high);
    }
}

void quick_sort_tagihan_reservasi_user(Reservasi* daftar, int low, int high, string username) {
    quick_sort_tagihan_reservasi(daftar, low, high);
    cout << "\n========================================" << endl;
    cout << "SORTING: Quick Sort" << endl;
    cout << "DATA: Total Tagihan Reservasi" << endl;
    cout << "URUTAN: Descending (Terbesar-Terkecil)" << endl;
    cout << "========================================" << endl;
    cout << "\n--- RIWAYAT TRANSAKSI (TERURUT) ---" << endl;
    bool ada = false;
    for (int indeks = 0; indeks < high + 1; indeks++) {
        if (daftar[indeks].usernamePemilik == username) {
            cout << "- Lapangan: " << daftar[indeks].namaLapangan << " | Total: Rp" << daftar[indeks].totalTagihan << endl;
            ada = true;
        }
    }
    if (!ada) cout << "Belum ada transaksi.\n";
}

void insertion_sort_bintang_rating(Rating* daftar_rating, int jumlah_rating) {
    for (int i = 1; i < jumlah_rating; i++) {
        Rating key = *(daftar_rating + i);
        int j = i - 1;
        while (j >= 0 && (*(daftar_rating + j)).bintang > key.bintang) {
            *(daftar_rating + j + 1) = *(daftar_rating + j);
            j--;
        }
        *(daftar_rating + j + 1) = key;
    }
}

void insertion_sort_bintang_rating_user(Rating* daftar_rating, int jumlah_rating) {
    insertion_sort_bintang_rating(daftar_rating, jumlah_rating);
    cout << "\n========================================" << endl;
    cout << "SORTING: Insertion Sort" << endl;
    cout << "DATA: Bintang Rating" << endl;
    cout << "URUTAN: Ascending (Terkecil-Terbesar)" << endl;
    cout << "========================================" << endl;
    cout << "\n--- SEMUA RATING (TERURUT) ---" << endl;
    for (int indeks = 0; indeks < jumlah_rating; indeks++) {
        cout << indeks+1 << ". [" << (*(daftar_rating + indeks)).namaUser << "] * " << (*(daftar_rating + indeks)).bintang << " - " << (*(daftar_rating + indeks)).ulasan << endl;
    }
}

int pencarian_linier_nama(Lapangan* daftar_lapangan, int jumlah_lapangan, string target) {
    for (int indeks = 0; indeks < jumlah_lapangan; indeks++) {
        if ((*(daftar_lapangan + indeks)).nama == target) {
            return indeks;
        }
    }
    return -1;
}

int pencarian_biner_tagihan(Reservasi* daftar_reservasi, int jumlah_reservasi, int target) {
    int kiri = 0;
    int kanan = jumlah_reservasi - 1;
    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        int nilai_tengah = (*(daftar_reservasi + tengah)).totalTagihan;
        if (nilai_tengah == target) return tengah;
        if (nilai_tengah < target) kiri = tengah + 1;
        else kanan = tengah - 1;
    }
    return -1;
}

void menu_admin(Lapangan* daftar_lapangan, int& jumlah_lapangan, Rating* daftar_rating, int& jumlah_rating, Reservasi* daftar_reservasi, int& jumlah_reservasi) {
    int pilihan_admin;
    while (true) {
        cout << "\n[ MENU ADMIN ]" << endl;
        cout << "1. Status Lapangan" << endl;
        cout << "2. Lihat Daftar Rating" << endl;
        cout << "3. Hapus Ulasan (Rating)" << endl;
        cout << "4. Tambah Lapangan" << endl;
        cout << "5. Hapus Lapangan" << endl;
        cout << "6. Edit Detail Lapangan" << endl;
        cout << "7. Urutkan Lapangan (Nama - Ascending)" << endl;
        cout << "8. Urutkan Reservasi (Tagihan - Descending)" << endl;
        cout << "9. Urutkan Rating (Bintang - Ascending)" << endl;
        cout << "10. Cari Lapangan (Nama - Linear Search)" << endl;
        cout << "11. Cari Tagihan (Binary Search)" << endl;
        cout << "12. Keluar" << endl;
        cout << "Pilih: "; cin >> pilihan_admin;
        
        if (pilihan_admin == 1) {
            cout << "\n" << left << setw(20) << "NAMA" << setw(15) << "TERSEDIA" << "TOTAL UNIT" << endl;
            for(int indeks=0; indeks<jumlah_lapangan; indeks++) cout << left << setw(20) << (*(daftar_lapangan + indeks)).nama << setw(15) << (*(daftar_lapangan + indeks)).tersedia << (*(daftar_lapangan + indeks)).kapasitasAwal << endl;
        } else if (pilihan_admin == 2) {
            cout << "\n--- SEMUA ULASAN PENGGUNA ---" << endl;
            for (int indeks = 0; indeks < jumlah_rating; indeks++) cout << indeks+1 << ". [" << (*(daftar_rating + indeks)).namaUser << "] * " << (*(daftar_rating + indeks)).bintang << "\n   Ulasan: " << (*(daftar_rating + indeks)).ulasan << endl;
        } else if (pilihan_admin == 3) {
            cout << "\n--- HAPUS ULASAN ---" << endl;
            for (int indeks = 0; indeks < jumlah_rating; indeks++) cout << indeks+1 << ". [" << (*(daftar_rating + indeks)).namaUser << "] * " << (*(daftar_rating + indeks)).bintang << endl;
            cout << "Pilih nomor ulasan untuk dihapus (0 batal): "; int pilihan = masukan_angka();
            if (pilihan > 0 && pilihan <= jumlah_rating) { hapus_rating(daftar_rating, jumlah_rating, pilihan - 1); tampilkan_pesan("Ulasan berhasil dihapus."); }
        } else if (pilihan_admin == 4) {
            tambah_lapangan(daftar_lapangan, jumlah_lapangan);
        } else if (pilihan_admin == 5) {
            hapus_lapangan(daftar_lapangan, jumlah_lapangan, daftar_reservasi, jumlah_reservasi);
        } else if (pilihan_admin == 6) {
            edit_lapangan(daftar_lapangan, jumlah_lapangan);
        } else if (pilihan_admin == 7) {
            bubble_sort_nama_lapangan_user(daftar_lapangan, jumlah_lapangan);
        } else if (pilihan_admin == 8) {
            if (jumlah_reservasi > 1) quick_sort_tagihan_reservasi(daftar_reservasi, 0, jumlah_reservasi - 1);
            cout << "\n========================================" << endl;
            cout << "SORTING: Quick Sort" << endl;
            cout << "DATA: Total Tagihan Reservasi" << endl;
            cout << "URUTAN: Descending (Terbesar-Terkecil)" << endl;
            cout << "========================================" << endl;
            cout << "\n--- SEMUA RESERVASI (TERURUT) ---" << endl;
            for (int indeks = 0; indeks < jumlah_reservasi; indeks++) {
                cout << "- [" << daftar_reservasi[indeks].usernamePemilik << "] " << daftar_reservasi[indeks].namaLapangan << " | Rp" << daftar_reservasi[indeks].totalTagihan << endl;
            }
        } else if (pilihan_admin == 9) {
            insertion_sort_bintang_rating_user(daftar_rating, jumlah_rating);
        } else if (pilihan_admin == 10) {
            cout << "\n--- PENCARIAN LAPANGAN (LINEAR SEARCH) ---" << endl;
            bersihkan_masukan();
            cout << "Masukkan nama lapangan yang dicari: ";
            string nama_cari;
            getline(cin, nama_cari);
            int hasil = pencarian_linier_nama(daftar_lapangan, jumlah_lapangan, nama_cari);
            if (hasil != -1) {
                cout << "\n>>> LAPANGAN DITEMUKAN! <<<" << endl;
                cout << "Nama        : " << (*(daftar_lapangan + hasil)).nama << endl;
                cout << "Harga/Jam   : Rp" << (*(daftar_lapangan + hasil)).harga << endl;
                cout << "Bahan       : " << (*(daftar_lapangan + hasil)).bahan << endl;
                cout << "Deskripsi   : " << (*(daftar_lapangan + hasil)).deskripsi << endl;
                cout << "Tersedia    : " << (*(daftar_lapangan + hasil)).tersedia << " dari " << (*(daftar_lapangan + hasil)).kapasitasAwal << endl;
            } else {
                cout << "\n[!] Lapangan tidak ditemukan.\n";
            }
        } else if (pilihan_admin == 11) {
            cout << "\n--- PENCARIAN TAGIHAN (BINARY SEARCH) ---" << endl;
            cout << "Catatan: Data harus diurutkan terlebih dahulu (Opsi 8)" << endl;
            cout << "Masukkan nominal tagihan yang dicari: Rp";
            int tagihan_cari = masukan_angka();
            if (jumlah_reservasi > 0) {
                quick_sort_tagihan_reservasi(daftar_reservasi, 0, jumlah_reservasi - 1);
                int hasil = pencarian_biner_tagihan(daftar_reservasi, jumlah_reservasi, tagihan_cari);
                if (hasil != -1) {
                    cout << "\n>>> TAGIHAN DITEMUKAN! <<<" << endl;
                    cout << "Pemesan     : " << (*(daftar_reservasi + hasil)).namaPemesan << endl;
                    cout << "Lapangan    : " << (*(daftar_reservasi + hasil)).namaLapangan << endl;
                    cout << "Tanggal     : " << (*(daftar_reservasi + hasil)).jadwal.tanggal << endl;
                    cout << "Jam         : " << (*(daftar_reservasi + hasil)).jadwal.jam << endl;
                    cout << "Total       : Rp" << (*(daftar_reservasi + hasil)).totalTagihan << endl;
                    cout << "Bayar       : Rp" << (*(daftar_reservasi + hasil)).uangBayar << endl;
                    cout << "Kembalian   : Rp" << (*(daftar_reservasi + hasil)).kembalian << endl;
                } else {
                    cout << "\n[!] Tagihan Rp" << tagihan_cari << " tidak ditemukan.\n";
                }
            } else {
                cout << "\n[!] Belum ada data reservasi.\n";
            }
        } else if (pilihan_admin == 12) {
            break;
        } else {
            cout << "[!] Menu tidak valid.\n";
        }
    }
}

void menu_pengguna(string nama_pengguna, Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, Rating* daftar_rating, int& jumlah_reservasi, int& jumlah_rating) {
    int pilihan_pengguna;
    while (true) {
        cout << "\n[ MENU PENGGUNA - " << nama_pengguna << " ]" << endl;
        cout << "1. Info Detail Lapangan" << endl;
        cout << "2. Sewa Lapangan (Pesan)" << endl;
        cout << "3. Riwayat Pembayaran" << endl;
        cout << "4. Beri Rating & Ulasan" << endl;
        cout << "5. Hapus Riwayat Pesan Saya" << endl;
        cout << "6. Hapus Rating Saya" << endl;
        cout << "7. Urutkan Lapangan (Nama - Ascending)" << endl;
        cout << "8. Urutkan Rating (Bintang - Ascending)" << endl;
        cout << "9. Urutkan Riwayat Saya (Tagihan - Descending)" << endl;
        cout << "10. Cari Lapangan (Nama - Linear Search)" << endl;
        cout << "11. Keluar" << endl;
        cout << "Pilih: "; pilihan_pengguna = masukan_angka();

        if (pilihan_pengguna == 1) tampilkan_detail_lapangan(daftar_lapangan, jumlah_lapangan);
        else if (pilihan_pengguna == 2) proses_pesan(nama_pengguna, daftar_lapangan, jumlah_lapangan, daftar_reservasi, jumlah_reservasi);
        else if (pilihan_pengguna == 3) tampilkan_riwayat(nama_pengguna, daftar_reservasi, jumlah_reservasi);
        else if (pilihan_pengguna == 4) tambah_rating(nama_pengguna, daftar_rating, jumlah_rating);
        else if (pilihan_pengguna == 5) {
            cout << "\n--- HAPUS RIWAYAT PESAN ---" << endl;
            int peta_indeks[100], jumlah_temuan = 0;
            for(int indeks=0; indeks<jumlah_reservasi; indeks++) {
                if (daftar_reservasi[indeks].usernamePemilik == nama_pengguna) {
                    cout << jumlah_temuan+1 << ". [" << daftar_reservasi[indeks].jadwal.tanggal << " " << daftar_reservasi[indeks].jadwal.jam << "] " 
                         << daftar_reservasi[indeks].namaLapangan << " | Rp" << daftar_reservasi[indeks].totalTagihan << endl;
                    peta_indeks[jumlah_temuan] = indeks; jumlah_temuan++;
                }
            }
            if(jumlah_temuan == 0) { cout << "Belum ada transaksi.\n"; continue; }
            cout << "Pilih nomor untuk dihapus (0 batal): "; int pilihan = masukan_angka();
            if(pilihan > 0 && pilihan <= jumlah_temuan) { hapus_reservasi(daftar_lapangan, jumlah_lapangan, daftar_reservasi, jumlah_reservasi, peta_indeks[pilihan-1]); tampilkan_pesan("Reservasi berhasil dihapus & kuota dikembalikan."); }
        } else if (pilihan_pengguna == 6) {
            hapus_rating_pengguna(nama_pengguna, daftar_rating, jumlah_rating);
        } else if (pilihan_pengguna == 7) {
            bubble_sort_nama_lapangan_user(daftar_lapangan, jumlah_lapangan);
        } else if (pilihan_pengguna == 8) {
            insertion_sort_bintang_rating_user(daftar_rating, jumlah_rating);
        } else if (pilihan_pengguna == 9) {
            if (jumlah_reservasi > 1) quick_sort_tagihan_reservasi(daftar_reservasi, 0, jumlah_reservasi - 1);
            quick_sort_tagihan_reservasi_user(daftar_reservasi, 0, jumlah_reservasi - 1, nama_pengguna);
        } else if (pilihan_pengguna == 10) {
            cout << "\n--- PENCARIAN LAPANGAN (LINEAR SEARCH) ---" << endl;
            bersihkan_masukan();
            cout << "Masukkan nama lapangan yang dicari: ";
            string nama_cari;
            getline(cin, nama_cari);
            int hasil = pencarian_linier_nama(daftar_lapangan, jumlah_lapangan, nama_cari);
            if (hasil != -1) {
                cout << "\n>>> LAPANGAN DITEMUKAN! <<<" << endl;
                cout << "Nama        : " << (*(daftar_lapangan + hasil)).nama << endl;
                cout << "Harga/Jam   : Rp" << (*(daftar_lapangan + hasil)).harga << endl;
                cout << "Bahan       : " << (*(daftar_lapangan + hasil)).bahan << endl;
                cout << "Deskripsi   : " << (*(daftar_lapangan + hasil)).deskripsi << endl;
                cout << "Tersedia    : " << (*(daftar_lapangan + hasil)).tersedia << " dari " << (*(daftar_lapangan + hasil)).kapasitasAwal << endl;
            } else {
                cout << "\n[!] Lapangan tidak ditemukan.\n";
            }
        } else if (pilihan_pengguna == 11) {
            break;
        } else {
            cout << "[!] Pilihan tidak valid.\n";
        }
    }
}

void proses_pesan(string nama_pengguna, Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi) {
    if (jumlah_reservasi >= MAX_DATA) { cout << "\n[!] Kapasitas sistem reservasi penuh.\n"; return; }
    cout << "\n--- PILIH LAPANGAN ---" << endl;
    for(int indeks=0; indeks<jumlah_lapangan; indeks++) cout << indeks+1 << ". " << left << setw(18) << (*(daftar_lapangan + indeks)).nama << "(Tersedia: " << (*(daftar_lapangan + indeks)).tersedia << ")" << endl;
    cout << jumlah_lapangan+1 << ". Batal & Kembali" << endl; cout << "Pilih (1-" << jumlah_lapangan+1 << "): "; int pilih_lapangan; cin >> pilih_lapangan;
    if (pilih_lapangan == jumlah_lapangan+1) return;
    if (pilih_lapangan >= 1 && pilih_lapangan <= jumlah_lapangan) {
        int indeks = pilih_lapangan - 1;
        if ((*(daftar_lapangan + indeks)).tersedia > 0) {
            cout << "\n--- FORM PEMESANAN [" << (*(daftar_lapangan + indeks)).nama << "] ---" << endl;
            bersihkan_masukan();
            cout << "Nama Pemesan      : "; getline(cin, (*(daftar_reservasi + jumlah_reservasi)).namaPemesan);
            cout << "[Contoh: 10-03] Tanggal : "; cin >> (*(daftar_reservasi + jumlah_reservasi)).jadwal.tanggal;
            cout << "[Contoh: 19:00] Jam     : "; cin >> (*(daftar_reservasi + jumlah_reservasi)).jadwal.jam;
            cout << "Durasi Main (Jam)       : "; cin >> (*(daftar_reservasi + jumlah_reservasi)).jadwal.durasi;
            if ((*(daftar_reservasi + jumlah_reservasi)).jadwal.durasi <= 0) { cout << "\n[!] Durasi tidak valid!\n"; return; }
            int total = (*(daftar_lapangan + indeks)).harga * (*(daftar_reservasi + jumlah_reservasi)).jadwal.durasi;
            cout << "\nTOTAL TAGIHAN : Rp" << total << "\nMasukkan Uang : Rp"; int bayar; cin >> bayar;
            if (bayar < total) cout << "\n[!] PEMBAYARAN GAGAL! Uang kurang Rp" << total - bayar << endl;
            else {
                (*(daftar_reservasi + jumlah_reservasi)).totalTagihan = total;
                (*(daftar_reservasi + jumlah_reservasi)).uangBayar = bayar;
                (*(daftar_reservasi + jumlah_reservasi)).kembalian = bayar - total;
                (*(daftar_reservasi + jumlah_reservasi)).namaLapangan = (*(daftar_lapangan + indeks)).nama;
                (*(daftar_reservasi + jumlah_reservasi)).usernamePemilik = nama_pengguna;
                (*(daftar_lapangan + indeks)).tersedia--;
                if (bayar == total) tampilkan_pesan("BERHASIL! (Uang Pas)");
                else tampilkan_pesan("BERHASIL! Kembalian", bayar-total);
                jumlah_reservasi++;
            }
        } else cout << "\n[!] Lapangan penuh!" << endl;
    } else cout << "\n[!] Pilihan tidak valid!" << endl;
}

void tampilkan_riwayat(string nama_pengguna, Reservasi* daftar_reservasi, int jumlah_reservasi) {
    cout << "\n--- RIWAYAT TRANSAKSI ---" << endl; bool ada = false;
    for (int indeks = 0; indeks < jumlah_reservasi; indeks++) {
        if (daftar_reservasi[indeks].usernamePemilik == nama_pengguna) {
            cout << "- Lapangan: " << daftar_reservasi[indeks].namaLapangan << " | Total: Rp" << daftar_reservasi[indeks].totalTagihan << " | Bayar: Rp" << daftar_reservasi[indeks].uangBayar << " | Kembali: Rp" << daftar_reservasi[indeks].kembalian << endl;
            ada = true;
        }
    }
    if (!ada) cout << "Belum ada transaksi.\n";
}

void tambah_rating(string nama_pengguna, Rating* daftar_rating, int& jumlah_rating) {
    if(jumlah_rating >= MAX_DATA) { cout << "\n[!] Kapasitas rating penuh.\n"; return; }
    cout << "\n--- BERI RATING ---" << endl;
    (*(daftar_rating + jumlah_rating)).namaUser = nama_pengguna;
    cout << "Bintang (1-5): "; (*(daftar_rating + jumlah_rating)).bintang = masukan_angka();
    if((*(daftar_rating + jumlah_rating)).bintang < 1 || (*(daftar_rating + jumlah_rating)).bintang > 5) { cout << "[!] Rating batal.\n"; return; }
    bersihkan_masukan();
    cout << "Ulasan       : "; getline(cin, (*(daftar_rating + jumlah_rating)).ulasan);
    jumlah_rating++;
    tampilkan_pesan("Terima kasih " + nama_pengguna + "!");
}

void hapus_rating_pengguna(string nama_pengguna, Rating* daftar_rating, int& jumlah_rating) {
    cout << "\n--- HAPUS RATING SAYA ---" << endl;
    int peta_indeks[100], jumlah_temuan = 0;
    for(int indeks = 0; indeks < jumlah_rating; indeks++) {
        if((*(daftar_rating + indeks)).namaUser == nama_pengguna) {
            cout << jumlah_temuan+1 << ". [" << (*(daftar_rating + indeks)).bintang << "/5] " << (*(daftar_rating + indeks)).ulasan << endl;
            peta_indeks[jumlah_temuan] = indeks; jumlah_temuan++;
        }
    }
    if(jumlah_temuan == 0) { cout << "Belum ada rating dari kamu.\n"; return; }
    cout << "Pilih nomor rating untuk dihapus (0 batal): "; int pilihan = masukan_angka();
    if(pilihan > 0 && pilihan <= jumlah_temuan) {
        int indeks_asli = peta_indeks[pilihan-1];
        hapus_rating(daftar_rating, jumlah_rating, indeks_asli);
        tampilkan_pesan("Rating berhasil dihapus.");
    }
}

void hapus_reservasi(Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi, int indeks) {
    if (indeks < 0 || indeks >= jumlah_reservasi) return;
    string nama_lapangan = (*(daftar_reservasi + indeks)).namaLapangan;
    for(int indeks_lap=0; indeks_lap<jumlah_lapangan; indeks_lap++) { if((*(daftar_lapangan + indeks_lap)).nama == nama_lapangan) { (*(daftar_lapangan + indeks_lap)).tersedia++; break; } }
    for(int indeks_geser = indeks; indeks_geser < jumlah_reservasi - 1; indeks_geser++) { *(daftar_reservasi + indeks_geser) = *(daftar_reservasi + indeks_geser + 1); }
    jumlah_reservasi--;
}

void hapus_rating(Rating* daftar_rating, int& jumlah_rating, int indeks) {
    if (indeks < 0 || indeks >= jumlah_rating) return;
    for(int indeks_geser = indeks; indeks_geser < jumlah_rating - 1; indeks_geser++) { *(daftar_rating + indeks_geser) = *(daftar_rating + indeks_geser + 1); }
    jumlah_rating--;
}