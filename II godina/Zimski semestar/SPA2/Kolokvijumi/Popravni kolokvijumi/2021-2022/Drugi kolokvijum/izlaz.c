//Resio: Ljubomir Matovic 58/2020

#include<stdio.h>
#include<stdlib.h>

#define ULAZ 'U'
#define IZLAZ 'I'
#define ZID '#'
#define SLOBODNO '.'
#define PROSAO '*'


#define LEVO 1
#define DESNO 2
#define GORE 3
#define DOLE 4

#define INF -1


typedef struct LISTA{
    int x,y;
    struct LISTA *sledeci;
}LISTA;

typedef struct TACKA{
    int x,y; 
}TACKA;

LISTA* alocirajListu(int x,int y){
    LISTA *temp=(LISTA*)malloc(sizeof(LISTA));
    if(temp==NULL){
        printf("GRESKA\n");
        exit(1);
    }
    temp->x=x;
    temp->y=y;
    temp->sledeci=NULL;
    return temp;
}

void dodaj(LISTA **pocetak,LISTA **kraj,int x,int y){
    LISTA *temp=alocirajListu(x,y);
    if(*pocetak==NULL){
        *pocetak=*kraj=temp;
    }else{
        (*kraj)->sledeci=temp;
        *kraj=temp;
    }

}
LISTA* skini(LISTA **pocetak){
    if(*pocetak==NULL)
    return NULL;
    LISTA *temp=*pocetak;
    *pocetak=temp->sledeci;
    return temp;
}

int van(int x,int y,int n,int m){
    if(x>n-1 || x<0 || y>m-1 || y<0)
    return 1;
    return 0;
}

int dajSledeci(char **maze,int n,int m,int smer,int *x,int *y){
    int pX=*x,pY=*y;
    switch(smer){
        case GORE:
        pX--;
        break;
        case DOLE:
        pX++;
        break;
        case LEVO:
        pY--;
        break;
        default:
        pY++;
        break;
    }
    if(!van(pX,pY,n,m) && maze[pX][pY]!=ZID && maze[pX][pY]!=ULAZ){
        *x=pX;
        *y=pY;
        return 1;
    }
    return 0;
}

void rekonstrukcija(char **maze,TACKA **pret,int startX,int startY,int endX,int endY){
    if(startX==endX && startY==endY)
    return;
    if(endX==-1 || endY==-1)
    {
        printf("GRESKA\n");
        return;
    }
    TACKA t=pret[endX][endY];
    maze[endX][endY]=PROSAO;
    rekonstrukcija(maze,pret,startX,startY,t.x,t.y);
}
int main(){
    int i,j;
    int n,m;
    int startX,startY,endX,endY;
    char c;
    scanf("%d %d",&n,&m);
    char **maze=(char**)malloc(n*sizeof(char*));
    int **rastojanje=(int**)malloc(n*sizeof(int*));
    TACKA **pret=(TACKA**)malloc(n*sizeof(TACKA*));
    TACKA t;
    t.x=-1;
    t.y=-1;
    for(i=0;i<n;i++){
        maze[i]=(char*)malloc(m*sizeof(char));
        rastojanje[i]=(int*)malloc(m*sizeof(int));
        pret[i]=(TACKA*)malloc(m*sizeof(TACKA));
        for(j=0;j<m;j++){
            getchar();
            scanf("%c",&c);
            maze[i][j]=c;
            if(c==ULAZ){
                startX=i;
                startY=j;
            }else if(c==IZLAZ){
                endX=i;
                endY=j;
            }
            rastojanje[i][j]=INF;
            pret[i][j]=t;
        }
    }
    LISTA *pocetak=NULL,*kraj=NULL;
    LISTA *u;
    dodaj(&pocetak,&kraj,startX,startY);
    rastojanje[startX][startY]=0;
    int x,y;
    while(pocetak!=NULL){
        u=skini(&pocetak);
        t.x=u->x;
        t.y=u->y;
        //printf("%d %d\n",u->x,u->y);
        if(u->x==endX && u->y==endY)
        break;
        for(i=1;i<5;i++){
        x=u->x;
        y=u->y;
        if(dajSledeci(maze,n,m,i,&x,&y) && rastojanje[x][y]==INF){
                rastojanje[x][y]=rastojanje[u->x][u->y]+1;
                pret[x][y]=t;
                dodaj(&pocetak,&kraj,x,y);

                //printf("%d %d\n",x,y);
            }
        }
        free(u);
    }
    if(rastojanje[endX][endY]==INF){
        printf("NE POSTOJI\n");
    }else{
        printf("%d\n",rastojanje[endX][endY]);
        t=pret[endX][endY];
        rekonstrukcija(maze,pret,startX,startY,t.x,t.y);
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++){
                printf("%c ",maze[i][j]);
            }
            putchar('\n');
        }
    }
}