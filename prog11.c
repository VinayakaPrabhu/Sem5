#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
sem_t wrt,mutex;
 
//pthread_mutex_t wrt=PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
 
int queue[500];
int qLength,readcount=0,data=0;
char buf[256];
void *writer(void *param){
    //do{
        sem_wait(&wrt);
        //int fd =creat("p1.txt",O_RDWR);
        //printf("%d\n",fd);
        //printf("Writing\n");
        //gets(buf);
        //printf("Writing Finished\n");
        //write(fd,buf,sizeof(buf));
        data++;
        printf("Data written by write %d\n",data);
        sleep(1);
        sem_post(&wrt);
    //}while(1);
}
 
void *reader(void *param){
    //do{
        sem_wait(&mutex);
        readcount++;
        if(readcount==1)
            sem_wait(&wrt);
        sem_post(&mutex);  
        int fd =fopen("p1.txt","O_RDWR");
        //printf("%d\n",fd);
        //char buf[256];
        //while(read((int)fd,buf,sizeof(buf))){
            //puts(buf);
        //}
        //printf("Reading\n");
        //puts(buf);
        //printf("Reading Done\n");
        printf("Data read by reader %d\n",readcount);
        sleep(1);
        sem_wait(&mutex);
        readcount--;
        if(readcount==0)
            sem_post(&wrt);
        sem_post(&mutex);
    //}while(1);
}
int main(){
    pthread_t rthreads[2],wthreads[2];
    sem_init(&wrt,0,1);
    int i;
    sem_init(&mutex,0,1);
    for(i=0;i<2;i++){
        pthread_create(&rthreads[i],0,&writer,0);
        pthread_create(&wthreads[i],0,&reader,0);
    }
    for(i=0;i<2;i++){
        pthread_join(rthreads[i],0);
        pthread_join(wthreads[i],0);
    }
    sem_destroy(&wrt);
    sem_destroy(&mutex);
    return 0;
}
