
#define OOM -1

#include "tokenizer.h"
#include <string.h>
#include <stdio.h>

int Ttokenizer_crear(TTokenizer* tt)
{
    tt->numero_separadores=0;
    strcpy(tt->separadores[0],"e");
    tt->numero_separadores++;
    strcpy(tt->separadores[1],"y");
    tt->numero_separadores++;
    strcpy(tt->separadores[2],"o");
    tt->numero_separadores++;
    strcpy(tt->separadores[3],"u");
    tt->numero_separadores++;
    strcpy(tt->separadores[4],"si");
    tt->numero_separadores++;
    strcpy(tt->separadores[5],"no");
    tt->numero_separadores++;
  /*  strcpy(tt->separadores[4],"and");
    tt->numero_separadores++;
    strcpy(tt->separadores[5],"or");*/

    return 0;
}

int Ttokenizer_destruir(TTokenizer* tt)
{
    return 0;
}

int esSeparador(TTokenizer* tt,char * palabra)
{ /*esta funcion determina si una palabra es un separador o no*/
int i;

for ( i=0; i< tt->numero_separadores ;i++)
    {
    if(!strcmp(palabra,tt->separadores[i]))
        {
        return TRUE;
        }
     }
return FALSE;
}


int Ttokenizer_analizar(TTokenizer* tt, char* frase, TListaSimple * terminos)
{
    int offset_mayusculas= 'a' - 'A';
    int largo=strlen(frase)-1;
    int i,idx;
    char  buffer_palabra[128]; /*completamente arbitrario*/
   /* char * buffer2;*/


    idx=0;
    buffer_palabra[idx]=0;



    for(i=0;i<=largo;i++)
    {
        if ((frase[i] >= 'A') && (frase[i] <= 'Z'))
            {
                /*es una mayuscula*/
                buffer_palabra[idx]=frase[i] + offset_mayusculas;
                buffer_palabra[idx+1]=0;
                idx++;
            }
        else
            if  ((frase[i] >= 'a') && (frase[i] <= 'z'))
                {   /*minuscula */
                    buffer_palabra[idx]=frase[i];
                    buffer_palabra[idx+1]=0;
                    idx++;
                }
                else
                { /*cualquier otra cosa es un separador*/
                if((idx>0) && !esSeparador(tt,buffer_palabra))
                {

                    /*buffer2=(char*)malloc(strlen(buffer_palabra)+1);
                    strcpy(buffer2,buffer_palabra);*/

                    L_Insertar_Cte(terminos,L_Siguiente,buffer_palabra);
                    /*printf("%s\n",buffer_palabra);*/
                }


                idx=0;
                buffer_palabra[idx]=0;
                }
    }




    return 0;
}
