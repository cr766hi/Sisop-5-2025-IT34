# Sisop-5-2025-IT34

## Kelompok

Nama | NRP
--- | ---
Christiano Ronaldo Silalahi | 5027241025
Naila Cahyarani Idelia      | 5027241063
Daniswara Fausta Novanto    | 5027241050


## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

1. Jawaban:
Fungsi `readString` :
   Fungsi ini digunakan untuk membaca input dari pengguna melalui keyboard.
```c
  void readString(char *buf) {
    int i = 0;
    while (1) {
        char c = interrupt(0x16, 0, 0, 0, 0);
        if (c == '\r' || c == '\n') {
            buf[i] = '\0';
            printString("\r\n");
            return;
        } else if (c == '\b' && i > 0) {
            i--;
            printString("\b \b");
        } else if (c >= 32 && c <= 126) {
            buf[i++] = c;
            interrupt(0x10, 0x0E00 | c, 0, 0, 0);
        }
    }
}
```

Fungsi `printString` :
    Fungsi ini digunakan untuk menampilkan string yang diberikan.
```c
void printString(char *str) {
    while (*str) {
        interrupt(0x10, 0x0E00 | *str, 0, 0, 0);
        str++;
    }
}
```

output :

![image](https://github.com/user-attachments/assets/e3e99075-7871-45c0-9cb4-86bc0c4054b8)


2. Jawaban:
    Fungsi ini menangani input dari pengguna dan memprosesnya.
Untuk nomor ini masih belum memiliki implementasi nya

3. Jawaban:
   Fungsi ini menangani perintah user untuk mengubah username shell.
```c
if (strcmp(cmd, "user")) {
      if (strcmp(args[0], "")) {
        strcpy(username, args[0]);
        printString("Username changed to ");
        printString(username);
        printString("\n");
      } else {
        strcpy(username, "user");
        printString("Username changed to user\n");
      }
    }
```

4. Jawaban:
Fungsi `shell`:
   Fungsi ini menangani perintah grandcompany untuk bergabung dengan Grand Company tertentu dan mengubah prompt shell.
```c
else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(args[0], "maelstrom")) {
        clearScreen();
        textColor = 0x04; // Red
        strcpy(grandcompany, "Storm");
      }
      else if (strcmp(args[0], "twinadder")) {
        clearScreen();
        textColor = 0x0E; // Yellow
        strcpy(grandcompany, "Serpent");
      }
      else if (strcmp(args[0], "immortalflames")) {
        clearScreen();
        textColor = 0x01; // Blue
        strcpy(grandcompany, "Flame");
      }
      else if (strcmp(args[0], "clear")) {
        clearScreen();
        textColor = 0x07; // White
        strcpy(grandcompany, "");
      }
      else {
        printString("Error: Invalid grand company\n");
      }
    }
```

Fungsi `clear`:
```c
else if (strcmp(cmd, "clear")) {
      clearScreen();
      textColor = 0x07;
      strcpy(grandcompany, "");
    }
```

5. Jawaban:
   Fungsi ini menangani perintah kalkulasi dari pengguna seperti add, sub, mul, dan div.
```c
else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || 
             strcmp(cmd, "mul") || strcmp(cmd, "div")) {
        int x, y, result;
        char numStr[16];
        
        atoi(args[0], &x);
        atoi(args[1], &y);
        
        if (strcmp(cmd, "add")) result = x + y;
        else if (strcmp(cmd, "sub")) result = x - y;
        else if (strcmp(cmd, "mul")) result = x * y;
        else if (strcmp(cmd, "div")) result = div(x, y);
        
        itoa(result, numStr);
        printString(numStr);
        printString("\n");
    }
```

6. Jawaban:
   Fungsi ini menangani perintah yogurt yang memberikan output acak dari tiga pilihan yang disiapkan.
```c
else if (strcmp(cmd, "yogurt")) {
      // Random responses
      int tick = getBiosTick();
      switch (mod(tick, 3)) {
        case 0: printString("yo\n"); break;
        case 1: printString("ts unami gng </3\n"); break;
        case 2: printString("sygau\n"); break;
      }
    }
```

7. Isi Makefile:
```
CC = bcc
LD = ld86
ASM = nasm

CFLAGS = -ansi -I./include -c
ASMFLAGS_BOOT = -f bin
ASMFLAGS_KERNEL = -f as86
LDFLAGS = -d

all: build

prepare:
	mkdir -p bin
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	$(ASM) $(ASMFLAGS_BOOT) src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

stdlib:
	$(CC) $(CFLAGS) src/std_lib.c -o bin/std_lib.o

shell: stdlib
	$(CC) $(CFLAGS) src/shell.c -o bin/shell.o

kernel: stdlib
	$(CC) $(CFLAGS) src/kernel.c -o bin/kernel.o
	$(ASM) $(ASMFLAGS_KERNEL) src/kernel.asm -o bin/kernel_asm.o

link: kernel shell
	$(LD) $(LDFLAGS) -o bin/kernel.bin bin/kernel.o bin/kernel_asm.o bin/std_lib.o bin/shell.o
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc

build: prepare bootloader link

clean:
	rm -f bin/*.o bin/*.bin bin/floppy.img
```
