
#include "itkImage.h"

#include "itkImageFileReader.h"
#include "itkImageRegionIterator.h"
// Software Guide : EndCodeSnippet

#include "itkImageFileWriter.h"
#include <itkImageRegionConstIterator.h>
// Software Guide : EndCodeSnippet

int main( int argc, char * argv[])
{
  if( argc < 3 ) {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputRGBImageFile  outputRGBImageFile " << std::endl;
    return EXIT_FAILURE;
  }

  typedef unsigned char          PixelType;
  const unsigned int             Dimension = 2;

  typedef itk::Image< PixelType, Dimension >   ImageType;
  using ReaderType = itk::ImageFileReader< ImageType >;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  typedef itk::ImageFileWriter< ImageType >  WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  const char * filename = argv[1];
  const char * output = argv[2];
  reader->SetFileName( filename );
  writer->SetFileName( output );

  reader->Update();

  ImageType::Pointer image = reader->GetOutput();
  ImageType::RegionType region = image->GetLargestPossibleRegion();
  ImageType::SizeType regionSize = region.GetSize();

 // ImageType::RegionType regionSize;
  region.SetSize(regionSize);

  itk::ImageRegionIterator<ImageType> imageIterator(image,regionSize);
  /*
   * calculate histogram
   */
  int hist[923];
  for(int i = 0; i <= 923; i++){

    hist[i] = 0;
  }

  while(!imageIterator.IsAtEnd())
  {
    // Get the value of the current pixel
    unsigned int val = imageIterator.Get();
    std::cout << (int)val << std::endl;
    hist[val]++;
    ++imageIterator;
  }

  int size = sizeof(hist)/sizeof(hist[0]);

  /*
   * print histogram
   */

  std::cout <<"histogram"  << std::endl;
  for(int i=0; i<=size; i++){

    std::cout << "pixel"<<i <<"  "<<hist[i] << std::endl;
  }
  std::cout << "image size"<<regionSize << std::endl;

/*
 * calculate segmenation
 */

  int  w = regionSize[0];
  int  h = regionSize[1];
  int threshold;
  int totalPixels= w*h;
  std::cout << totalPixels << std::endl;
  float G1= 0;
  float G2 = 0;
  int n1 = 0;
  int n2 = 0;
  float varMax = 0;

  for (int i = 0; i <= 255; i++){
    G1 += i * ((int)hist[i]);
  }

  for (int i = 0 ; i <= 255 ; i++) {
    // Update q1
    n1 += hist[i];
    if (n1 == 0)
      continue;
    // Update q2
    n2 = totalPixels - n1;

    if (n2 == 0)
      break;
    // Update m1 and m2
    G2 += (float) (i * ((int)hist[i]));
    float mu1 = G2 / n1;
    float mu2 = (G1 - G2) / n2;

    // Update the between class variance
    float varBetween = (float) n1 * (float) n2 * (mu1 - mu2) * (mu1 - mu2);

    // Update the threshold if necessary
    if (varBetween > varMax) {
      varMax = varBetween;
      threshold = i;
    }
  }
/*
 * Segment Image
 */
  std::cout <<"optimal threshold"<< threshold << std::endl;
  itk::ImageRegionIterator<ImageType> imageIterator2(image,regionSize);
  while(!imageIterator2.IsAtEnd())
  {
    unsigned int val = imageIterator2.Get();
    if(val > threshold) {
      imageIterator2.Set(255);
    }
    else {
      imageIterator2.Set(0);
    }
    ++imageIterator2;
  }
  writer->SetInput( image );
  writer->Update();

return EXIT_SUCCESS;
}
