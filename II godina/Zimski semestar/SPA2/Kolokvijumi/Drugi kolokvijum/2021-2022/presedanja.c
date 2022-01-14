//Resio: Ljubomir Matovic 58/2020

#include<stdio.h>
#include<stdlib.h>

#define POVEZANO 1
#define NEPOVEZANO 0
#define INF -1

int jeManji(int i,int j){
    if(i==INF)
        return 0;
    if(j==INF)
        return 1;
    return i<j;
}
#define kreirajNiz(t,n) (t*)malloc((n)*sizeof(t))

typedef struct RED{
    int v;
    struct RED *sledeci;
} RED;

void dodaj(RED **pocetak,RED **kraj,int v){
    RED *temp=kreirajNiz(RED,1);
    temp->v=v;
    temp->sledeci=NULL;
    if(*pocetak==NULL){
        *pocetak=*kraj=temp;
    }else{
        (*kraj)->sledeci=temp;
        *kraj=temp;
    }
}
int skini(RED **red){
    if(*red==NULL)
        return -1;
    RED *temp=*red;
    *red=temp->sledeci;
    int v=temp->v;
    free(temp);
    return v;    
}

void bfs(int **graf,int start,int *d,int n){
    int u,v;
    for(u=0;u<n;u++)
        d[u]=INF;
    d[start]=0;
    RED *pocetak=NULL,*kraj=NULL;
    dodaj(&pocetak,&kraj,start);
    while(pocetak!=NULL)
    {
        u=skini(&pocetak);
        for(v=0;v<n;v++){
            if(graf[u][v]==POVEZANO && d[v]==INF){
                d[v]=d[u]+1;
                dodaj(&pocetak,&kraj,v);
            }
          }
    }
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int **graf=kreirajNiz(int*,n);
    int i,j;
    for(i=0;i<n;i++){
        graf[i]=kreirajNiz(int,n);
        for(j=0;j<n;j++)
            graf[i][j]=NEPOVEZANO;
    }
    int x,y;
    int *dX=kreirajNiz(int,n),*dY=kreirajNiz(int,n);
    for(i=0;i<m;i++){
        scanf("%d%d",&x,&y);
        graf[x][y]=graf[y][x]=POVEZANO;
    }
    scanf("%d%d",&x,&y);
    bfs(graf,x,dX,n);
    bfs(graf,y,dY,n);
    int z=INF,minRast=INF;
    for(i=0;i<n;i++)
    if(dX[i]==dY[i] && jeManji(dX[i],minRast)){
        z=i;
        minRast=dX[i];
    }
    if(z==INF)
        printf("NE POSTOJI\n");
    else printf("%d\n",z);
    return 0;
}