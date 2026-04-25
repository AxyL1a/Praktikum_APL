#include "GorStruk.h"
#include "GorLibrary.h"

void tampilkan_pesan_string(const string& pesan) { 
    cetak_berwarna("\n>>> " + pesan + " <<<", 32); 
    cout << endl; 
}

void tampilkan_pesan_nilai(const string& pesan, int nilai) { 
    cetak_berwarna("\n[!] " + pesan + ": " + to_string(nilai), 33); 
    cout << endl; 
}

void bersihkan_masukan() { 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

int masukan_angka() {
    int angka;
    while (true) {
        if (cin >> angka) {
            return angka;
        } else {
            cin.clear();
            bersihkan_masukan();
            cetak_berwarna("\n[!] ERROR: Input harus berupa angka! Silakan coba lagi.", 31);
            cout << endl;
        }
    }
}

float hitung_total_bintang_rekursif(Rating* daftar_rating, int jumlah) {
    if (jumlah <= 0) return 0;
    return (*(daftar_rating + jumlah - 1)).bintang + hitung_total_bintang_rekursif(daftar_rating, jumlah - 1);
}

void tampilkan_header(Rating* daftar_rating, int jumlah_rating) {
    header_berwarna();
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
        cetak_berwarna("\n[!] Kapasitas pengguna penuh.\n", 31); 
        return; 
    }
    cout << "\nNama Pengguna Baru : "; 
    cin >> (*(daftar_pengguna + jumlah_pengguna)).username;
    cout << "Kata Sandi Baru : "; 
    cin >> (*(daftar_pengguna + jumlah_pengguna)).password;
    jumlah_pengguna++; 
    tampilkan_pesan_string("REGISTRASI BERHASIL! Silakan Masuk.");
}

bool proses_masuk(User* daftar_pengguna, int jumlah_pengguna, string& nama_pengguna_keluar) {
    string nama_pengguna, kata_sandi; 
    int batas_gagal = 0;
    
    while (batas_gagal < 3) {
        cout << "\nNama Pengguna : "; cin >> nama_pengguna; 
        cout << "Kata Sandi : "; cin >> kata_sandi;
        if (nama_pengguna == "adminGor" && kata_sandi == "sanjayaclub990") { 
            nama_pengguna_keluar = "adminGor"; 
            return true; 
        }
        for (int indeks = 0; indeks < jumlah_pengguna; indeks++) {
            if ((*(daftar_pengguna + indeks)).username == nama_pengguna && (*(daftar_pengguna + indeks)).password == kata_sandi) { 
                nama_pengguna_keluar = nama_pengguna; 
                return true; 
            }
        }
        batas_gagal++;
        cetak_berwarna("\n[!] MASUK GAGAL! Nama Pengguna atau Kata Sandi salah.", 31);
        if (batas_gagal < 3) cout << "[!] Sisa percobaan: " << 3 - batas_gagal << " kali." << endl;
    }
    return false;
}

void tambah_lapangan(Lapangan* daftar_lapangan, int& jumlah_lapangan) {
    if (jumlah_lapangan >= MAX_DATA) { 
        cetak_berwarna("\n[!] Kapasitas data lapangan penuh.\n", 31); 
        return; 
    }
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
    tampilkan_pesan_string("Lapangan berhasil ditambahkan.");
}

void hapus_lapangan(Lapangan* daftar_lapangan, int& jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi) {
    if (jumlah_lapangan <= 0) { 
        cetak_berwarna("\n[!] Tidak ada lapangan untuk dihapus.\n", 31); 
        return; 
    }
    tampilkan_daftar_lapangan_admin(daftar_lapangan, jumlah_lapangan);
    cout << "\nPilih nomor lapangan untuk dihapus (0 batal): "; 
    int pilihan = masukan_angka();
    if (pilihan < 1 || pilihan > jumlah_lapangan) { 
        cout << "[!] Batal menghapus.\n"; 
        return; 
    }
    int indeks = pilihan - 1;
    string nama_lapangan = (*(daftar_lapangan + indeks)).nama;
    for(int indeks_res = 0; indeks_res < jumlah_reservasi; indeks_res++) {
        if (daftar_reservasi[indeks_res].namaLapangan == nama_lapangan) {
            cetak_berwarna("[!] Tidak bisa hapus: masih ada reservasi aktif.\n", 31); 
            return;
        }
    }
    for(int indeks_geser = indeks; indeks_geser < jumlah_lapangan - 1; indeks_geser++) {
        *(daftar_lapangan + indeks_geser) = *(daftar_lapangan + indeks_geser + 1);
    }
    jumlah_lapangan--;
    tampilkan_pesan_string("Lapangan berhasil dihapus.");
}

void edit_lapangan(Lapangan* daftar_lapangan, int jumlah_lapangan) {
    if (jumlah_lapangan <= 0) { 
        cetak_berwarna("\n[!] Tidak ada lapangan untuk diedit.\n", 31); 
        return; 
    }
    tampilkan_daftar_lapangan_admin(daftar_lapangan, jumlah_lapangan);
    cout << "\nPilih nomor lapangan untuk diedit (0 batal): "; 
    int pilihan = masukan_angka();
    if (pilihan < 1 || pilihan > jumlah_lapangan) { 
        cout << "[!] Batal mengedit.\n"; 
        return; 
    }
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
    tampilkan_pesan_string("Data lapangan berhasil diperbarui.");
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
    cetak_berwarna("SORTING: Bubble Sort\nDATA: Nama Lapangan\nURUTAN: Ascending (A-Z)", 34);
    cout << "\n========================================" << endl;
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
    cetak_berwarna("SORTING: Quick Sort\nDATA: Total Tagihan\nURUTAN: Descending", 34);
    cout << "\n========================================" << endl;
    bool ada = false;
    for (int indeks = 0; indeks < high + 1; indeks++) {
        if (daftar[indeks].usernamePemilik == username) { 
            cout << "- " << daftar[indeks].namaLapangan << " | Rp" << daftar[indeks].totalTagihan << endl; 
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
    cetak_berwarna("SORTING: Insertion Sort\nDATA: Bintang Rating\nURUTAN: Ascending", 34);
    cout << "\n========================================" << endl;
    for (int indeks = 0; indeks < jumlah_rating; indeks++) {
        cout << indeks+1 << ". [" << (*(daftar_rating + indeks)).namaUser << "] * " << (*(daftar_rating + indeks)).bintang << " - " << (*(daftar_rating + indeks)).ulasan << endl;
    }
}

int pencarian_linier_nama(Lapangan* daftar_lapangan, int jumlah_lapangan, string target) {
    for (int indeks = 0; indeks < jumlah_lapangan; indeks++) {
        if ((*(daftar_lapangan + indeks)).nama == target) return indeks;
    }
    throw DataTidakDitemukanException("Lapangan '" + target + "' tidak ditemukan dalam database!");
}

int pencarian_biner_tagihan(Reservasi* daftar_reservasi, int jumlah_reservasi, int target) {
    int kiri = 0, kanan = jumlah_reservasi - 1;
    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        int nilai_tengah = (*(daftar_reservasi + tengah)).totalTagihan;
        if (nilai_tengah == target) return tengah;
        if (nilai_tengah < target) kiri = tengah + 1;
        else kanan = tengah - 1;
    }
    throw DataTidakDitemukanException("Tagihan Rp" + to_string(target) + " tidak ditemukan!");
}

void proses_pesan(string nama_pengguna, Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi) {
    try {
        if (jumlah_reservasi >= MAX_DATA) { 
            cetak_berwarna("[!] Kapasitas sistem reservasi penuh.\n", 31); 
            return; 
        }
        cout << "\n--- PILIH LAPANGAN ---" << endl;
        for(int indeks=0; indeks<jumlah_lapangan; indeks++) 
            cout << indeks+1 << ". " << (*(daftar_lapangan + indeks)).nama << "(Tersedia: " << (*(daftar_lapangan + indeks)).tersedia << ")" << endl;
        cout << jumlah_lapangan+1 << ". Batal & Kembali" << endl; 
        cout << "Pilih (1-" << jumlah_lapangan+1 << "): "; 
        int pilih_lapangan = masukan_angka();
        
        if (pilih_lapangan == jumlah_lapangan+1) return;
        if (pilih_lapangan < 1 || pilih_lapangan > jumlah_lapangan) 
            throw logic_error("Nomor lapangan tidak valid!");

        int indeks = pilih_lapangan - 1;
        if ((*(daftar_lapangan + indeks)).tersedia > 0) {
            cout << "\n--- FORM PEMESANAN [" << (*(daftar_lapangan + indeks)).nama << "] ---" << endl;
            bersihkan_masukan();
            cout << "Nama Pemesan      : "; getline(cin, (*(daftar_reservasi + jumlah_reservasi)).namaPemesan);
            cout << "Tanggal : "; cin >> (*(daftar_reservasi + jumlah_reservasi)).jadwal.tanggal;
            cout << "Jam     : "; cin >> (*(daftar_reservasi + jumlah_reservasi)).jadwal.jam;
            cout << "Durasi  : "; (*(daftar_reservasi + jumlah_reservasi)).jadwal.durasi = masukan_angka();
            
            if ((*(daftar_reservasi + jumlah_reservasi)).jadwal.durasi <= 0) 
                throw logic_error("Durasi main tidak boleh 0 atau negatif!");
            
            int total = (*(daftar_lapangan + indeks)).harga * (*(daftar_reservasi + jumlah_reservasi)).jadwal.durasi;
            cout << "\nTOTAL TAGIHAN : Rp" << total << "\nMasukkan Uang : Rp"; 
            int bayar = masukan_angka();
            
            if (bayar < total) 
                throw KurangBayarException("Uang pembayaran kurang!", total - bayar);
            
            (*(daftar_reservasi + jumlah_reservasi)).totalTagihan = total;
            (*(daftar_reservasi + jumlah_reservasi)).uangBayar = bayar;
            (*(daftar_reservasi + jumlah_reservasi)).kembalian = bayar - total;
            (*(daftar_reservasi + jumlah_reservasi)).namaLapangan = (*(daftar_lapangan + indeks)).nama;
            (*(daftar_reservasi + jumlah_reservasi)).usernamePemilik = nama_pengguna;
            (*(daftar_lapangan + indeks)).tersedia--;
            
            if (bayar == total) 
                tampilkan_pesan_string("BERHASIL! (Uang Pas)");
            else 
                tampilkan_pesan_nilai("BERHASIL! Kembalian", bayar-total);
            jumlah_reservasi++;
        } else {
            throw runtime_error("Lapangan sedang penuh!");
        }
    } catch (const KurangBayarException& e) {
        cetak_berwarna("\n[!] TRANSAKSI DITOLAK: " + string(e.what()), 31);
        cout << "[!] Anda kurang membayar sebesar: Rp" << e.getJumlahKurang() << endl;
    } catch (const logic_error& e) {
        cetak_berwarna("\n[!] KESALAHAN LOGIKA: " + string(e.what()), 31);
    } catch (const runtime_error& e) {
        cetak_berwarna("\n[!] KESALAHAN SISTEM: " + string(e.what()), 31);
    }
}

void tampilkan_riwayat(string nama_pengguna, Reservasi* daftar_reservasi, int jumlah_reservasi) {
    cout << "\n--- RIWAYAT TRANSAKSI ---" << endl; 
    bool ada = false;
    for (int indeks = 0; indeks < jumlah_reservasi; indeks++) {
        if (daftar_reservasi[indeks].usernamePemilik == nama_pengguna) {
            cout << "- " << daftar_reservasi[indeks].namaLapangan << " | Total: Rp" << daftar_reservasi[indeks].totalTagihan << endl;
            ada = true;
        }
    }
    if (!ada) cout << "Belum ada transaksi.\n";
}

void tambah_rating(string nama_pengguna, Rating* daftar_rating, int& jumlah_rating) {
    if(jumlah_rating >= MAX_DATA) { 
        cetak_berwarna("\n[!] Kapasitas rating penuh.\n", 31); 
        return; 
    }
    cout << "\n--- BERI RATING ---" << endl;
    (*(daftar_rating + jumlah_rating)).namaUser = nama_pengguna;
    cout << "Bintang (1-5): "; 
    (*(daftar_rating + jumlah_rating)).bintang = masukan_angka();
    if((*(daftar_rating + jumlah_rating)).bintang < 1 || (*(daftar_rating + jumlah_rating)).bintang > 5) { 
        cetak_berwarna("[!] Rating batal.\n", 31); 
        return; 
    }
    bersihkan_masukan();
    cout << "Ulasan       : "; 
    getline(cin, (*(daftar_rating + jumlah_rating)).ulasan);
    jumlah_rating++;
    tampilkan_pesan_string("Terima kasih " + nama_pengguna + "!");
}

void hapus_rating_pengguna(string nama_pengguna, Rating* daftar_rating, int& jumlah_rating) {
    cout << "\n--- HAPUS RATING SAYA ---" << endl;
    int peta_indeks[100], jumlah_temuan = 0;
    for(int indeks = 0; indeks < jumlah_rating; indeks++) {
        if((*(daftar_rating + indeks)).namaUser == nama_pengguna) {
            cout << jumlah_temuan+1 << ". [" << (*(daftar_rating + indeks)).bintang << "/5] " << (*(daftar_rating + indeks)).ulasan << endl;
            peta_indeks[jumlah_temuan] = indeks; 
            jumlah_temuan++;
        }
    }
    if(jumlah_temuan == 0) { 
        cout << "Belum ada rating dari kamu.\n"; 
        return; 
    }
    cout << "Pilih nomor rating untuk dihapus (0 batal): "; 
    int pilihan = masukan_angka();
    if(pilihan > 0 && pilihan <= jumlah_temuan) {
        hapus_rating(daftar_rating, jumlah_rating, peta_indeks[pilihan-1]);
        tampilkan_pesan_string("Rating berhasil dihapus.");
    }
}

void hapus_reservasi(Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi, int indeks) {
    if (indeks < 0 || indeks >= jumlah_reservasi) return;
    string nama_lapangan = (*(daftar_reservasi + indeks)).namaLapangan;
    for(int indeks_lap=0; indeks_lap<jumlah_lapangan; indeks_lap++) { 
        if((*(daftar_lapangan + indeks_lap)).nama == nama_lapangan) { 
            (*(daftar_lapangan + indeks_lap)).tersedia++; 
            break; 
        } 
    }
    for(int indeks_geser = indeks; indeks_geser < jumlah_reservasi - 1; indeks_geser++) { 
        *(daftar_reservasi + indeks_geser) = *(daftar_reservasi + indeks_geser + 1); 
    }
    jumlah_reservasi--;
}

void hapus_rating(Rating* daftar_rating, int& jumlah_rating, int indeks) {
    if (indeks < 0 || indeks >= jumlah_rating) return;
    for(int indeks_geser = indeks; indeks_geser < jumlah_rating - 1; indeks_geser++) { 
        *(daftar_rating + indeks_geser) = *(daftar_rating + indeks_geser + 1); 
    }
    jumlah_rating--;
}

void menu_admin(Lapangan* daftar_lapangan, int& jumlah_lapangan, Rating* daftar_rating, int& jumlah_rating, Reservasi* daftar_reservasi, int& jumlah_reservasi) {
    int pilihan_admin;
    while (true) {
        try {
            cout << "\n[ MENU ADMIN ]" << endl;
            cout << "1. Status Lapangan\n2. Lihat Daftar Rating\n3. Hapus Ulasan\n4. Tambah Lapangan\n5. Hapus Lapangan\n6. Edit Detail Lapangan\n7. Urutkan Lapangan (Nama - Ascending)\n8. Urutkan Reservasi (Tagihan - Descending)\n9. Urutkan Rating (Bintang - Ascending)\n10. Cari Lapangan (Linear Search)\n11. Cari Tagihan (Binary Search)\n12. Keluar\nPilih: "; 
            pilihan_admin = masukan_angka();
            
            if (pilihan_admin == 1) {
                cout << "\n" << left << setw(20) << "NAMA" << setw(15) << "TERSEDIA" << "TOTAL UNIT" << endl;
                for(int indeks=0; indeks<jumlah_lapangan; indeks++) 
                    cout << left << setw(20) << (*(daftar_lapangan + indeks)).nama << setw(15) << (*(daftar_lapangan + indeks)).tersedia << (*(daftar_lapangan + indeks)).kapasitasAwal << endl;
            } else if (pilihan_admin == 2) {
                for (int indeks = 0; indeks < jumlah_rating; indeks++) 
                    cout << indeks+1 << ". [" << (*(daftar_rating + indeks)).namaUser << "] * " << (*(daftar_rating + indeks)).bintang << " - " << (*(daftar_rating + indeks)).ulasan << endl;
            } else if (pilihan_admin == 3) {
                for (int indeks = 0; indeks < jumlah_rating; indeks++) 
                    cout << indeks+1 << ". [" << (*(daftar_rating + indeks)).namaUser << "] * " << (*(daftar_rating + indeks)).bintang << endl;
                cout << "Pilih nomor ulasan untuk dihapus (0 batal): "; 
                int pilih = masukan_angka();
                if (pilih > 0 && pilih <= jumlah_rating) { 
                    hapus_rating(daftar_rating, jumlah_rating, pilih - 1); 
                    tampilkan_pesan_string("Ulasan berhasil dihapus."); 
                }
            } else if (pilihan_admin == 4) 
                tambah_lapangan(daftar_lapangan, jumlah_lapangan);
            else if (pilihan_admin == 5) 
                hapus_lapangan(daftar_lapangan, jumlah_lapangan, daftar_reservasi, jumlah_reservasi);
            else if (pilihan_admin == 6) 
                edit_lapangan(daftar_lapangan, jumlah_lapangan);
            else if (pilihan_admin == 7) 
                bubble_sort_nama_lapangan_user(daftar_lapangan, jumlah_lapangan);
            else if (pilihan_admin == 8) {
                if (jumlah_reservasi > 1) 
                    quick_sort_tagihan_reservasi(daftar_reservasi, 0, jumlah_reservasi - 1);
                cout << "\n========================================\n"; 
                cetak_berwarna("SORTING: Quick Sort\nDATA: Total Tagihan\nURUTAN: Descending", 34); 
                cout << "\n========================================\n";
                for (int indeks = 0; indeks < jumlah_reservasi; indeks++) 
                    cout << "- [" << daftar_reservasi[indeks].usernamePemilik << "] " << daftar_reservasi[indeks].namaLapangan << " | Rp" << daftar_reservasi[indeks].totalTagihan << endl;
            } else if (pilihan_admin == 9) 
                insertion_sort_bintang_rating_user(daftar_rating, jumlah_rating);
            else if (pilihan_admin == 10) {
                cout << "\n--- PENCARIAN LAPANGAN (LINEAR SEARCH) ---" << endl; 
                bersihkan_masukan();
                cout << "Masukkan nama lapangan: "; 
                string nama_cari; 
                getline(cin, nama_cari);
                try {
                    int hasil = pencarian_linier_nama(daftar_lapangan, jumlah_lapangan, nama_cari);
                    cout << "\n>>> LAPANGAN DITEMUKAN! <<<\nNama: " << (*(daftar_lapangan + hasil)).nama << "\nHarga: Rp" << (*(daftar_lapangan + hasil)).harga << endl;
                } catch (const DataTidakDitemukanException& e) { 
                    cetak_berwarna("\n" + string(e.what()), 31); 
                }
            } else if (pilihan_admin == 11) {
                cout << "\n--- PENCARIAN TAGIHAN (BINARY SEARCH) ---" << endl; 
                cout << "Masukkan nominal tagihan: Rp"; 
                int tagihan_cari = masukan_angka();
                try {
                    if (jumlah_reservasi > 0) {
                        quick_sort_tagihan_reservasi(daftar_reservasi, 0, jumlah_reservasi - 1);
                        int hasil = pencarian_biner_tagihan(daftar_reservasi, jumlah_reservasi, tagihan_cari);
                        cout << "\n>>> TAGIHAN DITEMUKAN! <<<\nPemesan: " << (*(daftar_reservasi + hasil)).namaPemesan << "\nTotal: Rp" << (*(daftar_reservasi + hasil)).totalTagihan << endl;
                    } else 
                        throw runtime_error("Belum ada data reservasi.");
                } catch (const DataTidakDitemukanException& e) { 
                    cetak_berwarna("\n" + string(e.what()), 31); 
                } catch (const runtime_error& e) { 
                    cetak_berwarna("\n" + string(e.what()), 31); 
                }
            } else if (pilihan_admin == 12) 
                break;
            else 
                throw invalid_argument("Nomor menu tidak valid.");
        } catch (const exception& e) { 
            cetak_berwarna("\n[!] ERROR: " + string(e.what()), 31); 
        }
    }
}

void menu_pengguna(string nama_pengguna, Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, Rating* daftar_rating, int& jumlah_reservasi, int& jumlah_rating) {
    int pilihan_pengguna;
    while (true) {
        try {
            cout << "\n[ MENU PENGGUNA - " << nama_pengguna << " ]" << endl;
            cout << "1. Info Detail Lapangan\n2. Sewa Lapangan\n3. Riwayat Pembayaran\n4. Beri Rating\n5. Hapus Riwayat Saya\n6. Hapus Rating Saya\n7. Urutkan Lapangan\n8. Urutkan Rating\n9. Urutkan Riwayat Saya\n10. Cari Lapangan\n11. Keluar\nPilih: "; 
            pilihan_pengguna = masukan_angka();

            if (pilihan_pengguna == 1) 
                tampilkan_detail_lapangan(daftar_lapangan, jumlah_lapangan);
            else if (pilihan_pengguna == 2) 
                proses_pesan(nama_pengguna, daftar_lapangan, jumlah_lapangan, daftar_reservasi, jumlah_reservasi);
            else if (pilihan_pengguna == 3) 
                tampilkan_riwayat(nama_pengguna, daftar_reservasi, jumlah_reservasi);
            else if (pilihan_pengguna == 4) 
                tambah_rating(nama_pengguna, daftar_rating, jumlah_rating);
            else if (pilihan_pengguna == 5) {
                cout << "\n--- HAPUS RIWAYAT PESAN ---" << endl;
                int peta_indeks[100], jumlah_temuan = 0;
                for(int indeks=0; indeks<jumlah_reservasi; indeks++) {
                    if (daftar_reservasi[indeks].usernamePemilik == nama_pengguna) {
                        cout << jumlah_temuan+1 << ". [" << daftar_reservasi[indeks].jadwal.tanggal << " " << daftar_reservasi[indeks].jadwal.jam << "] " << daftar_reservasi[indeks].namaLapangan << " | Rp" << daftar_reservasi[indeks].totalTagihan << endl;
                        peta_indeks[jumlah_temuan] = indeks; 
                        jumlah_temuan++;
                    }
                }
                if(jumlah_temuan == 0) { 
                    cout << "Belum ada transaksi.\n"; 
                    continue; 
                }
                cout << "Pilih nomor untuk dihapus (0 batal): "; 
                int pilihan = masukan_angka();
                if(pilihan > 0 && pilihan <= jumlah_temuan) { 
                    hapus_reservasi(daftar_lapangan, jumlah_lapangan, daftar_reservasi, jumlah_reservasi, peta_indeks[pilihan-1]); 
                    tampilkan_pesan_string("Reservasi berhasil dihapus."); 
                }
            } else if (pilihan_pengguna == 6) 
                hapus_rating_pengguna(nama_pengguna, daftar_rating, jumlah_rating);
            else if (pilihan_pengguna == 7) 
                bubble_sort_nama_lapangan_user(daftar_lapangan, jumlah_lapangan);
            else if (pilihan_pengguna == 8) 
                insertion_sort_bintang_rating_user(daftar_rating, jumlah_rating);
            else if (pilihan_pengguna == 9) {
                if (jumlah_reservasi > 1) 
                    quick_sort_tagihan_reservasi(daftar_reservasi, 0, jumlah_reservasi - 1);
                quick_sort_tagihan_reservasi_user(daftar_reservasi, 0, jumlah_reservasi - 1, nama_pengguna);
            } else if (pilihan_pengguna == 10) {
                cout << "\n--- PENCARIAN LAPANGAN ---" << endl; 
                bersihkan_masukan();
                cout << "Masukkan nama lapangan: "; 
                string nama_cari; 
                getline(cin, nama_cari);
                try {
                    int hasil = pencarian_linier_nama(daftar_lapangan, jumlah_lapangan, nama_cari);
                    cout << "\n>>> DITEMUKAN! <<<\nNama: " << (*(daftar_lapangan + hasil)).nama << endl;
                } catch (const DataTidakDitemukanException& e) { 
                    cetak_berwarna("\n" + string(e.what()), 31); 
                }
            } else if (pilihan_pengguna == 11) 
                break;
            else 
                throw invalid_argument("Nomor menu tidak valid.");
        } catch (const exception& e) { 
            cetak_berwarna("\n[!] ERROR: " + string(e.what()), 31); 
        }
    }
}