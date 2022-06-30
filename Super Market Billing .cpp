# include<iostream>
# include<fstream>
# include<conio.h>
# include<string.h>
# include<stdlib.h>
# include<stdio.h>
using namespace std;
char ven[51];//Global Variable        //To declare Administrator ID
//Class starts here
class product
{
    int pno;
    char name[25];
    double price,qty,discount;

  public:
    void create_product();

    void show_product();

    int retpno()
    {
        return pno;
    }
    double retprice()
    {
        return price;
    }
    double retdiscount()
    {
        return discount;
    }
    char* retname()
    {
        return name;
    }

};
//Class ends here
  void product:: create_product()
    {
        cout<<"Enter the product number of the product";
        cin>>pno;
        cout<<endl;
        cout<<"Enter name  of  the product";
        cin>>name;
        cout<<endl;
        cout<<"Enter price of the product";
        cin>>price;
        cout<<endl;
        cout<<"Enter discount percentage given on product";
        cin>>discount;
        cout<<endl;
    }
   void product::show_product()
    {
       /* cout<<"Product number:"<<endl;
        cout<<"Name of product:"<<endl;
        cout<<"Price of product:"<<endl;
        cout<<"Discount given on the product:"<<endl;*/
        cout<<"product number  \t"<<retpno()<<endl;
     cout<<"product name    \t"<<retname()<<endl;
     cout<<"price of product\t"<<retprice()<<endl;
  cout<<"discount given  \t"<<retdiscount()<<endl;
    }
fstream fp;
product pr;
//Function written in file
void write_product()
{
    fp.open("Shop.txt", ios::out | ios::app);
    pr.create_product();
    cout<<endl;
    fp.write((char * ) & pr, sizeof(product));
   //fp<<pr.retpno()<<" "<<pr.retname()<<" "<<pr.retprice()<<" "<<pr.retdiscount()<<"\n";
    fp.close();
    cout << "\n\nThe Product Has Been Created ";

}

//Function to write all records in file
void display_all()
    {
         cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.txt", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
     /*cout<<"product number  \t"<<pr.retpno()<<endl;
     cout<<"product name    \t"<<pr.retname()<<endl;
     cout<<"price of product\t"<<pr.retprice()<<endl;
  cout<<"discount given  \t"<<pr.retdiscount()<<endl;*/
        pr.show_product();
    }
       fp.close();}

//Function to display a specific product from the file
void display_specific(int n)
{
    int flag = 0;
    fp.open("Shop.txt", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() == n)
        {
            cout<<"product number\t"<<pr.retpno()<<endl;
            cout<<"product name  \t"<<pr.retname()<<endl;
            cout<<"product price \t "<<pr.retprice()<<endl;
            cout<<"discount given\t"<<pr.retdiscount()<<endl;

            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\n\nrecord  does not exist";
        }
//Function for the modification of file
void modify_product()
{
    int no, found = 0;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No. of The Product";
    cin >> no;
    fp.open("Shop.txt", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0)
    {
        if (pr.retpno() == no)
        {
            cout<<"product number\t"<<pr.retpno();
            cout<<endl;
            cout<<"product name  \t"<<pr.retname();
            cout<<endl;
            cout<<"product price \t"<<pr.retprice();
            cout<<endl;
            cout<<"discount given\t"<<pr.retdiscount();
            cout<<endl;
            cout << "\nPlease Enter The New Details of Product" << endl;
            pr.create_product();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char * ) & pr, sizeof(product));
            cout << "\n\n\t Record Updated";
            found = 1;
        }}
     fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
}
//Function to delete a record of file
void delete_product()
{
    int no;
cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.txt", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        if (pr.retpno() != no)
        {
            fp2.write((char * ) & pr, sizeof(product));
        }}
    fp2.close();
    fp.close();
    remove("Shop.txt");
    rename("Temp.txt", "Shop.txt");
    cout << "\n\n\tRecord Deleted ..";}
//Function to display all products price list
void menu()
{
    fp.open("Shop.txt", ios:: in );
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        cout << "\n\n\n Program is closing ....";

    }
   cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";
    while (fp.read((char * ) & pr, sizeof(product)))
    {
        cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
    }
    fp.close();}
void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
    cout << "\n\n******************************** INVOICE ************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount \n ";
    for (int x = 0; x <= c; x++)
    {
        fp.open("Shop.txt", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof())
        {
            if (pr.retpno() == order_arr[x])
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdiscount() / 100);
                cout << "\n" << order_arr[x] << "\t" << pr.retname() <<
                    "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }


   fp.close();}
    cout<<endl<<endl;
    cout << "\t\t\t\t\tTOTAL = " << total;}
//Introduction Function
void intro()
{
    //char ven[50];
    cout << "                                            SUPER MARKET  ";
    cout << "BILLING   ";
    cout << "PROJECT"<<endl;
    cout<<endl;
    cout << "\t\t\t\t MADE BY :     VALLAKONDA ALEKHYA  "<<endl;
    cout<<endl;
    cout << "                             INDIAN INSTITUTE OF TECHNOLOGY KHARAGPUR"<<endl<<endl;
    //cout<<"Please enter Administrator ID"<<endl;
    //cin>>ven;}
    }
//Administration  Menu Function
void admin_menu()
{


    char ch2;
    cout<<endl<<endl<<endl;
    cout << "\tADMIN MENU"<<endl<<endl;
    cout << "\t1.CREATE PRODUCT"<<endl<<endl;
    cout << "\t2.DISPLAY ALL PRODUCTS"<<endl<<endl;
    cout << "\t3.QUERY "<<endl<<endl;
    cout << "\t4.MODIFY PRODUCT"<<endl<<endl;
    cout << "\t5.DELETE PRODUCT"<<endl<<endl;
    cout << "\t6.VIEW PRODUCT MENU"<<endl<<endl;
    cout << "\t7.BACK TO MAIN MENU"<<endl<<endl;
    cout << "\tPlease Enter Your Choice (1-7) ";
    ch2 = getche();
    cout<<endl<<endl;
    switch (ch2)
    {
    case '1':
        write_product();
        //write_product1();
        break;
    case '2':
        display_all();
        break;
    case '3':
        int num;
        cout<<endl<<endl;
        cout << "\tPlease Enter The Product No. ";
        cin >> num;
        display_specific(num);
        break;
    case '4':
        modify_product();
        break;
    case '5':
        delete_product();
        break;
    case '6':
        menu();
    case '7':
        break;
    default:
        cout << "\a";
        admin_menu();
    }
}
//Main Function of  Program
int main()
{
  char ch,ch1;
    char che[30];
    intro();
        cout<<"\t\tEnter Administrator ID:          ";
    cin>>ven;
  fp.open("LoggedData.txt",ios::app);
  fp<<ven;
     fp<<endl;
    fp.close();
 cout<<"\t\tEnter password:          ";
    cin>>che;
    cout<<endl<<endl;
   if( strcmp(che,"IIT")==0)
    {
cout<<"                                      NOW YOU CAN ACCESS"<<endl<<endl<<endl<<endl<<endl;
  do
    {
        cout<<endl<<endl<<endl;
        cout << "\tMAIN MENU"<<endl<<endl;
        cout << "\t01. CUSTOMER"<<endl<<endl;
        cout << "\t02. ADMINISTRATOR"<<endl<<endl;
        cout << "\t03. EXIT"<<endl<<endl;
        cout << "\tPlease Select Your Option (1-3) ";
        ch = getche();
        cout<<endl<<endl;
        switch (ch)
        {
        case '1':
         place_order();
         fp.close();
            break;
        case '2':
            admin_menu();
            break;
        case '3':
        default:
            cout << "                       Exit Program ";
        }
    } while (ch != '3');}
    else
    {
        cout<<"                                WRONG PASSWORD ENTERED                     "<<endl;
        cout<<"                          !!!!!!ONLY ONCE YOU CAN TRY SORRY!!!!!!        "<<endl;
    }
return 0;}
//*******************************************************// END OF   PROJECT          //***************************************************************

