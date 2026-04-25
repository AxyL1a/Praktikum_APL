#ifndef GOR_LIBRARY_H
#define GOR_LIBRARY_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class KurangBayarException : public runtime_error {
public:
    KurangBayarException(const string& msg, int kurang) : runtime_error(msg), jumlahKurang(kurang) {}
    int getJumlahKurang() const { return jumlahKurang; }
private:
    int jumlahKurang;
};

class DataTidakDitemukanException : public out_of_range {
public:
    DataTidakDitemukanException(const string& msg) : out_of_range(msg) {}
};

inline void cetak_berwarna(const string& teks, int kode_warna) {
    cout << "\033[1;" << kode_warna << "m" << teks << "\033[0m";
}

inline void header_berwarna() {
    cetak_berwarna("\n======================================\n", 36);
    cetak_berwarna("       GOR BADMINTON SANJAYA          \n", 36);
    cetak_berwarna("======================================\n", 36);
}

#endif