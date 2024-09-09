#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int create_new_user();
int nosila();
int lift();
int brojanje = 0;
int aktivacija();
char nosilo[20];
int spratovi;
int servis;

int main() {
    char admin_email[50];
    char admin_pass[50];
    char input_email[50];
    char input_password[20];
    char file_email[50];
    char file_pass[50];
    FILE *p1;
    FILE *p2;
    int choice;
    int korisnik_choice;
    int random = 0;

    p1 = fopen("admin.dat", "r+");
    if (p1 == NULL) {
        printf("Datoteka nije otvorena\n");
        sleep(1);
        return 1;
    }

    p2 = fopen("informacije.txt", "r+");
    if (p2 == NULL) {
        printf("Datoteka nije otvorena\n");
        sleep(1);
        fclose(p1);
        return 1;
    }

    fscanf(p1, "%s", admin_email);
    fscanf(p1, "%s", admin_pass);
    fscanf(p2, "%s %s", file_email, file_pass);

    fclose(p1);
    fclose(p2);

    while ((strcmp(input_email, admin_email) != 0 || strcmp(input_password, admin_pass) != 0) &&
           (strcmp(input_password, file_pass) != 0 || strcmp(input_email, file_email) != 0)) {
        printf("Molimo unesite vas e-mail:\n");
        scanf("%s", input_email);

        printf("\nMolimo unesite vasu sifru:\n");
        scanf("%s", input_password);

        system("cls");

        if (strcmp(admin_email, input_email) == 0 && strcmp(admin_pass, input_password) == 0) {
            random = 1;
            while (1) {
                printf("Dobrodosli na Admin stranu\n");
                printf("\nVase opcije su:\n\n1.Kreiranje novog korisnika\n2.Kreiranje novog nosila\n3.Exit\n\n");

                scanf("%d", &choice);
                system("cls");

                switch (choice) {
                    case 1:
                        create_new_user();
                        break;
                    case 2:
                        system("cls");
                        printf("\n\nMolimo unesite naziv vaseg nosila:");
                        nosila();
                        break;
                    case 3:
                        printf("Odabrali ste da izadjete iz programa\n");
                        return 0;
                    default:
                        printf("Pogresan unos!\n\nMolimo pokusajte ponovo");
                        sleep(1);
                        system("cls");
                }
            }
        } else if (strcmp(file_email, input_email) == 0 && strcmp(file_pass, input_password) == 0) {
            while (1) {
                printf("Dobrodosli na Korisnik stranu\n");
                printf("\nVase opcije su:\n\n");
                printf("1.Aktivacija nosila ili lifta\n2.Pozivanje i koristenje nosila ili lifta\n3.Exit\n\n");

                scanf("%d", &korisnik_choice);
                system("cls");

                switch (korisnik_choice) {
                    case 1:
                        aktivacija();
                        break;
                    case 2:
                        lift();
                        break;
                    case 3:
                        printf("\nOdabrali ste da izadjete iz programa");
                        brojanje++;
                        return 0;
                    default:
                        printf("Pogresan unos!\n\nMolimo pokusajte ponovo");
                        sleep(1);
                        system("cls");
                }
            }
        } else {
            printf("Pogresan email ili sifra\n\n");
            printf("Molimo pokusajte ponovo!");
            sleep(1);
            system("cls");
        }
    }

    return 0;
}

int create_new_user() {
    char new_email[20];
    char new_password[20];
    FILE *datoteka;

    datoteka = fopen("informacije.txt", "a");
    if (datoteka == NULL) {
        printf("Datoteka nije otvorena\n");
        return 1;
    }
    printf("\nUnesite novi e-mail: ");
    scanf("%s", new_email);
    printf("\nUnesite novi password:");
    scanf("%s", new_password);
    fprintf(datoteka, "%s\n", new_email);
    fprintf(datoteka, "%s\n", new_password);
    printf("\nNapravili ste novog korisnika\n");
    sleep(1);
    system("cls");

    fclose(datoteka);
    return 1;
}

int nosila() {
    FILE *p;
    int choice;

    system("cls");
    printf("Molimo unesite naziv nosila:\n");
    scanf("%s", nosilo);
    printf("\nNaziv vaseg nosila je:\n%s", nosilo);

    printf("\n\nMolimo unesite broj spratova:\n");
    scanf("%d", &spratovi);
    printf("\nMolimo unesite koliko puta nosilo moze biti aktivirano prije servisa:\n");
    scanf("%d", &servis);
    printf("\nDa li zelite da snimite sve podatke?(1 - DA ,2 - NE)\n");
    scanf("%d", &choice);

    if (choice == 1) {
        p = fopen("nosila.dat", "a");
        if (p == NULL) {
            printf("\nGreska prilikom otvaranja datoteke");
            return 1;
        }
        fprintf(p, "\nIme nosila - %s\n", nosilo);
        fprintf(p, "Broj spratova - %d\n", spratovi);
        fprintf(p, "Broj upotrebe prije servisa - %d\n", servis);

        fclose(p);
        printf("\nVasi podatci su snimljeni\n\n");

        sleep(1);
        system("cls");

        return 0;
    }

    sleep(1);
    system("cls");

    return 0;
}

void prikazi_lift(const int MAX_SPRAT,int sprat) {
        system("cls");  // ili system("clear"); za Unix sisteme
        for (int i = MAX_SPRAT; i >= 1; i--) {
            printf("%d.%s\n", i, (i == sprat) ? "|||" : "|");
        }
}


void display_lift(int max_floors, int current_floor) {
    system("cls"); // Clear the screen
    for (int i = max_floors; i >= 1; i--) {
        printf("%d.%s\n", i, (i == current_floor) ? "|||" : "|");
    }
}

int lift() {
    const int MAX_FLOORS = 7;
    const int MAX_USES = 6;

    int current_floor = 1;
    int desired_floor;
    int num_uses = 0;

    while (num_uses < MAX_USES) {
        display_lift(MAX_FLOORS, current_floor);
        prikazi_lift(MAX_FLOORS, current_floor);
        printf("\nOdaberite sprat na koji zelite ici (1-%d), Unesite 0 da bi ste izasli: ", MAX_FLOORS);

        if (scanf("%d", &desired_floor) != 1) {
            while (getchar() != '\n'); // Clear the input buffer
            printf("Nevalidan unos.Pokusajte ponovo\n");
            sleep(1);
            continue;
        }

        if (desired_floor == 0) {
            break;
        }

        if (desired_floor < 1 || desired_floor > MAX_FLOORS) {
            printf("Odaberite broj izmedju 1 i %d.\n", MAX_FLOORS);
            sleep(1);
            continue;
        }

        if (desired_floor != current_floor) {
            int direction = (desired_floor > current_floor) ? 1 : -1;
            while (current_floor != desired_floor) {
                current_floor += direction;
                display_lift(MAX_FLOORS, current_floor);
                sleep(1);
            }
            num_uses++;
        } else {
            printf("Vec ste na tom spratu %d.\n", current_floor);
            sleep(1);
        }
    }

    if (num_uses == MAX_USES) {
        printf("\nOvom liftu je potreban servis.\n");
        sleep(2);
    }

    return 0;
}
int aktivacija() {
    char naziv_nosila[20];
    char line[100];
    FILE *p1;

    p1 = fopen("nosila.dat", "r");
    if (p1 == NULL) {
        printf("Nosilo nije otvoreno\n");
        return 1;
    }

    printf("Molimo unesite naziv nosila:\n");
    scanf("%s", naziv_nosila);

    while (fgets(line, sizeof(line), p1) != NULL) {
        char* name_label = "Ime nosila - ";
        char* floors_label = "Broj spratova - ";
        char* service_label = "Broj upotrebe prije servisa - ";

        if (strncmp(line, name_label, strlen(name_label)) == 0) {

            char* name_pos = line + strlen(name_label);
            char* newline_pos = strchr(name_pos, '\n');
            if (newline_pos) *newline_pos = '\0';

            if (strcmp(name_pos, naziv_nosila) == 0) {

                char floors_line[100];
                char service_line[100];


                if (fgets(floors_line, sizeof(floors_line), p1) != NULL &&
                    strncmp(floors_line, floors_label, strlen(floors_label)) == 0) {
                    int spratovi = atoi(floors_line + strlen(floors_label));


                    if (fgets(service_line, sizeof(service_line), p1) != NULL &&
                        strncmp(service_line, service_label, strlen(service_label)) == 0) {
                        int num_uses = atoi(service_line + strlen(service_label));

                        system("cls");

                        printf("Ime nosila: %s\n", name_pos);
                        printf("Broj spratova: %d\n", spratovi);
                        printf("Broj koristenja nosila: %d\n\n", num_uses);

                        fclose(p1);
                        return 0;
                    }
                }
            }
        }
    }

    printf("Zeljeno nosilo nije pronadjeno\n\n");
    fclose(p1);
    return 1;
}
