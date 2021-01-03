//
// <<Bhavana Laxmi Radharapu>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

using namespace std;

// struct to store the data related to a specific movie 
struct MovieData
{
int PubYear;
string movieName;
int movieID;
int Num5Stars;
int Num4Stars;
int Num3Stars;
int Num2Stars;
int Num1Stars;
};


binarysearchtree<int,MovieData> BSTbyID; // storing data with the key as the ID and value as the movieData struct
binarysearchtree<string,MovieData> BSTbyName; // storing data with the name as the ID and value as the movieData struct

//---------------------------------------------------------------------------------
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}
//---------------------------------------------------------------------------------
//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

	while (!moviesFile.eof())
	{
		MovieData data;
		data.movieID = id;
		data.Num5Stars = 0;
		data.Num4Stars = 0;
		data.Num3Stars = 0;
		data.Num2Stars = 0;
		data.Num1Stars = 0;
	  
    // we have more data, so input publication year and movie name:

		moviesFile >> pubYear;
		data.PubYear = pubYear;
		getline(moviesFile, name);  // movie name fills rest of input line:
	  
    // trim potential whitespace from both ends of movie name:
    
	    name = trim(name);
		data.movieName = name;
	

    // debugging:
//     cout << id << "," << pubYear << "," << name << endl;
      
		BSTbyID.insert(id, data);
		BSTbyName.insert(name, data);
		moviesFile >> id;  // get next ID, or set EOF flag if no more data:
	}
}
//---------------------------------------------------------------------------------
// A function to update the variables in the movieData struct related to the reviews
void Reviews(int review, MovieData* data)
{
	if( review == 5){
		data->Num5Stars++;
	}
	else if(review == 4){
		data->Num4Stars++;
	}
	else if(review == 3){
		data->Num3Stars++;
	}
	else if(review == 2){
		data->Num2Stars++;
	}
	else if(review == 1){
		data->Num1Stars++;
	}
}
//---------------------------------------------------------------------------------
// A function to read data from the "reviews.txt" file and then update the data in the nodes for the tree.
void InputReviews(string reviewsFilename, int &reviews)
{

	ifstream reviewsFile(reviewsFilename);
	int movieid, reviewid,review;
	
	if (!reviewsFile.good())
	{
		cout << "**Error: unable to open movies file '" << reviewsFilename << "', exiting" << endl;
		return;
	}
	
	reviewsFile >> reviewid;  // get first ID, or set EOF flag if file empty:

	while (!reviewsFile.eof())
	{
		MovieData data;
		// we have more data, so input publication year and movie name:
		reviewsFile >> movieid;
		data.movieID = movieid;
		reviewsFile >> review;
		reviews++;
		
		MovieData* Data1 = BSTbyID.search(movieid);
		string name = Data1->movieName;
		
		// debugging:
		MovieData* Data2 = BSTbyName.search(name);
		BSTbyID.insert(movieid, data);
		BSTbyName.insert(name, data);
		Reviews(review,Data1);
		Reviews(review,Data2);
		reviewsFile >> reviewid;  // get next ID, or set EOF flag if no more data:
	}
}
//---------------------------------------------------------------------------------
// A funtion to calculate the average rating for the movie
double average(MovieData* data)
{
	double sum =0.0;
	double avg = 0.0;
	// sum of the reviews
	sum = 5*data->Num5Stars + 4*data->Num4Stars + 3*data->Num3Stars + 2*data->Num2Stars +data->Num1Stars;
	if(sum == 0.0)
		return 0.0;
	// to calculate the number of reviews 
	double numReviews = data->Num5Stars + data->Num4Stars + data->Num3Stars + data->Num2Stars + data->Num1Stars;
	avg = sum/numReviews;
	return avg;
	
}
//---------------------------------------------------------------------------------
//
// main
//
int main()
{
	string moviesFilename; // = "movies1.txt";
	string reviewsFilename; // = "reviews1.txt";
	string userInput;
	int numreviews = 0;
	
	cout << "movies file?> ";
	cin >> moviesFilename;

	cout << "reviews file?> ";
	cin >> reviewsFilename;

	string junk;
	getline(cin, junk);  // discard EOL following last input:

	InputMovies(moviesFilename);
	InputReviews(reviewsFilename,numreviews);
	
	cout<<"Num movies: "<<BSTbyName.size()<<endl;
	cout<<"Num reviews: "<<numreviews<<endl<<endl;
	cout<<"Tree by movie id: size="<<BSTbyID.size()<<", height="<<BSTbyID.height()<<endl;
	cout<<"Tree by movie name: size="<<BSTbyName.size()<<", height="<<BSTbyName.height()<<endl<<endl;
	
	cout<<"Enter a movie id or name (or # to quit)> ";
	getline(cin,userInput);
	
	
	//to check for input if it is a movie id or movie name
	while(userInput != "#"){
		bool allDigits = true;
		for(size_t i=0;i<userInput.length();i++){
			// to check if the input is movie name
			if(isalpha(userInput[i]))
			{
				allDigits = false;
				break;
			}
		}
		
		//if the input is movie name the loop below is executed
		if(!allDigits)
		{
			MovieData* data = BSTbyName.search(userInput);
			//to check if the movie exists in the file
			if(data == nullptr){
				cout<<"not found..."<<endl<<endl;
			}
			
			else
			{
				cout<<"Movie ID: "<< data->movieID<<endl;
				cout<<"Movie Name: " << data->movieName<<endl;
				
					cout<<"Avg rating: "<<average(data)<<endl;
					cout<<"5 stars: "<<data->Num5Stars<<endl;
					cout<<"4 stars: "<<data->Num4Stars<<endl;
					cout<<"3 stars: "<<data->Num3Stars<<endl;
					cout<<"2 stars: "<<data->Num2Stars<<endl;
					cout<<"1 star: "<<data->Num1Stars<<endl;
					cout<<endl;
				
				
			}
		}
		//if the userInput is movie id then the loop below is executed
		else 
		{
			MovieData* data = BSTbyID.search(stoi(userInput));
			if(data == nullptr){
				cout<<"not found..."<<endl<<endl;
			}
			else
			{
				cout<<"Movie ID: "<< data->movieID<<endl;
				cout<<"Movie Name: " << data->movieName<<endl;

					cout<<"Avg rating: "<<average(data)<<endl;
					cout<<"5 stars: "<<data->Num5Stars<<endl;
					cout<<"4 stars: "<<data->Num4Stars<<endl;
					cout<<"3 stars: "<<data->Num3Stars<<endl;
					cout<<"2 stars: "<<data->Num2Stars<<endl;
					cout<<"1 star: "<<data->Num1Stars<<endl;
					cout<<endl;
				
				
			}
		}
		
		cout<<"Enter a movie id or name (or # to quit)> ";
		getline(cin,userInput);
	}
	
  // done:
  return 0;
}
