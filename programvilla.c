#include <stdio.h>   //header standar input output dalam bahasa C
#include <stdlib.h>  //header standar input output dalam bahasa C
#include <string.h>  //header yang berisi fungsi-fungsi yang digunakan untuk pengoprasian string dan array
#include <time.h>    //header yang digunakan untuk menampilkan format tanggal dan waktu
#define JUM_BLOK 1	//berfungsi untuk mendefine nilai jum_lok satu saat pengoprasian file

// Note : Pada beberapa compiler kode system ("clear") dapat dituliskan system ("cls");

// Dekalarasi variable global yang digunakan pada program pemesanan villa ini:
int passwordbenar;        //variabel passwordbenar => berfungsi untuk menyimpan password yang benar sesuai dengan input user ke dalam bentuk data integer
char passP[20];           //variabel passP         => berfungsi untuk menyimpan password pegawai sesuai dengan input user ke dalam bentuk data char dengan jumlah maksimal 20 karakter
char passwordP[20];       //variabel passwordP     => berfungsi untuk menyimpan password pegawai yang diubah dari passP menjadi passwordP dengan strcpy ke dalam bentuk data char dengan jumlah maksimal 20 karakter
float deposito = 500000 ; //variabel deposito      => berfungsi untuk menyimpan deposito ke dalam variabel bertipe data float dengan nilai deposito tetap Rp. 500.000,-
float biaya_ADM = 2000 ;  //variabel biaya_ADM     => berfungsi untuk menyimpan biaya_ADM ke dalam variabel bertipe data float dengan nilai biaya_ADM tetap Rp. 2.000,-
char jawab ;              //variabel jawab         => berfungsi untuk menyimpan jawab sesuai dengan input user ke dalam variabel bertipe char 
int hari1 ;               //variabel hari1         => berfungsi untuk menyimpan hari1 yaitu hari check in ke dalam variabel bertipe integer
int hari2 = 1;            //variabel hari1         => berfungsi untuk menyimpan hari2 yaitu hari check out ke dalam variabel bertipe integer, dimana hari checkout ditentukkan berdasarkan hari checkin + 1 hari
time_t waktuserver;       //variabel waktuserver   => berfungsi untuk mengambil waktu dari sistem.
int id_pemesan;

// Struct User untuk menyimpan member nama, username, password, email
typedef struct {
    char nama[50];      //untuk menyimpan nama dengan maksimal 50 karakter pada saat registrasi pengguna
    char username[12];  //untuk menyimpan username dengan maksimal 12 karakter pada saat registrasi serta login pengguna
    char password[10];  //untuk menyimpan password dengan maksimal 10 karakter pada saat registrasi serta login pengguna
    char email[50];     //untuk menyimpan email dengan maksimal 50 karakter pada saat registrasi pengguna
}User;
User u; //Mendeklarasikan variabel u pada struct User


// Struct untuk menyimpan Pesanan Villa
typedef struct {
	int nomor_villa;        //untuk menyimpan nomor_villa yang dipesan ke dalam variabel integer saat input pemesanan villa
	char nama_pemesan[50];  //untuk menyimpan nama_pemesan ke dalam variabel char dengan maksimal 50 karakter saat input pemesanan villa
	char noHP [15];         //untuk menyimpan noHP pemesan ke dalam variabel char dengan maksimal 15 karakter saat input pemesanan villa
	char email [50];        //untuk menyimpan email pemesan ke dalam variabel char dengan maksimal 50 karakter saat input pemesanan villa
	int orang ;             //untuk menyimpan banyaknya orang yang ada didalam suatu villa, disimpan ke variabel bertipe integer, input saat pemesanan villa
	int tglCI ;             //berfungsi untuk menyimpan tanggal check in saat input pemesanan villa ke dalam variabel bertipe integer
	int blnCI ;             //berfungsi untuk menyimpan bulan check in saat input pemesanan villa ke dalam variabel bertipe integer
	int thnCI ;             //berfungsi untuk menyimpan tahun check in saat input pemesanan villa ke dalam variabel bertipe integer
	int tglCO ;             //berfungsi untuk menyimpan tanggal check out saat input pemesanan villa ke dalam variabel bertipe integer
	int blnCO ;             //berfungsi untuk menyimpan bulan check out saat input pemesanan villa ke dalam variabel bertipe integer
	int thnCO ;             //berfungsi untuk menyimpan tahun check out saat input pemesanan villa ke dalam variabel bertipe integer
	float totalPembayaran ; //berfungsi untuk menyimpan total pembayaran villa ke dalam variabel bertipe float
	float DPpemesan ;       //berfungsi untuk menyimpan total DP Pemesan ke dalam variabel bertipe float
	float sisaPembayaran ;  //berfungsi untuk menyimpan sisa pembayaran villa ke dalam variabel bertipe float
	int id_pesan ;	        //berfungsi untuk menyimpan id_villa yang diinput user ke dalam variabel bertipe integer
}pesan_villa;
pesan_villa pesanvl; //Mendeklarasikan variabel pesanvl pada struct pesan_villa

FILE *dtvilla;
//struct untuk menyimpan data villa
typedef struct{
	int kode_villa;
	char nama_villa[15];
	char tipe_fasilitasLain[10];
	char tipe_kamar [25];
	int harga_lunas;
	int DP_villa;
	int kapasitas;
	char check_in[10];
	char check_out[10];
	char lama_inap [25];
}data_villa;
data_villa villa;

FILE*dtpenilaian;
//struct untuk menyimpan penilaian pengunjung villa
typedef struct {
	int idPemesan;
	char nama_penilai[12];
	int rating ;
	int tglPenilaian;
	int blnPenilaian;
	int thnPenilaian;
	char komentar[200];
}data_ratingKomentar;
data_ratingKomentar penilaian;

//Deklarasi fungsi-fungsi yang digunakan pada program pemesanan villa :
void header ();                                   /*Merupakan fungsi yang digunakan untuk menampilkan header program yang ditunjukkan pertama kali saat program dijalankan*/
void menu_masuk();                                /*Merupakan fungsi menu masuk untuk user pegawai maupun user pengunjung yang berisi 4 opsi,Masuk Sebagai Admin,Masuk Sebagai Pengunjung,Registrasi Pengunjung, dan EXIT*/
void masuk_admin();                               /*Merupakan fungsi untuk masuk admin (login admin) dengan memasukkan password admin atau pegawai villa anyelir*/
void daftar();                                    /*Merupakan fungsi untuk daftar atau registrasi bagi pengunjung yang belum membuat akun*/
void error_alert();                               /*Merupakan fungsi untuk pesan error*/
void masuk_pengunjung ();                         /*Merupakan fungsi untuk masuk pengunjung (login) yang berisi input username dan password*/
void ambil_password();                            /*Merupakan fungsi untuk mengambil password yang diinput dan dicek pada file passwordAdmin.txt*/
void selesai();                                   /*Merupakan fungsi untuk menampilkan kata-kata selesai yang digunakan bila berhasil login*/
void menuadm();                                   /*Merupakan fungsi untuk menu admin yang berisi 4 opsi yaitu Lihat List Villa, Pesan Villa, Lihat Data Pesanan, Hapus Pesanan, dan Exit*/
void waktu();                                     /*Merupakan fungsi yang digunakan untuk menampilkan waktu pada sistem tempat user mengakses*/
void menu_pengunjung();                           /*Merupakan fungsi untuk menu pengunjung ketika berhasil login atau masuk dengan menghadirkan 4 opsi yaitu untuk melihat lokasi villa, list villa, riwayat pesan villa, dan Exit*/
void list_villa ();                               /*Merupakan fungsi untuk menampilkan list villa anyelir */
void lokasi_villa ();                             /*Merupakan fungsi untuk menampilkan lokasi dari setiap villa anyelir*/
void list_villa_pengunjung ();                    /*Merupakan fungsi untuk menampilkan list villa pengunjung dengan memanggil fungsi yang telah dibuat sebelumnya yaitu list_villa*/
void pesan_villa_anyelir ();                      /*Merupakan fungsi yang digunakan untuk memesan villa anyelir (pemesanan dilakukan oleh admin atau pegawai anyelir)*/
void lihat_data_pesanan ();                       /*Merupakan fungsi untuk melihat data pesanan villa anyelir jika telah memesan dengan admin atau pegawai*/
void hapus_pesanan ();                            /*Merupakan fungsi bagian dari menu admin untuk menghapus data pesanan villa anyelir yang dilakukan oleh pegawai atau adminn*/
void pemesanan_villa();                           /*Merupakan fungsi yang berhubungan dengan pemesanan villa yang memuat harga dari setiap villa anyelir*/
void hapus ();                                    /*Merupakan fungsi yang digunakan untuk menghapus data pemesanan (lanjutan dari fungsi hapus_pesanan)*/
void hapusdtpesan (pesan_villa pesanvl, int r);   /*Merupakan fungsi lanjutan dari hapus yang merujuk langsung pada database datapesan.txt sehingga apabila menghapus data maka data pada database juga ikut terhapus*/
void list_data_pemesan ();                        /*Merupakan fungsi yang berisi list data pemesanan villa anyelir*/
void detPemesanan ();                             /*Merupakan fungsi berupa output keseluruhan saat pemesanan villa anyelir */
void kalenderuntukCO ();                          /*Merupakan fungsi yang digunakan untuk perhitungan kalender pada saat check out */
void hari ();                                     /*Merupakan fungsi yang digunakan untuk menampilkan nama-nama hari*/
void tampilan_pemesanan ();                       /*Merupakan fungsi yang digunakan untuk menampilkan pesanan namun secara singkat berisi id pemesan, id villa dan tanggal check in yang bisa dilihat oleh pengunjung villa*/
void cara_pesan_villa ();                         /*Merupakan fungsi yang digunakan untuk menampilkan tata cara pemesanan villa yang dapat dibaca dan diakses oleh pengunjung villa*/
int Februari (int thn);                           /*Merupakan fungsi untuk menyeleksi bulan februari, karena bulan februari ada yang jumlahnya 28 atau 29*/
int BknFeb (int thn, int bln);                    /*Merupakan fungsi untuk menyeleksi selain bulan Februari*/
int checkNomor(pesan_villa pesanvl,int id);       /*Merupakan fungsi yang digunakan untuk mengecek nomor atau id villa apakah tersedia, yang berfungsi saat menghapus villa.*/
void inputVillaAnyelir ();                        /*Merupakan fungsi yang digunakan untuk menginput data villa anyelir baru*/
void hapusdtvilla (data_villa villa, int r);      /*Merupakan fungsi yang digunakan untuk menghapus data villa*/
int checkKode(data_villa villa,int id);           /*Merupakan fungsi untuk mengecek kode / id villa saat penghapusan villa*/
void hapusvilla ();                               /*Merupakan fungsi untuk menghapus data villa (lanjutan dari fungsi hapus_villa)*/
void hapus_villa();                               /*Merupakan fungsi untuk menghapus data villa yang terdapat pada menu pegawai villa anyelir*/
void tipeFasilitasdanKamar ();                    /*Merupakan fungsi untuk menampilkan tipe fasilitas dan kamar pada villa anyelir*/
void menuRatingPengunjung ();                     /*Merupakan fungsi untuk menampilkan rating pengunjung villa anyelir*/
void ratingPengunjung ();                         /*Merupakan fungsi lanjutan dari menuRatingPengunjung yang digunakan untuk menginput nama, rating, dan komentar*/
void tampilanPenilaian ();						  /*Merupakan fungsi untuk menampilakan Penilaian dari pengunjung yang sudah pernah memakai villa anyelir*/


// assign namaFile (nF) agar menyimpan string "logRecord.txt"
char namaFile[] = "logRecord.txt";

// fungsi main () adalah kepala dari program ini, dimana program akan di eksekusi oleh fungsi main ini.
int main (){
   system ("color F5"); //pewarnaan latar program saat dijalankan F = Light White , 5 = Purple 
   header (); //pemanggilan fungsi header
   menu_masuk (); //pemanggilan fungsi menu masuk
}

//=======================================================================//
//*****           Fungsi Untuk Menampilkan Header Program           *****//
//=======================================================================//
// Nama Fungsi    : header                                               //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Menampilkan nama dari penyusun program               //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void header (){
  system ("cls");
	printf  ("\t\t\t\t\t=========================================================\n");
	printf  ("\t\t\t\t\t||                                                     ||\n");	
	printf  ("\t\t\t\t\t||                TUGAS BESAR PEMROGRAMAN              ||\n");
	printf  ("\t\t\t\t\t||            Program Pemesanan Villa Anyelir          ||\n");
	printf  ("\t\t\t\t\t||                                                     ||\n");
	printf  ("\t\t\t\t\t=========================================================\n");
	printf  ("\t\t\t\t\t||          Program disusun dan dibuat oleh :          ||\n");
	printf  ("\t\t\t\t\t||                                                     ||\n");
	printf  ("\t\t\t\t\t||  1. Gusti Ayu Wahyu Whurapsari       (2105551042)   ||\n");
	printf  ("\t\t\t\t\t||  2. Putu Eternalie Prajnani Welaga   (2105551046)   ||\n");
	printf  ("\t\t\t\t\t||                                                     ||\n");
	printf  ("\t\t\t\t\t||           Program Studi Teknologi Informasi         ||\n");
	printf  ("\t\t\t\t\t||                   Fakultas Teknik                   ||\n");
	printf  ("\t\t\t\t\t||                 Universitas Udayana                 ||\n");
	printf  ("\t\t\t\t\t||                       2021                          ||\n");
	printf  ("\t\t\t\t\t=========================================================\n");
	printf  ("\t\t\t\t\t              Tekan ENTER  untuk melanjutkan....\n");
    printf  ("\t\t\t\t\t=========================================================\n");
	getchar (); //digunakan untuk membaca data yang bertipe karakter yang harus diakhiri oleh enter
  system ("cls");
}

//=======================================================================//
//*****         Fungsi Untuk Menampilkan Menu Masuk Program         *****//
//=======================================================================//
// Nama Fungsi    : menu_masuk                                           //
// Input Argumen  : int pilihan                                          //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan menu masuk    //
//                  ke program dengan menginputkan angka sesuai dengan   //
//                  pilihan dari pengguna program                        //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void menu_masuk (){
	system ("cls");
	// Variabel pilihan yang digunakan untuk menyimpan pilihan pengguna antara Masuk dengan Registrasi
    int pilihan;

    // Instruksi yang diberikan kepada pengguna
    instruksi:
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|                PILIHAN MENU MASUK              |\n");
    printf ("\t\t\t\t\t|                  VILLA ANYELIR                 |\n");
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|   No  |    Menu Masuk                          |\n");
    printf ("\t\t\t\t\t|-------|----------------------------------------|\n");
    printf ("\t\t\t\t\t|   1   |    Masuk Sebagai Admin                 |\n");
    printf ("\t\t\t\t\t|   2   |    Masuk Sebagai Pengunjung            |\n");
    printf ("\t\t\t\t\t|   3   |    Registrasi Pengunjung               |\n");
    printf ("\t\t\t\t\t|   4   |    Exit                                |\n");
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t| Masukkan pilihan Anda => ");
    scanf  ("%d", &pilihan);
    printf ("\t\t\t\t\t|================================================|\n");
    system ("cls");
    switch (pilihan){
    case 1:
        // Jika pengguna menginput angka 1 maka dipanggil fungsi masuk
        masuk_admin();
        break;
    case 2 :
    	masuk_pengunjung ();
    break ;
    case 3:
        // Jika pengguna menginput angka 2 maka dipanggil fungsi registrasi
        daftar();
        break;
    case 4:
    	printf ("\t\t\t\t\t  TERIMAKASIH TELAH MENGGUNAKAN PROGRAM INI ....  \n");
        exit(1);
        break;
    default:
        error_alert();
        // Kembali ke label instruksi jika terjadi kesalahan dalam menginput pilihan
        goto instruksi;
        break;
    }
}
//=======================================================================//
//*****                  Fungsi Untuk Masuk Pegawai                 *****//
//=======================================================================//
// Nama Fungsi    : masuk_admin                                          //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi khusus bagi pegawai atau admin  //
//                  untuk masuk ke dalam program, dengan menginputkan    //
//                  password yang sudah terdapat pada file databases     //
//                  'passwordAdmin.txt'                                  //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void masuk_admin (){
	system("cls");
	ambil_password ();
	printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|                   MENU MASUK                   |\n");
    printf ("\t\t\t\t\t|                 PEGAWAI ANYELIR                |\n");
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t| Masukkan password : ");
	scanf("%s", &passP);
	passwordbenar=strcmp(passP,passwordP);
	if(passwordbenar !=0){
		printf("\t\t\t\t\t Password yang anda masukan salah!");
		printf("\t\t\t\t\t Kembali ke menu utama\n");
		getch();
		system("cls");
		main();
	}
	else{
		selesai(); //void selesai dapat kalian ubah ke void menu
	}
    
}

//=======================================================================//
//*****           Fungsi Untuk Mengambil Password Pegawai           *****//
//=======================================================================//
// Nama Fungsi    : ambil_password                                       //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi untuk mengambil password pegawai dari database//
//                  passwordAdmin.txt                                    //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void ambil_password(){
	FILE *file; // Membuat pointer file untuk menunjuk pada file "passwordAdmin.txt"
	file=fopen("passwordAdmin.txt", "r"); // Membuka file dengan mode "r"
	fscanf(file, "%s", passwordP);
	fclose(file); //menutup file "passwordAdmin"
}

//=======================================================================//
//*****                    Fungsi Untuk Daftar Akun                 *****//
//=======================================================================//
// Nama Fungsi    : daftar                                               //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan bahwa login   //
//                  yang dilakukan oleh pegawai sudah berhasil atau      //
//                  sukses                                               //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//   
void selesai(){
	printf("\t\t\t\t\t\t\tLOGIN SUKSES!\n");
	getch(); fflush(stdin); //berfungsi untuk menghilangkan nilai buffer pada sistem
	menuadm();
}

//=======================================================================//
//*****                 Fungsi Untuk Login Pengunjung              ******//
//=======================================================================//
// Nama Fungsi    : masuk_pengunjung                                     //
// Input Argumen  : char username[12], char password[10], dan int pilihan//
// Output Argumen : -                                                    //
// Deskripsi      : Menginput username dan passowrd saat masuk pengunjung//
//                  yang sesuai dengan rekaman pada logrecord.txt        //
//                  akan berlanjut pada menu pengunjung                  //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void masuk_pengunjung (){
	/*  Variabel username[12] digunakan untuk menyimpan input username
        yang dilakukan oleh pengguna. Inputan tersebut akan divalidasi
        dengan username yang sudah terdaftar pada file logRecord.txt   */
    char username[12];

    /*  Variabel password[10] digunakan untuk menyimpan input password
        yang dilakukan oleh pengguna. Inputan tersebut akan divalidasi
        dengan password yang sudah terdaftar pada file logRecord.txt   */
    char password[10];

    // Variabel pilihan untuk pilihan user apakah ingin mendaftar atau keluar
    int pilihan;

    // Membuat pointer record untuk menunjuk pada file "logRecord.txt"
    FILE *record;
    // Membuka file dengan mode "r"
    record = fopen (namaFile, "r");
    if (record == NULL){
        fputs ("Error, Tidak terdapat File untuk penyimpanan akun\n", stderr);
        daftar();
    }

    // Memperlihatkan tanggal login
    waktu();
    // Instruksi untuk LOGIN
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|                          LOGIN                          |\n");
    printf ("\t\t\t\t\t|                    PENGUNJUNG ANYELIR                   |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t| Username: "); //input username
    scanf  ("%s", username);
    printf ("\t\t\t\t\t| Password: "); //input password
    scanf  ("%s", password);
    printf ("\t\t\t\t\t|=========================================================|\n");
    system ("cls");
    // Membaca file "logRecord.txt"
    while(fread(&u,sizeof(u),1,record)){
        /*  Mengkomparasi username serta password yang diinput pengguna kedalam fungsi
            masuk() dengan username serta password yang sudah terdaftar */
        if(strcmp(username, u.username)==0 && strcmp(password, u.password)==0){
            menu_pengunjung();
        }
        //  Jika akun tidak terdaftar maka akan diberikan pilihan untuk mendaftar atau keluar dari program
        else {
            printf ("\t\t\t\t\t|=========================================================|\n");
            printf ("\t\t\t\t\t|                   Akun tidak terdaftar!                 |\n");
            printf ("\t\t\t\t\t|=========================================================|\n");

            instruksi:
            printf ("\t\t\t\t\t|=========================================================|\n");
            printf ("\t\t\t\t\t| Ketik 1 untuk daftar");
            printf ("\n\t\t\t\t\t| Ketik 2 untuk masuk ulang");
            printf ("\n\t\t\t\t\t| Ketik 3 untuk EXIT\n");
            printf ("\t\t\t\t\t|=========================================================|\n");
            printf ("\n\t\t\t\t\t| Pilihan: ");
            scanf ("%d", &pilihan);
            system ("cls");
            // Jika pengguna mengetik nomor 1 maka akan dialihkan kepada fungsi daftar
            if (pilihan == 1){
                daftar();
            // Jika pengguna mengetik nomor 2 maka akan dialihkan kepada fungsi masuk_pengunjung
            } else if (pilihan==2) {
                masuk_pengunjung();
        	// Jika pengguna mengetik nomor 3, karena exit maka akan dialihkan kepada menu_masuk
            } else if (pilihan ==3){
                menu_masuk ();
            // Jika pengguna salah menginput nomor yang tidak sesuai dengan pilihan yang ada maka pengguna akan dialihkan kembali untuk memasukkan pilihan yang sesuai
            } else {
                printf ("\t\t\t\t\t HARAP MASUKKAN PILIHAN YANG SESUAI [1-3]\n");
                goto instruksi;
            }
        }
    }
    fclose(record); //menutup file "logRecord.txt"
    return;
}

//=======================================================================//
//*****                    Fungsi Untuk Daftar Akun                 *****//
//=======================================================================//
// Nama Fungsi    : daftar                                               //
// Input Argumen  : struct User u                                        //
// Output Argumen : u.nama                                               //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan program daftar//
//                  atau registrasi akun, disetai dengan menginputkan    //
//                  username dan password, yang nantinya akan tersimpan  //
//                  pada file "logRecord.txt"                            //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//      
void daftar (){
	// Membuat pointer regis untuk file "logRecord.txt"
    FILE *regis;

    // Membuka file "logRecord.txt" dengan mode "w"
    regis = fopen(namaFile,"w");

    // Melakukan Pengecekan apakah pointer regis menunjuk kepada file yang dituju ("logRecord.txt")
    if (regis == NULL)
    {
        fputs("ERROR, Tidak ada File!", stderr);
        exit(1);
    }

    // Instruksi untuk menginput nama
    printf("\n\t\t\t\t\t Silahkan registrasi akun anda!\n\n");
    getchar();
    printf("\t\t\t\t\t Nama Lengkap: ");
    gets(u.nama);
    printf("\t\t\t\t\t Email anda: ");
    scanf ("%s", u.email);
    printf("\n\t\t\t\t\t Hallo %s!\n", u.nama);
    printf ("\t\t\t\t\t Silahkan membuat username (max 12 karakter) serta membuat password (max 10 karakter)\n");

    // Instruksi untuk menginput username serta password
    printf("\n\t\t\t\t\t Enter Username:");
    scanf ("%s", u.username);
    printf("\n\t\t\t\t\t Enter Password:");
    scanf ("%s", u.password);

    // Menuliskan nama yang diinput oleh pengguna kedalam file "logRecord.txt"
    fwrite(&u,sizeof(u),1,regis);
    fclose(regis);
    printf("\n\t\t\t\t\t Registrasi Selesai!");
    printf ("\n\t\t\t\t\t Akun anda terdaftar, silahkan mencoba !");
    getchar();

    // Membersikan layar terminal
    system ("cls");
    // Memanggil fungsi masuk()
    menu_pengunjung();
}


//=======================================================================//
//***********     Fungsi Untuk Menampilkan Waktu Sistem     *************//
//=======================================================================//
// Nama Fungsi    : waktu                                                //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk mengambil dan menampilkan //
//                 Waktu sistem pada saat user mengakses program.        //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 14-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void waktu(){
    time( & waktuserver);
    struct tm * waktu = localtime( & waktuserver);
    printf ("\t\t\t\t\t|=====================Tanggal: %i/%i/%i===================|\n", waktu -> tm_mday, waktu -> tm_mon + 1, waktu -> tm_year + 1900);                      
}

//=======================================================================//
//*****                      Fungsi Error Program                   *****//
//=======================================================================//
// Nama Fungsi    : error                                                //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan program error // 
//                  atau pilihan yang diinput baik oleh pegawai atau     //
//                  pengguna tidak terdapat pada pilihan                 //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void error_alert (){
	printf   ("\t\t\t\t\t=========================================================  \n");
    printf   ("\t\t\t\t\t||         Pilihan yang Anda masukan Salah!!!          || \n");
    printf   ("\t\t\t\t\t||      Silahkan Memilih Pilihan yang Sudah ada        || \n");
    printf   ("\t\t\t\t\t=========================================================  \n");
}

//=======================================================================//
//*****             Fungsi Untuk Menampilkan Menu Admin             *****//
//=======================================================================//
// Nama Fungsi    : menuadm                                              //
// Input Argumen  : char a, int kategori                                 //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan kategori menu //
//                  khusus untuk pegawai atau admin, yaitu 1 untuk lihat //
//                  list villa, 2 untuk pesan villa, 3 untuk lihat data  //
//                  pesanan, 4 untuk hapus pesanan dan 5 untuk exit atau //
//                  keluar                                               //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void menuadm (){
	char a ;
	int kategori ;
	int opsi;
	system ("cls");
	ulangi :
	printf ("\n\n");
	printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|                        KATEGORI MENU                    |\n");
    printf ("\t\t\t\t\t|                    PEGAWAI VILLA ANYELIR                |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|   No  |    Pilihan Kategori                             |\n");
    printf ("\t\t\t\t\t|-------|-------------------------------------------------|\n");
    printf ("\t\t\t\t\t|   1   |    Input Data Villa                             |\n");
    printf ("\t\t\t\t\t|   2   |    Lihat List Villa                             |\n");
    printf ("\t\t\t\t\t|   3   |    Lihat List Fasilitas dan Tipe Kamar          |\n");
    printf ("\t\t\t\t\t|   4   |    Hapus Data Villa                             |\n");
    printf ("\t\t\t\t\t|   5   |    Pesan Villa                                  |\n");
    printf ("\t\t\t\t\t|   6   |    Lihat Data Pesanan                           |\n");
    printf ("\t\t\t\t\t|   7   |    Hapus Pesanan                                |\n"); 
    printf ("\t\t\t\t\t|   8   |    Exit                                         |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t| Masukkan No Pilihan Anda : ");
	scanf  ("%d",&kategori);
    system ("cls");
    switch (kategori){ 
    	case 1 :
    		inputVillaAnyelir ();
    	break ;
    	
    	//case 2 dari menu switch (kategori) ini mengeksekusi perintah jika pegawai memilih lihat list villa pada kategori menu pegawai villa anyelir. 
		//Pada case ini memanggil fungsi list_villa untuk menampilkan detail villa jika pegawai ingin memesan juga bisa langsung dari sini dengan klik Y atau y pada 
    	case 2 :
    	list_villa ();
    		printf ("|                                                         Proses Pemesanan [Y/T]? : ");
    		scanf  ("%s", &a);
    		if (a=='Y'|| a=='y')
    			pesan_villa_anyelir();
    		else
    			menuadm ();
    	break ;
    	
    	case 3 :
    		tipeFasilitasdanKamar ();
			opsi1 :
			printf ("\t\t\t\t\t  Kembali Tekan 1 : ");
    		scanf ("%d", &opsi);
    		if (opsi==1){ //jika menekan 1 maka akan mengarah ke menu_pengunjung
    		menuadm ();
			}
			else //jika menekan selain 1 akan diminta ulang menekan
			printf ("\t\t\t\t\t  Silahkan ketik ulang 1 \n");
			goto opsi1 ; //kembali pada opsi
    	break ;
    	
    	case 4 :
    		hapus_villa ();
    	break ;
    	
    	//case 5 dari menu switch (kategori) ini mengeksekusi perintah jika pegawai miilih pesan villa pada kategori menu pegawai villa anyelir, dalam case 2 ini terdapat pemanggilan fungsi pesan_villa_anyelir
    	case 5 :
    		pesan_villa_anyelir ();
    	break ;
    	
    	//case 6 dari menu switch (kategori) ini mengeksekusi perintah jika pegawai miilih lihat data pesanan pada kategori menu pegawai villa anyelir, dalam case 3 ini terdapat pemanggilan fungsi lihat_data_pesanan
    	case 6 :
    		lihat_data_pesanan ();
    	break ;
    
    	//case 7 dari menu switch (kategori) ini mengeksekusi perintah jika pegawai miilih hapus pesanan pada kategori menu pegawai villa anyelir, dalam case 4 ini terdapat pemanggilan fungsi hapus_pesanan
    	case 7 :
    		hapus_pesanan ();
    	break ;
    	
    	//case 8 dari menu switch (kategori) ini mengeksekusi perintah jika pegawai miilih EXIT pada kategori menu pegawai villa anyelir, dalam case 4 ini user akan diarahkan langsung keluar yaitu pada menu masuk dengan memanggil fungsi menu_masuk
    	case 8 :
    		menu_masuk ();
    	break ;
    	
    	//Jika user menginput pilihan yang salah, atau menginput nilai yang tidak ada pada tampilan menu maka pegawao villa anyelir maka akan mengesekusi pada bagian default seperti di bawah ini dengan memanggil fungsi error_alert
    	default :
    		error_alert ();
    		goto ulangi ;
    	break ;
	}
}


//=======================================================================//
//*****           Fungsi Untuk Menampilkan Pesanan Villa            *****//
//=======================================================================//
// Nama Fungsi    : pesan_villa_anyelir                                  //
// Input Argumen  : pesanvl.nomor_villa, pesanvl.id_pesan,               //
//                  pesanvl.nama_pemesan, pesanvl.noHP, pesanvl.email    //
//                  pesanvl.orang, int hari1, pesanvl.tglCI, pesanvl.blnCI//
//                  pesanvl.thnCI, dan pesanvl.DPpemesan                 //
// Output Argumen : deposito, biaya_ADM,pesanvl.totalPembayaran,         //
//                  pesanvl.sisaPembayaran                               //
// Deskripsi      : Menampilkan program pesan villa dengan menginputkan  //
//                  data diri pengguna dan juga detail dari pesanan      //
//                  seperti biaya dan juga tanggal check in yang nantinya//
//                  akan tersimpan pada file databases "datapesan.txt"   //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void pesan_villa_anyelir (){
	system ("cls");
	list_villa (); //memanggil fungsi list_villa untuk menampilkan list villa anyelir
	printf ("\n\n"); 
	printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|                   PESAN VILLA ANYELIR                   |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    FILE*dtpesan ; // Membuat pointer dtpesan untuk menunjuk pada file "datapesan.txt"
    dtpesan = fopen ("datapesan.txt", "ab"); // Membuka file "datapesan.txt" dengan mode "ab"
    
    // Melakukan Pengecekan apakah pointer dtpesan menunjuk kepada file yang dituju ("datapesan.txt")
    if (dtpesan== NULL ){
		printf("\t\t\t\t\t|File tidak dapat dibuat!\r\n");
		menuadm();
	}
	
	do {
		//intruksi untuk menginput id villa
		printf ("\t\t\t\t\t| Masukkan Id Villa     : ");
		scanf  ("%d", &pesanvl.nomor_villa);
		//karena id villa hanya ada 1-12 maka jika memilih dengan benar maka akan dieksekusi di dalam if ini
		if (pesanvl.nomor_villa >=1 && pesanvl.nomor_villa <=12){
			pemesanan_villa (); //untuk menyeleksi harga villa sesuai dengan id villa masing-masing dengan memanggil fungsi pemesanan_villa
				printf ("\t\t\t\t\t| Id Pemesanan          : "); fflush(stdin); scanf ("%d", &pesanvl.id_pesan);
				printf ("\t\t\t\t\t| Nama Pemesan          : "); fflush(stdin); gets (pesanvl.nama_pemesan);
				printf ("\t\t\t\t\t| No HP Pemesan         : "); fflush(stdin); scanf ("%s", &pesanvl.noHP);
				printf ("\t\t\t\t\t| Email Pemesan         : "); fflush(stdin); scanf ("%s", &pesanvl.email);
				printf ("\t\t\t\t\t| Jumlah Orang          : "); fflush(stdin); scanf ("%d", &pesanvl.orang);
				printf ("\t\t\t\t\t| Check In HARI [ANGKA] : ");
				scanf ("%d", &hari1);
				printf ("\t\t\t\t\t| Check In [DD/MM/YYYY] : "); fflush(stdin); scanf ("%d/%d/%d", &pesanvl.tglCI, &pesanvl.blnCI, &pesanvl.thnCI);
				printf ("\t\t\t\t\t| Deposito              : Rp.%.2f\n", deposito);
				printf ("\t\t\t\t\t| Biaya Admin           : Rp.%.2f\n", biaya_ADM);
				printf ("\t\t\t\t\t| Total Pembayaran      : Rp.%.2f\n", pesanvl.totalPembayaran);
				printf ("\t\t\t\t\t| DP Pemesan            : "); fflush(stdin); scanf ("%f", &pesanvl.DPpemesan);
				pesanvl.sisaPembayaran = pesanvl.totalPembayaran - pesanvl.DPpemesan ;
				printf ("\t\t\t\t\t| Sisa Pembayaran       : Rp.%.2f\n", pesanvl.sisaPembayaran);
				// Menuliskan semua data yang sebelumnya yang diinput oleh pengguna kedalam file "datapesan.txt"
		    	fwrite(&pesanvl, sizeof(pesanvl), 1, dtpesan);
		}
		//jika memilih id villa selain 1-12 tersebut maka akan dieksekusi pada else berikut
		else {
			fflush(stdin);
			printf ("\t\t\t\t\t| HARAP MASUKKAN ID VILLA DENGAN BENAR \n");
			getch();
			pesan_villa_anyelir(); //memanggil fungsi pesan_villa_anyelir
				
		}
		detPemesanan (); //mencetak struk dengan memanggil fungsi detPemesanan
		printf ("\t\t\t\t\t Data pemesanan tersimpan. \n");
		printf("\t\t\t\t\t Pesan villa lagi? (Y/T) : "); fflush(stdin); //menghadirkan opsi jika ingin pesan villa lagi
	    scanf("%s", &jawab)	;
	}
	while (jawab == 'Y'||jawab=='y'); //jika user menginput Y atau Y maka akan balik lagi ke awal perulangan do
	fclose(dtpesan); //menutup file dengan fclose		
	menuadm();
}  


//=======================================================================//
//*****        Fungsi Menyeleksi Harga Total Pembayaran             *****//
//=======================================================================//
// Nama Fungsi    : pemesanan_villa                                      //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Menampilkan sistem harga total pembayaran Villa      //
//                  berdasarkan id masing-masing villa karena setiap     //
//                  villa memiliki harga yang berbeda-beda               //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void pemesanan_villa (){
	if (pesanvl.nomor_villa==1){
		pesanvl.totalPembayaran = 1800000 + biaya_ADM + deposito ;	
	}
	else if(pesanvl.nomor_villa==2){
		pesanvl.totalPembayaran = 1650000 + biaya_ADM + deposito ;	
	}
	else if (pesanvl.nomor_villa==3){
		pesanvl.totalPembayaran = 1750000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==4){
		pesanvl.totalPembayaran = 3800000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==5){
		pesanvl.totalPembayaran = 7750000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==6){
		pesanvl.totalPembayaran = 5800000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==7){
		pesanvl.totalPembayaran = 4800000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==8){
		pesanvl.totalPembayaran = 4300000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==9){
		pesanvl.totalPembayaran = 5960000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==10){
		pesanvl.totalPembayaran = 2750000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==11){
		pesanvl.totalPembayaran = 4120000 + biaya_ADM + deposito ;
	}
	else if (pesanvl.nomor_villa==12){
		pesanvl.totalPembayaran = 4800000 + biaya_ADM + deposito ;
	}
}

//=======================================================================//
//*****        Fungsi Untuk Menampilkan Detail Penesanan            *****//
//=======================================================================//
// Nama Fungsi    : detPemesanan                                         //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan detail        //
//                  pemesanan yang akan tamppil saat setelah memesan     //
//                  villa                                                //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void detPemesanan (){
	printf ("\n\n");
	printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|                  DETAIL PEMESANAN VILLA                 |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
	waktu (); //memanggil fungsi waktu
	printf ("\t\t\t\t\t| Id Villa              : %d\n", pesanvl.nomor_villa);
	printf ("\t\t\t\t\t| Id Pemesanan          : %d\n", pesanvl.id_pesan);
	printf ("\t\t\t\t\t| Nama Pemesan          : %s\n", pesanvl.nama_pemesan);
	printf ("\t\t\t\t\t| No HP Pemesan         : %s\n", pesanvl.noHP);
	printf ("\t\t\t\t\t| Email Pemesan         : %s\n", pesanvl.email);
	printf ("\t\t\t\t\t| Jumlah Orang          : %d\n", pesanvl.orang);
	printf ("\t\t\t\t\t| Check In              : ");
	hari (); //memanggil fungsi hari 
	printf (" %d/%d/%d\n", pesanvl.tglCI, pesanvl.blnCI, pesanvl.thnCI);
	kalenderuntukCO (); //memanggil fungsi kalenderuntukCO
	
	//rumus untuk perhitungan hari, karena input menggunakan angka maka akan diproses dengan rumus di bawah ini :
	hari1=hari1+(hari2%7);
	while (hari1>7)
		hari1=hari1%7;
		
	printf ("\t\t\t\t\t| Check Out             : ");
	hari (); //memanggil fungsi hari 
	printf (" %d/%d/%d\n", pesanvl.tglCO,pesanvl.blnCO, pesanvl.thnCO) ;
	printf ("\t\t\t\t\t| Deposito              : Rp.%.2f\n", deposito);
	printf ("\t\t\t\t\t| Biaya Admin           : Rp.%.2f\n", biaya_ADM);
	printf ("\t\t\t\t\t| Total Pembayaran      : Rp.%.2f\n", pesanvl.totalPembayaran);
	printf ("\t\t\t\t\t| DP Pemesan            : Rp.%.2f\n", pesanvl.DPpemesan);
	printf ("\t\t\t\t\t| Sisa Pembayaran       : Rp.%.2f\n", pesanvl.sisaPembayaran);
	printf ("\t\t\t\t\t|=========================================================|\n");
}


//=======================================================================//
//*****          Fungsi Untuk Menampilkan Tanggal Check Out         *****//
//=======================================================================//
// Nama Fungsi    : kalenderuntukCO                                      //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan tanggal check //
//                  out Villa                                            //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void kalenderuntukCO (){
	//tetapkan nilai dari tgl bulan dan thn checkout adalah 0
	pesanvl.tglCO = 0 ;
	pesanvl.blnCO = 0 ;
	pesanvl.thnCO = 0 ;
	//menggunakan do while 
	do {
		if (hari2 <= 31) //jika hari2 atau check out kurang dari sama dengan 31
		{
			if (pesanvl.blnCI == 2) //jika bulannya 2 maka akan diproses pada bulan Februari dengan memanggil fungsi Februari (int thn)
				pesanvl.tglCO = Februari (pesanvl.thnCI);
			else //jika selain februari maka akan diproses dengan memanggil fungsi BknFeb (int thn, int bln)
				pesanvl.tglCO = BknFeb (pesanvl.thnCI,pesanvl.blnCI);
				
			if (pesanvl.tglCI + hari2 > pesanvl.tglCO) 
			{
				pesanvl.blnCO = pesanvl.blnCI + 1 ;
				
				//jika bulannya lebih dari 12 karena tidak ada bulan yang jumlahnya lebih dari 12 maka kita akan ganti tahun menjadi + 1
				if (pesanvl.blnCO>12){
					pesanvl.thnCO=pesanvl.thnCI+1;
					pesanvl.blnCO=1;
				}
				else // jika tidak lebih dari 12 bulannya maka tahunnya tetap
				pesanvl.thnCO = pesanvl.thnCI ;
				pesanvl.tglCO = pesanvl.tglCI + hari2 - pesanvl.tglCO ;

			}
			else //jika statement if tidak memenuhi maka tanggal CO hanya ditambah dengan hari2=1, bulan dan tahun tetap
			{
				pesanvl.tglCO= pesanvl.tglCI+hari2;
				pesanvl.blnCO=pesanvl.blnCI;
				pesanvl.thnCO=pesanvl.thnCI;
			}
		
		}
		else //jika statement if tidak memenuhi maka else ini akan dieksekusi
		{
			if (pesanvl.blnCI == 2) //jika bulan CI = 2 maka akan memanggil fungsi Februari
				pesanvl.tglCO = Februari (pesanvl.blnCI);
			else //jika bulan CI selain Februari maka akan memanggil fungsi BknFeb
				pesanvl.tglCO = BknFeb (pesanvl.thnCI,pesanvl.blnCI);
				hari2 = hari2 - pesanvl.tglCO;
			if (pesanvl.blnCI == 12)//jika bulan CI = 12 atau Desember
			{
				pesanvl.blnCI = 1 ; 
				pesanvl.thnCI = pesanvl.thnCI + 1 ;
			}
			else
				pesanvl.blnCI = pesanvl.blnCI + 1 ;
		}
	}
	while (pesanvl.thnCO== 0); //akan mengalami perualangan ke do jika tahun CO=0
}


//=======================================================================//
//***** Fungsi Untuk Menyeleksi Jumlah Tanggal Pada Bulan Februari   ****//
//=======================================================================//
// Nama Fungsi    : int Februari                                         //
// Passing Argumen: int thn                                              //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menyeleksi jumlah tanggal //
//                  pada bulan Februari                                  //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
int Februari (int thn){
	thn = pesanvl.thnCI;
	if ((pesanvl.thnCI % 100 != 0) && (pesanvl.thnCI % 4 == 0)||(pesanvl.thnCI % 400 == 0)){ //perhitungan bila jumlah tanggal pada bulan februari sebanyak 29
		return 29 ; //mengembalikan nilai 29
	}
	else {
		return 28 ; //mengembalikan nilai 28
	}		
}


//=======================================================================//
//****Fungsi Untuk Menyeleksi Jumlah Tanggal Pada Bulan Bukan Februari***//
//=======================================================================//
// Nama Fungsi    : int BknFeb                                           //
// Passing Argumen: int thn, int bln                                     //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menyeleksi jumlah tanggal //
//                  pada bulan selain Februari                           //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
int BknFeb (int thn, int bln){
	thn = pesanvl.thnCI;
	bln = pesanvl.blnCI;
	//karena bulan 1,3,5,7,8,10,12 jumlah tanggalnya 31 maka mengembalikan nilai 31
	if ((pesanvl.blnCI==1) || (pesanvl.blnCI==3) || (pesanvl.blnCI==5) || (pesanvl.blnCI==7) || (pesanvl.blnCI==8) || (pesanvl.blnCI==10) || (pesanvl.blnCI==12)){
		return 31 ;
	}
	else { //selain bulan yg tidak diseleksi pada if diatas maka mengembalikan nilai 30
		return 30 ;
	}
}


//=======================================================================//
//*****                  Fungsi Untuk Menampilkan Hari              *****//
//=======================================================================//
// Nama Fungsi    : hari                                                 //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan hari pada     //
//                  program yang akan ditampilkan pada detail pemesanan  //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void hari (){
	switch (hari1){
		case 1 : printf ("SENIN"); break ;
		case 2 : printf ("SELASA"); break ;
		case 3 : printf ("RABU"); break ;
		case 4 : printf ("KAMIS"); break ;
		case 5 : printf ("JUMAT"); break ;
		case 6 : printf ("SABTU"); break ;
		case 7 : printf ("MINGGU"); break ;
	}
} 

//=======================================================================//
//***********   Fungsi Untuk Menampilkan Data Pesananan     *************//
//=======================================================================//
// Nama Fungsi    : lihat_data_pesanan                                   //
// Input Argumen  : char opsi_kembali                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan data pesanan  //
//                  villa anyelir dengan memanggil fungsi                //
//                  list_data_pemesan                                    //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void lihat_data_pesanan (){
	char opsi_kembali; //deklarasi opsi_kembali ke dalam variabel bertipe data char
	system ("cls");
	list_data_pemesan (); //memanggil fungsi list_data_pemesan
	opsi :
	printf("\t\t| Kembali ke menu ketik Y : ");
	scanf ("%s", &opsi_kembali);
	if (opsi_kembali=='Y'||opsi_kembali=='y') //jika mengetik Y atau y maka akan mengarah pada fungsi menuadm
	    menuadm();
	else //jika selain Y atau y maka akan balik pada opsi
	    goto opsi ;
}

//=======================================================================//
//*****          Fungsi Untuk Menampilkan List Data Pemesan         *****//
//=======================================================================//
// Nama Fungsi    : list_data_pemesan                                    //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk menampilkan list data     //
//                  dari pemesan Villa dan khusus untuk pegawai          //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void list_data_pemesan (){
	system ("cls");
	printf ("\t\t|==================================================================================================================================|\n");
	printf ("\t\t|                                                 DATA PEMESAN VILLA ANYELIR                                                       |\n");
	printf ("\t\t|==================================================================================================================================|\n");
	printf ("\t\t| Id Pemesanan | Kode Villa |     Nama Pemesan      |        NO HP      |     Check In     | Total Pembayaran  | Sisa Pembayaran   |\n");
	printf ("\t\t|--------------|------------|-----------------------|-------------------|------------------|-------------------|-------------------|\n");                                                                                          
	FILE*dtpesan ; // Membuat pointer dtpesan untuk menunjuk pada file "datapesan.txt"
    dtpesan = fopen ("datapesan.txt", "rt"); // Membuka file "datapesan.txt" dengan mode "rt"
    if (dtpesan== NULL ){ // Melakukan Pengecekan apakah pointer dtpesan menunjuk kepada file yang dituju ("datapesan.txt")
		printf("\t\t\t| FILE TIDAK DAPAT DIBUKA!\r\n");
		menuadm();
	}
		/* Ambil isi file ngenggunakan fungsi fread(), lalu tampilkan ke layar */
	while ((fread(&pesanvl, sizeof(pesanvl), JUM_BLOK, dtpesan)) == JUM_BLOK )
	printf ("\t\t|     %d          %d           %s               %s           %d/%d/%d      Rp.%.2f      Rp.%.2f\n", pesanvl.id_pesan, pesanvl.nomor_villa, pesanvl.nama_pemesan, pesanvl.noHP, pesanvl.tglCI, pesanvl.blnCI, pesanvl.thnCI, pesanvl.totalPembayaran, pesanvl.sisaPembayaran);
	fclose(dtpesan);
	printf ("\t\t|==================================================================================================================================|\n");
}

//=======================================================================//
//*****            Fungsi Untuk Check Nomor ID Pemesanan            *****//
//=======================================================================//
// Nama Fungsi    : checkNomor                                           //
// Passing Argumen: pesan_villa pesanvl,int id                           //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk mengecek nomor ID Pemesanan//
//                   yang digunakan saat menghapus data pemesanan        //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
int checkNomor(pesan_villa pesanvl,int id){
	FILE *dtpesan;
	int c = 1;
	if(c==1){
		dtpesan = fopen("datapesan.txt","rb");
		while(fread(&pesanvl, sizeof(pesanvl),1,dtpesan)){
			if( id == pesanvl.id_pesan){
				fclose(dtpesan);
				return 1;
			}
		}
	}else{
		c = 0;
		fclose(dtpesan);
		return 0;
	}
}

//=======================================================================//
//***********    Fungsi Untuk Melihat Data Pesanan Villa    *************//
//=======================================================================//
// Nama Fungsi    : hapus_pesanan                                        //
// Input Argumen  : int pil_hapus                                        //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menghapus pesanan dengan  //
//                  memanggil fungsi hapus jika memilih 1 dan memanggil  //
//                  fungsi menuadm jika memilih 2                        //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void hapus_pesanan (){
	system ("cls");
	int pil_hapus ; //deklarasi variabel pil_hapus bertipe data integer
	list_data_pemesan (); //memanggil fungsi list_data_pemesan
	printf ("\n\n"); //untuk enter jarak
	printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|                       HAPUS PESANAN                     |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t| Ketik 1 untuk hapus pesanan di atas                     |\n");
    printf ("\t\t\t\t\t| Ketik 2 untuk keluar                                    |\n");
    kembali_memilih :
    printf ("\t\t\t\t\t| Pilihan : ");
    scanf  ("%d", &pil_hapus);
    if (pil_hapus==1){ //jika memilih 1 akan mengarah pada fungsi hapus
    	hapus ();
	}
	else if (pil_hapus==2){ //jika memilih 2 akan mengarah pada fungsi menuadm
		menuadm ();
	}
	else //jika salah memilih maka akan tampil error dengan memanggil fungsi error_alert dan kembali untuk memilih pilihan yang sesuai
		error_alert ();
		goto kembali_memilih ;
}

//=======================================================================//
//*******         Fungsi Untuk Menghapus Data Pemesanan           *******//
//=======================================================================//
// Nama Fungsi    : hapus                                                //
// Input Argumen  : int pil_hapus                                        //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menghapus pesanan dengan  //
//                  memilih id pemesanan yang akan dihapus serta         //
//                  meyakinkan user apakah yakin akan menghapus data     //
//                  tersebut.                                            //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void hapus (){
	int pil_hapus ; //deklarasi pil_hapus pada fungsi hapus ke dalam variabel bertipe data int
	printf ("\t\t\t\t\t| Pilih ID pemesanan yang akan dihapus : ");
	scanf  ("%d",&pil_hapus); fflush(stdin);
	printf ("\t\t\t\t\t| Apakah anda yakin? (Y/T) : ");
	jawab = toupper(getche());			/* Baca jawaban dari keyboard */
	if (jawab == 'Y'|| jawab == 'y') 
	{	hapusdtpesan(pesanvl, pil_hapus); //memanggil fungsi hapusdtpesan
		hapus_pesanan();
	}hapus_pesanan(); //kembali pada fungsi hapus_pesanan jika tidak memilih Y atau y
}

//=======================================================================//
//*******       Fungsi Untuk Menghapus Database Pemesanan         *******//
//=======================================================================//
// Nama Fungsi    : hapusdtpesan                                         //
// Passing Argumen: pesan_villa pesanvl, int r                           //
// Input Argumen  : int r, int s                                         //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menghapus pesanan dengan  //
//                  memilih id pemesanan yang akan dihapus serta         //
//                  meyakinkan user apakah yakin akan menghapus data     //
//                  tersebut.                                            //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void hapusdtpesan (pesan_villa pesanvl, int r){
	FILE *tmp; // Membuat pointer tmp untuk menunjuk pada file "Temp_Data.txt"
	int s;
	
		if (checkNomor(pesanvl, r) == 0){ //memanggil fungsi checkNomor jika 0 maka akan menampilkan data pemesanan tidak ditemukan
			printf("\t\t\t\t\t Data pemesanan %d tidak ditemukan\n",r);
		}
		else{
			FILE*dtpesan ; // Membuat pointer dtpesan untuk menunjuk pada file "datapesan.txt"
			dtpesan = fopen("datapesan.txt","rb"); //membuka file "datapesan.txt" dengan rb
			tmp = fopen("Temp_Data.txt","wb");  //membuka file "Temp_Data.txt"
			while (fread(&pesanvl, sizeof(pesanvl), 1, dtpesan)){
				s = pesanvl.id_pesan;
				if ( s != r){
					//Menyalin data file yang tidak ingin dihapus
					fwrite(&pesanvl, sizeof(pesanvl), 1, tmp);
				}
			}
			fclose(dtpesan);
			fclose(tmp);
			dtpesan = fopen("datapesan.txt","wb");
			tmp = fopen("Temp_Data.txt","rb");
			while(fread(&pesanvl,sizeof(pesanvl),1,tmp)){
				fwrite(&pesanvl,sizeof(pesanvl),1,dtpesan);
			}
			fclose(dtpesan);  //Menggunakan fungsi fclose untuk menutup file "datapesan.txt" agar tidak diproses lagi
			fclose(tmp);      //Menggunakan fungsi fclose untuk menutup file "tmp" agar tidak diproses lagi
		}
}

//=======================================================================//
//***********   Fungsi Untuk Menampilkan Menu Pengunjung    *************//
//=======================================================================//
// Nama Fungsi    : menu_pengunjung                                      //
// Input Argumen  : int pilihan_deskripsi                                //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan menu          //
//                  pengunjung yang berisi deskripsi villa dan pilihan   //
//                  menu apabila tekan 1 akan mengarah pada fungsi lokasi//
//                  villa, tekan 2 mengarah pada fungsi list villa pengun//
//                  jung, tekan 3 mengarah pada fungsi tampilan pesanan  //
//                  serta 4 exit yaitu kembali ke menu masuk             //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void menu_pengunjung (){
    system ("cls");
    int opsi ;
    int pilihan_deskripsi ; //deklarasi variabel bernama pilihan_deskripsi bertipe integer yang digunakan dalam fungsi menu_pengunjung
	printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|    *      *     *   *      *  *****   *      ***   ***  |\n");
    printf ("\t\t\t\t\t|   * *     * *   *     *   *   *       *       *    *  * |\n");
    printf ("\t\t\t\t\t|  *****    *   * *       *     *****   *       *    ***  |\n");
    printf ("\t\t\t\t\t| *     *   *     *       *     *       *       *    * *  |\n");
    printf ("\t\t\t\t\t|*       *  *     *       *     *****   *****  ***   *  * |\n");
    printf ("\t\t\t\t\t|             SELAMAT DATANG DI VILLA ANYELIR             |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|Villa  Anyelir  adalah  salah  satu  villa  yang  berada |\n");
    printf ("\t\t\t\t\t|di Pulau Bali yang memiliki 5 cabang yang telah menyebar |\n");
    printf ("\t\t\t\t\t|di sekitar Denpasar, Kuta, Ubud, Jimbaran, dan Canggu.   |\n");
    printf ("\t\t\t\t\t|                                                         |\n");
    printf ("\t\t\t\t\t|Villa Anyelir memiliki beberapa fasilitas seperti kamar  |\n");
    printf ("\t\t\t\t\t|yang nyaman,  kamar mandi luas,  ruangan ber AC, dan ada |\n");
    printf ("\t\t\t\t\t|kolam renang di dalamnya.                                |\n");
    printf ("\t\t\t\t\t|                                                         |\n");
    printf ("\t\t\t\t\t|Villa Anyelir memadukan arsitektur Bali dan modern yang  |\n");
    printf ("\t\t\t\t\t|membuat pengunjung senantiasa nyaman saat berada dalam   |\n");
    printf ("\t\t\t\t\t|villa ini. Jika ingin melakukan pemesanan segera hubungi |\n");
    printf ("\t\t\t\t\t|admin.                                                   |\n");
    printf ("\t\t\t\t\t|                                                         |\n");
    printf ("\t\t\t\t\t|Pusat Villa  : Jalan Anyelir No.61, Denpasar Timur, Bali |\n");
    printf ("\t\t\t\t\t|Email Villa  : anyelirvilla@gmail.com                    |\n");
    printf ("\t\t\t\t\t|Kontak Villa : 0361 974 311                              |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|        Tekan 1 untuk melihat rating dan komentar villa  |\n");
    printf ("\t\t\t\t\t|        Tekan 2 untuk melihat lokasi vila                |\n");
	printf ("\t\t\t\t\t|        Tekan 3 untuk melihat list vila                  |\n");
	printf ("\t\t\t\t\t|        Tekan 4 untuk melihat riwayat pesan villa        |\n");
	printf ("\t\t\t\t\t|        Tekan 5 untuk melihat aturan pesan villa         |\n");
	printf ("\t\t\t\t\t|        Tekan 6 untuk melihat tipe fasilitas dan kamar   |\n"); 
	printf ("\t\t\t\t\t|        Tekan 7 untuk beri rating dan komentar villa     |\n"); 
	printf ("\t\t\t\t\t|        Tekan 8 untuk kembali ke menu                    |\n");          
    printf ("\t\t\t\t\t|=========================================================|\n");
    tekan_benar :
    printf ("\t\t\t\t\t                       Tekan : ");
    scanf  ("%d", &pilihan_deskripsi);
    if (pilihan_deskripsi==1){
    	tampilanPenilaian ();
	}
    else if (pilihan_deskripsi==2){ //jika menekan 1 maka akan mengarah pada fungsi lokasi_villa
    	lokasi_villa ();
	}
	else if (pilihan_deskripsi==3){ //jika menekan 2 maka akan mengarah pada fungsi list_villa_pengunjung
		list_villa_pengunjung ();
	}
	else if (pilihan_deskripsi==4){ //jika menekan 3 maka akan mengarah pada fungsi tampilan_pemesanan
		tampilan_pemesanan ();
	}
	else if (pilihan_deskripsi==5){ //jika menekan 4 maka akan mengarah pada fungsi cara_pesan_villa
		cara_pesan_villa ();
	}
	else if (pilihan_deskripsi==6){
		tipeFasilitasdanKamar();
		opsi1 :
		printf ("\t\t\t\t\t  Kembali Tekan 1 : ");
    	scanf ("%d", &opsi);
    	if (opsi==1){ //jika menekan 1 maka akan mengarah ke menu_pengunjung
    	menu_pengunjung ();
		}
		else //jika menekan selain 1 akan diminta ulang menekan
		printf ("\t\t\t\t\t  Silahkan ketik ulang 1 \n");
		goto opsi1 ; //kembali pada opsi	
	}
	
	else if (pilihan_deskripsi==7){
		menuRatingPengunjung ();
	}
	
	else if(pilihan_deskripsi==8){ //jika menekan 7 maka akan kembali pada fungsi menu_masuk
		menu_masuk();
	}
	else { //jika user salah menekan (tidak ada pada pilihan) maka akan terpanggil fungsi error_alert dan akan kembali diminta memilih sesuai dengan opsi yang ada
		error_alert ();
		goto tekan_benar ;
	}
}


//=======================================================================//
//*****            Fungsi Untuk Menampilkan Data Pemesan            *****//
//=======================================================================//
// Nama Fungsi    : tampilan_pemesan                                     //
// Input Argumen  : int pilih1                                           //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk memperlihatkan data       //
//                  para pemesan yang dikhususkan untuk pengguna agar    //
//                  tidak terjadinya pembookingan yang sama              //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void tampilan_pemesanan (){
	int pilih1 ;
	system ("cls");
	printf ("\t\t\t\t\t|================================================|\n");
	printf ("\t\t\t\t\t|            DATA PEMESAN VILLA ANYELIR          |\n");
	printf ("\t\t\t\t\t|================================================|\n");
	printf ("\t\t\t\t\t| Id Pemesanan | Kode/Id Villa |     Check In    |\n");
	printf ("\t\t\t\t\t|--------------|---------------|-----------------|\n");                                                                                          
	FILE*dtpesan ; // Membuat pointer dtpesan untuk menunjuk pada file "datapesan.txt"
    dtpesan = fopen ("datapesan.txt", "rt"); //membuka file "datapesan.txt" dengan rt
    if (dtpesan== NULL ){ // Melakukan Pengecekan apakah pointer dtpesan menunjuk kepada file yang dituju ("datapesan.txt")
		printf("\t\t\t| FILE TIDAK DAPAT DIBUKA!\r\n");
		menuadm();
	}
		/* Ambil isi file ngenggunakan fungsi fread(), lalu tampilkan ke layar */
	while ((fread(&pesanvl, sizeof(pesanvl), JUM_BLOK, dtpesan)) == JUM_BLOK )
	printf ("\t\t\t\t\t|     %d          %d           %d/%d/%d        \n", pesanvl.id_pesan, pesanvl.nomor_villa,pesanvl.tglCI, pesanvl.blnCI, pesanvl.thnCI);
	fclose(dtpesan);
	printf ("\t\t\t\t\t|================================================|\n");
	printf ("\t\t\t\t\t|   Tekan  1 untuk kembali ke menu pengunjung    |\n");
    printf ("\t\t\t\t\t|================================================|\n");
    tekan1 :
    printf ("\t\t\t\t\t| Tekan      : ") ;
	scanf  ("%d", &pilih1);
	if (pilih1== 1) //jika menekan 1 maka akan diarahkan pada menu pengunjung dengan memanggil fungsi menu_pengunjung
		menu_pengunjung ();
	else  //jika menekan selain 1 maka akan diminta untuk mengetik 1 sampai benar
		printf ("\t\t\t\t\t| Silahkan ketik ulang 1 \n"); 
		goto tekan1 ;
}


//=======================================================================//
//*****               Fungsi Untuk Mengecek Lokasi Villa            *****//
//=======================================================================//
// Nama Fungsi    : lokasi_villa                                         //
// Input Argumen  : int pilih1                                           //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini berfungsi untuk mengecek lokasi villa yang//
//                  ada dengan memperlihatkan daerah dan alamat villa    //
//                  untuk memudahi pengguna dalam memilih villa          //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 13-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void lokasi_villa (){
	int pilih1 ;
	system ("cls");
    printf ("\n");
    printf ("\t\t\t\t\t|============================================================|\n");
    printf ("\t\t\t\t\t|                          LOKASI VILLA                      |\n");
    printf ("\t\t\t\t\t|============================================================|\n");
    printf ("\t\t\t\t\t|  Lokasi    |                    Alamat                     |\n");
    printf ("\t\t\t\t\t|------------|-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Anyelir No.61, Denpasar Timur, Bali      |\n");
    printf ("\t\t\t\t\t|1. Denpasar | ----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Hayam Wuruk No.05, Denpasar Timur, Bali  |\n");
    printf ("\t\t\t\t\t|------------|-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Raya Kesambi No.42, Kuta, Bali           |\n");
    printf ("\t\t\t\t\t|2. Kuta     |-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Dewi Sri No.80, Kuta, Bali               |\n");
    printf ("\t\t\t\t\t|------------|-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Raya Pengosekan No.67, Ubud, Bali        |\n");
    printf ("\t\t\t\t\t|3. Ubud     | ----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Raya Pengosekan No.102, Ubud, Bali       |\n");
    printf ("\t\t\t\t\t|------------|-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Raya Uluwatu No.121, Jimbaran, Bali      |\n");
    printf ("\t\t\t\t\t|            |-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|4. Jimbaran |Jalan Bukit Permai No.66, Jimbaran, Bali       |\n");
    printf ("\t\t\t\t\t|            |-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Raya Uluwatu No.46, Jimbaran, Bali       |\n");
    printf ("\t\t\t\t\t|------------|-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Sahadewa No.21, Canggu, Bali             |\n");
    printf ("\t\t\t\t\t|            |-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|5. Canggu   |Jalan Pantai Berawa No.61, Canggu, Bali        |\n");
    printf ("\t\t\t\t\t|            |-----------------------------------------------|\n");
    printf ("\t\t\t\t\t|            |Jalan Nelayan No.81, Canggu, Bali              |\n");
    printf ("\t\t\t\t\t|------------------------------------------------------------|\n");
    printf ("\t\t\t\t\t|============================================================|\n");
    printf ("\t\t\t\t\t|         Tekan  1 untuk kembali ke menu pengunjung          |\n");
    printf ("\t\t\t\t\t|============================================================|\n");
    tekan1 :
    printf ("\t\t\t\t\t| Tekan      : ") ;
	scanf  ("%d", &pilih1);
	if (pilih1== 1)
		menu_pengunjung ();
	else 
		printf ("\t\t\t\t\t| Silahkan ketik ulang 1 \n");
		goto tekan1 ;
   
}

//=======================================================================//
//***********     Fungsi Untuk Menampilkan List Villa       *************//
//=======================================================================//
// Nama Fungsi    : list_villa                                           //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan list villa    //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Putu Eternalie Prajnani Welaga - 2105551046                           //
// Kelas B                                                               //
//=======================================================================//
void list_villa (){
	system ("cls");
	printf ("|======================================================================================================================================================================|\n");
    printf ("|                                                                     LIST VILLA ANYELIR                                                                               |\n");
    printf ("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf ("|ID/KODE VILLA|    NAMA VILLA   |   TIPE   FASILITAS  |    TIPE KAMAR   | HARGA LUNAS  |      DP      |   KAPASITAS   |   CHECK IN  | CHECK OUT |     LAMA INAP        |\n");
    printf ("|-------------|-----------------|---------------------|-----------------|--------------|--------------|---------------|-------------|-----------|----------------------|\n");
    	/* Buka file untuk dibaca isinya */
	if ((dtvilla=fopen("datavilla.dat", "rt")) == NULL )
		{
			printf("\t\t File tidak dapat dibuka!\n");
			exit(1);
		}
		/* Ambil isi file ngenggunakan fungsi fread(), lalu tampilkan ke layar */
	while ((fread(&villa, sizeof(villa), JUM_BLOK, dtvilla)) == JUM_BLOK )
	printf("|    %d\t          %-15s          %-10s     %-25s   Rp.%d      Rp.%d      %d Orang       %-10s  %-10s  %-25s\n", villa.kode_villa, villa.nama_villa, villa.tipe_fasilitasLain, villa.tipe_kamar, villa.harga_lunas, villa.DP_villa, villa.kapasitas, villa.check_in, villa.check_out, villa.lama_inap);
	printf ("|======================================================================================================================================================================|\n");
	fclose(dtvilla);		/* Tutup file */

}

//=======================================================================//
//****              Fungsi Untuk Menghapus Data Villa (1)            ****//
//=======================================================================//
// Nama Fungsi    : hapus_villa                                          //
// Passing Argumen: int pil_hapus  									   	 //
// Input Argumen  : -                               		             //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menghapus data villa      //
//                  anyelir                                              //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 1-1-2021                                 Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void hapus_villa(){
	system ("cls");
	int pil_hapus ; //deklarasi variabel pil_hapus bertipe data integer
	list_villa (); //memanggil fungsi list_data_pemesan
	printf ("\n\n"); //untuk enter jarak
	printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t|                    HAPUS DATA VILLA                     |\n");
    printf ("\t\t\t\t\t|=========================================================|\n");
    printf ("\t\t\t\t\t| Ketik 1 untuk hapus data villa di atas                  |\n");
    printf ("\t\t\t\t\t| Ketik 2 untuk keluar                                    |\n");
    pilihLagi:
    printf ("\t\t\t\t\t| Pilihan : ");
    scanf  ("%d", &pil_hapus);
    if (pil_hapus==1){ //jika memilih 1 akan mengarah pada fungsi hapus
    	hapusvilla ();
	}
	else if (pil_hapus==2){ //jika memilih 2 akan mengarah pada fungsi menuadm
		menuadm ();
	}
	else //jika salah memilih maka akan tampil error dengan memanggil fungsi error_alert dan kembali untuk memilih pilihan yang sesuai
		error_alert ();
		goto pilihLagi ;
}

//=======================================================================//
//****    Fungsi Untuk Menghapus Data Villa dari Database            ****//
//=======================================================================//
// Nama Fungsi    : hapusdtvilla                                         //
// Passing Argumen: data_villa villa, int r                              //
// Input Argumen  : -                               		             //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menghapus data villa dari //
//					database datavilla.dat kemudian yang tidak dihapus   //
//    				akan disimpan sementara di Temp_Data dan akan dikem -//
//                  balikan lagi pada datavilla.dat                      //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 1-1-2021                                 Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void hapusdtvilla (data_villa villa, int r){
	FILE *tmp;
	int s;
	
		if (checkKode(villa, r) == 0){
			printf("\t\t\t\t\t Data villa %d tidak ditemukan\n\n",r);
		}
		else{
			dtvilla = fopen("datavilla.dat","rb");
			tmp = fopen("Temp_Data.txt","wb");
			while (fread(&villa, sizeof(villa), 1, dtvilla)){
				s = villa.kode_villa;
				if ( s != r){
					//Menyalin data file yang tidak ingin dihapus
					fwrite(&villa, sizeof(villa), 1, tmp);
				}
			}
			fclose(dtvilla);
			fclose(tmp);
			dtvilla = fopen("datavilla.dat","wb");
			tmp = fopen("Temp_Data.txt","rb");
			while(fread(&villa,sizeof(villa),1,tmp)){
				fwrite(&villa,sizeof(villa),1,dtvilla);
			}
			fclose(dtvilla);
			fclose(tmp);
		}
}

//=======================================================================//
//****              Fungsi Untuk Mengecek Kode/ID Villa              ****//
//=======================================================================//
// Nama Fungsi    : checkKode                                            //
// Passing Argumen: data_villa villa, int id                             //
// Input Argumen  : -                               		             //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk mengecek kode/ID villa    //
//       		    yang digunakan saat menghapus data villa             //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 1-1-2021                                 Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
int checkKode(data_villa villa,int id){
	FILE *dtvilla;
	int c = 1;
	if(c==1){
		dtvilla = fopen("datavilla.dat","rb");
		while(fread(&villa, sizeof(villa),1,dtvilla)){
			if( id == villa.kode_villa){
				fclose(dtvilla);
				return 1;
			}
		}
	}else{
		c = 0;
		fclose(dtvilla);
		return 0;
	}
}

//=======================================================================//
//****              Fungsi Untuk Menghapus Data Villa (2)            ****//
//=======================================================================//
// Nama Fungsi    : hapusvilla                                           //
// Input Argumen  : int pil_hapus                                        //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menghapus data villa yang //
//                  merupakan lanjutan dari fungsi hapus_villa           //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 1-1-2021                                 Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void hapusvilla (){
	int pil_hapus ; //deklarasi pil_hapus pada fungsi hapus ke dalam variabel bertipe data int
	printf ("\t\t\t\t\t| Pilih ID villa yang akan dihapus : ");
	scanf  ("%d",&pil_hapus); fflush(stdin);
	printf ("\t\t\t\t\t| Apakah anda yakin? (Y/T)         : ");
	jawab = toupper(getche());			/* Baca jawaban dari keyboard */
	if (jawab == 'Y'|| jawab == 'y') 
	{	hapusdtvilla(villa, pil_hapus); //memanggil fungsi hapusdtpesan
		hapus_villa();
	}hapus_villa(); //kembali pada fungsi hapus_pesanan jika tidak memilih Y atau y
}

//=======================================================================//
//****         Fungsi Untuk Menginput Data Villa Anyelir Baru        ****//
//=======================================================================//
// Nama Fungsi    : inputVillaAnyelir                                    //
// Input Argumen  : villa.kode_villa, villa.tipe_fasilitasLain,          //
//					villa.nama_villa, villa.tipe_kamar, villa.harga_lunas//
// 					villa.DP_villa, villa.kapasitas, villa.check_in,     //
//  				villa.check_in, villa.check_out,villa.lama_inap, jawab//
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk meninput data villa anye- //
//                  lir baru                                             //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 1-1-2021                                 Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void inputVillaAnyelir (){
	system ("cls");
	printf ("\t\t\t\t\t|===========================================================|\n");
    printf ("\t\t\t\t\t|                 INPUT DATA VILLA ANYELIR                  |\n");
    printf ("\t\t\t\t\t|===========================================================|\n");
    	if ((dtvilla=fopen("datavilla.dat", "ab")) == NULL )
	{
		printf("\t\t\t\t\t File tidak dapat dibuat!\r\n");
		menuadm();
	}
	
	do {
		printf("\t\t\t\t\t Kode Villa     : "); fflush(stdin);
		scanf("%d", &villa.kode_villa);
		printf("\t\t\t\t\t Nama Villa     : "); fflush(stdin);
		gets(villa.nama_villa);
		printf("\t\t\t\t\t Tipe Fasilitas : "); fflush(stdin);
		gets(villa.tipe_fasilitasLain);
		printf("\t\t\t\t\t Tipe Kamar     : "); fflush(stdin);
		gets(villa.tipe_kamar);
		printf("\t\t\t\t\t Harga Lunas    : "); fflush(stdin);
		scanf("%d", &villa.harga_lunas);
		printf("\t\t\t\t\t DP             : "); fflush(stdin);
		scanf("%d", &villa.DP_villa);
		printf("\t\t\t\t\t Kapasitas      : "); fflush(stdin);
		scanf("%d", &villa.kapasitas);
		printf("\t\t\t\t\t CHECK IN [Jam] : "); fflush(stdin);
		gets(villa.check_in);
		printf("\t\t\t\t\t CHECK OUT [Jam]: "); fflush(stdin);
		gets(villa.check_out);
		printf("\t\t\t\t\t Lama Inap      : "); fflush(stdin);
		gets(villa.lama_inap);
				
		/* Rekam sebuah data bertipe record menggunakan fungsi fwrite */
		fwrite(&villa, sizeof(villa), 1, dtvilla);
		
		printf("\t\t\t\t\t Memasukkan data lagi (Y/T)? => "); fflush(stdin);
		jawab = toupper(getche());		/* Baca jawaban dari keyboard */
	}
	while (jawab == 'Y');
	fclose(dtvilla);		/* Tutup file */
	
	printf("\n\t\t\t\t\t Data sudah disimpan pada file. \n");
	printf("\t\t\t\t\t Lihat isi file (Y/T)? => "); fflush(stdin);
	jawab = toupper(getche());			/* Baca jawaban dari keyboard */
	if (jawab == 'Y');
	{	list_villa();
	}
	
	menuadm();
}

//=======================================================================//
//****       Fungsi Untuk Menampilkan Tipe Fasilitas dan Kamar       ****//
//=======================================================================//
// Nama Fungsi    : tipeFasilitasdanKamar                                //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan tipe fasilitas//
//                  dan kamar pada villa anyelir                         //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 1-1-2021                                 Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void tipeFasilitasdanKamar (){
	system ("cls");
	printf ("\n\n");
	printf ("\t\t\t\t\t|======================================================================|\n");
    printf ("\t\t\t\t\t|                         TIPE FASILITAS DAN KAMAR                     |\n");
    printf ("\t\t\t\t\t|======================================================================|\n");
    printf ("\t\t\t\t\t| Tipe Fasilitas Villa                                                 |\n");
    printf ("\t\t\t\t\t|----------------------------------------------------------------------|\n");
    printf ("\t\t\t\t\t|1. Tipe A : Dilengkapi dengan AC, BathUp, Billyard, Ruang Tamu Luas,  |\n");
    printf ("\t\t\t\t\t|            villa 3 lantai, 3 TV, Towel, Ruang Mandi Air Hangat, Dapur|\n");
    printf ("\t\t\t\t\t|            yang luas, Wi-Fi, Kolam Renang Dekat Pantai, mendapat view|\n");
    printf ("\t\t\t\t\t|            pantai, 5 kamar mandi, ruang makan, dan balkon.           |\n");
    printf ("\t\t\t\t\t|2. Tipe B : Dilengkapi dengan AC, BathUp, Ruang Tamu Sedang, 3 kamar  |\n");
    printf ("\t\t\t\t\t|            mandi, towel, 2 TV, Villa 3 lantai, ruang makan, kolam    |\n");
    printf ("\t\t\t\t\t|            renang lantai 1, dan balkon, ruang mandi air hangat, dan  |\n");
    printf ("\t\t\t\t\t|            1 dapur sedang.                                           |\n");
    printf ("\t\t\t\t\t|3. Tipe C : Dilengkapi dengan AC, Ruang Tamu Sedang, 2 kamar mandi    |\n");
    printf ("\t\t\t\t\t|            towel, kolam renang lantai 1, villa 2 lantai, towel, kolam|\n");
    printf ("\t\t\t\t\t|            renang sedang lantai 1, 1 dapur sedang.                   |\n");
    printf ("\t\t\t\t\t|----------------------------------------------------------------------|\n");
    printf ("\t\t\t\t\t| Tipe Kamar                                                           |\n");
    printf ("\t\t\t\t\t|----------------------------------------------------------------------|\n");
    printf ("\t\t\t\t\t| 1. Single Room          : 1 kamar dengan 1 kasur besar               |\n");
    printf ("\t\t\t\t\t| 2. Twin Room            : 2 kamar dengan masing-masing 1 kasur besar |\n");
    printf ("\t\t\t\t\t| 3. Twin Room and Bed    : 2 kamar dengan masing-masing 2 kasur besar |\n");  
    printf ("\t\t\t\t\t| 4. Triple Room          : 3 kamar dengan masing-masing 1 kasur besar |\n");  
    printf ("\t\t\t\t\t| 5. Deluxe Room          : 5 kamar besar dengan masing-masing 1 kasur |\n");  
	printf ("\t\t\t\t\t|                           besar                                      |\n");  
    printf ("\t\t\t\t\t|======================================================================|\n");
}

//=======================================================================//
//****       Fungsi Untuk Menampilkan Menu Rating Penginjung         ****//
//=======================================================================//
// Nama Fungsi    : menuRatingPengunjung                                 //
// Input Argumen  : int pilihan, int opsiPilihan                         //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan menu rating   //
//                  pengunjung, jika tekan 1 maka akan mengarah pada     //
//                  fungsi ratingPengunjung, dan tekan 2 untuk keluar    //
//                  yaitu ke menu pengunjung                             //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 1-1-2021                                 Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void menuRatingPengunjung (){
	int pilihan ;
	int opsiPilihan ;
	system ("cls");
	printf ("\n\n");
	printf ("\t\t\t\t\t|======================================================================|\n");
    printf ("\t\t\t\t\t|             RATING DAN KOMENTAR PENGUNJUNG VILLA ANYELIR             |\n");
    printf ("\t\t\t\t\t|======================================================================|\n");
    printf ("\t\t\t\t\t| Pilih :                                                              |\n");
    printf ("\t\t\t\t\t| 1. Lanjutkan untuk beri rating                                       |\n");
    printf ("\t\t\t\t\t| 2. Keluar                                                            |\n");
    pilihUlang :
    printf ("\t\t\t\t\t| Masukkan pilihan anda  : ");
    scanf ("%d", &opsiPilihan);
    switch (opsiPilihan){
    	case 1 :
    	   ratingPengunjung ();	
    	break ;
    	
    	case 2 :
    		menu_pengunjung ();
    	break ;
    	
    	default :
    		error_alert();
    		goto pilihUlang ;
    		break ;
	}
}

//=======================================================================//
//****                Fungsi Untuk Penilaian Pengunjung              ****//
//=======================================================================//
// Nama Fungsi    : ratingPengunjung                                     //
// Input Argumen  : int tekan 1, penilaian.idPemesan, penilaian.nama_    //
//                  penilai, penilaian.tglPenilaian, penilaian.blnPeni   //
//                  laian, penilaian.thnPenilaian,penilaian.rating,      //
//                  penilaian.komentar                                   //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menginputkan rating yang  //
//                  diberikan pengunjung villa anyelir                   //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void ratingPengunjung (){
	int tekan1 ;
	    
	FILE*dtpenilaian ; // Membuat pointer dtpenilaian untuk menunjuk pada file "datapesan.txt"
	dtpenilaian = fopen ("datapenilaian.txt", "ab"); // Membuka file "datapenilaian.txt" dengan mode "ab"
	
    // Melakukan Pengecekan apakah pointer dtpesan menunjuk kepada file yang dituju ("datapenilaian.txt")
   	if (dtpenilaian== NULL ){
	printf("\t\t\t\t\t|File tidak dapat dibuat!\r\n");
	menu_pengunjung();
	}
	
    else {
	
	printf ("\t\t\t\t\t| Masukkan ID Pemesanan anda     		: "); fflush(stdin);
	scanf ("%d", &penilaian.idPemesan);
	printf ("\t\t\t\t\t| Masukkan Nama Anda [MAX 12 huruf]		: "); fflush(stdin);
	gets (penilaian.nama_penilai);
	printf ("\t\t\t\t\t| Masukkan Tanggal Hari Ini [DD/MM/YYYY] : "); fflush(stdin);
	scanf ("%d/%d/%d", &penilaian.tglPenilaian, &penilaian.blnPenilaian, &penilaian.thnPenilaian);
	printf ("\t\t\t\t\t| Masukkan rating anda, berikut detail rating\n");
	printf ("\t\t\t\t\t| 1. Sangat Kurang\n");
	printf ("\t\t\t\t\t| 2. Kurang\n");
	printf ("\t\t\t\t\t| 3. Cukup Memuaskan\n");
	printf ("\t\t\t\t\t| 4. Memuaskan\n");
	printf ("\t\t\t\t\t| 5. Sangat Memuaskan\n");
	masukkanUlang :
	printf ("\t\t\t\t\t| Masukkan Rating [1-5]                  : "); fflush(stdin);
	scanf  ("%d", &penilaian.rating);
	if (penilaian.rating >=6){
		printf ("\t\t\t\t\t| Beri Rating yang Sesuai pada Opsi !\n"); fflush(stdin);
		goto masukkanUlang ;
	}
	printf ("\t\t\t\t\t| Beri Komentar [MAX 200 huruf]          : "); fflush(stdin);
	gets (penilaian.komentar);
	
	fwrite(&penilaian, sizeof(penilaian), 1, dtpenilaian);
	fclose(dtpenilaian);
	
	printf ("\t\t\t\t\t                             DATA TELAH DISIMPAN\n");
	printf ("\t\t\t\t\t                 TERIMAKASIH TELAH BERI RATING DAN KOMENTAR\n");
	printf ("\t\t\t\t\t                       SEMOGA HARI MU MENYENANGKAN ^_^ \n");
	tekan1Lagi :
	printf ("\t\t\t\t\t   Kembali ke Menu Tekan 1 : ");
	scanf ("%d", &tekan1);
	if (tekan1=1){
		menu_pengunjung ();
	}
	else {
		printf ("\t\t\t\t\t  Silahkan tekan ulang 1");
		goto tekan1Lagi;
	}
  }	
}


//=======================================================================//
//****         Fungsi Untuk Menampilkan Penilaian Villa Anyelir      ****//
//=======================================================================//
// Nama Fungsi    : tampilanPenilaian                                    //
// Input Argumen  : int pilih1                                           //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan penilaian     //
//                  pengunjung terhadap villa anyelir                    //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void tampilanPenilaian (){
	int pilih1;
	system ("cls");
	printf ("|======================================================================================================================================================================|\n");
    printf ("|                                                               PENILAIAN DARI PENGUNJUNG VILLA ANYELIR                                                                |\n");
    printf ("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf ("| ID Pemesan  |         Nama        |        Rating [1-5]       | Tgl Beri Rating  |                                         Komentar                                  |\n");
    printf ("|-------------|---------------------|---------------------------|------------------|-----------------------------------------------------------------------------------|\n");
    FILE*dtpenilaian ; // Membuat pointer dtpesan untuk menunjuk pada file "datapesan.txt"
    dtpenilaian = fopen ("datapenilaian.txt", "rt"); //membuka file "datapesan.txt" dengan rt
    if (dtpenilaian== NULL ){ // Melakukan Pengecekan apakah pointer dtpesan menunjuk kepada file yang dituju ("datapesan.txt")
		printf("\t\t\t| FILE TIDAK DAPAT DIBUKA!\r\n");
		menu_pengunjung();
	}
		/* Ambil isi file ngenggunakan fungsi fread(), lalu tampilkan ke layar */
	while ((fread(&penilaian, sizeof(penilaian), JUM_BLOK, dtpenilaian)) == JUM_BLOK )
	printf ("      %d            %-12s              %d                    %d/%d/%d              %-200s", penilaian.idPemesan, penilaian.nama_penilai, penilaian.rating, penilaian.tglPenilaian, penilaian.blnPenilaian, penilaian.thnPenilaian, penilaian.komentar);
    fclose(dtpenilaian);
	printf ("\n|======================================================================================================================================================================|\n");
    tekan1 :
    printf ("  Tekan 1 untuk balik ke menu pengunjung      : ") ;
	scanf  ("%d", &pilih1);
	if (pilih1== 1) //jika menekan 1 maka akan diarahkan pada menu pengunjung dengan memanggil fungsi menu_pengunjung
		menu_pengunjung ();
	else  //jika menekan selain 1 maka akan diminta untuk mengetik 1 sampai benar
		printf ("\t\t\t\t\t| Silahkan ketik ulang 1 \n"); 
		goto tekan1 ;
}	

//=======================================================================//
//****      Fungsi Untuk Menampilkan List Villa Untuk Pengunjung     ****//
//=======================================================================//
// Nama Fungsi    : list_villa_pengunjung                                //
// Input Argumen  : int pilih                                            //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan list villa    //
//                  pada pengunjung                                      //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2021                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void list_villa_pengunjung (){
	int pilih ; //deklarasi variabel pilih pada fungsi list_villa_pengunjung bertipe data integer
	list_villa (); //memanggil fungsi list_villa
    printf ("|                                                                PROSES PEMESANAN HARAP PANGGIL ADMIN                                                                  |\n");
    printf ("|======================================================================================================================================================================|\n");
    masukkan1 :
    printf ("| Tekan 1 untuk kembali ke menu pengunjung      : ") ; //input memasukkan atau tekan 1
	scanf  ("%d", &pilih);
	if (pilih== 1){ //jika tekan 1 maka akan mengarah pada fungsi menu_pengunjung
	
		menu_pengunjung ();
	}
	else { //jika user salah memilih maka akan kembali pada masukkan 1
		printf ("\t\t\t| Silahkan ketik ulang 1 \n");
		goto masukkan1 ; //kembali pada masukkan1
	}
}

//=======================================================================//
//****          Fungsi Untuk Menampilkan Cara Pesan Villa            ****//
//=======================================================================//
// Nama Fungsi    : cara_pesan_villa                                     //
// Input Argumen  : int opsi                                             //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk menampilkan cara pemesanan//
//                  villa anyelir                                        //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 10-12-2020                               Tgl: -               //
// Gusti Ayu Wahyu Whurapsari - 2105551042                               //
// Kelas B                                                               //
//=======================================================================//
void cara_pesan_villa (){
	system ("cls");
	printf ("\n\n");
	int opsi ;
	printf ("\t\t\t\t\t|===========================================================|\n");
    printf ("\t\t\t\t\t|                  PEMESANAN VILLA ANYELIR                  |\n");
    printf ("\t\t\t\t\t|===========================================================|\n");
    printf ("\t\t\t\t\t|Berikut adalah hal yang harus anda ketahui bila ingin      |\n");
    printf ("\t\t\t\t\t|memesan Villa Anyelir :                                    |\n");
    printf ("\t\t\t\t\t|1. Pemesanan dilayani oleh admin / pegawai  villa anyelir  |\n");
    printf ("\t\t\t\t\t|2. Setiap memesan harus persiapkan DP sesuai dengan        |\n");
    printf ("\t\t\t\t\t|   DP minimal masing-masing villa (DP bisa dilihat pada    |\n");
    printf ("\t\t\t\t\t|   menu list villa)                                        |\n");
    printf ("\t\t\t\t\t|3. Setiap pemesanan akan dikenakan biaya admin Rp.2000.00  |\n");
    printf ("\t\t\t\t\t|4. Pemesan akan dikenakan deposito sebesar Rp.500.000.00   |\n");
    printf ("\t\t\t\t\t|   deposito akan dikembalikan saat check out bila tidak ada|\n");
    printf ("\t\t\t\t\t|   kerusakan barang atau fasilitas saat menempati villa    |\n");
    printf ("\t\t\t\t\t|5. Waktu check in setiap villa sama pukul 14.00 WITA dan   |\n");
    printf ("\t\t\t\t\t|   waktu check out pukul 12.00 WITA                        |\n");
    printf ("\t\t\t\t\t|6. Lama waktu menginap semua villa sama yakni 2 hari 1     |\n");
    printf ("\t\t\t\t\t|   malam, bila ingin menambah hari maka harus memesan lagi |\n");
    printf ("\t\t\t\t\t|===========================================================|\n");
    opsi1 :
	printf ("\t\t\t\t\t  Kembali Tekan 1 : ");
    scanf ("%d", &opsi);
    if (opsi==1){ //jika menekan 1 maka akan mengarah ke menu_pengunjung
    	menu_pengunjung ();
	}
	else //jika menekan selain 1 akan diminta ulang menekan
		printf ("\t\t\t\t\t| Silahkan ketik ulang 1 \n");
		goto opsi1 ; //kembali pada opsi
}

