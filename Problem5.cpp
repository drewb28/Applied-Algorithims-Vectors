/*
Drew Boodhan
drewb28@bu.edu
U33298069

partner: Noah Malhi
malhin@bu.edu
U12534528

Out codes run time is 0(n^2). We calculated this as the worst runtime is caused by a nested for loop. Thus the asymptotic run time would be O(n^2).
The program finds all the slopes and y intercepts from the given cordinates, finds all the different slopes and intercepts without repitition, and then finds the cordinates that correspond to those slopes/intercepts if the number of cordinates is >= 4.
This finds collinear points basically (duh).
    */

#include <iostream>
using namespace std;

#include <string>
#include <limits>
#include <vector>
#include <fstream>

//uses infinity in cases slope is undefined(vertical)
float inf = numeric_limits<float>::infinity();
float calcSlope(float xPoint1,float xPoint2,float yPoint1,float yPoint2);
float calcB(float xPoint, float yPoint, float slope);


int main(int argc, char *argv[]){
  
//recieves name of file from argument
    string fileName;
    fileName = argv[1];
    
//opens and reads fuke
    fstream File;
    File.open(fileName);
    float num1;
    int count;
    count  = 0;


    vector<float> xVal;	//xcords
    vector<float> yVal;		//ycords

 
    while(!File.eof())
	{
        File >> num1;

        //Multiples of two are y values
        if(count % 2 == 0)
	{
            yVal.push_back(num1);
        }
	else
	{
            xVal.push_back(num1);
        }
        count = count + 1;
    }

    //Delete last number
    xVal.pop_back();
    yVal.erase(yVal.begin());

   
    File.close();

    //Calculates the number of points
    int numPoints = count/2;


     
    vector<float> slopes;
    vector<float> BVals;

   
    int size = yVal.size();


     int fooCount = 0;	
    
	while (fooCount != size)
	{
     		  for(int k = fooCount + 1; k < size; k++)
		{
      		  //calculates the slopes and intercepts and returns the colinear point
       

  		     if(k == fooCount)
			{
         	   slopes.push_back(inf);
			BVals.push_back(inf);
      		  }
		else
		{
			float slope = calcSlope(xVal[fooCount],xVal[k],yVal[fooCount],yVal[k]);
			float intercept = calcB(xVal[fooCount],yVal[fooCount],slope);
			slopes.push_back(slope);
			BVals.push_back(intercept);
		}
	
       }
	fooCount++;
    }


    vector<float> diffSlope;
	
    //checks if value is already in the vector to make sure there is no repeats
    bool real = false;
    int diffCount = 0;	

     while (diffCount != slopes.size())
	{
        if(diffCount==0)
	{
            diffSlope.push_back(slopes[diffCount]);
        }
	else
 	    {
            for(int j=0; j<diffSlope.size();j++)
	     {
                if(slopes[diffCount] == diffSlope[j])
	    {
                    real = true;
                }
            }
            if(!real)
		{
                diffSlope.push_back(slopes[diffCount]);
            }
            real = false;
        }
	diffCount++;
    }

    
    vector<float> newBVal;

    //puts non repeating values into an array
    bool exists = false;
    for(int i=0; i< BVals.size(); i++)
	{
        if(i==0)
	{
            newBVal.push_back(BVals[i]);
        }
	else
	 {
            for(int j=0; j<newBVal.size();j++)
		{
                if(BVals[i] == newBVal[j])
		{
                    exists = true;
                }
            }
            if(!exists)
	    {
               newBVal.push_back(BVals[i]);
            }
            exists = false;
        }
    }
    

	//Finds the number of slopes for each slope
	vector<float> slopenumber(diffSlope.size(),0);
	for(int i=0; i<diffSlope.size();i++)
	{
		for(int j=0; j<slopes.size();j++)
		{
			if(diffSlope[i] == slopes[j])
			{
				slopenumber[i] = slopenumber[i]+1;
			}
		}
	}


	vector<float> interceptnum(newBVal.size(),0);
	for(int i=0; i<newBVal.size();i++){
		for(int j=0; j< BVals.size();j++){
			if(newBVal[i] == BVals[j]){
				interceptnum[i] = interceptnum[i]+1;
			}
		}
	}


	//Finds the final slope that the cordinates will be found from
	vector<float> endSlope;
		int slopeNum = 0;
    		while(slopeNum != slopenumber.size())
		{
			if(slopenumber[slopeNum] >= 2 && slopenumber[slopeNum]!= inf)
			{
				endSlope.push_back(diffSlope[slopeNum]);
			}	
			slopeNum++;
		}
	

	//Finds the final interscepts that the cordinates will be found from
	vector<float> endBVal;
	int intNum = 0;	
	while(intNum != interceptnum.size())
	{
		if(interceptnum[intNum] >= 2)
		{
			endBVal.push_back(newBVal[intNum]);
		}	
		intNum++;
	}



 //Finds all the cordinates and outputs them
for(int x = 0; x <endSlope.size(); x++){

       for(int j=0; j<slopes.size(); j++){
 
		float slope = calcSlope(xVal[j],xVal[j+1],yVal[j],yVal[j+1]);
		float intercept = calcB(xVal[j],yVal[j],slope);

		
		
		if(slope == endSlope[x] && intercept == endBVal[x]){
			cout << "(" << xVal[j] << "," << yVal[j] << ")" << endl;
	}
	
       }

	cout << endl;
 }

    return 0;
}
//functions for slope and intercept calculations
float calcB(float xPoint, float yPoint, float slope){
	//y = mx+b, b = y - mx
	float bVal = yPoint - (slope * xPoint);
	return bVal;
}

float calcSlope(float xPoint1,float xPoint2,float yPoint1,float yPoint2){

	float deltaY, deltaX;
	
	deltaY = yPoint2-yPoint1;
	deltaX = xPoint2-xPoint1;
	
	if(deltaX == 0){
		return inf;
	}
	
	float slope = deltaY/deltaX;
	return slope;
}

