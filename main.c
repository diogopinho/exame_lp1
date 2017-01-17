#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct movie {
    char *title;
    char *actors;
    struct movie *pnext;
} MOVIE;

typedef struct year {
    int year;
    int nmovies;
    MOVIE *pmovie;
} YEAR;

typedef struct colection {
    int nyears;
    YEAR *pyear;
} COLECTION;

void init_decade(COLECTION *c, int dec);
//int number_of_actors(char * actors);
void inserir_filme_coleccao(COLECTION *c,int year,char *title,char * actors);

int main() {
    int i;
    COLECTION c={0,NULL};
    init_decade(&c,1994);
    init_decade(&c,1953);
    init_decade(&c,1973);
    init_decade(&c,1993);
    init_decade(&c,1893);
    YEAR *check=c.pyear;
    inserir_filme_coleccao(&c,1999,"Exame de LP","Diogo Pinho,Rui Rodrigues");
    for(i=0;i<c.nyears;i++) {
        printf("%d\n",check[i].year);
    }
    printf("%s %s",c.pyear->pmovie->title,c.pyear->pmovie->actors);
    return 0;
}


void init_decade(COLECTION *c, int dec) {
    int i,j,bool=0;
    dec=dec/10*10;
    YEAR *paux=NULL;
    c->nyears+=10;
    if (c->pyear==NULL) {
        c->pyear = (YEAR *) malloc(sizeof(YEAR) * 10);
        paux = c->pyear;
        for (i = dec + 9; i >= dec; i--) {
            paux->year = i;
            paux->nmovies = 0;
            paux->pmovie = NULL;
            paux++;
        }
        return;
    }

    for (i=0;i<c->nyears;i++) {
        if (c->pyear[i].year==dec+9) {
            c->nyears-=10;
            printf("Decada ja existente.");
            return;
        }
    }

    YEAR *pyear=c->pyear, *pfirst=NULL;
    paux=(YEAR*)malloc(sizeof(YEAR)*(c->nyears+10));
    c->pyear=paux;
    pfirst=pyear;
    for (i=0;i<c->nyears;i++) {
        if((pfirst->year<dec+9&&bool==0)||i==c->nyears-10) {
            for (j=dec+9;j>=dec;j--) {
                paux->year = j;
                paux->nmovies = 0;
                paux->pmovie = NULL;
                paux++;
                bool=1;
                i++;
            }
        }
        paux->nmovies=pfirst->nmovies;
        paux->pmovie=pfirst->pmovie;
        paux->year=pfirst->year;
        paux++;
        pfirst++;
    }
    free(pyear);
}
/*
int number_of_actors(char * actors) {
    int i, count=0;
    for (i=0;actors[i]!='\0';i++) {
        count=1;
        if(actors[i]==',') {
            count++;
        }
    }
    return count;
}*/

void inserir_filme_coleccao(COLECTION *c,int year,char *title,char * actors) {
    YEAR *paux=NULL;
    int i;
    for(paux=c->pyear,i=0;paux->year>year;paux++,i++) {
        if(i==c->nyears) {
            printf("Ano nao encontrado.");
            return;
        }
    }
    MOVIE *movie=NULL;
    if(paux->pmovie!=NULL) {
        movie=paux->pmovie;
        while(movie!=NULL) {
            movie=movie->pnext;
        }
    }
    movie=(MOVIE*)malloc(sizeof(MOVIE));
    paux->pmovie=movie;
    movie->actors=(char*)malloc(sizeof(char)*strlen(actors)+1);
    movie->title=(char*)malloc(sizeof(char)*strlen(title)+1);
    movie->actors=actors;
    movie->title=title;
}