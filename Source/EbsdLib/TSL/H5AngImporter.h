/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
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
///////////////////////////////////////////////////////////////////////////////
// This code was partly written under US Air Force Contract FA8650-07-D-5800
///////////////////////////////////////////////////////////////////////////////

#ifndef _H5ANGIMPORTER_H_
#define _H5ANGIMPORTER_H_

#if defined (_MSC_VER)
#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers
#endif


#include "hdf5.h"

#include <vector>
#include <string>

#include "EbsdLib/EbsdLibTypes.h"
#include "EbsdLib/EbsdSetGetMacros.h"
#include "EbsdLib/EbsdImporter.h"
#include "EbsdLib/TSL/AngReader.h"

/**
 * @class H5AngImporter H5AngImporter.h AIM/ANG/H5AngImporter.h
 * @brief
 * @author Michael A. Jackson for BlueQuartz Software
 * @date March 23, 2011
 * @version 1.2
 *
 */
class EbsdLib_EXPORT H5AngImporter : public EbsdImporter
{

  public:
    EBSD_SHARED_POINTERS(H5AngImporter)
    EBSD_TYPE_MACRO(H5AngImporter)
   // EBSD_STATIC_NEW_MACRO(H5AngImporter)
    EBSD_STATIC_NEW_SUPERCLASS(EbsdImporter, H5AngImporter)

    virtual ~H5AngImporter();

    int importFile(hid_t fileId, int index, const std::string &angFile);

    int writePhaseData(AngReader &reader, hid_t gid);

    int writeHKLFamilies(AngPhase* p, hid_t pid);

    virtual void getDims(int &x, int &y);
    virtual void getResolution(float &x, float &y);

  protected:
    H5AngImporter();


  private:
    int xDim;
    int yDim;
    float xRes;
    float yRes;

    H5AngImporter(const H5AngImporter&); // Copy Constructor Not Implemented
    void operator=(const H5AngImporter&); // Operator '=' Not Implemented
};


#endif /* _H5ANGIMPORTER_H_ */
