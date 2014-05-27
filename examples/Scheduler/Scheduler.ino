#include "OrderedList.h"

// This example creates a task scheduler that can be used to execute tasks at specific millisecons.
// The tasks in the example are simply turning outputs pins on or off, 
// but they can be used to do anything else with few changes to the code.

// It also shows how to add new tasks dinamically by pressing a button connected to a input pin.


// During the setup some random tasks are created to change the values of pins 5, 6, 7
// When pressing a button connected to pin 8, it creates 2 new tasks to change the value of pin 7

// Create any class you want, making it extend the class Comparable
class Task: public Comparable
{
    public:
        Task( unsigned long time, byte target, byte value );
        int compare(Comparable* comparable);
        int execute();      // Execute the action specified in this task
        void printData();   // print all the data from this task (optional)
        unsigned long time; // Time to execute the task
        byte target;        // Target for the task (in this example it's a pin number)
        byte value;         // Value for the task (in this example indicates if the pin is on or off)
};

// Constructor for the Task objects
// We can add/change parameters to perform more complex tasks 
Task::Task( unsigned long time, byte target, byte value )
{
    this->time = time;
    this->target = target;
    this->value = value;
}

// The tasks are ordered chronologically, so we only use the time to compare them
int Task::compare(Comparable* comparable)
{
    Task* task = (Task*)comparable;
    return this->time - task->time;
}    

// Used to print the information on a Task object to the console
void Task::printData()
{
    Serial.print("time:");
    Serial.print(this->time);
    Serial.print("\ttarget:");
    Serial.print(this->target);
    Serial.print("\tvalue:");
    Serial.println(this->value);
}

// Executing the task is simply changing the state of a digital pin
int Task::execute()
{
    printData();  // optional
    digitalWrite(this->target, this->value);    
}

// Let's create a empty list of tasks
OrderedList* tasks = new OrderedList();
// Last time the button was clicked
unsigned long last_click;

void setup()
{
    Serial.begin(115200);
    Serial.println(F("Starting the program"));
    // Configure pins 5, 6, 7 as outputs and 8 as input
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, INPUT);
    last_click = 0;

    // Adding some random tasks to the list, because we can! :)
    // At 2000ms, set pin 5 to high
    tasks->addElement(new Task(2000, 5, 1));    
    // At 2800ms, set pin 6 to high
    tasks->addElement(new Task(2800, 6, 1));    
    // At 4000ms, set pin 5 to low
    tasks->addElement(new Task(4000, 5, 0));    
    // At 5000ms, set pin 7 to high
    tasks->addElement(new Task(5000, 7, 1));    
    // At 5200ms, set pin 7 to low
    tasks->addElement(new Task(5200, 7, 0));    
}

void loop()
{
    // If there are any tasks on the list, let's see if it's time to execute the first one
    if (tasks->count() > 0) 
    {
        Task* next_task = (Task*)tasks->getPosition(0);
        // If it's already time for this task, let's execute and remove it from the task list
        if ( millis() >= next_task->time)
        {
            next_task->execute();
            tasks->destroyElement(0);
        }
    }
    
    // If the button is pressed, cretes a task to turn pin 7 on 1 second from now,
    // and another to turn it off 2.5 seconds from now
    // This is only allowed to happen every 3 seconds
    if (digitalRead(8) && last_click + 3000 < millis())
    {
        last_click = millis();
        Serial.println(F("Adding new tasks!"));
        tasks->addElement(new Task(last_click+1000, 7, 1));    
        tasks->addElement(new Task(last_click+2500, 7, 0));            
    }
}
