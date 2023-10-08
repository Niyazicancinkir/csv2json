#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* dosya;
FILE* tempDosya;
FILE* jsonDosya;
int sutun, satir;
void donusturtxt();
char* dosyaAdi;
char* jsonDosyaAdi;
char* header;

typedef struct{
char* eleman[20];
}elemanlar;

int main(int argc, char** argv)
{
 	dosyaAdi =argv[1];
    jsonDosyaAdi= argv[2];
    header = argv[3];

    donusturtxt();
	sutunBul();
	satirBul();

    if (!strcmp("header=ON", argv[3]))
    {
        jsonDonusturHeaderOn();
    }
    else
    {
        jsonDonusturHeaderOff();
    }

    return 0;

}

 void donusturtxt ()
 {
     char satir[100];
     dosya=fopen(dosyaAdi, "r");
     tempDosya=fopen("temp.txt", "w");

     while(!feof(dosya))
    {
        if(fgets(satir,100,dosya))
        {
            fputs(satir,tempDosya);
        }
    }

    fclose(dosya);
    fclose(tempDosya);
 }



int sutunBul()
{
    char temp;
    sutun=1;
    tempDosya=fopen("temp.txt", "r");

    while((temp=fgetc(tempDosya)) != EOF)
    {
        if(temp == ',')
        {
            sutun++;
        }
        else if(temp == '\n')
        {
            return sutun;
        }
    }

    fclose(tempDosya);
}


int satirBul()
{
    char temp;
    satir=0;

    tempDosya=fopen("temp.txt", "r");


    while((temp=fgetc(tempDosya)) != EOF)
    {
        if(temp == '\n')
        {
            satir++;
        }
    }

    return satir;

    fclose(tempDosya);
}


void jsonDonusturHeaderOn()
{
    int i;

	tempDosya = fopen ("temp.txt", "r");

	char* satirlar[satir];
	for(i =0 ; i<satir ; ++i)
    {
        satirlar[i] = malloc(128);
        fscanf(tempDosya, "%127s", satirlar[i]);
    }

    char* kelime;

    FILE* yeniTemp=fopen("yeniTemp.txt","w");

    for(i=0 ; i<satir ; ++i)
    {
        kelime = strtok(satirlar[i], ",");
        while (kelime != NULL)
        {
            fprintf(yeniTemp,"%s\n", kelime);
            kelime = strtok(NULL, ",");
        }
    }

    int boyut=satir*sutun;

    fclose(yeniTemp);

    yeniTemp=fopen("yeniTemp.txt","r");

    elemanlar dizi[satir][sutun];

    int b;
    while(!feof(yeniTemp))
    {
        for(i=0 ; i<satir ; i++)
        {
            for( b=0 ; b<sutun ; b++)
            {
                fscanf(yeniTemp, "%s", dizi[i][b].eleman);
            }
        }
    }

    jsonDosya=fopen(jsonDosyaAdi,"w");

    fprintf(jsonDosya, "[\n");
        for( i=1 ; i<satir ; i++)
        {
            fprintf(jsonDosya, "\t{");
            fprintf(jsonDosya,"\n");
            for( b=0 ; b<sutun ; b++)
            {
                if(sutun-1 == b)
                {
                    fprintf(jsonDosya, "\t\t \"\%s\":\"\%s\"\n",dizi[0][b].eleman, dizi[i][b].eleman);
                }
                else
                {
                    fprintf(jsonDosya, "\t\t \"\%s\":\"\%s\",\n",dizi[0][b].eleman, dizi[i][b].eleman);

                }
            }

            if(satir-1 == i)
            {
                fprintf(jsonDosya, "\t}\n");

            }
            else
            {
                fprintf(jsonDosya, "\t},\n");
            }
        }
    fprintf(jsonDosya, "\n]");

    fclose(jsonDosya);
    fclose(yeniTemp);

	}


	void jsonDonusturHeaderOff()
{
    int i;
	tempDosya = fopen("temp.txt", "r");

	char* satirlar[satir];
	for (i =0 ; i < satir ; ++i)
    {
        satirlar[i] = malloc (128);
        fscanf(tempDosya, "%127s", satirlar[i]);
    }


   char * kelime;

    FILE* yeniTemp=fopen("yeniTemp.txt", "w");

    for(i=0 ; i<satir ; ++i)
    {
        kelime = strtok(satirlar[i], ",");
        while(kelime != NULL)
        {
            fprintf(yeniTemp,"%s\n", kelime);
            kelime = strtok(NULL, ",");
        }
    }

    int boyut=satir*sutun;

    fclose(yeniTemp);

    yeniTemp=fopen("yeniTemp.txt","r");

    elemanlar dizi[satir][sutun];

    int j=0,b;
    while(!feof(yeniTemp))
    {
        for(i=0 ; i<satir ; i++)
        {
            for(b=0 ; b<sutun ; b++)
            {
                fscanf(yeniTemp,"%s", dizi[i][b].eleman);
            }
        }
    }

    jsonDosya=fopen(jsonDosyaAdi,"w");

    int sayilar[sutun];
    for(i=0 ; i<sutun ; i++)
        {
            sayilar[i]=i+1;
        }

    fprintf(jsonDosya, "[\n");
        for(int i=1 ; i<satir ; i++)
        {
            fprintf(jsonDosya, "\t{");
            fprintf(jsonDosya,"\n");
            for(int b=0 ; b<sutun ; b++)
            {
                if(sutun-1 == b)
                {
                    fprintf(jsonDosya, "\t\t \"\Kolon%d\":\"\%s\"\n",sayilar[b], dizi[i][b].eleman);
                }
                else
                {
                    fprintf(jsonDosya, "\t\t \"\Kolon%d\":\"\%s\",\n",sayilar[b], dizi[i][b].eleman);
                }
            }

            if(satir-1 == i)
            {
                fprintf(jsonDosya, "\t}\n");
            }
            else
            {
                fprintf(jsonDosya, "\t},\n");
            }

        }
    fprintf(jsonDosya, "\n]");

    fclose(jsonDosya);
    fclose(yeniTemp);
}
