#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cctype>

int i;
int bal;
int bet;
int dealer = 0;
int player = 0;
int facecard = 10;
int ace = 1;
int seed = 0;
bool done = false;
bool playerTurn = true;
std::string action;


int card(int score)
{
    int card = rand() % 13;
    card++;

    if(card >= 10) // handles J Q K and turns them into 10
        card = 10;

    if(score <= 10 && card == 1) // handles ace
        card += 10;
    
    return card;

}

void setup()
{

        std::cout << "Give a number between 1 - 100 000 000 to use as a seed for the game :)" << std::endl;
        std::cin >> seed;
        srand(seed);

        std::cout << "Give a number to use as your balance" << std::endl;
        std::cin >> bal; 

        if(seed >= 100000001 || seed <= 0){
            std::cout << "stop" << std::endl; 
            return;
        }return;
}

/*


Add a loop for multiple hits.

Add dealer turn after player turn ends.

Add ending condition and reset or stop logic.

 */
int main()
{ 
    setup();
    std::cout << "You have " << bal << " credits." << std::endl;
    std::cout << "Enter bet amount." <<std::endl;

    std::cin >> bet;
    bal -= bet;

    while(!done)
    {
        dealer = card(dealer);
        player = card(player);
        player += card(player);


        while(playerTurn){
            std::cout <<"Dealer shows " << dealer << std::endl;
            std::cout <<"You have " << player << std::endl;

            std::cout <<"Do you stand, hit or double?" << std::endl;
            std::cin >> action;


            action:
            int cmpaction = 
                (action == "stand") ? 1:
                (action == "hit") ? 2:
                (action == "double") ? 3: 4;

            switch(cmpaction)
            {
                case 1: // stand
                    if(dealer >=17){
                        playerTurn = false;
                        continue;
                    }
                    else
                        while(dealer <=16){
                            i=0;
                            i = card(dealer);
                            std::cout<<"Dealer has "<< dealer <<" and picked up " << i << std::endl;
                            dealer += i;
                        }
                    playerTurn = false;
                    break;

                case 2: // hit
                    player += card(player);
                    std::cout<<"You have " << player << std::endl;
                    break;
 
                case 3: // double
                    bet += bet;
                    bal -= bet;
                    player += card(player);
                    playerTurn = false;
                    std::cout<<"You have " << player << std::endl;
                    playerTurn = false;
                    break;
                
                case 4: // err
                    std::cout << "Incorrect or missing input, please type hit, stand or double." << std::endl;
                    goto action;
                    break;
            }
        } // playerturn end
        
        while(dealer <= 16){
            i=0;
            i = card(dealer);
            std::cout<<"Dealer has"<< dealer <<" and picked up " << i << std::endl;
            dealer += i;
        }
        std::cout<<"Dealer got " << dealer << std::endl;
        std::cout<<"You have " << player << std::endl;

        if(player > dealer){
            bal += bet + bet;
            std::cout << "You win! Your new balance is "<< bal << std::endl;
        }else if (player > dealer || player == 21){
            bal += bet +bet * 1.5;
            std::cout << "You got blackjack! Your new balance is "<< bal << std::endl;
        }else if(player == dealer){
            bal += bet;
            std::cout << "You tied. Your balance is still "<< bal << std::endl;
        }else if (player < dealer || dealer <= 21){
            std::cout << "You lost :( Your new balance is "<< bal << std::endl;
        }else if (player < dealer || dealer >= 22 || player <= 20){
            std::cout << "You lost :( Your new balance is "<< bal << std::endl;
        }
        playerTurn = false;
        done = true;
        std::cout << "Play again?" << std::endl;
    }
 
}



