#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define max_name 50
#define max_players 50

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define PINK "\033[38;2;255;105;180m"
#define L_BLUE    "\033[38;2;173;216;230m"
#define BLUE    "\033[94m"
#define RESET   "\033[0m"

typedef struct{
char pl1_name[max_name];
int pl1_score;
char pl2_name[max_name];
int pl2_score;
} Match;

typedef struct{
    char name[max_name];
    int wins;
    int matches;
}Player;

void header()
{
    printf(L_BLUE"\n------------------------\n"RESET);
}
void header2()
{
    printf(L_BLUE"\n==============================\n"RESET);
}
void header3()
{
    printf(L_BLUE".................................\n"RESET);
}

int valid_name(const char *name) {
    if (strlen(name) == 0) return 0;
    for (int i = 0; name[i]; i++) {
        if (!isalpha(name[i])) {
            return 0;
        }
    }
    return 1;
}

int valid_score(int score) {
    return score >= 0 && score <= 21;
}

void new_match()
{
    Match match;

    printf("Enter player 1 name:\n");
    scanf("%24s", match.pl1_name);
    while(!valid_name(match.pl1_name))
    {
        printf("Invalid name.Try again using only letters!\n");
        scanf("%24s", match.pl1_name);
    }

    printf("Enter player 1 score(0-21): \n");
    scanf("%d", &match.pl1_score);
    while(!valid_score(match.pl1_score))
    {
        printf("Invalid score.Use only numbers between 0 and 21.\n");
        scanf("%d", &match.pl1_score);
    }

     printf("Enter player 2 name:\n");
     scanf("%24s", match.pl2_name);
     while(!valid_name(match.pl2_name))
     {
        printf("Invalid name.Try again using only letters!\n");
        scanf("%24s", match.pl2_name);
     }

    printf("Enter player 2 score(0-21): \n");
    scanf("%d", &match.pl2_score);
    while(!valid_score(match.pl2_score))
    {
        printf("Invalid score.Use only numbers between 0 and 21.\n");
        scanf("%d", &match.pl2_score);
    }

     while (!((match.pl1_score == 21 && match.pl2_score < 21) || (match.pl2_score == 21 && match.pl1_score < 21))) {
        printf(RED "\nInvalid score combination. One player must score exactly 21, and the other less than 21.\n" RESET);
        printf("Re-enter player 1 score (0-21): \n");
        scanf("%d", &match.pl1_score);
        while(!valid_score(match.pl1_score)) {
            printf("Invalid score. Use only numbers between 0 and 21.\n");
            scanf("%d", &match.pl1_score);
        }

        printf("Re-enter player 2 score (0-21): \n");
        scanf("%d", &match.pl2_score);
        while(!valid_score(match.pl2_score)) {
            printf("Invalid score. Use only numbers between 0 and 21.\n");
            scanf("%d", &match.pl2_score);
        }
    }



    FILE *file=fopen("match_info.txt","a");
    if(file==NULL){
        printf("The file could not be opened\n");
        return;
    }
    fprintf(file,"%s,%d,%s,%d\n",match.pl1_name,match.pl1_score,match.pl2_name,match.pl2_score);

    fclose(file);
}

void players_info()
{


    char name[max_name];
    printf("\nEnter the name of the player whos statistics you wish to see:\n");
    scanf("%49s",name);
    char pl1_name[max_name],pl2_name[max_name];
    int pl1_score, pl2_score;
    int wins=0,losses=0,matches=0;

    FILE *file=fopen("match_info.txt","r");
    if(file == NULL)
    {
        printf("The file could not be opened.\n");
        return;
    }
    while(fscanf(file,"%49[^,],%d,%49[^,],%d\n", pl1_name, &pl1_score, pl2_name, &pl2_score)==4)
    {
     if(strcmp(name,pl1_name)==0)
     {
         matches++;
         if(pl1_score>pl2_score && pl1_score==21) wins++;
         else losses++;
     }
     else if(strcmp(name,pl2_name)==0)
     {
         matches++;
         if(pl2_score>pl1_score&& pl2_score==21) wins++;
         else losses++;
     }
    }
    fclose(file);

    if(matches==0) printf("\nNo matches found for %s.\n",name);
    else
    {
        header();
        printf("\nStats for %s:\n",name);
        printf(GREEN"Wins:%d, " RESET RED "Losses:%d" RESET,wins,losses);
        printf("\nMatches played:%d\n",matches);
        header();
    }
}

void view_matches() {
    FILE *file = fopen("match_info.txt", "r");
    if (file == NULL) {
        printf("The file could not be opened.\n");
        return;
    }

    char pl1_name[max_name], pl2_name[max_name];
    int pl1_score, pl2_score;

    header3();
    printf("Match History:\n\n");


    while (fscanf(file, "%49[^,],%d,%49[^,],%d\n", pl1_name, &pl1_score, pl2_name, &pl2_score) == 4) {
       if (pl1_score > pl2_score) {
            printf("%s " GREEN "%d" RESET " / " RED "%d" RESET " %s\n", pl1_name, pl1_score, pl2_score, pl2_name);
        } else if (pl2_score > pl1_score) {
            printf("%s " RED "%d" RESET " / " GREEN "%d" RESET " %s\n", pl1_name, pl1_score, pl2_score, pl2_name);
        } else { // if tie
            printf("%s %d / %d %s\n", pl1_name, pl1_score, pl2_score, pl2_name);
        }
    }

    header3();

    fclose(file);
}

int find_player(Player players[], int count, char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void sort_wins(Player players[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (players[j].wins > players[i].wins) {
                Player aux = players[i];
                players[i] = players[j];
                players[j] = aux;
            }
        }
    }
}

void sort_matches(Player players[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (players[j].matches > players[i].matches) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }
}



void generate(Player players[], int *count)
{
      FILE *file = fopen("match_info.txt", "r");
    if (file == NULL) {
        printf("The file could not be opened.\n");
        return;
    }

    char pl1[max_name], pl2[max_name];
    int pl1_score, pl2_score;
    *count = 0;
     while (fscanf(file, "%49[^,],%d,%49[^,],%d\n", pl1, &pl1_score, pl2, &pl2_score) == 4) {
        int index1 = find_player(players, *count, pl1);
        int index2 = find_player(players, *count, pl2);

        if (index1 == -1)
        {
            strcpy(players[*count].name, pl1);
            players[*count].wins = 0;
            players[*count].matches = 0;
            index1 = (*count)++;
        }
        if (index2 == -1)
        {
            strcpy(players[*count].name, pl2);
            players[*count].wins = 0;
            players[*count].matches = 0;
            index2 = (*count)++;
        }

        players[index1].matches++;
        players[index2].matches++;

        if (pl1_score > pl2_score && pl1_score == 21) {
            players[index1].wins++;
        } else if (pl2_score > pl1_score && pl2_score == 21) {
            players[index2].wins++;
        }
    }

    fclose(file);
}
void leaderboard()
{
    Player players[max_players];
    int count;

    generate(players, &count);
    sort_wins(players, count);

    header3();
    printf("\Ranking by most wins:\n");

    for (int i = 0; i < count; i++) {
        printf(BLUE "%s - "RESET "Wins:%d\n", players[i].name, players[i].wins);
    }
    header3();
}
void most_matches() {
    Player players[max_players];
    int count;

    generate(players, &count);
    sort_matches(players, count);

    header3();
    printf("\nRanking by most matches played:\n");
    for (int i = 0; i < count; i++) {
        printf(BLUE "%s " RESET "- Matches: %d\n", players[i].name, players[i].matches);
    }
    header3();
}

void submenu()
{
    int subopt;

    do
    {
        header2();

        printf("1.Leaderboard by most wins:\n");
        printf("2.Leaderboard by most matches played:\n");
        printf("0.Back to main menu.\n");
        header2();
        printf("\nChoose an option:");
        scanf("%d",&subopt);


    switch(subopt)
    {
    case 1:
        leaderboard();
        break;
    case 2:
        most_matches();
        break;
    case 0:
        printf("Returning to main menu...\n");
        system("cls");
        break;
    default:
        printf("Invalid choice!\n");
        system("cls");
        break;

     }
    } while(subopt>0 && subopt<=2);
}


void choice(int option)
{
    switch (option)
    {
    case 1:
        new_match();
        break;
    case 2:
        players_info();
        break;
    case 3:
        submenu();
        break;
    case 4:
        view_matches();
        break;
    case 0:
        printf("Exiting...");
        break;

    default:
        printf("Invalid choice!\n");


    }
}




void main_menu()
{
    printf(PINK"\nMAIN MENU:\n\n"RESET);
    printf(L_BLUE"-----------------------");
    printf("\n1.New match\n");
    printf("2.Players\n");
    printf("3.Leaderboard\n");
    printf("4.View all past matches\n");
    printf("0.Exit\n");
    printf("-----------------------\n"RESET);

}





int main()
{

    int option;
    do{
         main_menu();
         printf("Enter option:\n");
         scanf("%d", &option);
         choice(option);
    }while(option > 0 && option <= 4);

    return 0;
}
