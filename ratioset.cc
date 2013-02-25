#include "ratioset.h"

//defines how many neighbors much match ratios to be considered a similar ratio


ratioSet::ratioSet()
{
  count = 0;
  ratioSetVector = new vector<pixelRatio*>;
}

ratioSet::~ratioSet()
{

}

void ratioSet::constructRatioSet()
{
  //if the grey levels aren't already set, then do so.
  if(!ratioSetVector->front()->greyFound)
  {
    cout << "Grey levels not set for this image. Setting grey levels..." << endl;
    constructMeanGreyAll();
  }
  
  //this is probably literally the worst way to do this.
  //Unfortunately, in for a penny, in for a pound.
  for(unsigned int i = 0; i < ratioSetVector->size(); i++)
  {
    pixelRatio tempRatio = *ratioSetVector->at(i);
    int localGrey = tempRatio.grey;
    
    //if bordering, ignore certain pixels
    bool top=false, left=false, bottom=false, right = false;
    //left bordering pixel
    if(tempRatio.x == 0)
      left = true;
    if(tempRatio.y == 0)
      top = true;
    if(tempRatio.x == maxWidth-1) //literally the last element's xval
      right = true;
    if(tempRatio.y == maxHeight-1)// last yval; bottom
      bottom = true;
    
    //width*row + col
    //width*y + x

    // if we're on the left border
    // We could save on these operations by cascading them rather than having them all on
    // the same level.
    //int x = tempRatio.x+1 + (tempRatio.y-1)*maxWidth;

    if(left)
    {
      tempRatio.ratioUL = 0;
      tempRatio.ratioML = 0;
      tempRatio.ratioDL = 0;
      
      tempRatio.ratioULPtr = 0;
      tempRatio.ratioMLPtr = 0;
      tempRatio.ratioDLPtr = 0;
    }
    
    else
    {
      if(!top)
      {
	tempRatio.ratioUL = localGrey / ratioSetVector->at(tempRatio.x-1 + (tempRatio.y-1)*maxWidth)->grey;
	tempRatio.ratioULPtr = ratioSetVector->at(tempRatio.x-1 + (tempRatio.y-1)*maxWidth);
      }
      tempRatio.ratioML = localGrey / ratioSetVector->at(i-1)->grey;
      tempRatio.ratioMLPtr = ratioSetVector->at(i-1);
      if(!bottom)
      {
	tempRatio.ratioDL = localGrey / ratioSetVector->at(tempRatio.x-1 + (tempRatio.y+1)*maxWidth)->grey;
	tempRatio.ratioDLPtr = ratioSetVector->at(tempRatio.x-1 + (tempRatio.y+1)*maxWidth);
      }
    }
    

    if(right)
    {
      tempRatio.ratioUR = 0;
      tempRatio.ratioMR = 0;
      tempRatio.ratioDR = 0;
      
      tempRatio.ratioURPtr = 0;
      tempRatio.ratioMRPtr = 0;
      tempRatio.ratioDRPtr = 0;
    }
    else
    {
      
      if(!top)
      {
	tempRatio.ratioUR = localGrey / ratioSetVector->at(tempRatio.x+1 + (tempRatio.y-1)*maxWidth)->grey;
	tempRatio.ratioURPtr = ratioSetVector->at(tempRatio.x+1 + (tempRatio.y-1)*maxWidth);
      }
      tempRatio.ratioMR = localGrey / ratioSetVector->at(i+1)->grey;
      tempRatio.ratioMRPtr = ratioSetVector->at(i+1);
      if(!bottom)
      {
	tempRatio.ratioDR = localGrey / ratioSetVector->at(tempRatio.x+1 + (tempRatio.y+1)*maxWidth)->grey;
	tempRatio.ratioDRPtr = ratioSetVector->at(tempRatio.x+1 + (tempRatio.y+1)*maxWidth);
      }
    }


    if(top)
    {
      tempRatio.ratioUL = 0;
      tempRatio.ratioUM = 0;
      tempRatio.ratioUR = 0;
      
      tempRatio.ratioULPtr = 0;
      tempRatio.ratioUMPtr = 0;
      tempRatio.ratioURPtr = 0;
    }
    else
    {
      tempRatio.ratioUM = localGrey / ratioSetVector->at(tempRatio.x + (tempRatio.y-1)*maxWidth)->grey;
      tempRatio.ratioUMPtr = ratioSetVector->at(tempRatio.x + (tempRatio.y-1)*maxWidth);
    }
    
    
    if(bottom)
    {
      tempRatio.ratioDL = 0;
      tempRatio.ratioDM = 0;
      tempRatio.ratioDR = 0;
      
      tempRatio.ratioDLPtr = 0;
      tempRatio.ratioDMPtr = 0;
      tempRatio.ratioDRPtr = 0;
    }
    else
    {
      tempRatio.ratioDM = localGrey / ratioSetVector->at(tempRatio.x + (tempRatio.y+1)*maxWidth)->grey;
      tempRatio.ratioDMPtr = ratioSetVector->at(tempRatio.x + (tempRatio.y+1)*maxWidth);
    }
    
    tempRatio.ratioComb = (tempRatio.ratioUL + tempRatio.ratioUM + tempRatio.ratioUR + tempRatio.ratioML
		    + tempRatio.ratioMR + tempRatio.ratioDL + tempRatio.ratioDM + tempRatio.ratioDR) / 8;
	

    ratioSetVector->at(i)->ratioUL = tempRatio.ratioUL;
    ratioSetVector->at(i)->ratioUM = tempRatio.ratioUM;
    ratioSetVector->at(i)->ratioUR = tempRatio.ratioUR;
    ratioSetVector->at(i)->ratioML = tempRatio.ratioML;
    ratioSetVector->at(i)->ratioMR = tempRatio.ratioMR;
    ratioSetVector->at(i)->ratioDL = tempRatio.ratioDL;
    ratioSetVector->at(i)->ratioDM = tempRatio.ratioDM;
    ratioSetVector->at(i)->ratioDR = tempRatio.ratioDR; 
    
    ratioSetVector->at(i)->ratioComb = tempRatio.ratioComb;
    
    ratioSetVector->at(i)->ratioULPtr = tempRatio.ratioULPtr;
    ratioSetVector->at(i)->ratioUMPtr = tempRatio.ratioUMPtr;
    ratioSetVector->at(i)->ratioURPtr = tempRatio.ratioURPtr;
    ratioSetVector->at(i)->ratioMLPtr = tempRatio.ratioMLPtr;
    ratioSetVector->at(i)->ratioMRPtr = tempRatio.ratioMRPtr;
    ratioSetVector->at(i)->ratioDLPtr = tempRatio.ratioDLPtr;
    ratioSetVector->at(i)->ratioDMPtr = tempRatio.ratioDMPtr;
    ratioSetVector->at(i)->ratioDRPtr = tempRatio.ratioDRPtr; 
  }
}

/**
 * Here's where we store the original pixel data in
 * our structures.
 */
void ratioSet::storeRawPixelData(tuple** inputImage, pam inpam)
{ 
  maxWidth = inpam.width;
  maxHeight = inpam.height;
  cerr << "ROFCAKES " << endl;
  //if we're greyscale, shortcut the op. An additional if per pixel would be multiple MOPS.
  if(inpam.depth == 1)
  {
    cerr << "Storing greyscale pixel image data. " << endl;
    for( int y = 0; y < maxHeight; y++)
    {
      for(int x = 0; x < maxHeight; x++)
      {
	pixelRatio* newRatio = new pixelRatio();
	int greyLevel = newRatio->grey;
	newRatio->grey = inputImage[y][x][0];
	newRatio->blue = greyLevel;
	newRatio->red = greyLevel;
	newRatio->green = greyLevel;
	newRatio->x = x;
	newRatio->y = y;
	newRatio->greyFound = true;
	
	ratioSetVector->push_back(newRatio);
      }
    }
  }	

  for(int y = 0; y < maxHeight; y++)
  {
    for(int x = 0; x < maxWidth; x++)
    {
      pixelRatio* newRatio = new pixelRatio();

      newRatio->blue = inputImage[y][x][2];
      newRatio->green = inputImage[y][x][1];
      newRatio->red = inputImage[y][x][0];
      newRatio->x = x;
      newRatio->y = y;
      
      ratioSetVector->push_back(newRatio);
    }
  }

  //pnm_freepamarray(inputImage, &inpam);
  
//  delete[] inputImage;
  
//  delete &	inpam;
  static int count = 0;
  count++;
  cerr << "Raw pixel data stored " << count << endl;
}

/** 
 * Averages the input ratio set's red, green and blue to create a grey. 
 */
void ratioSet::constructMeanGrey(pixelRatio* inRatio)
{
  inRatio->grey = (inRatio->blue + inRatio->green + inRatio->red) / 3.0;
  inRatio->greyFound = true;
}

/**
 * Creates the greyscale averaged data for all ratios in the local ratiosetvector.
 */
void ratioSet::constructMeanGreyAll()
{
  static int opCount = 1;
  cerr << "Constructing greys for image " << opCount << endl;
  for(unsigned int i = 0; i < ratioSetVector->size(); i++)
  {
    constructMeanGrey(ratioSetVector->at(i));
  }
  opCount++;
}

/**
 * Here is the crux, wherein we define what "similar ratio" means
 * and then search for and return them throughout all of this given 
 * RatioSet.
 */
vector< pixelRatio* >* ratioSet::findSimilarRatios(pixelRatio* inRatio, vector <pixelRatio* >* compareRatioSetVector)
{
  vector <pixelRatio*>* similarRatios = new vector<pixelRatio*>();
  
  for(unsigned int i = 0; i < compareRatioSetVector->size(); i++)
  {
  // cerr << "nonefound " << i << endl;
    if(compareRatioSetVector->at(i)->sameRatioCount(*inRatio) >= RAT_NEIGHBOR_SENSITIVITY)
      similarRatios->push_back(compareRatioSetVector->at(i));
    
    if(similarRatios->size() >= RAT_SIZE_LIMIT)
      return similarRatios;
    
  }
  
  //cerr << "Similar Ratio Count: " << similarRatios->size() << endl;
  
  return similarRatios;
}
