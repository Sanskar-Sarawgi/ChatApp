#include <stdio.h>
#include <string.h>

void Find_Argument(char *req,char *arg){
    int len = strlen(req);
    
    // find the starting of the argument
    int i;
    for(i=0;i<len;i++){
        if(req[i] == '/'){
            i++;
            if(req[i] == '?'){
                i++;
                break;
            }
            i--;
        }
    }

    int j = 0;
    while(req[i] != ' ' && req[i] != '\0'){
        arg[j] = req[i];
        i++;
        j++;
    }
    arg[j] = '\0';
}

// int main(){
//     char req[] = "Request :GET /?fname=Sanskar HTTP/1.1 Host: localhost:8080 Connection: keep-alive Cache-Control: max-age=0sec-ch-ua:sec-ch-ua-mobile: ?0sec-ch-ua-platform: Upgrade-Insecure-Requests: 1";
//     char arg[100];
//     Find_Argument(req,arg);
//     printf("%s",arg);
//     return 0;
// }