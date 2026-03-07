#include <stdio.h>
#include <string.h>

FILE *file;



int autetification (char login[], char password[]){
    file = fopen("DB/db.txt", "r");
    if (file == NULL){
        perror("Error");
        return 1;
    }
    char line1[256], line2[256];
    fprintf(file, "%s\n%s\n", login, password);
    if (fgets(line1, sizeof(line1), file)){
        line1[strcspn(line1, "\n")] = 0;
        while (fgets(line2, sizeof(line2), file)){
            line2[strcspn(line2, "\n")] = 0;
            if(strcmp(line1, login) == 0 && strcmp(line2, password) == 0){
                printf("Успех!\n");
            }
            else{
                printf("Не удалось войти. Попробуйте авторищзоваться\n");
                return 1;
            }
        }
    fclose(file);
    return 0;
    }
    return 0;
}


int autorization(char login[], char password[]){
    if (login[0] != '\0' && password[0] != '\0'){
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
    int choice;
    printf("Hello! 1. Log in or 2. Autorize\n");
    printf("1. Log in\n");
    printf("2. Autorize");
    scanf("%d", &choice);

    printf("Login: ");
    scanf("%49s", login);

    printf("Password: ");
    scanf("%49s", password);

    if (choice == 1){
        autetification(login, password);
        return 0;
    }
    else if (choice == 2){
       autorization(login,  password);
        return 0;
    }
    return 0;
return 0;
}
