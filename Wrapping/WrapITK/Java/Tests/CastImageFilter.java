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

/**
 *  Example on the use of the CastImageFilter
 *
 */

import InsightToolkit.*;

public class CastImageFilter
{
  public static void main( String argv[] )
  {
    System.out.println("CastImageFilter Example");

    itkImageFileReaderIUC2_Pointer reader = itkImageFileReaderIUC2.itkImageFileReaderIUC2_New();
    itkImageFileWriterIUS2_Pointer writer = itkImageFileWriterIUS2.itkImageFileWriterIUS2_New();

    itkCastImageFilterIUC2IUS2_Pointer filter = itkCastImageFilterIUC2IUS2.itkCastImageFilterIUC2IUS2_New();

    filter.SetInput( reader.GetOutput() );
    writer.SetInput( filter.GetOutput() );

    reader.SetFileName( argv[0] );
    writer.SetFileName( argv[1] );

    writer.Update();
  }

}


