#include <iostream>
#include <string>
#include <clocale>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

#define MAX_SAYI 20

struct Siparis {
    int siparis_id;
    string musteri_adi;
    string tup_tipi;
    int adet;
    double toplam_ucret;
};

Siparis kayitlar[MAX_SAYI];
int toplam_siparis = 0;

string hazir_musteriler[] = {"Ahmet Yilmaz", "Ayse Demir", "Mehmet Kaya", "Fatma Celik", "Hasan Ozturk"};
string hazir_tupler[] = {"12kg Mutfak", "2kg Piknik", "12kg Mutfak", "45kg Sanayi", "2kg Piknik"};

void dosyaya_kaydet() {
    ofstream dosya("tupcu_defteri.txt");
    if (dosya.is_open()) {
        dosya << "ID | Musteri | Tup Tipi | Adet | Ucret" << endl;
        for (int i = 0; i < toplam_siparis; i++) {
            if (kayitlar[i].musteri_adi != "-IPTAL-") {
                dosya << kayitlar[i].siparis_id << " | " 
                      << kayitlar[i].musteri_adi << " | " 
                      << kayitlar[i].tup_tipi << " | " 
                      << kayitlar[i].adet << " Adet | "
                      << kayitlar[i].toplam_ucret << " TL" << endl;
            }
        }
        dosya.close();
    }
}

void verileri_yukle() {
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        kayitlar[i].musteri_adi = hazir_musteriler[i];
        kayitlar[i].tup_tipi = hazir_tupler[i];
        kayitlar[i].siparis_id = 100 + i;
        kayitlar[i].adet = (rand() % 3) + 1;
        
 	if(kayitlar[i].tup_tipi == "2kg Piknik") 
            kayitlar[i].toplam_ucret = kayitlar[i].adet * 80;
        else 
            kayitlar[i].toplam_ucret = kayitlar[i].adet * 350;

        toplam_siparis++;
    }
}

void siparis_ekle() {
    system("cls");
    if (toplam_siparis >= MAX_SAYI) {
        cout << "Siparis defteri doldu, daha fazla kayit alinamaz!\n";
        return;
    }
    
    bool yer_doldu = false;
    int s_id, s_adet;
    string s_musteri, s_tup;
    double s_ucret;

    cout << "\n--- Yeni Tup Siparisi ---\n";
    cout << "Siparis No (ID): "; cin >> s_id;
    cin.ignore();
    cout << "Musteri Adi Soyadi: "; getline(cin, s_musteri);
    cout << "Tup Tipi (Mutfak/Piknik/Sanayi): "; getline(cin, s_tup);
    cout << "Adet: "; cin >> s_adet;
    cout << "Toplam Alinan Ucret: "; cin >> s_ucret;

 	for (int a = 0; a < toplam_siparis; a++) {
        if (kayitlar[a].musteri_adi == "-IPTAL-") {
            kayitlar[a].siparis_id = s_id;
            kayitlar[a].musteri_adi = s_musteri;
            kayitlar[a].tup_tipi = s_tup;
            kayitlar[a].adet = s_adet;
            kayitlar[a].toplam_ucret = s_ucret;
            yer_doldu = true; 
            break; 
        }
    }

 	if (!yer_doldu) {
        kayitlar[toplam_siparis].siparis_id = s_id;
        kayitlar[toplam_siparis].musteri_adi = s_musteri;
        kayitlar[toplam_siparis].tup_tipi = s_tup;
        kayitlar[toplam_siparis].adet = s_adet;
        kayitlar[toplam_siparis].toplam_ucret = s_ucret;
        toplam_siparis++;
    }

    cout << "Siparis basariyla sisteme girildi.\n";
    dosyaya_kaydet();
}

void siparis_ara(string isim) {
    system("cls");
    bool bulundu = false;
    if (isim == "") {
        cin.ignore(1000, '\n');
        cout << "\nAranacak Musteri Ismi: ";
        getline(cin, isim);
    }

    cout << "\n--- Arama Sonuclari ---\n";
    for (int k = 0; k < toplam_siparis; k++) {
      	if (isim == kayitlar[k].musteri_adi && kayitlar[k].musteri_adi != "-IPTAL-") {
            cout << "Siparis No: " << kayitlar[k].siparis_id << endl;
            cout << "Musteri: " << kayitlar[k].musteri_adi << endl;
            cout << "Urun: " << kayitlar[k].tup_tipi << " (" << kayitlar[k].adet << " Adet)" << endl;
            cout << "Tutar: " << kayitlar[k].toplam_ucret << " TL" << endl;
            cout << "-------------------------" << endl;
            bulundu = true;
        }
    }

    if (!bulundu) cout << "\n'" << isim << "' adina ait aktif siparis bulunamadi.\n";
}

void listeyi_dok() {
    system("cls");
    double toplam_ciro = 0;
    int toplam_tup_sayisi = 0;

    cout << "\nGUNLUK TUP SATIS LISTESI:\n";
    cout << "ID  | MUSTERI            | URUN TIPI       | ADET | TUTAR\n";
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < toplam_siparis; i++) {
     	if (kayitlar[i].musteri_adi != "-IPTAL-") {
            cout << kayitlar[i].siparis_id << " | " 
                 << kayitlar[i].musteri_adi << "\t | " 
                 << kayitlar[i].tup_tipi << "\t | " 
                 << kayitlar[i].adet << "    | "
                 << kayitlar[i].toplam_ucret << " TL" << endl;
            
            toplam_ciro += kayitlar[i].toplam_ucret;
            toplam_tup_sayisi += kayitlar[i].adet;
        }
    }
    cout << "------------------------------------------------------------\n";
    cout << "Toplam Satilan Tup: " << toplam_tup_sayisi << " Adet" << endl;
    cout << "Kasadaki Toplam Para (Ciro): " << toplam_ciro << " TL" << endl;
}

void siparis_sil(string isim) {
    system("cls");
    bool silindi = false;
    if (isim == "") {
        cin.ignore(1000, '\n');
        cout << "\nIptal Edilecek Musteri Ismi: ";
        getline(cin, isim);
    }

    for (int d = 0; d < toplam_siparis; d++) {
        if (isim == kayitlar[d].musteri_adi && kayitlar[d].musteri_adi != "-IPTAL-") {
           	kayitlar[d].musteri_adi = "-IPTAL-";
            kayitlar[d].tup_tipi = "-IPTAL-";
            kayitlar[d].siparis_id = 0;
            kayitlar[d].adet = 0;
            kayitlar[d].toplam_ucret = 0;
            silindi = true;
            cout << "\nKayit (ID: " << kayitlar[d].siparis_id << ") basariyla silindi." << endl;
         	break; 
        }
    }
    
    if (silindi) {
        dosyaya_kaydet();
    } else {
        cout << "\nAranan musteri bulunamadigi icin iptal islemi yapilamadi!" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Turkish");
    cout << "Tupcu Stok ve Musteri Takip Sistemi Yukleniyor...";
	verileri_yukle();
    system("cls");
    
    int secim = 0;
    while (secim != 5) {
        cout << "\n=== TUPCU OTOMASYONU ===\n";
        cout << "1. Siparis Ekle\n";
        cout << "2. Musteri Ara\n";
        cout << "3. Satis Listesi ve Ciro\n";
        cout << "4. Siparis Iptal Et (Sil)\n";
        cout << "5. Kaydet ve Cikis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1: siparis_ekle(); break;
            case 2: siparis_ara(""); break;
            case 3: listeyi_dok(); break;
            case 4: siparis_sil(""); break;
        }
    }

    dosyaya_kaydet();
    cout << "Veriler 'tupcu_defteri.txt' dosyasina kaydedildi. Iyi gunler!";
    return 0;
}
