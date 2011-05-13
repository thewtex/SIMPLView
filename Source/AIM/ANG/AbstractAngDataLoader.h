/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2010, Dr. Michael A. Grober (US Air Force Research Laboratories
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef _AbstractAngReader_h_
#define _AbstractAngReader_h_


#include "MXA/Common/MXASetGetMacros.h"
#include "AIM/Common/AIMCommonConfiguration.h"
#include "AIM/Common/ReconstructionVoxel.h"



class AIMCOMMON_EXPORT AbstractAngDataLoader
{

  public:
    MXA_SHARED_POINTERS(AbstractAngDataLoader)
    MXA_TYPE_MACRO(AbstractAngDataLoader)

    virtual ~AbstractAngDataLoader() {}

    virtual int loadData(ReconstructionVoxel voxels[],
                         int xpoints, int ypoints, int zpoints) = 0;

    virtual int getSizeAndResolution(int &xpoints, int &ypoints, int &zpoints,
                                       float &xres, float &yres, float &zres) = 0;


  protected:
    AbstractAngDataLoader() {};

  private:
    AbstractAngDataLoader(const AbstractAngDataLoader&); // Copy Constructor Not Implemented
    void operator=(const AbstractAngDataLoader&); // Operator '=' Not Implemented

};



#endif /* _AbstractAngReader_h_  */
