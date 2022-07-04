#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<windows.h>

//defining colors
#define yellow 1
#define green 2
#define red 3
#define blue 4 
int Current_player = blue;

//defining pieces//
#define pawn 1
#define rook 2
#define bishop 3
#define knight 4
#define queen 5
#define king 6

//declaring functions
void Chess_Board(void);
int Valid_Piece_Moves(int, int);
int piece_symbols(int);
void background_color(int);

//decalring other variables used in the program
int flag = 0;
int num = -1;
int lost_player[3] = { 0 };
//orignal board
int Board_Pieces[14][14] =
{
    {9,9,9,2,4,3,5,6,3,4,2,9,9,9},
    {9,9,9,1,1,1,1,1,1,1,1,9,9,9},
    {9,9,9,0,0,0,0,0,0,0,0,9,9,9},
    {2,1,0,0,0,0,0,0,0,0,0,0,1,2},
    {4,1,0,0,0,0,0,0,0,0,0,0,1,4},
    {3,1,0,0,0,0,0,0,0,0,0,0,1,3},
    {6,1,0,0,0,0,0,0,0,0,0,0,1,5},
    {5,1,0,0,0,0,0,0,0,0,0,0,1,6},
    {3,1,0,0,0,0,0,0,0,0,0,0,1,3},
    {4,1,0,0,0,0,0,0,0,0,0,0,1,4},
    {2,1,0,0,0,0,0,0,0,0,0,0,1,2},
    {9,9,9,0,0,0,0,0,0,0,0,9,9,9},
    {9,9,9,1,1,1,1,1,1,1,1,9,9,9},
    {9,9,9,2,4,3,6,5,3,4,2,9,9,9}
};
int Player_Colors[14][14] =
{
    {9,9,9,1,1,1,1,1,1,1,1,9,9,9},
    {9,9,9,1,1,1,1,1,1,1,1,9,9,9},
    {9,9,9,0,0,0,0,0,0,0,0,9,9,9},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {4,4,0,0,0,0,0,0,0,0,0,0,2,2},
    {9,9,9,0,0,0,0,0,0,0,0,9,9,9},
    {9,9,9,3,3,3,3,3,3,3,3,9,9,9},
    {9,9,9,3,3,3,3,3,3,3,3,9,9,9}
};

int Moves_Array[14][14] = {0};

//start of program
void main()
{
   //start of program
    while (1) {
        system("@cls||clear");
        printf("\n***************************************************************\n");
        printf("\t\t--------------------------------\n");
        printf("\t\tWELCOME TO 4 PLAYER CHESS IN C !\n");
        printf("\t\t--------------------------------\n\n");
        printf("\t\tEnter what you would like to do\n");
        printf("\t\t\t1.Start playing\n");
        printf("\t\t\t2.See Rules\n");
        printf("\t\t\t3.Exit Game\n");
        printf("\n***************************************************************\n");

        int tab;
        scanf_s("%d", &tab);
        printf("\n\n");
        switch (tab) {
        case 1://game begins
            goto start;
            break; 
        
        case 2://rules
            system("@cls||clear");
            printf("\n*********************************************************************************************\n");
            printf("\t\t\t--------------------------------\n");
            printf("\t\t\t           INSTRUCTIONS\n");
            printf("\t\t\t--------------------------------\n\n");
            printf("-Player with the color yellow will start.\n");
            printf("-Players will have turns clockwise.\n");
            printf("-Each player is required to select a chess piece.\n");
            printf("-Firstly you select a x position by typing a number from 1-8 and press enter.\n");
            printf("-After that you select a y position from 1-8 and press enter\n");
            printf("-Once the piece is selected, all possible moves will be highlighted green.\n");
            printf("-If the move results in a capture it will be highlighted in red.\n");
            printf("-The player is then required to choose the horizontal and vertical position of the move\n\n");
            printf("-If the king of a player is killed, the player looses and all his pieces are removed.\n");
            printf("-The rest of the players continue playing and the last player standing wins!\n");
            printf("-The chess pieces have the following symbols:\n[pawn: %c ] [rook: %c ] [bishop: %c ] [knight: %c ] [king:%c] [queen: %c]", 231, 254, 30, 20, 227, 232);
            printf("\n*********************************************************************************************\n");
            printf("\nTo go back and start game, press any number and enter.");
            scanf_s("%d", &tab);
            break;
        case 3://game ends
            printf("Thank you for playing!");
            return 0;
            break;
        }
    }
start:
    while (1) 
    {
        system("@cls||clear");
        switch (Current_player)//printing the turn of player
        {
        case yellow: printf("\t\t\t\tYELLOW'S TURN\n\n"); break;
        case green: printf("\t\t\t\tGREEEN'S TURN\n\n"); break;
        case red: printf("\t\t\t\tRED'S TURN\n\n"); break;
        case blue: printf("\t\t\t\tBLUE'S TURN\n\n"); break;
        }
        Chess_Board();//board printed
        //player chooses which piece to move
        int a;
        printf("Choose horizontal position of piece:");
        scanf_s("%d", &a);
        int x = a - 1;
        printf("Choose vertical position of piece:");
        scanf_s("%d", &a);
        int y = a - 1;
        if (Board_Pieces[y][x] == 0 || Board_Pieces[y][x]==9)//if piece chose if off board or none
            continue;
        if (Player_Colors[y][x] != Current_player)//if piece chosen is not of the player
            continue;
        if (Valid_Piece_Moves(x, y) == 1)//no valid moves hence loop continued
        {
            for (int x_ = 0; x_ < 14; x_++) //resetting move array to zero. 
                for (int y_ = 0; y_ < 14; y_++) 
                    Moves_Array[x_][y_] = 0;
            continue;
        }
        system("@cls||clear");
        Chess_Board();// moves shown
        printf("\n");
        //inputting move
        int input[2];
        int c;
        printf("Choose move:\n");
        printf("Choose horizontal position of move:");
        scanf_s("%d", &c);
        input[0] = c - 1;
        printf("Choose vertical position of move:");
        scanf_s("%d", &c);
        input[1] = c - 1;

        if (flag == 1)//flag tells that pawn has to be promoted.
        {
            printf("\nPromote pawn enter respective numbers:\nqueen\t5\nKnight\t4\nBishop\t3\nRook\t2\n");
            int p;
            scanf_s("%d", &p);
            Board_Pieces[y][x] = p;
        }
        if ((input[0] >= 0 && input[0] <= 13) && (input[1] >= 0 && input[1] <= 13) && (Moves_Array[input[1]][input[0]] == 1 || Moves_Array[input[1]][input[0]] == 3))
        {    
            if (Board_Pieces[input[1]][input[0]] == king)//if move results in the killing of a king
            {
                int loosing_side = Player_Colors[input[1]][input[0]];//color of loosing side is seen and stored
                num++;
                lost_player[num] = loosing_side;//stored in an array to keep track of all loosing sides
                //king killed//value of new piece addedd in place of king
                Player_Colors[input[1]][input[0]] = Player_Colors[y][x];
                Board_Pieces[input[1]][input[0]] = Board_Pieces[y][x];
                Board_Pieces[y][x] = 0;
                //board and color of loosing side set to zero to remove pieces of that size
                for (int y1 = 0; y1 < 14; y1++)
                {  
                    for (int x1 = 0; x1 < 14; x1++)
                    {
                        if (Player_Colors[y1][x1] == loosing_side)
                        {
                            Board_Pieces[y1][x1] = 0;
                            Player_Colors[y1][x1] = 0;
                        }
                        else
                            continue;
                    }
                }
            }
            else //if piece killed is not the king them simple the killed piece is replaced by the piece that kills it.
            {
                Player_Colors[input[1]][input[0]] = Player_Colors[y][x];
                Board_Pieces[input[1]][input[0]] = Board_Pieces[y][x];
                Board_Pieces[y][x] = 0;
            }   
            //setting turn of next player
            switch (Current_player)
            {
            case yellow: (Current_player = green); break;
            case green: Current_player = red;   break;
            case red:   Current_player = blue;  break;
            case blue:  Current_player = yellow; break;
            }
            //in case the next player is not in the game anymore
            for (int a = 1; a < 3; a++)
            {
                if (Current_player != lost_player[0] && Current_player != lost_player[1] && Current_player != lost_player[2])
                    break;
                else
                    Current_player = (Current_player == 4) ? 1 : Current_player + 1;
            }
        }
        //if input is not within range or after killing/moving pieces the moves array is cleared
        for (int x_ = 0; x_ < 14; x_++) 
            for (int y_ = 0; y_ < 14; y_++) 
                Moves_Array[x_][y_] = 0;
        
        flag = 0;
    }
}
//function to determine valid piece moves
int Valid_Piece_Moves(int x, int y)
{
    int Current_piece = Board_Pieces[y][x];
    int Current_color = Player_Colors[y][x];
    int Cant_move = 1;
    Moves_Array[y][x] = 2;
    if (x > 14 || x < 0 || y > 14 || y < 0 )//in case piece selected is out of range
        return 1;
    else if (Current_piece == 0 || Current_piece==9)//in case pieces selected is zero or not on board
        return 1;
    if (Current_piece == rook || Current_piece == queen)//when rook or queen are selected
    {
        for (int dir = -1; dir < 2; dir += 2) 
        {
            int count = 1;
            while (1) //loop continues until broken
            {
                //positive and negative directions along x-axis.
                if (x + (count * dir) <= 13 && x + (count * dir) >= 0)
                {
                    if (Board_Pieces[y][x + (count * dir)] != 0 && Board_Pieces[y][x + (count * dir)] != 9)
                    {
                        if (Player_Colors[y][x + (count * dir)] != Current_color)
                        {
                            Moves_Array[y][x + (count * dir)] = 3;//moves array set to 3 where piece has the option to capture another piece
                            Cant_move = 0;
                        }
                        break;
                    }
                    else if (Board_Pieces[y][x + (count * dir)] == 0)
                    {
                        Moves_Array[y][x + (count * dir)] = 1;// move array set to 1 where piece has valid moves.
                        Cant_move = 0;
                    }
                    else
                        break;
                }
                else 
                    break;
                count++;
            }
            count = 1;
            while (1) 
            {
                //for positive and negative direction along y-axis.
                if (y + (count * dir) <= 13 && y + (count * dir) >= 0) 
                {
                    if (Board_Pieces[y + (count * dir)][x] != 0 && Board_Pieces[y + (count * dir)][x] != 9) {
                        if (Player_Colors[y + (count * dir)][x] != Current_color) {
                            Moves_Array[y + (count * dir)][x] = 3;
                            Cant_move = 0;
                        }
                        break;
                    }
                    else if (Board_Pieces[y + (count * dir)][x] == 0)
                    {
                        Moves_Array[y + (count * dir)][x] = 1;
                        Cant_move = 0;
                    }
                    else
                        break;
                }
                else 
                    break;
                count++;
            }
        }
    }
    if (Current_piece == bishop || Current_piece == queen)//valid moves for bishop and queen
    {
        for (int Dir_X = -1; Dir_X < 2; Dir_X += 2) //positive and negative x direction
        {
            for (int Dir_Y = -1; Dir_Y < 2; Dir_Y += 2) //poitive and negative y direction
            {
                int count = 1;
                while (1) 
                {
                    if (x + (count * Dir_X) <= 13 && x + (count * Dir_X) >= 0 && y + (count * Dir_Y) <= 13 && y + (count * Dir_Y) >= 0)//for moves within range 
                    {
                        //for capture of piece
                        if (Board_Pieces[y + (count * Dir_Y)][x + (count * Dir_X)] != 0 && Board_Pieces[y + (count * Dir_Y)][x + (count * Dir_X)] != 9)
                        {
                            if (Player_Colors[y + (count * Dir_Y)][x + (count * Dir_X)] != Current_color)
                            {
                                Moves_Array[y + (count * Dir_Y)][x + (count * Dir_X)] = 3;
                                Cant_move = 0;
                            }
                            break;
                        }
                        else if (Board_Pieces[y + (count * Dir_Y)][x + (count * Dir_X)] == 0)//for valid moves
                        {
                            Moves_Array[y + (count * Dir_Y)][x + (count * Dir_X)] = 1;
                            Cant_move = 0;
                        }
                        else 
                            break;
                    }
                    else 
                        break;
                    count++;
                }
            }
        }
    }
    if (Current_piece == pawn)//valid moves for pawn
    {
        if (Current_color == red) 
        { 
            if (y - 1 >= 0)
            {
                if (Board_Pieces[y - 1][x] == 0)
                {
                    flag = (y==1) ? 1 : 0;//to set falg to 1 if pawn reaches second last block
                    Moves_Array[y - 1][x] = 1;
                    if (y == 12 && Board_Pieces[y - 2][x] == 0)//for the very first move of pawn
                        Moves_Array[y - 2][x] = 1;
                    Cant_move = 0;
                }
                if (x + 1 <= 13 && Player_Colors[y - 1][x + 1] != red && Board_Pieces[y - 1][x + 1] != 0 && Board_Pieces[y - 1][x + 1] != 9)//killing piece front right
                {
                    Moves_Array[y - 1][x + 1] = 3;
                    Cant_move = 0;
                }
                if (x - 1 >= 0 && Player_Colors[y - 1][x - 1] != red && Board_Pieces[y - 1][x - 1] != 0 && Board_Pieces[y - 1][x - 1] != 9) //killing piece front left
                {
                    Moves_Array[y - 1][x - 1] = 3;
                    Cant_move = 0;
                }
            }
        }
        else if(Current_color==yellow)
        { 
            if (y + 1 <= 13)
            {   
                if (Board_Pieces[y + 1][x] == 0)
                {
                    flag = (y == 12) ? 1 : 0;
                    Moves_Array[y + 1][x] = 1;
                    if (y == 1 && Board_Pieces[y + 2][x] == 0)
                        Moves_Array[y + 2][x] = 1;
                    Cant_move = 0;
                }
                if (x + 1 <= 13 && Player_Colors[y + 1][x + 1] != yellow && Board_Pieces[y + 1][x + 1] != 0 && Board_Pieces[y + 1][x + 1] != 9)
                {
                    Moves_Array[y + 1][x + 1] = 3;
                    Cant_move = 0;
                }
                if (x - 1 >= 0 && Player_Colors[y + 1][x - 1] != yellow && Board_Pieces[y + 1][x - 1] != 0 && Board_Pieces[y + 1][x - 1] != 9)
                {
                    Moves_Array[y + 1][x - 1] = 3;
                    Cant_move = 0;
                }
            }
        }
        else if (Current_color == green)
        {
            if (x - 1 >= 0)
            {
                if (Board_Pieces[y][x-1] == 0)
                {
                    flag = (x == 1) ? 1 : 0;
                    Moves_Array[y][x-1] = 1;
                    if (x == 12 && Board_Pieces[y][x-2] == 0)
                        Moves_Array[y ][x-2] = 1;
                    Cant_move = 0;
                }
                if (y + 1 <= 13 && Player_Colors[y + 1][x - 1] != green && Board_Pieces[y + 1][x - 1] != 0 && Board_Pieces[y + 1][x - 1] != 9)
                {
                    Moves_Array[y + 1][x - 1] = 3;
                    Cant_move = 0;
                }
                if (y - 1 >= 0 && Player_Colors[y - 1][x - 1] != green && Board_Pieces[y - 1][x - 1] != 0 && Board_Pieces[y - 1][x - 1] != 9)
                {
                    Moves_Array[y - 1][x - 1] = 3;
                    Cant_move = 0;
                }
            }
        }
        else
        {
            if (x + 1 <= 13)
            {
                if (Board_Pieces[y][x +1] == 0)
                {
                    flag = (x == 12) ? 1 : 0;
                    Moves_Array[y][x + 1] = 1;
                    if (x == 1 && Board_Pieces[y][x+2] == 0)
                        Moves_Array[y][x + 2] = 1;
                    Cant_move = 0;
                }
                if (y + 1 <= 13 && Player_Colors[y + 1][x + 1] != blue && Board_Pieces[y + 1][x + 1] != 0 && Board_Pieces[y + 1][x + 1] != 9)
                {
                    Moves_Array[y + 1][x + 1] = 3;
                    Cant_move = 0;
                }
                if (y - 1 >= 0 && Player_Colors[y + 1][x - 1] != blue && Board_Pieces[y - 1][x + 1] != 0 && Board_Pieces[y - 1][x + 1] != 9)
                {
                    Moves_Array[y + 1][x - 1] = 3;
                    Cant_move = 0;
                }
            }
        }
    }
    if (Current_piece == knight)//has all eight moves of knight
    {
        int horizontal[8] = { 2,1,-1,-2,-2,-1,1,2 };//horizontal translations
        int vertical[8] = { -1,-2,-2,-1,1,2,2,1 };
        int current_row = y;
        int current_column = x;
        for (int move_numbr = 0; move_numbr < 8; move_numbr++)
        {
            current_row += vertical[move_numbr];//setting row and column according to move postion
            current_column += horizontal[move_numbr];
            if (current_row <=13 && current_column <= 13 && current_column >= 0 && current_row >= 0 &&Board_Pieces[current_row][current_column] != 9)
            {
                if (Board_Pieces[current_row][current_column] == 0)
                {
                    Moves_Array[current_row][current_column] = 1;
                    Cant_move = 0;
                }
                else if (Player_Colors[current_row][current_column] != Current_player)
                {
                    Moves_Array[current_row][current_column] = 3;
                    Cant_move = 0;
                }
            }
            current_row -= vertical[move_numbr];	//resetting to go back to the initial sqaure of knight to check other moves
            current_column -= horizontal[move_numbr];
        }
    }
    if (Current_piece == king) 
    {
        for (int Dir_X = -1; Dir_X < 2; Dir_X++)//positive and negative x directions set.
        {
            for (int Dir_Y = -1; Dir_Y < 2; Dir_Y++)//positive and negative y directions set. 
            {
                if (Dir_X + x <= 13 && Dir_X + x >= 0 && y + Dir_Y >= 0 && Dir_Y + y <= 14 && !(Dir_X == 0 && Dir_Y == 0)) 
                {
                    if (Board_Pieces[Dir_Y + y][Dir_X + x] != 0 && Board_Pieces[Dir_Y + y][Dir_X + x] != 9 && Player_Colors[Dir_Y + y][Dir_X + x] != Current_color)
                    {
                        Moves_Array[Dir_Y + y][Dir_X + x] = 3;
                        Cant_move = 0;
                    }
                    else if (Board_Pieces[Dir_Y + y][Dir_X + x] == 0) {
                        Moves_Array[Dir_Y + y][Dir_X + x] = 1;
                        Cant_move = 0;
                    }
                    else
                        break;
                }
            }
        }
    }
    return Cant_move;
}

void Chess_Board() 
{
    //printing top row 
    printf("     ");
    for (int y = 0; y < 14; y++) {
        if (y < 9)
            printf("%d:   ", y + 1);
        else
            printf("%d:  ", y + 1);
    }
    printf("\n\n");   
    for (int x = 0; x < 14; x++) 
    {
        //printing first column
        if (x < 9)
            printf("%d:   ", x + 1);
        else
            printf("%d:  ", x + 1);
        //printing board
        for (int y = 0; y < 14; y++) 
        {
            int piece = Board_Pieces[x][y];
            int color = Player_Colors[x][y];
            int m = Moves_Array[x][y];
            int b = Board_Pieces[x][y];
            //for each piece the following steps are followed
            background_color(m);//1. background color selected using move array.
            if (b != 0 && b != 9)
            {
                switch (color)
                {
                case blue:printf("\x1b[34m%c \x1b[0m", piece_symbols(piece)); printf("\x1b[0m  "); break;
                case green:printf("\x1b[32m%c \x1b[0m", piece_symbols(piece)); printf("\x1b[0m  "); break;
                case red:printf("\x1b[31m%c \x1b[0m", piece_symbols(piece)); printf("\x1b[0m  "); break;
                case yellow:printf("\x1b[33m%c \x1b[0m", piece_symbols(piece)); printf("\x1b[0m  "); break;
                }
            }
            else if (b == 0)
            {
                printf("--");
                printf("\x1b[0m  ");
            } 
            else
                printf("\x1b[30mxx  \x1b[0m");
            printf(" ");
        }
        printf("\n\n");
    }
}

void background_color(int m)
{ 
    switch (m)
    {
    case 3:printf("\x1b[48;5;52m");  break;
    case 1:printf("\x1b[48;5;22m");  break;
    case 2:printf("\x1b[48;5;234m");  break;
    default:printf("\x1b[40m"); break;
    }  
}
int piece_symbols(int p)
{
    char c;
    switch (p)
    {
    case pawn:c = 231; break;
    case rook:c = 254; break;
    case bishop:c = 30; break;
    case knight:c = 20; break;
    case queen:c = 227; break;
    case king:c = 232; break;
    }
    return c;
}
