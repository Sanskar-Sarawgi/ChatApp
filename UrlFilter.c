#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dict
{
    char key[10];
    char value[10];
} dict;

typedef struct Url
{
    char page[30];
    dict *list;
    int arg_no;
} Url;

void Get_URL(char *req, char *url)
{
    int len = strlen(req);
    int i = 0;
    for (int j = 0; j < len; j++)
    {
        if (req[j] == '/')
        {
            while (req[j] != ' ' && req[j] != '\0')
            {
                url[i++] = req[j++];
            }
            break;
        }
    }
    url[i] = '\0';
}

int Count_Argument(char *url)
{
    int count = 0;
    for (int i = 0; url[i] != '\0'; i++)
    {
        if (url[i] == '=')
            count++;
    }
    return count;
}

void Set_UrlPath(char *url_str, Url *url)
{
    int i;
    for (i = 0; url_str[i] != '\0' && url_str[i] != '?'; i++)
    {
        url->page[i] = url_str[i];
    }
    url->page[i] = '\0';
}

void Set_UrlArgu(char *url_str, Url *url)
{
    int no = url->arg_no;
    int i = 0;
    int len = strlen(url_str);
    while (url_str[i] != '?')
    {
        i++;
        if (i == len)
            break;
    }
    i++;
    int key_i;
    int value_i;
    url->list = (dict *)calloc(no, sizeof(dict));
    int j = 0;
    while (no--)
    {
        key_i = 0;
        while (url_str[i] != '=')
        {
            url->list[j].key[key_i++] = url_str[i];
            i++;
        }
        url->list[j].key[key_i] = '\0';
        i++;
        value_i = 0;
        while (url_str[i] != '&' && url_str[i] != '\0')
        {
            url->list[j].value[value_i++] = url_str[i];
            i++;
        }
        url->list[j].value[value_i] = '\0';
        i++;
        j++;
    }
}

Url *Find_Element(char *req)
{
    char *arg;
    char *page;
    Url *url = (Url *)malloc(sizeof(Url));
    // find url in request
    char url_str[100];
    Get_URL(req, url_str);

    // find no of count
    url->arg_no = Count_Argument(url_str);

    // set page path
    Set_UrlPath(url_str, url);

    // set argument
    Set_UrlArgu(url_str, url);

    return url;
}

// int main()
// {
//     char req[] = "Request :GET /?fname=Sanskar&Lname=Sarawgi&cdfe=flsdk HTTP/1.1 Host: localhost:8080 Connection: keep-alive Cache-Control: max-age=0sec-ch-ua:sec-ch-ua-mobile: ?0sec-ch-ua-platform: Upgrade-Insecure-Requests: 1";
//     char arg[100];
//     Find_Element(req);
//     return 0;
// }