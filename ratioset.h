/**
 * Class Ratioset
 * 
 * Uses the Ratio struct to define a set of "ratios" for a given image.
 * 
 * A "ratio" is a collection of pixel ratios for a given pixel, constructed
 * by dividing it with a neighbor, for each neighbor intensity.
 * Thus each image will have around 8*y*x ratios in its ratioset.
 * 	(Bordering pixels will have less)
 */

#ifndef RATIOSET_H
#define RATIOSET_H

#define RAT_NEIGHBOR_SENSITIVITY 1 //how many neighbors need to match before we say the ratios are equitable?
#define RAT_SIZE_LIMIT 1	    //after how many matches do we bail out?
#define RAT_SIMILARITY_RANGE_UPPER 0.4	//how lenient are we in terms of what constitutes a "same" ratio match?
#define RAT_SIMILARITY_RANGE_LOWER 0.4
#define RAT_COMB_SIZE 8
#define RAT_SAMEPIXEL_ONLY false
//only compared if the greyval is the same, otherwise skip.



#include <iostream>
#include <vector>
//#include <hash_map>
#include "pam_assistant.h"

using namespace std;

struct pixelRatio{
  int red, green, blue;
  float grey;
  bool greyFound;
  
  int x, y;
  
  //ratios of us:neighbors
  float ratioUL, ratioUM, ratioUR, ratioML, ratioMR, ratioDL, ratioDM, ratioDR;
  
  //combination ratio 
  float ratioComb;
  
  //pointers to neighbors.
  pixelRatio* ratioULPtr, *ratioUMPtr, *ratioURPtr, *ratioMLPtr, *ratioMRPtr, *ratioDLPtr, *ratioDMPtr, *ratioDRPtr;
  
  pixelRatio(){red = 0; blue = 0; green = 0; grey = 0; greyFound = false; }
  
  //returns the amount of matches - border pixels
  int sameRatioCount(pixelRatio inRatio)
  { 
    //Leniency filters.
     if(inRatio.ratioComb > ratioComb && inRatio.ratioComb < ratioComb + RAT_SIMILARITY_RANGE_UPPER)
       return RAT_NEIGHBOR_SENSITIVITY;
     else if(inRatio.ratioComb < ratioComb && inRatio.ratioComb > ratioComb - RAT_SIMILARITY_RANGE_LOWER)
       return RAT_NEIGHBOR_SENSITIVITY;
     else if(inRatio.ratioComb > 2 || ratioComb > 2)
       
     cerr << "upper pass vars " << inRatio.ratioComb << " " << ratioComb << endl; 
    /*
    if(ratioComb > 0
    
    // We autopass if the combined ratio is close enough.
    if(ratioComb > inRatio.ratioComb && ratioComb < inRatio.ratioComb + RAT_SIMILARITY_RANGE_UPPER)
    {
      cerr << "upper pass vars " << inRatio.ratioComb << " " << ratioComb << endl; 
      return RAT_NEIGHBOR_SENSITIVITY;
    }
    else if(ratioComb < inRatio.ratioComb && ratioComb > inRatio.ratioComb - RAT_SIMILARITY_RANGE_LOWER)
    {
      cerr << "inner pass vars " << inRatio.ratioComb << " " << ratioComb << endl;
      return RAT_NEIGHBOR_SENSITIVITY;
    }
    */
    
    int matchCount = 0;
    if(ratioUL == inRatio.ratioUL && ratioULPtr != 0)
      matchCount++;
    if(ratioUR == inRatio.ratioUR && ratioURPtr != 0)
      matchCount++;
    if(ratioUM == inRatio.ratioUM && ratioUMPtr != 0)
      matchCount++;
    if(ratioML == inRatio.ratioML && ratioMLPtr != 0)
      matchCount++;
    if(ratioMR == inRatio.ratioMR && ratioMRPtr != 0)
      matchCount++;
    if(ratioDL == inRatio.ratioDL && ratioDLPtr != 0)
      matchCount++;
    if(ratioDM == inRatio.ratioDM && ratioDMPtr != 0)
      matchCount++;
    if(ratioDR == inRatio.ratioDR && ratioDRPtr != 0)
      matchCount++;
    
    return matchCount;
  }
  
  int booleanSameCount(pixelRatio inRatio)
  {
    if(inRatio.ratioComb == ratioComb)
      return 1;
    else
      return 0;
  }
  
};

/**
 * A Ratioset. Actually, this is really just another representation of the original images.
 */
class ratioSet
{
  public:
    ratioSet();
    ~ratioSet();
    
    vector <pixelRatio*>* ratioSetVector;
    
    //Constructs the ratio set data from the input image data.
    void constructRatioSet();
    
    // Stores the raw pixel information in records.
    void storeRawPixelData(tuple** inputImage, pam inpam);
    
    //creates a grey from R+G+B /3
    void constructMeanGrey(pixelRatio*);
    
    //Calls constructmeangrey on all pixelrecords
    void constructMeanGreyAll();
    
    int count;
    
    //Width/height of this given image
    int maxWidth, maxHeight;
    
    //
    vector <pixelRatio*>* findSimilarRatios(pixelRatio* inRatio, vector <pixelRatio* >* compareRatioSetVector); 
    
  private:
    
};





#endif 