#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///150202114 - Nedret Gegeoglu
///140202121 - Selda Yapal

struct ogrenci {
    int ogrNo;
	int k_sirasi;
	char ad[20];
	char soyad[30];
	char ogretim[5];
};

int satirNoBul();
void atama();
int taraVeDuzenle();
void fonk_devam();

int main()
{
    struct ogrenci ogr[1000];

	atama(ogr);
	fonk_devam(ogr);

	return 0;
}

int satirNoBul()
{
    char cumle[150];
    int satir=0;

    FILE *dosya;
	dosya=fopen("text/ogrenci_kayit_bilgileri.txt","r");

    ///txt satir sayisini verir
    while (fgets(cumle,150,dosya)!= NULL)
    {
		satir++;
	}
	fclose(dosya);

	return satir;
}
int taraVeDuzenle(struct ogrenci *ogr)
{
    ///____________________________________AYNI ISIM TARAMA ISLEMLERI___________________________________///

    printf("\nListede birden fazla kez adi gecenler: \n\n");
    int i,j,k;
    int satir=satirNoBul();
    int aKontrol=0;
    int sKontrol=0;
    int yakalanan=0;
    yakalanan-=ogr[900].ogrNo;

    for(i=0;i<satir-yakalanan;i++)
    {
        for(j=i+1;j<satir-yakalanan;j++)
        {
            if((ogr[i].ogrNo==ogr[j].ogrNo) && ogr[i].ogrNo==0)
            {
                aKontrol=strcmp(ogr[i].ad,ogr[j].ad);
                sKontrol=strcmp(ogr[i].soyad,ogr[j].soyad);

                if(aKontrol==0 && sKontrol==0)
                {
                    printf("(hata ismi: isim soyisim benzerligi)\t%d ogr numarali %s %s birden fazla kaydedilmis\n",ogr[i].ogrNo,ogr[i].ad,ogr[i].soyad);
                    yakalanan++;

                    for(k=j;k<satir-yakalanan;k++)
                    {
                        strcpy(ogr[k].ad," ");
                        strcpy(ogr[k].ad,ogr[k+1].ad);

                        strcpy(ogr[k].soyad," ");
                        strcpy(ogr[k].soyad,ogr[k+1].soyad);

                        strcpy(ogr[k].ogretim," ");
                        strcpy(ogr[k].ogretim,ogr[k+1].ogretim);

                        ogr[k].k_sirasi=ogr[k+1].k_sirasi;
                        ogr[k].ogrNo=ogr[k+1].ogrNo;
                    }
                }

            }
            else if((ogr[i].ogrNo==ogr[j].ogrNo) && ogr[i].ogrNo!=0)
            {
                printf("(hata ismi: esit ogr numarasi)\t\t%3d ogr numarali %s %s birden fazla kaydedilmis\n",ogr[i].ogrNo,ogr[i].ad,ogr[i].soyad);
                yakalanan++;

                for(k=j;k<satir-yakalanan;k++)
                    {
                        strcpy(ogr[k].ad," ");
                        strcpy(ogr[k].ad,ogr[k+1].ad);

                        strcpy(ogr[k].soyad," ");
                        strcpy(ogr[k].soyad,ogr[k+1].soyad);

                        strcpy(ogr[k].ogretim," ");
                        strcpy(ogr[k].ogretim,ogr[k+1].ogretim);

                        ogr[k].k_sirasi=ogr[k+1].k_sirasi;
                        ogr[k].ogrNo=ogr[k+1].ogrNo;
                    }
            }

        }

    }
    printf("\nListenin Guncellenmis Hali:\n\n");
    printf("     OgrNo\t\tAd\t\tSoyad\t  KayitSirasi\tOgretimTuru\n\n");

    ///_________________________________________OGR NO DUZENLEME__________________________________________///

    ///Ogrno 0 olanlara numara verme islemi
    int ogretim1;
    int ogretim2;

    for(i=0;i<(satir-yakalanan);i++)
    {
        ogretim1=5;
        ogretim2=5;

        if(ogr[i].ogrNo==0)
        {
            ogretim1=strcmp(ogr[i].ogretim,"I");
            ogretim2=strcmp(ogr[i].ogretim,"II");

            if(ogretim1==0)
            {
                ogr[i].ogrNo=(1701000)+(ogr[i].k_sirasi);
            }
            else if(ogretim2==0)
            {
                ogr[i].ogrNo=(1702000)+(ogr[i].k_sirasi);
            }
        }
    }

    ///Ogrencilerin kayit sirasi gunceleme islemi
    for(i=0;i<(satir-yakalanan);i++)
    {
        if((ogr[i].ogrNo%1000)!=ogr[i].k_sirasi)
        {
            ogr[i].k_sirasi=ogr[i].ogrNo%1000;
        }
    }
    for(i=0;i<(satir-yakalanan)-1;i++)
    {
        printf("%3d. %7d %15s %15s %10d %15s\n",i,ogr[i].ogrNo,ogr[i].ad,ogr[i].soyad,ogr[i].k_sirasi,ogr[i].ogretim);
    }

    return yakalanan;
}
void atama(struct ogrenci *ogr)
{
	char cumle[150];
	char buf[150];
	int satir=0;
	int i,x;

	FILE *dosya;
	dosya=fopen("text/ogrenci_kayit_bilgileri.txt","r");

	satir=satirNoBul();
	printf("satir sayisi: %d\n",satir);

    /// dosya basina gider ve ilk satiri yazdirir
	fseek(dosya,0,SEEK_SET);
	fgets(cumle,150,dosya);

	for(i=0;i<satir;i++)
    {
        fscanf(dosya, "%d", &x);
        if(x<1000000)
        ogr[i].ogrNo=0;
        else
        ogr[i].ogrNo=x;

        fscanf(dosya, "%99s", &buf);
        strcpy(ogr[i].ad,buf);

        fscanf(dosya, "%99s", &buf);
        strcpy(ogr[i].soyad,buf);

        fscanf(dosya, "%d", &x);
        ogr[i].k_sirasi=x;

        fscanf(dosya, "%99s", &buf);
        strcpy(ogr[i].ogretim,buf);
    }
    int yeni_kayit=0;
    char isim[20];
    char soyisim[30];
    char ogretim_turu[2];
    int no;
    int kayit_sira;
    int yeni_kayit_indis=0;
    int tekrar=0;

    printf("yeni ogrenci kaydi yapmak istiyor musunuz ?\nEvet: 1 / Hayir: 2 ");
    scanf("%d",&yeni_kayit);

    ///yeni ogrenci kayit islemleri
    while(yeni_kayit!=2)
    {
        tekrar=0;
        no:
        printf("ogrenci no girin (ogr numarasi yoksa 0 girin): ");
        scanf("%d",&no);

        for(i=0;i<satir-1;i++)
        {
            if(no!=0 && ogr[i].ogrNo==no)
            {
                tekrar=1;
            }

        }
        if(tekrar==1)
        {
            printf("sistemde kayitli olan bir ogrenci numarasi girdiniz.(Hata: Kayitli ogr no)\n\n");
            goto no;
        }
        else if(tekrar==0)
        {
        ogr[satir-1].ogrNo=no;
        }

        printf("ogrenci adi girin: ");
        scanf("%s",&isim);
        strcpy(ogr[satir-1].ad,isim);

        printf("\nogrenci soyadi girin: ");
        scanf("%s",&soyisim);
        strcpy(ogr[satir-1].soyad,soyisim);

        if(no!=0)
        {
            printf("Kayit edilen ogrencinin ogrenci numarasi mevcuttur, ogretim turu giremezsiniz (Otomatik atanir)\n\n");

            if(ogr[satir-1].ogrNo%100000<2000)
                strcpy(ogr[satir-1].ogretim,"I");
            else if(ogr[satir-1].ogrNo%100000>2000)
                 strcpy(ogr[satir-1].ogretim,"II");


        }
        else if(no==0)
        {
        printf("\nogretim turunu girin (I/II): ");
        scanf("%s",&ogretim_turu);
        strcpy(ogr[satir-1].ogretim,ogretim_turu);
        }

        if(no!=0)
        {
            printf("Kayit edilen ogrencinin ogrenci numarasi mevcuttur, kayit sirasi giremezsiniz (Otomatik atanir)\n\n");
            ogr[satir-1].k_sirasi=ogr[satir-1].ogrNo%1000;
        }

        if(no==0)
        {
        kayit:
        printf("\nogrenci kayit sirasini girin: ");
        scanf("%d",&kayit_sira);
        ogr[satir-1].k_sirasi=kayit_sira;

            for(i=0;i<satir-1;i++)
            {
                if(ogr[i].ogrNo==0 && ogr[i].k_sirasi==kayit_sira)
                {
                    printf("ayni seneye ait ayni kayit numarasini girdiniz(Hata: Var olan kayit numarasi) \n");
                    goto kayit;
                }
            }
        }
        satir++;
        yeni_kayit_indis++;

        printf("yeni ogrenci kaydi yapmak istiyor musunuz ?\nEvet: 1 / Hayir: 2 ");
        scanf("%d",&yeni_kayit);
    }

    ///yeni kayit indisi ogr no ile tasimak
    ogr[900].ogrNo=yeni_kayit_indis;

    printf("\n    %s\n",cumle);

    ///struct ogrenciye aktarilan ogrencileri listeler
    for(i=0;i<satir-1;i++)
    {
	printf("%3d. %7d %15s %15s %10d %15s\n",i+1,ogr[i].ogrNo,ogr[i].ad,ogr[i].soyad,ogr[i].k_sirasi,ogr[i].ogretim);
    }

	fclose(dosya);

}
void fonk_devam(struct ogrenci *ogr)
{

     int satir=satirNoBul();
     int yakalanan=taraVeDuzenle(ogr);

    ///________________________________OGR No Sirala (kucukten buyuge)____________________________///
     int sirala[satir-yakalanan];
     int sirala_indis=1;
     int en_buyuk=2000000;
     int en_kucuk=2000000;
     int indis;
     int i,j,k,z;

             ///en kucuk eleman bulundu
             for(i=0;i<(satir-yakalanan)-1;i++)
             {
                 if(ogr[i].ogrNo<en_kucuk)
                 {
                     en_kucuk=ogr[i].ogrNo;
                     sirala[0]=i;
                 }
             }

     for(i=0;i<(satir-yakalanan)-1;i++)
     {
         for(j=0;j<(satir-yakalanan)-1;j++)
         {
             ///en kucukten buyuk, en buyukten kucuk araligi
             if(ogr[j].ogrNo>en_kucuk && ogr[j].ogrNo<en_buyuk)
             {
                 en_buyuk=ogr[j].ogrNo;
                 sirala[sirala_indis]=j;
                 indis=j;
             }
         }
         en_kucuk=ogr[indis].ogrNo;
         sirala_indis++;
         en_buyuk=2000000;
     }

     ///kucukten buyuge sirala dizisini yazdirir
    /* for(i=0;i<(satir-yakalanan)-1;i++)
     {
         printf("%d\n",sirala[i]);
     }
*/
     int ogretim1;
     int ogretim2;

    printf("\nListenin Ogrenci Numaralari Kucukten Buyuge Siralanmis Hali:\n\n");
    printf("     OgrNo\t\tAd\t\tSoyad\t  KayitSirasi\tOgretimTuru\n\n");
     for(i=0;i<(satir-yakalanan)-1;i++)
    {
        printf("%3d. %7d %15s %15s %10d %15s\n",i,ogr[sirala[i]].ogrNo,ogr[sirala[i]].ad,ogr[sirala[i]].soyad,ogr[sirala[i]].k_sirasi,ogr[sirala[i]].ogretim);
    }

    ///__________________________________Ogrencileri Siniflara Ayirma Islemleri_________________________________///

    ///1. ve 2. ogretim ayirma islemi

    int kontrol=5;
    int ogretim_bir=0,ogretim_iki=0;
    ///birinci ve ikinci ogretim dizilerine struct uzerinden indis atamasi yapar
    int ogr_bir[200];
    int ogr_iki[200];

    for(i=0;i<(satir-yakalanan)-1;i++)
    {
        ogretim1=5;
        ogretim2=5;

        ogretim1=strcmp(ogr[i].ogretim,"I");
        ogretim2=strcmp(ogr[i].ogretim,"II");

        if(ogretim1==0)
        {
            ogr_bir[ogretim_bir]=i;
            ogretim_bir++;
        }
        if(ogretim2==0)
        {
            ogr_iki[ogretim_iki]=i;
            ogretim_iki++;
        }
    }
    printf("\ntoplam kayitli ogrenci sayisi: %d\n",satir-yakalanan-1);
    printf("1. ogretimde: %d adet ogrenci mevcut \n2. ogretimde: %d adet ogrenci mevcut\n\n",ogretim_bir,ogretim_iki);

    printf("kac sinif olacak: ");
    int s_adet;
    scanf("%d",&s_adet);

    int esit_dagilim1=ogretim_bir/s_adet;
    int esit_dagilim2=ogretim_iki/s_adet;

    printf("\n1. ogretim icin sinif basina ogrenci ortalamasi (Esit Sinif Dagilimi) : %d\n",esit_dagilim1);
    printf("2. ogretim icin sinif basina ogrenci ortalamasi (Esit Sinif Dagilimi) : %d\n\n",esit_dagilim2);

    int sinif[s_adet];
    printf("sinif mevcutlarini girin:\n");

    for(i=0;i<s_adet;i++)
    {
        printf("%d. sinif mevcudu: ",i+1);
        scanf("%d",&sinif[i]);
    }

    FILE *dosya;
    char sinif_birinci[50];
    char sinif_ikinci[50];

    ///Her sinif ve ogretime ait text dosyasi olusturma islemleri
    for(i=0;i<s_adet;i++)
    {
        sprintf(sinif_birinci,"sonuc/sinif%d_ogr1.txt",i+1);
        dosya=fopen(sinif_birinci,"w");
        fprintf(dosya,"OGRETIM 1 SINIF %d SINIF LISTESI:\n\n",i+1);
        fclose(dosya);

        sprintf(sinif_ikinci,"sonuc/sinif%d_ogr2.txt",i+1);
        dosya=fopen(sinif_ikinci,"w");
        fprintf(dosya,"OGRETIM 2 SINIF %d SINIF LISTESI:\n\n",i+1);
        fclose(dosya);
    }

    ///siniflara atamalari yap
    ///esit dagilim

    int kalan1=ogretim_bir%s_adet;
    int kalan2=ogretim_iki%s_adet;
    int arti=0;
    sirala_indis=0;

    int ogr_bir_kb[ogretim_bir];
    int ogr_iki_kb[ogretim_iki];
    int ogr_bir_indis=0;
    int ogr_iki_indis=0;

    ///birinci ogretim ve ikinci ogretimin kucukten buyuge sirali indis dizisi olusturur

               for(j=0;j<satir-yakalanan-1;j++)
               {
                    for(i=0;i<ogretim_bir;i++)
                    {
                        if(sirala[sirala_indis]==ogr_bir[i])
                        {
                            ogr_bir_kb[ogr_bir_indis]=ogr_bir[i];
                            ogr_bir_indis++;
                        }
                        if(sirala[sirala_indis]==ogr_iki[i])
                        {
                            ogr_iki_kb[ogr_iki_indis]=ogr_iki[i];
                            ogr_iki_indis++;
                        }
                    }
                sirala_indis++;
               }
               /*printf("ogretim bir kucukten buyuge indis: \n");
               for(i=0;i<ogretim_bir;i++)
               {
                   printf("%d. %d\n",i,ogr_bir_kb[i]);
               }*/

    int kb_indis=0;
    int kb_indis2=0;

    ///toplam mevcudu bulur
    int toplam_mevcut=0;

    for(i=0;i<s_adet;i++)
    {
        toplam_mevcut+=sinif[i];
    }

    ///girilen toplam sinif mevcudunun ogrencilerden fazla olmasini saglar
    while(toplam_mevcut<ogretim_bir || toplam_mevcut<ogretim_iki)
    {
        toplam_mevcut=0;
        printf("ogrenciler icin yeterli mevcut bulunmamakta. Tekrar mevcut gir\n");

        printf("kac sinif olacak: ");
        scanf("%d",&s_adet);

        sinif[s_adet];
        printf("sinif mevcutlarini girin:\n");

        for(i=0;i<s_adet;i++)
        {
            printf("%d. sinif mevcudu: ",i+1);
            scanf("%d",&sinif[i]);
        }
        for(i=0;i<s_adet;i++)
        {
            toplam_mevcut+=sinif[i];
        }
    }

    int kucuk_mevcutlu_siniflar1[100];
    int kucuk_mevcutlu_siniflar2[100];
    int kms1=0 , kms2=0;

    int kalan1_adet=0;
    int kalan2_adet=0;

    if((kalan1/s_adet)<=1)
    {
        kalan1_adet=1;
    }
    if((kalan2/s_adet)<=1)
    {
        kalan2_adet=1;
    }
    if((kalan1/s_adet)>1)
    {
        kalan1_adet=kalan1/s_adet;
    }
    if((kalan2/s_adet)>1)
    {
        kalan2_adet=kalan2/s_adet;
    }

    for(i=0;i<s_adet;i++)
    {
        if(esit_dagilim1+kalan1_adet>sinif[i])
        {
            kucuk_mevcutlu_siniflar1[kms1]=i;
            kms1++;
        }
        if(esit_dagilim2+kalan2_adet>sinif[i])
        {
            kucuk_mevcutlu_siniflar2[kms2]=i;
            kms2++;
        }
    }



    int dagilim_tercih=0;
    printf("Esit dagilim icin: 1 / En az sinif dagilimi icin: 2 :");
    scanf("%d",&dagilim_tercih);

    ///_______________________________________ESIT DAGILIM________________________________________///
    if(dagilim_tercih==1)
    {
        printf("\nEsit Dagilim: \n\n");
    /// GIRILEN TUM SINIF MEVCUTLARI ESIT DAGILIM ORTALAMASINDAN BUYUKSE
    if(kms1==0)
    {
    /// 1. ogretim esit dagilim
    for(i=0;i<s_adet;i++)
    {
        sprintf(sinif_birinci,"sonuc/sinif%d_ogr1.txt",i+1);
        dosya=fopen(sinif_birinci,"w");
        fprintf(dosya,"OgrNo\t\t\tAd\t\tSoyad\tKayitSirasi\tOgretimTuru\n\n");

        if(kalan1!=0)
        {
            arti=1;
        }
        else if(kalan1==0)
        {
            arti=0;
        }
        if((esit_dagilim1+arti)<sinif[i])
        {
            for(j=0;j<(esit_dagilim1+arti);j++)
            {
                fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_bir_kb[kb_indis]].ogrNo,ogr[ogr_bir_kb[kb_indis]].ad,ogr[ogr_bir_kb[kb_indis]].soyad,ogr[ogr_bir_kb[kb_indis]].k_sirasi,ogr[ogr_bir_kb[kb_indis]].ogretim);
                kb_indis++;
            }
        }
        fclose(dosya);

        if(kalan1!=0){
        kalan1--;
        }
    }
    printf("\n1. ogretim ogrencileri basari ile yerlestirilmistir. (Esit Sinif Dagilimi)\n");
    }
        ///ogretim iki kb listele
        /*printf("\n");
        for(i=0;i<ogretim_iki;i++)
            printf("ogretim 2 kb %d. %d\n",i,ogr_iki_kb[i]);
*/
    ///2. ogretim esit dagilim
    if(kms2==0)
    {

    for(i=0;i<s_adet;i++)
    {
        sprintf(sinif_ikinci,"sonuc/sinif%d_ogr2.txt",i+1);
        dosya=fopen(sinif_ikinci,"w");
        fprintf(dosya,"OgrNo\t\t\tAd\t\tSoyad\tKayitSirasi\tOgretimTuru\n\n");

        if(kalan2!=0)
        {
            arti=1;
        }
        else if(kalan2==0)
        {
            arti=0;
        }
        if((esit_dagilim2+arti)<sinif[i])
        {
            for(j=0;j<(esit_dagilim2+arti);j++)
            {
                fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_iki_kb[kb_indis2]].ogrNo,ogr[ogr_iki_kb[kb_indis2]].ad,ogr[ogr_iki_kb[kb_indis2]].soyad,ogr[ogr_iki_kb[kb_indis2]].k_sirasi,ogr[ogr_iki_kb[kb_indis2]].ogretim);
                kb_indis2++;
            }
        }
        fclose(dosya);

        if(kalan2!=0){
        kalan2--;
        }
    }
    printf("2. ogretim ogrencileri basari ile yerlestirilmistir. (Esit Sinif Dagilimi)\n");
    }
    printf("\n");

    if(kms1!=0)
    {
        int ogr1_ort=ogretim_bir/s_adet;;
        int ogr2_ort=ogretim_iki/s_adet;

        int ort_buyuk_siniflar1[100];
        for(i=0;i<100;i++)
            ort_buyuk_siniflar1[i]=212;

        int ort_buyuk_siniflar2[100];
        for(i=0;i<100;i++)
            ort_buyuk_siniflar2[i]=212;

        int ort_kucuk_siniflar1[100];
        for(i=0;i<100;i++)
            ort_kucuk_siniflar1[i]=212;

        int ort_kucuk_siniflar2[100];
        for(i=0;i<100;i++)
            ort_kucuk_siniflar2[i]=212;

        int ort_buyuk_indis1=0;
        int ort_buyuk_indis2=0;
        int ort_kucuk_indis1=0;
        int ort_kucuk_indis2=0;
        int gozden_gecirildi=0;

        int atama_yapilan_siniflar1[s_adet];
        int ays_indis1=0;

        int atama_yapilan_siniflar2[s_adet];
        int ays_indis2=0;

        ///1. Ogretim Atama Islemleri
        /// ortalamadan kucuk siniflari atama islemi

            ///1. ogretim ortalamasindan kucuk sinif var mi kontrolu yapar
            for(i=0;i<s_adet;i++)
            {
                ogr1_ort=(ogretim_bir-kb_indis)/(s_adet-ays_indis1);
                gozden_gecirildi=0;

                if(ogr1_ort>=sinif[i])
                {
                    for(j=0;j<s_adet;j++)
                    {
                        if(i==ort_kucuk_siniflar1[j])
                        {
                            gozden_gecirildi=1;
                        }
                    }

                    if(gozden_gecirildi==0)
                    {
                    ort_kucuk_siniflar1[ort_kucuk_indis1]=i;
                    ort_kucuk_indis1++;

                    ///full atama yap
                    atama_yapilan_siniflar1[ays_indis1]=i;

                    for(j=0;j<sinif[i];j++)
                    {
                       sprintf(sinif_birinci,"sonuc/sinif%d_ogr1.txt",i+1);
                       dosya=fopen(sinif_birinci,"a");
                       fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_bir_kb[kb_indis]].ogrNo,ogr[ogr_bir_kb[kb_indis]].ad,ogr[ogr_bir_kb[kb_indis]].soyad,ogr[ogr_bir_kb[kb_indis]].k_sirasi,ogr[ogr_bir_kb[kb_indis]].ogretim);
                       kb_indis++;
                       fclose(dosya);
                    }
                    printf("1. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",atama_yapilan_siniflar1[ays_indis1]+1,kb_indis);
                    ays_indis1++;
                    }
                }
            }

        //printf("\n");
       /* for(i=0;i<ort_kucuk_indis1;i++)
        {
            printf("ortalamadan kucuk siniflar indis(1. Ogretim): %d. %d\n",i+1,ort_kucuk_siniflar1[i]);
        }*/
        int kalan_hesabi=0;

       /* for(i=0;i<s_adet;i++)
            printf("ort buyuk siniflar indis %d. : %d\n",i,ort_buyuk_siniflar1[i]);
*/
        ///ortalamadan buyuk siniflara atama yaptir
        ogr1_ort=(ogretim_bir-kb_indis)/(s_adet-ays_indis1);
        kalan1=(ogretim_bir-kb_indis)%(s_adet-ays_indis1);
        int ekle=0;
            for(i=0;i<s_adet;i++)
            {
                ekle=0;
                if(kalan1>0)
                    kalan_hesabi=1;

                else if(kalan1==0)
                    kalan_hesabi=0;

                gozden_gecirildi=0;

                if(ogr1_ort<=sinif[i])
                {

                    if(ogr1_ort+kalan_hesabi<=sinif[i])
                        ekle=1;

                    else if(ogr1_ort+kalan_hesabi>sinif[i])
                        ekle=0;

                    for(j=0;j<s_adet;j++)
                        {
                            if(i==ort_buyuk_siniflar1[j])
                            {
                                gozden_gecirildi=1;
                            }
                        }

                        if(gozden_gecirildi==0)
                        {
                            ort_buyuk_siniflar1[ort_buyuk_indis1]=i;
                            ort_buyuk_indis1++;

                            ///full atama yap
                            atama_yapilan_siniflar1[ays_indis1]=i;

                            for(j=0;j<ogr1_ort+kalan_hesabi;j++)
                            {
                               sprintf(sinif_birinci,"sonuc/sinif%d_ogr1.txt",i+1);
                               dosya=fopen(sinif_birinci,"a");
                               fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_bir_kb[kb_indis]].ogrNo,ogr[ogr_bir_kb[kb_indis]].ad,ogr[ogr_bir_kb[kb_indis]].soyad,ogr[ogr_bir_kb[kb_indis]].k_sirasi,ogr[ogr_bir_kb[kb_indis]].ogretim);
                               kb_indis++;
                               fclose(dosya);
                            }
                            printf("1. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",atama_yapilan_siniflar1[ays_indis1]+1,kb_indis);

                        }
                        kalan1--;
                }
                ays_indis1++;
            }

            /*printf("\n");
            for(i=0;i<ort_buyuk_indis1;i++)
            {
                printf("ortalamadan buyuk siniflar indis(1. Ogretim): %d. %d\n",i+1,ort_buyuk_siniflar1[i]);
            }
*/
        ///2. Ogretim Atama Islemleri
        gozden_gecirildi=0;

            /// ortalamadan kucuk siniflari atama islemi
            printf("\n");
            ///2. ogretim ortalamasindan kucuk sinif var mi kontrolu yapar
            for(i=0;i<s_adet;i++)
            {
                ogr2_ort=(ogretim_iki-kb_indis2)/(s_adet-ays_indis2);
                gozden_gecirildi=0;

                if(ogr2_ort>=sinif[i])
                {
                    for(j=0;j<s_adet;j++)
                    {
                        if(i==ort_kucuk_siniflar2[j])
                        {
                            gozden_gecirildi=1;
                        }
                    }

                    if(gozden_gecirildi==0)
                    {
                    ort_kucuk_siniflar2[ort_kucuk_indis2]=i;
                    ort_kucuk_indis2++;

                    ///full atama yap
                    atama_yapilan_siniflar2[ays_indis2]=i;

                    for(j=0;j<sinif[i];j++)
                    {
                       sprintf(sinif_ikinci,"sonuc/sinif%d_ogr2.txt",i+1);
                       dosya=fopen(sinif_ikinci,"a");
                       fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_iki_kb[kb_indis2]].ogrNo,ogr[ogr_iki_kb[kb_indis2]].ad,ogr[ogr_iki_kb[kb_indis2]].soyad,ogr[ogr_iki_kb[kb_indis2]].k_sirasi,ogr[ogr_iki_kb[kb_indis2]].ogretim);
                       kb_indis2++;
                       fclose(dosya);
                    }
                    printf("2. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",atama_yapilan_siniflar2[ays_indis2]+1,kb_indis2);

                    ays_indis2++;
                    }
                }
            }
        kalan_hesabi=0;

        ///ortalamadan buyuk siniflara atama yaptir
        ogr2_ort=(ogretim_iki-kb_indis2)/(s_adet-ays_indis2);
        kalan2=(ogretim_iki-kb_indis2)%(s_adet-ays_indis2);
            for(i=0;i<s_adet;i++)
            {
                if(kalan2>0)
                    kalan_hesabi=1;

                else if(kalan2==0)
                    kalan_hesabi=0;

                gozden_gecirildi=0;

                if((ogr2_ort+kalan_hesabi)<=sinif[i])
                {
                    for(j=0;j<s_adet;j++)
                        {
                            if(i==ort_buyuk_siniflar2[j])
                            {
                                gozden_gecirildi=1;
                            }
                        }

                        if(gozden_gecirildi==0)
                        {
                            ort_buyuk_siniflar2[ort_buyuk_indis2]=i;
                            ort_buyuk_indis2++;

                            ///full atama yap
                            atama_yapilan_siniflar2[ays_indis2]=i;

                            for(j=0;j<ogr2_ort+kalan_hesabi;j++)
                            {
                               sprintf(sinif_ikinci,"sonuc/sinif%d_ogr2.txt",i+1);
                               dosya=fopen(sinif_ikinci,"a");
                               fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_iki_kb[kb_indis2]].ogrNo,ogr[ogr_iki_kb[kb_indis2]].ad,ogr[ogr_iki_kb[kb_indis2]].soyad,ogr[ogr_iki_kb[kb_indis2]].k_sirasi,ogr[ogr_iki_kb[kb_indis2]].ogretim);
                               kb_indis2++;
                               fclose(dosya);
                            }
                            printf("2. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",atama_yapilan_siniflar2[ays_indis2]+1,kb_indis2);

                        }
                        kalan2--;
                }
                ays_indis2++;
            }

            if(kb_indis==ogretim_bir)
                printf("\n1. Ogretim icin tum ogrenciler basariyla atandi!\n");

            if(kb_indis2==ogretim_iki)
                printf("2. Ogretim icin tum ogrenciler basariyla atandi!\n");

    }

    }
    ///____________________________________EN AZ SINIF DAGILIMI(SORUNSUZ)_______________________________///
    else if(dagilim_tercih==2)
    {
        printf("\nEn az sinif dagilimi:\n\n");
        int buyukten_kucuge_siniflar[s_adet];
        int bk_indis=1;
        int buyuk=0;
        int kucuk=0;

        /// en buyuk eleman
        for(i=0;i<s_adet;i++)
        {
            if(sinif[i]>buyuk)
            {
                buyuk=sinif[i];
                buyukten_kucuge_siniflar[0]=i;
            }
        }
        for(i=0;i<s_adet;i++)
        {
            kucuk=0;
            kontrol=0;

            for(j=0;j<s_adet;j++)
            {
                if(j==buyukten_kucuge_siniflar[0])
                {
                    kontrol=1;
                }
                if(sinif[j]>=kucuk && sinif[j]<sinif[buyukten_kucuge_siniflar[bk_indis-1]])
                {
                    kucuk=sinif[j];
                    buyukten_kucuge_siniflar[bk_indis]=j;
                }
                else if(kontrol==0 && sinif[j]==sinif[buyukten_kucuge_siniflar[bk_indis-1]])
                {
                    buyukten_kucuge_siniflar[bk_indis]=j;
                }


            }
            bk_indis++;
        }

        /*printf("buyukten kucuge sinif indisleri:\n");
        for(i=0;i<s_adet;i++)
            printf("%d. %d\n",i,buyukten_kucuge_siniflar[i]);
*/
            ///EN BUYUK SINIFTAN KUCUGE DOGRU FULL ATAMA ISLEMI
            kb_indis=0;
/*
        printf("ogretim bir: %d\n",ogretim_bir);
        printf("ogretim iki: %d\n",ogretim_iki);
*/
        ///1. ogretim atama
        bitir:

            if(kb_indis!=ogretim_bir)
            {
                 for(i=0;i<s_adet;i++)
                {
                    for(j=0;j<sinif[buyukten_kucuge_siniflar[i]];j++)
                    {
                        if(kb_indis==ogretim_bir)
                        {
                           printf("1. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",buyukten_kucuge_siniflar[i]+1,kb_indis);
                           goto bitir;
                        }
                            sprintf(sinif_birinci,"sonuc/sinif%d_ogr1.txt",buyukten_kucuge_siniflar[i]+1);
                            dosya=fopen(sinif_birinci,"a");
                            //printf("%s \tkod calisiyor: %d\n",sinif_birinci,kb_indis);

                            fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_bir_kb[kb_indis]].ogrNo,ogr[ogr_bir_kb[kb_indis]].ad,ogr[ogr_bir_kb[kb_indis]].soyad,ogr[ogr_bir_kb[kb_indis]].k_sirasi,ogr[ogr_bir_kb[kb_indis]].ogretim);
                            kb_indis++;
                            fclose(dosya);

                    }
                     printf("1. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",buyukten_kucuge_siniflar[i]+1,kb_indis);

                }
            }

            printf("\n");
            ///2. ogretim atama
            bitir2:

            if(kb_indis2!=ogretim_iki)
            {
                 for(i=0;i<s_adet;i++)
                {
                    for(j=0;j<sinif[buyukten_kucuge_siniflar[i]];j++)
                    {
                        if(kb_indis2==ogretim_iki)
                        {
                           printf("2. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",buyukten_kucuge_siniflar[i]+1,kb_indis2);
                           goto bitir2;
                        }
                            sprintf(sinif_ikinci,"sonuc/sinif%d_ogr2.txt",buyukten_kucuge_siniflar[i]+1);
                            dosya=fopen(sinif_ikinci,"a");
                            fprintf(dosya,"%3d. %7d %15s %15s %10d %15s\n",j+1,ogr[ogr_iki_kb[kb_indis2]].ogrNo,ogr[ogr_iki_kb[kb_indis2]].ad,ogr[ogr_iki_kb[kb_indis2]].soyad,ogr[ogr_iki_kb[kb_indis2]].k_sirasi,ogr[ogr_iki_kb[kb_indis2]].ogretim);
                            kb_indis2++;
                            fclose(dosya);
                    }
                     printf("2. Ogretim : atama yapilan sinif: %d\tsiniflara atanilan toplam ogrenci: %d\n",buyukten_kucuge_siniflar[i]+1,kb_indis2);


                }
            }
            if(kb_indis==ogretim_bir)
                printf("\n1. Ogretim icin tum ogrenciler basariyla atandi!\n");

            if(kb_indis2==ogretim_iki)
                printf("2. Ogretim icin tum ogrenciler basariyla atandi!\n");
    }
}
