#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t Pen_and_Paper;
sem_t paper_and_questionp;
sem_t Pen_and_questionPaper;
sem_t Assign_Done;
void work(char *s)
{
    printf("%s is doing his Assignment\n",s);
}

void *teacher()
{
  while(1)
  {
  sem_wait(&Assign_Done);
   int r=rand()%3;
   switch (r) {
     case 0: printf("Teacher has put Pen and Paper on table:\n");
             sem_post(&Pen_and_Paper);
              break;
     case 1:printf("Teacher has put Paper and QuestionPaper on the table:\n");
             sem_post(&paper_and_questionp);
              break;
     case 2:printf("Teacher has put Pen and QuestionPaper on the Table:\n");
            sem_post(&Pen_and_questionPaper);
             break;
   }
   sleep(rand()%5);
 }
}
void *Student_A()
{
  while(1){
    //Wait for our two ingredients
      sem_wait(&Pen_and_Paper);
        work("Student A(has QuestionPaper)");
        //Wait for student A to complete his assignment
          sleep(rand()%6);
        //Signal that we are done doing assignment so that the teacher can put down
        //next ingredients.
        printf("Student A has done Assignment:\n");
        sem_post(&Assign_Done);

  }

}
void *Student_B()
{
  while(1){
    //Wait for our two ingredients
      sem_wait(&paper_and_questionp);
        work("Student B(has Pen)");
        //wait for student B to complete his assignment
        sleep(rand()%6);
        //Signal that we are done doing assignment so that the teacher can put down
        //next ingredients.
        printf("Student B has done Assignment\n");
        sem_post(&Assign_Done);

  }
}
void *Student_C()
{
  while(1){
    //Wait for our two ingredients
      sem_wait(&Pen_and_questionPaper);
        work("Student C(has Paper)");
        //Wait for student C to complete his Assignment
          sleep(rand()%6);

        //Signal that we are done doing assignment so that the teacher can put down
        //next ingredients.
        printf("Student C has done Assignment\n");
        sem_post(&Assign_Done);

  }

}
int main() {
   printf("Welcome to Teacher Student Processs Syncronization simulation \n");
   printf("Student A has QuestionPaper\n");
   printf("Student B has Pen\n");
   printf("Student C has Paper\n");
   sem_init(&Pen_and_Paper,0,0);
   sem_init(&paper_and_questionp,0,0);
   sem_init(&Pen_and_questionPaper,0,0);
   sem_init(&Assign_Done,0,1);
   pthread_t s1,s2,s3,t;
   pthread_create(&s1,NULL,Student_A,NULL);
   pthread_create(&s2,NULL,Student_B,NULL);
   pthread_create(&s3,NULL,Student_C,NULL);
   pthread_create(&t,NULL,teacher,NULL);
   pthread_join(s1,NULL);
   pthread_join(s2,NULL);
   pthread_join(s3,NULL);
   pthread_join(t,NULL);
  return 0;
}
