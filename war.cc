/***************************************************************************
 * war.cc
 * Author: Apurva Gandhi
 * Date: 02/15/2019
 * Class: CSCI 132
 * Assignment 2
 * Purpose: To play the game, "WAR!"
 * Input: User inputs number of number of cards to be dealt and asks whether
 * user wants to continue playing the game
 * Output: It prints the value and suit of the card from the deck for
 * user and computer, then prints the winner of the round.
 * keeps playing until there are no more cards in either user or player
 * types 'n', wishing to quite the game, the program will 
 *  declares the winner and status of each part.
 ***************************************************************************/

#include "stack.h"
#include "card.h"

int numCard;
char answer;
bool isOver = false; 
Stack userDraw;
Stack userWin;
Stack computerDraw;
Stack computerWin;
Stack ties;
Deck deck;
Card computerCard;
Card userCard;

/************************************************************************
 *Name: promptUser
 *Pre:
 *    None 
 *Post:
 *     Prompt the user for and read in the number of cards to be dealt.
 *Purpose:
 *     Prompts the user to enter a number of cards to dealt between 0 and 27.
 *****************************************************************************/        
void promptUser(void)
{
	cout << "How many cards in each hand (not more than 26)? ";
	cin >> numCard;
	cout << endl;

    //Checking for the input ERROR in range entered by user 
    while (numCard > 26 || numCard < 1)
    {
        if(numCard > 26)
        {
            cout << "That's too many cards. Please enter a number less than 27: ";
            cin >> numCard;
            cout << endl;
        }
        if(numCard < 1)
        {
            cout << "Please enter a number greater than zero: ";
            cin >> numCard;
            cout << endl;
        }
    }
}//end of promptUser

/****************************************************************
 *Name: declareWinner
 *Pre: 
 *     None.
 *Post:
 *    If either player runs out of cards, end the game and report the winner.
 *Purpose: To end the game 
 *****************************************************************/

void declareWinner(void)
{
    if (computerDraw.empty() && computerWin.empty())
    {
        cout << "Computer have no cards left. You win!" << endl;
        isOver = true;
    }
    if  (userDraw.empty() && userWin.empty())
    {
        cout << "You have no cards left. Computer wins!" << endl;
        isOver = true;
    }   
}//end of declareWinner

/*********************************************************************
 *Name: printGameStatus
 *Pre: 
 *     None
 *Post:
 *     reports the winner based on the total number of cards for 
 *     each player (win pile and draw pile combined).
 *Purpose:
 *      Prints the final status of an entire game and to declare winner
 *********************************************************************/

void printGameStatus(void)
{
    cout << "You have " << userDraw.size() + userWin.size() << " cards." << endl;
    cout << "The computer has " << computerDraw.size() + computerWin.size() << " cards." << endl;
    cout << "There are " << ties.size() << " in the tie pile" << endl;
    if (userDraw.size() + userWin.size() > computerDraw.size() + computerWin.size())
    {
        cout << "You Win!" << endl;
    }
    else if(userDraw.size() + userWin.size() < computerDraw.size() + computerWin.size())
    {
        cout << "Computer Wins!" << endl;
    }
    else
    {
        cout << "This is a tie. No one wins the game" << endl;
    }
}//end of printGameStatus

/****************************************************************
 *Name:deal
 *Pre:
 *    decalaration of Deck class object 
 *Post:
 *     The deal should alternate giving a card to the computer and 
 *      to the user until each has the required number of cards. 
 *Purpose:
 *      To deal the cards. 
 *****************************************************************/

void deal(void)
{
    for (int i = 0; i < numCard; i++)
    {
        computerDraw.push(deck.dealCard());
        userDraw.push(deck.dealCard());
    }
}//end of deal

/****************************************************************
 *Name: movePile
 *Pre:
 *    None 
 *Post:
 *     Turn over the win card pile when the draw card pile is emptied 
       (for computer or user). Print out the card values as they 
        are transferred.
*****************************************************************/
void movePile (Stack &win, Stack &draw, Card &card)
{
    while (!win.empty())
    {
        if(win.top(card) == underflow)
        {
            cout << "There are no cards left in win pile, Please add cards and try again" << endl;
        }
                
        if(draw.push(card) == overflow)
        {
            cout << "There is not enough space available in draw and you can not add more" << endl;
        }
        cout << "Moving ";
        card.write_card();
        cout << endl;
        if(win.pop() == underflow)
        {
            cout << "There are no cards left to remove in win, please add cards and try again" << endl;
        }
    }
}//end of movingPile

/****************************************************************
 *Name: printCurrentRoundCard
 *Pre:
 *    There must be a card in the draw stack  
 *Post:
 *    It prints out the drawn card of current round 
 *    for both players to the screen
 *****************************************************************/

void printCurrentRoundCard(Stack &draw, Card &card)
{
    if((draw.top(card)) == underflow)
    {
        cout << "There are no cards left in draw, Please add cards and try again" << endl;
    }
    card.write_card();
    cout << endl;
    if(draw.pop() == underflow)
    {
        cout << "There are no cards left to remove in draw, please add cards and try again" << endl;
    }
}//end of printCurrentRoundCard

/****************************************************************
 *Name: printRoundWinner
 *Pre:
 *    None  
 *Post:
 *    Prints the winner of the current round based on the
 *    value of drawn card for current round. In addition,
 *    It adds(pushes) both cards into the appropriate winning or
 *    tie stack.
 *****************************************************************/
void printRoundWinner(Card userCard, Card computerCard)
{
    if (userCard.get_value() > computerCard.get_value())
    {
        cout << "You win this round" << endl;
        cout << endl;
        if(userWin.push(userCard) == overflow)
        {
            cout << "There is not enough space available in user win stack and you can not push (add) more" << endl;
        }
        if( userWin.push(computerCard) == overflow)
        {
            cout << "There is not enough space available in user win stack and you can not push (add) more" << endl;
        }
    }
    else if (userCard.get_value() < computerCard.get_value())
    {
        cout << "Computer wins this round" << endl;
        cout << endl;
        if(computerWin.push(computerCard) == overflow)
        {
            cout << "There is not enough space available in computer win stack and you can not push (add) more" << endl;
        }
        if(computerWin.push(userCard) == overflow)
        {
            cout << "There is not enough space available in computer win stack and you can not push (add) more" << endl;
        }
    }
    else 
    {
        cout << "This round is a tie." << endl;
        cout << endl;

        if (ties.push(computerCard) == overflow)
        {
            cout << "There is not enough space available in tie stack and you can not push (add) more" << endl;
        }
        if(ties.push(userCard) == overflow)
        {
            cout << "There is not enough space available in tie stack and you can not push (add) more" << endl;
        }
    }
}//end of printRoundWinner

/****************************************************************
 *Name: main
 *Purpose: To play a game, WAR!
 *****************************************************************/

int main(void) 
{
	cout << "Shuffling cards." << endl;
	deck.shuffle();
   
    promptUser();
	
    //Putting each card into Players' and Computers' draw stack (Dealing the card)
	cout << "Dealing cards." << endl;
	cout << endl;
    deal();
    
    cout << "Do you want to begin playing (y/n)? ";
	cin >> answer;
    cout << endl;
   
	while (answer != 'n' && !isOver)
	{
        //Prints the card for the current round
        cout << "Your card is a ";
        printCurrentRoundCard(userDraw, userCard);
        cout << "The computer's card is a ";
        printCurrentRoundCard(computerDraw, computerCard);

        //Examine the cards and decide the winner of current round
        printRoundWinner(userCard, computerCard);
       
        //declares the winner of the game and ends the game, IF there is any winner
        declareWinner();

        /* Turn over the win card pile when the draw card pile is emptied 
           (for computer or user). Print out the card values as they are transferred.*/
        if (computerDraw.empty() || userDraw.empty())
        {
            if(!computerWin.empty())
                cout << "Moving Computer's win pile to draw pile" << endl;
            movePile(computerWin, computerDraw, computerCard);

            if (!userWin.empty())  
                cout << "Moving your win pile to draw pile" << endl;
            movePile(userWin, userDraw, userCard);   
        }
        
        //Ask the user whether he/she wants to continue 
        if (!isOver)
        {
            cout << "Do you want to continue (y/n)? ";
            cin >> answer;
            cout << endl;   
        }
    }//end of while loop
   
    cout << endl;   
    //When the game ends, prints the status of the game
    if (isOver || answer == 'n')
        printGameStatus();
    
    return 0;
}// end of main

//end of war.cc
