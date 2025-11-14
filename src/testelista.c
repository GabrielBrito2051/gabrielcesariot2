#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void print_info(Circulo f){
    printf("ID:%d, X;%lf, Y:%lf, R:%lf, corb:%s, corp:%s\n",getIDcirculo(f),getXcirculo(f),getYcirculo(f),getRcirculo(f),getCORBcirculo(f),getCORPcirculo(f));
}

int main()
{

    Lista l = criar_lista();

    Circulo c = criar_circulo(2,3,5,7,"#FF0000","#00FFFF");
    Pacote pac = criarPacote();
    setTipoForma(pac, 'c');
    setFormaPacote(pac, c);

    Circulo c2 = criar_circulo(11,13,17,19,"#0000FF","#FFFFFF");
    Pacote pac2 = criarPacote();
    setTipoForma(pac2, 'c');
    setFormaPacote(pac2, c2);

    Circulo c3 = criar_circulo(4,6,8,10,"#FF6400","#FFFF00");
    Pacote pac3 = criarPacote();
    setTipoForma(pac3, 'c');
    setFormaPacote(pac3, c3);

    insere_lista(l,pac);
    insere_lista(l,pac2);
    insere_lista(l,pac3);

    int tam = getTAMANHOlista(l);
    printf("TAMANHO:%d\n",tam);

    Pacote pactemp = get_inicio_lista(l);
    Circulo temp = getFORMApacote(pactemp);
    print_info(temp);

    pactemp = get_final_lista(l);
    temp = getFORMApacote(pactemp);
    print_info(temp);

    remove_lista(l,compara_forma, 2);
    
    pactemp = remove_lista(l,compara_forma,11);
    temp = getFORMApacote(pactemp);
    print_info(temp);
    remove_lista(l,compara_forma,5);
    remove_lista(l,compara_forma,4);

    tam = getTAMANHOlista(l);
    printf("TAMANHO:%d\n",tam);

    insere_lista(l, pac);
    insere_lista(l,pac2);
    insere_lista(l,pac3);

    destroiLista(l);

 return 0;
}