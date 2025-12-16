# Penjelasan Program Kereta (Bahasa Bayi)

## 1. Baris `#include`
- Kayak bilang ke C++: "Hei, aku butuh alat ini."
- `iostream` buat cetak dan baca teks.
- `iomanip` buat rapihin tabel dengan `setw`.
- `string`, `vector`, `ctime`, `cstdlib`, `limits`, `sstream` itu kotak alat lain yang dipakai fungsi di bawah.
- Kenapa nggak pakai alat lain? Karena alat ini sudah pas dan bawaan standar, jadi aman.

## 2. `using namespace std;`
- Biar nggak ngetik `std::` terus.
- Bisa aja nggak dipakai, tapi nanti setiap kata kudu panjang (`std::string`). Capek kan?

## 3. Struct `Kereta` dan `Penumpang`
- Struct itu kayak kotak berisi data.
- `Kereta` simpan kode, nama, asal, tujuan, tanggal, jam, kelas, harga, kursi.
- `Penumpang` simpan nama + NIK.
- Kenapa struct? Biar data rapi, tinggal ambil field-nya. Kalau pakai array biasa bakal bikin pusing.

## 4. Fungsi Pendukung

### `clearInputLine`
- Tugas: bersihin sisa karakter di buffer input.
- Kalau nggak ada fungsi ini, input berikutnya bisa langsung ke-skip.
- `cin.ignore` paling simpel buat masalah ini.

### `isDigitsOnly`
- Cek apakah string cuma angka.
- Loop karakter satu-satu. Cara lain? Bisa pakai regex, tapi berat buat tugas kecil ini.

### `validasiNIK`
- Panggil `isDigitsOnly` + cek panjang 10–16.
- Jadi NIK kosong atau huruf langsung ditolak.

### `generateKodeBooking`
- Bikin kode unik: prefix `KAI` + jam sekarang + angka random 3 digit.
- Kenapa pakai `strftime` + `rand`? Karena gampang dan sudah cukup unik buat demo.

### `tampilkanDaftarKereta`
- Cetak tabel kereta. `setw` dipakai biar kolom rata.
- Print manual karena datanya sedikit; nggak perlu library tabel fancy.

### `hitungTotalHarga`
- Cuma kalikan harga per orang dengan jumlah penumpang.
- Dipisah biar gampang dibaca dan kalau logika berubah tinggal ubah sini.

### `inputDataPenumpang`
- Loop minta nama + NIK, ulangi kalau kosong/invalid.
- `getline` dipakai supaya nama dengan spasi tetap kebaca.
- Kenapa bukan `cin >>`? Karena `cin >>` putus di spasi.

### `cetakTiket`
- Tampilkan tiket rapih. Cuma urut panjang string doang.
- Dipisah jadi fungsi supaya main nggak panjang banget.

## 5. Fungsi `main`

1. **`ios::sync_with_stdio(false);`**  
   - Biar input/output lebih cepat dan `cout` nggak ngaret. Cocok buat program interaktif.

2. **`srand(time(nullptr));`**  
   - Kasih bibit ke `rand` supaya kode booking benar-benar random tiap jalan.

3. **`vector<Kereta> daftarKereta = {...};`**  
   - Simpan daftar kereta awal. Kenapa `vector`? Lebih fleksibel dibanding array fix.

4. **Cetak judul + panggil `tampilkanDaftarKereta`.**  
   - Ada `cout << flush;` supaya teks langsung nongol di IDE yang nge-buffer.

5. **Input pilihan kereta.**  
   - Pakai `cin >>`. Kalau gagal, langsung bilang "input tidak valid".  
   - Cek juga angkanya harus 1–jumlah kereta.

6. **Input jumlah penumpang.**  
   - Sama kayak pilihan, tapi dicek juga > 0 dan tidak melebihi kursi tersedia.

7. **Panggil `inputDataPenumpang`.**  
   - Minta nama & NIK sesuai jumlah tadi.

8. **Hitung total harga dan tampilkan ringkasan.**

9. **Konfirmasi (Y/T).**  
   - Kalau `Y`, kurangi kursi, bikin kode booking, cetak tiket.  
   - Kalau bukan `Y`, bilang dibatalkan.

10. **Cetak ucapan terima kasih dan selesai.**

## 6. Kenapa Tidak Pakai Sintaks Lain?
- **Array biasa?** Susah tambah/hapus kereta, jadi pakai `vector`.
- **Regex untuk NIK?** Kebutuhan kecil, loop manual lebih ringan.
- **I/O canggih (GUI, JSON, dsb.)?** Program ini latihan dasar console, jadi cukup `cout`/`cin`.
- **Framework besar?** Overkill untuk proyek sekolah; bikin susah compile.

Intinya, setiap alat dipilih karena:
1. Bawaan standar (nggak perlu instal macam-macam).
2. Kode tetap pendek tapi gampang dibaca.
3. Sudah cukup buat fungsi yang diinginkan.

Semoga gampang dipahami ya!
