#include<iostream.h>
#include<windows.h>
#include<conio.h>
#include<process.h>

#pragma comment (lib,"./Inpout32.lib")                            //For getting access to the port.                                           
void _stdcall Out32(short PortAddress, short data);                //Function prototype for sending output on port

void camera(void *);                                            //Function prototype for camera display   

void main()
{

    cout <<"            PARALLEL PORT INTERFACING AND THREADING                "<<endl;
    cout <<"                Controlling a gun via LPT1                        "<<endl<<endl;

    int a,b,c,d,e,f,g;
    cout<<"Do you want to operate\nmanually(1)\nautomtically(2)"<<endl; //user chooses the mode of controlling gun
    cin>>a;

_beginthread(camera,0,NULL);                                //THREADING
   
    switch(a)
    {
    case 1:
        {
    int  data=0,pdata,qdata=15;                              
    while(!GetAsyncKeyState(VK_ESCAPE))                            //Loop for sending data until Escape is pressed.
    {           
        pdata=data;       
        cout <<endl<<"            PARALLEL PORT INTERFACING AND THREADING                "<<endl<<endl;
        cout <<"Controlling a gun via LPT1(manually)"<<endl;
       
        cout<<"                USER GUIDE"<<endl<<endl;
       
        cout <<"Press UP key to move UP"<<endl;            //Displaying functions of keys.
        cout <<"Press DOWN key to move DOWN"<<endl;            //for the help of user.
        cout <<"Press LEFT key to turn LEFT"<<endl;       
        cout <<"Press RIGHT key to turn RIGHT"<<endl;
        cout <<"Press SPACE key to turn SHOOT"<<endl;
        cout <<"Press F2 key to turn on/off LASER"<<endl;
        cout <<"Press F3 key to turn on/off FLASH LIGHT"<<endl;
        cout <<"Press ESCAPE key to EXIT "<<endl<<endl;

/******************************** CHECKING THE KEY STATES ********************************/
       
        if (GetAsyncKeyState(VK_UP))                       
        {                                                       
            cout << "            FORWARD\t";                       
            pdata=4+data;
        }                                                       
                       
        if (GetAsyncKeyState(VK_DOWN))                       
        {
            cout << "            BACKWARD\t";
            pdata=2+data;
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            cout << "            LEFT\t";
            pdata=1+data;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            cout << "            RIGHT\t";
            pdata=8+data;
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            cout << "            SHOOT\t";
            pdata=16+data;
        }
        if (GetAsyncKeyState(VK_F3))    //Key for Flashlight ON/OFF
        {
            if (data==0||data==64)
            data=data+32;
            else data=data-32;
        }
        if (GetAsyncKeyState(VK_F2))    //Key for Laser ON/OFF
        {
            if (data==0||data==32)
            data=data+64;
            else data=data-64;
        }

//********************************** SENDING DATA TO LPT1 **********************************//
   
        if (pdata==0||pdata==32||pdata==64||pdata==96)
        {
            Out32(0x378,(qdata+pdata));
            cout<<"Data on port is:"<<(qdata+pdata);
        }
        else
        {
            Out32(0x378,pdata);
            cout<<"Data on port is:"<<pdata;                                            //Sending data to LPT1(Parallel port).
        }

//********************************** DISPLAYING ACTIVATED PIN NUMBER **********************************//
        {
            if (pdata==1||pdata==33||pdata==65||pdata==97)
            cout << endl << "Pin no. 2 is ACTIVATED" ;
           
            if (pdata==2||pdata==34||pdata==66||pdata==98)
            cout << endl << "Pin no. 3 is ACTIVATED" ;
           
            if (pdata==4||pdata==36||pdata==68||pdata==100)
            cout << endl << "Pin no. 4 is ACTIVATED" ;
           
            if (pdata==8||pdata==40||pdata==72||pdata==104)
            cout << endl << "Pin no. 5 is ACTIVATED" ;
           
            if (pdata==16||pdata==48||pdata==80||pdata==112)
            cout << endl << "Pin no. 6 is ACTIVATED" ;
           
            if ((pdata>=32&&pdata<=48)||(pdata>=96&&pdata<=112))
            cout << endl << "FLASH LIGHT is ON \t Pin no. 7 is ACTIVATED" ;
           
            if ((pdata>=64&&pdata<=80)||(pdata>=96&&pdata<=112))
            cout << endl << "LASER is ON \t Pin no. 8 is ACTIVATED" ;
        }
        system("cls");                                                //Clear the screen.
    }
    break;
}
    case 2:                                                            //second choice for entering the angular displacements
    {    while (char m=getch()!='e')
    {        system("cls");
        Out32(0x378,0);
        cout <<endl<<"            PARALLEL PORT INTERFACING AND THREADING                "<<endl;
        cout <<"            Controlling a gun via LPT1(automatically)                "<<endl<<endl;
        cout<<"Do you want to turn on FLASHLIGHT?(y,n)"<<endl;
        char x=getch();
        if (x=='y')
        {
            Out32(0x378,32);
            e=32;
        }
        cout<<"Do you want to turn on LASER?(y,n)"<<endl;
        char z=getch();
        if (z=='y')
        {
            Out32(0x378,64);
            e=64;
        }
        if ((x=='y')&&(z=='y'))
        {
            Out32(0x378,96);
            e=96;
        }
        cout<<"Enter angular displacements (x,y)"<<endl;            // User cadtn enter positve/negtive
        cin>>b>>c;
        f=((b%5)+1);
        g=((c%5)+1);
        if (f<0)
        {
        for (d=0;d>=f;d--)
        {Out32(0x378,1+e);
        Sleep(150);}
        }
        else
        {
        for (d=0;d<=f;d++)
        {Out32(0x378,8+e);
        Sleep(150);}
        }
        if (g>0)
        {
        for (d=0;d<=g;d++)
        {Out32(0x378,4+e);
        Sleep(150);}
        }
        else
        {
        for (d=0;d>=g;d--)
        {Out32(0x378,2+e);
        Sleep(150);}
        }
        Out32(0x378,16+e);
        Sleep(200);
        Out32(0x378,0);
        cout<<"Press 'e' to end or 'enter' to continue"<<endl;
   
    }
    break;
    }
    }
}



void camera(void *)
{
    system("D:\\project\\code\\camera.lnk");            //Accessing the file for displaying camera feed
}