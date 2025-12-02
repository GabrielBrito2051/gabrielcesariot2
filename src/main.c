#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "qry.h"
#include "arvore.h"
#include "criarSvg.h"

#define PATH_LEN 512
#define FILE_NAME_LEN 256

void get_nome_sem_extensao(char* nome_arq, char* buffer){
    if(!nome_arq) return;
    strcpy(buffer, nome_arq);
    char* ponto = strrchr(buffer,'.');
    if(ponto) *ponto = '\0';
}

char* concatena_caminho_arquivo(char* path, char* file){
    if(file==NULL) return NULL;
    char* full = malloc(1024);

    if(path != NULL && strlen(path)>0){
        char last = path[strlen(path) - 1];
        if(last == '/'){
            sprintf(full, "%s%s", path, file);
        }else{
            sprintf(full,"%s/%s", path, file);
        }
    }else{
        strcpy(full,file);
    }
    return full;
}

int main(int argc, char* argv[])
{
    
    char dirEntrada[PATH_LEN] = " ";
    char dirSaida[PATH_LEN] = " ";
    char nomeArquivoGeo[FILE_NAME_LEN] = " ";
    char nomeArquivoQry[FILE_NAME_LEN] = " ";
    char sortType = 'q';
    int sortParam = 10;
    int hasGeo = 0, hasQry = 0, hasSaida = 0;

    for(int i=1;i<argc;i++){
        if(strcmp(argv[i], "-e")==0 && i+1<argc){
            strcpy(dirEntrada, argv[++i]);
        }
        else if(strcmp(argv[i],"-f")==0 && i+1<argc){
            strcpy(nomeArquivoGeo, argv[++i]);
            hasGeo = 1;
        }
        else if(strcmp(argv[i],"-o")==0 && i+1<argc){
            strcpy(dirSaida, argv[++i]);
            hasSaida = 1;
        }
        else if(strcmp(argv[i],"-q")==0 && i+1<argc){
            strcpy(nomeArquivoQry,argv[++i]);
            hasQry = 1;
        }
        else if(strcmp(argv[i],"-to")==0 && i+1<argc){
            sortType = argv[++i][0];
        }
        else if(strcmp(argv[i],"-i")==0 && i+1<argc){
            sortParam = atoi(argv[++i]);
        }else{
            fprintf(stderr,"Parametro desconhecido ou invalido: %s\n", argv[i]);
            return 1;
        }
    }

    if(hasGeo==0 || hasSaida==0){
        printf("Parametros obrigatorios ausentes\n");
        return 1;
    }

    char* fullGeo = concatena_caminho_arquivo(dirEntrada, nomeArquivoGeo);
    char* fullQry = concatena_caminho_arquivo(dirEntrada, nomeArquivoQry);

    char nomeGeo[FILE_NAME_LEN], nomeQry[FILE_NAME_LEN];
    get_nome_sem_extensao(nomeArquivoGeo, nomeGeo);

    char nomeBase[2*FILE_NAME_LEN + 1];
    if(hasQry==1){
        get_nome_sem_extensao(nomeArquivoQry, nomeQry);
    }else{
        strcpy(nomeBase, nomeGeo);
    }

    FILE* geo;
    FILE* qry;
    FILE* txt;
    FILE* svgGeo;
    FILE* svgQry;

    geo = abre_arquivo_leitura(fullGeo);
    qry = abre_arquivo_leitura(fullQry);
    txt = abre_arquivo_escrita(nomeGeo);

    Lista formas = criar_lista();
    Lista anteparos = criar_lista();
    Estilo ts = criar_estilo("sans", "n", "12");
    int maior_id = 0;

    svgGeo = abre_arquivo_escrita(nomeGeo);
    startSVG(svgGeo);
    
    le_geo(geo, svgGeo, ts, formas, &maior_id);
    fechasvg(svgGeo);

    svgQry = abre_arquivo_escrita(nomeBase);
    startSVG(svgQry);

    leComandoQry(qry, svgQry, txt, formas, anteparos, &maior_id, sortType, sortParam);
    printar_lista(formas, svgQry, ts);
    fechasvg(svgQry);

    fecha_arquivo(svgGeo);
    fecha_arquivo(svgQry);
    fecha_arquivo(qry);
    fecha_arquivo(geo);
    fecha_arquivo(txt);

    destroiListaDeFormas(formas);
    destroiListaDeFormas(anteparos);
    free(ts);

    return 0;
}