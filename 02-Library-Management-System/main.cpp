#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Member;

//Base Class
class LibraryItem
{
protected:
    int id;
    string title;
    string author;
    bool is_issued = false;
    vector<Member *> waitlist;

public:
    LibraryItem(int id, string title, string author) : id(id), title(title), author(author) {}
    virtual ~LibraryItem() {} // virtual destructor to prevent memory leaks

    virtual void print() const = 0;
    virtual string getType() const = 0;

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isIssued() const { return is_issued; }
    const vector<Member *>& getWaitlist() const { return waitlist; }

    void setIssued(bool status) { is_issued = status; }
    void addWaitlist(Member *member) { waitlist.push_back(member); }
    void clearWaitlist() { waitlist.clear(); }
};

// Derived Classes 
class Book : public LibraryItem
{
protected:
    int ISBN;

public:
    Book(int id, string title, string author, int a) : LibraryItem(id, title, author), ISBN(a) {}

    void print() const override
    {
        cout << "Book " << id << " | " << title << " by " << author
             << " | " << (is_issued ? "Issued" : "Available")
             << " | ISBN: " << ISBN << endl;
    }

    string getType() const override { return "Book"; }
};

class Magazine : public LibraryItem
{
protected:
    int issue_no;

public:
    Magazine(int id, string title, string author, int a) : LibraryItem(id, title, author), issue_no(a) {}

    void print() const override
    {
        cout << "Magazine " << id << " | " << title << " by " << author
             << " | " << (is_issued ? "Issued" : "Available")
             << " | Issue No: " << issue_no << endl;
    }

    string getType() const override { return "Magazine"; }
};

// Member Class
class Member
{
protected:
    int member_id;
    string name;
    vector<LibraryItem *> items;

public:
    Member(int a, string name) : member_id(a), name(name) {}

    string getName() const { return name; }
    int getId() const { return member_id; }

    void Borrow(LibraryItem *item) { items.push_back(item); }

    void Remove(LibraryItem *item)
    {
        // remove item from vector
        items.erase(remove(items.begin(), items.end(), item), items.end());
    }

    void notify(LibraryItem *item) const
    {
        if (item->isIssued())
            cout << "Sorry, " << item->getTitle() << " is not available right now." << endl;
        else
            cout << item->getTitle() << " is free now, grab it!" << endl;
    }

    void display() const
    {
        cout << "\nItems borrowed by " << name << ":" << endl;
        for (auto it : items)
            it->print();
    }
};

// Librarian Class
class Librarian
{
protected:
    vector<LibraryItem *> all_items;

public:
    ~Librarian()
    {
        // free up heap memory
        for (auto it : all_items)
            delete it;
        all_items.clear();
    }

    void addItem(LibraryItem *item) { all_items.push_back(item); }

    void IssueItem(Member &member, int id)
    {
        for (auto it : all_items)
        {
            if (it->getId() == id)
            {
                if (!it->isIssued())
                {
                    it->setIssued(true);
                    member.Borrow(it);
                    cout << it->getTitle() << " issued to " << member.getName() << endl;
                }
                else
                {
                    // item already taken, add to waitlist
                    cout << member.getName() << " ";
                    member.notify(it);
                    it->addWaitlist(&member);
                }
                break;
            }
        }
    }

    void ReturnItem(Member &member, int id)
    {
        for (auto it : all_items)
        {
            if (it->getId() == id)
            {
                it->setIssued(false);
                member.Remove(it);
                cout << it->getTitle() << " returned by " << member.getName() << endl;
                
                // notify people on the waitlist
                for (auto wait_member : it->getWaitlist())
                {
                    cout << wait_member->getName() << " ";
                    wait_member->notify(it);
                }
                it->clearWaitlist();
            }
        }
    }

    void displayAll() const
    {
        cout << "\nLibrary Inventory:" << endl;
        for (auto it : all_items)
            it->print();
    }

    void saveStatus(const string &filename) const
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (auto it : all_items)
                file << it->getType() << " | " << it->getId() << " | " << it->getTitle()
                     << " | " << it->getAuthor() << " | " << (it->isIssued() ? "Issued" : "Available") << "\n";
            file.close();
            cout << "Status saved to " << filename << endl;
        }
    }
};

int main()
{
    Librarian lb;
    
    // add items to the library
    lb.addItem(new Book(1, "Harry Potter", "J.K. Rowling", 1112));
    lb.addItem(new Book(2, "The Great Gatsby", "F. Scott Fitzgerald", 1113));
    lb.addItem(new Magazine(3, "Time", "Time Editorial", 100));

    Member c(1, "Charan"), s(2, "Sahiti");
  
    lb.IssueItem(c, 1);
    lb.IssueItem(s, 2);
    lb.IssueItem(s, 1); 
    lb.ReturnItem(c, 1);
    lb.IssueItem(s, 1);
    lb.IssueItem(c, 3);

    lb.displayAll();
    c.display();
    s.display();
    
    lb.saveStatus("library_status.txt");

    return 0;
}
