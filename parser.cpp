#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

int check_1(string check);
int check_2(string check);
int check_3(string check);
int check_4(string check);
int check_5(string check);
bool existcheck (string n,Shape ** shapesArray);
bool typecheck(string t);

int main() {

    string line;
    string command;

    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);



        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        if (lineStream.fail())
        {cout<<"Error: invalid command"<<endl;}
        else {


            if (command == keyWordsList[0] || command == keyWordsList[1] || command == keyWordsList[2] ||
                command == keyWordsList[3] || command == keyWordsList[4] || command == keyWordsList[5] ||
                command == keyWordsList[6])
            {
                if (command == keyWordsList[1])//User has typed in maxShapes
                {
                    int s = 0;
                    int check = check_1(line);//calls a function to check the number of arguments
                    if (check == 2) {
                        cout << "Error: too many arguments" << endl;
                    } else if (check == 1) { cout << "Error: too few arguments" << endl; }

                    else {
                        lineStream >> max_shapes;


                        if (lineStream.fail()) {
                            cout << "Error: invalid argument" << endl;// if the string after makeShapes is not a number

                        } else {
                            if (max_shapes < 0) {
                                cout << "Error: invalid value" << endl;
                            } else {


                                if (s == 0) {

                                    shapesArray = new Shape *[max_shapes];
                                    cout << "New database: max shapes is " << max_shapes << endl;
                                    for (int i = 0; i < max_shapes; i++) {
                                        shapesArray[i] = new Shape("", "", 0, 0, 0, 0);
                                    }
                                    s = s + 1;
                                } else if (s > 0) {
                                    shapeCount = 0;
                                    for (int i = 0; i < max_shapes; i++) {
                                        delete shapesArray[i];
                                        shapesArray[i] = NULL;
                                    }
                                    delete[] shapesArray;
                                    shapesArray = nullptr;

                                    shapesArray = new Shape *[max_shapes];
                                    cout << "New database: max shapes is " << max_shapes << endl;
                                    for (int i = 0; i < max_shapes; i++) {
                                        shapesArray[i] = NULL;
                                    }

                                }
                            }


                        }
                    }


                } else if (command == keyWordsList[2])//User has typed in Create
                {
                    int check = check_2(line);
                    string n;
                    string t;
                    int xloca;
                    int yloca;
                    int xvalue;
                    int yvalue;
                    if (lineStream.peek() == EOF) {
                        cout << "Error: too few arguments" << endl;
                    } else {
                        lineStream >> n;
                        if (lineStream.fail()) {
                            cout << "Error: invalid argument" << endl;
                        }
                        lineStream >> ws;
                        if (n == keyWordsList[0] || n == keyWordsList[1] || n == keyWordsList[2] ||
                            n == keyWordsList[3] || n == keyWordsList[4] || n == keyWordsList[5] ||
                            n == keyWordsList[6] || n == shapeTypesList[0] || n == shapeTypesList[1] ||
                            n == shapeTypesList[2] || n == shapeTypesList[3]) {
                            cout << "Error: invalid shape name" << endl;
                        } else if (existcheck(n, shapesArray) == false) {
                            cout << "Error: shape" << n << " exists" << endl;
                        } else if (lineStream.peek() == EOF) {
                            cout << "Error: too few arguments" << endl;
                        } else {
                            lineStream >> t;
                            lineStream >> ws;
                            if (typecheck(t) == false) {
                                cout << "Error: invalid shape type" << endl;
                            } else if (lineStream.peek() == EOF) {
                                cout << "Error: too few arguments" << endl;
                            } else {
                                lineStream >> xloca;
                                lineStream >> ws;
                                if (lineStream.fail()) {
                                    cout << "Error: invalid argument" << endl;
                                } else if (xloca < 0) { cout << "Error: invalid value" << endl; }
                                else if (lineStream.peek() == EOF) {
                                    cout << "Error: too few arguments" << endl;
                                } else {
                                    lineStream >> yloca;
                                    lineStream >> ws;
                                    if (lineStream.fail()) { cout << "Error: invalid argument" << endl; }
                                    else if (yloca < 0) {
                                        cout << "Error: invalid value" << endl;
                                    } else if (lineStream.peek() == EOF) {
                                        cout << "Error: too few arguments" << endl;
                                    } else {
                                        lineStream >> xvalue;
                                        lineStream >> ws;
                                        if (lineStream.fail()) {
                                            cout << "Error: invalid argument" << endl;
                                        } else if (xvalue < 0) {
                                            cout << "Error: invalid value" << endl;
                                        } else if (lineStream.peek() == EOF) {
                                            cout << "Error: too few arguments" << endl;
                                        } else {
                                            lineStream >> yvalue;
                                            lineStream >> ws;
                                            if (lineStream.fail()) {
                                                cout << "Error: invalid argument" << endl;
                                            } else if (yvalue < 0) {
                                                cout << "Error: invalid value" << endl;
                                            } else if (t == shapeTypesList[0] && xvalue != yvalue) {
                                                cout << "Error: invalid value" << endl;
                                            } else if (lineStream.peek() != EOF) {
                                                cout << "Error: too many arguments" << endl;
                                            } else if (shapeCount == max_shapes) {
                                                cout << "Error: shape array is full" << endl;
                                            } else {
                                                shapesArray[shapeCount]->setName(n);
                                                shapesArray[shapeCount]->setType(t);
                                                shapesArray[shapeCount]->setXlocation(xloca);
                                                shapesArray[shapeCount]->setYlocation(yloca);
                                                shapesArray[shapeCount]->setXsize(xvalue);
                                                shapesArray[shapeCount]->setYsize(yvalue);
                                                cout << "Created " << shapesArray[shapeCount]->getName() << ": "
                                                     << shapesArray[shapeCount]->getType() << " "
                                                     << shapesArray[shapeCount]->getXlocation() << " "
                                                     << shapesArray[shapeCount]->getYlocation() << " "
                                                     << shapesArray[shapeCount]->getXsize() << " "
                                                     << shapesArray[shapeCount]->getYsize() << endl;
                                                shapeCount = shapeCount + 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                }
                    //Function is called to check if arguments are exact
                    //cout<<check<<endl; debugging process

                    //Arguments are exact

                    /*if(shapeCount < max_shapes)
                    {
                        int s=0;
                        //cout<<s; debugging #2
                        string n;
                        int xloca;
                        int yloca;
                        int xvalue;
                        int yvalue;
                        string t;
                        lineStream >> n;

                        if(n=="")
                        {
                            cout<<"Error: too few arguments"<<endl;
                        }
                        else if(n == keyWordsList[0] || n == keyWordsList[1] || n == keyWordsList[2] || n == keyWordsList[3] || n == keyWordsList[4] || n == keyWordsList[5] || n == keyWordsList[6] || n == shapeTypesList[0] || n == shapeTypesList[1] || n == shapeTypesList[2] || n == shapeTypesList[3])
                        {
                            cout<<"Error: invalid shape name"<<endl;
                        }
                        else
                        {
                            for(int i=0;i<=shapeCount;i++)
                            {
                                if(n == shapesArray[i]->getName())
                                {
                                    cout<<"Error: shape "<<n<<" exists"<<endl;
                                }
                                else
                                {
                                    lineStream >> t;
                                    if(t=="")
                                    {
                                        cout<<"Error: too few arguments"<<endl;
                                    }
                                    else if(t == shapeTypesList[0] || t == shapeTypesList[1] ||t == shapeTypesList[2] ||t == shapeTypesList[3])
                                    {

                                        lineStream >> xloca;
                                        if(lineStream.eof())
                                        {
                                            cout<<xloca;
                                            cout<<"Error: too few arguments"<<endl;
                                        }
                                        else if(lineStream.fail())
                                        {
                                            cout<<"Error: invalid argument"<<endl;
                                        }
                                        else if(xloca <0)
                                        {
                                            cout<<"Error: invalid value"<<endl;
                                        }
                                        else
                                        {
                                            lineStream >> yloca;
                                            if(lineStream.eof())
                                            {
                                                cout<<"Error: too few arguments"<<endl;
                                            }
                                            else if(lineStream.fail())
                                            {
                                                cout<<"Error: invalid argument"<<endl;
                                            }
                                            else if(yloca <0)
                                            {
                                                cout<<"Error: invalid value"<<endl;
                                            }
                                            else
                                            {
                                                lineStream >> xvalue;
                                                if(lineStream.eof())
                                                {
                                                    cout<<"Error: too few arguments"<<endl;
                                                }
                                                else if(lineStream.fail())
                                                {
                                                    cout<<"Error: invalid argument"<<endl;
                                                }
                                                else if(xvalue <0)
                                                {
                                                    cout<<"Error: invalid value"<<endl;
                                                }
                                                else
                                                {
                                                    lineStream >> yvalue;
                                                    if(lineStream.eof())
                                                    {
                                                        cout<<"Error: too few arguments"<<endl;
                                                    }
                                                    else if(lineStream.fail())
                                                    {
                                                        cout<<"Error: invalid argument"<<endl;
                                                    }
                                                    else if(yvalue <0)
                                                    {
                                                        cout<<"Error: invalid value"<<endl;
                                                    }
                                                    else
                                                    {
                                                        if(shapesArray[i]->getType() == shapeTypesList[0])
                                                        {
                                                            if(xvalue == yvalue)
                                                            {
                                                                if(check == 2){cout<<"Error: too many arguments"<<endl;}
                                                                else
                                                                {
                                                                    shapesArray[shapeCount]->setName(n); shapesArray[shapeCount]->setType(t);shapesArray[shapeCount]->setXlocation(xloca); shapesArray[shapeCount]->setYlocation(yloca);shapesArray[shapeCount]->setXsize(xvalue);shapesArray[shapeCount]->setYsize(yvalue);
                                                                    cout<<"Created "<<shapesArray[shapeCount]->getName()<<": "<<shapesArray[shapeCount]->getType()<<" "<<shapesArray[shapeCount]->getXlocation()<<" "<<shapesArray[shapeCount]->getYlocation()<<" "<<shapesArray[shapeCount]->getXsize()<<" "<<shapesArray[shapeCount]->getYsize()<<endl;
                                                                    shapeCount=shapeCount+1;
                                                                }

                                                            }
                                                            else
                                                            {
                                                                cout<<"Error: invalid value"<<endl;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            if(check == 2){cout<<"Error: too many arguments"<<endl;}
                                                            else
                                                            {
                                                                shapesArray[shapeCount]->setName(n); shapesArray[shapeCount]->setType(t);shapesArray[shapeCount]->setXlocation(xloca); shapesArray[shapeCount]->setYlocation(yloca);shapesArray[shapeCount]->setXsize(xvalue);shapesArray[shapeCount]->setYsize(yvalue);
                                                                cout<<"Created "<<shapesArray[shapeCount]->getName()<<": "<<shapesArray[shapeCount]->getType()<<" "<<shapesArray[shapeCount]->getXlocation()<<" "<<shapesArray[shapeCount]->getYlocation()<<" "<<shapesArray[shapeCount]->getXsize()<<" "<<shapesArray[shapeCount]->getYsize()<<endl;
                                                                shapeCount=shapeCount+1;
                                                            }

                                                        }
                                                    }

                                                }
                                            }

                                        }
                                    }
                                    else
                                    {

                                        cout<<"Error: invalid shape type"<<endl;
                                    }

                                }
                            }

                        }
                    }*/
                    /*cout<<n; debugging #3 no problem here gives correct output
                    if(lineStream.fail())
                    {
                        cout<<"Error: too few arguments"<<endl;// float is put instead of string for eg.
                    }
                    else
                    {

                        for(int i=0;i<=3;i++)
                        {
                            if(n == shapeTypesList[i])//Checks if the name is same as a reserved word or not
                            {
                                cout << "Error: invalid shape name" << endl;
                                s = s + 1;
                            }
                        }
                        for(int i=0;i<=6;i++)
                        {
                            if(n == keyWordsList[i])//Checks if the name is same as a reserved word or not
                            {
                                cout << "Error: invalid shape name" << endl;
                                s = s + 1;
                            }
                        }


                        for(int i=0;i<=shapeCount;i++)// Checks if the name has been used before or not
                        {
                            if(n == shapesArray[i]->getName())
                            {
                                if(check == 2){cout<<"Error: too many arguments"<<endl;}
                                else if(check == 1){cout<<"Error: too few arguments"<<endl;}
                                else
                                {
                                    cout<<"Error: shape "<<n<<" exists"<<endl;
                                    s=s+1;
                                }

                            }
                        }
                        if(s==0)
                        {

                            //The name does not exist and is initalised

                            lineStream >> t;
                            if(lineStream.fail())//to check if it is not a string
                            {
                                cout<<"Error: too few arguments"<<endl;
                            }
                            else
                            {
                                if(t == shapeTypesList[0] || t == shapeTypesList[1] || t == shapeTypesList[2] || t == shapeTypesList[3])
                                {
                                    ////to check which shape was entered by the user (case sensitve)
                                    lineStream >> xloca;//passes to the next part of string which is a value by correct syntax
                                    if(lineStream.fail())
                                    {
                                        cout<<"Error: invalid argument"<<endl;
                                    }
                                    else if(lineStream.eof())
                                    {
                                        cout<<"Error: too few arguments"<<endl;
                                    }
                                    else
                                    {
                                        ////How to check which array it is being set in
                                        lineStream >> yloca;
                                        if(lineStream.fail())
                                        {
                                            cout<<"Error: invalid argument"<<endl;
                                        }
                                        else if(lineStream.eof())
                                        {
                                            cout<<"Error: too few arguments"<<endl;
                                        }
                                        else
                                        {
                                            ////How to check which array it is being set in
                                            lineStream >> xvalue;
                                            if(lineStream.fail())
                                            {
                                                cout<<"Error: invalid argument"<<endl;
                                            }
                                            else if(lineStream.eof())
                                            {
                                                cout<<"Error: too few arguments"<<endl;
                                            }
                                            else
                                            {
                                                ////How to check which array it is being set in
                                                lineStream >> yvalue;
                                                if(lineStream.fail())
                                                {
                                                    cout<<"Error: invalid argument"<<endl;
                                                }
                                                else if(lineStream.eof())
                                                {
                                                    cout<<"Error: too few arguments"<<endl;
                                                }
                                                else
                                                {
                                                    //

                                                        if(xloca < 0 || yloca < 0)
                                                        {
                                                            cout<<"Error: invalid value"<<endl;
                                                        }
                                                        else
                                                        {
                                                            if(check == 2){cout<<"Error: too many arguments"<<endl;}
                                                            else if(check == 1){cout<<"Error: too few arguments"<<endl;}
                                                            else
                                                            {
                                                            //if(shapesArray[shapeCount]->getType() == shapeTypesList[0] && shapesArray[shapeCount]->getXsize() == shapesArray[shapeCount]->getYsize())
                                                            //{
                                                            //shapesArray[shapeCount]->draw();
                                                            //}
                                                                if(t == shapeTypesList[0])
                                                                {
                                                                    if(xvalue == yvalue)
                                                                    {
                                                                     if(check == 2)
                                                                        {
                                                                            cout<<"Error: too many arguments"<<endl;
                                                                        }
                                                                        else if(check == 1)
                                                                            {cout<<"Error: too few arguments"<<endl;}
                                                                        else
                                                                        {
                                                                            shapesArray[shapeCount]->setName(n); shapesArray[shapeCount]->setType(t);shapesArray[shapeCount]->setXlocation(xloca); shapesArray[shapeCount]->setYlocation(yloca);shapesArray[shapeCount]->setXsize(xvalue);shapesArray[shapeCount]->setYsize(yvalue);
                                                                            cout<<"Created "<<shapesArray[shapeCount]->getName()<<": "<<shapesArray[shapeCount]->getType()<<" "<<shapesArray[shapeCount]->getXlocation()<<" "<<shapesArray[shapeCount]->getYlocation()<<" "<<shapesArray[shapeCount]->getXsize()<<" "<<shapesArray[shapeCount]->getYsize()<<endl;
                                                                            shapeCount=shapeCount+1;
                                                                        }

                                                                    }
                                                                    else
                                                                    {
                                                                         cout<<"Error: invalid value"<<endl;

                                                                    }
                                                                }
                                                                else
                                                                {


                                                                    if(check == 2)
                                                                    {
                                                                        cout<<"Error: too many arguments"<<endl;
                                                                    }
                                                                    else if(check == 1)
                                                                        {cout<<"Error: too few arguments"<<endl;}
                                                                    else
                                                                    {
                                                                        shapesArray[shapeCount]->setName(n); shapesArray[shapeCount]->setType(t);shapesArray[shapeCount]->setXlocation(xloca); shapesArray[shapeCount]->setYlocation(yloca);shapesArray[shapeCount]->setXsize(xvalue);shapesArray[shapeCount]->setYsize(yvalue);
                                                                        cout<<"Created "<<shapesArray[shapeCount]->getName()<<": "<<shapesArray[shapeCount]->getType()<<" "<<shapesArray[shapeCount]->getXlocation()<<" "<<shapesArray[shapeCount]->getYlocation()<<" "<<shapesArray[shapeCount]->getXsize()<<" "<<shapesArray[shapeCount]->getYsize()<<endl;

                                                                        shapeCount=shapeCount+1;
                                                                    }
                                                                }
                                                            }
                                                        }




                                                }

                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    cout<<"Error: invalid shape type"<<endl;

                                }
                            }

                        }

                    }
                }
                else
                {
                    cout<<"Error: shape array is full"<<endl;
                }
                    */


                else if (command == keyWordsList[3])//User has typed in move
                {
                    int s = 0;
                    int value;
                    int check = check_3(line);//checks for the number of arguments



                    string n;
                    lineStream >> n;   // sends the name value to n
                    if (lineStream.fail()) {
                        cout << "Error: too few arguments" << endl;
                    } else {
                        for (int i = 0; i <= 6; i++) {
                            if (n == keyWordsList[i]) {
                                cout << "Error: invalid name" << endl;
                                s = s + 1;
                            }
                        }
                        for (int i = 0; i <= shapeCount; i++)// tries to match the name with the stored names upto
                        {
                            if (n == shapesArray[i]->getName()) {
                                int temp1 = shapesArray[i]->getXlocation();//setting temporary value so that can be changed if input is faulty
                                lineStream >> value;
                                if (check == 2) { cout << "Error: too many arguments" << endl; }
                                else if (check == 1) { cout << "Error: too few arguments" << endl; }
                                else {
                                    if (lineStream.fail()) {
                                        cout << "Error: invalid argument" << endl;
                                        s = s + 1;
                                    } else {

                                        shapesArray[i]->setXlocation(value);// setting new x location
                                        lineStream >> value;// get y location value from input
                                        if (lineStream.fail()) {
                                            cout << "Error: invalid argument" << endl;// input wasn't int type
                                            shapesArray[i]->setXlocation(
                                                    temp1);// setting x location back to what it was orignally
                                            s = s + 1;
                                        } else {


                                            int temp2 = shapesArray[i]->getYlocation(); // setting temporary value so that can be changed if input is faulty
                                            shapesArray[i]->setYlocation(value);// setting new y location
                                            if (shapesArray[i]->getXlocation() < 0 ||
                                                shapesArray[i]->getYlocation() < 0)//final check of insanity
                                            {
                                                cout << "Error: invalid value"
                                                     << endl;// if any location less than 0 then it fails
                                                shapesArray[i]->setYlocation(temp2);// sets back to orignal values
                                                shapesArray[i]->setXlocation(temp1);
                                                s = s + 1;
                                            } else {
                                                cout << "Moved " << shapesArray[i]->getName() << " to "
                                                     << shapesArray[i]->getXlocation() << " "
                                                     << shapesArray[i]->getYlocation() << endl;
                                                s = s +
                                                    1;// This is done so that invalid name is not printed when one of these outputs go forward
                                            }

                                        }
                                    }
                                }

                            }
                        }
                        if (s == 0) {
                            cout << "Error: shape " << n << " not found"
                                 << endl;// However, if none go forward this will be executed as s is initialised as 0
                        }
                    }


                }
                else if (command == keyWordsList[4])//User has typed in rotate
                {
                    int check = check_4(line);


                    string n;
                    int value;
                    int s = 0;
                    lineStream >> n;//sets the string name to n
                    if (lineStream.fail()) {
                        cout << "Error: too few arguments" << endl;// the expected input wasn't the correct type
                    } else {
                        for (int i = 0; i <= 6; i++) {
                            if (n == keyWordsList[i])//Checks if the name is same as a reserved word or not
                            {
                                cout << "Error: invalid shape name" << endl;
                                s = s + 1;
                            }
                        }
                        for (int i = 0; i <= 3; i++) {
                            if (n == shapeTypesList[i])//Checks if the name is same as a reserved word or not
                            {
                                cout << "Error: invalid shape name" << endl;
                                s = s + 1;
                            }
                        }

                        for (int i = 0; i <= shapeCount; i++) {

                            if (n == shapesArray[i]->getName())// checks if name matches any from the database that's stored
                            {

                                if (check == 2) {
                                    cout << "Error: too many arguments" << endl;
                                } else if (check == 1) { cout << "Error: too few arguments" << endl; }
                                else {
                                    lineStream >> value;
                                    if (lineStream.fail()) {
                                        cout << "Error: invalid argument" << endl;//type of value sent wasn't integer type
                                        s = s + 1;
                                    } else {
                                        if (value >= 0 && value <=
                                                          360)// angle has to be between 0-360 degrees so for that if else statement
                                        {
                                            shapesArray[i]->setRotate(value);
                                            cout << "Rotated " << shapesArray[i]->getName() << " by " << value << " degrees"
                                                 << endl;
                                            s = s + 1;
                                        } else {
                                            cout << "Error: invalid value" << endl;
                                            s = s + 1;
                                        }

                                    }
                                }

                            }

                        }
                        if (s == 0) {
                            cout << "Error: shape " << n << " not found" << endl;// if the name doesn't match
                        }
                    }


                }


                else if(command == keyWordsList[5])//User has typed in draw
                {
                    int check = check_5(line);// checking for the number of small strings in the input



                    int s=0;
                    string n;
                    lineStream >> n;
                    if(lineStream.fail())//given the name to n
                    {
                        cout<<"Error: too few arguments"<<endl;// if wrong type is input
                    }
                    else
                    {



                        for(int i=1;i<=6;i++)
                        {
                            if(n == keyWordsList[i])//checks if it matches one of the reserve word
                            {
                                cout<<"Error: invalid name"<<endl;
                                s=s+1;
                            }
                        }
                        if(n == keyWordsList[0])// if it matches 'all' then it should print every data in memory
                        {

                            cout<<"Drew all shapes"<<endl;
                            for(int i=0;i<=shapeCount;i++)
                            {
                                if(shapesArray[i] == nullptr || shapesArray[i]->getName() == "")
                                {

                                }
                                else
                                {
                                    shapesArray[i]->draw();
                                    cout<<"\n";
                                }


                            }

                        }
                        else
                        {
                            for(int i=0;i<=shapeCount;i++)//matches all the data base for a name
                            {
                                if(shapesArray[i] != nullptr)
                                {



                                    if(n == shapesArray[i]->getName())// if it finds one it calls the function draw from class shape of that specific variable
                                    {
                                        if(check == 2)
                                        {
                                            cout<<"Error: too many arguments"<<endl;
                                            s=s+1;
                                        }
                                        else if(check == 1)
                                        {cout<<"Error: too few arguments"<<endl;
                                            s=s+1;}

                                        else
                                        {
                                            s=s+1;
                                            cout<<"Drew "; shapesArray[i]->draw(); cout<<"\n";
                                        }

                                    }


                                }

                            }
                            if(s==0)
                            {
                                cout<<"Error: shape "<<n<<" not found"<<endl;
                            }
                        }


                    }

                }
                else//User has typed in delete
                {
                    int check = check_5(line);



                    int s=0;
                    string n;
                    lineStream >> n;
                    if(lineStream.fail())
                    {
                        cout<<"Error: too few arguments"<<endl;
                    }
                    else
                    {

                        if(n == keyWordsList[1] || n == keyWordsList[2] || n == keyWordsList[3] || n == keyWordsList[4] || n == keyWordsList[5] || n == keyWordsList[6] || n == shapeTypesList[0] || n == shapeTypesList[1] || n == shapeTypesList[2] || n == shapeTypesList[3])
                        {
                            cout<<"Error: invalid name"<<endl;
                            s=s+1;
                        }
                        else
                        {

                            if( n == keyWordsList[0])
                            {
                                if(check == 2)
                                {cout<<"Error: too many arguments"<<endl;}
                                else if(check == 1)
                                {cout<<"Error: too few arguments"<<endl;}
                                else
                                {


                                    cout<<"Deleted: all shapes"<<endl;
                                    for(int i=0;i<=shapeCount;i++)
                                    {
                                        delete shapesArray[i];
                                        shapesArray[i]=NULL;

                                    }
                                    delete [] shapesArray;
                                    shapesArray = nullptr;
                                    s=s+1;
                                }
                            }
                            else
                            {

                                for(int i=0;i<=shapeCount;i++)
                                {



                                    if(n == shapesArray[i]->getName())
                                    {
                                        if(check == 2)
                                        {cout<<"Error: too many arguments"<<endl;}
                                        else if(check == 1)
                                        {cout<<"Error: too few arguments"<<endl;}
                                        else
                                        {
                                            cout<<"Deleted shape "<<shapesArray[i]->getName()<<endl;
                                            delete shapesArray[i];
                                            shapesArray[i] = NULL;
                                            s=s+1;
                                            shapeCount = shapeCount-1;
                                        }

                                    }


                                }
                                if(s==0)
                                {
                                    cout<<"Error: shape "<<n<<" not found"<<endl;
                                }
                            }

                        }
                    }

                }
            }
            else{cout<<"Error: invalid command"<<endl;}

        }



        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);

    }  // End input loop until EOF.

    return 0;
}
int check_1(string check)
{
    int s=5;
    string checking[3];
    stringstream lineStream (check);
    for(int i=0;i<3;i++)
    {
        lineStream >> checking[i];
        lineStream >> ws;
        if(lineStream.eof())
        {s=s-1;}
        else
        {s=s+1;}
    }
    if(s > 4)
    {return (2);}
    else if(s<4)
    {return (1);}
    else {return (0);}
}
int check_2(string check)
{
    int s=8;
    string checking[8];
    stringstream lineStream(check);
    for(int i=0;i<8;i++)
    {
        lineStream >> checking[i];
        lineStream >> ws;
        if(lineStream.eof())
        {s=s-1;}
        else
        {s=s+1;}
    }
    if(s > 12)
    {return (2);}
    else if(s<12)
    {return (1);}
    else {return (0);}
}
int check_3(string check)
{
    int s=5;
    string checking[5];
    stringstream lineStream(check);
    for(int i=0;i<5;i++)
    {
        lineStream >> checking[i];
        lineStream >> ws;
        if(lineStream.eof())
        {s=s-1;}
        else
        {s=s+1;}
    }
    if(s > 6)
    {return (2);}
    else if(s<6)
    {return (1);}
    else {return (0);}
}
int check_4(string check)
{
    int s=5;
    string checking[4];
    stringstream lineStream(check);
    for(int i=0;i<4;i++)
    {
        lineStream >> checking[i];
        lineStream >> ws;
        if(lineStream.eof())
        {s=s-1;}
        else
        {s=s+1;}
    }
    if(s > 5)
    {return (2);}
    else if(s<5)
    {return (1);}
    else {return (0);}
}
int check_5(string check)
{
    int s=5;
    string checking[3];
    stringstream lineStream(check);
    for(int i=0;i<3;i++)
    {
        lineStream >> checking[i];
        lineStream >> ws;
        if(lineStream.eof())
        {s=s-1;}
        else
        {s=s+1;}
    }
    if(s > 4)
    {return (2);}
    else if(s<4)
    {return (1);}
    else {return (0);}
}
bool existcheck (string n,Shape ** shapesArray)
{
    for (int i = 0; i <= shapeCount; i++)
    {
        if (n == shapesArray[i]->getName())
        {
            return false;
        }
    }
    return true;
}
bool typecheck(string t)
{
    
    for(int i=0;i<=3;i++)
    {
        if(t == shapeTypesList[i])
        {
            return true;
        }
    }
    return false;
}


