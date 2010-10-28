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
#ifndef __itkMeanSquaresPointSetToImageMetric_h
#define __itkMeanSquaresPointSetToImageMetric_h

#include "itkPointSetToImageMetric.h"
#include "itkCovariantVector.h"
#include "itkPoint.h"

namespace itk
{
/** \class MeanSquaresPointSetToImageMetric
 * \brief Computes similarity between pixel values of a point set and
 * intensity values of an image.
 *
 * This metric computes the average squared differences between pixels
 * in the point set and the transformed set of pixels.
 *
 * Spatial correspondance between both images is established through a
 * Transform.
 *
 * \ingroup RegistrationMetrics
 */
template< class TFixedPointSet, class TMovingImage >
class ITK_EXPORT MeanSquaresPointSetToImageMetric:
  public PointSetToImageMetric< TFixedPointSet, TMovingImage >
{
public:

  /** Standard class typedefs. */
  typedef MeanSquaresPointSetToImageMetric                      Self;
  typedef PointSetToImageMetric< TFixedPointSet, TMovingImage > Superclass;
  typedef SmartPointer< Self >                                  Pointer;
  typedef SmartPointer< const Self >                            ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MeanSquaresPointSetToImageMetric, Object);

  /** Types transferred from the base class */
  typedef typename Superclass::RealType                RealType;
  typedef typename Superclass::TransformType           TransformType;
  typedef typename Superclass::TransformPointer        TransformPointer;
  typedef typename Superclass::TransformParametersType TransformParametersType;
  typedef typename Superclass::TransformJacobianType   TransformJacobianType;
  typedef typename Superclass::GradientPixelType       GradientPixelType;
  typedef typename Superclass::InputPointType          InputPointType;
  typedef typename Superclass::OutputPointType         OutputPointType;

  typedef typename Superclass::MeasureType               MeasureType;
  typedef typename Superclass::DerivativeType            DerivativeType;
  typedef typename Superclass::FixedPointSetType         FixedPointSetType;
  typedef typename Superclass::MovingImageType           MovingImageType;
  typedef typename Superclass::FixedPointSetConstPointer FixedPointSetConstPointer;
  typedef typename Superclass::MovingImageConstPointer   MovingImageConstPointer;

  typedef typename Superclass::PointIterator     PointIterator;
  typedef typename Superclass::PointDataIterator PointDataIterator;

  /** Get the derivatives of the match measure. */
  void GetDerivative(const TransformParametersType & parameters,
                     DerivativeType & Derivative) const;

  /**  Get the value for single valued optimizers. */
  MeasureType GetValue(const TransformParametersType & parameters) const;

  /**  Get value and derivatives for multiple valued optimizers. */
  void GetValueAndDerivative(const TransformParametersType & parameters,
                             MeasureType & Value, DerivativeType & Derivative) const;

protected:
  MeanSquaresPointSetToImageMetric();
  virtual ~MeanSquaresPointSetToImageMetric() {}
private:
  MeanSquaresPointSetToImageMetric(const Self &); //purposely not implemented
  void operator=(const Self &);                   //purposely not implemented
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMeanSquaresPointSetToImageMetric.txx"
#endif

#endif
