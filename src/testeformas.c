#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

int main(){

    Pacote pac = criarPacote();
    char letra;
    scanf("%c",&letra);
    setTipoForma(pac, letra);
    Forma f = criar_circulo(1, 10, 15, 5, "#FFFFFF", "#FF0000");
    setFormaPacote(pac, f);
    tipoforma tipo = getTipoForma(pac);
    Forma forma = getFORMApacote(pac);
    int id = getIDforma(forma, tipo);
    freePacote(pac);

 return 0;
}