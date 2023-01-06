#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Text_Size 100
#define Maximum_Member 10
#define Name_Size 20


typedef struct Chat{
    char data[Text_Size];
    struct Chat *next;
}Chat;


typedef struct Person_detail{
    char name[Name_Size];
    int Id;
    Chat *member[Maximum_Member];
    int Memeber_no;
}Person_detail;

typedef struct Contact{
    Person_detail* list[Maximum_Member];
    int list_size;
}Contact;

Chat* Create_Chat(char* text){
    Chat* temp = (Chat*)malloc(sizeof(Chat));
    strcpy(temp->data,text);
    temp->next = NULL;
    return temp;
}

Chat* Add_Chat(Chat* head,char text[]){
    if(!head){
        return Create_Chat(text);   
    }
    else{
        Chat* temp = head;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = Create_Chat(text);
    }
    return head;
}

Contact *Create_Contact(){
    Contact* cont = (Contact*)malloc(sizeof(Contact));
    cont->list_size = 0;
    return cont;
}

Contact* Add_Contact(char name[],Contact *cont){
    if(cont == NULL) cont = Create_Contact();
    
    // setting up the user detail
    Person_detail *user =(Person_detail *)malloc(sizeof(Person_detail));
    strcpy(user->name,name);
    user->Id = cont->list_size;
    user->Memeber_no = 0;
    for(int i=0;i<Maximum_Member;i++){
        user->member[i] = NULL;
    }

    // adding to the contact
    cont->list[(cont->list_size)++] = user;
    return cont;
}

void Send_Chat(char data[],int from,int to,Contact* cont){
    Person_detail* Sender = cont->list[from];
    Person_detail* Receiver = cont->list[to];

    // add chat to the sender
    Sender->member[to] = Add_Chat(Sender->member[to],data);
    // add chat to the receiver
    Receiver->member[from] = Add_Chat(Receiver->member[from],data);

}

void print(Contact* cont,int id,int of){
    Person_detail* person = cont->list[id];
    Chat* temp = person->member[of];
    printf("%s\n",person->name);

    while(temp){
        printf("%s\n",temp->data);
        temp = temp->next;
    }
}

int main(){
    char *a[] = {"sanskar","vansh","vinita","sanjay"};
    Contact *cont = NULL;
    for(int i=0;i<4;i++){
        cont = Add_Contact(a[i],cont);
    }

    int from;
    int to;
    char str[100];
    int n = 5;
    while(n--){
        scanf("%d",&from);
        scanf("%d",&to);
        scanf("%s",str);
        Send_Chat(str,from,to,cont);
    }
    print(cont,0,1);
    print(cont,1,0);
}



