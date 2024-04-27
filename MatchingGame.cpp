#include <iostream>
using namespace std;
char cardArray[6][7]={};
bool checkLDiagonal(char p){
    int count = 0;
    int row=0,col= 0;
    bool won = false;
    //No possible arrangements for 4 cards above 4th col and below 4th row
    //Iteration through cols
    for (size_t i = 0; i <= 3; i++)
    {
        //Iterating through rows
        for (size_t j = 5; j >= 3; j--)
        {
            row=j;//starting from downwards and going backwards
            col=i;
            for(int k = 0; k <= j; k++)
            {
                if (cardArray[row][col]==p)
                {
                    count++;
                    won=true;
                    if (count == 4 && won == true)
                    {
                        return won;
                    }
                }
                else{
                    won = false;
                    count=0;
                }
                //Also checks the possible arrangements of the cards.
                col++;//move to the diagnol element. (going backwards)
                row--;
            }
        }
    }
    return won;
}
bool checkRDiagonal(char p){
    int count = 0;
    int row=0,col= 0;
    bool won = false;
    //No possible arrangements for 4 cards above 4th col and below 4th row
    //Loop for changing the diagonal. Diagonal changes when col is incremented.
    for (size_t i = 3; i <=6; i++)
    {
        for (size_t j = 5; j >= 3; j--)
        {
            row=j;//starting from upwards and going backwards
            col=i;
            for(int k = 0; k <= j; k++)
            {
                if (cardArray[row][col]==p)
                {
                    count++;
                    won=true;
                    if (count == 4 && won == true)
                    {
                        return won;
                    }
                }
                else{
                    won = false;
                    count=0;
                }
                //Also check the possible arrangements of the cards.
                col--;//move to the diagnol element. (going backwards)
                row--;
            }
        }
    }
    return won;
}
bool checkY(char p){
    int count=0;//counter to count 4 consecutive matching cards in y-direction
    int a = 0;//helps in checking for 4 consecutive cards
    bool won = false;
    //Iterating through the cols
    for (size_t i = 0; i < 7; i++)
    {
        a=0;
        //Iterating through the rows. j<3 b/c the no. of arrangements of 4 consecutive similar cards all together in 6 rows = 3
        for (size_t j = 0; j < 3 ; j++)
        {
            a = 4+j;//1st iteration(0-3), 2nd iteration(1-4) and so on to check 4 cards
            for (size_t k = j; k < a; k++)
            {
                //counting the cards that matches the inserted card.
                if (cardArray[k][i] == p)
                {
                    count++;
                    won=true;
                    //This means the cards are consecutively placed
                    if (count == 4 && won == true)
                    {
                        return won;
                    }
                }
                else
                {
                    won = false;
                    count = 0;
                    //changes the col so we can look for 4 cards from that col onwards
                    break;
                }
            }
        }
    }
    return won;
}
bool checkX(char p){
    int count=0;//counter to count 4 consecutive matching cards in x-direction
    int a = 0;//helps in checking for 4 consecutive cards
    bool won = false;
    //Iterating through the rows
    for (size_t i = 0; i < 6; i++)
    {
        a=0;
        //Iterating through the cols. j<4 b/c the no. of arrangements of 4 consecutive similar cards all together in 7 cols = 4
        for (size_t j = 0; j < 4 ; j++)
        {
            a = 4+j;//1st iteration(0-3), 2nd iteration(1-4) and so on to check 4 cards
            for (size_t k = j; k < a; k++)
            {
                //counting the cards that matches the inserted card.
                if (cardArray[i][k] == p)
                {
                    count++;
                    won=true;
                    //This means the cards are consecutively placed
                    if (count == 4 && won == true)
                    {
                        return won;
                    }
                }
                else
                {
                    won = false;
                    count=0;
                    //changes the col so we can look for 4 cards from that col onwards
                    break;
                }
            }
        }
    }
    return won;
}
bool insert(char p,int x){
    int pos = 0;
    if (p == 'R')
    {
        cout<<"Drop a red disk at column (0-6): ";
        cin>> pos;//asking for position
    }
    else{
        cout<<"Drop a yellow disk at column (0-6): ";
        cin>> pos;
    }
    //checking the required column is filled or not to avoid overwriting on the prev card
    while (cardArray[x][pos] != 'E')
    {
        x--;
        if (x == 0 && cardArray[x][pos] != 'E')
        {
            x=5;
            cout<<"Drop the disk at diff column. column "<<pos<<" is full ";
            cin>> pos;
        }
    }
    //placing the card at the position entered by the user
    cardArray[x][pos]= p;
    //checking if the player has won the game or not.
    if(checkX(p) == true || checkY(p) == true || checkLDiagonal(p) == true || checkRDiagonal(p) == true){
        return true;
    }
    else{
        return false;
    }
}
void display(){
    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            cout<<"|"<<::cardArray[i][j]<<"|";
        }
        cout<<endl; 
    }
}
int main(){
    char p1,p2;
    //Initializing the array. E denotes "Empty".
    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            cardArray[i][j]='E';
        }
    }
    cout<<"Welcome!";
    cout<<"P1, choose color, 'R' or 'Y' ? ";
    cin>> p1;
    cout<<"P2, choose color, 'R' or 'Y' ? ";
    cin>> p2;
    bool flag1 = false;//for p1
    bool flag2 = false;// for p2
    int x=5;// a variable to stack the card given by the player. last row is the 0th row.
    while(flag1 == false && flag2==false){
        flag1=insert(p1,x);//takes the card of the player and the stack variable and returns whether the player has one or not.
        if (flag1==false)
        {
            flag2 = insert(p2,x);
        }
        if (flag1 == true || flag2 == true)
        {
            // as soon as someone wins, display the array and notify who has won.
            display();
            break;
        }
    }
    if (flag1 == true)
    {
        cout<< p1 <<" won!!";
    }
    else{
        cout<< p2 <<" won!!";
    }
    return 0;
}