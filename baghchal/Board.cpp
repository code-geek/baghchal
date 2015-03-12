#include "Board.h"

//set the co-ordinates of the points of the board
void Board::SetPoints(int initialX, int initialY)
{
    int i = 1;//start from the first point
    for (int j = 0; j < 5; j++)//vertical
    {
        for (int k = 0; k < 5; k++)//horizontal
        {
            point[i].SetX(initialX + k * incrementX);
            point[i].SetY(initialY + j * incrementY);

            if (i == 1 || i == 5 || i == 21 || i == 25)
            {
                //set the state of the sprite inside the point object to tiger.
                point[i].SetState(T);
            }

            else
            {
                point[i].SetState(N);
            }

            i++; //goes to the next point

        }//end of inner for loop
    }//end of outer for loop
}//end of function

void Board::SetIncrements(int X, int Y)
{
    incrementX = X;
    incrementY = Y;
}

void Board::Reset()
{
    for (int i = 1; i < 26; i++)
    {
        if (i == 1 || i == 5 || i == 21 || i == 25)
        {
            point[i].SetState(T);
        }

        else
        {
            point[i].SetState(N);
        }
    }
}
