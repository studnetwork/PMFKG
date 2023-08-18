// resenje 4. zadatka za domaci: https://knezevicmarko.github.io/os2/2017/207-pthread6.html

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define S 4
#define J 4

#define N 3

#define VREME_PRELASKA 2

#define NIJE_DEFINISAN 0
#define SEVER 1
#define JUG 2


int automobilaNaMostu = 0;
int smer = NIJE_DEFINISAN;

pthread_mutex_t most;
pthread_cond_t uslov;

void *sever(void *arg) {
    long id = (long) arg;
    
    int vremeDolaska = 1 + rand() % 6;
    sleep( vremeDolaska );
    printf("Automobila %ld sa severa je stigao na most\n", id );
    
    pthread_mutex_lock( &most );
    while ( automobilaNaMostu >= N || smer == JUG ) 
        pthread_cond_wait( &uslov, &most );
    // krece da prelazi most
    automobilaNaMostu ++;
    smer = SEVER;
    pthread_mutex_unlock( &most );
    
    printf("Automobila %ld sa severa prelazi most\n", id );
    sleep( VREME_PRELASKA );
    
    // presao je most
    pthread_mutex_lock( &most );
    automobilaNaMostu--;
    if ( ! automobilaNaMostu ) {
        smer = NIJE_DEFINISAN;
        pthread_cond_broadcast( &uslov );
    }
    pthread_mutex_unlock( &most );
    printf("Automobila %ld sa severa je presao most\n", id );
    
    pthread_exit(NULL);
}

void *jug(void *arg) {
    long id = (long) arg;
    
    int vremeDolaska = 1 + rand() % 6;
    sleep( vremeDolaska );
    printf("Automobila %ld sa juga je stigao na most\n", id );
    
    pthread_mutex_lock( &most );
    while ( automobilaNaMostu >= N || smer == SEVER ) 
        pthread_cond_wait( &uslov, &most );
    // kreni da prelazis most
    automobilaNaMostu ++;
    smer = JUG;
    pthread_mutex_unlock( &most );
    
    printf("Automobila %ld sa juga prelazi most\n", id );
    sleep( VREME_PRELASKA );
    
    // presao je most
    pthread_mutex_lock( &most );
    automobilaNaMostu--;
    if ( ! automobilaNaMostu ) {
        smer = NIJE_DEFINISAN;
        pthread_cond_broadcast( &uslov );
    }
    pthread_mutex_unlock( &most );
    printf("Automobila %ld sa juga je presao most\n", id );
    
    pthread_exit(NULL);
}


int main() {
    pthread_t t[ S + J ];
    
    pthread_mutex_init( &most, NULL );
    pthread_cond_init( &uslov, NULL );
    
    for ( int i = 0; i < S; i ++ )
        pthread_create( t + i, NULL, sever, (void *) i  );
    
    for ( int i = 0; i < J; i ++ )
        pthread_create( t + S + i, NULL, jug, (void *) i );
    
    for ( int i = 0; i < S + J; i ++ )
        pthread_join( t[ i ], NULL );
    
    return 0;
}
