#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

#define SUCCESS 1
#define FAILURE 0
#define AVAILABLE 2
#define UNAVAILABLE -2
#define SHELF_FULL 3

typedef int status_t;

class Book{
    private:
        string name;
        string auther;
        int avalibility;

    public:
        status_t create_book(string name, string auther, int avalibility){
            this->name = name;
            this->auther = auther;
            this->avalibility = avalibility;
            return SUCCESS;
        }
    friend class Shelf;
};

class Shelf{
    private:
        string list_category;
        Book **book_list;
        int index;
    
    public:
        Shelf(){
            this->book_list = (Book**)malloc(sizeof(Book*) * 10);
            this->index = 0;
        }
    
        status_t set_category(string category){
            this->list_category = category;
            return SUCCESS;
        }

        status_t add_book(Book* book){
            if(index < 10){
                book_list[index] = book;
                return SUCCESS;
            }
            return SHELF_FULL;
        }

        void show_books(){
            int i;
            cout << this->list_category << endl;
            for(i = 0; i <= index; i++){
                cout << book_list[i]->name << "\t" << book_list[i]->auther << endl;
            }
        }

        status_t check_availibility(string name){
            int i;
            for(i = 0; i <= index; i++){
                if(name == book_list[i]->name && book_list[i]->avalibility == 1){
                    return AVAILABLE;
                }
            }
            return UNAVAILABLE;
        }
};

int main(){
    status_t s;

    Book *book = new Book();
    
    if(book->create_book("jungle book", "mogli", 1) == SUCCESS){
        cout << "book created" << endl;
    }

    Shelf *shelf = new Shelf();
    shelf->set_category("fictional");
    if(shelf->add_book(book) == SUCCESS){
        cout << "book added to shelf" << endl;
    }

    shelf->show_books();
    if(shelf->check_availibility("jungle book") == AVAILABLE){
        cout << "available" << endl;
    }
    else {
        cout << "unavailable" << endl;
    }

    if(shelf->check_availibility("marvel") == AVAILABLE){
        cout << "available" << endl;
    }
    else {
        cout << "unavailable" << endl;
    }
}