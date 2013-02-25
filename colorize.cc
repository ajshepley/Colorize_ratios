/**
 * CPSC 4850 - Digital Image Processing
 * Final Project
 * 
 * File: hist_eq.cc
 * Date: November 27th, 2012
 * Author: Adam Shepley
 * 
 * This program uses downloading of example user-specified imagery,
 * and localized kernal creation and placement to attempt to colorize
 * an input greyscale image.
 * 
 * Essentially, we create "ratios" between each pixel and its neighbors, for
 * each sample image relating to our grey image.
 * 
 * We then attempt to find a consensus among these (or a closest match),
 * and fine the most likely color therein. We then use these resulting colors
 * to color our original image.
 */

#ifndef M_PI
#define M_PI atan(1)*4
#endif


#ifndef DEBUG
#define DEBUG true
#endif


#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string.h>
#include <sstream>


#include <dirent.h>
#include <map>


#include "imageDownload.h"
#include "ratioset.h"
#include "pam_assistant.h"

using namespace std;
  
tuple** ColorToGrey(tuple** inputImage, const pam &inpam, pam& greyPam);


int main(int argc, char *argv[])
{
  
  /*
   * Command inputs: argv[0] is program call
   * 		     argv[1] is input greyscale pgm name
   * 		     argv[2] is output color pnm name
   */
  
  /* structures for input image */
  pam inpam;
  pam outpam;
  /* a dynamic two-dimensional array to store the pixels...note that
     pnm uses a tuple (for color images with multiple planes) for
     each pixel.  For PGM files it will only be one plane. */
  tuple **input_array, **output_array;

  /* initializes the library */
  pm_init(argv[0], 0);

  /* read the image */
  input_array = read_image(argv[1], inpam);  

  /*
   * Established variables for our to-be-resized image.
   */ 
  outpam = inpam;
  
  //vector <tuple**>* colorImages = DirectoryToImageVector();

  //downloadImages();	couldn't get the bash script working properly with WGET, so this feature is stripped.
  
  //output_array = ColorToGrey(input_array, inpam, outpam);
  
  
  
  // Load our images into our ratio set class.
  if(DEBUG)
    cerr << "Loading images..." << endl;
  
  //load a directory of images into a ratio set.
  vector <ratioSet*>* comparisonImages = DirectoryToImageVector();
  ratioSet* original_grey_ratioset = new ratioSet();
  
  cerr << "Constructing ratioset for input image..." << endl;
  original_grey_ratioset->storeRawPixelData(input_array, inpam);
  original_grey_ratioset->constructRatioSet();

  cerr << "Loaded images. " << endl;
  
  /**
   * Now that we have the images all stored internally, we can create the
   * "greyscale equivalents" for every single ratioSet/pixel.
   */
  
  // Convert all of the images to greyscale.
  if(DEBUG)
    cerr << "Converting images to greyscale..." << endl;
  for(unsigned int i = 0; i < comparisonImages->size(); i++)
  {
    comparisonImages->at(i)->constructMeanGreyAll();
    
    if(DEBUG)
      cerr << "Constructed image " << i+1 << " of " << comparisonImages->size() << ". Building ratiosets..." << endl;
    comparisonImages->at(i)->constructRatioSet();
  }
  
  
  cout << "Comparing greypixels with sample images..." << endl;
  /**
   * With every image having a greyscale representation AND greyscale ratios
   * calculated, we raw_search every ratioset for a ratio equivalency to every single
   * one in our original grey image.
   */
  vector <vector <pixelRatio*>* > myLikelyRatios;	//should equal [originalSize][likelyResults] in size
  for(unsigned int i = 0; i < original_grey_ratioset->ratioSetVector->size(); i++)
  {
    //cerr << "Examining original greypixel " << original_grey_ratioset->ratioSetVector->at(i)->x << " " << original_grey_ratioset->ratioSetVector->at(i)->y << endl;
    for(unsigned int j = 0; j < comparisonImages->size(); j++)
    {
      //compare our pixel ratio with every single on in the other images.
     myLikelyRatios.push_back(original_grey_ratioset->findSimilarRatios(original_grey_ratioset->ratioSetVector->at(i), 
							  comparisonImages->at(j)->ratioSetVector));
    }
    if((i%original_grey_ratioset->maxWidth*20) == 0)
      cerr << "Examining original greypixel " << original_grey_ratioset->ratioSetVector->at(i)->x << " " << original_grey_ratioset->ratioSetVector->at(i)->y << endl;
  }
  cerr << "Done. " <<endl;
  
  
  
  
  delete comparisonImages;
   // int x; cin >> x;
  
  //write_image(argv[2], outpam, output_array);

  /* clean up */
  pnm_freepamarray(input_array, &inpam);
//  pnm_freepamarray(output_array, &outpam);
  

  cerr << "Finished processing." << endl;
  return 0;
}




/**
 * Takes a color image and returns a PAM (and correspondingly allocated
 * tuple image) of it in greyscale (arithmetic averaged) form.
 * 
 * Returns the image tuple, modifies the new pam by reference.
 * 
 * Since PAM uses cstrs, we need to use strcmp and strcpy.
 */
tuple** ColorToGrey(tuple** inputImage, const pam& inpam, pam& greyPam)
{
  greyPam = inpam;
  strcpy(greyPam.tuple_type, "GRAYSCALE");
  greyPam.format = 20533;	//greyscale - color is 20534.
  greyPam.depth = 1;
  tuple** greyArray = pnm_allocpamarray(&greyPam);
  
  if(DEBUG == TRUE)
  {
    cerr << "Converting " << inpam.width << "x" << inpam.height << " image to GRAYSCALE." << endl;
  }
  
  if(strcmp("GRAYSCALE", inpam.tuple_type) == 0)
  {
    if(DEBUG)
      cout << "Source image is already a Grayscale image.";
    return greyArray;
  }
  else if(strcmp("RGB", inpam.tuple_type) == 0)
  {
    for(int y = 0; y < inpam.height; y++)
    {
      for(int x = 0; x < inpam.width; x++)
      {
	greyArray[y][x][0] = (inputImage[y][x][0] + inputImage[y][x][1] + inputImage[y][x][2]) / 3;
      }
    }
  }
  
  return greyArray;
}


