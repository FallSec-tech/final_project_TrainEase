#include <iostream>
#include <iomanip>   // setw, setfill
#include <string>
#include <vector>    // vector
#include <ctime>     // time, localtime, strftime
#include <cstdlib>   // rand, srand
#include <limits>    // numeric_limits
#include <sstream>   // ostringstream

using namespace std;

struct Kereta {
    string kodeKereta;
    string namaKereta;
    string asal;
    string tujuan;
    string tanggal;
    string jam;
    string kelas;
    int harga;
    int kursiTersedia;
};

struct Penumpang {
    string nama;
    string nik;
};

static void clearInputLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static bool isDigitsOnly(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

static bool validasiNIK(const string& nik) {
    // Simpel: hanya angka dan panjang 10-16 digit
    if (!isDigitsOnly(nik)) return false;
    if (nik.size() < 10 || nik.size() > 16) return false;
    return true;
}

static string generateKodeBooking(const string& prefix = "KAI") {
    // prefix + YYYYMMDDHHMMSS + 3 digit random
    time_t now = time(nullptr);
    tm* lt = localtime(&now);

    char buf[32];
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", lt);

    int r = rand() % 1000;

    ostringstream oss;
    oss << prefix << buf << setw(3) << setfill('0') << r;
    return oss.str();
}

static void tampilkanDaftarKereta(const vector<Kereta>& daftar) {
    cout << "\n=== DAFTAR KERETA TERSEDIA ===\n";
    cout << left
         << setw(4)  << "No"
         << setw(8)  << "Kode"
         << setw(14) << "Nama"
         << setw(12) << "Asal"
         << setw(12) << "Tujuan"
         << setw(12) << "Tanggal"
         << setw(8)  << "Jam"
         << setw(10) << "Kelas"
         << setw(12) << "Harga"
         << setw(6)  << "Seat"
         << "\n";

    cout << string(96, '-') << "\n";

    for (size_t i = 0; i < daftar.size(); i++) {
        cout << left
             << setw(4)  << (int)(i + 1)
             << setw(8)  << daftar[i].kodeKereta
             << setw(14) << daftar[i].namaKereta
             << setw(12) << daftar[i].asal
             << setw(12) << daftar[i].tujuan
             << setw(12) << daftar[i].tanggal
             << setw(8)  << daftar[i].jam
             << setw(10) << daftar[i].kelas
             << "Rp" << setw(10) << daftar[i].harga
             << setw(6)  << daftar[i].kursiTersedia
             << "\n";
    }
}

static int hitungTotalHarga(int hargaPerOrang, int jumlahPenumpang) {
    return hargaPerOrang * jumlahPenumpang;
}

static vector<Penumpang> inputDataPenumpang(int jumlah) {
    vector<Penumpang> penumpang;
    penumpang.reserve(jumlah);

    cout << "\n=== INPUT DATA PENUMPANG ===\n";
    for (int i = 1; i <= jumlah; i++) {
        Penumpang p;

        cout << "Penumpang " << i << " - Nama: ";
        cout << flush;
        getline(cin, p.nama);
        while (p.nama.empty()) {
            cout << "Nama tidak boleh kosong. Masukkan lagi: ";
            getline(cin, p.nama);
        }

        cout << "Penumpang " << i << " - NIK: ";
        cout << flush;
        getline(cin, p.nik);
        while (!validasiNIK(p.nik)) {
            cout << "NIK tidak valid (angka, 10-16 digit). Masukkan lagi: ";
            getline(cin, p.nik);
        }

        penumpang.push_back(p);
    }

    return penumpang;
}

static void cetakTiket(const string& kodeBooking,
                       const Kereta& k,
                       const vector<Penumpang>& penumpang,
                       int totalHarga) {
    cout << "\n========================================\n";
    cout << "            === TIKET KERETA ===\n";
    cout << "========================================\n";
    cout << "Kode Booking : " << kodeBooking << "\n";
    cout << "Kereta       : " << k.namaKereta << " (" << k.kodeKereta << ")\n";
    cout << "Rute         : " << k.asal << " -> " << k.tujuan << "\n";
    cout << "Tanggal      : " << k.tanggal << "\n";
    cout << "Jam          : " << k.jam << "\n";
    cout << "Kelas        : " << k.kelas << "\n";
    cout << "Jumlah       : " << penumpang.size() << " penumpang\n";
    cout << "----------------------------------------\n";
    cout << "Daftar Penumpang:\n";
    for (size_t i = 0; i < penumpang.size(); i++) {
        cout << "  " << (int)(i + 1) << ". " << penumpang[i].nama
             << " | NIK: " << penumpang[i].nik << "\n";
    }
    cout << "----------------------------------------\n";
    cout << "Total Harga  : Rp" << totalHarga << "\n";
    cout << "Status       : LUNAS\n";
    cout << "========================================\n\n";
}

int main() {
    ios::sync_with_stdio(false);

    srand((unsigned)time(nullptr));

    vector<Kereta> daftarKereta = {
        {"KA001", "ArgoBromo", "Jakarta", "Surabaya", "20-12-2025", "07:00", "Eksekutif", 350000, 30},
        {"KA002", "Taksaka",   "Jakarta", "Yogyakarta", "20-12-2025", "08:00", "Eksekutif", 300000, 25},
        {"KA003", "Lodaya",    "Bandung", "Solo",      "21-12-2025", "09:30", "Bisnis",    200000, 20},
        {"KA004", "Matarmaja", "Malang",  "Jakarta",   "22-12-2025", "16:00", "Ekonomi",   150000, 40}
    };

    cout << "=== SISTEM PEMESANAN TIKET KERETA (C++) ===\n";

    tampilkanDaftarKereta(daftarKereta);
    cout << flush;

    int pilihanKereta = 0;
    cout << "\nPilih kereta (No): ";
    cout << flush;
    if (!(cin >> pilihanKereta)) {
        cout << "Input tidak valid.\n";
        return 0;
    }
    clearInputLine();

    if (pilihanKereta < 1 || pilihanKereta > (int)daftarKereta.size()) {
        cout << "Pilihan kereta tidak valid.\n";
        return 0;
    }

    Kereta& keretaDipilih = daftarKereta[pilihanKereta - 1];

    int jumlahPenumpang = 0;
    cout << "Jumlah penumpang: ";
    cout << flush;
    if (!(cin >> jumlahPenumpang)) {
        cout << "Input jumlah penumpang tidak valid.\n";
        return 0;
    }
    clearInputLine();

    if (jumlahPenumpang <= 0) {
        cout << "Jumlah penumpang harus lebih dari 0.\n";
        return 0;
    }

    if (jumlahPenumpang > keretaDipilih.kursiTersedia) {
        cout << "Kursi tidak mencukupi. Tersedia: " << keretaDipilih.kursiTersedia << "\n";
        return 0;
    }

    vector<Penumpang> penumpang = inputDataPenumpang(jumlahPenumpang);

    int totalHarga = hitungTotalHarga(keretaDipilih.harga, jumlahPenumpang);

    cout << "\n=== RINGKASAN PEMESANAN ===\n";
    cout << "Kereta   : " << keretaDipilih.namaKereta << " (" << keretaDipilih.kodeKereta << ")\n";
    cout << "Rute     : " << keretaDipilih.asal << " -> " << keretaDipilih.tujuan << "\n";
    cout << "Tanggal  : " << keretaDipilih.tanggal << "\n";
    cout << "Jam      : " << keretaDipilih.jam << "\n";
    cout << "Kelas    : " << keretaDipilih.kelas << "\n";
    cout << "Jumlah   : " << jumlahPenumpang << "\n";
    cout << "Total    : Rp" << totalHarga << "\n";

    char konfirmasi;
    cout << "\nKonfirmasi pemesanan? (Y/T): ";
    cout << flush;
    cin >> konfirmasi;

    if (konfirmasi == 'Y' || konfirmasi == 'y') {
        keretaDipilih.kursiTersedia -= jumlahPenumpang;

        string kodeBooking = generateKodeBooking("KAI");
        cout << "\nPembayaran berhasil!\n";
        cetakTiket(kodeBooking, keretaDipilih, penumpang, totalHarga);

        cout << "Sisa kursi untuk kereta ini: " << keretaDipilih.kursiTersedia << "\n";
    } else {
        cout << "\nPemesanan dibatalkan.\n";
    }

    cout << "\nTerima kasih sudah menggunakan program ini.\n";
    return 0;
}
