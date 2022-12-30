#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <assert.h>

#define CLEAR_SCREEN "\033[2J"
#define MOVE_CURSOR_HOME "\033[H"
#define _XOPEN_SOURCE 700

#define CURSOR_ON "\033[?25h"
#define CURSOR_OFF "\033[?25l"

#define COLOR_RESET "\033[0m"
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

#define STYLE_BOLD "\033[1m"
#define STYLE_UNDERLINE "\033[4m"

#define KEY_UP 'A'
#define KEY_DOWN 'B'
#define KEY_RIGHT 'C'
#define KEY_LEFT 'D'

#define MENU_ITEM_COUNT 5

const char *menu_items[MENU_ITEM_COUNT] = {
    "Item 1",
    "Item 2",
    "Item 3",
    "Item 4",
    "Item 5"};

// int getkey()
// {
//     int character;
//     struct termios orig_term_attr;
//     struct termios new_term_attr;

//     /* set the terminal to raw mode */
//     tcgetattr(fileno(stdin), &orig_term_attr);
//     memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
//     new_term_attr.c_lflag &= ~(ECHO | ICANON);
//     new_term_attr.c_cc[VTIME] = 0;
//     new_term_attr.c_cc[VMIN] = 0;
//     tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

//     /* read a character from the stdin stream without blocking */
//     /*   returns EOF (-1) if no character is available */
//     character = fgetc(stdin);

//     /* restore the original terminal attributes */
//     tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

//     return character;
// }

int getch(void)
{
    int c = 0;

    struct termios org_opts, new_opts;
    int res = 0;
    //-----  store old settings -----------
    res = tcgetattr(STDIN_FILENO, &org_opts);
    assert(res == 0);
    //---- set new terminal parms --------
    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    c = getchar();
    //------  restore old settings ---------
    res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
    assert(res == 0);
    return (c);
}

int main(int argc, char **argv)
{
    int current_item = 0;

    // Masque le curseur et efface l'écran
    printf(CURSOR_OFF CLEAR_SCREEN);

    while (1)
    {
        // Déplace le curseur en haut de l'écran et affiche les éléments de menu
        printf(MOVE_CURSOR_HOME);

        for (int i = 0; i < MENU_ITEM_COUNT; i++)
        {
            // Met en surbrillance l'élément de menu actuellement sélectionné
            if (i == current_item)
            {
                printf(STYLE_BOLD COLOR_YELLOW "%s\n" COLOR_RESET, menu_items[i]);
            }
            else
            {
                printf("%s\n", menu_items[i]);
            }
        }

        // Lit une touche pressée par l'utilisateur
        char key = getch();

        // Navigue dans le menu en fonction de la touche pressée
        switch (key)
        {
        case KEY_UP:
            current_item--;
            if (current_item < 0)
            {
                current_item = MENU_ITEM_COUNT - 1;
            }
            break;
        case KEY_DOWN:
            current_item++;
            if (current_item >= MENU_ITEM_COUNT)
            {
                current_item = 0;
            }
            break;
        case KEY_LEFT:
            // Traitement des touches de gauche ici
            break;
        case KEY_RIGHT:
            // Traitement des touches de droite ici
            break;
        default:
            // Traitement des autres touches ici
            break;
        }
    }
    // Réactive le curseur
    printf(CURSOR_ON);

    // printf("\n");
    // printf("\x1B[31mTexting\033[0m\t\t");
    // printf("\x1B[32mTexting\033[0m\t\t");
    // printf("\x1B[33mTexting\033[0m\t\t");
    // printf("\x1B[34mTexting\033[0m\t\t");
    // printf("\x1B[35mTexting\033[0m\n");

    // printf("\x1B[36mTexting\033[0m\t\t");
    // printf("\x1B[36mTexting\033[0m\t\t");
    // printf("\x1B[36mTexting\033[0m\t\t");
    // printf("\x1B[37mTexting\033[0m\t\t");
    // printf("\x1B[93mTexting\033[0m\n");

    // printf("\033[3;42;30mTexting\033[0m\t\t");
    // printf("\033[3;43;30mTexting\033[0m\t\t");
    // printf("\033[3;44;30mTexting\033[0m\t\t");
    // printf("\033[3;104;30mTexting\033[0m\t\t");
    // printf("\033[3;100;30mTexting\033[0m\n");

    // printf("\033[3;47;35mTexting\033[0m\t\t");
    // printf("\033[2;47;35mTexting\033[0m\t\t");
    // printf("\033[1;47;35mTexting\033[0m\t\t");
    // printf("\t\t");
    // printf("\n");

    return 0;
}

// int main()
// {
//     int key;

//     /* initialize the random number generator */
//     srand(time(NULL));

//     for (;;)
//     {
//         key = getkey();
//         /* terminate loop on ESC (0x1B) or Ctrl-D (0x04) on STDIN */
//         if (key == 0x1B || key == 0x04)
//         {
//             break;
//         }
//         else
//         {
//             /* print random ASCII character between 0x20 - 0x7F */
//             key = (rand() % 0x7F);
//             printf("%c", ((key < 0x20) ? (key + 0x20) : key));
//         }
//     }

//     return 0;
// }