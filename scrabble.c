#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "scrabble.h"
#include "print_board.h"
char game_board[BOARD_SIZE][BOARD_SIZE];
void task_0()
{
    print_board(game_board);
}
void input(int *X,int *Y,int *D)
{
    char D_ch,c;
    int x;
    int p=1;
    while((c = getchar())!= ' ')//formez Y-ul(linia) pana la spatiu
    {
        x=c-48;
        *Y=*Y*p+x;
        p=10;
    }
    p=1;
    while((c = getchar())!= ' ')//formez X-ul(coloana) pana la spatiu
    {
        x=c-48;
        *X=*X*p+x;
        p=10;
    }
    D_ch=getchar();
    *D=D_ch-48;
    getchar();
}
void asez_pe_tabla(char WORD[15],int X,int Y,int D,int lenght_of_word)
{
    if(D==0)//orizontala
    {
        int i=0;
        while(i<lenght_of_word)
        {
            game_board[Y][X+i]=WORD[i];
            i++;
        }
    }
    else//verticala
    {
        int i=0;
        while(i<lenght_of_word)
        {
            game_board[Y+i][X]=WORD[i];
            i++;
        }
    }
}

void task_1()
{
    int X=0,Y=0,D,N;
    char WORD[15], N_str[100];
    fgets(N_str, sizeof(N_str), stdin);//citesc numarul de linii ca string
    N=atoi(N_str);
    while(N>0)
    {
        input(&X,&Y,&D);
        fgets(WORD,sizeof(WORD), stdin);
        int lenght_of_word=strlen(WORD)-1;
        asez_pe_tabla(WORD,X,Y,D,lenght_of_word);
        N--;
        X=0;
        Y=0;
        D=0;
    }
    print_board(game_board);
}

int functie_scor_fara_bonus(char WORD[15],int lenght_of_word)
{
    int points[26]= {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    int scor_fara_bonus_1=0;

    for(int i=0; i<lenght_of_word; i++)
        scor_fara_bonus_1=scor_fara_bonus_1+points[WORD[i]-'A'];

    return scor_fara_bonus_1;
}

void task_2()
{
    int X=0,Y=0,D,N,player=1,scor_player_1=0,scor_player_2=0;
    char WORD[15], N_str[100];
    fgets(N_str, sizeof(N_str), stdin);//citesc numarul de linii ca string
    N=atoi(N_str);
    while(N>0)
    {
        input(&X,&Y,&D);
        fgets(WORD,sizeof(WORD), stdin);
        int lenght_of_word=strlen(WORD)-1;

        if(player%2!=0)//cuvantul apartine primului player
            scor_player_1=scor_player_1+functie_scor_fara_bonus(WORD,lenght_of_word);

        else//cuvantul apartine celui de-al doilea player
            scor_player_2=scor_player_2+functie_scor_fara_bonus(WORD,lenght_of_word);
        N--;
        X=0;
        Y=0;
        D=0;
        player++;
    }
    printf("Player 1: %d Points\n",scor_player_1);
    printf("Player 2: %d Points\n",scor_player_2);
}


void verificare_substring(char WORD[15],char XX[3],char YY[3],int lenght_of_word,int *okXX,int *okYY)
{
    if(WORD[lenght_of_word-2]==YY[0] && WORD[lenght_of_word-1]==YY[1])//daca are substringul YY la sfarsit
        *okYY=1;
    for(int i=0; i<lenght_of_word-1; i++)
    {
        if(WORD[i]==XX[0] && WORD[i+1]==XX[1])//daca are substringul XX in compozitie
            *okXX=1;
        if(*okXX==1)
            break;
    }
}

int functie_scor_bonus_orizontala(char WORD[15],int Y,int X,int lenght_of_word,int okXX,int okYY)
{
    int i=0,scor_cuvant_1;
    scor_cuvant_1=functie_scor_fara_bonus(WORD,lenght_of_word);
    while(i<lenght_of_word)
    {
        if(bonus_board[Y][X+i]==1)
        {
            if(okXX==1)//are xx in compozitie
                scor_cuvant_1=scor_cuvant_1*2;
        }
        if(bonus_board[Y][X+i]==2)
        {
            if(okYY==1)//are yy la sfarsit
                scor_cuvant_1=scor_cuvant_1*3;
        }
        i++;
    }
    return scor_cuvant_1;
}


int functie_scor_bonus_verticala(char WORD[15],int Y,int X,int lenght_of_word,int okXX,int okYY)
{
    int i=0,scor_cuvant_1;
    scor_cuvant_1=functie_scor_fara_bonus(WORD,lenght_of_word);
    while(i<lenght_of_word)
    {
        if(bonus_board[Y+i][X]==1)
        {
            if(okXX==1)//are xx in compozitie
                scor_cuvant_1=scor_cuvant_1*2;
        }
        if(bonus_board[Y+i][X]==2)
        {
            if(okYY==1)//are yy la sfarsit
                scor_cuvant_1=scor_cuvant_1*3;
        }
        i++;
    }
    return scor_cuvant_1;
}


void task_3()
{
    int X=0,Y=0,D,N,player=1,scor_player_1=0,scor_player_2=0,okYY=0,okXX=0,scor_cuvant_1=1,scor_cuvant_2=1;
    char WORD[15], N_str[100],XX[3],YY[3];

    fgets(XX,sizeof(XX), stdin);//substringul pentru bonusul primit pentru casutele marcate cu 1.
    getchar();
    fgets(YY,sizeof(YY), stdin);//substringul pentru bonusurile primite pentru casutele marcate cu 2.
    getchar();
    fgets(N_str, sizeof(N_str), stdin);//citesc numarul de linii ca string

    N=atoi(N_str);
    while(N>0)
    {
        input(&X,&Y,&D);
        fgets(WORD,sizeof(WORD), stdin);//primesc cuvant

        int lenght_of_word=strlen(WORD)-1;

        verificare_substring(WORD,XX,YY,lenght_of_word,&okXX,&okYY);

        if(player%2!=0)//cuvantul apartine primului player
        {
            scor_cuvant_1=functie_scor_fara_bonus(WORD,lenght_of_word);//daca n-are niciun bonus

            if(D==0)//am cuvantul pe orizontala
                scor_cuvant_1=functie_scor_bonus_orizontala(WORD,Y,X,lenght_of_word,okXX,okYY);

            else//am cuvantul pe verticala
                scor_cuvant_1=functie_scor_bonus_verticala(WORD,Y,X,lenght_of_word,okXX,okYY);

            scor_player_1=scor_player_1+scor_cuvant_1;
        }

        else//sunt pe playerul 2
        {
            scor_cuvant_2=functie_scor_fara_bonus(WORD,lenght_of_word);//daca n-are niciun bonus

            if(D==0)//am cuvantul pe orizontala
                scor_cuvant_2=functie_scor_bonus_orizontala(WORD,Y,X,lenght_of_word,okXX,okYY);

            else//am cuvantul pe verticala
                scor_cuvant_2=functie_scor_bonus_verticala(WORD,Y,X,lenght_of_word,okXX,okYY);

            scor_player_2=scor_player_2+scor_cuvant_2;
        }

        player++;//trec pe celalalt player
        okYY=0;
        okXX=0;
        N--;
        X=0;
        Y=0;
        D=0;
    }
    printf("Player 1: %d Points\n",scor_player_1);
    printf("Player 2: %d Points\n",scor_player_2);
}

int functie_verificare_amplasare_verticala(int m,int n, int lenght_of_new_word)
{
    int OK_verticala=0;
    if( m+lenght_of_new_word-1 < BOARD_SIZE )//daca ar putea fi scris pe verticala
    {
        //pozitii de start pentru verificare suprascriere
        int punct_pornire_linie=m+1, punct_de_pornire_coloana=n;
        int nu_suprascriu=1;//presupun ca nu voi suprascrie
        int next=0,counter_de_litere=0;

        while(counter_de_litere!=lenght_of_new_word-1)
        {
            if(game_board[punct_pornire_linie+next][punct_de_pornire_coloana]!='.')
                nu_suprascriu=0;//presupunere falsa
            next++;
            counter_de_litere++;
        }
        next=0;
        counter_de_litere=0;
        if(nu_suprascriu==1)
            OK_verticala=1;//retin ca acest cuvant poate fi scris pe tabla( pe verticala)
    }
    return OK_verticala;
}

int functie_verificare_amplasare_orizontala(int m,int n, int lenght_of_new_word)
{
    int OK_orizontala=0;
    if( n+lenght_of_new_word-1 < BOARD_SIZE )//daca ar putea fi scris pe orizontala
    {
        //pozitii de start pentru verificare suprascriere
        int punct_pornire_linie=m,punct_de_pornire_coloana=n+1;
        int next=0,counter_de_litere=0;

        int nu_suprascriu=1;//presupun ca nu voi suprascrie pe tabla
        while( counter_de_litere != lenght_of_new_word-1 )
        {
            if(game_board[punct_pornire_linie][punct_de_pornire_coloana+next]!='.')
                nu_suprascriu=0;
            next++;
            counter_de_litere++;
        }
        next=0;
        counter_de_litere=0;

        if(nu_suprascriu==1)
            OK_orizontala=1;//retin ca acest cuvant poate fi scris pe tabla( pe orizontala)
    }
    return OK_orizontala;
}


void task_4()
{
    int X=0,Y=0,D,N;
    char cuvinte_jucate[255][225];
    int nr_cuvinte_jucate=0;
    char XX[3],YY[3],N_str[100],WORD[15];
    fgets(XX,sizeof(XX), stdin);//substringul pentru bonusul primit pentru casutele marcate cu 1.
    getchar();
    fgets(YY,sizeof(YY), stdin);//substringul pentru bonusurile primite pentru casutele marcate cu 2.
    getchar();
    fgets(N_str, sizeof(N_str), stdin);//citesc numarul de linii ca string
    N=atoi(N_str);
    while(N>0)
    {
        input(&X,&Y,&D);
        fgets(WORD,sizeof(WORD), stdin);
        int lenght_of_word=strlen(WORD)-1;
        for(unsigned int i=0; i<strlen(WORD)-1; i++)
            cuvinte_jucate[nr_cuvinte_jucate][i]=WORD[i];

        asez_pe_tabla(WORD,X,Y,D,lenght_of_word);
        nr_cuvinte_jucate++;
        N--;
        X=0;
        Y=0;
        D=0;
    }

    //am pe game_board toate cuvintele jucate pana acum
    int stop=0,cuvant_ok,OK_verticala,OK_orizontala;

    for( int i=0; i < NUM_WORDS && stop!=1; i++ )//incep sa parcurg vectorul words
    {
        cuvant_ok=1;//presupun ca nu a fost jucat inca
        for( int j=0; j < nr_cuvinte_jucate; j++ )
            if(strcmp(words[i],cuvinte_jucate[j])==0)
                cuvant_ok=0;//presupunere falsa

        if(cuvant_ok==1)
        {
            int lenght_of_new_word=strlen(words[i]);
            char c=words[i][0];//primul caracter din cuvantul nou
            for( int m=0; m < BOARD_SIZE && stop!=1; m++ )
            {
                for( int n=0; n <= BOARD_SIZE && stop!=1; n++ )
                {
                    if(game_board[m][n]==c)//gasesc pe tabla primul caracter
                    {
                        OK_verticala=functie_verificare_amplasare_verticala(m,n,lenght_of_new_word);//0 sau 1
                        OK_orizontala=functie_verificare_amplasare_orizontala(m,n,lenght_of_new_word);

                        if((OK_verticala==1 && OK_orizontala==1) || (OK_verticala==0 && OK_orizontala==1))//il voi scrie pe orizontala
                        {
                            int j=0;
                            while(j<lenght_of_new_word)
                            {
                                game_board[m][n+j]=words[i][j];
                                j++;
                            }
                            stop=1;
                        }
                        if( OK_verticala==1 && OK_orizontala==0 )//il voi scrie pe verticala
                        {
                            int j=0;
                            while(j<lenght_of_new_word)
                            {
                                game_board[m+j][n]=words[i][j];
                                j++;
                            }
                            stop=1;
                        }
                    }
                }
            }
        }
    }
    print_board(game_board);
}

int functie_scor_bonus_orizontala_task5(char WORD[15],char XX[3],char YY[3], int Y, int X)
{
    int okYY=0,okXX=0,scor;
    int lenght_of_word=strlen(WORD);

    verificare_substring(WORD,XX,YY,lenght_of_word,&okXX,&okYY);
    scor=functie_scor_bonus_orizontala(WORD,Y,X,lenght_of_word,okXX,okYY);

    return scor;
}

int functie_scor_bonus_verticala_task5(char WORD[15],char XX[3],char YY[3], int Y, int X)
{
    int okYY=0,okXX=0,scor;
    int lenght_of_word=strlen(WORD);

    verificare_substring(WORD,XX,YY,lenght_of_word,&okXX,&okYY);
    scor=functie_scor_bonus_verticala(WORD,Y,X,lenght_of_word,okXX,okYY);
    return scor;
}

void task_5()
{
    char cuvinte_jucate[255][225];
    int nr_cuvinte_jucate=0;
    int X=0,Y=0,D,N,player=1,scor_player_1=0,scor_player_2=0,okYY=0,okXX=0,scor_cuvant_1=1,scor_cuvant_2=1;
    char WORD[15], N_str[100],XX[3],YY[3];

    fgets(XX,sizeof(XX), stdin);//substringul pentru bonusul primit pentru casutele marcate cu 1.
    getchar();
    fgets(YY,sizeof(YY), stdin);//substringul pentru bonusurile primite pentru casutele marcate cu 2.
    getchar();
    fgets(N_str, sizeof(N_str), stdin);//citesc numarul de linii ca string
    N=atoi(N_str);
    while(N>0)
    {
        input(&X,&Y,&D);
        fgets(WORD,sizeof(WORD), stdin);//primesc cuvant
        int lenght_of_word=strlen(WORD)-1;

        for(unsigned int i=0; i<strlen(WORD)-1; i++)//il retin in cuvinte_jucate
            cuvinte_jucate[nr_cuvinte_jucate][i]=WORD[i];

        asez_pe_tabla(WORD,X,Y,D,lenght_of_word);
        nr_cuvinte_jucate++;

        //incep sa calculez punctajul
        verificare_substring(WORD,XX,YY,lenght_of_word,&okXX,&okYY);

        if(player%2!=0)//cuvantul apartine primului player
        {
            scor_cuvant_1=functie_scor_fara_bonus(WORD,lenght_of_word);

            if(D==0)//orizontala
                scor_cuvant_1=functie_scor_bonus_orizontala(WORD,Y,X,lenght_of_word,okXX,okYY);

            else// verticala
                scor_cuvant_1=functie_scor_bonus_verticala(WORD,Y,X,lenght_of_word,okXX,okYY);
            scor_player_1=scor_player_1+scor_cuvant_1;
        }

        else// pe playerul 2
        {
            scor_cuvant_2=functie_scor_fara_bonus(WORD,lenght_of_word);//daca n-are niciun bonus
            if(D==0)// orizontala
                scor_cuvant_2=functie_scor_bonus_orizontala(WORD,Y,X,lenght_of_word,okXX,okYY);

            else// verticala
                scor_cuvant_2=functie_scor_bonus_verticala(WORD,Y,X,lenght_of_word,okXX,okYY);

            scor_player_2=scor_player_2+scor_cuvant_2;
        }
        player++;//trec pe celalalt player
        okYY=0;
        okXX=0;
        scor_cuvant_1=1;
        scor_cuvant_2=1;
        N--;
        X=0;
        Y=0;
        D=0;
    }
//am toate cuvintele pe game_board, cuvintele jucate retinute si cele doua scoruri
//urmeaza sa calculez scorul pt fiecare cuvant din words+bonus si sa verific daca poate fi pus pe tabla

    int scoruri[NUM_WORDS][4];
    for(int i=0; i<NUM_WORDS; i++) //matrice pt scor optim, directie,linie,coloana
    {
        scoruri[i][0]=-9999;
        scoruri[i][1]=-9999;
        scoruri[i][2]=-9999;
        scoruri[i][3]=-9999;
    }
    int cuvant_ok;
    for(int i=0; i<NUM_WORDS; i++)//incep sa parcurg vectorul words
    {
        int lenght_of_new_word=strlen(words[i]);
        cuvant_ok=1;//presupun ca nu a fost jucat inca

        for(int j=0; j<nr_cuvinte_jucate; j++)
            if(strcmp(words[i],cuvinte_jucate[j])==0)
                cuvant_ok=0;//presupunere falsa

        if(cuvant_ok==1)
        {
            int OK_verticala,OK_orizontala;
            char c=words[i][0];//primul caracter din cuvantul nou

            for(int m=0; m < BOARD_SIZE ; m++)
            {
                for(int n=0; n< BOARD_SIZE; n++)
                {
                    if(game_board[m][n]==c)//gasesc pe tabla primul caracter
                    {
                        OK_verticala=0;
                        OK_orizontala=0;

                        OK_verticala=functie_verificare_amplasare_verticala(m,n,lenght_of_new_word);
                        OK_orizontala=functie_verificare_amplasare_orizontala(m,n,lenght_of_new_word);

                        if( OK_orizontala==1 ||OK_verticala==1 )
                        {
                            int scor_cuvant_verticala=-9999;
                            int scor_cuvant_orizontala=-9999;

                            if(OK_verticala==1)//calculez scorul pe care l-ar obtine pe verticala
                                scor_cuvant_verticala=functie_scor_bonus_verticala_task5(words[i],XX,YY,m,n);

                            if(OK_orizontala==1)//calculez scorul pe care l-ar obtine pe orizontalA
                                scor_cuvant_orizontala=functie_scor_bonus_orizontala_task5(words[i],XX,YY,m,n);


                            if(scor_cuvant_verticala > scor_cuvant_orizontala && scor_cuvant_verticala > scoruri[i][0])
                            {
                                scoruri[i][0]=scor_cuvant_verticala;
                                scoruri[i][1]=1;//retin ca il voi pune verticala
                                scoruri[i][2]=m;
                                scoruri[i][3]=n;
                            }
                            if(scor_cuvant_verticala<=scor_cuvant_orizontala &&  scor_cuvant_orizontala > scoruri[i][0])
                            {
                                scoruri[i][0]=scor_cuvant_orizontala;
                                scoruri[i][1]=0;//retin ca il voi pune pe orizontala
                                scoruri[i][2]=m;
                                scoruri[i][3]=n;
                            }
                        }
                    }
                }
            }
        }
    }

    int scor_optim_maxim=-1,directie,linie,coloana,pozitie_in_words;

    //stabilesc scorul maxim, si carui cuvant apartine
    for(int i=0; i < NUM_WORDS; i++)
        if(scoruri[i][0]>scor_optim_maxim)
        {
            scor_optim_maxim=scoruri[i][0];
            directie=scoruri[i][1];
            linie=scoruri[i][2];
            coloana=scoruri[i][3];
            pozitie_in_words=i;
        }

    //stabilesc cuvantul cu scor maxim si linie minima
    for(int i=0; i<NUM_WORDS; i++)
        if(scoruri[i][0]==scor_optim_maxim && scoruri[i][2]<linie)
        {
            directie=scoruri[i][1];
            linie=scoruri[i][2];
            coloana=scoruri[i][3];
            pozitie_in_words=i;
        }

    //stabilesc cuvantul cu scor maxim, linie minima si coloana minima
    for(int i=0; i<NUM_WORDS; i++)
        if(scoruri[i][0]==scor_optim_maxim && scoruri[i][2]==linie && scoruri[i][3]<coloana)
        {
            directie=scoruri[i][1];
            coloana=scoruri[i][3];
            pozitie_in_words=i;
        }

    if(scor_player_2+scor_optim_maxim<scor_player_1)
        printf("Fail!");

    else
    {
        int lungime=strlen(words[pozitie_in_words]);
        asez_pe_tabla(words[pozitie_in_words],coloana,linie,directie,lungime);
        print_board(game_board);
    }
}

void task_6()
{
    char cuvinte_jucate[255][225];
    int nr_cuvinte_jucate=0;
    int X=0,Y=0,D,N,scor_player_1=0,okYY=0,okXX=0,scor_player_2=0,scor_cuvant_1=1;
    char WORD[16], N_str[100],XX[3],YY[3];

    fgets(XX,sizeof(XX), stdin);//substringul pentru bonusul primit pentru casutele marcate cu 1.
    getchar();
    fgets(YY,sizeof(YY), stdin);//substringul pentru bonusurile primite pentru casutele marcate cu 2.
    getchar();
    fgets(N_str, sizeof(N_str), stdin);//citesc numarul de linii ca string

    N=atoi(N_str);
    while(N>0)
    {
        input(&X,&Y,&D);
        fgets(WORD,sizeof(WORD), stdin);//primesc cuvant

        int lenght_of_word=strlen(WORD)-1;
        verificare_substring(WORD,XX,YY,lenght_of_word,&okXX,&okYY);

        scor_cuvant_1=functie_scor_fara_bonus(WORD,lenght_of_word);//daca n-are niciun bonus

        if(D==0)// orizontala
            scor_cuvant_1=functie_scor_bonus_orizontala(WORD,Y,X,lenght_of_word,okXX,okYY);

        else// verticala
            scor_cuvant_1=functie_scor_bonus_verticala(WORD,Y,X,lenght_of_word,okXX,okYY);


        asez_pe_tabla(WORD,X,Y,D,lenght_of_word);

        scor_player_1=scor_player_1+scor_cuvant_1;

        for(unsigned int i=0; i<strlen(WORD)-1; i++)//il retin in cuvinte_jucate
            cuvinte_jucate[nr_cuvinte_jucate][i]=WORD[i];
        nr_cuvinte_jucate++;

        int scoruri[NUM_WORDS][4];
        for(int i=0; i<NUM_WORDS; i++) 
        {
            scoruri[i][0]=-9999;
            scoruri[i][1]=-9999;
            scoruri[i][2]=-9999;
            scoruri[i][3]=-9999;
        }
        int cuvant_ok;
        for(int i=0; i<NUM_WORDS; i++)//incep sa parcurg vectorul words
        {
            int lenght_of_new_word=strlen(words[i]);
            cuvant_ok=1;//presupun ca nu a fost jucat inca
            for(int j=0; j<nr_cuvinte_jucate; j++)
                if(strcmp(words[i],cuvinte_jucate[j])==0)
                    cuvant_ok=0;//presupunere falsa

            if(cuvant_ok==1)
            {
                int OK_verticala,OK_orizontala;
                char c=words[i][0];//primul caracter din cuvantul nou

                for(int m=0; m < BOARD_SIZE ; m++)
                {
                    for(int n=0; n< BOARD_SIZE; n++)
                    {
                        if(game_board[m][n]==c)//gasesc pe tabla primul caracter
                        {
                            OK_verticala=0;
                            OK_orizontala=0;

                            OK_verticala=functie_verificare_amplasare_verticala(m,n,lenght_of_new_word);
                            OK_orizontala=functie_verificare_amplasare_orizontala(m,n,lenght_of_new_word);

                            if(OK_orizontala==1 ||OK_verticala==1)
                            {
                                int scor_cuvant_verticala=-9999;
                                int scor_cuvant_orizontala=-9999;

                                if(OK_verticala==1)//calculez scorul pe care l-ar obtine pe verticala
                                    scor_cuvant_verticala=functie_scor_bonus_verticala_task5(words[i],XX,YY,m,n);

                                if(OK_orizontala==1)//calculez scorul pe care l-ar obtine pe orizontala
                                    scor_cuvant_orizontala=functie_scor_bonus_orizontala_task5(words[i],XX,YY,m,n);

                                if(scor_cuvant_verticala > scor_cuvant_orizontala && scor_cuvant_verticala > scoruri[i][0])
                                {
                                    scoruri[i][0]=scor_cuvant_verticala;
                                    scoruri[i][1]=1;//retin ca il voi pune verticala
                                    scoruri[i][2]=m;
                                    scoruri[i][3]=n;
                                }
                                if(scor_cuvant_verticala<=scor_cuvant_orizontala &&  scor_cuvant_orizontala > scoruri[i][0])
                                {
                                    scoruri[i][0]=scor_cuvant_orizontala;
                                    scoruri[i][1]=0;//retin ca il voi pune pe orizontala
                                    scoruri[i][2]=m;
                                    scoruri[i][3]=n;
                                }
                            }
                        }
                    }
                }
            }
        }

        int scor_optim_maxim=-1,directie,linie,coloana,pozitie_in_words;

        for(int i=0; i < NUM_WORDS; i++)
        {
            for(int j=0; j<nr_cuvinte_jucate; j++ )
                if(strcmp(words[i],cuvinte_jucate[j])==0)
                    scoruri[i][0]=-9999;
        }

        for(int i=0; i < NUM_WORDS; i++)
            if(scoruri[i][0]>scor_optim_maxim)
            {
                scor_optim_maxim=scoruri[i][0];
                directie=scoruri[i][1];
                linie=scoruri[i][2];
                coloana=scoruri[i][3];
                pozitie_in_words=i;
            }

        for(int i=0; i<NUM_WORDS; i++)
            if(scoruri[i][0]==scor_optim_maxim && scoruri[i][2]<linie)
            {
                directie=scoruri[i][1];
                linie=scoruri[i][2];
                coloana=scoruri[i][3];
                pozitie_in_words=i;
            }

        for(int i=0; i<NUM_WORDS; i++)
            if(scoruri[i][0]==scor_optim_maxim && scoruri[i][2]==linie && scoruri[i][3]<coloana)
            {
                directie=scoruri[i][1];
                coloana=scoruri[i][3];
                pozitie_in_words=i;
            }

        for(unsigned int i=0; i<strlen(words[pozitie_in_words]); i++)//il retin in cuvinte_jucate
            cuvinte_jucate[nr_cuvinte_jucate][i]=words[pozitie_in_words][i];
        nr_cuvinte_jucate++;

        scor_player_2=scor_player_2+scor_optim_maxim;
        int lungime=strlen(words[pozitie_in_words]);
        asez_pe_tabla(words[pozitie_in_words],coloana,linie,directie,lungime);

        okYY=0;
        okXX=0;
        N--;
        X=0;
        Y=0;
        D=0;
    }

    print_board(game_board);
    if(scor_player_2>scor_player_1)
        printf("Player 2 Won!");
    else
        printf("Player 1 Won!");

}
int main()
{
    //INITIALIZARE MATRICE
    for(int i=0; i<BOARD_SIZE; i++)
        for(int j=0; j<BOARD_SIZE; j++)
            game_board[i][j]='.';

    int nr_task;
    nr_task=getchar();
    getchar();
    if(nr_task-48==0)//taskul 0
        task_0();
    if(nr_task-48==1)//taskul 1
        task_1();
    if(nr_task-48==2)//taskul 2
        task_2();
    if(nr_task-48==3)
        task_3();
    if(nr_task-48==4)
        task_4();
    if(nr_task-48==5)
        task_5();
    if(nr_task-48==6)
        task_6();
    return 0;
}
