#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#include "FuncionesGlobales.h"

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0;i<tam;i++){
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    /// Si se escribieron mas letras de las que entran, se descarta el resto
    /// para que no quede para la proxima pregunta.
    if(i==tam){
        char letra=cin.get();
        while(letra!='\n'){
            letra=cin.get();
        }
    }
    pal[i]='\0';
    fflush(stdin);
}

void cargarTextoObligatorio(const char *mensaje, char *texto, int tam){
    cout<<mensaje;
    cargarCadena(texto, tam);
    while(strlen(texto)==0){
        cout<<"  No puede quedar vacio."<<endl;
        cout<<mensaje;
        cargarCadena(texto, tam);
    }
}

int leerEntero(const char *mensaje){
    char texto[12];
    int numero=0;
    bool valido=false;

    while(!valido){
        cout<<mensaje;
        cargarCadena(texto, 11);

        valido=true;
        numero=0;
        bool negativo=false;
        int i=0, digitos=0;

        if(texto[0]=='-'){
            negativo=true;
            i=1;
        }
        while(texto[i]!='\0'){
            if(texto[i]>='0' && texto[i]<='9'){
                digitos++;
                if(digitos<=9){
                    numero=numero*10+(texto[i]-'0');
                }
            }
            else{
                valido=false;
            }
            i++;
        }
        if(digitos==0 || digitos>9){
            valido=false;
        }
        if(!valido){
            cout<<"  Valor invalido. Ingrese un numero entero."<<endl;
        }
        else if(negativo){
            numero=-numero;
        }
    }
    return numero;
}

float leerFloat(const char *mensaje){
    char texto[12];
    float numero=0;
    bool valido=false;

    while(!valido){
        cout<<mensaje;
        cargarCadena(texto, 11);

        valido=true;
        numero=0;
        bool hayComa=false;
        float divisor=1;
        int digitos=0;

        for(int i=0;texto[i]!='\0';i++){
            if(texto[i]>='0' && texto[i]<='9'){
                digitos++;
                if(digitos<=9){
                    if(!hayComa){
                        numero=numero*10+(texto[i]-'0');
                    }
                    else{
                        divisor=divisor*10;
                        numero=numero+(texto[i]-'0')/divisor;
                    }
                }
            }
            else if((texto[i]=='.' || texto[i]==',') && !hayComa){
                hayComa=true;   /// se acepta 8.5 y 8,5
            }
            else{
                valido=false;
            }
        }
        if(digitos==0 || digitos>9){
            valido=false;
        }
        if(!valido){
            cout<<"  Valor invalido. Ingrese un numero (por ejemplo 8.5)."<<endl;
        }
    }
    return numero;
}

bool confirmar(const char *mensaje){
    char respuesta[2];
    cout<<mensaje<<" (S/N): ";
    cargarCadena(respuesta, 1);
    while(respuesta[0]!='S' && respuesta[0]!='s' && respuesta[0]!='N' && respuesta[0]!='n'){
        cout<<"  Responda S o N: ";
        cargarCadena(respuesta, 1);
    }
    if(respuesta[0]=='S' || respuesta[0]=='s'){
        return true;
    }
    return false;
}

void pasarAMayusculas(char *cad){
    int i;
    for(i=0;cad[i]!='\0';i++){
        if(cad[i]>='a' && cad[i]<='z'){
            cad[i]=cad[i]-32;   /// en ASCII la mayuscula esta 32 lugares antes
        }
    }
}

int compararSinMayusculas(const char *cad1, const char *cad2){
    char copia1[201], copia2[201];
    strcpy(copia1, cad1);
    strcpy(copia2, cad2);
    pasarAMayusculas(copia1);
    pasarAMayusculas(copia2);
    return strcmp(copia1, copia2);
}

void ponerCeroVector(int *v, int tam){
    int i;
    for(i=0;i<tam;i++){
        v[i]=0;
    }
}

void lineaDoble(){
    cout<<"======================================================="<<endl;
}

void lineaSimple(){
    cout<<"-------------------------------------------------------"<<endl;
}

void titulo(const char *texto){
    system("cls");
    lineaDoble();
    cout<<"          BOLETERA - BOLETERIA DE CINE"<<endl;
    cout<<"          "<<texto<<endl;
    lineaDoble();
}
