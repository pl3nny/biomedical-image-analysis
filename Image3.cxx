/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

// Software Guide : BeginLatex
//
// This example illustrates the use of the \code{SetPixel()} and
// \code{GetPixel()} methods.  These two methods provide direct access to the
// pixel data contained in the image. Note that these two methods are
// relatively slow and should not be used in situations where
// high-performance access is required. Image iterators are the appropriate
// mechanism to efficiently access image pixel data. (See
// Chapter~\ref{sec:ImageIteratorsChapter} on page
// \pageref{sec:ImageIteratorsChapter} for information about image
// iterators.)
//
// Software Guide : EndLatex

#include "itkImage.h"

#include "itkImageFileReader.h"
#include "itkImageRegionIterator.h"
// Software Guide : EndCodeSnippet

#include "itkImageFileWriter.h"



int main( int argc, char * argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " x1  y1 " << std::endl;
    return EXIT_FAILURE;
  }
  typedef unsigned char PixelType;
  const unsigned int Dimension = 2;

  typedef itk::Image<PixelType, Dimension> ImageType;
  using ReaderType = itk::ImageFileReader<ImageType>;

  typedef itk::ImageFileReader<ImageType> ReaderType;
  //typedef itk::ImageFileWriter<ImageType> WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  ReaderType::Pointer reader2 = ReaderType::New();

  //WriterType::Pointer writer = WriterType::New();

  const char *filename = argv[1];
  const char *filename2 = argv[2];

  reader->SetFileName(filename);
  reader2->SetFileName(filename2);
  //writer->SetFileName( output );

  reader->Update();
  reader2->Update();

  ImageType::Pointer image = reader->GetOutput();
  ImageType::Pointer image2 = reader2->GetOutput();

  ImageType::RegionType region = image->GetLargestPossibleRegion();
  ImageType::RegionType region2 = image2->GetLargestPossibleRegion();

  ImageType::SizeType regionSize = region.GetSize();
  ImageType::SizeType regionSize2 = region2.GetSize();

  // ImageType::RegionType regionSize;
  region.SetSize(regionSize);
  region2.SetSize(regionSize);
  // First the image type should be declared

  itk::ImageRegionIterator<ImageType> imageIterator(image, regionSize);
  itk::ImageRegionIterator<ImageType> imageIterator2(image2, regionSize2);

  int SegmentedPixel = 255;
  std::cout << SegmentedPixel << std::endl;
  int X1;
  int Y1;
  int TP;
  int TN;
  double J;

 // while (!imageIterator.IsAtEnd()) {
  //  unsigned int val = imageIterator.Get();
  //  if (val == SegmentedPixel)
  //    X1 += 1;
   // ++imageIterator;
 // }

  //while (!imageIterator2.IsAtEnd()) {
   // unsigned int val2 = imageIterator2.Get();
   // if (val2 == SegmentedPixel) {
   //   Y1 += 1;
    //   ++imageIterator2;
  //}

  std::cout << "point #0" << std::endl;

    while (!imageIterator2.IsAtEnd() && !imageIterator.IsAtEnd()) {

     // std::cout << "point #1" << std::endl;

      unsigned int val = imageIterator.Get();
      unsigned int val2 = imageIterator2.Get();


     // std::cout << "point #2" << std::endl;

      if (val == SegmentedPixel) {
        X1 += 1;
        std::cout << X1 << std::endl;

      }

     // std::cout << "point #3" << std::endl;

      if (val2 == SegmentedPixel) {
        Y1 += 1;
        std::cout << Y1 << std::endl;

      }
      if (val == SegmentedPixel && val2 == SegmentedPixel) {

        TP += 1;

      }
      if (val != SegmentedPixel && val2 != SegmentedPixel) {
        TN += 1;
        //std::cout << TN << std::endl;

      }
      ++imageIterator;
      ++imageIterator2;
    }

    //  std::cout << "point #4" << std::endl;

      J = ((float) TP) / (((float) (X1 + Y1)) - ((float) TP));
      std::cout << "Jaccard Index"<< J << std::endl;


    int FN = X1-TP;
    int FP = Y1-TP;
    double sensitivity;
    double specificity;
    double precision;
    double accuracy;
    sensitivity = ((float)TP) / (((float)(TP+FN)));
    specificity = ((float)TN)/ (((float)(TN+FP)));
    precision = ((float)TP)/ (((float)(TP+FP)));
    accuracy = (((float)(TP+TN)))/(((float)(TP+FN+TN+FP)));

    std::cout<< "Sensitivity "<<sensitivity<< std::endl;
    std::cout<< "Specificity "<<specificity<< std::endl;
    std::cout<< "precision "<<precision<< std::endl;
    std::cout<< "accuracy "<<accuracy<< std::endl;

      return EXIT_SUCCESS;
    }


