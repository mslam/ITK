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
#ifndef __itkLabelImageToStatisticsLabelMapFilter_txx
#define __itkLabelImageToStatisticsLabelMapFilter_txx

#include "itkLabelImageToStatisticsLabelMapFilter.h"
#include "itkProgressAccumulator.h"

namespace itk
{
template< class TInputImage, class TFeatureImage, class TOutputImage >
LabelImageToStatisticsLabelMapFilter< TInputImage, TFeatureImage, TOutputImage >
::LabelImageToStatisticsLabelMapFilter()
{
  m_BackgroundValue = NumericTraits< OutputImagePixelType >::NonpositiveMin();
  m_ComputeFeretDiameter = false;
  m_ComputePerimeter = true;
  m_NumberOfBins = 128;
  m_ComputeHistogram = true;
  this->SetNumberOfRequiredInputs(2);
}

template< class TInputImage, class TFeatureImage, class TOutputImage >
void
LabelImageToStatisticsLabelMapFilter< TInputImage, TFeatureImage, TOutputImage >
::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // We need all the input.
  InputImagePointer input = const_cast< InputImageType * >( this->GetInput() );
  if ( input )
    {
    input->SetRequestedRegion( input->GetLargestPossibleRegion() );
    }
}

template< class TInputImage, class TFeatureImage, class TOutputImage >
void
LabelImageToStatisticsLabelMapFilter< TInputImage, TFeatureImage, TOutputImage >
::EnlargeOutputRequestedRegion(DataObject *)
{
  this->GetOutput()
  ->SetRequestedRegion( this->GetOutput()->GetLargestPossibleRegion() );
}

template< class TInputImage, class TFeatureImage, class TOutputImage >
void
LabelImageToStatisticsLabelMapFilter< TInputImage, TFeatureImage, TOutputImage >
::GenerateData()
{
  // Create a process accumulator for tracking the progress of this minipipeline
  ProgressAccumulator::Pointer progress = ProgressAccumulator::New();

  progress->SetMiniPipelineFilter(this);

  // Allocate the output
  this->AllocateOutputs();

  typename LabelizerType::Pointer labelizer = LabelizerType::New();
  labelizer->SetInput( this->GetInput() );
  labelizer->SetBackgroundValue(m_BackgroundValue);
  labelizer->SetNumberOfThreads( this->GetNumberOfThreads() );
  progress->RegisterInternalFilter(labelizer, .5f);

  typename LabelObjectValuatorType::Pointer valuator = LabelObjectValuatorType::New();
  valuator->SetInput( labelizer->GetOutput() );
  valuator->SetFeatureImage( this->GetFeatureImage() );
  valuator->SetNumberOfThreads( this->GetNumberOfThreads() );
  valuator->SetComputePerimeter(m_ComputePerimeter);
  valuator->SetComputeFeretDiameter(m_ComputeFeretDiameter);
  valuator->SetComputeHistogram(m_ComputeHistogram);
  valuator->SetNumberOfBins(m_NumberOfBins);
  progress->RegisterInternalFilter(valuator, .5f);

  valuator->GraftOutput( this->GetOutput() );
  valuator->Update();
  this->GraftOutput( valuator->GetOutput() );
}

template< class TInputImage, class TFeatureImage, class TOutputImage >
void
LabelImageToStatisticsLabelMapFilter< TInputImage, TFeatureImage, TOutputImage >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "BackgroundValue: "
     << static_cast< typename NumericTraits< OutputImagePixelType >::PrintType >( m_BackgroundValue ) << std::endl;
  os << indent << "ComputeFeretDiameter: " << m_ComputeFeretDiameter << std::endl;
  os << indent << "ComputePerimeter: " << m_ComputePerimeter << std::endl;
  os << indent << "ComputeHistogram: " << m_ComputeHistogram << std::endl;
  os << indent << "NumberOfBins: " << m_NumberOfBins << std::endl;
}
} // end namespace itk
#endif
