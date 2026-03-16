#include <iostream>
#include <string>
#include <iomanip>
#include <limits> 

using namespace std;

struct Waktu {
    string tanggal; 
    string jam;     
    int durasi;
};

struct Lapangan {
    string nama;
    int harga;
    string bahan;
    string deskripsi;
    int kapasitasAwal; 
    int tersedia;      
};

struct Rating {
    string namaUser;
    int bintang;
    string ulasan;
};

struct Reservasi {
    string namaPemesan;
    string namaLapangan;
    Waktu jadwal; 
    int totalTagihan;
    int uangBayar;
    int kembalian;
    string usernamePemilik;
};

struct User {
    string username;
    string password; 
};

float hitungTotalBintang(Rating daftar[], int n) {
    if (n <= 0) return 0;
    return (float)daftar[n - 1].bintang + hitungTotalBintang(daftar, n - 1);
}

void tampilkanPesan(string msg) {
    cout << "\n>>> " << msg << " <<<" << endl;
}

void tampilkanPesan(string msg, int nilai) {
    cout << "\n[!] " << msg << ": " << nilai << endl;
}

void tampilkanHeader(int jumlahRating, Rating daftarRating[]) {
    cout << "\n======================================" << endl;
    cout << "       GOR BADMINTON SANJAYA          " << endl;
    cout << "======================================" << endl;

    if (jumlahRating > 0) {
        float totalBintang = hitungTotalBintang(daftarRating, jumlahRating);
        cout << "Rating GOR: " << fixed << setprecision(1) << (totalBintang/jumlahRating) << "/5.0 stars" << endl;
        cout << "Ulasan terbaru oleh [" << daftarRating[jumlahRating-1].namaUser << "]:" << endl;
        cout << "\"" << daftarRating[jumlahRating-1].ulasan << "\" (" << daftarRating[jumlahRating-1].bintang << "/5)" << endl;
        cout << "--------------------------------------" << endl;
    } else {
        cout << "Rating: Belum ada ulasan dari pelanggan" << endl;
        cout << "--------------------------------------" << endl;
    }
}

void menuAdmin(Lapangan listLap[], Rating daftarRating[], int jumlahRating) {
    int pilAdmin;
    while (true) {
        cout << "\n[ MENU ADMIN ]" << endl;
        cout << "1. Status Lapangan" << endl;
        cout << "2. Lihat Daftar Rating" << endl;
        cout << "3. Logout" << endl;
        cout << "Pilih: "; 
        cin >> pilAdmin;
        
        if (pilAdmin == 1) {
            cout << "\n" << left << setw(20) << "NAMA" << setw(15) << "TERSEDIA" << "TOTAL UNIT" << endl;
            for(int i=0; i<3; i++) cout << left << setw(20) << listLap[i].nama << setw(15) << listLap[i].tersedia << listLap[i].kapasitasAwal << endl;
        } else if (pilAdmin == 2) {
            cout << "\n--- SEMUA ULASAN USER ---" << endl;
            for (int i = 0; i < jumlahRating; i++) cout << i+1 << ". [" << daftarRating[i].namaUser << "] * " << daftarRating[i].bintang << "\n   Ulasan: " << daftarRating[i].ulasan << endl;
        } else if (pilAdmin == 3) {
            break;
        } else {
            cout << "[!] Menu tidak valid.\n";
        }
    }
}

void prosesBooking(string u, Lapangan listLap[], Reservasi daftarRes[], int &jumlahRes, int MAX_DATA) {
    if (jumlahRes >= MAX_DATA) {
        cout << "\n[!] Kapasitas sistem reservasi penuh. Hubungi Admin.\n";
        return;
    }

    cout << "\n--- PILIH LAPANGAN ---" << endl;
    for(int i=0; i<3; i++) cout << i+1 << ". " << left << setw(18) << listLap[i].nama << "(Tersedia: " << listLap[i].tersedia << ")" << endl;
    cout << "4. Batal & Kembali" << endl;
    
    cout << "Pilih (1-4): "; 
    int lapPilih;
    cin >> lapPilih;

    if (lapPilih == 4) return;
    if (lapPilih >= 1 && lapPilih <= 3) {
        int idx = lapPilih - 1;
        if (listLap[idx].tersedia > 0) {
            cout << "\n--- FORM PEMESANAN [" << listLap[idx].nama << "] ---" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Nama Pemesan      : "; getline(cin, daftarRes[jumlahRes].namaPemesan);
            cout << "[Contoh: 10-03] Tanggal : "; cin >> daftarRes[jumlahRes].jadwal.tanggal;
            cout << "[Contoh: 19:00] Jam     : "; cin >> daftarRes[jumlahRes].jadwal.jam;
            cout << "Durasi Main (Jam)       : "; cin >> daftarRes[jumlahRes].jadwal.durasi;

            if (daftarRes[jumlahRes].jadwal.durasi <= 0) {
                cout << "\n[!] Durasi tidak valid! Batal memesan.\n";
                return;
            }

            int total = listLap[idx].harga * daftarRes[jumlahRes].jadwal.durasi;
            cout << "\nTOTAL TAGIHAN : Rp" << total << endl;
            cout << "Masukkan Uang : Rp"; 
            int bayar;
            cin >> bayar;

            if (bayar < total) {
                cout << "\n[!] PEMBAYARAN GAGAL! Uang kurang Rp" << total - bayar << endl;
            } else {
                daftarRes[jumlahRes].totalTagihan = total;
                daftarRes[jumlahRes].uangBayar = bayar;
                daftarRes[jumlahRes].kembalian = bayar - total;
                daftarRes[jumlahRes].namaLapangan = listLap[idx].nama;
                daftarRes[jumlahRes].usernamePemilik = u;
                listLap[idx].tersedia--; 
                
                if (bayar == total) tampilkanPesan("BERHASIL! (Uang Pas)");
                else tampilkanPesan("BERHASIL! Kembalian", bayar-total);
                
                jumlahRes++;
            }
        } else cout << "\n[!] Lapangan penuh!" << endl;
    } else cout << "\n[!] Pilihan lapangan tidak valid!" << endl;
}

int inputAngka() {
    int angka;
    if (!(cin >> angka)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        return -1; 
    }
    return angka;
}

int main() {
    const int MAX_DATA = 100;
    User daftarUser[MAX_DATA];
    Reservasi daftarRes[MAX_DATA];
    Rating daftarRating[MAX_DATA];
    
    int jumlahUser = 0;
    int jumlahRes = 0;
    int jumlahRating = 0; 

    Lapangan listLap[3];
    listLap[0] = {"Vinyl Premium", 60000, "Rubber Vinyl", "Standar BWF", 1, 1};
    listLap[1] = {"Karpet Standar", 40000, "Sintetis", "Latihan Pro", 2, 2};
    listLap[2] = {"Semen Beton", 25000, "Semen Halus", "Ekonomis", 2, 2};

    daftarUser[jumlahUser] = {"firman", "000"};
    jumlahUser++;

    int pilihanUtama;

    while (true) {
        tampilkanHeader(jumlahRating, daftarRating);

        cout << "1. Login" << endl;
        cout << "2. Registrasi" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: "; 
        pilihanUtama = inputAngka(); 

        if (pilihanUtama == 1) {
            string u, p;
            int statusLogin = -1; 
            int batasGagal = 0;

            while (batasGagal < 3) {
                cout << "\nUsername : "; cin >> u;
                cout << "Password : "; cin >> p;

                if (u == "adminGor" && p == "sanjayaclub990") {
                    menuAdmin(listLap, daftarRating, jumlahRating);
                    statusLogin = 67;
                    break;
                } else {
                    for (int i = 0; i < jumlahUser; i++) {
                        if (daftarUser[i].username == u && daftarUser[i].password == p) {
                            statusLogin = i; break;
                        }
                    }
                }

                if (statusLogin != -1) break; 
                else {
                    batasGagal++;
                    cout << "\n[!] LOGIN GAGAL! Username atau Password salah." << endl;
                    if (batasGagal < 3) cout << "[!] Sisa percobaan: " << 3 - batasGagal << " kali." << endl;
                }
            }

            if (statusLogin != -1 && statusLogin != 67) {
                int pilUser;
                while (true) {
                    cout << "\n[ MENU USER - " << u << " ]" << endl;
                    cout << "1. Info Detail Lapangan" << endl;
                    cout << "2. Sewa Lapangan (Booking)" << endl;
                    cout << "3. Riwayat Pembayaran" << endl;
                    cout << "4. Beri Rating & Ulasan" << endl;
                    cout << "5. Logout" << endl;
                    cout << "Pilih: "; 
                    pilUser = inputAngka();

                    if (pilUser == 1) {
                        cout << "\n" << setfill('=') << setw(85) << "" << endl;
                        cout << setfill(' ') << left << setw(18) << "NAMA" << setw(13) << "HARGA/JAM" << setw(18) << "BAHAN" << setw(12) << "TERSEDIA" << "DESKRIPSI" << endl;
                        cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
                        for(int i=0; i<3; i++) {
                            cout << left << setw(18) << listLap[i].nama << "Rp" << setw(10) << listLap[i].harga << setw(18) << listLap[i].bahan << setw(12) << listLap[i].tersedia << listLap[i].deskripsi << endl;
                        }
                    } else if (pilUser == 2) {
                        prosesBooking(u, listLap, daftarRes, jumlahRes, MAX_DATA);
                    } else if (pilUser == 3) {
                        cout << "\n--- RIWAYAT TRANSAKSI ---" << endl;
                        bool adaRiwayat = false;
                        for (int i = 0; i < jumlahRes; i++) {
                            if (daftarRes[i].usernamePemilik == u) {
                                cout << "- Lapangan: " << daftarRes[i].namaLapangan << " | Total: Rp" << daftarRes[i].totalTagihan << " | Bayar: Rp" << daftarRes[i].uangBayar << " | Kembali: Rp" << daftarRes[i].kembalian << endl;
                                adaRiwayat = true;
                            }
                        }
                        if (!adaRiwayat) cout << "Belum ada transaksi.\n";
                    } else if (pilUser == 4) {
                        cout << "\n--- BERI RATING ---" << endl;
                        daftarRating[jumlahRating].namaUser = u;
                        cout << "Bintang (1-5): "; 
                        daftarRating[jumlahRating].bintang = inputAngka();
                        if(daftarRating[jumlahRating].bintang < 1 || daftarRating[jumlahRating].bintang > 5) {
                            cout << "[!] Rating batal (hanya terima angka 1 sampai 5).\n";
                            continue;
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                        cout << "Ulasan       : "; getline(cin, daftarRating[jumlahRating].ulasan);
                        jumlahRating++;
                        tampilkanPesan("Terima kasih " + u + "!");
                    } else if (pilUser == 5) {
                        break;
                    }
                }
            } 
        } else if (pilihanUtama == 2) {
            cout << "\nUsername Baru : "; cin >> daftarUser[jumlahUser].username;
            cout << "Password Baru : "; cin >> daftarUser[jumlahUser].password;
            jumlahUser++; 
            tampilkanPesan("REGISTRASI BERHASIL! Silakan Login.");
        } else if (pilihanUtama == 3) {
            cout << "\nTerima kasih telah menggunakan layanan kami!\n";
            break;
        }
    }
    return 0;
}