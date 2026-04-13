#ifndef GOR_STRUK_H
#define GOR_STRUK_H
// User: firman pw: 000
// Admin: adminGor pw: sanjayaclub990
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_DATA = 100;

struct Waktu { string tanggal; string jam; int durasi; };
struct Lapangan { string nama; int harga; string bahan; string deskripsi; int kapasitasAwal; int tersedia; };
struct Rating { string namaUser; int bintang; string ulasan; };
struct Reservasi { string namaPemesan; string namaLapangan; Waktu jadwal; int totalTagihan; int uangBayar; int kembalian; string usernamePemilik; };
struct User { string username; string password; };

void tampilkan_pesan(string pesan);
void tampilkan_pesan(string pesan, int nilai);
void bersihkan_masukan();
int masukan_angka();

float hitung_total_bintang_rekursif(Rating* daftar_rating, int jumlah);
void tampilkan_header(Rating* daftar_rating, int jumlah_rating);
void tampilkan_detail_lapangan(Lapangan* daftar_lapangan, int jumlah_lapangan);
void tampilkan_daftar_lapangan_admin(Lapangan* daftar_lapangan, int jumlah_lapangan);

void proses_registrasi(User* daftar_pengguna, int& jumlah_pengguna);
bool proses_masuk(User* daftar_pengguna, int jumlah_pengguna, string& nama_pengguna_keluar);

void tambah_lapangan(Lapangan* daftar_lapangan, int& jumlah_lapangan);
void hapus_lapangan(Lapangan* daftar_lapangan, int& jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi);
void edit_lapangan(Lapangan* daftar_lapangan, int jumlah_lapangan);

void bubble_sort_nama_lapangan(Lapangan* daftar_lapangan, int jumlah_lapangan);
int partition_tagihan_reservasi(Reservasi* daftar, int low, int high);
void quick_sort_tagihan_reservasi(Reservasi* daftar, int low, int high);
void insertion_sort_bintang_rating(Rating* daftar_rating, int jumlah_rating);

void bubble_sort_nama_lapangan_user(Lapangan* daftar_lapangan, int jumlah_lapangan);
void insertion_sort_bintang_rating_user(Rating* daftar_rating, int jumlah_rating);
void quick_sort_tagihan_reservasi_user(Reservasi* daftar, int low, int high, string username);

void menu_admin(Lapangan* daftar_lapangan, int& jumlah_lapangan, Rating* daftar_rating, int& jumlah_rating, Reservasi* daftar_reservasi, int& jumlah_reservasi);
void menu_pengguna(string nama_pengguna, Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, Rating* daftar_rating, int& jumlah_reservasi, int& jumlah_rating);

void proses_pesan(string nama_pengguna, Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi);
void tampilkan_riwayat(string nama_pengguna, Reservasi* daftar_reservasi, int jumlah_reservasi);
void tambah_rating(string nama_pengguna, Rating* daftar_rating, int& jumlah_rating);

void hapus_rating_pengguna(string nama_pengguna, Rating* daftar_rating, int& jumlah_rating);
void hapus_reservasi(Lapangan* daftar_lapangan, int jumlah_lapangan, Reservasi* daftar_reservasi, int& jumlah_reservasi, int indeks);
void hapus_rating(Rating* daftar_rating, int& jumlah_rating, int indeks);

#endif