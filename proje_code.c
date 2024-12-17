#include <stdio.h>//merhaba ilsat
#include<stdlib.h>
#include<string.h>

//Çalışanın verilerini tutmak için yapı tanımladık.
struct isci
{
    unsigned int sicil;
    int saat, dakika;
    char girisCikis;
} calisan;

int main(){
    // Önceden dosyaları açtık.
    FILE *gunluk, *gec, *erken;
    gunluk = fopen("gunluk.dat", "r");
    gec= fopen("gec.dat", "w");
    erken=fopen("erken.dat", "w");

//Dosyaların herhangi biri açılmadığı veya bulunmadığı zaman bilgilendirir ve programı sonlandırır. 
    if( gunluk==NULL||gec==NULL||erken==NULL )
    {
        printf("dosya acma basarisiz!\n");
        return 1;
    }  
    int max_gec_sicil=0;  //En GEÇ GELEN çalışanın sicili
    int max_erken_sicil=0;  //En ERKEN GİDEN çalışanın sicili
    int max_gec_dakika=0;  //En geç gelenin kaç dakıka geciktiği
    int max_erken_dakika=0;  //En erken gidenin kaç dakika erken gittiği 
    int baslama_dakika=9*60; //Başlama saati (09:00) dakikayla
    int bitis_dakika=17*60;  //Bitiş saatı (17:00) dakikayla
    while(fscanf(gunluk,"%d %d:%d %c", &calisan.sicil, &calisan.saat, &calisan.dakika, &calisan.girisCikis)!=EOF)
    {
        int toplam_dakika= (calisan.saat*60)+calisan.dakika;
            //Gecikme dakikalarını hesaplar ve en çok gecikeni bulur
        if(calisan.girisCikis=='<' && toplam_dakika > baslama_dakika)
        {
          int gecikme= toplam_dakika - baslama_dakika;
          if(gecikme>max_gec_dakika)
           {
              max_gec_dakika=gecikme;
              max_gec_sicil=calisan.sicil;
           }
        }
            //Kaç dakika erken gittiğini hesaplar ve en erken gideni bulur
        if(calisan.girisCikis=='>' && toplam_dakika < bitis_dakika)
        {
          int erken_cikis= bitis_dakika - toplam_dakika;
          if(erken_cikis>max_erken_dakika)
           {
             max_erken_dakika=erken_cikis;
             max_erken_sicil=calisan.sicil;
           }
        }
    }
     /*En gec gelenin ve En erken gidenin sicil numaralarını
      ve kaç dakikaya gecikmiş ve erken gitmiş olduklarını dosyalara yazdırır */
    if(max_gec_sicil!=0)
    {
        fprintf(gec, "%d %d\n", max_gec_sicil, max_gec_dakika);
    }
    if(max_erken_sicil!=0)
    {
        fprintf(erken, "%d %d\n", max_erken_sicil, max_erken_dakika);
    }
      // Dosyalar kapatılır
    fclose(gunluk);
    fclose(gec);
    fclose(erken);

printf("basarili!");
    return 0;
}
