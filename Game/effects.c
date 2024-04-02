

#include "effects.h"

void sbircia(CFU_Cards **mazzo,CFU_Cards **scarti,Player* current)
{
    CFU_Cards *cfu1=*mazzo;
    CFU_Cards *cfu2= (CFU_Cards *) cfu1->next;


    printf("Scelgi quale carta tenere, l'altra verra aggiunta agli scarti\n");
    //int scelta =choose2();
    int scelta=1;
    if (scelta==1)
    {
        //aggiungo la carta 1 alla mano del giocatore;
        add_card_to_hand(current,cfu1);

        add_card_to_scarti(&scarti,&cfu2);

    } else
    {
        //aggiungo la carta 2 alla mano del giocatore

        add_card_to_hand(current,cfu2);

        add_card_to_scarti(scarti,cfu1);
    }

}