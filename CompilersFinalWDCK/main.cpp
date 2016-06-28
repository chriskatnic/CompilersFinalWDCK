/*
 / Christopher Katnic
 / Wyatt Dorn
 / CPSC 323 - Final Project
 / Ray Ahmadnia
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <locale>					//locale includes isalpha() function
#include <sstream>					//sstream includes istringstream class
#include <iterator>
using namespace std;

void cleanup();
void start();
vector<string> getvectorfromfile();
bool startcheck(vector<string>);
bool checknext(vector<string>);
bool checknext2(vector<string>);
bool checknext3(vector<string>);
bool checknext4(vector<string>, vector<string>);
bool checknext5(vector<string>, vector<string>);
bool checknext6(vector<string>, vector<string>);
bool checknext7(vector<string>, vector<string>);
bool checknext8(vector<string>, vector<string>);
bool checkiddigit(char);
bool checkexpression(vector<string>, vector<string>);
void highleveltranslate();

int main()
{
    cleanup();
    start();
    return 0;
    
    /* - - This segment of code in each function checks to make sure that the inputted program
     is complete - - - -
     input.erase(input.begin());
     if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
     */
}

void start()
{
    //get program from text and parse into space delimited vector
    vector<string> input = getvectorfromfile();
    
    //Program follows a recursive function to compile
    bool accept;
    accept = startcheck(input);
    
    //if program compiles, translate and output to .txt
    if(accept)
        highleveltranslate();
    
}

//Open file containing program to be compiled
vector<string> getvectorfromfile()
{
    ifstream infile;
    infile.open("newdata.txt");
    vector<string> myvector;
    string temp;
    //store all space delimited tokens to a vector array to be checked in main function
    while(infile >> temp)
        myvector.push_back(temp);
    infile.close();
    return myvector;
}

//Begin recursive function to compile - each function is the next step in compiling
//program will return the boolean value of the next function, which corresponds to each
//necessary part of the program. Each segment will check for necessary syntax and reserved words
bool startcheck(vector<string> input)
{
    if(input.front() == "PROGRAM")
    {
        //if the first word in the program is PROGRAM, the compiler removes it from the stack and continues
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        return checknext(input);
    }
    else
    {
        cout << "\nCompile failed: PROGRAM missing or misspelled\n";
        return false;
    }
    
}

//this function will check to make sure that the title of the program has proper syntax
bool checknext(vector<string> input)
{
    string temp = input.front();
    
    if(temp[0] == 'a' || temp[0] == 'b' || temp[0] == 'c' || temp[0] == 'd' || temp[0] == 'e')
    {
        
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        return checknext2(input);
    }
    
    else
    {
        cout << "\nCompile failed: Improper identifier found after PROGRAM\n";
        return false;
    }
}

//this function will check for a semicolon
bool checknext2(vector<string> input)
{
    string temp = input.front();
    
    
    if(temp[0] == ';')
    {
        
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        return checknext3(input);
    }
    
    else
    {
        cout << "\nCompile failed: Did not find ';' after identifier\n";
        return false;
    }
}

//this function will check for the reserved word VAR
bool checknext3(vector<string> input)
{
    if(input.front() == "VAR")
    {
        //good so far, keep checking
        input.erase(input.begin());
        vector<string> newstack;
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        return checknext4(input, newstack);
    }
    else
    {
        cout << "\nCompile failed: VAR missing or misspelled\n";
        return false;
    }
}

//this function checks for the declaration list, and will repeat after every comma to check for a valid list
bool checknext4(vector<string> input, vector<string> identifiers)
{
    string temp = input.front();
    
    if(temp[0] == 'a' || temp[0] == 'b' || temp[0] == 'c' || temp[0] == 'd' || temp[0] == 'e')
    {
        for(int i = 0; i < temp.length(); i++)
            if(checkiddigit(temp[i]) == false) { cout << "Compile failed: Improper identifier\n"; return false; }
        //we know it's an identifier, check for comma. if next is a comma, come back to checknext4
        //if next is a :, move onward to the type
        //store the identifier in a new stack
        identifiers.push_back(input.front());
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        if(input.front() == ",")
        {
            input.erase(input.begin());
            if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
            return checknext4(input, identifiers);
        }
        else if(input.front() == ":")
        {
            input.erase(input.begin());
            if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
            return checknext5(input, identifiers);
        }
        else
        {
            cout << "\nCompile failed: Declaration list syntax invalid!\n";
            return false;
        }
    }
    else
    {
        cout << "\nCompile failed: Declaration list syntax invalid!\n";
        return false;
    }
    
    
    
    
}
//check for the reserved word INTEGER
bool checknext5 (vector<string> input, vector<string> identifiers)
{
    if(input.front() == "INTEGER")
    {
        //good so far, keep checking
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        return checknext6(input, identifiers);
    }
    else
    {
        cout << "\nCompile failed: INTEGER missing or misspelled\n";
        return false;
    }
    
}

//check for semicolon
bool checknext6 (vector<string> input, vector<string> identifiers)
{
    if(input.front() == ";")
    {
        //good so far, keep checking
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        return checknext7(input, identifiers);
    }
    else
    {
        cout << "\nCompile failed: Missing ';' after INTEGER\n";
        return false;
    }
    
}

//check for reserved word BEGIN
bool checknext7 (vector<string> input, vector<string> identifiers)
{
    if(input.front() == "BEGIN")
    {
        //good so far, keep checking
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        return checknext8(input, identifiers);
    }
    else
    {
        cout << "\nCompile failed: BEGIN missing or misspelled\n";
        return false;
    }
    
}

//check for expression list
//within this function is the checkexpression function that
bool checknext8 (vector<string> input, vector<string> identifiers)
{
    bool match = false;
    if(input.front() == "END.")
    {
        cout << "No errors, program ready for high level translation.\n\n"; return true;
    }
    else if(input.front() == "WRITE(")
    {
        //write function - check and go back
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        
        
        for(int i = 0; i < identifiers.size(); i++)
            if (input.front() == (identifiers.at(i)))
                match = true;
        if(match == false)
        {
            cout << "Compile failed: UNKNOWN IDENTIFIER used in statement\n";
            return false;
        }
        
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        
        if(input.front() != ")")  { cout << "Compile failed: Expression incomplete or incorrect\n"; return false; }
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        if(input.front() != ";")  { cout << "Compile failed: Expression incomplete or incorrect\n"; return false; }
        input.erase(input.begin());
        if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
        
        return checknext8(input, identifiers);
    }
    
    else
    {
        for(int i = 0; i < identifiers.size(); i++)
            if (input.front() == (identifiers.at(i)))
                match = true;
        if(match == false)
        {
            if(input.front() == "END")
                cout << "Compile failed: missing '.' after END \n";
            else
                cout << "Compile failed: UNKNOWN IDENTIFIER used in statement\n";
            return false;
        }
        else
        {
            input.erase(input.begin());
            if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
            if(input.front() != "=")  { cout << "Compile failed: Expression incomplete or incorrect\n"; return false; }
            input.erase(input.begin());
            if(input.empty()) { cout << "Program incomplete! Cannot compile\n"; return false; }
            
            //before going in here, we've got x = thingthing + thing - thing etc. we need to go until we get a ;
            match = checkexpression(input, identifiers);
            
            if(match)
            {
                while(input.front() != ";") {input.erase(input.begin());}
                input.erase(input.begin());
            }
            else
            {  cout << "Expression incomplete or incorrect! Cannot compile\n"; return false; }
        }
        return checknext8(input, identifiers);
    }
}

bool checkiddigit(char x)
{
    if(x == 'a' || x == 'b' || x == 'c' || x == 'd' || x == 'e' )
        return true;
    else if (x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9')
        return true;
    else
        return false;
}

//in order to check an expression, you need to evaluate this vector until you get a ;
bool checkexpression(vector<string> input,  vector<string> identifiers)
{
    stack<char> stack1; vector<char> einput;
    stack1.push('$');	stack1.push('E');	//stack1: E$ take from top
    string temp;
    while(input.front() != ";")
    {
        temp = input.front();
        
        //check if we got an identifier, replace with i if we did, else exit
        if(isalpha(temp[0]))
        {
            for(int x = 0; x < identifiers.size(); x++)
            {
                if (temp == (identifiers.at(x)))
                    temp = "i";
            }
            if(temp != "i")
            {
                cout << "Improper identifier used, or missing ';'! Compile failed\n";
                return false;
            }
        }
        
        //build the einput vector with input
        switch(temp[0])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':	{ einput.push_back('#'); break;}
            case '+':
            case '-':
            case '*':
            case '/':	{ einput.push_back(temp[0]); break; }
            case 'i':	{ einput.push_back(temp[0]); break; }
            default: break;
        }
        input.erase(input.begin());
    }
    
    //einput will now have the entire expression as a character input
    static string table[5][9] = {
        "NULL",	"NULL", "NULL", "NULL", "TQ", "NULL", "TQ", "TQ", "NULL",
        "+TQ", "-TQ", "NULL", "NULL", "NULL", "lambda", "NULL", "NULL", "lambda",
        "NULL",	"NULL", "NULL", "NULL", "FR", "NULL", "FR", "FR", "NULL",
        "lambda", "lambda", "*FR", "/FR", "NULL", "lambda", "NULL", "NULL", "lambda",
        "NULL",	"NULL", "NULL", "NULL", "(E)", "NULL", "i", "#", "NULL",
    };
    
    /*		+	-	*	/	(	)	i	#	$
     ----------------------------------------
     E |	-	-	-	-	TQ	-	TQ	-	-
     Q |	+TQ	-TQ	-	-	-	lam	-	-	lam
     T |	-	-	-	-	FR	-	FR	-	-
     R |	lam	lam	*FR	/FR	-	lam	-	-	lam
     F |	-	-	-	-	(E)	-	i	#	-
     -----------------------------------------
     */
    
    int x, y = 0;
    char s, i = '0';
    
    einput.push_back('$');
    while(1)
    {
        //get coordinates
        char s = stack1.top();
        char i = einput.front();
        if(s == i && s == '$')
        {
            return true;
        }
        else if(s == i && s != '$')
        {
            stack1.pop();
            einput.erase(einput.begin());
        }
        else{
            
            switch(s)
            {
                case 'E': y = 0; break;
                case 'Q': y = 1; break;
                case 'T': y = 2; break;
                case 'R': y = 3; break;
                case 'F': y = 4; break;
                default: break;
            };
            
            switch(i)
            {
                case '+':	x = 0; break;
                case '-':	x = 1; break;
                case '*':	x = 2; break;
                case '/':	x = 3; break;
                case '(':	x = 4; break;
                case ')':	x = 5; break;
                case 'i':	x = 6; break;
                case '#':	x = 7; break;
                case '$':	x = 8; break;
                default: break;
            }
            
            if(table[y][x] == "lambda")
            {
                stack1.pop();
            }
            
            else if(table[y][x] == "NULL")
            {
                cout << "Expression syntax invalid! Cannot compile\n";
                return false;
            }
            else
            {
                temp = table[y][x];
                int l = temp.length();
                //push whatever is at table[x][y] into the stack1
                //after removing what's on top
                stack1.pop();
                
                for(int j = 0; j < l; j++)
                {
                    stack1.push(temp[l - j - 1]);
                }
            }
            
        }
        
    }
}

void highleveltranslate()
{
    ifstream infile;
    infile.open("newdata.txt");
    vector<string> myvector;
    string temp;
    while(infile >> temp)
        myvector.push_back(temp);
    infile.close();
    
    ofstream outfile;
    outfile.open("highleveloutput.txt");
    
    outfile << "#include <iostream>\nusing namespace std ;\nint main()\n{\n";
    for(int i = 0; i < 4; i++)
        myvector.erase(myvector.begin());
    outfile << "int ";
    while(myvector.front() != ":")
    {
        
        if(myvector.front() == ",")
        { outfile << ", "; myvector.erase(myvector.begin()); }
        else
        { outfile << myvector.front(); myvector.erase(myvector.begin()); }
    }
    outfile << " ;" << endl;
    
    for(int i = 0; i < 4; i++)
        myvector.erase(myvector.begin());
    
    while(myvector.front() != "END.")
    {
        bool t = false;
        if(myvector.front() == ";")
            outfile << ";" << endl;
        else if(myvector.front() == "WRITE(")
        {
            outfile << "cout << " << myvector.at(1) << " << endl ;" << endl;
            t = true;
        }
        else
            outfile << myvector.front() << " ";
        
        if(!t)
            myvector.erase(myvector.begin());
        if(t)
            for(int i = 0; i < 4; i++)
                myvector.erase(myvector.begin());
    }
    outfile << "return 0 ;\n}";
    outfile.close();
    
    cout << "High level translation complete... see \"highleveloutput.txt\" for C++ code\n\n";
}


void cleanup()
{
    string getinput();
    float evaluate(string);
    //////////////////////////////
    //read file first time, adding "$$" to indicate end of line
    //////////////////////////////
    vector<string> readit;
    ifstream fe("data.txt");
    
    string line;
    while(getline(fe, line))
    {
        readit.push_back(line+" $$");
    }
    
    //////////////////////////////
    //initial output to newdata.txt
    //source: http://stackoverflow.com/questions/6406356/writing-vector-values-to-a-file
    //////////////////////////////
    ofstream output_file("newdata.txt");
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(readit.begin(), readit.end(), output_iterator);
    output_file.close();
    
    //////////////////////////////
    //read information from new file to a vector named "store"
    //////////////////////////////
    ifstream inFile ("newdata.txt");
    vector<string> store;
    string temp;
    while (inFile >> temp)
    {
        store.push_back(temp);
    }
    inFile.close();
    /*istream_iterator<string> in_iter(inFile) ;
     istream_iterator<string> eof;
     
     while (in_iter != eof)
     {
     store.push_back(*in_iter++);
     }
     *in_iter++;
     
     inFile.close();
     */
    //////////////////////////////
    //remove all other comments that exist on their own line
    //////////////////////////////
    for(int x = 0; x<store.size(); x++)
    {
        if(store[x][0]=='(' && store[x][1]=='*')
        {
            int y = 0;
            do{								//comment starts at word: store[x]
                store.erase(store.begin()+x);
            }while(store[x][store[x].size() - 2]!='*' &&store[x][store[x].size() - 1]!=')' );			//comment ends then we read end of line symbol ($$)
            store.erase(store.begin()+x);
        }
    }
    
    ////////////////////////////////
    //Remve any comments found after a semicolon
    ////////////////////////////////
    for(int x = 0; x<store.size(); x++)
    {
        for(int y = 0; y<store[x].size(); y++)
        {
            if(store[x][y]==';')
            {
                for(int z = y+1; z<store[x].size(); z++)
                {
                    store[x][z]=NULL;
                }
            }
        }
    }
    
    ///////////////////////////////////
    //Remove all where there are two End of Line signifiers ("$$")
    //////////////////////////////////
    for(int x = 0; x<store.size(); x++)
    {
        if(store[x]=="$$")
        {
            store.erase(store.begin()+x);
            x--;
        }
    }
    ////////////////////////////////
    // put "VAR" and "BEGIN"
    ////////////////////////////////
    for(int x = 0; x<store.size(); x++)
    {
        if(store[x]=="VAR" || store[x]=="BEGIN")
        {
            store[x].insert(store[x].begin()+store[x].size(),'\n');
        }
    }
    
    
    ////////////////////////////////
    //Add spaces around + - = , ;
    ///////////////////////////////
    for(int x = 0; x<store.size(); x++)
    {
        for(int y = 0; y<store[x].size(); y++)
        {
            if(store[x][y]=='+' || store[x][y]=='-' || store[x][y]=='=' || store[x][y]==',' || store[x][y]==';' || store[x][y]=='*' || store[x][y]==')' || (store[x][y] == '(' && store[x][y-1] != 'E'))
            {
                    store[x].insert(store[x].begin()+y,' ');
                if(store[x][y+2] != ' ')
                    store[x].insert(store[x].begin()+y+2, ' ');
                y++;
            }
        }
        if(store[x][0]!=' ')
        {
            store[x].insert(store[x].begin(), ' ');
        }
    }
    
    /////////////////////////////////
    //Combine the words together on the respective lines
    /////////////////////////////////
    vector<string> finalOutput(store.size());
    int z = 0;
    for(int x = 0; x<store.size(); x++)
    {
        finalOutput[z]+=store[x];
        for(int y=0; y<store[x].size(); y++)
        {
            if(store[x][y]==';')
            {
                z++;
            }
        }
    }
    
    store = finalOutput;
    
    //////////////////////////////
    //output final data to newdata.txt
    //source: http://stackoverflow.com/questions/6406356/writing-vector-values-to-a-file
    //////////////////////////////
    ofstream output_file2("newdata.txt");
    ostream_iterator<string> output_iterator2(output_file2, "\n");
    copy(store.begin(), store.end(), output_iterator2);
    output_file2.close();
    
    /////////////////////////////
    //Cout to verify code was executed correctly
    /////////////////////////////
    char sent = 'y';
    
    cout<<"Your data from data.txt has been successfully parsed, and placed in file newdata.txt."
    <<endl
    <<"enter a character and press enter to proceed"
    <<endl;
    cin >> sent;
}
