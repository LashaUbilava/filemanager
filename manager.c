#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

FILE *file;


void create_file(char *path){
    char name_file[50];
    char final_path[256];
    char dir_path[250];
    char content[256];
    char* first_path = "file";
    if (mkdir(first_path, 0775) !=0 && errno != EEXIST){    
        perror("Error");
        return;
    }
    printf("Выберите путь, куда вы хотите записать файл(Пример ввода путь/путь): ");
    scanf("%255s", path);
    snprintf(dir_path, sizeof(dir_path), "%s/%s", first_path, path);
    if (mkdir(dir_path, 0775) != 0 && errno != EEXIST){    
        perror("Error");
        return;
    }
    printf("Введите название текстового файла: ");
    scanf("%49s", name_file);
    snprintf(final_path, sizeof(final_path), "%s/%s/%s", first_path, path, name_file);
    file = fopen(final_path, "w");
    printf("Введите любой текст: ");
    scanf("%255s", content);
    fprintf(file, "%s", content);
    fclose(file);
    return;
}

char* hash_function(char password[]) {
    static char stri[16];
    unsigned int hash = 5381; 
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; 
    sprintf(stri, "%d", hash);
    return stri;
}

int autetification (char login[], char password[]){
    file = fopen("DB/db.txt", "r");
    if (file == NULL){
        perror("Error");
        return 1;
    }
    char line1[50], line2[50];
    char* hash = hash_function(password);
    int found = 0;
    while (fgets(line1, sizeof(line1), file)){
        line1[strcspn(line1, "\n")] = 0;
        if (fgets(line2, sizeof(line2), file)){
            line2[strcspn(line2, "\n")] = 0;
            if(strcmp(line1, login) == 0 && strcmp(line2, hash) == 0){
                found+=1;
                break;
        }
    }
}
    fclose(file);
    if(found){
        printf("Успех!\n");
        return 0;
    } else{
        printf("Не удалось войти. Попробуйте авторизоваться\n");
        return 1;
    }
    return  0;
}

int autorization(char login[], char password[]){
    if (login[0] != '\0' && password[0] != '\0'){
        password = hash_function(password);
        file = fopen("DB/db.txt", "a");
        if (file == NULL){
            perror("Error");
            return 1;
        }
        fprintf(file, "%s\n%s\n", login, password);
        fclose(file);
        return 0;
    }
    return 0;
}


int main(void){
    char login[50];
    char password[50];
    int choice1;
    int choice2;
    char path[256];
    printf("Hello! 1. Log in or 2. Autorize\n");
    printf("1. Log in\n");
    printf("2. Autorize\n");
    scanf("%d", &choice1);

    printf("Login: ");
    scanf("%49s", login);

    printf("Password: ");
    scanf("%49s", password);

    if (choice1 == 1){
        if (autetification(login, password) != 0){
            exit(-1);
        }
    }
    else if (choice1 == 2){
       autorization(login,  password);
    }
    printf("Выберите действие: 1. Записать текстовый файл\n");
    scanf("%d", &choice2);
    if (choice2 == 1){
        create_file(path);
    }
    return 0;
}
