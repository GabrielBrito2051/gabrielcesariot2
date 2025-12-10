#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "qry.h"
#include "arvore.h"
#include "criarSvg.h"

#define PATH_LEN 512
#define FILE_NAME_LEN 256

int main(int argc, char* argv[])
{
    
    char dirEntrada[PATH_LEN] = "";
    char dirSaida[PATH_LEN] = "";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    char onlyQry[FILE_NAME_LEN] = "";
    char baseQry[FILE_NAME_LEN]="";
    char baseGeo[FILE_NAME_LEN]="";
    char sortType = 'q';
    int sortParam = 10;
    int hasGeo = 0, hasSaida = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            strcpy(dirEntrada, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strcpy(dirSaida, argv[++i]);
            hasSaida = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoGeo, argv[++i]);
            hasGeo = 1;
            char *pNome = strrchr(nomeArquivoGeo, '/');
            strcpy(baseGeo, pNome ? pNome + 1 : nomeArquivoGeo);
            char *pExt = strrchr(baseGeo, '.');
            if (pExt && strcmp(pExt, ".geo") == 0) {
                *pExt = '\0';
            }
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoQry, argv[++i]);
            char *p = strrchr(argv[i], '/');
            strcpy(onlyQry, p ? p + 1 : argv[i]);
            char *pNome = strrchr(nomeArquivoQry, '/');
            strcpy(baseQry, pNome ? pNome + 1 : nomeArquivoQry);
            char *pExt = strrchr(baseQry, '.');
            if (pExt && strcmp(pExt, ".qry") == 0) {
                *pExt = '\0';
            }
        }else if(strcmp(argv[i],"-to")==0 && i+1<argc){
            sortType = argv[++i][0];
        }else if(strcmp(argv[i],"-i")==0 && i+1 < argc){
            sortParam = atoi(argv[++i]);
        }else {
            fprintf(stderr, "Parametro desconhecido ou invalido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!hasGeo || !hasSaida) {
        fprintf(stderr, "Erro: parametros obrigatorios -f (geo) e -o (saida) nao fornecidos.\n");
        return EXIT_FAILURE;
    }

    char fullPathGeo[1024];
    snprintf(fullPathGeo, sizeof(fullPathGeo), "%s/%s", dirEntrada, nomeArquivoGeo);

    char fullPathQry[1024];
    if (strlen(nomeArquivoQry) > 0) {
        snprintf(fullPathQry, sizeof(fullPathQry), "%s/%s", dirEntrada, nomeArquivoQry);
    }

    char arquivoSaidaSvgGeo[1024];
    snprintf(arquivoSaidaSvgGeo, sizeof(arquivoSaidaSvgGeo), "%s/%s.svg", dirSaida, baseGeo);

    char arquivoSaidaSvgQry[1024];
    if (strlen(nomeArquivoQry) > 0) {
        snprintf(arquivoSaidaSvgQry, sizeof(arquivoSaidaSvgQry)+sizeof(onlyQry), "%s/%s-%s.svg", dirSaida, baseGeo, baseQry);
    }

    char arquivoSaidaTxt[1024];
    if (strlen(nomeArquivoQry) > 0) {
        snprintf(arquivoSaidaTxt, sizeof(arquivoSaidaTxt)+sizeof(onlyQry), "%s/%s-%s.txt", dirSaida, baseGeo, baseQry);
    }

    char nomeBase[1024];
    if(strlen(nomeArquivoGeo)>0 && strlen(nomeArquivoQry) > 0){
        snprintf(nomeBase, sizeof(nomeBase), "%s/%s-%s",dirSaida, baseGeo, baseQry);
    }

    FILE* geo;
    FILE* qry;
    FILE* txt;
    FILE* svgGeo;
    FILE* svgQry;

    geo = abre_arquivo_leitura(fullPathGeo);
    qry = abre_arquivo_leitura(fullPathQry);
    txt = abre_arquivo_escrita(arquivoSaidaTxt);
    svgGeo = abre_arquivo_escrita(arquivoSaidaSvgGeo);
    svgQry = abre_arquivo_escrita(arquivoSaidaSvgQry);

    Lista formas = criar_lista();
    Lista anteparos = criar_lista();
    Estilo ts = criar_estilo("sans", "n", "12pt");
    int maior_id = 0;

    startSVG(svgGeo);
    le_geo(geo, svgGeo, ts, formas, &maior_id);
    fechasvg(svgGeo);
    
    startSVG(svgQry);
    leComandoQry(qry, svgQry, txt, formas, anteparos, &maior_id, sortType, sortParam, nomeBase, ts);
    printar_lista(formas, svgQry, ts);
    printar_lista_anteparos(anteparos, svgQry);
    fechasvg(svgQry);

    fecha_arquivo(svgGeo);
    fecha_arquivo(svgQry);
    fecha_arquivo(qry);
    fecha_arquivo(geo);
    fecha_arquivo(txt);

    destroiListaDeFormas(formas);
    destroiListaDeAnteparos(anteparos);
    freeEstilo(ts);

    return 0;
}