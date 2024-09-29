#include<iostream>

using namespace std;



class publication
{
    public:

    string title;
    int price;

     virtual void getdata()
     {
         cin>>title;
         cin>>price;
     }

   virtual  void putdata()
   {
       cout<<title<<endl;
       cout<<price<<endl;
   }



};

class book:public publication
{
    public:

    int page_count;

    void getdata()
    {
        cin>>page_count;
    }

   void  putdata()
    {
       cout<<"Page Count:"<<page_count<<endl;
    }



};

class  tape:public publication
{public:


    int minutes;

    void getdata()
    {
       cin>>minutes;
    }


     void putdata()
    {
        cout<<"Minutes:"<<minutes<<endl;

    }

};




int main()
{


    tape p;
    book b;
    publication pub;

    publication *pu=&pub;
    pu->getdata();
    pu->putdata();

    publication  *p1=&p;

   publication  *p2=&b;

  p1->getdata();
  p1->putdata();

  p2->getdata();
  p2->putdata();



}