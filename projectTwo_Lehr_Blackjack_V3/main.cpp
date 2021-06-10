/*
    Author:    Cody Pfrunder
    Date:      3 June 2021  7:05 pm
    Project 2: Blackjack Game
    Version:   v.3 (Finished array for 4 players hand values, fixing arrays for 
               choice/answers to hit again or stand and align correctly with
               ptReslt function for each individual.)
 */

//System Libraries
#include <iostream>    //Input/Output Library
#include <iomanip>     //Input/Output Manipulation
#include <cstdlib>     //Random Number Library
#include <ctime>       //Time Library
#include <cmath>       //cmath library
#include <string>      //String Library
#include <vector>      //Vector Library
using namespace std;   //Library Name-space

//User Libraries

//Global/Universal Constants -- No Global Variables
//Science, Math, Conversions, Higher Dimensioned constants only
const float BLACKJACK = 1.25; //Pay increase for a blackjack
const int   SIZE = 4;         //Amt of players

//Function Prototypes
int calcD1C(int&, int);
int calcD2C(int&, int);
int calcD3C(int&, int);
int calcD4C(int&, int);
void ptReslt(int, int, int, int);
void prntF1C(int&, int, string, string, string, string);
void prntF2C(int&, int, string, string, string, string);
void prntF3C(int&, int, string, string, string, string);
void prntF4C(int&, int, string, string, string, string);
void prntD1C(int&, int, string, string, string, string);
void prntD2C(int&, int, string, string, string, string);
void prntD3C(int&, int, string, string, string, string);
void prntD4C(int&, int, string, string, string, string);


//Execution Begins Here
int main(int argc, char** argv){
    
    //Set the Random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    char   answer,   //Answer to play or not
           choice;   //Choice to stand with hand, or hit for more cards
    
    int    nShuff,   //Number of card shuffles
           score,    //Score for sum1 for each player
           bet,      //Player's bet
           tenVal,   //Cards with value of ten
           s1,       //Sum of card values (Player's hand)
           sum2,     //Sum of card values (Dealer's hand)
           card1,    //Player's first card
           card2,    //Player's second card
           card3,    //Player's third card if decided to hit.
           card4,    //Player's fourth card if decided to hit twice
           cdOne,    //Dealer's first card
           cdTwo,    //Dealer's second card
           cdTres,   //Dealer's third card if value is less than 21
           cdFour;   //Dealer's fourth card if value is less than 21
    
    string king,     //king face card
           queen,    //queen face card
           jack,     //jack face card
           ten;      //ten card
    
    static int win,  //Player wins
               loss; //Player loses
    
    int    bets[SIZE]; //4 players bets array  
    int    sum1[SIZE]; //4 players card value sums
    
    char   choices[SIZE]; //4 players choice to stand or hit array
    char   answrs[SIZE];  //4 Players answer to hit for fourth card after third
    
    //Initialize variables
    nShuff = 1;      //1 random card shuffle
    king = "KING";   //King card
    queen = "QUEEN"; //Queen card
    jack = "JACK";   //Jack card
    ten = "TEN";     //Ten card
    
    
    cout << "Welcome to the High Stakes Blackjack Table.\n";
    cout << "Would you four like to play a game? "
         << "(Type y for yes/Type n for no)\n";
    cin >> answer;
 
    //Process, map inputs to outputs
    //Answers no
    if((answer == 'n') || (answer == 'N') )
    {
        cout<<"Okay, maybe another day!\n";
        exit(1);
    }
    //Answers yes
    if((answer == 'y') || (answer == 'Y'))
    {
        cout << "Take a seat happy gambler! PLACE YOUR BETS.\n";
        cout << "Only whole bills are allowed, no coins or change.\n";
        for (int k = 0; k < SIZE; k++)
        {
            cin>>bet; 
            bets[k]=bet;
            cout << fixed << setprecision(2) << showpoint;
            cout << "Player "<<k+1<<" placed a bet of $"
                 <<static_cast<float>(bets[k])<<endl; 
            cout << "------------------------------------------------\n";
        }
        
        cout << "If you win, you get your money back - doubled!\n\n";
        cout << "The game will now begin...\n";
        
        //4 Players get first two cards
        for(int k = 0; k < SIZE; k++){
            //Calculate first card for player
            card1 = rand()%10+1;  //[1, 10]
            
            //Calculate second card for player
            card2 = rand()%10+1;  //[1, 10]
            
            //Begin to store sum
            s1 = card1 + card2;
            
            //Assign a sum to 4 players
            sum1[k] = s1;
            
            //Align player's first and second card to face number/name
            cout << "Player " << k+1 << ":\n";
            prntF1C(card1, tenVal, queen, jack, king, ten);
            prntF2C(card2, tenVal, queen, jack, king, ten);
            cout << "The value of your first two cards are " << sum1[k] << endl
                 << endl;
        }
        
        //Call calcD1C func. for dealer's first card
        calcD1C(cdOne, nShuff);
        
        //Align & print dealer's first card to name using prntD2C func.
        prntD1C(cdOne, tenVal, queen, jack, king, ten);
        cout << endl << endl;
        
        //Prompt player to stand with current hand or get a third card
        cout << "Would you like to stand, or hit again? Type(s for stand "
             <<   "or h for hit)\n\n";
        
        //Assign choice (s for stand/h for hit) to each player
        for(int x = 0; x < SIZE; x++)
        {
            cin>>choice; 
            choices[x]=choice;
            cout << "Player "<< x+1 << " decided: " << choices[x] << endl; 
            cout << "----------------------------\n";
        }
        cout << endl;
        
        //Call calcD2C func. for dealer's second card reveal
        calcD2C(cdTwo, nShuff);
                
        //Align & print dealer's second card name/number
        prntD2C(cdTwo, tenVal, queen, jack, king, ten);
        cout << endl << endl;
        
        //Call calcD3C func. for dealer's third card
        calcD3C(cdTres, nShuff);
        
        //Print dealer's third card and add to hand
        int n = 1;
        do
        {
            prntD3C(cdTres, tenVal, queen, jack, king, ten);
            cout << endl << endl;
                    
            sum2 = cdOne + cdTwo + cdTres;
                    
            n++;
        }while(n<=nShuff);
        
        //Calc dealer's fourth card
        calcD4C(cdFour, nShuff);
        
        //Player chose to stand
        for(int x = 0; x < SIZE; x++)
        {
            if(choices[x] == 's'||choices[x] == 'S')
            {
                sum2 = cdOne + cdTwo + cdTres;
                //Who wins? Func. ptResult()
                ptReslt(sum1[x], sum2, bets[x], x);
                cout << "-----------------------" << endl
                     << endl;
            }
            
            else if(choices[x] == 'h'||choices[x] == 'H')
            {
                //Calculate third card for player
                card3 = rand()%10+1;  //[1, 10]
          
                //Assign sum to player that hit
                sum1[x] += card3;
            
                //Align player's third card to face number/name
                cout << "Player " << x+1 << ":\n";
                prntF3C(card3, tenVal, queen, jack, king, ten);
                cout << "The total value of your hand is " << sum1[x] << endl
                     << endl;
                
                if(sum1[x] == 21 || sum1[x] > 21)
                {
                    sum2 = cdOne + cdTwo + cdTres;
                    //Who wins? Func. ptResult()
                    ptReslt(sum1[x], sum2, bets[x], x);
                    cout << "-----------------------" << endl;
                }
                
                //Not a blackjack 
                else if(sum1[x] < 21) 
                {   
                    cout << "The total value of your hand is "<< sum1[x] << "." 
                         << " Would you like to hit again? (y/n)\n";
            
                    cin >> answer;
                    answrs[x]=answer;
                    cout << endl << endl;
                
                    //Name dealer's card type
                    prntD4C(cdFour, tenVal, queen, jack, king, ten); 
                    
                    //Player chooses to hit for a fourth card
                    if (answrs[x]=='y'||answrs[x]=='Y')
                    {   
                        //Add dealer's fourth card to hand
                        sum2 = cdOne + cdTwo + cdTres + cdFour;  
                        
                        //Calculate fourth card for player
                        card4 = rand()%10+1;  //[1, 10]
                        //Assign sum to player that hit
                        sum1[x] += card4;
            
                        //Align player's fourth card to face number/name
                        cout << "Player " << x+1 << ":\n";
                        prntF4C(card4, tenVal, queen, jack, king, ten);
                        cout << "The value of your hand is " << sum1[x] << endl 
                             << endl;
                        
                        //Who wins? Func. ptResult()
                        ptReslt(sum1[x], sum2, bets[x], x);
                        cout << "-----------------------" << endl;
                    }
                    //Player chooses not to hit for a fourth card
                    else if (answrs[x]=='n'||answrs[x]=='N')
                    {
                        sum2 = cdOne + cdTwo + cdTres;
                        ptReslt(sum1 [x], sum2, bets[x], x);
                        cout << "-----------------------" << endl;
                    }
                }
            }
        }     
    }
    //Exit stage right
    return 0;
}

//Dealer's hand (first card)
int calcD1C(int &cdOne, int nShuff){
    for(int n=1; n<=nShuff; n++)
    {
        cdOne = rand()%10+1; //[1, 10]
    }
    return cdOne;
}

//Dealer's hand (second card)
int calcD2C(int &cdTwo, int nShuff){
    for(int n=1; n<=nShuff; n++)
    {
        cdTwo = rand()%10+1; //[1, 10]
    }
    return cdTwo;
}

//Dealer's hand (third card)
int calcD3C(int &cdTres, int nShuff){
    for(int n=1; n<=nShuff; n++)
    {
        cdTres = rand()%10+1; //[1, 10]
    }
    return cdTres;
}

//Dealer's hand (fourth card)
int calcD4C(int &cdFour, int nShuff){
    for(int n=1; n<=nShuff; n++)
    {
        cdFour = rand()%10+1; //[1, 10]
    }
    return cdFour;
}

//Print player's first card
void prntF1C(int &card1, int tenVal, string queen, string jack, string king, 
        string ten){
    //Name card type
    switch(card1){
        case 1: cout<<"Your first card is a ONE\n";break;
        case 2: cout<<"Your first card is a TWO\n";break;
        case 3: cout<<"Your first card is a THREE\n";break;
        case 4: cout<<"Your first card is a FOUR\n";break;
        case 5: cout<<"Your first card is a FIVE\n";break;
        case 6: cout<<"Your first card is a SIX\n";break;
        case 7: cout<<"Your first card is a SEVEN\n";break;
        case 8: cout<<"Your first card is an EIGHT\n";break;
        case 9: cout<<"Your first card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(card1==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<<"Your first card is a "<<queen<<endl;break;
                    case 2: cout<<"Your first card is a "<<jack<<endl;break;
                    case 3: cout<<"Your first card is a "<<king<<endl;break;
                    case 4: cout<<"Your first card is a "<<ten<<endl;break;
                }
            }break;        
    }
}

void prntF2C(int &card2, int tenVal, string queen, string jack, string king, 
        string ten){
    switch(card2){
        case 1: cout<<"Your second card is a ONE\n";break;
        case 2: cout<<"Your second card is a TWO\n";break;
        case 3: cout<<"Your second card is a THREE\n";break;
        case 4: cout<<"Your second card is a FOUR\n";break;
        case 5: cout<<"Your second card is a FIVE\n";break;
        case 6: cout<<"Your second card is a SIX\n";break;
        case 7: cout<<"Your second card is a SEVEN\n";break;
        case 8: cout<<"Your second card is an EIGHT\n";break;
        case 9: cout<<"Your second card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(card2==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<<"Your second card is a "<<queen<<endl;break;
                    case 2: cout<<"Your second card is a "<<jack<<endl;break;
                    case 3: cout<<"Your second card is a "<<king<<endl;break;
                    case 4: cout<<"Your second card is a "<<ten<<endl;break;
                }
            }break;        
    }
}

void prntF3C(int &card3, int tenVal, string queen, string jack, string king, 
        string ten){
    switch(card3){
        case 1: cout<<"Your third card is a ONE\n";break;
        case 2: cout<<"Your third card is a TWO\n";break;
        case 3: cout<<"Your third card is a THREE\n";break;
        case 4: cout<<"Your third card is a FOUR\n";break;
        case 5: cout<<"Your third card is a FIVE\n";break;
        case 6: cout<<"Your third card is a SIX\n";break;
        case 7: cout<<"Your third card is a SEVEN\n";break;
        case 8: cout<<"Your third card is an EIGHT\n";break;
        case 9: cout<<"Your third card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(card3==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<<"Your third card is a "<<queen<<endl;break;
                    case 2: cout<<"Your third card is a "<<king<<endl;break;
                    case 3: cout<<"Your third card is a "<<jack<<endl;break;
                    case 4: cout<<"Your third card is a "<<ten<<endl;break;
                }
            }break;
    }
}

void prntF4C(int &card4, int tenVal, string queen, string jack, string king, 
        string ten){
    //Name card type
    switch(card4){
        case 1: cout<<"Your fourth card is a ONE\n";break;
        case 2: cout<<"Your fourth card is a TWO\n";break;
        case 3: cout<<"Your fourth card is a THREE\n";break;
        case 4: cout<<"Your fourth card is a FOUR\n";break;
        case 5: cout<<"Your fourth card is a FIVE\n";break;
        case 6: cout<<"Your fourth card is a SIX\n";break;
        case 7: cout<<"Your fourth card is a SEVEN\n";break;
        case 8: cout<<"Your fourth card is an EIGHT\n";break;
        case 9: cout<<"Your fourth card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(card4==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<<"Your fourth card is a "<<queen<<endl;break;
                    case 2: cout<<"Your fourth card is a "<<king<<endl;break;
                    case 3: cout<<"Your fourth card is a "<<jack<<endl;break;
                    case 4: cout<<"Your fourth card is a "<<ten<<endl;break;
                }
            }break;
    }
}

//Print dealer's first card
void prntD1C(int &cdOne, int tenVal, string queen, string jack, 
        string king, string ten){
    switch(cdOne){
        case 1: cout<<"The dealer's first card is a ONE\n";break;
        case 2: cout<<"The dealer's first card is a TWO\n";break;
        case 3: cout<<"The dealer's first card is a THREE\n";break;
        case 4: cout<<"The dealer's first card is a FOUR\n";break;
        case 5: cout<<"The dealer's first card is a FIVE\n";break;
        case 6: cout<<"The dealer's first card is a SIX\n";break;
        case 7: cout<<"The dealer's first card is a SEVEN\n";break;
        case 8: cout<<"The dealer's first card is an EIGHT\n";break;
        case 9: cout<<"The dealer's first card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(cdOne==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<<"Dealer's first card is a "<<queen<<endl;break;
                    case 2: cout<<"Dealer's first card is a "<<jack<<endl;break;
                    case 3: cout<<"Dealer's first card is a "<<king<<endl;break;
                    case 4: cout<<"Dealer's first card is a "<<ten<<endl;break;
                }
            }break;
    }
}
//Print dealer's second card
void prntD2C(int &cdTwo, int tenVal, string queen, string jack, 
        string king, string ten){
    switch(cdTwo){
        case 1: cout<<"The dealer's second card is a ONE\n";break;
        case 2: cout<<"The dealer's second card is a TWO\n";break;
        case 3: cout<<"The dealer's second card is a THREE\n";break;
        case 4: cout<<"The dealer's second card is a FOUR\n";break;
        case 5: cout<<"The dealer's second card is a FIVE\n";break;
        case 6: cout<<"The dealer's second card is a SIX\n";break;
        case 7: cout<<"The dealer's second card is a SEVEN\n";break;
        case 8: cout<<"The dealer's second card is an EIGHT\n";break;
        case 9: cout<<"The dealer's second card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(cdTwo==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<<"Dealer's second card is a "<<queen<<endl;break;
                    case 2: cout<<"Dealer's second card is a "<<jack<<endl;break;
                    case 3: cout<<"Dealer's second card is a "<<king<<endl;break;
                    case 4: cout<<"Dealer's second card is a "<<ten<<endl;break;
                }
            }break;
    }
}

//Print dealers third card
void prntD3C(int &cdTres, int tenVal, string queen, string jack, 
        string king, string ten){
    //Name card type
    switch(cdTres){
        case 1: cout<<"The dealer's third card is a ONE\n";break;
        case 2: cout<<"The dealer's third card is a TWO\n";break;
        case 3: cout<<"The dealer's third card is a THREE\n";break;
        case 4: cout<<"The dealer's third card is a FOUR\n";break;
        case 5: cout<<"The dealer's third card is a FIVE\n";break;
        case 6: cout<<"The dealer's third card is a SIX\n";break;
        case 7: cout<<"The dealer's third card is a SEVEN\n";break;
        case 8: cout<<"The dealer's third card is an EIGHT\n";break;
        case 9: cout<<"The dealer's third card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(cdTres==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<< "Dealer's third card is a "<<queen<<endl;break;
                    case 2: cout<< "Dealer's third card is a "<<king<<endl;break;
                    case 3: cout<< "Dealer's third card is a "<<jack<<endl;break;
                    case 4: cout<< "Dealer's third card is a "<<ten<<endl;break;
                }
            }break;
    }
}

void prntD4C(int &cdFour, int tenVal, string queen, string jack, string king, 
        string ten){
    switch(cdFour){
        case 1: cout<<"Dealer's fourth card is a ONE\n";break;
        case 2: cout<<"Dealer's fourth card is a TWO\n";break;
        case 3: cout<<"Dealer's fourth card is a THREE\n";break;
        case 4: cout<<"Dealer's fourth card is a FOUR\n";break;
        case 5: cout<<"Dealer's fourth card is a FIVE\n";break;
        case 6: cout<<"Dealer's fourth card is a SIX\n";break;
        case 7: cout<<"Dealer's fourth card is a SEVEN\n";break;
        case 8: cout<<"Dealer's fourth card is an EIGHT\n";break;
        case 9: cout<<"Dealer's fourth card is a NINE\n";break;
        case 10: //Special case - cards with value 10
            if(cdFour==10)
            {
                tenVal = rand()%4+1;
                switch(tenVal){
                    case 1: cout<<"Dealer's fourth card is a "<<queen<<endl;break;
                    case 2: cout<<"Dealer's fourth card is a "<<king<<endl;break;
                    case 3: cout<<"Dealer's fourth card is a "<<jack<<endl;break;
                    case 4: cout<<"Dealer's fourth card is a "<<ten<<endl;break;
                }
            }break;
    }
}

void ptReslt(int sum1, int sum2, int bets, int k){
    cout << "Player " << k + 1 <<": \n";
    //Dealer wins by greater
    if(sum2 > sum1 && sum2 < 21)
    {
        cout << "You lose...\n";
        cout << "Dealer wins with value of " << sum2 <<".\n";
    }
    //Dealer bust
    else if(sum2 > 21)
    {
        cout << "Dealer has a hand with total value: " << sum2 << ".\n";
        cout << "You win! the dealer busts.\n";
        bets *= 2.0;
        cout << "Your winnings are: $" << bets << endl;
    }
    //Dealer bust
    else if(sum1 > 21)
    {
        cout << "Your hand holds the total value: " << sum1 << ".\n";
        cout << "You lose with a busted hand. Dealer wins.\n";
    }
    //Player and dealer have same hand
    else if(sum1 == sum2)
    {
        cout << "Dealer has a hand with total value: "<< sum2 << ".\n"
             << "You and the dealer have the same hand.\n"
             << "You get your money back with no damage done!\n";
    }
    //Player wins
    else if(sum1 > sum2 && sum1 < 21)
    {
        cout << "You win!\n"
             << "Dealer has a hand with total value: "<< sum2 << ".\n"
             << "Your winnings are: $" << (bets*2) << endl;
    }
    //Player got blackjack
    else if(sum1 == 21 && sum1 > sum2) 
    {
        cout << "The total value of your hand is " << sum1 << ".\n"
             << "You got BLACKJACK!\n"
             << "Dealer has a hand with total value: " << sum2 << ".\n"
             << "Because you got BLACKJACK your winnings are "
             << "increased by 1.25x.\n";
        bets = bets + (bets*BLACKJACK);
        cout << "Your winnings are: $" << bets << endl;
    }
    //Player got blackjack and dealer busts
    else if(sum1 == 21 && sum2 > 21) 
    {
        cout << "The total value of your hand is " << sum1 << ".\n"
             << "You got BLACKJACK!\n"
             << "Dealer has a hand with total value: " << sum2 << ".\n"
             << "Because you got BLACKJACK your winnings are "
             << "increased by 1.25x.\n";
        bets = bets + (bets*BLACKJACK);
        cout << "Your winnings are: $" << bets << endl;
    }
    //Dealer and Player got blackjack
    else if(sum1 == 21 && sum2 == 21)  
    {                                 
        cout << "The total value of your hand is " << sum1 << ".\n";
        cout << "You and the dealer both got Blackjack!\n"
             << "You get your money back with no damage done.\n";
    }
    //Dealer wins by blackjack
    else if(sum2 == 21 && sum1 < sum2) 
    {
        cout << "The dealer's hand is valued " << sum2 << ".\n"
             << "The dealer got BLACKJACK\n"
             << "Sorry, you lose, better luck next time.\n";
    }
}