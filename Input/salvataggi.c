#include "salvataggi.h"



void printFileContents(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    int numPlayers;
    fread(&numPlayers, sizeof(int), 1, file);

    printf("Number of players: %d\n", numPlayers);

    Player player;


    //for (int i = 0; i < numPlayers; i++) {

    char username[MAX_CHAR];
    Character character;
    int punti;
    char nomeChar[MAX_CHAR];
    int arr[4];

    char stringa[MAX_CHAR];
    int a,b,c,d,e;

    CFU_Cards mano;
    CFU_Cards mano2;

    fread(&player, sizeof(Player), 1, file);
/*
        fread(username,sizeof (username),1,file);
        fread(nomeChar, sizeof(nomeChar),1,file);
        for (int i = 0; i < 4; ++i) {
            fread(&arr[i], sizeof(arr[i]),1,file);
        }
        //fread(&character, sizeof(Character),1,file);
        fread(&punti, sizeof(punti),1,file);

        //fread(&a,sizeof (a),1,file);

        //fread(&player, sizeof(Player), 1, file);
        //printf("%s, %d, %s\n",player.username,player.cfu_score,player.character.name);
        //printf("%p",player.hand);
    fread(stringa,sizeof(4*8),1,file);
        fread(stringa, sizeof(stringa),1,file);
*/
    for (int i=0;i<5;i++) {
        fread(&mano, sizeof(CFU_Cards), 1, file);
        fread(&mano2, sizeof(CFU_Cards), 1, file);
        printf("%s", mano2.name);
    }

    int pazzodicazzo=1000;
}
// Read the number of CFU cards in hand




//////

/*
while (fread(&temp, sizeof(CFU_Cards), 1, file) == 1) {
    CFU_Cards *node = malloc(sizeof(CFU_Cards));
    *node = temp;
    node->next = NULL;

    if (head == NULL) {
        head = node;
    } else {
        current->next = node;
    }
    current = node;
}
print_cards(head);*/







/*
    Player player;
    for (int i = 0; i < numPlayers; i++) {
        fread(&player, sizeof(Player), 1, file);
        // Print the player information here...
    }

    int count=0;
    char buffer[32];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("  %s", buffer);
        count++;

    }
*/
