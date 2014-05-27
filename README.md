OrderedList
===========

Simple ordered list for Arduino.

Create objects and add them to one or more lists ordered any way you like. The order is set on a user defined function.

Usage example:
Create a class with any fields you need, and make sure it implements the method compare(Comparable* comparable).

    class Person: public Comparable
    {
        public:
            Person( char* name, int age, long id);
            int compare(Comparable* comparable);
            char name[20];
            int age;
            long id;        
    };
    
Implement the method compare(), which will be used to decide how the elements will be ordered.

    int Person::compare(Comparable* comparable)
    {
        Person* person = (Person*)comparable;
        // Using this comparation will order the persons by name
        return strcmp(this->name, person->name);
        // To order them by age, you would do use the next line instead of the previous one
        // return this->age - person->age;
    }
    

Create your list and add any elements you like.

    OrderedList* students = new OrderedList();
    students->addElement(new Person("Jones", 28, 7233)); 
    students->addElement(new Person("Tim", 17, 2113)); 
    students->addElement(new Person("Jane", 32, 336)); 
    students->addElement(new Person("Ann", 24, 4235)); 

Access the data that is ordered automatically
The following line would print all the names in order:

    for (int i=0; i<students->count(); i++) 
    {
        Serial.println(((Person*)students->getPosition(i))->name);
    }

Check the example that comes with the library to see this code in action.

Version history
===========
1.0 released in 2014-05-27
