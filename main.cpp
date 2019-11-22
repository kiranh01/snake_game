#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#define _WIN32_WINNT 0x0A00
#include <windows.h>
#include <ctime>
#include <fstream>
#include <limits>

using namespace std;



int SNAKE_SIZE = 3;
int MAX_SNAKE_SIZE = 200;
char SNAKE_MOVEMENT='R';
ofstream fout;

typedef struct SNAKE_BODY
{
    char seg = 48;
    COORD seg_coord;

} SNAKE;


void get_console_boundry(SMALL_RECT&);
void generate_food (SMALL_RECT&, COORD&);
void get_cursor_coord(COORD&);
void put_cursor_at_coord(COORD&);

int snake_step(SNAKE []);
int cursor_correction(SNAKE ,COORD&);

int main_page();
void error_page();
void scoreboard();



/*
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}*/



int main()
{
    int choice=0;
    //ofstream fout;
    time_t starttime;
    time(&starttime);

    //cout<<"starttime:"<<starttime;
    char logfile[100];
    sprintf(logfile,"snake_logfiles/snake_logfile_%ld.log",starttime);

    //fout.open(logfile);
    fout<<"log file :["<<logfile<<"]"<<endl;





    int end_result=0;
    SNAKE s1[MAX_SNAKE_SIZE];
    for (int i=0;i<MAX_SNAKE_SIZE;i++)
    {
        s1[i].seg_coord.X=0;
        s1[i].seg_coord.Y=0;

    }
    fout<<"snake segments initialized to zero"<<endl;
    fout<<"********************* Snake Game Begins ********************"<<endl;
    system("cls");
  //  CURSOR_MOVEMENT='L';
    //cout<<"CURSOR_MOVEMENT:"<<CURSOR_MOVEMENT<<endl;


    srand(time(NULL));
    fout<<"random number generating engine seeded"<<endl;

    COORD dummyxy;

    //SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,&dummyxy);
/*
    HWND hw = GetConsoleWindow();
    ShowWindow(hw,SW_MAXIMIZE);
*/  fout<<"header page displayed"<<endl;



    while (choice!=3)
    {
        choice=main_page();
        //getch();
        if (choice==1)
        {
            system("cls");
            fout<<"Calling function snake_step"<<endl;
            end_result=snake_step(s1);
            //printf("\e[?25h");
            fout<<"value of end_result=["<<end_result<<"] returned by func snake_step"<<endl;
            if (end_result == -1)
            {
                //system("cls");
                cout<<" Game Over.....Press any key to return to main menu"<<endl;
                fout<<"Game over buddy"<<endl;
            }
            getch();
        }
        if (choice==2)
        {
            system("cls");
            cout<<"This is the scoreboard....press any key to return to main menu";
            getch();
        }
        if (choice==3)
        {
            system("cls");
            cout<<"Thank you for playing the Snake Game....press any key to exit";
            getch();
        }

    }
    //fout.close();
    return(0);
}




int main_page()
{
    int choice=0;
    char dummy;

    while( choice!=1 && choice!=2 && choice!=3 )
    {
        system("cls");
        cout<<"*********************** Welcome to Snake Game ***********************"<<endl;
        cout<<"\n\n\n\t\t\t  Main Menu"<<endl;
        cout<<endl;
        cout<<"\t\t\t1. Start Game"<<endl;
        cout<<"\t\t\t2. Scoreboard"<<endl;
        cout<<"\t\t\t3. Quit"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"Enter your option number:";
        cin>>choice;

        /*dummy=cin.get();
        if(dummy!=0 && dummy != '\n')
        {
            cout<<"\nextra data found";
            choice=0;
        }*/

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //dummy=getchar();
        //choice=dummy;

        //printf("apna choice [%c],[%d],[%d]",dummy,dummy,choice);
        //getch();
        if ( choice != 1 && choice !=2 && choice !=3 )
        {
            cout<<"\a   ! Enter the correct number from Menu";
            choice=0;
            Sleep(700);
        }
        else
        {
            if(choice==1)
                return 1;
            if(choice==2)
                return 2;
            if(choice==3)
                return 3;
        }
    }
}








void get_console_boundry(SMALL_RECT& xy_sr_win)
{
    fout<<"Entering get_console_boundry ver 1.0"<<endl;
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cbsi);
    xy_sr_win.Left = cbsi.srWindow.Left;
    xy_sr_win.Top = cbsi.srWindow.Top;
    xy_sr_win.Right = cbsi.srWindow.Right;
    xy_sr_win.Bottom = cbsi.srWindow.Bottom;

}

void generate_food (SMALL_RECT& sr_xy, COORD& xydata)
{
    fout<<"Entering generate_food ver 1.0"<<endl;
    xydata.X = (rand() % ((sr_xy.Right - sr_xy.Left)+1)) + sr_xy.Left;
    xydata.Y = (rand() % ((sr_xy.Bottom - sr_xy.Top)+1)) + sr_xy.Top;


}

void get_cursor_coord(COORD& xydata)
{
    fout<<"Entering get_cursor_coord ver 1.0"<<endl;
    CONSOLE_SCREEN_BUFFER_INFO cbinfo;
    if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cbinfo)){}
        //cout<<"\nget error";
    xydata.X=cbinfo.dwCursorPosition.X;
    xydata.Y=cbinfo.dwCursorPosition.Y;

}

void put_cursor_at_coord(COORD& xydata)
{
    fout<<"Entering put_cursor_at_coord ver 1.0"<<endl;
    if(!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),xydata)){}
        //cout<<"\nput error";

}


int cursor_correction(SNAKE snake0_xy,SMALL_RECT& sr_win)
{
    fout<<"Entering cursor_correction ver 1.0"<<endl;
    COORD xydata;
    if(SNAKE_MOVEMENT=='R')
    {
        xydata.X = (snake0_xy.seg_coord.X + 1);
        xydata.Y = snake0_xy.seg_coord.Y ;
    }
    else if(SNAKE_MOVEMENT=='L')
    {
        xydata.X = (snake0_xy.seg_coord.X - 1);
        xydata.Y = snake0_xy.seg_coord.Y ;
    }
    else if(SNAKE_MOVEMENT=='D')
    {
        xydata.X = snake0_xy.seg_coord.X;
        xydata.Y = (snake0_xy.seg_coord.Y + 1);
    }
    else if(SNAKE_MOVEMENT=='U')
    {
        xydata.X = snake0_xy.seg_coord.X;
        xydata.Y = (snake0_xy.seg_coord.Y - 1);
    }

    if ((xydata.X < sr_win.Left) ||
        (xydata.X > sr_win.Right))
            {return (-1);}
    else if ((xydata.Y < sr_win.Top) ||
             (xydata.Y > sr_win.Bottom))
            {return (-1);}
    else
    {
        put_cursor_at_coord(xydata);
        return 0;
    }

}



int snake_step(SNAKE loc_s1[])
{
    fout<<"Entering func snake_step 1.0"<<endl;

    unsigned char key;
    unsigned char key2;
    unsigned char ch='0';
    int food_flag=0;
    int snake_food_overlap=1;

    for (int i=0;i<10000;i++)
    {
        fout<<">>>>>>>> snake movement loop starts i=["<<i<<"]"<<endl;
        fout<<"snake movement direction:"<<SNAKE_MOVEMENT<<endl;

        Sleep(100);

        //------------------ Get BOUNDARY coordinates ---------//
        SMALL_RECT sr_win;
        get_console_boundry(sr_win);
        fout<<"console boundary"<<endl;
        fout<<" left_top["<<sr_win.Left<<","<<sr_win.Top<<"]"<<endl;
        fout<<"right_bot["<<sr_win.Right<<","<<sr_win.Bottom<<"]"<<endl;


        //------------------ FOOD generation -----------------//

        COORD xy_food;
        fout<<"food_flag :["<<food_flag<<"]"<<endl;

        while (food_flag == 0 && i>0)
        {
            generate_food(sr_win,xy_food);
            fout<<"rough food coordinates:X["<<xy_food.X<<"] Y["<<xy_food.Y<<"]"<<endl;
            for (int n=0;n<SNAKE_SIZE;n++)
            {
                if ((xy_food.X == loc_s1[n].seg_coord.X) &&
                    (xy_food.Y == loc_s1[n].seg_coord.Y))
                    {
                        snake_food_overlap = 1;
                        break;
                    }
                else
                {
                    snake_food_overlap = 0;
                }

            }
            if (snake_food_overlap == 0)
            {
                fout<<"final food coordinates:X["<<xy_food.X<<"] Y["<<xy_food.Y<<"]"<<endl;
                put_cursor_at_coord(xy_food);
                cout<<"0";
                food_flag = 1;
            }

        }


        //------------ FOOD out of bounds check -------//
/*
        if (((xy_food.X < sr_win.Left) || (xy_food.X > sr_win.Right)) ||
            ((xy_food.Y < sr_win.Top) || (xy_food.Y > sr_win.Bottom)))
        {
            food_flag = 0;
        }*/



        //------------ CURSOR correction/direction setting -------//
        if (i>0)
        {
            if(cursor_correction(loc_s1[0],sr_win))
                return (-1);
        }
        COORD current_cur;
        get_cursor_coord(current_cur);

        //------------------ SNAKE touching itself ---------//
        if (i>3)
        {
            for (int m=0;m<=(SNAKE_SIZE-1);m++)
            {
                if ((current_cur.X == loc_s1[m].seg_coord.X) &&
                    (current_cur.Y == loc_s1[m].seg_coord.Y))
                    return (-1);
            }
        }
        //*****************************************//
        //************* SNAKE motion **************//
        //*****************************************//
        if (i>=SNAKE_SIZE)
        {
            if ((current_cur.X != xy_food.X) ||
                (current_cur.Y != xy_food.Y))
            {
                fout<<"food not touched...so snake moves"<<endl;
                put_cursor_at_coord(loc_s1[SNAKE_SIZE-1].seg_coord);
                cout<<" ";
                put_cursor_at_coord(current_cur);
            }
            else
            {
                fout<<"food touched"<<endl;
                SNAKE_SIZE++;
                food_flag=0;
            }
        }

        fout<<"the snake moves....by printing 0"<<endl;
        cout<<"0";

        fout<<"address shifting logic begins....aka slithering"<<endl;
        for(int j=(SNAKE_SIZE-1);j>=0;j--)
        {
            if (j==0)
            {
                loc_s1[j].seg_coord.X = current_cur.X;
                loc_s1[j].seg_coord.Y = current_cur.Y;
            }
            else
            {
                loc_s1[j].seg_coord.X = loc_s1[j-1].seg_coord.X;
                loc_s1[j].seg_coord.Y = loc_s1[j-1].seg_coord.Y;
            }


        }

        fout<<"checking for any key hit"<<endl;

        if(kbhit())
        {
            key=getch();
            fout<<"key ["<<(int)key<<"]"<<endl;
            if ( key == 0 || key == 224 )
            {
                key2=getch();
                fout<<"key2 ["<<(int)key2<<"]"<<endl;

                if (key2==72 && SNAKE_MOVEMENT!='D')
                    SNAKE_MOVEMENT='U';
                else if (key2==80 && SNAKE_MOVEMENT!='U')
                    SNAKE_MOVEMENT='D';
                else if (key2==77 && SNAKE_MOVEMENT!='L')
                    SNAKE_MOVEMENT='R';
                else if (key2==75 && SNAKE_MOVEMENT!='R')
                    SNAKE_MOVEMENT='L';
            }
            else if (key==27)
                return (-1);
        }
    }
}



