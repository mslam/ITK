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
#ifndef __itkMeanImageFunction_txx
#define __itkMeanImageFunction_txx

#include "itkMeanImageFunction.h"
#include "itkConstNeighborhoodIterator.h"

namespace itk
{
/**
 * Constructor
 */
template< class TInputImage, class TCoordRep >
MeanImageFunction< TInputImage, TCoordRep >
::MeanImageFunction()
{
  m_NeighborhoodRadius = 1;
}

/**
 *
 */
template< class TInputImage, class TCoordRep >
void
MeanImageFunction< TInputImage, TCoordRep >
::PrintSelf(std::ostream & os, Indent indent) const
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "NeighborhoodRadius: "  << m_NeighborhoodRadius << std::endl;
}

/**
 *
 */
template< class TInputImage, class TCoordRep >
typename MeanImageFunction< TInputImage, TCoordRep >
::RealType
MeanImageFunction< TInputImage, TCoordRep >
::EvaluateAtIndex(const IndexType & index) const
{
  RealType sum;

  sum = NumericTraits< RealType >::Zero;

  if ( !this->GetInputImage() )
    {
    return ( NumericTraits< RealType >::max() );
    }

  if ( !this->IsInsideBuffer(index) )
    {
    return ( NumericTraits< RealType >::max() );
    }

  // Create an N-d neighborhood kernel, using a zeroflux boundary condition
  typename InputImageType::SizeType kernelSize;
  kernelSize.Fill(m_NeighborhoodRadius);

  ConstNeighborhoodIterator< InputImageType >
  it( kernelSize, this->GetInputImage(), this->GetInputImage()->GetBufferedRegion() );

  // Set the iterator at the desired location
  it.SetLocation(index);

  // Walk the neighborhood
  const unsigned int size = it.Size();
  for ( unsigned int i = 0; i < size; ++i )
    {
    sum += static_cast< RealType >( it.GetPixel(i) );
    }
  sum /= double( it.Size() );

  return ( sum );
}
} // end namespace itk

#endif
