#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>

//consts
#define VERSION				"1.0.0"
#define AUTHOR 				"Edoardo Stucchi"
#define MOSSE				3
#define FLAGS				4
#define ITEMS				1
#define MAX_NPCS			16
#define DEBUG_MODE			TRUE
//bool
#define boolean				int
#define FALSE				0
#define TRUE				1
//dir
#define DIRECTION_UP		0
#define DIRECTION_RIGHT		1
#define DIRECTION_BOTTOM	2
#define DIRECTION_LEFT		3
//simboli
#define SIMBOLO_YOU			'O'
#define SIMBOLO_NPC			'o'
#define SIMBOLO_ERBA_BASSA	'w'
#define SIMBOLO_ERBA_ALTA	'W'
#define SIMBOLO_POKEMON_NPC	'&'
#define SIMBOLO_LEG_PKM_NPC	'%'
#define SIMBOLO_OSTACOLO	'X'
#define SIMBOLO_ALBERO		'A'
#define SIMBOLO_EVENTO		'^'
#define SIMBOLO_CARTELLO	'T'
#define SIMBOLO_NONE		' '
#define SIMBOLO_ACQUA_BASSA	's'
#define SIMBOLO_ACQUA_ALTA	'S'
#define SIMBOLO_MURO_SS		'-'
#define SIMBOLO_MURO_LATO	'|'
#define SIMBOLO_GRADINO		'_'
//colors
#define COLOR_WHITE			0
#define COLOR_RED			1
#define COLOR_BOLD_RED		2
#define COLOR_GREEN			3
#define COLOR_BOLD_GREEN	4
#define COLOR_YELLOW		5
#define COLOR_BOLD_YELLOW	6
#define COLOR_BLUE			7
#define COLOR_BOLD_BLUE		8
#define COLOR_MAGENTA		9
#define COLOR_BOLD_MAGENTA	10
#define COLOR_CYAN			11
#define COLOR_BOLD_CYAN		12
#define COLOR_GRAY			13
//sessi
#define SEX_NONE			0
#define SEX_MALE			1
#define SEX_FEMALE			2
//tipi di eventi
#define EVENT_WALK			0
#define EVENT_ACTION		1
//states
#define STATE_NORMAL		0
//tipi
#define TIPO_NONE			-1
#define TIPO_NORMALE		0
#define TIPO_ERBA			1
#define TIPO_FUOCO			2
#define TIPO_ACQUA			3
//items
#define ITEM_POZIONE		0
//borsa
#define BORSA_STRUMENTI		0
#define BORSA_RIMEDI		1
#define BORSA_POKEBALL		2
#define BORSA_MT_MN			3
#define BORSA_BACCHE		4
#define BORSA_MESSAGGI		5
#define BORSA_STRUM_LOTTA	6
#define BORSA_STRM_BASE		7
//mosse
#define MOSSA_AZIONE		0
#define MOSSA_GRAFFIO		1
#define MOSSA_BOTTA			2
//PKM
#define PKM_TARTWIG			0
#define PKM_CHIMCHAR		1
#define PKM_PIPLUP			2

//strutture dati
typedef struct
{
	int id;
	int pp;
    int ppMax;
    int atk;
    int precision;
    int tipo;
    char nome[64];
} mossa;

typedef struct
{
	int id;
	char nome[64];
	int amount;
	int borsa;
} item;

typedef struct
{
	int id;
	int sex;
	int tipo1;
	int tipo2;
	int state;
	int ps;
	int psMax;
	int atk;
	int def;
	int atkSp;
	int defSp;
	int speed;
	int precision;
	int elusion;
	int numMosse;
	int exp;
	int lvl;
	int nextExp;
    int lvlToEvolve;
    char nome[64];
    boolean catturabile;
    boolean item;
    item strum;
    mossa mosse[4];
} pokemon;

typedef struct
{
	int x;
	int y;
    int sex;
    int numPokemon;
    int money;
    int medals;
    int catturati;
    int dir;
    boolean valid;
    char nome[64];
    char occupazione[64];
    pokemon squadra[6];
} allenatore;

typedef struct
{
    char tileChar;
    boolean isEvento;
    boolean solid;
    int tipo;
    int color;
    void (*action)(void);
} tile;

//variabili globali
allenatore you, rivale, npcs[MAX_NPCS];
tile mappa[128][128];
item items[ITEMS];
boolean flags[FLAGS];
int idMappa = 0, r = 0, c = 0;

//funzioni
void gameLogic();
void loadItems();
void loadMossa(mossa*, int);
void loadMappa(int, tile*, int, int);
void stampaMappa(tile*, boolean);
void setColor(int);
void delay(int);
void showConsoleCursor(boolean);

//eventi
void event0();
void event1();
void event2();
void event3_0();
void event3_1();
void event4();
void event5();
void event6();
void event7();
void event8();
void event9();
void event10();
void event11();
void event12();
void event13();
void event14();
void event15();
void event16();
void event17();
void event18();
void event19();
void event20();
void event21();
void event22();
void event23();
void event24();
void event25();
void event26();
void event27();
void event28();
void event29();
void event30();
void event31();

//funzioni di battaglia
boolean lotta(allenatore*, int, int);
void lvlUp(pokemon*, int);
void stampaPokemon(allenatore*, int, int);
void funzioneMossa(pokemon*, pokemon*, int);

int main()
{
	int cont = 0, i, j;
	char input;

	loadItems();
	showConsoleCursor(FALSE);
	srand((unsigned) time(NULL));

	system("cls");
    printf("Benvenuto alla versione %s di pokemon creata da %s.\n", VERSION, AUTHOR);
	system("PAUSE");

	do
	{
		system("cls");
		printf("Scegli un'opzione:\n");

		if(cont == 0)
			printf("> Nuovo <\n");
		else
			printf("  Nuovo\n");

		if(cont == 1)
			printf("> Carica <\n");
		else
			printf("  Carica\n");

		fflush(stdin);
		input = getch();

		switch(input)
		{
		case 72:
			if(cont == 0)
				cont = 1;
			else
				cont--;
			break;
		case 80:
			if(cont == 1)
				cont = 0;
			else
				cont++;
			break;
		}
	} while(input != 13);

	system("cls");

	if(cont == 0)
	{
		you.numPokemon = 0;
		you.money = 500;
		you.medals = 0;
		you.catturati = 0;
		strcpy(you.occupazione, "");
		you.dir = DIRECTION_UP;
		rivale.numPokemon = 0;
		rivale.money = 0;
		rivale.sex = SEX_MALE;
		rivale.catturati = 0;
		rivale.medals = 0;
		strcpy(rivale.occupazione, "Rivale");
		rivale.dir = DIRECTION_UP;

		//discorso iniziale del prof. rowan
		printf("Ciao, felice di conoscerti!\n");
		getch();
		system("cls");
		printf("Ti do il benvenuto nel mondo dei Pokemon!\n");
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("Il mio nome e' Rowan, ma per tutti sono il Prof. Pokemon.\n");
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("Questo mondo e' abitato da creature chiamate Pokemon.\n");
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("Ecco, questa e' una Pokeball.\n");
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("Premi un tasto qualsiasi.\n");
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		delay(1000);
		system("cls");
		printf("\t%c%c\t\n", SIMBOLO_POKEMON_NPC, SIMBOLO_NPC);
		delay(1000);
		printf("Noi umani viviamo al fianco dei pokemon, che sono nostri amici fedeli.\n");
		getch();
		system("cls");
		printf("\t%c%c\t\n", SIMBOLO_POKEMON_NPC, SIMBOLO_NPC);
		printf("A volte i Pokemon sono compagni di gioco, a volte preziosi collaboratori.\n");
		getch();
		system("cls");
		printf("\t%c%c\t\n", SIMBOLO_POKEMON_NPC, SIMBOLO_NPC);
		printf("Alcuni di noi si coalizzano con i Pokemon per sfidare altre persone, stabilendo con essi un profondo legame.\n");
		getch();
		system("cls");
		printf("\t%c%c\t\n", SIMBOLO_POKEMON_NPC, SIMBOLO_NPC);
		printf("Cosa faccio io?.\n");
		getch();
		system("cls");
		printf("\t%c%c\t\n", SIMBOLO_POKEMON_NPC, SIMBOLO_NPC);
		printf("Mi dedico alla ricerca sui Pokemon, per saperne sempre di piu'.\n");
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("Prima di tutto, parlami un po' di te!\n");
		getch();

		boolean flag = FALSE;

		while(!flag)
		{
			input = 0;
			cont = 0;

			do
			{
				system("cls");
				printf("Sei una ragazza o un ragazzo?\n");

				if(cont == 0)
					printf("> %c <\n", SIMBOLO_NPC);
				else
					printf("  %c\n", SIMBOLO_NPC);

				if(cont == 1)
					printf("> %c <\n", SIMBOLO_NPC);
				else
					printf("  %c\n", SIMBOLO_NPC);

				if(cont == 0)
					printf("RAGAZZA\n");
				else if(cont == 1)
					printf("RAGAZZO\n");

				fflush(stdin);
				input = getch();

				switch(input)
				{
				case 72:
					if(cont == 0)
						cont = 1;
					else
						cont--;
					break;
				case 80:
					if(cont == 1)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(input != 13);

			if(cont == 0)
				you.sex = SEX_FEMALE;
			else if(cont == 1)
				you.sex = SEX_MALE;

			input = 0;
			cont = 0;

			do
			{
				system("cls");
				if(you.sex == SEX_MALE)
					printf("Ah, allora sei un ragazzo!\n");
				else
					printf("Ah, allora sei una ragazza!\n");

				if(cont == 0)
					printf("> SI' <\n");
				else
					printf("  SI'\n");

				if(cont == 1)
					printf("> NO <\n");
				else
					printf("  NO\n");

				fflush(stdin);
				input = getch();

				switch(input)
				{
				case 72:
					if(cont == 0)
						cont = 1;
					else
						cont--;
					break;
				case 80:
					if(cont == 1)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(input != 13);

			if(cont == 0)
				flag = TRUE;
		}

		flag = FALSE;

		while(!flag)
		{
			system("cls");
			printf("Come ti chiami?\n");
			showConsoleCursor(TRUE);

			do
			{
				fflush(stdin);
				gets(you.nome);
			} while(strcmp(you.nome, "") == 0 || strcmp(you.nome, "\0") == 0);

            input = 0;
            cont = 0;
            showConsoleCursor(FALSE);

            do
			{
				system("cls");
				printf("Ti chiami %s, giusto?\n", you.nome);

				if(cont == 0)
					printf("> SI' <\n");
				else
					printf("  SI'\n");

				if(cont == 1)
					printf("> NO <\n");
				else
					printf("  NO\n");

				fflush(stdin);
				input = getch();

				switch(input)
				{
				case 72:
					if(cont == 0)
						cont = 1;
					else
						cont--;
					break;
				case 80:
					if(cont == 1)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(input != 13);

			if(cont == 0)
				flag = TRUE;
		}

		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("Ok...\nE cosi' tu sei %s?\n", you.nome);
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("E' proprio un bel nome!\n", you.nome);
		getch();
		system("cls");
		printf("\t %c\t\n", SIMBOLO_NPC);
		printf("E questo invece...\nPenso che sia un tuo amico.\n", you.nome);
		getch();

		flag = FALSE;

		while(!flag)
		{
			input = 0;
			cont = 0;

            do
			{
				system("cls");
				printf("Come si chiama?\n");
				printf("\t %c\t\n", SIMBOLO_NPC);

				if(cont == 0)
					printf("> Nuovo <\n");
				else
					printf("  Nuovo\n");

				if(cont == 1)
					printf("> Alvise <\n");
				else
					printf("  Alvise\n");

				if(cont == 2)
					printf("> Rolando <\n");
				else
					printf("  Rolando\n");

				if(cont == 3)
					printf("> Ricky <\n");
				else
					printf("  Ricky\n");

				if(cont == 4)
					printf("> Gino <\n");
				else
					printf("  Gino\n");

				fflush(stdin);
				input = getch();

				switch(input)
				{
				case 72:
					if(cont == 0)
						cont = 4;
					else
						cont--;
					break;
				case 80:
					if(cont == 4)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(input != 13);

			switch(cont)
			{
			case 0:
				system("cls");
				printf("Come si chiama?\n");
				showConsoleCursor(TRUE);

				do
				{
					fflush(stdin);
					gets(rivale.nome);
				} while(strcmp(rivale.nome, "") == 0 || strcmp(rivale.nome, "\0") == 0);
				showConsoleCursor(FALSE);
				break;
			case 1:
				strcpy(rivale.nome, "Alvise");
				break;
			case 2:
				strcpy(rivale.nome, "Rolando");
				break;
			case 3:
				strcpy(rivale.nome, "Ricky");
				break;
			case 4:
				strcpy(rivale.nome, "Gino");
				break;
			}

			input = 0;
            cont = 0;

            do
			{
				system("cls");
				printf("Hai detto %s?\nSi chiama cosi' il tuo amico?\n", rivale.nome);

				if(cont == 0)
					printf("> SI' <\n");
				else
					printf("  SI'\n");

				if(cont == 1)
					printf("> NO <\n");
				else
					printf("  NO\n");

				fflush(stdin);
				input = getch();

				switch(input)
				{
				case 72:
					if(cont == 0)
						cont = 1;
					else
						cont--;
					break;
				case 80:
					if(cont == 1)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(input != 13);

			if(cont == 0)
				flag = TRUE;
		}

        system("cls");
        printf("\t %c\t\n", SIMBOLO_NPC);
        printf("Bene, %s, e' arrivato il grande momento.\n", you.nome);
        getch();
        system("cls");
        printf("\t %c\t\n", SIMBOLO_NPC);
        printf("Nel corso del viaggio, incontrerai molte persone e Pokemon.\n");
        getch();
        system("cls");
        printf("\t %c\t\n", SIMBOLO_NPC);
        printf("Di sicuro farai tante scoperte e imparerai qualcosa anche su di te.\n");
        getch();
        system("cls");
        printf("\t %c\t\n", SIMBOLO_NPC);
        printf("E adesso, vai! Tuffati nel meraviglioso mondo dei Pokemon!\n");
        getch();

        //inizio del gioco
        for(i = 0; i < FLAGS; i++)
			flags[i] = FALSE;
        loadMappa(idMappa, (tile*) mappa, 4, 3);
		gameLogic();
	}
	else if(cont == 1)
	{
		int realX, realY;
		FILE *save = fopen("saves/save.data", "r");

		if(!save)
		{
			printf("Non e' presente alcuna partita salvata.\n");
			getch();
			exit(0);
		}
		else
		{
            fscanf(save, "x=%d\n", &realX);
            fscanf(save, "y=%d\n", &realY);
            fscanf(save, "mapId=%d\n", &idMappa);
            fseek(save, 7, SEEK_CUR);
            fgets(you.nome, 64, save);
            you.nome[strlen(you.nome) - 1] = '\0';
            fscanf(save, "y_money=%d\n", &you.money);
            fscanf(save, "y_catturati=%d\n", &you.catturati);
            fscanf(save, "y_dir=%d\n", &you.dir);
            fscanf(save, "y_sex=%d\n", &you.sex);
            fscanf(save, "y_numPokemon=%d\n", &you.numPokemon);
            fscanf(save, "y_medals=%d\n", &you.medals);

            for(i = 0; i < you.numPokemon; i++)
			{
				fseek(save, 8, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].id);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].sex);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].tipo1);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].tipo2);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].state);
				fseek(save, 8, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].ps);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].psMax);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].atk);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].def);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].atkSp);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].defSp);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].speed);
				fseek(save, 10, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].precision);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].elusion);
				fseek(save, 14, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].numMosse);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].exp);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].lvl);
				fseek(save, 13, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].nextExp);
				fseek(save, 17, SEEK_CUR);
				fscanf(save, "%d\n", &you.squadra[i].lvlToEvolve);
				fseek(save, 10, SEEK_CUR);
				fscanf(save, "%s\n", &you.squadra[i].nome);

				for(j = 0; j < you.squadra[i].numMosse; j++)
				{
					fseek(save, 11, SEEK_CUR);
					fscanf(save, "%d\n", &you.squadra[i].mosse[j].id);
					fseek(save, 11, SEEK_CUR);
					fscanf(save, "%d\n", &you.squadra[i].mosse[j].pp);
					fseek(save, 14, SEEK_CUR);
					fscanf(save, "%d\n", &you.squadra[i].mosse[j].ppMax);
					fseek(save, 12, SEEK_CUR);
					fscanf(save, "%d\n", &you.squadra[i].mosse[j].atk);
					fseek(save, 18, SEEK_CUR);
					fscanf(save, "%d\n", &you.squadra[i].mosse[j].precision);
					fseek(save, 13, SEEK_CUR);
					fscanf(save, "%d\n", &you.squadra[i].mosse[j].tipo);
					fseek(save, 13, SEEK_CUR);
					fgets(you.squadra[i].mosse[j].nome, 64, save);
				}
			}

            fseek(save, 7, SEEK_CUR);
            fgets(rivale.nome, 64, save);
            rivale.nome[strlen(rivale.nome) - 1] = '\0';
            fseek(save, 14, SEEK_CUR);
            fgets(rivale.occupazione, 64, save);
            rivale.occupazione[strlen(rivale.occupazione) - 1] = '\0';
            fscanf(save, "r_money=%d\n", &rivale.money);
            fscanf(save, "r_catturati=%d\n", &rivale.catturati);
            fscanf(save, "r_dir=%d\n", &rivale.dir);
            fscanf(save, "r_sex=%d\n", &rivale.sex);
            fscanf(save, "r_numPokemon=%d\n", &rivale.numPokemon);
            fscanf(save, "r_medals=%d\n", &rivale.medals);

            for(i = 0; i < rivale.numPokemon; i++)
			{
				fseek(save, 8, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].id);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].sex);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].tipo1);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].tipo2);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].state);
				fseek(save, 8, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].ps);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].psMax);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].atk);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].def);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].atkSp);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].defSp);
				fseek(save, 11, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].speed);
				fseek(save, 10, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].precision);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].elusion);
				fseek(save, 14, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].numMosse);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].exp);
				fseek(save, 9, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].lvl);
				fseek(save, 13, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].nextExp);
				fseek(save, 17, SEEK_CUR);
				fscanf(save, "%d\n", &rivale.squadra[i].lvlToEvolve);
				fseek(save, 10, SEEK_CUR);
				fscanf(save, "%s\n", &rivale.squadra[i].nome);

				for(j = 0; j < rivale.squadra[i].numMosse; j++)
				{
					fseek(save, 11, SEEK_CUR);
					fscanf(save, "%d\n", &rivale.squadra[i].mosse[j].id);
					fseek(save, 11, SEEK_CUR);
					fscanf(save, "%d\n", &rivale.squadra[i].mosse[j].pp);
					fseek(save, 14, SEEK_CUR);
					fscanf(save, "%d\n", &rivale.squadra[i].mosse[j].ppMax);
					fseek(save, 12, SEEK_CUR);
					fscanf(save, "%d\n", &rivale.squadra[i].mosse[j].atk);
					fseek(save, 18, SEEK_CUR);
					fscanf(save, "%d\n", &rivale.squadra[i].mosse[j].precision);
					fseek(save, 13, SEEK_CUR);
					fscanf(save, "%d\n", &rivale.squadra[i].mosse[j].tipo);
					fseek(save, 13, SEEK_CUR);
					fgets(rivale.squadra[i].mosse[j].nome, 64, save);
				}
			}
            for(i = 0; i < ITEMS; i++)
				fscanf(save, "%d\n", &items[i].amount);

            for(i = 0; i < FLAGS; i++)
				fscanf(save, "%d\n", &flags[i]);
		}

		fclose(save);

		//carica partita
		loadMappa(idMappa, (tile*) mappa, realX, realY);
		gameLogic();
	}

	system("PAUSE");

	return 0;
}

void gameLogic()
{
	char input;
	int cont, i;
	boolean flag = FALSE;

	while(!flag)
	{
		system("cls");

		stampaMappa((tile*) mappa, FALSE);

		fflush(stdin);
		input = getch();

		switch(input)
		{
		case 97: //A
			you.dir = DIRECTION_LEFT;
			if(!(*((tile*) mappa + (you.y * c) + you.x - 1)).solid && (*((tile*) mappa + (you.y * c) + you.x - 1)).tileChar != SIMBOLO_GRADINO)
				you.x--;
			break;
		case 100: //D
			you.dir = DIRECTION_RIGHT;
			if(!(*((tile*) mappa + (you.y * c) + you.x + 1)).solid && (*((tile*) mappa + (you.y * c) + you.x + 1)).tileChar != SIMBOLO_GRADINO)
				you.x++;
			break;
		case 101: //E
		{
			cont = 0;
			input = 0;

			do
			{
				system("cls");

				setColor(COLOR_WHITE);

				stampaMappa((tile*) mappa, FALSE);

				if(cont == 0)
				{
					setColor(COLOR_WHITE);
					printf("> ");
					setColor(COLOR_GRAY);
					printf("Pokedex");
					setColor(COLOR_WHITE);
					printf(" <\n");
				}
				else
				{
					setColor(COLOR_GRAY);
					printf("  Pokedex\n");
				}

				if(cont == 1)
				{
					setColor(COLOR_WHITE);
					printf("> ");
					if(!flags[2])
						setColor(COLOR_GRAY);
					printf("Pokemon");
					setColor(COLOR_WHITE);
					printf(" <\n");
				}
				else
				{
					setColor(COLOR_WHITE);
					if(!flags[2])
						setColor(COLOR_GRAY);
					printf("  Pokemon\n");
				}

				setColor(COLOR_WHITE);

				if(cont == 2)
					printf("> Borsa <\n");
				else
					printf("  Borsa\n");

				if(cont == 3)
					printf("> %s <\n", you.nome);
				else
					printf("  %s\n", you.nome);

				if(cont == 4)
					printf("> Salva <\n");
				else
					printf("  Salva\n");

				if(cont == 5)
					printf("> Esci Dal Menu <\n");
				else
					printf("  Esci Dal Menu\n");

				if(cont == 6)
					printf("> Esci Dal Gioco <\n");
				else
					printf("  Esci Dal Gioco\n");

				fflush(stdin);
				input = getch();

				switch(input)
				{
				case 13:
					if(cont == 0 || (cont == 1 && !flags[2]))
						input = 0;
					break;
				case 72:
					if(cont == 0)
						cont = 6;
					else
						cont--;
					break;
				case 80:
					if(cont == 6)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(input != 13 && input != 101);

			if(input == 13)
			{
				switch(cont)
				{
				case 1: //pokemon
				{
					if(flags[2])
					{
						int i;

						for(i = 0; i < you.numPokemon; i++)
						{
							stampaMappa((tile*) mappa, FALSE);
							printf("Squadra Pokemon:\n");
							printf("%s\n", you.squadra[i].nome);
						}

						getch();
					}
					break;
				}
				case 2: //borsa
				{
					int pagina = 0, list = 0;
					char in;
					cont = 0;

					do
					{
						stampaMappa((tile*) mappa, FALSE);

						switch(pagina)
						{
						case BORSA_STRUMENTI:
							printf("< Strumenti >\n");
							break;
						case BORSA_RIMEDI:
							printf("< Rimedi >\n");
							break;
						case BORSA_POKEBALL:
							printf("< Pokeball >\n");
							break;
						case BORSA_MT_MN:
							printf("< MN e MT >\n");
							break;
						case BORSA_BACCHE:
							printf("< Bacche >\n");
							break;
						case BORSA_MESSAGGI:
							printf("< Messaggi >\n");
							break;
						case BORSA_STRUM_LOTTA:
							printf("< Strumenti Lotta >\n");
							break;
						case BORSA_STRM_BASE:
							printf("< Strumenti Base >\n");
							break;
						}

						for(i = 0; i < ITEMS; i++)
						{
							if(items[i].borsa == pagina && items[i].amount > 0)
							{
								if(cont == list)
									printf("> %s: x%d <\n", items[i].nome, items[i].amount);
								else
									printf("> %s: x%d <\n", items[i].nome, items[i].amount);
								list++;
							}
						}

						fflush(stdin);
						in = getch();

						switch(in)
						{
						case 72: //su
							if(cont == 0)
								cont = list;
							else
								cont--;
							break;
						case 75: //sinistra
							if(pagina == 0)
								pagina = 7;
							else
								pagina--;
							break;
						case 77: //destra
							if(pagina == 7)
								pagina = 0;
							else
								pagina++;
							break;
						case 80: //giù
							if(cont == list)
								cont = 0;
							else
								cont++;
						}
					} while(in != 'e' && in != 13);
					break;
				}
				case 3: //nome del giocatore
				{
					system("cls");
					printf("Nome: %s.\n", you.nome);
					printf("Money: %d.\n", you.money);
					printf("Medaglie: %d.\n", you.medals);
					printf("Sesso: %s.\n", (you.sex == SEX_MALE) ? "Maschio" : "Femmina");
					printf("Pokemon Catturati: %d.\n", you.catturati);
					getch();
					break;
				}
				case 4: //save
				{
					int i, j;

					system("cls");

					FILE *save = fopen("saves/save.data", "w");

					printf("Salvataggio In Corso, Non Chiudere Il Terminale...\n");

					if(save)
					{
						fprintf(save, "x=%d\n", you.x);
						fprintf(save, "y=%d\n", you.y);
						fprintf(save, "mapId=%d\n", idMappa);
						fprintf(save, "y_nome=%s\n", you.nome);
						fprintf(save, "y_money=%d\n", you.money);
						fprintf(save, "y_catturati=%d\n", you.catturati);
						fprintf(save, "y_dir=%d\n", you.dir);
						fprintf(save, "y_sex=%d\n", you.sex);
						fprintf(save, "y_numPokemon=%d\n", you.numPokemon);
						fprintf(save, "y_medals=%d\n", you.medals);

						for(i = 0; i < you.numPokemon; i++)
						{
							fprintf(save, "y_s%d_id=%d\n", i, you.squadra[i].id);
							fprintf(save, "y_s%d_sex=%d\n", i, you.squadra[i].sex);
							fprintf(save, "y_s%d_tipo1=%d\n", i, you.squadra[i].tipo1);
							fprintf(save, "y_s%d_tipo2=%d\n", i, you.squadra[i].tipo2);
							fprintf(save, "y_s%d_state=%d\n", i, you.squadra[i].state);
							fprintf(save, "y_s%d_ps=%d\n", i, you.squadra[i].ps);
							fprintf(save, "y_s%d_psMax=%d\n", i, you.squadra[i].psMax);
							fprintf(save, "y_s%d_atk=%d\n", i, you.squadra[i].atk);
							fprintf(save, "y_s%d_def=%d\n", i, you.squadra[i].def);
							fprintf(save, "y_s%d_atkSp=%d\n", i, you.squadra[i].atkSp);
							fprintf(save, "y_s%d_defSp=%d\n", i, you.squadra[i].defSp);
							fprintf(save, "y_s%d_speed=%d\n", i, you.squadra[i].speed);
							fprintf(save, "y_s%d_prec=%d\n", i, you.squadra[i].precision);
							fprintf(save, "y_s%d_elu=%d\n", i, you.squadra[i].elusion);
							fprintf(save, "y_s%d_numMosse=%d\n", i, you.squadra[i].numMosse);
							fprintf(save, "y_s%d_exp=%d\n", i, you.squadra[i].exp);
							fprintf(save, "y_s%d_lvl=%d\n", i, you.squadra[i].lvl);
							fprintf(save, "y_s%d_nextExp=%d\n", i, you.squadra[i].nextExp);
							fprintf(save, "y_s%d_lvlToEvolve=%d\n", i, you.squadra[i].lvlToEvolve);
							fprintf(save, "y_s%d_nome=%s\n", i, you.squadra[i].nome);

							for(j = 0; j < you.squadra[i].numMosse; j++)
							{
								fprintf(save, "y_s%d_m%d_id=%d\n", i, j, you.squadra[i].mosse[j].id);
								fprintf(save, "y_s%d_m%d_pp=%d\n", i, j, you.squadra[i].mosse[j].pp);
								fprintf(save, "y_s%d_m%d_ppMax=%d\n", i, j, you.squadra[i].mosse[j].ppMax);
								fprintf(save, "y_s%d_m%d_atk=%d\n", i, j, you.squadra[i].mosse[j].atk);
								fprintf(save, "y_s%d_m%d_precision=%d\n", i, j, you.squadra[i].mosse[j].precision);
								fprintf(save, "y_s%d_m%d_tipo=%d\n", i, j, you.squadra[i].mosse[j].tipo);
								fprintf(save, "y_s%d_m%d_nome=%s\n", i, j, you.squadra[i].mosse[j].nome);
							}
						}

						fprintf(save, "r_nome=%s\n", rivale.nome);
						fprintf(save, "r_occupazione=%s\n", rivale.occupazione);
						fprintf(save, "r_money=%d\n", rivale.money);
						fprintf(save, "r_catturati=%d\n", rivale.catturati);
						fprintf(save, "r_dir=%d\n", rivale.dir);
						fprintf(save, "r_sex=%d\n", rivale.sex);
						fprintf(save, "r_numPokemon=%d\n", rivale.numPokemon);
						fprintf(save, "r_medals=%d\n", rivale.medals);

						for(i = 0; i < rivale.numPokemon; i++)
						{
							fprintf(save, "r_s%d_id=%d\n", i, rivale.squadra[i].id);
							fprintf(save, "r_s%d_sex=%d\n", i, rivale.squadra[i].sex);
							fprintf(save, "r_s%d_tipo1=%d\n", i, rivale.squadra[i].tipo1);
							fprintf(save, "r_s%d_tipo2=%d\n", i, rivale.squadra[i].tipo2);
							fprintf(save, "r_s%d_state=%d\n", i, rivale.squadra[i].state);
							fprintf(save, "r_s%d_ps=%d\n", i, rivale.squadra[i].ps);
							fprintf(save, "r_s%d_psMax=%d\n", i, rivale.squadra[i].psMax);
							fprintf(save, "r_s%d_atk=%d\n", i, rivale.squadra[i].atk);
							fprintf(save, "r_s%d_def=%d\n", i, rivale.squadra[i].def);
							fprintf(save, "r_s%d_atkSp=%d\n", i, rivale.squadra[i].atkSp);
							fprintf(save, "r_s%d_defSp=%d\n", i, rivale.squadra[i].defSp);
							fprintf(save, "r_s%d_speed=%d\n", i, rivale.squadra[i].speed);
							fprintf(save, "r_s%d_prec=%d\n", i, rivale.squadra[i].precision);
							fprintf(save, "r_s%d_elu=%d\n", i, rivale.squadra[i].elusion);
							fprintf(save, "r_s%d_numMosse=%d\n", i, rivale.squadra[i].numMosse);
							fprintf(save, "r_s%d_exp=%d\n", i, rivale.squadra[i].exp);
							fprintf(save, "r_s%d_lvl=%d\n", i, rivale.squadra[i].lvl);
							fprintf(save, "r_s%d_nextExp=%d\n", i, rivale.squadra[i].nextExp);
							fprintf(save, "r_s%d_lvlToEvolve=%d\n", i, rivale.squadra[i].lvlToEvolve);
							fprintf(save, "r_s%d_nome=%s\n", i, rivale.squadra[i].nome);

							for(j = 0; j < rivale.squadra[i].numMosse; j++)
							{
								fprintf(save, "r_s%d_m%d_id=%d\n", i, j, rivale.squadra[i].mosse[j].id);
								fprintf(save, "r_s%d_m%d_pp=%d\n", i, j, rivale.squadra[i].mosse[j].pp);
								fprintf(save, "r_s%d_m%d_ppMax=%d\n", i, j, rivale.squadra[i].mosse[j].ppMax);
								fprintf(save, "r_s%d_m%d_atk=%d\n", i, j, rivale.squadra[i].mosse[j].atk);
								fprintf(save, "r_s%d_m%d_precision=%d\n", i, j, rivale.squadra[i].mosse[j].precision);
								fprintf(save, "r_s%d_m%d_tipo=%d\n", i, j, rivale.squadra[i].mosse[j].tipo);
								fprintf(save, "r_s%d_m%d_nome=%s\n", i, j, rivale.squadra[i].mosse[j].nome);
							}
						}

						for(i = 0; i < ITEMS; i++)
							fprintf(save, "%d\n", i, items[i].amount);

						for(i = 0; i < FLAGS; i++)
							fprintf(save, "%d\n", flags[i]);

						printf("Partita Salvata Con Successo!");
						getch();
					}
					else
					{
						printf("\033[0;31m");
						fprintf(stderr, "Errore Nel Salvare La Partita.\n");
						printf("\033[0m");
						getch();
						exit(1);
					}

					fclose(save);
					break;
				}
				case 6: //esci dal gioco
					exit(0);
					break;
				}
			}
			break;
		}
		case 102: //F
		{
			switch(you.dir)
			{
			case DIRECTION_UP:
				if((*((tile*) mappa + ((you.y - 1) * c) + you.x)).isEvento && (*((tile*) mappa + ((you.y - 1) * c) + you.x)).tipo == EVENT_ACTION)
					(*((tile*) mappa + ((you.y - 1) * c) + you.x)).action();
				break;
			case DIRECTION_RIGHT:
				if((*((tile*) mappa + (you.y * c) + you.x + 1)).isEvento && (*((tile*) mappa + (you.y * c) + you.x + 1)).tipo == EVENT_ACTION)
					(*((tile*) mappa + (you.y * c) + you.x + 1)).action();
				break;
			case DIRECTION_BOTTOM:
				if((*((tile*) mappa + ((you.y + 1) * c) + you.x)).isEvento && (*((tile*) mappa + ((you.y + 1) * c) + you.x)).tipo == EVENT_ACTION)
					(*((tile*) mappa + ((you.y + 1) * c) + you.x)).action();
				break;
			case DIRECTION_LEFT:
				if((*((tile*) mappa + (you.y * c) + you.x - 1)).isEvento && (*((tile*) mappa + (you.y * c) + you.x - 1)).tipo == EVENT_ACTION)
					(*((tile*) mappa + (you.y * c) + you.x - 1)).action();
				break;
			}

			break;
		}
		case 115: //S
            you.dir = DIRECTION_BOTTOM;
            if((*((tile*) mappa + ((you.y + 1) * c) + you.x)).tileChar == SIMBOLO_GRADINO)
			{
				you.y++;
				system("cls");
				stampaMappa((tile*) mappa, FALSE);
				delay(100);
				you.y++;
				delay(100);
			}
			else if(!(*((tile*) mappa + ((you.y + 1) * c) + you.x)).solid)
				you.y++;
			break;
		case 119: //W
			you.dir = DIRECTION_UP;
			if(!(*((tile*) mappa + ((you.y - 1) * c) + you.x)).solid && (*((tile*) mappa + ((you.y - 1) * c) + you.x)).tileChar != SIMBOLO_GRADINO)
				you.y--;
			break;
		}

		if((*((tile*) mappa + (you.y * c) + you.x)).isEvento && (*((tile*) mappa + (you.y * c) + you.x)).tipo == EVENT_WALK && (input == 97 || input == 100 || input == 115 || input == 119))
			(*((tile*) mappa + (you.y * c) + you.x)).action();
	}
}

void loadMossa(mossa *m, int id)
{
	char nomeFile[30];
	int i;
	sprintf(nomeFile, "data/mosse/mossa%d.data", id);
	FILE *fp = fopen(nomeFile, "r");

	if(fp)
	{
		fseek(fp, 5, SEEK_CUR);
		fgets(m->nome, 64, fp);
		m->nome[strlen(m->nome) - 1] = '\0';
		fscanf(fp, "ppMax=%d\n", &m->ppMax);
		m->pp = m->ppMax;
		fscanf(fp, "atk=%d\n", &m->atk);
		fscanf(fp, "precision=%d\n", &m->precision);
		fscanf(fp, "tipo=%d\n", &m->tipo);
	}
	else
	{
		setColor(COLOR_RED);
        fprintf(stderr, "Error Opening %s.\n", nomeFile);
        setColor(COLOR_WHITE);
	}

	fclose(fp);
}

void loadItems()
{
	int i;
	FILE *fp = fopen("data/items/items.data", "r");

	if(fp)
	{
		for(i = 0; i < ITEMS; i++)
		{
			fscanf(fp, "id=%d\n", &items[i].id);
			fseek(fp, 5, SEEK_CUR);
			fgets(items[i].nome, 64, fp);
			items[i].nome[strlen(items[i].nome) - 1] = '\0';
			items[i].amount = 0;
			fscanf(fp, "borsa=%d\n", &items[i].borsa);
		}
	}
	else
	{
		setColor(COLOR_RED);
        fprintf(stderr, "Error Opening Items File\n");
        setColor(COLOR_WHITE);
	}

	fclose(fp);
}

void loadMappa(int id, tile* mappa, int x, int y)
{
	char nomeMappa[64], ch = 0;
	int i, j, event = 0, numInvalid = 0, invalids[MAX_NPCS];
	boolean npcsFlag = FALSE;

	for(i = 0; i < MAX_NPCS; i++)
		npcs[i].valid = FALSE;

	sprintf(nomeMappa, "maps/map%d.pkmp", id);
	FILE *fp = fopen(nomeMappa, "r");

	if(fp)
	{
		fscanf(fp, "r=%d\n", &r);
		fscanf(fp, "c=%d\n", &c);

		you.x = x;
		you.y = y;
		i = 0;

		while(!feof(fp))
		{
			ch = fgetc(fp);

			if(ch == '"')
			{
				npcsFlag = TRUE;
				break;
			}
			else if(ch != '\n' && ch != EOF)
			{
				(*(mappa + i)).tileChar = ch;
				(*(mappa + i)).color = COLOR_WHITE;

				if(ch == SIMBOLO_ALBERO)
				{
					(*(mappa + i)).color = COLOR_GREEN;
					(*(mappa + i)).solid = TRUE;
				}
				else if(ch == SIMBOLO_OSTACOLO || ch == SIMBOLO_MURO_SS || ch == SIMBOLO_MURO_LATO)
					(*(mappa + i)).solid = TRUE;
				else
					(*(mappa + i)).solid = FALSE;

				if(isdigit(ch))
				{
					char buffer[5] = "";

					j = 0;
					while(isdigit(ch))
					{
						buffer[j] = ch;
						ch = fgetc(fp);

						j++;

						if(ch == '@')
							j--;
					}

					fseek(fp, j * -1, SEEK_CUR);
					sscanf(buffer, "%d", &event);

					if(j == 2 || (j == 1 && ch == '@'))
						fseek(fp, 1, SEEK_CUR);

					if(DEBUG_MODE)
					{
						printf("%d\n", event);
						getch();
					}

					(*(mappa + i)).tileChar = SIMBOLO_EVENTO;
					(*(mappa + i)).isEvento = TRUE;

					if(event == 0)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event0;
					}
					else if(event == 1)
					{
						(*(mappa + i)).color = COLOR_YELLOW;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_CARTELLO;
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).action = event1;
					}
					else if(event == 2)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event2;
					}
					else if(event == 3)
					{
						(*(mappa + i)).tileChar = SIMBOLO_NONE;
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event3_0;
					}
					else if(event == 4)
					{
						(*(mappa + i)).tileChar = SIMBOLO_NPC;
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).action = event3_1;
					}
					else if(event == 5)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event4;
					}
					else if(event == 6)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event6;
					}
					else if(event == 7)
					{
						(*(mappa + i)).color = COLOR_YELLOW;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_CARTELLO;
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).action = event7;
					}
					else if(event == 8)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event8;
					}
					else if(event == 9)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event9;
					}
					else if(event == 10)
					{
						(*(mappa + i)).color = COLOR_YELLOW;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_CARTELLO;
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).action = event10;
					}
					else if(event == 11)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event11;
					}
					else if(event == 12)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event12;
					}
					else if(event == 13)
					{
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_NPC;
						(*(mappa + i)).action = event13;
					}
					else if(event == 14)
					{
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_NPC;
						(*(mappa + i)).action = event14;
					}
					else if(event == 15)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event15;
					}
					else if(event == 16)
					{
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_NPC;
						(*(mappa + i)).action = event16;
					}
					else if(event == 17)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event17;
					}
					else if(event == 18)
					{
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_NPC;
						(*(mappa + i)).action = event18;
					}
					else if(event == 19)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event19;
					}
					else if(event == 20)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).tileChar = SIMBOLO_NONE;
						(*(mappa + i)).action = event20;
					}
					else if(event == 21)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event21;
					}
					else if(event == 22)
					{
						(*(mappa + i)).isEvento = FALSE;
						(*(mappa + i)).tileChar = SIMBOLO_NONE;

						if(flags[1])
						{
							invalids[numInvalid] = 0;
							numInvalid++;
						}
					}
					else if(event == 23)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).tileChar = SIMBOLO_NONE;
						(*(mappa + i)).action = event22;
					}
					else if(event == 24)
					{
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).tileChar = SIMBOLO_NPC;
						(*(mappa + i)).action = event23;
					}
					else if(event == 25)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event24;
					}
					else if(event == 26)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event26;
					}
					else if(event == 27)
					{
						(*(mappa + i)).isEvento = FALSE;
						(*(mappa + i)).tileChar = SIMBOLO_NONE;

						if(flags[2])
						{
							invalids[numInvalid] = 0;
							invalids[numInvalid + 1] = 1;
							numInvalid = 2;
						}
					}
					else if(event == 28)
					{
						(*(mappa + i)).tipo = EVENT_ACTION;
						(*(mappa + i)).solid = TRUE;
						(*(mappa + i)).tileChar = SIMBOLO_NPC;
						(*(mappa + i)).action = event29;
					}
					else if(event == 29)
					{
                        (*(mappa + i)).tipo = EVENT_ACTION;
                        (*(mappa + i)).solid = TRUE;
                        (*(mappa + i)).tileChar = SIMBOLO_NPC;
                        (*(mappa + i)).action = event27;
					}
					else if(event == 30)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event28;
					}
					else if(event == 31)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).action = event30;
					}
					else if(event == 32)
					{
						(*(mappa + i)).tipo = EVENT_WALK;
						(*(mappa + i)).tileChar = SIMBOLO_NONE;
						(*(mappa + i)).action = event31;
					}
				}
				else if(ch == SIMBOLO_ACQUA_BASSA)
				{
					(*(mappa + i)).color = COLOR_BOLD_BLUE;
					(*(mappa + i)).solid = TRUE;
					(*(mappa + i)).isEvento = TRUE;
					(*(mappa + i)).tipo = EVENT_ACTION;
					(*(mappa + i)).action = event5;
				}
				else if(ch == SIMBOLO_ERBA_BASSA)
				{
					(*(mappa + i)).color = COLOR_BOLD_GREEN;
					(*(mappa + i)).isEvento = TRUE;
					(*(mappa + i)).tipo = EVENT_WALK;
					(*(mappa + i)).action = event25;
				}
				else
					(*(mappa + i)).isEvento = FALSE;
			}

			i++;
		}

		fgetc(fp);

		if(npcsFlag)
		{
			i = 0;
			int k = 0;
			boolean localFlag;
			while(!feof(fp))
			{
				localFlag = TRUE;
				for(j = k; j < numInvalid; j++)
				{
					if(i == invalids[j])
					{
						char trash[8];

						localFlag = FALSE;
						fgets(trash, 8, fp);
						fgets(trash, 8, fp);
						k++;
						break;
					}
				}

				if(localFlag)
				{
					npcs[i].valid = TRUE;
					fscanf(fp, "e_x=%d\n", &npcs[i].x);
					fscanf(fp, "e_y=%d\n", &npcs[i].y);
				}

				i++;
			}
		}
	}
	else
	{
		printf("\033[0;31m");
		fprintf(stderr, "Error Loading Map %s.\n", nomeMappa);
		printf("\033[0m");
		getch();
		exit(1);
	}

	fclose(fp);
}

void stampaMappa(tile* mappa, boolean debug)
{
	system("cls");

    int x, y, i;
    boolean npcFlag;

    if(DEBUG_MODE)
	{
		printf("x: %d\ny: %d\n", you.x, you.y);

		switch(you.dir)
		{
		case DIRECTION_BOTTOM:
			printf("Dir: v\n");
			break;
		case DIRECTION_LEFT:
			printf("Dir: <\n");
			break;
		case DIRECTION_RIGHT:
			printf("Dir: >\n");
			break;
		case DIRECTION_UP:
			printf("Dir: ^\n");
			break;
		}
	}

    if(r > 14 || c > 28)
	{
		int maxX, maxY;

		if(you.x + 14 < c - 1)
			maxX = you.x + 14;
		else
			maxX = c;

		if(you.y + 7 < r - 1)
			maxY = you.y + 7;
		else
			maxY = r;

		for((you.y - 7 < 0) ? (y = 0) : (y = you.y - 7); y < maxY; y++)
		{
			for((you.x - 14 < 0) ? (x = 0) : (x = you.x - 14); x < maxX; x++)
			{
				npcFlag = FALSE;

				setColor((*(mappa + (y * c) + x)).color);

				if(debug)
					printf("%d", (*(mappa + (y * c) + x)).solid);
				else
				{
					for(i = 0; i < MAX_NPCS; i++)
					{
						if(npcs[i].valid)
						{
							if(x == npcs[i].x && y == npcs[i].y && npcs[i].valid)
							{
								(*(mappa + (y * c) + x)).solid = TRUE;
								npcFlag = TRUE;
								setColor(COLOR_WHITE);
								printf("%c", SIMBOLO_NPC);
							}
						}
					}

					if(!npcFlag)
					{
						if(x == you.x && y == you.y)
						{
							setColor(COLOR_WHITE);
							printf("%c", SIMBOLO_YOU);
						}
						else
							printf("%c", (*(mappa + (y * c) + x)).tileChar);
					}
				}
			}

			printf("\n");
		}
	}
	else
	{
		for(y = 0; y < r; y++)
		{
			for(x = 0; x < c; x++)
			{
				npcFlag = FALSE;

				setColor((*(mappa + (y * c) + x)).color);

				if(debug)
					printf("%d", (*(mappa + (y * c) + x)).solid);
				else
				{
					for(i = 0; i < MAX_NPCS; i++)
					{
						if(npcs[i].valid)
						{
							if(x == npcs[i].x && y == npcs[i].y && npcs[i].valid)
							{
								(*(mappa + (y * c) + x)).solid = TRUE;
								npcFlag = TRUE;
								printf("%c", SIMBOLO_NPC);
							}
						}
					}

					if(!npcFlag)
					{
						if(x == you.x && y == you.y)
						{
							setColor(COLOR_WHITE);
							printf("%c", SIMBOLO_YOU);
						}
						else
							printf("%c", (*(mappa + (y * c) + x)).tileChar);
					}
				}
			}

			printf("\n");
		}
	}

	printf("\033[0m");
}

void setColor(int color)
{
	switch(color)
	{
	case COLOR_GRAY:
		printf("\033[1;30m");
		break;
	case COLOR_WHITE:
		printf("\033[0m");
		break;
	case COLOR_RED:
		printf("\033[0;31m");
		break;
	case COLOR_BOLD_RED:
		printf("\033[1;31m");
		break;
	case COLOR_GREEN:
		printf("\033[0;32m");
		break;
	case COLOR_BOLD_GREEN:
		printf("\033[1;32m");
		break;
	case COLOR_YELLOW:
		printf("\033[0;33m");
		break;
	case COLOR_BOLD_YELLOW:
		printf("\033[1;33m");
		break;
	case COLOR_BLUE:
		printf("\033[0;34m");
		break;
	case COLOR_BOLD_BLUE:
		printf("\033[1;34m");
		break;
	case COLOR_MAGENTA:
		printf("\033[0;35m");
		break;
	case COLOR_BOLD_MAGENTA:
		printf("\033[1;35m");
		break;
	case COLOR_CYAN:
		printf("\033[0;36m");
		break;
	case COLOR_BOLD_CYAN:
		printf("\033[1;36m");
		break;
	}
}

void showConsoleCursor(boolean flag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void delay(int millis)
{
    int milli_seconds = 1000 * millis;
    clock_t start_time = clock();
    while (clock() < start_time + millis);
}

//eventi
//evento 0
void event0() { delay(1000); idMappa = 1; loadMappa(idMappa, (tile*) mappa, 7, 1); }
//evento 1
void event1()
{
	stampaMappa((tile*) mappa, FALSE);
	printf("Usa I Tasti WASD Per Muoverti.");
	getch();
	stampaMappa((tile*) mappa, FALSE);
	printf("Usa Il Tasto E Per Aprire Il Menu.");
	getch();
	stampaMappa((tile*) mappa, FALSE);
	printf("Usa Il Tasto F Per Interagire.");
	getch();
}

//evento 2
void event2() { delay(1000); idMappa = 0; loadMappa(idMappa, (tile*) mappa, 8, 1); }
//evento 3
void event3_0()
{
	if(!flags[0])
	{
		(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).isEvento = FALSE;
		(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).tileChar = SIMBOLO_NONE;

		while(npcs[0].x - you.x != 0)
		{
			stampaMappa((tile*) mappa, FALSE);

			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			if(npcs[0].x - you.x > 0)
				npcs[0].x--;
			else if(npcs[0].x - you.x < 1)
				npcs[0].x++;

			delay(500);
		}
		while(npcs[0].y - you.y != 1)
		{
			stampaMappa((tile*) mappa, FALSE);

			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			if(npcs[0].y - you.y > 1)
				npcs[0].y--;
			else if(npcs[0].y - you.y < 1)
				npcs[0].y++;

			delay(500);
		}

		event3_1();

		(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).isEvento = TRUE;
		(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).action = event3_1;
		(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).tipo = EVENT_ACTION;
		flags[0] = TRUE;
	}
}

void event3_1()
{
	stampaMappa((tile*) mappa, FALSE);
	printf("Mamma: %s!\n", you.nome);
	getch();
	stampaMappa((tile*) mappa, FALSE);
	printf("Mamma: %s ti stava cercando poco fa.\n", rivale.nome);
	getch();
	stampaMappa((tile*) mappa, FALSE);
	printf("Mamma: Credo sia andato a casa sua.\n");
	getch();
	stampaMappa((tile*) mappa, FALSE);
	printf("Mamma: E mi raccomando, attento all'erba alta.\n");
	getch();
}

//evento 4
void event4() { delay(1000); idMappa = 2; loadMappa(idMappa, (tile*) mappa, 38, 18); }
//evento 5
void event5() { printf("L'acqua ha un colore azzurro marino...\n"); getch(); }
//evento 6
void event6() { delay(1000); idMappa = 1; loadMappa(idMappa, (tile*) mappa, 6, 4); }
//evento 7
void event7() { printf("Casa di %s\n", you.nome); getch(); }
//evento 8
void event8() { delay(1000); idMappa = 3; loadMappa(idMappa, (tile*) mappa, 6, 4); }
//evento 9
void event9() { delay(1000); idMappa = 4; loadMappa(idMappa, (tile*) mappa, 6, 4); }
//evento 10
void event10() { printf("Casa di %s\n", rivale.nome); getch(); }
//evento 11
void event11() { delay(1000); idMappa = 5; loadMappa(idMappa, (tile*) mappa, 6, 4); }
//evento 12
void event12() { delay(1000); idMappa = 2; loadMappa(idMappa, (tile*) mappa, 9, 18); }
//evento 13
void event13()
{
	printf("Ho sentito che il prof Rowan e' tornato dal suo viaggio da Khanto.\n");
	getch();
	stampaMappa((tile*) mappa, FALSE);
	printf("Mi chiedo cosa ci sia andato a fare...\n");
	getch();
}

//evento 14
void event14() { printf("Quanto vorrei avere un Pokemon...\n"); getch(); }
//evento 15
void event15() { delay(1000); idMappa = 2; loadMappa(idMappa, (tile*) mappa, 38, 11); }
//evento 16
void event16()
{
	printf("Hai sentito la leggenda del lago?\n");
	getch();
	stampaMappa((tile*) mappa, FALSE);
	printf("Dicono che sul lago abiti un Pokemon leggendario...");
	getch();
}

//evento 17
void event17() { delay(1000); idMappa = 2; loadMappa(idMappa, (tile*) mappa, 9, 11); }
//evento 18
void event18()
{
    if(!flags[1])
	{
		printf("%s e' al piano di sopra.\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("Quel ragazzo non sta mai fermo...\n");
		getch();
	}
	else
	{
		printf("%s e' scappato fuori!\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("Quel ragazzo non sta mai fermo...\n");
		getch();
	}
}

//evento 19
void event19() { delay(1000); idMappa = 6; loadMappa(idMappa, (tile*) mappa, 2, 1); }

//evento 20
void event20()
{
    if(!flags[1])
    {
    	int i;

    	stampaMappa((tile*) mappa, FALSE);
    	printf("%s!", you.nome);
    	getch();
    	stampaMappa((tile*) mappa, FALSE);
    	printf("Ti aspetto al percorso 1!\n");
    	getch();
    	stampaMappa((tile*) mappa, FALSE);
    	printf("Se fai tardi ti faccio una multa di 140 mila$!\n");
    	getch();

    	for(i = 0; i < 4; i++)
        {
        	(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).tileChar = SIMBOLO_NONE;
        	(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
        	npcs[0].x--;
			stampaMappa((tile*) mappa, FALSE);
			delay(200);
        }

        if(you.x == 3 && you.y == 1)
		{
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).tileChar = SIMBOLO_NONE;
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
        	npcs[0].x--;
			stampaMappa((tile*) mappa, FALSE);
			delay(200);

			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).tileChar = SIMBOLO_NONE;
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
        	npcs[0].y--;
			stampaMappa((tile*) mappa, FALSE);
			delay(200);

			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			npcs[0].valid = FALSE;
		}
		else
		{
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).tileChar = SIMBOLO_NONE;
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
        	npcs[0].y--;
			stampaMappa((tile*) mappa, FALSE);
			delay(200);

			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).tileChar = SIMBOLO_NONE;
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
        	npcs[0].x--;
			stampaMappa((tile*) mappa, FALSE);
			delay(200);

			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			npcs[0].valid = FALSE;
		}

    	flags[1] = TRUE;
    }
}

//evento 21
void event21() { delay(1000); idMappa = 4; loadMappa(idMappa, (tile*) mappa, 3, 1); }
//evento 22
void event22()
{
	if(!flags[1])
	{
		stampaMappa((tile*) mappa, FALSE);
		printf("Hey, %s!\n", you.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s ti stava cercando!\n", rivale.nome);
		getch();
		you.y++;
	}
}

//evento 23
void event23()
{
	if(!flags[1])
	{
		stampaMappa((tile*) mappa, FALSE);
		printf("Hey, %s!\n", you.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s ti stava cercando!\n", rivale.nome);
		getch();
	}
	else
	{
		stampaMappa((tile*) mappa, FALSE);
		printf("%s si trova sul percorso 1.\n", rivale.nome);
		getch();
	}
}

//evento 24
void event24() { delay(1000); idMappa = 7; loadMappa(idMappa, (tile*) mappa, 21, 8); }

//evento 25
void event25() {}
//evento 26
void event26() { delay(1000); idMappa = 2; loadMappa(idMappa, (tile*) mappa, 22, 1); }
//evento 27
void event27()
{
    if(!flags[3])
	{
		printf("Quando i tuoi Pokemon perdono della salute, puoi curarli con le pozioni.\n");
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("Tieni, prendine una!\n");
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s ottiene \033[1;34mPozione\033[0m!\n", you.nome);
		items[ITEM_POZIONE].amount++;
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s mette \033[1;34mPozione\033[0m nella tasca \033[1;34mRimedi\033[0m della borsa.\n", you.nome);
		getch();
		flags[3] = TRUE;
	}
	else
	{
		printf("Quando i tuoi Pokemon perdono della salute, puoi curarli con le pozioni.\n");
		getch();
	}
}

//evento 28
void event28() { delay(1000); idMappa = 8; loadMappa(idMappa, (tile*) mappa, 1, 1); }
//evento 29
void event29()
{
    printf("Da questo gradino si puo' scendere ma non salire...\n");
    getch();
}

//evento 30
void event30() { delay(1000); idMappa = 9; loadMappa(idMappa, (tile*) mappa, 1, 1); }
//evento 31
void event31()
{
	int i, cont;
	char ch;
	boolean answerYes = FALSE;

	if(!flags[2])
	{
		stampaMappa((tile*) mappa, FALSE);

		if(you.y != 8)
		{
			delay(200);
			you.y = 8;
		}

		stampaMappa((tile*) mappa, FALSE);

		while(you.x < npcs[0].x)
		{
			delay(200);
			you.x++;
			stampaMappa((tile*) mappa, FALSE);
		}

		(*((tile*) mappa + (npcs[1].y * c) + npcs[1].x)).solid = FALSE;
		npcs[1].x = you.x - 15;

		for(i = 0; i < 3; i++)
		{
			delay(200);
			you.x++;
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			(*((tile*) mappa + (npcs[1].y * c) + npcs[1].x)).solid = FALSE;
			npcs[0].x++;
			npcs[1].x++;
			stampaMappa((tile*) mappa, FALSE);
		}

		printf("%s: %s!\n", rivale.nome, you.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Per andare al laboratorio del prof Rowan dobbiamo passare questo percorso.\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Come dici? Hai paura dell'erba alta?\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Ma si', basta evitarla.\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Sei pronto?\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: 3... ", rivale.nome);
		getch();
		printf("2... ");
		getch();
		printf("1...\n");
		getch();

		for(i = 0; i < 4; i++)
		{
			delay(200);
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			npcs[0].x++;
			stampaMappa((tile*) mappa, FALSE);
		}

		printf("???: FERMI!\n");
		getch();

		for(i = 0; i < 14; i++)
		{
			delay(250);
			(*((tile*) mappa + (npcs[1].y * c) + npcs[1].x)).solid = FALSE;
			npcs[1].x++;
			stampaMappa((tile*) mappa, FALSE);
		}

		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Ma tu...\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Sei il Prof. Rowan!\n", rivale.nome);
		getch();

		for(i = 0; i < 4; i++)
		{
			delay(200);
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			npcs[0].x--;
			stampaMappa((tile*) mappa, FALSE);
		}

		printf("Prof. Rowan: Questi ragazzi stavano per entrare nell'erba alta nonostante non abbiano con loro nessun pokemon...");
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("Prof. Rowan: Cosa fare? La loro vita di sicuro cambiera' se dovessero incontrare dei pokemon...\n");
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("Prof. Rowan: Ragazzi, vi porgo una domanda.\n");
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("Voi amate davvero i pokemon?\n");
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Cosa? Ce lo puo' chiedere anche 100 volte e la nostra risposta sara' sempre di si'!\n", rivale.nome);
		getch();

		while(!answerYes)
		{
			cont = 0;

			do
			{
				stampaMappa((tile*) mappa, FALSE);
				printf("%s: Vero %s?\n", rivale.nome, you.nome);

				if(cont == 0)
					printf("> SI' <\n");
				else
					printf("  SI'\n");

				if(cont == 1)
					printf("> NO <\n");
				else
					printf("  NO\n");

				fflush(stdin);
				ch = getch();

				switch(ch)
				{
				case 72:
					if(cont == 0)
						cont = 1;
					else
						cont--;
					break;
				case 80:
					if(cont == 1)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(ch != 13);

			if(cont == 1)
			{
				stampaMappa((tile*) mappa, FALSE);
				printf("%s: Stai scherzando?\n", rivale.nome);
				getch();
				stampaMappa((tile*) mappa, FALSE);
				printf("%s: Cosa? Ce lo puo' chiedere anche 100 volte e la nostra risposta sara' sempre di si'!\n", rivale.nome);
				getch();
			}
			else if(cont == 0)
				answerYes = TRUE;
		}

		stampaMappa((tile*) mappa, FALSE);
		printf("Prof. Rowan: Va bene, allora vi credo, quindi vi daro' la possibilita' di scegliere tra 3 Pokemon molto rari dalla mia valigetta.\n");
		getch();
		delay(500);
		(*((tile*) mappa + ((npcs[1].y + 1) * c) + npcs[1].x)).tileChar = SIMBOLO_OSTACOLO;
		(*((tile*) mappa + ((npcs[1].y + 1) * c) + npcs[1].x)).color = COLOR_BOLD_YELLOW;
		stampaMappa((tile*) mappa, FALSE);
		delay(500);
		printf("%s: Ok, %s, faro' scegliere prima a te.\n", rivale.nome, you.nome);
		getch();

		answerYes = FALSE;
		while(!answerYes)
		{
			int secCont = 0;
			cont = 0;

			do
			{
				stampaMappa((tile*) mappa, FALSE);
				printf("Chi scegli?\n");

				if(cont == 0)
					printf("> Tartwig <\n");
				else
					printf("  Tartwig\n");

				if(cont == 1)
					printf("> Chimchar <\n");
				else
					printf("  Chimchar\n");

				if(cont == 2)
					printf("> Piplup <\n");
				else
					printf("  Piplup\n");

				fflush(stdin);
				ch = getch();

				switch(ch)
				{
				case 72:
					if(cont == 0)
						cont = 2;
					else
						cont--;
					break;
				case 80:
					if(cont == 2)
						cont = 0;
					else
						cont++;
					break;
				}
			} while(ch != 13);

            do
			{
				stampaMappa((tile*) mappa, FALSE);
				printf("Sei sicuro?\n");

				if(secCont == 0)
					printf("> SI' <\n");
				else
					printf("  SI'\n");

				if(secCont == 1)
					printf("> NO <\n");
				else
					printf("  NO\n");

				fflush(stdin);
				ch = getch();

				switch(ch)
				{
				case 72:
					if(secCont == 0)
						secCont = 1;
					else
						secCont--;
					break;
				case 80:
					if(secCont == 1)
						secCont = 0;
					else
						secCont++;
					break;
				}
			} while(ch != 13);

			if(secCont == 0)
				answerYes = TRUE;
		}

		you.squadra[0].sex = you.sex;
		you.squadra[0].tipo2 = TIPO_NONE;

		stampaMappa((tile*) mappa, FALSE);
		printf("%s ottiene ", you.nome);

		if(cont == 0)
		{
			you.squadra[0].id = PKM_TARTWIG;
			you.squadra[0].tipo1 = TIPO_ERBA;
			you.squadra[0].state = STATE_NORMAL;
			you.squadra[0].ps = 19;
			you.squadra[0].psMax = 19;
			you.squadra[0].atk = 9;
			you.squadra[0].def = 12;
			you.squadra[0].atkSp = 7;
			you.squadra[0].defSp = 10;
			you.squadra[0].speed = 13;
			you.squadra[0].precision = 100;
			you.squadra[0].elusion = 0;
			you.squadra[0].numMosse = 1;
			you.squadra[0].exp = 0;
			you.squadra[0].lvl = 5;
			you.squadra[0].nextExp = 30;
			you.squadra[0].lvlToEvolve = 18;
			strcpy(you.squadra[0].nome, "Tartwig");
			you.squadra[0].catturabile = FALSE;
			you.squadra[0].item = FALSE;
			loadMossa(&you.squadra[0].mosse[0], MOSSA_AZIONE);
			rivale.squadra[0].id = PKM_CHIMCHAR;
			rivale.squadra[0].tipo1 = TIPO_FUOCO;
			rivale.squadra[0].state = STATE_NORMAL;
			rivale.squadra[0].ps = 21;
			rivale.squadra[0].psMax = 21;
			rivale.squadra[0].atk = 11;
			rivale.squadra[0].def = 9;
			rivale.squadra[0].atkSp = 9;
			rivale.squadra[0].defSp = 7;
			rivale.squadra[0].speed = 10;
			rivale.squadra[0].precision = 100;
			rivale.squadra[0].elusion = 0;
			rivale.squadra[0].numMosse = 1;
			rivale.squadra[0].exp = 0;
			rivale.squadra[0].lvl = 5;
			rivale.squadra[0].nextExp = 35;
			rivale.squadra[0].lvlToEvolve = 14;
			strcpy(rivale.squadra[0].nome, "Chimchar");
			rivale.squadra[0].catturabile = FALSE;
			rivale.squadra[0].item = FALSE;
			loadMossa(&rivale.squadra[0].mosse[0], MOSSA_GRAFFIO);

			setColor(COLOR_GREEN);
		}
		else if(cont == 1)
		{
			you.squadra[0].id = PKM_CHIMCHAR;
			you.squadra[0].tipo1 = TIPO_FUOCO;
			you.squadra[0].state = STATE_NORMAL;
			you.squadra[0].ps = 21;
			you.squadra[0].psMax = 21;
			you.squadra[0].atk = 11;
			you.squadra[0].def = 9;
			you.squadra[0].atkSp = 9;
			you.squadra[0].defSp = 7;
			you.squadra[0].speed = 10;
			you.squadra[0].precision = 100;
			you.squadra[0].elusion = 0;
			you.squadra[0].numMosse = 1;
			you.squadra[0].exp = 0;
			you.squadra[0].lvl = 5;
			you.squadra[0].nextExp = 35;
			you.squadra[0].lvlToEvolve = 14;
			strcpy(you.squadra[0].nome, "Chimchar");
			you.squadra[0].catturabile = FALSE;
			you.squadra[0].item = FALSE;
			loadMossa(&you.squadra[0].mosse[0], MOSSA_GRAFFIO);
			rivale.squadra[0].id = PKM_PIPLUP;
			rivale.squadra[0].tipo1 = TIPO_ACQUA;
			rivale.squadra[0].state = STATE_NORMAL;
			rivale.squadra[0].ps = 19;
			rivale.squadra[0].psMax = 19;
			rivale.squadra[0].atk = 12;
			rivale.squadra[0].def = 11;
			rivale.squadra[0].atkSp = 9;
			rivale.squadra[0].defSp = 8;
			rivale.squadra[0].speed = 11;
			rivale.squadra[0].precision = 100;
			rivale.squadra[0].elusion = 0;
			rivale.squadra[0].numMosse = 1;
			rivale.squadra[0].exp = 0;
			rivale.squadra[0].lvl = 5;
			rivale.squadra[0].nextExp = 34;
			rivale.squadra[0].lvlToEvolve = 16;
			strcpy(rivale.squadra[0].nome, "Piplup");
			rivale.squadra[0].catturabile = FALSE;
			rivale.squadra[0].item = FALSE;
			loadMossa(&rivale.squadra[0].mosse[0], MOSSA_BOTTA);

			setColor(COLOR_RED);
		}
		else if(cont == 2)
		{
			you.squadra[0].id = PKM_PIPLUP;
			you.squadra[0].tipo1 = TIPO_ACQUA;
			you.squadra[0].state = STATE_NORMAL;
			you.squadra[0].ps = 19;
			you.squadra[0].psMax = 19;
			you.squadra[0].atk = 12;
			you.squadra[0].def = 11;
			you.squadra[0].atkSp = 9;
			you.squadra[0].defSp = 8;
			you.squadra[0].speed = 11;
			you.squadra[0].precision = 100;
			you.squadra[0].elusion = 0;
			you.squadra[0].numMosse = 1;
			you.squadra[0].exp = 0;
			you.squadra[0].lvl = 5;
			you.squadra[0].nextExp = 34;
			you.squadra[0].lvlToEvolve = 16;
			strcpy(you.squadra[0].nome, "Piplup");
			you.squadra[0].catturabile = FALSE;
			you.squadra[0].item = FALSE;
			loadMossa(&you.squadra[0].mosse[0], MOSSA_BOTTA);
			rivale.squadra[0].id = PKM_TARTWIG;
			rivale.squadra[0].tipo1 = TIPO_ERBA;
			rivale.squadra[0].state = STATE_NORMAL;
			rivale.squadra[0].ps = 19;
			rivale.squadra[0].psMax = 19;
			rivale.squadra[0].atk = 9;
			rivale.squadra[0].def = 12;
			rivale.squadra[0].atkSp = 7;
			rivale.squadra[0].defSp = 10;
			rivale.squadra[0].speed = 13;
			rivale.squadra[0].precision = 100;
			rivale.squadra[0].elusion = 0;
			rivale.squadra[0].numMosse = 1;
			rivale.squadra[0].exp = 0;
			rivale.squadra[0].lvl = 5;
			rivale.squadra[0].nextExp = 30;
			rivale.squadra[0].lvlToEvolve = 18;
			strcpy(rivale.squadra[0].nome, "Tartwig");
			rivale.squadra[0].catturabile = FALSE;
			rivale.squadra[0].item = FALSE;
			loadMossa(&rivale.squadra[0].mosse[0], MOSSA_AZIONE);

			setColor(COLOR_BLUE);
		}

		printf("%s", you.squadra[0].nome);
		setColor(COLOR_WHITE);
		printf("!\n");
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Ok, allora io scelgo %s.\n", rivale.nome, rivale.squadra[0].nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("Prof. Rowan: Ok, adesso che siete al sicuro me ne posso andare.\n");
		getch();
		delay(500);
		(*((tile*) mappa + ((npcs[1].y + 1) * c) + npcs[1].x)).tileChar = SIMBOLO_NONE;
		(*((tile*) mappa + ((npcs[1].y + 1) * c) + npcs[1].x)).color = COLOR_WHITE;
		delay(500);
		stampaMappa((tile*) mappa, FALSE);
		printf("Prof. Rowan: Buona fortuna!\n");
		getch();

		for(i = 0; i < 3; i++)
		{
			delay(250);
			(*((tile*) mappa + (npcs[1].y * c) + npcs[1].x)).solid = FALSE;
			npcs[1].x--;
			stampaMappa((tile*) mappa, FALSE);
		}

		delay(250);
		(*((tile*) mappa + (npcs[1].y * c) + npcs[1].x)).solid = FALSE;
		npcs[1].y++;
		stampaMappa((tile*) mappa, FALSE);
		delay(250);
		(*((tile*) mappa + (npcs[1].y * c) + npcs[1].x)).solid = FALSE;
		npcs[1].valid = FALSE;
		stampaMappa((tile*) mappa, FALSE);
		delay(500);
		printf("%s: %s!\n", rivale.nome, you.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Finalmente lo posso dire!\n", rivale.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Ti sfido a una battaglia Pokemon!\n", rivale.nome);
		getch();

		you.catturati++;
		you.numPokemon++;
		rivale.numPokemon++;

		if(lotta(&rivale, 500, 150))
		{
			stampaMappa((tile*) mappa, FALSE);
			printf("%s: Caspita!\n", rivale.nome);
			getch();
			stampaMappa((tile*) mappa, FALSE);
			printf("%s: Mi hai battuto!\n", rivale.nome);
			getch();
		}
		else
		{
			stampaMappa((tile*) mappa, FALSE);
			printf("%s: Ahahaah!\n", rivale.nome);
			getch();
			stampaMappa((tile*) mappa, FALSE);
			printf("%s: Ti ho battuto!\n", rivale.nome);
			getch();
		}

		delay(1000);
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: %s, e' ora che io parta all'avventura!\n", rivale.nome, you.nome);
		getch();
		stampaMappa((tile*) mappa, FALSE);
		printf("%s: Ci vediamo!\n", rivale.nome);
		getch();

		for(i = 0; i < 14; i++)
		{
			delay(200);
			(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
			npcs[0].x++;
			stampaMappa((tile*) mappa, FALSE);
		}

		(*((tile*) mappa + (npcs[0].y * c) + npcs[0].x)).solid = FALSE;
		npcs[0].valid = FALSE;
		flags[2] = TRUE;
	}
}

//funzioni di battaglia
void stampaPokemon(allenatore *avversario, int r_i, int y_i)
{
	int i;

	system("cls");
	printf("   %c\t %s |", SIMBOLO_POKEMON_NPC, avversario->squadra[r_i].nome);

	for(i = 0; i < 10; i++)
	{
		if(i < (((float) avversario->squadra[r_i].ps) / avversario->squadra[r_i].psMax) * 10)
			printf("X");
		else
			printf(" ");
	}

	printf("| Lvl. %d\n", avversario->squadra[r_i].lvl);
	printf(" %c  \t %s |", SIMBOLO_POKEMON_NPC, you.squadra[y_i].nome);

	for(i = 0; i < 10; i++)
	{
		if(i < (((float) you.squadra[y_i].ps) / you.squadra[y_i].psMax) * 10)
			printf("X");
		else
			printf(" ");
	}

	printf("| Lvl. %d  Ps: %d/%d\n", you.squadra[y_i].lvl, you.squadra[y_i].ps, you.squadra[y_i].psMax);
	printf("    \t ");

	for(i = 0; i < strlen(you.squadra[y_i].nome) - 3; i++)
		printf(" ");

	printf("Exp:|");

	for(i = 0; i < 10; i++)
	{
		if(i < (((float) you.squadra[y_i].exp) / you.squadra[y_i].nextExp) * 10)
			printf("X");
		else
			printf(" ");
	}

	printf("|\n\n");
}

void lvlUp(pokemon *pkm, int y_i)
{
	int max = 0, amPs, amA, amD, amAs, amDs, amS;

	switch(you.squadra[y_i].id)
	{
	case PKM_TARTWIG:
	case PKM_CHIMCHAR:
	case PKM_PIPLUP:
		max = 2;
		break;
	}

	amPs = (rand() % max) + 1;
	amA = (rand() % max) + 1;
	amD = (rand() % max) + 1;
	amAs = (rand() % max) + 1;
	amDs = (rand() % max) + 1;
	amS = (rand() % max) + 1;

	pkm->atk += amA;
	pkm->def += amD;
	pkm->lvl++;
	system("cls");
	printf("%s sale al livello %d!", you.squadra[y_i].nome, you.squadra[y_i].lvl);
	getch();
	system("cls");
	printf("Ps:       %d + %d\n", pkm->psMax, amPs);
	printf("Atk.:     %d + %d\n", pkm->atk, amA);
	printf("Def.:     %d + %d\n", pkm->def, amD);
	printf("Atk. Sp.: %d + %d\n", pkm->atkSp, amAs);
	printf("Def. Sp.: %d + %d\n", pkm->defSp, amDs);
	printf("Speed:    %d + %d\n", pkm->speed, amS);
	pkm->ps += amPs;
	pkm->psMax += amPs;
	pkm->atk += amA;
	pkm->def += amD;
	pkm->atkSp += amAs;
	pkm->defSp += amDs;
	pkm->speed += amS;
	getch();
	system("cls");
	printf("Ps:       %d\n", pkm->psMax);
	printf("Atk.:     %d\n", pkm->atk);
	printf("Def.:     %d\n", pkm->def);
	printf("Atk. Sp.: %d\n", pkm->atkSp);
	printf("Def. Sp.: %d\n", pkm->defSp);
	printf("Speed:    %d\n", pkm->speed);
	getch();
}

boolean lotta(allenatore *avversario, int cashWon, int cashLost)
{
	int i, y_i = 0, r_i = 0, y_n = you.numPokemon, r_n = avversario->numPokemon, cont = 0;
	char input;
	boolean finish = FALSE, won = FALSE;

	system("cls");
	printf("%c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf(" %c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf("  %c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf("   %c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf("    %c\n", SIMBOLO_NPC);
	printf("Parte la sfida d %s, %s!\n", avversario->nome, avversario->occupazione);
	getch();
	system("cls");
	printf("   %c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf("  %c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf(" %c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf("%c\n", SIMBOLO_NPC);
	delay(200);
	system("cls");
	printf("%s manda in campo %s.\n", avversario->nome, avversario->squadra[r_i].nome);
	getch();
	system("cls");
	printf("%c\n", SIMBOLO_POKEMON_NPC);
	delay(200);
	system("cls");
	printf(" %c\n", SIMBOLO_POKEMON_NPC);
	delay(200);
	system("cls");
	printf("  %c\n", SIMBOLO_POKEMON_NPC);
	delay(200);
	system("cls");
	printf("   %c\n", SIMBOLO_POKEMON_NPC);
	stampaPokemon(avversario, r_i, y_i);
	printf("Vai, %s!\n", you.squadra[y_i].nome);
	getch();

	while(!finish)
	{
		cont = 0;

		do
		{
			stampaPokemon(avversario, r_i, y_i);
			printf("Cosa deve fare %s?\n", you.squadra[y_i].nome);

			for(i = 0; i < you.squadra[y_i].numMosse; i++)
			{
				if(cont == i)
					printf("> %s PP:[%d/%d] <\n", you.squadra[y_i].mosse[i].nome, you.squadra[y_i].mosse[i].pp, you.squadra[y_i].mosse[i].ppMax);
				else
					printf("  %s PP:[%d/%d]\n", you.squadra[y_i].mosse[i].nome, you.squadra[y_i].mosse[i].pp, you.squadra[y_i].mosse[i].ppMax);
			}

			fflush(stdin);
			input = getch();

			switch(input)
			{
			case 72:
				if(cont == 0)
					cont = you.squadra[y_i].numMosse - 1;
				else
					cont--;
				break;
			case 80:
				if(cont == you.squadra[y_i].numMosse - 1)
					cont = 0;
				else
					cont++;
				break;
			}
		} while(input != 13);

		if(you.squadra[y_i].speed >= avversario->squadra[r_i].speed)
		{
			stampaPokemon(avversario, r_i, y_i);
			printf("%s usa %s!\n", you.squadra[y_i].nome, you.squadra[y_i].mosse[cont].nome);
			getch();
			funzioneMossa(&you.squadra[y_i], &avversario->squadra[r_i], cont);

			if(avversario->squadra[r_i].ps <= 0)
			{
				stampaPokemon(avversario, r_i, y_i);
				printf("%s e' esausto!\n", avversario->squadra[r_i].nome);
				r_n--;
				getch();
				int exp = (int) ((avversario->squadra[r_i].lvl * avversario->squadra[r_i].atk * avversario->squadra[r_i].def * avversario->squadra[r_i].atkSp * avversario->squadra[r_i].defSp) / 1000);
				printf("%s ha guadagnato %d punti esperienza!\n", you.squadra[y_i].nome, exp);
				getch();

                while(exp >= you.squadra[y_i].nextExp)
				{
					exp -= you.squadra[y_i].nextExp;
					lvlUp(&you.squadra[y_i], y_i);
				}

				you.squadra[y_i].exp += exp;
				stampaPokemon(avversario, r_i, y_i);
				getch();
			}

			if(r_n == 0)
			{
				system("cls");
				printf("%s ha la meglio su %s, %s!\n", you.nome, avversario->nome, avversario->occupazione);
				getch();
				printf("%s ottiene %d$!", you.nome, cashWon);
				getch();
				you.money += cashWon;

				won = TRUE;
				break;
			}

			stampaPokemon(avversario, r_i, y_i);
			cont = rand() % avversario->squadra[r_i].numMosse;
			printf("%s usa %s!\n", avversario->squadra[r_i].nome, avversario->squadra[r_i].mosse[cont].nome);
			getch();
			funzioneMossa(&avversario->squadra[r_i], &you.squadra[y_i], cont);

			if(you.squadra[y_i].ps <= 0)
			{
				stampaPokemon(avversario, r_i, y_i);
				printf("%s e' esausto!\n", you.squadra[r_i].nome);
				y_n--;
				getch();
			}

			if(y_n == 0)
			{
				system("cls");
				printf("%s %s ha avuto la meglio su %s!\n", avversario->nome, avversario->occupazione, you.nome);
				getch();
				printf("%s paga %d$!", you.nome, cashLost);
				getch();

				if(you.money - cashLost > 0)
					you.money -= cashLost;
				else
					you.money = 0;

				won = FALSE;
				break;
			}
		}
		else
		{
			stampaPokemon(avversario, r_i, y_i);
			cont = rand() % avversario->squadra[r_i].numMosse;
			printf("%s usa %s!\n", avversario->squadra[r_i].nome, avversario->squadra[r_i].mosse[cont].nome);
			getch();
			funzioneMossa(&avversario->squadra[r_i], &you.squadra[y_i], cont);

			if(you.squadra[y_i].ps <= 0)
			{
				stampaPokemon(avversario, r_i, y_i);
				printf("%s e' esausto!\n", you.squadra[r_i].nome);
				y_n--;
				getch();
			}

			if(y_n == 0)
			{
				system("cls");
				printf("%s %s ha avuto la meglio su %s!\n", avversario->nome, avversario->occupazione, you.nome);
				getch();
				printf("%s paga %d$!", you.nome, cashLost);
				getch();

				if(you.money - cashLost > 0)
					you.money -= cashLost;
				else
					you.money = 0;

				won = FALSE;
				break;
			}

			stampaPokemon(avversario, r_i, y_i);
			printf("%s usa %s!\n", you.squadra[y_i].nome, you.squadra[y_i].mosse[cont].nome);
			getch();
			funzioneMossa(&you.squadra[y_i], &avversario->squadra[r_i], cont);

			if(avversario->squadra[r_i].ps <= 0)
			{
				stampaPokemon(avversario, r_i, y_i);
				printf("%s e' esausto!\n", avversario->squadra[r_i].nome);
				r_n--;
				getch();
				int exp = (int) ((avversario->squadra[r_i].lvl * avversario->squadra[r_i].atk * avversario->squadra[r_i].def * avversario->squadra[r_i].atkSp * avversario->squadra[r_i].defSp) / 1000);
				printf("%s ha guadagnato %d punti esperienza!\n", you.squadra[y_i].nome, exp);
				getch();

                while(exp >= you.squadra[y_i].nextExp)
				{
					exp -= you.squadra[y_i].nextExp;
					lvlUp(&you.squadra[y_i], y_i);
				}

				you.squadra[y_i].exp += exp;
				stampaPokemon(avversario, r_i, y_i);
				getch();
			}

			if(r_n == 0)
			{
				system("cls");
				printf("%s ha la meglio su %s, %s!\n", you.nome, avversario->nome, avversario->occupazione);
				getch();
				printf("%s ottiene %d$!", you.nome, cashWon);
				getch();
				you.money += cashWon;

				won = TRUE;
				break;
			}
		}
	}

	return won;
}

void funzioneMossa(pokemon *atk, pokemon *victim, int mossaIndex)
{
	if(atk->mosse[mossaIndex].id == MOSSA_AZIONE || atk->mosse[mossaIndex].id == MOSSA_BOTTA || atk->mosse[mossaIndex].id == MOSSA_GRAFFIO)
		victim->ps -= ((atk->atk + atk->atkSp) * atk->mosse[mossaIndex].atk / 10) / (victim->def + victim->defSp);

	if(victim->ps < 0)
		victim->ps = 0;

	atk->mosse[mossaIndex].pp--;
}
