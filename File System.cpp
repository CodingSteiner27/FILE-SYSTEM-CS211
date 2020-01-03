#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
using namespace std;

class ABC {
protected:
ABC(string n, string t)  : name(n), type(t) {};
string name;
const string type;

public:

virtual ~ABC(){}

virtual void display() const = 0;
void rename(string n) {name = n;} 
const string getName() const {return name;}
const string getType() const {return type;}

private:
ABC(const ABC &source);
ABC& operator= (const ABC &rhs) {return *this;}
};


// Class Folder down here
class Folder : public ABC {

protected:
vector<ABC*> vec;
Folder(const string n, const string t) : ABC(n, t) {}; 

public:
~Folder()  {
  for (int i = 0; i<vec.size(); ++i)
   if(vec[i]!=NULL) delete vec[i]; 
}

Folder(Folder &parent, string n) : ABC(n, "Folder") {
   parent.addItem(this);
 } 
 
 vector<ABC*>& items() { 
   return vec;}

  bool const addItem (ABC *ptr) {
  for (int i = 0; i < vec.size(); ++i) {
     if (vec[i]!=NULL) {
      if (ptr->getName()==vec[i]->getName()) 
        return false; 
        }
      
    }
      vec.push_back(ptr);
      return true; 
}

bool const deleteItem( const string n) {
  for (int i = 0; i < vec.size(); ++i) {
     if (vec[i] != NULL) {
      if (vec[i]->getName() == n) {
        delete vec[i];
        vec[i] = NULL;
        return true;
     }
    }
   } 
  
  cout << "Nothing to delete" << endl;
  return false;
}

 bool const moveItem(Folder &f, const string n) {
  if (this == &f) {return false;}
  for (int i = 0; i < vec.size(); ++i) {
     if (vec[i] != NULL) { 
       
       if (vec[i]->getName() == n) {
        bool answer = f.addItem(vec[i]);
        if (answer == true) {
         vec[i] = NULL;
         return true;
        }
        return false;
      }
        
      } 
    
  }
  return true;

}

virtual void display() const {
  cout << endl << "Name: " << this->getName() << " | ";
  cout << "Type: " << this->getType() << endl;
  cout << endl;
  for (int i = 0; i < vec.size(); ++i) {
    if(vec[i] != NULL) vec[i]->display();
  }
}

};

//Sorting functions down here
bool compareName(const ABC *a, const ABC *b)
{
if (a == NULL) return false;
if (b == NULL) return true;
return (a->getName() < b->getName()); 
}
bool compareType(const ABC *a, const ABC *b)
{
if (a == NULL) return false;
if (b == NULL) return true;
if (a->getType() < b->getType()) return true;
if (b->getType() < a->getType()) return false;
return (a->getName() < b->getName()); 
}
void sortByName(Folder &f) {
vector<ABC*> &v = f.items();
sort(v.begin(), v.end(), compareName); 
}
void sortByType(Folder &f) {
vector<ABC*> &v = f.items();
sort(v.begin(), v.end(), compareType); 
}
//Class File down here
class File : public ABC {  

public:
File(Folder &parent, string n) : ABC(n, "File") {
  parent.addItem(this); }
virtual void display() const {
  cout << "Item: ";
  cout << "(Name: " << this->getName() << " | ";
  cout << "Type: " << this->getType() << ")" << endl; 
  }
};
//Class Image down here
class Image : public ABC { 

public:
Image(Folder &parent, string n) : ABC(n, "Image") {
 parent.addItem(this); }
virtual void display() const {
  cout << "Item: ";
  cout << "(Name: " << this->getName() << " | ";
  cout << "Type: " << this->getType() << ")" <<endl;
  }
};
//Additional class down here
class Audio : public ABC  
{
public:
Audio(Folder &parent, string n) : ABC(n, "Audio") {
   parent.addItem(this); 
  } 
virtual void display() const { 
  cout << "Item: ";
  cout << "(Name: " << this->getName() << " | ";
  cout << "Type: " << this->getType() << ")" << endl;
  }
};


class Drive : public Folder 
{
public:
static Drive C; 
static Drive D; 
protected:
Drive(string n, string t) : Folder(n, t) {}
};

Drive Drive::C("C:", "Drive"); 
Drive Drive::D("D:", "Drive"); 


int main() { 

Drive &C = Drive::C;
Drive &D = Drive::D;
Folder *f1 = new Folder(C, "Alice"); // add "Alice" to C: drive
File *a_pdf = new File(*f1,"a.pdf"); // add "a.pdf" to folder "Alice"
Folder *f2 = new Folder(*f1, "Bob"); // add folder "Bob" to folder "Alice"
Image *b_png = new Image(*f2,"b.png"); // add "b.png" to folder "Bob"
Image *d_jpg = new Image(C,"d.jpg"); // add "d.jpg" to C: drive
Audio *loud_audio = new Audio(*f2, "loud.Audio");
// etc, put stuff in D drive

C.display(); // display names and types in C: drive
D.display(); // display names and types in D: drive
b_png->rename("BB.png"); // rename an item
f1->deleteItem("a.pdf"); // delete an item
C.moveItem(D, "d.jpg"); // move an item
sortByName(*f2);
Image *i_jpg = new Image(D,"i.jpg");
//D.addItem(d_jpg);
D.display();
// display stuff after sort
C.display();
sortByType(*f1);  
  return 0;}
