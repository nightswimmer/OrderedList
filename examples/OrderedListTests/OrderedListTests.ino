#include "OrderedList.h"

// Utility functions to display the free ram in the Arduino
int freeRam() 
{
    extern int __heap_start, *__brkval; 
    int v; 
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
void printRam()
{
    Serial.print(F("Free RAM:"));  Serial.println(freeRam());
}

// Create any class you want, making it extend the class Comparable
class Person: public Comparable
{
    public:
        Person( char* name, int age, long id);
        int compare(Comparable* comparable);
        void printData();
        char name[20];
        int age;
        long id;        
};

Person::Person( char* name, int age, long id)
{
    strcpy(this->name, name);
    this->age = age;
    this->id = id;
}

// Implement the method compare(), which will be used to decide how the elements will be ordered
int Person::compare(Comparable* comparable)
{
    Person* person = (Person*)comparable;
    // Using this comparation one will order the persons by name
    return strcmp(this->name, person->name);
    // This one would order them by age
//    return this->age - person->age;
    // And this one would order them by id
//    return this->id - person->id;
}    

// Used to print the information on a Person object to the console
void Person::printData()
{
    Serial.print("name:");
    Serial.print(this->name);
    Serial.print("\tage:");
    Serial.print(this->age);
    Serial.print("\tid:");
    Serial.println(this->id);
}

void setup()
{
    Serial.begin(115200);
    Serial.println(F("Starting the program"));
    
    printRam();
    // Let's create a list of students
    Serial.println(F("Creating the list"));
    OrderedList* students = new OrderedList();

    // Now add some objects to it
    // All the objects are added in the order specified in the compare() method,
    // no matter what order they are inserted to here
    Serial.println(F("Adding some objects to the list"));
    students->addElement(new Person("Tammy", 55, 3456));    
    students->addElement(new Person("Ann", 24, 423425235)); 
    students->addElement(new Person("Jones", 28, 723523523)); 
    students->addElement(new Person("Mary", 3, 34523636)); 
    students->addElement(new Person("Jane", 30, 7345355)); 

    // Let's see how they are ordered...
    Serial.println(F("Printing the elements in the compare() order"));
    for (int i=0; i<students->count(); i++) ((Person*)students->getPosition(i))->printData();
    Serial.println();
    
    // Check if a specific person exists in the list (it does, all the data is the same)
    Person* test_person;
    int pos;
    Serial.println(F("Checking if Jane exists"));        
    test_person = new Person("Jane", 30, 7345355);        
    pos = students->checkElement(test_person);
    Serial.print(F("pos:")); Serial.println(pos);
    // Make sure we delete all the objects when they are no longer necessary
    delete(test_person);
    Serial.println();
    
    // Check if another specific person exists in the list (it does, even though only the name is
    // the same, the rule in the compare() functions assume the objects are the same if the name is the same
    Serial.println(F("Checking if Tammy exists"));        
    test_person = new Person("Tammy", 0, 0);        
    pos = students->checkElement(test_person);
    Serial.print(F("pos:")); Serial.println(pos);
    // Make sure we delete all the objects when they are no longer necessary
    delete(test_person);
    Serial.println();
    
    // Check if yet another specific person exists in the list (this one doesn't)
    Serial.println(F("Checking if Spiderman exists"));        
    test_person = new Person("Spiderman", 28, 3453465);        
    pos = students->checkElement(test_person);
    Serial.print(F("pos:")); Serial.println(pos);
    // Make sure we delete all the objects when they are no longer necessary
    delete(test_person);
    Serial.println();

    // Now doing some removals
    Serial.println(F("Deleting the first element"));
    // This removes the object from the list and destroys it (deletes it from memory)
    students->destroyElement(0);
    // To remove the element from the list but not destroy the object, use
    //students->removeElement(0);
          
    // Let's see the list again...
    Serial.println(F("Printing the elements again"));
    for (int i=0; i<students->count(); i++) ((Person*)students->getPosition(i))->printData();
    Serial.println();
    
    // Now removing an element in the middle of the list
    Serial.println(F("Now deleting the second element"));
    students->destroyElement(2);
    
    // Let's see the list again...
    Serial.println(F("Printing the elements again"));
    for (int i=0; i<students->count(); i++) ((Person*)students->getPosition(i))->printData();
    Serial.println();
    
    // Deleting everything, all the memory should be free again
    Serial.println(F("Destroying the list, deleting all the elements"));
    delete(students);

    Serial.println(F("The free RAM is the same as in the beginning"));
    printRam();    
}

void loop()
{
}
