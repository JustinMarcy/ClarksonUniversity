### Justin Marcy
### Date: 4/26/2020

# Pointers, Movie Example

* Task:
The file lab10movies.cppcontains  a  program  that  allows  the  user  to  read  movie  names  and movie release dates from a file called movies.txt. The data is read into a single ended linked list. Once all the data has been read in, the user is given a menu option with 3 choices. Choice1 will  list  all  movies  released  before  a  specified  year,  Choice  2  will  list  all  movies  stored  in  the linked list, and Choice 3 will exit the program.The file lab10movies.cppis incomplete, the sections you mustcomplete have the tag TODO on  them.  The  main  task  is  to  create  the  function showBeforeYearand  have  it  list  all  movies before a specified year, if there are no movies before the specified year then let the user know that there are no movies.

* Solution:

'''c++
#include<iostream>
#include<string>
#include<fstream>

//a struct called Movie
struct Movie {
  std::string movieName;
  int yearReleased;
};


//node represents a single node in the linked list
struct node
{
  Movie aMovie;
  node* prevPtr;
};

//Function: menu is used to display an interactive menu to the user
void menu();

//create a function prototype called showBeforeYear
void showBeforeYear(node* currentPtr, int userYear);

//Function: listMovies is used to display all movies in the linked list
void listMovies(node*);

int main()
{
	std::ifstream inputHandler;		//file handler for input file
	std::string movieNameFromFile;	//store movie name from file
	int movieYearFromFile;			//store movie year from file
	int userInput;					//get user input for menu interaction
	int userYear;					//get year from user to list movies
	node* currentPtr = NULL;		//currentPtr points to current list element, initialized to NULL
	node* headPtr = NULL;			//headPtr points to top of list, initialized to NULL

	//Open the movies.text file
	inputHandler.open("movies.txt");
	//Read the first line from the file
	inputHandler >> movieNameFromFile >> movieYearFromFile;

	while (!inputHandler.eof())
	{
		//create a new node called currentPtr
		currentPtr = new node;
	
		//set the value for currentPtr to the values read from the file
		currentPtr-> aMovie.movieName = movieNameFromFile;
		currentPtr-> aMovie.yearReleased = movieYearFromFile;	
	
		//set currentPtr->prevPtr to headPtr
		currentPtr->prevPtr = headPtr;

		//update headPtr to currentPtr
		headPtr = currentPtr;

		//read the next line from the file
		inputHandler >> movieNameFromFile >> movieYearFromFile;
	}

	//Close the file
	inputHandler.close();

	//Display the menu to the user
	menu();
	std::cin >> userInput;

	//Validate input
	while (userInput > 3 || userInput < 1)
	{
		//Display the menu to the user
		menu();
		std::cin >> userInput;
	}

	//List movies by year
	if (userInput == 1)
	{
	  // ask the user to enter the year
	  std::cout<<"Please enter a year"<<std::endl;
	  // store the year entered by the user in userYear
	  std::cin>>userYear;
	  // call function showBeforeYear with currentPtr and userYear
	  showBeforeYear(currentPtr, userYear); 
	  return 0;
	}
	//List all movies
	else if (userInput == 2)
	{
		//Call function listMovies to print all movies
		listMovies(currentPtr);
		return 0;
	}
	//Exit program
	else
	{
		//Show exit message and terminate program
		std::cout << "Exiting program." << std::endl;
		return 0;
	}
}

//Function: menu
//Inputs: none
//Outputs: none
//Errors: none
void menu()
{
	std::cout << "Press 1 to list movies released before a specific year." << std::endl;
	std::cout << "Press 2 to list all movies." << std::endl;
	std::cout << "Press 3 to quit." << std::endl;
	std::cout << "Enter your choice: ";
}

//TODO: create function showBeforeYear
//Function: showBeforeYear
//Inputs: node* currentPtr and int userYear
//Outputs: displays all movies before a specific year
//Errors: none
void showBeforeYear(node* currentPtr, int userYear)
{
  int atLeastOne = 0;
  while(currentPtr)
    {
      if(currentPtr->aMovie.yearReleased < userYear) {
      //Print entry from linked list
      std::cout << currentPtr->aMovie.movieName << " released in " << currentPtr->aMovie.yearReleased << std::endl;
      atLeastOne = 1;
      }
      //Move currentPtr to next location
      currentPtr = currentPtr->prevPtr;
    }
  if(atLeastOne == 0) {
    std::cout<<"No movies found before "<<userYear<<std::endl;
  }
  // if you find 0 movies before userYear, tell the user that you found no movies
}

//Function: listMovies
//Inputs: node* currentPtr
//Outputs: displays all movies stored in linked list
//Errors: none
void listMovies(node* currentPtr)
{
	//Loop until currentPtr hits NULL
	while(currentPtr)
	{
		//Print entry from linked list
		std::cout << currentPtr->aMovie.movieName << " released in " << currentPtr->aMovie.yearReleased << std::endl;
		//Move currentPtr to next location
		currentPtr = currentPtr->prevPtr;
	}
}
'''
