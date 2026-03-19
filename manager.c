#include <stdio.h>
#include <string.h>

FILE *file;

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
        return 0;
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
    int choice;
    printf("Hello! 1. Log in or 2. Autorize\n");
    printf("1. Log in\n");
    printf("2. Autorize\n");
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
}
