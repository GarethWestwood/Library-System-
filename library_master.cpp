#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class User
{
    protected:
        std::string first_name, last_name, password;
        int user_id;

    public:
        void create_user(std::string first_name, std::string last_name, std::string password)
        {
            this->first_name = first_name;
            this->last_name = last_name;
            this->password = password;
        }
        void print_user()
        {
            std::cout << first_name << " | " << last_name << " | " << password << std::endl;
        }
};

class Administrator: public User
{
    public:
        bool administrator_login_check(std::string first_name, std::string last_name, std::string password)
        {
            if(this->first_name == first_name && this->last_name == last_name && this->password == password)
            { 
                return true; 
            }
            return false; 
        }
}; 

class Customer: public User
{
    public:
        bool customer_login_check(std::string first_name, std::string last_name, std::string password)
        {
            if(this->first_name == first_name && this->last_name == last_name && this->password == password)
            { 
                return true; 
            }
            return false; 
        }
};



//--------------------------------------------------------------------------------------------------------------

class Book
{
    private:
        std::string author, title, copies;

    public:
        void set_book(std::string a, std::string b, std::string c)
        {
            author = a;
            title = b;
            copies = c;
        }    
        void get_book()
        {
            std::cout << author << " | " << title << " | " << copies << " Copies" << std::endl;
        }
        void book_search_print(std::string search)
        {
            if(search == author || search == title || search == copies)
            {
                get_book();
            }
        }   
        bool existing_book_check(std::string a, std::string b)
        {
            if(a == author && b == title)
            {
                std::cout << "Book already exists in database" << std::endl;
                get_book();
                return true;
            }
            return false;
        }
        bool book_search_return(std::string search)
        { 
            if(search == author || search == title)
            {
                get_book();
                return true;
            }
            return false;
        }
        void upload_book(int books_total, int book_counter) //dodgy code as it has to open and close the file on every iteration 
        { 
            std::ofstream file("MyProjects\\Library\\Library_Folder\\LibraryStorage.csv", std::ios::app);
            if(!file.is_open())
            { 
                std::cout << "LibraryStorage.csv file has not opened" << std::endl;
            }
            
            if(books_total == book_counter)
            {
                file << author << "," << title << "," << copies;
            }
            else
            {
                file << author << "," << title << "," << copies << std::endl;
            }
            file.close();
            std::cout << "book counter is " << book_counter << std::endl;
            std::cout << "book total is: " << books_total << std::endl;
        }
        
        
        void modify_author(std::string modify_option) //for tomorrow. Book is updated in class system. That data now need to be updated to the database by clearing and re-pasting. 
        {
            author = modify_option;
            get_book();
            std::cout << "Book modified" << std::endl;
        }
        void modify_title(std::string modify_option)
        {
            title = modify_option;
            get_book();
            std::cout << "Book modified" << std::endl;
        }
        void modify_copies(std::string modify_option)
        {
            copies = modify_option;
            get_book();
            std::cout << "Book modified" << std::endl;
        }
};

//DECLERATIONS
std::vector<Book> file_in_and_store();
void book_search();
char menu_function(std::string menu_option, std::string q);
void display_menu();

void customer_menu();
void add_book();
void remove_book();
void library_login();
void administrator_menu();
void modify_book();
bool yes_or_no();

//---------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------


std::vector<Administrator> administator_in()
{
    std::ifstream file ("MyProjects\\Library\\Library_Folder\\administator_users.csv"); 
    if(!file.is_open())
    { 
        std::cout << "administator_users.csv file has not opened" << std::endl;
    }
   
    std::vector<Administrator> admins;
    std::string first_name, last_name, password;
    std::string comma = ",";
    std::string line;
    int start = 0;
    
    while(file.good()) 
    {
        getline(file, line);
        int end = line.find(comma);
        for(int i = 0; i < 3; i++)
        {  
            switch(i) 
            {    
                case 0: first_name = line.substr(start, end - start); break;
                case 1: last_name = line.substr(start, end - start); break;
                case 2: password = line.substr(start, line.length()); break;
                default: std::cout << "Something went wrong, administator_in()!" << std::endl; break;
            }
            start = end + comma.length();
            end = line.find(comma, start);  
        }
        Administrator admin;
        admin.create_user(first_name, last_name, password);
        admins.push_back(admin); 
    }
    file.close();
    return admins;    
}


std::vector<Customer> customer_in()
{
    std::ifstream file ("MyProjects\\Library\\Library_Folder\\customer_users.csv"); 
    if(!file.is_open())
    { 
        std::cout << "customer_users.csv file has not opened" << std::endl;
    }
   
    std::vector<Customer> customers;
    std::string first_name, last_name, password;
    std::string comma = ",";
    std::string line;
    int start = 0;
    
    while(file.good()) 
    {
        getline(file, line);
        int end = line.find(comma);
        for(int i = 0; i < 3; i++)
        {  
            switch(i) 
            {    
                case 0: first_name = line.substr(start, end - start); break;
                case 1: last_name = line.substr(start, end - start); break;
                case 2: password = line.substr(start, line.length()); break;
                default: std::cout << "Something went wrong, customer_in()!" << std::endl; break;
            }
            start = end + comma.length();
            end = line.find(comma, start);  
        }
        Customer customer;
        customer.create_user(first_name, last_name, password);
        customers.push_back(customer); 
    }
    file.close();
    return customers;    
}


std::vector<Book> file_in_and_store()
{
    std::ifstream file ("MyProjects\\Library\\Library_Folder\\LibraryStorage.csv"); 
    if(!file.is_open())
    { 
        std::cout << "file has not opened" << std::endl;
    }
   
    std::vector<Book> library;
    std::string author, title, copies;
    std::string comma = ",";
    std::string line;
    int start = 0;
    
    while(file.good()) 
    {
        getline(file, line);
        int end = line.find(comma);
        for(int i = 0; i < 3; i++)
        {  
            switch(i) 
            {    
                case 0: author = line.substr(start, end - start); break;
                case 1: title = line.substr(start, end - start); break;
                case 2: copies = line.substr(start, line.length()); break;
                default: std::cout << "Something went wrong, file_in_and_store()!" << std::endl; break;
            }
            start = end + comma.length();
            end = line.find(comma, start);  
        }
        Book book;
        book.set_book(author, title, copies);
        library.push_back(book); 
    }
    file.close();
    return library;    
}



//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------



void library_login()
{
    std::vector<Administrator> admins = administator_in();
    std::vector<Customer> customers = customer_in();
    std::string first_name, last_name, password;
    bool login_admin = false, login_customer = false, admin_logged_in = false, customer_logged_in = false;
    
    do
    {
        admin_logged_in = false; 
        customer_logged_in = false;
        std::cout << "Welcome to the Online Library!\n" << "Please enter your login details or enter 'Q' to quit" << std::endl;
        std::cout << "First name: "; getline(std::cin >> std::ws, first_name);
        
        if(first_name == "q" || first_name == "Q")
        {
            return;
        }
        
        std::cout << "Last name: "; getline(std::cin >> std::ws, last_name);
        std::cout << "Password: " ; getline(std::cin >> std::ws, password);

        for(int i = 0; i < admins.size(); i++) //looping through admin users
        {
            login_admin = admins[i].administrator_login_check(first_name, last_name, password);
            if(login_admin)
            {
                admin_logged_in = true;
            }
        }
        for(int i = 0; i < customers.size(); i++) //looping through customer users
        {
            login_customer = customers[i].customer_login_check(first_name, last_name, password);
            if(login_customer)
            {
                customer_logged_in = true;
            }
        }
        
        // if(admin_logged_in == true && customer_logged_in == true) 
        // {                                                         
        //     customer_logged_in = false;
        // }
        
        if(admin_logged_in == true) //if for some reason admin and customer user database... 
        {                           //...both have the same user deatils then it will login in as admin
            administrator_menu();
            continue;
        }
        if(customer_logged_in == true)
        {
            customer_menu();
            continue;
        }
        else(admin_logged_in == false || customer_logged_in == false);
        {
            std::cout << "User does not exist, please try again" << std::endl;
        }             
    }while(true);  
}


//----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------


char menu_function(std::string menu_option, std::string q)
{
    int x = 1; 
    char choice;
    for(int i = 0; i < menu_option.size(); i++)
    {
        if(menu_option[i] == '|')
        {
            std::cout << std::endl; 
            std::cout << x++ << ". ";
            continue;
        }
        std::cout << menu_option[i];
    } 
    std::cout << "\nQ. " << q << std::endl;
    std::cout << "Please select an option: "; 
    std::cin >> choice;
    std::cout << std::endl;
    return toupper(choice);
}


void administrator_menu()
{
    std::cout << "Welcome to the Administrator menu\n";
    char choice; 
    do
    {
        choice = menu_function("|Search|Add a book to the database|Remove book from the database|Modify Book", "Back");
        
        switch(choice)
        {
            case '1':
                //system("cls");
                book_search();
                break;  
            case '2':
                //system("cls");
                add_book();
                break;
            case '3':
                //system("cls");
                remove_book();
                break;
            case '4':
                //system("cls");
                modify_book();
                break;
            case 'Q':
                //system("cls");
                break;    
            default:
                //system("cls");
                std::cout << "Option not available\n";
        }    
    }
    while(choice != 'Q');
}

void customer_menu()
{
    std::cout << "Welcome to the customer menu!\n";
    char choice; 
    do
    {
        choice = menu_function("|Search", "Back");
        
        switch(choice)
        {
            case '1':
                //system("cls");
                book_search();
                break;  
            case 'Q':
                //system("cls");
                break;    
            default:
                //system("cls");
                std::cout << "Option not available\n";
        }    
    }
    while(choice != 'Q'); 
}


//--------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------


void book_search() //works
{   
    std::string search;
    std::vector<Book> library = file_in_and_store();
    char choice;
    int yes_no;

    do
    {
        choice = menu_function("|Search for a book|Display full database", "Back");
        switch(choice)
        {    
            case '1':
                //system("cls");
                std::cout << "Press 'Q' to quit, otherwise enter what you would like to search for: ";
                
                getline(std::cin >> std::ws, search);
                std::cout << std::endl;
                for(int i = 0; i < library.size(); i++)
                {
                    library[i].book_search_print(search);
                }
                break;
            case '2':
                //system("cls");
                std::cout << std::endl;
                for(int i = 0; i < library.size(); i++)
                {
                    library[i].get_book();
                }
                break;
            case 'Q':
                //system("cls");
                return;    
            default:
                //system("cls");
                std::cout << "Option not available\n";    
        }    
    } while (choice != 'Q');        
}

void add_book() //works
{   
    std::ofstream file("MyProjects\\Library\\Library_Folder\\LibraryStorage.csv", std::ios::app);
    std::string author, title, copies;
    std::string answer;
    std::vector<Book> library = file_in_and_store();

    std::cout << "Enter book details" << std::endl;
    std::cout << "Author: ";
    getline(std::cin >> std::ws, author);
    std::cout << "Title: ";
    getline(std::cin >> std::ws, title);
    std::cout << "Number of Copies: ";
    getline(std::cin >> std::ws, copies);

    bool result;
    for(int i = 0; i < library.size(); i++)
    {
        result = library[i].existing_book_check(author, title);
        if(result == true)
        {
            return;
        }
    }
    
    std::cout << std::endl;
    std::cout << author << " | " << title << " | " << copies << " Copies" << std::endl;
    std::cout << "\nDo you want to save this to the database?" << "\nYes/No" << std::endl; 
    
    do
    {
        std::cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), toupper);     
        
        if(answer == "NO")
        {
            return;
        }
        else if(answer == "YES")
        {
            file << std::endl << author << "," << title << "," << copies; //store book
            return;
        }
        else(answer != "NO" || answer != "YES");
        {
            std::cout << "Input invalid. Please type YES or NO: " << std::endl;
        }
    }while(answer != "NO" || answer != "YES");
}

void remove_book()
{
    std::vector<Book> library = file_in_and_store();
    int books_total = (library.size()-1); //beacuse we are deleting a book
    int books_counter = 0;
    std::string search;
    std::string answer;
    int selected_book;
    bool match = false;
    
    do
    {        
        std::cout << "Press 'Q' to quit, otherwise enter what you would like to search for: ";
        getline(std::cin >> std::ws, search);
        std::cout << std::endl;
        
        if(search == "Q" || search == "q")
        {
            return;
        }

        for(int i = 0; i < library.size(); i++) //search through vector of books  //current search only searchs for 1 string, not 2.
        {
            match = library[i].book_search_return(search);
            if(match)
            {
                selected_book = i;
                break;
            }
        }
        if(!match)
        {
            std::cout << "Could not find book, please try again" << std::endl;  
        }
    } while(!match);        
    std::cout << "Selected book is equal to " << selected_book << std::endl;
    std::cout << library.size() << std::endl;
    //if nothing is returned then return out, or try again
    
    std::cout << "\nAre you sure you want to delete this book from the database?" << "\nYes/No" << std::endl; 
    do
    {
        std::cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), toupper);     
        
        if(answer == "NO")    //may not need returns, as while statment is true
        {
            return;
        }
        else if(answer == "YES")
        {
            std::ofstream file("MyProjects\\Library\\Library_Folder\\LibraryStorage.csv", std::ofstream::out | std::ofstream::trunc); //clears the database. Bit risky if something fails, but works for now.
            
            for(int x = 0; x < library.size(); x++) //reuploads the whole vector but selected book    //Currently doesn't wipe the old file.
            {
                if(x == selected_book)
                {
                    continue;
                }
                books_counter++;
                library[x].upload_book(books_total, books_counter); //+2 because minus one from the vecter starting at 0, and removing a book. Howver i don't think it works.
            }
            std::cout << "Book Deleted" << std::endl; 
            return;
        }
        else(answer != "NO" || answer != "YES");
        {
            std::cout << "Input invalid. Please type YES or NO: " << std::endl;
        }
    }while(answer != "NO" || answer != "YES");
}

void modify_book()
{
    std::vector<Book> library = file_in_and_store();  
    std::string search;
    bool match = false;
    int selected_book;

    do  //copied code from earlier (could be condensed)
    {        
        std::cout << "Press 'Q' to quit, otherwise enter what you would like to search for: ";
        getline(std::cin >> std::ws, search);
        std::cout << std::endl;
        
        if(search == "Q" || search == "q")
        {
            return;
        }

        for(int i = 0; i < library.size(); i++) //search through vector of books  //current search only searchs for 1 string, not 2.
        {
            match = library[i].book_search_return(search);
            if(match)
            {
                selected_book = i;
                break;
            }
        }
        if(!match)
        {
            std::cout << "Could not find book, please try again" << std::endl;  
        }
    } while(!match);        
    
   
    char choice;
    std::string modify_option;
    bool yes_no;
    do
    { 
        std::cout << "What would you like to modify" << std::endl;
        choice = menu_function("|Author|Title|Number of copies", "Back");
       
        switch(choice)
        {   
            case '1':
                //system("cls");
                std::cout << "What would you like to modify 'Author' to: ";
                getline(std::cin >> std::ws, modify_option);
                std::cout << "\nAre you sure you would like to modify 'Author' to: " << modify_option << "\nYes/No" << std::endl;
                yes_no = yes_or_no();
                if(yes_no) {
                library[selected_book].modify_author(modify_option);
                }
                return;
            case '2':
                //system("cls");
                std::cout << "What would you like to modify 'Title' to: ";
                getline(std::cin >> std::ws, modify_option);
                std::cout << "\nAre you sure you would like to modify 'Titles' to: " << modify_option << "\nYes/No" << std::endl;
                yes_no = yes_or_no();
                if(yes_no) {
                library[selected_book].modify_title(modify_option);
                }
                return;
            case '3':
                //system("cls");
                std::cout << "What would you like to modify 'Number of copies' to: ";
                getline(std::cin >> std::ws, modify_option);
                std::cout << "\nAre you sure you would like to modify 'Number of copies' to: " << modify_option << "\nYes/No" << std::endl;
                yes_no = yes_or_no();
                if(yes_no) {
                library[selected_book].modify_copies(modify_option);
                }
                return;
            case 'Q':
                //system("cls");
                return;
            default:
                //system("cls");
                std::cout << "Option not available\n";
                break;    
        }
    }while(true);
}

bool yes_or_no() //written differnetly so more compact
{ 
    bool yes_no;
    std::string answer;
    do
    {
        std::cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), toupper);
        std::cout << answer << std::endl;     
        if(answer == "NO") {
            yes_no = false; break;
        }
        if(answer == "YES"){
            yes_no = true; break;
        }
        std::cout << "Input invalid. Please type YES or NO: " << std::endl;
    }while(true);
    if(yes_no) {
        return yes_no;
    }
    return yes_no;  
}

// void rewrite_database()
// {
//     std::ofstream file("MyProjects\\Library\\Library_Folder\\LibraryStorage.csv", std::ofstream::out | std::ofstream::trunc); //clears the database. Bit risky if something fails, but works for now.
            
//     for(int x = 0; x < library.size(); x++) //reuploads the whole vector but selected book    //Currently doesn't wipe the old file.
//     {
//         if(x == selected_book)
//         {
//             continue;
//         }
//         books_counter++;
//         library[x].upload_book(books_total, books_counter); //+2 because minus one from the vecter starting at 0, and removing a book. Howver i don't think it works.
// }

//----------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------



int main()
{
    //system("cls");
    //display_menu();
    
    
    library_login();

    
    return 0;
}





// void display_menu()
// {
    
//     std::cout << "Welcome to the Online Library!" << std::endl;
//     char choice; 
//     do
//     {
//         choice = menu_function("|Customer|Administrator", "Quit");
        
//         switch(choice)
//         {
//             case '1':
//                 //system("cls");
//                 customer_menu();
//                 break;  
//             case '2':
//                 //system("cls");  
//                 administrator_menu();
//                 break;
//             case 'Q':
//                 //system("cls");
//                 std::cout << "You have left\n";
//                 break;    
//             default:
//                 //system("cls");
//                 std::cout << "Option not available\n";
//         }    
//     }
//     while(choice != 'Q'); 
// }