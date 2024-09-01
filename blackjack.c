#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Option menus
int menu1();
int menu2();
double menu3(double bal);
double menu4(string insur, double curbal, int csum, double bal);
int menu5(string again, double bal);

// Create card hands
void convertPlayer();
void convertCasino();
int hit();
void convertHit();

// Caluclate
int sum(int x, int y, int a, int b, int c);
int randGen(int upper, int lower);

int main()
{
    char hs[10], insur[10], again[10];
    int player, casino, p1, p2, c1, c2, lower = 1, upper = 13, ph1, ph2, ph3, ch1, ch2, ch3, psum, csum, hitCount, valid;
    bool valid_input2 = true, valid_input3 = true, bj = false;
    double bal = 1000.0, curbal, temp;
    valid = menu1();
    if (valid == 1)
    {
        return 1;
    }
    valid = menu2();
    if (valid == 1)
    {
        return 1;
    }
    while (valid == 0 && bal > 0) // The Game
    {
        printf("How much would you like to bet on this hand?\n");
        curbal = menu3(bal);
        hitCount = 0;
        srand(time(NULL));
        p1 = randGen(upper, lower);
        p2 = randGen(upper, lower);
        c1 = randGen(upper, lower);
        c2 = randGen(upper, lower);
        ph1 = randGen(upper, lower);
        ph2 = randGen(upper, lower);
        ph3 = randGen(upper, lower);
        ch1 = randGen(upper, lower);
        ch2 = randGen(upper, lower);
        ch3 = randGen(upper, lower);
        psum = sum(p1, p2, 0, 0, 0);
        csum = sum(c1, c2, 0, 0, 0);
        convertCasino(c1);
        printf("\t Player's Hand\n");
        convertPlayer(p1, p2, ph1, hitCount);
        bj = false;
        insur[0] = '\0';
        if ((c1 >= 10 || c1 == 1) && psum != 21)
        {
            curbal = menu4(insur, curbal, csum, bal);
            if (strcmp(insur, "yes") == 0 || strcmp(insur, "y") == 0 || strcmp(insur, "Yes") == 0 || strcmp(insur, "Y") == 0)
            {
                bal -= (curbal * .5);
            }
        }

        do // Option menu #5
        {
            if (psum < 21 && csum != 21)
            {
                printf("-------------------\n");
                printf("Hit or Stay(H|S): ");
                scanf("%s", hs);
                printf("-------------------\n");
                if (strcmp(hs, "hit") == 0 || strcmp(hs, "h") == 0 || strcmp(hs, "Hit") == 0 || strcmp(hs, "H") == 0)
                {
                    hitCount++;
                    if (hitCount == 1)
                    {
                        printf("\t Player's Hand\n");
                        convertPlayer(p1, p2, ph1, hitCount);
                        psum = sum(p1, p2, ph1, 0, 0);
                    }
                    else if (hitCount == 2)
                    {
                        printf("\t Player's Hand\n");
                        convertHit(p1, p2, ph1, ph2, ph3, hitCount);
                        psum = sum(p1, p2, ph1, ph2, 0);
                    }
                    else
                    {
                        printf("\t Player's Hand\n");
                        convertHit(p1, p2, ph1, ph2, ph3, hitCount);
                        psum = sum(p1, p2, ph1, ph2, ph3);
                    }
                    valid_input2 = true;
                }
                else if (strcmp(hs, "stay") == 0 || strcmp(hs, "s") == 0 || strcmp(hs, "Stay") == 0 || strcmp(hs, "S") == 0)
                {
                    valid_input2 = false;
                }
                else
                {
                    printf("Invalid input! Please enter Hit or Stay (H|S).\n");
                    valid_input2 = true;
                }
            }
            else
            {
                valid_input2 = false;
            }
        }
        while (valid_input2);
        valid_input2 = true;
        if (psum == 21 && hitCount == 0)
        {
            printf("Blackjack!!!\n");
            bal += curbal * 1.5;
            bj = true;
        }
        hitCount = 0;
        printf("\t Casino's Hand\n");
        convertPlayer(c1, c2, ch1, hitCount);
        if (hitCount == 0 && csum <= 16 && psum < 21)
        {
            do
            {
                if (csum <= 16)
                {
                    hitCount++;
                    if (hitCount == 1)
                    {
                        printf("\t Casino's Hand\n");
                        convertPlayer(c1, c2, ch1, hitCount);
                        csum = sum(c1, c2, ch1, 0, 0);
                    }
                    else if (hitCount == 2)
                    {
                        printf("\t Casino's Hand\n");
                        convertHit(c1, c2, ch1, ch2, ch3, hitCount);
                        csum = sum(c1, c2, ch1, ch2, 0);
                    }
                    else
                    {
                        printf("\t Casino's Hand\n");
                        convertHit(c1, c2, ch1, ch2, ch3, hitCount);
                        csum = sum(c1, c2, ch1, ch2, ch3);
                    }
                }
                else
                {
                    hitCount = 4;
                }
            }
            while (csum < 21 && hitCount < 4 && bj == false);
        }
        if (psum > 21)
        {
            printf("Player Busts\n");
            bal -= curbal;
        }
        if (csum > psum && csum <= 21)
        {
            printf("Casino Wins!!!\n");
            bal -= curbal;
        }
        if (psum == csum)
        {
            printf("Push\n");
        }
        if ((psum > csum && psum <= 21) || csum > 21)
        {
            printf("Player Wins\n");
            bal += curbal;
        }
    valid = menu5(again, bal);
    }
    if(bal <= 0){
    printf("You have run out of money!!!\n");
    }
    printf("Thanks for playing\n"); // End of game
}

int menu1()
{ // Option menu #1
    bool valid_input = true;
    string option;
    do
    {
        printf("-------------------------------------------------------\n");
        printf("|Welcome to virtual Blackjack generated with C code!!!|\n");
        printf("|Please select an option!!!                           |\n");
        printf("|Play:           1                                    |\n");
        printf("|Strategy Chart: 2                                    |\n");
        printf("|Exit:           3                                    |\n");
        printf("-------------------------------------------------------\n");
        option = get_string("Option:          ");
        if (strcmp(option, "1") == 0 || strcmp(option, "2") == 0 || strcmp(option, "3") == 0)
        {
            valid_input = true;
        }
        else
        {
            printf("Invalid input! Please enter 1, 2, or 3\n");
            valid_input = false;
        }
    }
    while (!valid_input);
    if (strcmp(option, "2") == 0)
    {
        printf("You can find the Strategy Chart here: https://www.blackjackapprenticeship.com/blackjack-strategy-charts/\n");
    }
    if (strcmp(option, "3") == 0)
    {
        printf("Maybe next time\n");
        return 1;
    }
    return 0;
}

int menu2()
{ // Option menu #2
    bool valid_input = true;
    string option;
    do
    {
        printf("------------------------------------------\n");
        option = get_string("Would you like to play Blackjack (Y|N): ");
        printf("------------------------------------------\n");
        if (strcmp(option, "yes") == 0 || strcmp(option, "y") == 0 || strcmp(option, "no") == 0 || strcmp(option, "n") == 0 ||
            strcmp(option, "Yes") == 0 || strcmp(option, "No") == 0 || strcmp(option, "Y") == 0 || strcmp(option, "N") == 0)
        {
            printf(strcmp(option, "yes") == 0 || strcmp(option, "y") == 0 ? "Let's play!\n" : "Maybe next time!\n");
            valid_input = false;
        }
        else
        {
            printf("Invalid input! Please enter Yes or No (Y|N).\n");
            valid_input = true;
        }
    }
    while (valid_input);
    if (strcmp(option, "no") == 0 || strcmp(option, "n") == 0 || strcmp(option, "No") == 0 || strcmp(option, "N") == 0)
    {
        return 1;
    }
    return 0;
}

double menu3(double bal)
{ // Option menu #3
    bool valid_input = true;
    float x;
    do
    {
        printf("Your Current Balance: $%.2f\n", bal);
        printf("Amount you want to gamble: $");
        scanf("%f", &x);
        if (bal >= x)
        {
            valid_input = false;
        }
        else
        {
            printf("Invalid input! Please enter a value less than your balance.\n");
            valid_input = true;
        }
    }
    while (valid_input);
    return x;
}

double menu4(string insur, double curbal, int csum, double bal)
{ // Option menu #4
    bool valid_input = true;
    do
    {
        printf("Would you like insurance(Y|N): ");
        scanf("%s", insur);
        int temp = curbal / 2.0;
        if (strcmp(insur, "yes") == 0 || strcmp(insur, "y") == 0 || strcmp(insur, "Yes") == 0 || strcmp(insur, "Y") == 0 ||
            strcmp(insur, "no") == 0 || strcmp(insur, "n") == 0 || strcmp(insur, "No") == 0 || strcmp(insur, "N") == 0)
        {
            valid_input = false;
        }
        else
        {
            valid_input = true;
        }
    }
    while (valid_input);
    if (csum == 21)
    {
        printf("Casino has Blackjack!!!\n");
    }
    else
    {
        printf("Casino does not have Blackjack!!!\n");
    }
    return curbal;
}

int menu5(string again, double bal){ // Option menu #6
bool valid_input = true;
    do
        {
            printf("Would you like to play again(Y|N): ");
            scanf("%s", again);
            if (strcmp(again, "yes") == 0 || strcmp(again, "y") == 0 || strcmp(again, "Yes") == 0 || strcmp(again, "Y") == 0)
            {
                valid_input = false;
                return 0;
            }
            else if (strcmp(again, "no") == 0 || strcmp(again, "n") == 0 || strcmp(again, "No") == 0 || strcmp(again, "N") == 0)
            {
                printf("Your final balance is: %.2f\n", bal);
                valid_input = false;
                return 1;
            }
            else
            {
                valid_input = true;
            }
        }
        while (valid_input);
        return 0;
}

int randGen(int upper, int lower)
{
    int x = (rand() % (upper - lower + 1)) + lower;
    return x;
}

void convertPlayer(int x, int y, int a, int b) // Print out players hand
{
    if (b == 0)
    {
        printf("----------- \t -----------\n");
        printf("|         | \t |         |\n");
        if (x >= 10 || x == 1)
        {
            if (x == 10)
            {
                printf("|    %d   | \t", x);
            }
            if (x == 1)
            {
                printf("|    A    | \t");
            }
            if (x == 11)
            {
                printf("|    J    | \t");
            }
            if (x == 12)
            {
                printf("|    Q    | \t");
            }
            if (x == 13)
            {
                printf("|    K    | \t");
            }
        }
        else
        {
            printf("|    %d    | \t", x);
        }
        if (y >= 10 || y == 1)
        {
            if (y == 10)
            {
                printf(" |    %d   | \n", y);
            }
            if (y == 1)
            {
                printf(" |    A    | \n");
            }
            if (y == 11)
            {
                printf(" |    J    | \n");
            }
            if (y == 12)
            {
                printf(" |    Q    | \n");
            }
            if (y == 13)
            {
                printf(" |    K    | \n");
            }
        }
        else
        {
            printf(" |    %d    | \n", y);
        }
        printf("|         | \t |         |\n");
        printf("----------- \t -----------\n");
    }
    else
    {
        printf("----------- \t ----------- \t -----------\n");
        printf("|         | \t |         | \t |         |\n");
        if (x >= 10 || x == 1)
        {
            if (x == 10)
            {
                printf("|    %d   | \t", x);
            }
            if (x == 1)
            {
                printf("|    A    | \t");
            }
            if (x == 11)
            {
                printf("|    J    | \t");
            }
            if (x == 12)
            {
                printf("|    Q    | \t");
            }
            if (x == 13)
            {
                printf("|    K    | \t");
            }
        }
        else
        {
            printf("|    %d    | \t", x);
        }
        if (y >= 10 || y == 1)
        {
            if (y == 10)
            {
                printf(" |    %d   | \t", y);
            }
            if (y == 1)
            {
                printf(" |    A    | \t");
            }
            if (y == 11)
            {
                printf(" |    J    | \t");
            }
            if (y == 12)
            {
                printf(" |    Q    | \t");
            }
            if (y == 13)
            {
                printf(" |    K    | \t");
            }
        }
        else
        {
            printf(" |    %d    | \t", y);
        }
        if (a >= 10 || a == 1)
        {
            if (a == 10)
            {
                printf(" |    %d   | \n", a);
            }
            if (a == 1)
            {
                printf(" |    A    | \n");
            }
            if (a == 11)
            {
                printf(" |    J    | \n");
            }
            if (a == 12)
            {
                printf(" |    Q    | \n");
            }
            if (a == 13)
            {
                printf(" |    K    | \n");
            }
        }
        else
        {
            printf(" |    %d    | \n", a);
        }
        printf("|         | \t |         | \t |         |\n");
        printf("----------- \t ----------- \t -----------\n");
    }
}

void convertCasino(int x) // Print out casinos hand
{
    printf("\t Casino's Hand\n");
    if (x >= 10 || x == 1)
    {
        if (x == 10)
        {
            printf("----------- \t -----------\n");
            printf("|         | \t |         |\n");
            printf("|    %d   | \t |    ?    |\n", x);
            printf("|         | \t |         |\n");
            printf("----------- \t -----------\n");
        }
        if (x == 1)
        {
            printf("----------- \t -----------\n");
            printf("|         | \t |         |\n");
            printf("|    A    | \t |    ?    |\n");
            printf("|         | \t |         |\n");
            printf("----------- \t -----------\n");
        }
        if (x == 11)
        {
            printf("----------- \t -----------\n");
            printf("|         | \t |         |\n");
            printf("|    J    | \t |    ?    |\n");
            printf("|         | \t |         |\n");
            printf("----------- \t -----------\n");
        }
        if (x == 12)
        {
            printf("----------- \t -----------\n");
            printf("|         | \t |         |\n");
            printf("|    Q    | \t |    ?    |\n");
            printf("|         | \t |         |\n");
            printf("----------- \t -----------\n");
        }
        if (x == 13)
        {
            printf("----------- \t -----------\n");
            printf("|         | \t |         |\n");
            printf("|    K    | \t |    ?    |\n");
            printf("|         | \t |         |\n");
            printf("----------- \t -----------\n");
        }
    }
    else
    {
        printf("----------- \t -----------\n");
        printf("|         | \t |         |\n");
        printf("|    %d    | \t |    ?    |\n", x);
        printf("|         | \t |         |\n");
        printf("----------- \t -----------\n");
    }
}

int sum(int x, int y, int a, int b, int c) // Find the sum of the cards in the players hand or the casinos hand
{
    int sum = 0;
    int aces = 0;
    if (x > 10 || x == 1)
    {
        if (x == 1)
        {
            aces++;
            sum += 11;
        }
        if (x == 11)
        {
            sum += 10;
        }
        if (x == 12)
        {
            sum += 10;
        }
        if (x == 13)
        {
            sum += 10;
        }
    }
    else
    {
        sum += x;
    }
    if (y > 10 || y == 1)
    {
        if (y == 1)
        {
            aces++;
            sum += 11;
        }
        if (y == 11)
        {
            sum += 10;
        }
        if (y == 12)
        {
            sum += 10;
        }
        if (y == 13)
        {
            sum += 10;
        }
    }
    else
    {
        sum += y;
    }
    if (a > 10 || a == 1)
    {
        if (a == 1)
        {
            aces++;
            sum += 11;
        }
        if (a == 11)
        {
            sum += 10;
        }
        if (a == 12)
        {
            sum += 10;
        }
        if (a == 13)
        {
            sum += 10;
        }
    }
    else
    {
        sum += a;
    }
    if (b > 10 || b == 1)
    {
        if (b == 1)
        {
            aces++;
            sum += 11;
        }
        if (b == 11)
        {
            sum += 10;
        }
        if (b == 12)
        {
            sum += 10;
        }
        if (b == 13)
        {
            sum += 10;
        }
    }
    else
    {
        sum += b;
    }
    if (c > 10 || c == 1)
    {
        if (c == 1)
        {
            aces++;
            sum += 11;
        }
        if (c == 11)
        {
            sum += 10;
        }
        if (c == 12)
        {
            sum += 10;
        }
        if (c == 13)
        {
            sum += 10;
        }
    }
    else
    {
        sum += c;
    }
    while (aces > 0 && sum > 21)
    {
        sum -= 10;
        aces--;
    }
    return sum;
}

int hit(int x, int y) // Prints out the new hand of the player or casino if a hit is requested
{
    if (y > 10 || y == 1)
    {
        if (y == 11)
        {
            x += 10;
        }
        if (y == 12)
        {
            x += 10;
        }
        if (y == 13)
        {
            x += 10;
        }
        if (y == 1)
        {
            if (11 + x > 21)
            {
                x += 1;
            }
            else
            {
                x += 11;
            }
        }
    }
    else
    {
        x += y;
    }
    return x;
}

void convertHit(int x, int y, int a, int b, int c, int d)
{
    if (d == 2)
    {
        printf("----------- \t ----------- \t ----------- \t -----------\n");
        printf("|         | \t |         | \t |         | \t |         |\n");
        if (x >= 10 || x == 1)
        {
            if (x == 10)
            {
                printf("|    %d   | \t", x);
            }
            if (x == 1)
            {
                printf("|    A    | \t");
            }
            if (x == 11)
            {
                printf("|    J    | \t");
            }
            if (x == 12)
            {
                printf("|    Q    | \t");
            }
            if (x == 13)
            {
                printf("|    K    | \t");
            }
        }
        else
        {
            printf("|    %d    | \t", x);
        }
        if (y >= 10 || y == 1)
        {
            if (y == 10)
            {
                printf(" |    %d   | \t", y);
            }
            if (y == 1)
            {
                printf(" |    A    | \t");
            }
            if (y == 11)
            {
                printf(" |    J    | \t");
            }
            if (y == 12)
            {
                printf(" |    Q    | \t");
            }
            if (y == 13)
            {
                printf(" |    K    | \t");
            }
        }
        else
        {
            printf(" |    %d    | \t", y);
        }
        if (a >= 10 || a == 1)
        {
            if (a == 10)
            {
                printf(" |    %d   | \t", a);
            }
            if (a == 1)
            {
                printf(" |    A    | \t");
            }
            if (a == 11)
            {
                printf(" |    J    | \t");
            }
            if (a == 12)
            {
                printf(" |    Q    | \t");
            }
            if (a == 13)
            {
                printf(" |    K    | \t");
            }
        }
        else
        {
            printf(" |    %d    | \t", a);
        }
        if (b >= 10 || b == 1)
        {
            if (b == 10)
            {
                printf(" |    %d   | \n", b);
            }
            if (b == 1)
            {
                printf(" |    A    | \n");
            }
            if (b == 11)
            {
                printf(" |    J    | \n");
            }
            if (b == 12)
            {
                printf(" |    Q    | \n");
            }
            if (b == 13)
            {
                printf(" |    K    | \n");
            }
        }
        else
        {
            printf(" |    %d    | \n", b);
        }
        printf("|         | \t |         | \t |         | \t |         |\n");
        printf("----------- \t ----------- \t ----------- \t -----------\n");
    }
    else
    {
        printf("----------- \t ----------- \t ----------- \t ----------- \t -----------\n");
        printf("|         | \t |         | \t |         | \t |         | \t |         |\n");
        if (x >= 10 || x == 1)
        {
            if (x == 10)
            {
                printf("|    %d   | \t", x);
            }
            if (x == 1)
            {
                printf("|    A    | \t");
            }
            if (x == 11)
            {
                printf("|    J    | \t");
            }
            if (x == 12)
            {
                printf("|    Q    | \t");
            }
            if (x == 13)
            {
                printf("|    K    | \t");
            }
        }
        else
        {
            printf("|    %d    | \t", x);
        }
        if (y >= 10 || y == 1)
        {
            if (y == 10)
            {
                printf(" |    %d   | \t", y);
            }
            if (y == 1)
            {
                printf(" |    A    | \t");
            }
            if (y == 11)
            {
                printf(" |    J    | \t");
            }
            if (y == 12)
            {
                printf(" |    Q    | \t");
            }
            if (y == 13)
            {
                printf(" |    K    | \t");
            }
        }
        else
        {
            printf(" |    %d    | \t", y);
        }
        if (a >= 10 || a == 1)
        {
            if (a == 10)
            {
                printf(" |    %d   | \t", a);
            }
            if (a == 1)
            {
                printf(" |    A    | \t");
            }
            if (a == 11)
            {
                printf(" |    J    | \t");
            }
            if (a == 12)
            {
                printf(" |    Q    | \t");
            }
            if (a == 13)
            {
                printf(" |    K    | \t");
            }
        }
        else
        {
            printf(" |    %d    | \t", a);
        }
        if (b >= 10 || b == 1)
        {
            if (b == 10)
            {
                printf(" |    %d   | \t", b);
            }
            if (b == 1)
            {
                printf(" |    A    | \t");
            }
            if (b == 11)
            {
                printf(" |    J    | \t");
            }
            if (b == 12)
            {
                printf(" |    Q    | \t");
            }
            if (b == 13)
            {
                printf(" |    K    | \t");
            }
        }
        else
        {
            printf(" |    %d    | \t", b);
        }
        if (c >= 10 || c == 1)
        {
            if (c == 10)
            {
                printf(" |    %d   | \n", c);
            }
            if (c == 1)
            {
                printf(" |    A    | \n");
            }
            if (c == 11)
            {
                printf(" |    J    | \n");
            }
            if (c == 12)
            {
                printf(" |    Q    | \n");
            }
            if (c == 13)
            {
                printf(" |    K    | \n");
            }
        }
        else
        {
            printf(" |    %d    | \n", c);
        }
        printf("|         | \t |         | \t |         | \t |         | \t |         |\n");
        printf("----------- \t ----------- \t ----------- \t ----------- \t -----------\n");
    }
}
// End of code
