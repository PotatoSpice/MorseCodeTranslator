/**
 * @file main.c
 * @author Grupo 24:
 *          | José Baltar 8170212 
 *          | Rodrigo Coelho 8170282 
 *          | Rui Silva 8170283 |
 * @date Created on 6 de Dezembro de 2017, 11:54
 * 
 * @brief (resumo)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "LP_Leitura.h"
#include "LP_Utils.h"

/**
 * @brief simboliza o traço presente na codificação MORSE (3 units)
 */
#define DASH '-'
/**
 * @brief simboliza o ponto presente na codificação MORSE (1 unit)
 */
#define DOT '.'
/**
 * @brief número de posições iniciais no array alocado 'traduc_registadas'
 */
#define TREG 10
/**
 * @brief tamanho limite do array 'identific' presente na estrutura 'traduc'
 */
#define MAXID 25
/**
 * @brief número de caracteres nas contantes 'morse_code' e 'texto'
 */
#define MAXC 36
/**
 * @brief número de caracteres nas contantes 'morse_pont' e 'texto_pont'
 */
#define MAXP 12

//morse code: https ://morsecode.scphillips.com/morse.html
/** A a Z em MORSE */
const char *morse_code[MAXC] = {".-", "-...", "-.-.", "-..", ".", "..-.",
    "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
    "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
    //numeros
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
    "---..", "----.",};
/** A a Z em texto */
const char *text[MAXC] = {"A", "B", "C", "D", "E", "F", "G", "H", "I",
    "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
/** pontuação em MORSE ".", ",", ":", "?", "'", "-", "/", "(", ")", "\"", "@", "=" */
const char *morse_pont[MAXP] = {".-.-.-", "--..--", "---...", "..--..",
    ".---.", "-....-", "-..-.", "-.--.", "-.--.-", ".-..-.", ".--.-.",
    "-...-"};
/** pontuação em texto ".", ",", ":", "?", "'", "-", "/", "(", ")", "\"", "@", "=" */
const char *text_pont[MAXP] = {".", ",", ":", "?", "'", "-", "/", "(", ")",
    "\"", "@", "="};

/**
 * Estrutura denominada "traduc".
 * 
 * Guarda a tradução feita durante a utilização do programa.
 * [o texto e o respetivo código MORSE (escrito)]
 * Tal como um identificação para essa tradução.
 */
typedef struct {
    char *txt; /**< Versão de texto da tradução.*/
    char *morse; /**< Versão código MORSE (escrito) da tradução.*/
    char identific[MAXID]; /**< Identificação da tradução.*/

} traduc;

/**
 * Reproduz o caracter passado em parâmetro nos 'speakers',
 * em forma de beep.
 * 
 * Esse caracter deve pertencer a um array que esteja escrito em formato
 * de código MORSE.
 * 
 * @warning Ter em conta que a função
 * exemplo de utilização:
 * @code
 * int i;
 * 
 * for (i = 0; i <= strlen('string a separar'); i++) {
 * 
 *     morse_beep('string a separar'[i]);
 * 
 * }
 * @endcode
 * 
 * @param inp caracter pertencente à string previamente separada
 */
void morse_beep(char inp) {

    Sleep(300);
    if (inp == DASH) {
        Beep(750, 240);
        Sleep(80);
    } else {
        if (inp == DOT) {
            Beep(750, 80);
            Sleep(80);
        } else {
            if (inp == ' ') {
                Sleep(240);
            } else {
                if (inp == '/') {
                    Sleep(560);
                }
            }
        }
    }
}

/**
 * Cria uma string de tamanho indeterminado,
 * preenchendo um array com caracteres introduzidos em stdin ou existentes
 * num ficheiro através da realocação (de memória) de um pointer.
 * 
 * @param input local de onde os caracteres são importados (stdin por definição)
 * @param sizeini tamanho inicial do array a ser preenchido
 * @return string com o tamanho inserido alocado
 */
char *AnySizeStr(FILE *input, int sizeini) {
    char *str;
    int ch, length = 0;

    str = (char*) calloc(sizeini, sizeof (char));

    while ((ch = fgetc(input)) != '\n' && EOF) { //introdução de caracteres

        str[length] = ch;
        length++; //verificação do tamanho

        if (length == sizeini) {//realocação 

            if ((str = (char*) realloc(str, sizeof (char)*(sizeini += sizeini))) == NULL) {
                printf("\nERRO !!\n");
                printf("Impossível alocar mais memória!\n");
                *str = 0;
                return NULL;
            }

        }
    }

    str[length++] = '\0';

    return realloc(str, length);
}

/**
 * Possibilita ao utilizador uma escolha entre duas alternativas, através
 * de uma simples pergunta de Sim ou Não
 * 
 * @param print representa a mensagem a imprimir com informação sobre a escolha
 * @return retorna 1 se afirmativo e 0 se negativo
 */
int escolher(char const *print) {
    char escolha = 0;

    while (escolha != 's' && escolha != 'n' && escolha != 'S' && escolha != 'N') {

        printf("%s", print);
        printf("S (sim) ou N (não): ");
        scanf(" %c", &escolha);
        cleanInputBuffer();

    }

    if (escolha == 's' || escolha == 'S')

        return 1;

    else

        return 0;
}

/**
 * Função com intuito de compactar o código.
 * 
 * Reproduz nos speakers, através do uso da função 'morse_beep', o código
 * morse passado em parâmetro.
 * 
 * @param morse é um pointer que contém um array de caracteres de formato
 * código MORSE (escrito)
 */
void reproduzir(char *morse) {
    int i, esc;

    esc = escolher("\nDeseja reproduzir o código nos 'speakers'? \n");

    if (esc == 1) {

        for (i = 0; i <= strlen(morse); i++) {

            morse_beep(morse[i]);

        }
    }
}

/**
 * (DEPRECATED)
 * Função com intuito de compactar o código.
 * 
 * Liberta a memória alocada para os pointers presentes na função main e zera
 * o ficheiro criado.
 * 
 * @param a pointer existente na função main a ser 'libertado' 
 * @param b pointer existente na função main a ser 'libertado' 
 * @param c pointer existente na função main a ser 'libertado' 
 * @param d pointer existente na função main a ser 'libertado' 
 * @param e pointer existente na função main a ser 'libertado'
 * @param file ficheiro a zerar 
 */
void free_memory(char *a, char *b, char *c, char *d, traduc *e) {

}

/**
 * Realiza uma mensagem especial se o código passado contiver um SOS
 * 
 * @param inp pointer que aponta para uma string escrita, em princípio, 
 * em código MORSE
 * @return retorna 1 se for ativado
 */
int sos(char *inp) {
    int esc, i;

    if (strcmp(inp, "... --- ...") == 0 || strcmp(inp, "... --- ... ") == 0) {

        printf("\n\n\t** PEDIDO DE AJUDA ATIVADO!! **\n");

        esc = escolher("\nPretende reproduzir o pedido de Socorro?!\n");
        if (esc == 1) {

            for (i = 0; i < 3; i++) {

                Sleep(100);
                Beep(690, 100);
                Sleep(100);
                Beep(690, 100);
                Sleep(100);
                Beep(690, 100);
                Sleep(300);
                Beep(690, 300);
                Sleep(100);
                Beep(690, 300);
                Sleep(100);
                Beep(690, 300);
                Sleep(300);
                Beep(690, 100);
                Sleep(100);
                Beep(690, 100);
                Sleep(100);
                Beep(690, 100);
                Sleep(600);

            }
        } else
            return 1;
    } else
        return 0;
}

/**
 * Guarda a tradução presente num espaço do array onde estão registadas as
 * traduções guardadas pelo utilizador no ficheiro de texto passado por
 * parâmetro
 * 
 * @param f pointer que representa o ficheiro onde as traduções serão
 * guardadas
 * @param registar pointer que representa o array, do tipo 'struct', onde
 * estão registadas as traduções
 * @param count representa o inteiro que identifica o local em 'registar'
 */
int guardar_traduc(FILE *f, traduc *registar, int count) {

    if ((f = fopen("traducoes.txt", "a")) == NULL) {
        perror(NULL);
        return 0;

    } else {

        fprintf(f, "Identificacao: %s \n", registar[count].identific);
        fprintf(f, "|texto| %s |\n|morse| %s |\n", registar[count].txt, registar[count].morse);

        fclose(f);
        return 1;
    }
}

/**
 * Função com intuito de compactar o código.
 * 
 * Regista e Guarda, se respondido afirmativamente (s ou S), a última tradução 
 * feita durante a utilização do programa, ficheiro de texto.
 * 
 * @param f pointer que representa o ficheiro onde as traduções serão
 * guardadas
 * @param registar pointer que representa o array, do tipo 'struct', onde
 * será registado o texto e a correspondente tradução em MORSE
 * @param morse pointer que contém um array de caracteres de formato
 * código MORSE (escrito)
 * @param txt pointer que contém um array de caracteres em formato de texto
 */
void pretende_guardar_traducao(FILE *f, traduc *registar, char *morse, char *txt) {
    int esc, count = 0, i, size_regis = TREG;

    esc = escolher("\nPretende guardar esta tradução para uso futuro?\n");

    if (esc == 1) {

        if (count < size_regis) {
            //enquanto houver espaço no array

            registar[count].txt = txt;
            registar[count].morse = morse;

            if (count == 0) {
                //primeira introdução
                printf("\n(MAX 25 caracteres)\n");
                printf("Introduza uma identificação da tradução.\n");
                fgets(registar[count].identific, MAXID, stdin);
                cleanInputBuffer();

            } else {
                //introduções seguintes
                do {
                    printf("\n(MAX 25 caracteres)\n");
                    printf("[identificações repetidas não são aceites]\n");
                    printf("Introduza uma identificação da tradução.\n");
                    fgets(registar[count].identific, MAXID, stdin);
                    cleanInputBuffer();

                } while (strcmp(registar[count].identific, registar[count - 1].identific) != 0);

            }

            if ((guardar_traduc(f, registar, count)) == 1) {
                //guardar no ficheiro

                count++;

                printf("\nA tradução foi guardada com exito! \n");
                printf("Nota: pode encontrar as traduções guardadas ");
                printf("num ficheiro presente na pasta deste projeto.");

            } else
                //em caso de erro
                printf("A tradução não foi guardada no ficheiro!! \n");

            registar -> txt = NULL;
            free(registar -> txt);

            registar -> morse = NULL;
            free(registar -> morse);

        } else

            registar = realloc(registar, sizeof (traduc) * (size_regis += TREG));

    }
}

/**
 * @brief Reproduz uma música utilizando o Beep do Sistema (Windows)
 */
void ImperialMarch() {
    Sleep(100);
    Beep(440, 600);
    Sleep(25);
    Beep(440, 550);
    Sleep(25);
    Beep(440, 550);
    Sleep(25);
    Beep(349, 350);
    Beep(523, 100);
    Beep(440, 500);
    Beep(349, 450);
    Beep(523, 100);
    Beep(440, 1000);
    Sleep(25);
    Beep(659, 500);
    Sleep(25);
    Beep(659, 500);
    Sleep(25);
    Beep(659, 500);
    Sleep(25);
    Beep(698, 350);
    Beep(523, 100);
    Beep(415, 500);
    Beep(349, 450);
    Beep(523, 100);
    Beep(440, 1000);
    Sleep(50);
}

/**
 * @brief Reproduz uma música utilizando o Beep do Sistema (Windows)
 */
void randommusic() {

    Sleep(250);
    Beep(1109, 900);
    Beep(1245, 800);
    Beep(831, 500);
    Beep(1245, 900);
    Beep(1397, 800);
    Beep(1661, 25);
    Beep(1480, 25);
    Beep(1397, 50);
    Beep(1109, 1100);
    Beep(1245, 900);
    Beep(831, 1500);

    Sleep(750);

    Beep(1109, 900);
    Beep(1245, 800);
    Beep(831, 500);
    Beep(1245, 900);
    Beep(1397, 800);
    Beep(1661, 50);
    Beep(1480, 50);
    Beep(1397, 75);
    Beep(1109, 1100);
    Beep(1245, 900);
    Beep(831, 1400);

    Sleep(1000);
    /*
     * Created by Reddit /u/TwoTinyTrees
     * https ://www.reddit.com/r/PowerShell/comments/3o13fq/cool_song_in_system_beeps_using_powershell/
     */
    Beep(450, 110);
    Beep(500, 110);
    Beep(550, 110);
    Beep(450, 110);
    Beep(675, 200);
    Beep(675, 200);
    Beep(600, 300);
    Sleep(50);
    Beep(450, 110);
    Beep(500, 110);
    Beep(550, 110);
    Beep(450, 110);
    Beep(600, 200);
    Beep(600, 200);
    Beep(550, 300);
    Beep(525, 110);
    Beep(450, 300);
    Sleep(50);
    Beep(450, 110);
    Beep(500, 110);
    Beep(550, 110);
    Beep(450, 110);
    Beep(500, 400);
    Sleep(25);
    Beep(600, 300);
    Sleep(25);
    Beep(500, 400);
    Beep(475, 200);
    Beep(450, 200);
    Beep(400, 200);
    Beep(600, 500);
    Beep(525, 500);
    Sleep(50);
    Beep(450, 110);
    Beep(500, 110);
    Beep(550, 110);
    Beep(450, 110);
    Beep(675, 200);
    Beep(675, 200);
    Beep(600, 300);
    Sleep(50);
    Beep(450, 110);
    Beep(500, 110);
    Beep(550, 110);
    Beep(450, 110);
    Beep(800, 200);
    Beep(500, 200);
    Beep(550, 300);
    Beep(525, 110);
    Beep(450, 300);
    Sleep(50);
    Beep(450, 110);
    Beep(500, 110);
    Beep(550, 110);
    Beep(450, 110);
    Beep(500, 400);
    Sleep(25);
    Beep(600, 300);
    Sleep(25);
    Beep(500, 400);
    Beep(475, 200);
    Beep(450, 200);
    Beep(400, 200);
    Beep(600, 500);
    Beep(525, 500);
}

void takingthehobbits() {

    Sleep(100);
    Beep(523, 400);
    Beep(587, 50);
    Beep(659, 350);
    Sleep(100);
    Beep(784, 450);
    Sleep(50);
    Beep(659, 450);
    Sleep(100);
    Beep(587, 550);
    Sleep(50);
    Beep(523, 1000);
    Sleep(250);

    Beep(659, 350);
    Beep(784, 50);
    Beep(880, 350);
    Sleep(100);
    Beep(1046, 550);
    Sleep(100);
    Beep(988, 550);
    Sleep(50);
    Beep(784, 550);
    Sleep(100);
    Beep(659, 700);
    Sleep(50);
    Beep(698, 100);
    Beep(659, 50);
    Beep(587, 650);
    Sleep(150);

    Sleep(100);
    Beep(523, 400);
    Beep(587, 50);
    Beep(659, 350);
    Sleep(100);
    Beep(784, 550);
    Sleep(50);
    Beep(659, 50);
    Beep(587, 100);
    Sleep(150);
    Beep(523, 250);
    Beep(587, 50);
    Beep(523, 1000);
    Sleep(150);

    Sleep(50);
    Beep(659, 400);
    Beep(784, 50);
    Beep(880, 450);
    Sleep(100);
    Beep(880, 450);
    Sleep(100);
    Beep(880, 650);
    Sleep(50);
    Beep(784, 50);
    Sleep(350);
    Beep(659, 250);
    Beep(784, 50);
    Beep(659, 150);
    Beep(587, 50);
    Beep(659, 150);
    Beep(587, 50);
    Sleep(50);
    Beep(523, 700);

}

/**
 * @brief Mini sintetizador. 
 * Reproduz as notas C5 - D5 - E5 - F5 - G5 - A5 - B5 - C6 utilizando o
 * Beep do Sistema.
 */
void play_music() {
    int notas[8] = {523, 587, 659, 698, 784, 880, 988, 1047};
    char inp;

    printf("\nIntroduza um dos caracteres abaixo para reproduzir uma nota musical!\n");
    printf("Dó -> A \t Ré -> S \t Mi -> D\nFá -> F \t Sol -> G \t Lá -> H\n");
    printf("Si -> J \t Dó -> K \t Sair ->0\n");
    // C - D - E - F - G - A - B - C  close

    while ((inp = fgetc(stdin)) != '0') {
        cleanInputBuffer();
        switch (inp) {
            case 'A': Beep(notas[0], 350);
                break;
            case 'S': Beep(notas[1], 350);
                break;
            case 'D': Beep(notas[2], 350);
                break;
            case 'F': Beep(notas[3], 350);
                break;
            case 'G': Beep(notas[4], 350);
                break;
            case 'H': Beep(notas[5], 350);
                break;
            case 'J': Beep(notas[6], 350);
                break;
            case 'K': Beep(notas[7], 350);
                break;
            default: printf("*Introduza um caracter válido.*\n");
        }
    }
}

/**
 * @brief Imprime os caracteres ASCII e o código MORSE correspondente. 
 * O código MORSE utilizado neste projeto é baseado no presente neste site.
 * morse code: https ://morsecode.scphillips.com/morse.html
 */
void imprimir_MORSE() {
    int i;

    printf("\n");
    for (i = 0; i < MAXC; i++) {

        printf("%s -> %s\n", text[i], morse_code[i]);
    }

    printf("\n");
    for (i = 0; i < MAXP; i++) {

        printf("%s -> %s\n", text_pont[i], morse_pont[i]);
    }
}

/**
 * Faz a tradução de texto para código MORSE (escrito)
 * (é passado em parametro uma string com o texto e devolvido em return outra
 * string com o código MORSE (escrito) correspondente)
 * 
 * @param str é um pointer que contém um array de caracteres (string)
 * em formato de texto
 * @return string com a tradução em código MORSE (escrito)
 */
char *txt_morse(char* str) {
    char *morse;
    int i, morse_avgsize = 5;

    if ((morse = (char*) calloc(strlen(str), sizeof (char) * morse_avgsize)) == NULL) {
        printf("\nERRO !!\n");
        printf("Tradução para morse não realizada.\n");
        printf("Impossível alocar memória!\n");
        *morse = 0;
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {

        str[i] = toupper(str[i]);
        //transformação dos caracteres em maiúsculas para facilitar a tradução 

        if (str[i] >= 'A' && str[i] <= 'Z') {
            strcat(&morse[i], morse_code[str[i] - 'A']);
            strcat(&morse[i], " ");

        } else
            //tradução das letras e números através da utilização da tabela ASCII

            if (str[i] >= '0' && str[i] <= '9') {
            strcat(&morse[i], morse_code[str[i] - '0' + 26]);
            strcat(&morse[i], " ");

        } else
            //pontuação
            switch (str[i]) {

                case '.':
                    strcat(&morse[i], morse_pont[0]);
                    strcat(&morse[i], " ");
                    break;
                case ',':
                    strcat(&morse[i], morse_pont[1]);
                    strcat(&morse[i], " ");
                    break;
                case ':':
                    strcat(&morse[i], morse_pont[2]);
                    strcat(&morse[i], " ");
                    break;
                case '?':
                    strcat(&morse[i], morse_pont[3]);
                    strcat(&morse[i], " ");
                    break;
                case '\'':
                    strcat(&morse[i], morse_pont[4]);
                    strcat(&morse[i], " ");
                    break;
                case '-':
                    strcat(&morse[i], morse_pont[5]);
                    strcat(&morse[i], " ");
                    break;
                case '/':
                    strcat(&morse[i], morse_pont[6]);
                    strcat(&morse[i], " ");
                    break;
                case '(':
                    strcat(&morse[i], morse_pont[7]);
                    strcat(&morse[i], " ");
                    break;
                case ')':
                    strcat(&morse[i], morse_pont[8]);
                    strcat(&morse[i], " ");
                    break;
                case '"':
                    strcat(&morse[i], morse_pont[9]);
                    strcat(&morse[i], " ");
                    break;
                case '@':
                    strcat(&morse[i], morse_pont[10]);
                    strcat(&morse[i], " ");
                    break;
                case '=':
                    strcat(&morse[i], morse_pont[11]);
                    strcat(&morse[i], " ");
                case ' ':
                    strcat(&morse[i], "/");
                    strcat(&morse[i], " ");
                    break;
                default:
                    //error handling em caso de existirem caracteres desconhecidos   
                    strcat(&morse[i], "#");
                    strcat(&morse[i], " ");
                    printf("**Caracter desconhecido encontrado ||%c||\n", str[i]);
                    printf("**Substituição do mesmo por ||#||\n");
            }

    }

    return morse;
}

/**
 * Faz a tradução de código MORSE (escrito) para texto
 * (é passado em parametro uma string com o código e devolvido em return outra
 * string com o texto traduzido)
 * 
 * @param str é um pointer que contém um array de caracteres (string)
 * em formato de código MORSE (escrito)
 * @return string com a tradução em texto
 */
char *morse_txt(char *str) {
    char *token, *txt, str_tokens[strlen(str)];
    int chk, i;

    for (i = 0; i <= strlen(str); i++) {
        str_tokens[i] = str[i]; //preenchimento do array destinado aos 'tokens'
                                //uma vez que a função 'strtok' vai "desfazer"
                                //a string introduzida!
    }

    if ((txt = (char*) calloc(1, sizeof (char))) == NULL) {
        printf("\nERRO !!\n");
        printf("Tradução para texto não realizada.\n");
        printf("Alocação de memória não permitida.\n");
        return (NULL);
    }

    token = strtok(str_tokens, " "); //criaçao do primeiro token

    while (token != NULL) {
        //traduçao de cada token então concatenados na string devolvida

        if (strcmp(token, "/") == 0) {
            strcat(txt, " ");

        } else {

            for (i = 0; i <= MAXC; i++) {
                chk = strcmp(token, morse_code[i]);

                if (chk == 0) {
                    strcat(txt, text[i]);

                }



            }

            for (i = 0; i <= MAXP; i++) {
                chk = strcmp(token, morse_pont[i]);

                if (chk == 0)
                    strcat(txt, text_pont[i]);
            }
        }
        token = strtok(NULL, " "); //restantes tokens
    }
    free(token);
    token = NULL;

    return txt;
}

/**
 * @brief Função com intuito de compactar o código. Cria um submenu.
 */
void outros() {
    int opcao;

    printf("\n\t ** BEM VINDO AO MENU \"Extras\" **\n");
    printf("Divirta-se!\n");

    do {

        do {
            printf("\n[Slct 1]-> Música: Star Wars - Imperial March Soundtrack\n");
            printf("[Slct 2]-> Música: Never gonna give you up!\n");
            printf("[Slct 3]-> Notas Musicais\n");
            printf("[Slct 4]-> We're Taking Hobbits to Isengard! \n");
            printf("[Slct 0]-> Close. \n");
            printf("<SELECT HERE>: ");
            scanf(" %d", &opcao);
            cleanInputBuffer();
        } while (opcao < 0 || opcao > 4);

        switch (opcao) {
            case 1:
                ImperialMarch();
                break;

            case 2:
                randommusic();
                break;

            case 3:
                play_music();
                break;

            case 4:
                takingthehobbits();
                break;

            default: printf("\n\t  ** Worten Sempre! **\n");
        }
    } while (opcao != 0);
}

/**
 * @brief Função principal do programa. 
 * Permite a interação do utilizador com o funcionamento do programa através de um simples menu.
 */
int main(int argc, char** argv) {
    FILE *traducoes;
    traduc *traduc_registadas = calloc(TREG, sizeof (traduc));
    unsigned int c;
    unsigned short int opcao, esc;
    char *txt_in = NULL, *morse_in = NULL, *morse_out = NULL, *txt_out = NULL;

    printf("\n\t|*|*| Seja Bem-Vindo ao Traduc MORSE 1.0 ! |*|*|\n");
    printf("\n\tEscolha uma destas opções para começar! \n");

    do {
        do {
            printf("\n[Slct 1]-> Introdução: Texto  &  Tradução: Texto - MORSE \n");
            printf("[Slct 2]-> Introdução: MORSE (escrito)  &  Tradução: MORSE - Texto \n");
            printf("[Slct 3]-> Ler o ficheiro inteiro. \n");
            printf("[Slct 4]-> Limpar o ficheiro. \n");
            printf("[Slct 5]-> Visualizar o código MORSE correspondente aos caracteres ASCII. \n");
            printf("[Slct 6]-> Extras \n");
            printf("[Slct 0]-> Close. \n");
            printf("<SELECT HERE>: ");
            scanf(" %d", &opcao);
        } while (opcao < 0 || opcao > 6);
        cleanInputBuffer();

        switch (opcao) {

            case 1:
                if (txt_in != NULL) {
                    //Se já existir um array em txt_in ...

                    esc = escolher("\nTenciona utilizar o mesmo texto? \n");
                    if (esc == 0) {
                        //Se 'n' ou 'N' (na função 'escolher')

                        printf("\nIntroduza o texto a traduzir: \n");
                        txt_in = AnySizeStr(stdin, 5);

                        morse_out = txt_morse(txt_in);
                        esc = escolher("\nVisualizar a tradução em MORSE escrita do texto inserido. \n");
                        if (esc == 1) {
                            printf("\nTRADUÇÃO: %s \n", morse_out);

                        }

                        reproduzir(morse_out);

                        pretende_guardar_traducao(traducoes, traduc_registadas, morse_out, txt_in);

                    } else {
                        //Se 's' ou 'S' (na função 'escolher')
                        printf("\nTRADUÇÃO: %s \n", morse_out);

                        reproduzir(morse_out);

                        pretende_guardar_traducao(traducoes, traduc_registadas, morse_out, txt_in);
                        //VERIFICAR SE NÃO ESTÁ A GUARDAR REPETIDAMENTE, DUPLICADOS
                    }

                } else {
                    //Se não existir um array em txt_in[= NULL] (início do programa)

                    printf("\nIntroduza o texto a traduzir: \n");
                    txt_in = AnySizeStr(stdin, 5);

                    morse_out = txt_morse(txt_in);
                    if (sos(morse_out) == 1) {
                        txt_in = NULL;
                        morse_out = NULL;
                        break;
                    }

                    esc = escolher("\nVisualizar a tradução em MORSE escrita do texto inserido. \n");
                    if (esc == 1) {
                        printf("\nTRADUÇÃO: %s \n", morse_out);

                    }

                    reproduzir(morse_out);

                    pretende_guardar_traducao(traducoes, traduc_registadas, morse_out, txt_in);

                }

                printf("\n");
                break;

            case 2:
                if (morse_in != NULL) {
                    //Se já existir um array em morse_in ...

                    esc = escolher("\nTenciona utilizar o mesmo código? \n");
                    if (esc == 0) {
                        //Se 'n' ou 'N' (na função 'escolher')

                        printf("\nIntroduza o código [em MORSE (\".\" & \"-\")]: \n");
                        morse_in = AnySizeStr(stdin, 10);

                        reproduzir(morse_in);

                        txt_out = morse_txt(morse_in);
                        esc = escolher("\nVisualizar a tradução em texto do código MORSE inserido. \n");
                        if (esc == 1) {
                            printf("\nTRADUÇÃO: %s \n", txt_out);

                        }

                        pretende_guardar_traducao(traducoes, traduc_registadas, morse_in, txt_out);


                    } else {
                        //Se 's' ou 'S' (na função 'escolher')
                        printf("\nTRADUÇÃO: %s \n", txt_out);

                        reproduzir(morse_in);

                        pretende_guardar_traducao(traducoes, traduc_registadas, morse_in, txt_out);
                        //VERIFICAR SE NÃO ESTÁ A GUARDAR REPETIDAMENTE, DUPLICADOS
                    }

                } else {
                    //Se não existir um array em morse_in[= NULL] (início do programa)

                    printf("\nIntroduza o código [ em MORSE (\".\" & \"-\") ]: \n");
                    morse_in = AnySizeStr(stdin, 10);

                    if (sos(morse_in) == 1) {
                        morse_in = NULL;
                        break;
                    }

                    reproduzir(morse_in);

                    txt_out = morse_txt(morse_in);
                    esc = escolher("\nVisualizar a tradução em texto do código MORSE inserido. \n");
                    if (esc == 1) {
                        printf("\nTRADUÇÃO: %s \n", txt_out);

                    }

                    pretende_guardar_traducao(traducoes, traduc_registadas, morse_in, txt_out);

                }

                printf("\n");
                break;

            case 3:
                traducoes = fopen("traducoes.txt", "r");

                if (traducoes != NULL) {
                    rewind(traducoes);
                    printf("\n"); //parágrafo para melhor visualização no output
                    while ((c = getc(traducoes)) != EOF)
                        putchar(c);
                    fclose(traducoes);

                } else
                    perror("\nError: ");

                break;

            case 4:
                esc = escolher("\nPretende Limpar o ficheiro?\nLembre-se de que se o fizer irá perder todo o conteúdo guardado!\n");
                if (esc == 1)
                    traducoes = fopen("traducoes.txt", "w");
                fclose(traducoes);

                break;

            case 5:
                imprimir_MORSE();

                break;

            case 6:
                outros();

                break;

            default:
                free(morse_in);
                morse_in = NULL;
                //--
                free(txt_out);
                txt_out = NULL;
                //--
                free(traduc_registadas);
                traduc_registadas = NULL;
                printf("\n\t\t******\n\tObrigado e volte sempre!\n\t\t******\n");
        }
    } while (opcao != 0);

    return (EXIT_SUCCESS);
}