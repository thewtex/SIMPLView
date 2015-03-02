/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
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
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
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
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef _IGeometry_H_
#define _IGeometry_H_

#include <vector>
#include <map>
#include <sstream>
#include <list>

#include <QtCore/QSet>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QMap>

#include "H5Support/QH5Utilities.h"
#include "H5Support/HDF5ScopedFileSentinel.h"
#include "H5Support/QH5Lite.h"

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/Common/Observable.h"
#include "DREAM3DLib/DataArrays/DynamicListArray.hpp"
#include "DREAM3DLib/DataArrays/DataArray.hpp"
#include "DREAM3DLib/DataContainers/AttributeMatrix.h"
#include "DREAM3DLib/HDF5/VTKH5Constants.h"

// -----------------------------------------------------------------------------
// Typedefs
// -----------------------------------------------------------------------------

typedef FloatArrayType SharedVertexList;
typedef Int64ArrayType SharedEdgeList;
typedef Int64ArrayType SharedTriList;
typedef Int64ArrayType SharedQuadList;
typedef UInt16Int64DynamicListArray CellDynamicList;

/**
 * @brief The IGeometry class
 */
class DREAM3DLib_EXPORT IGeometry : public Observable
{
  public:
    DREAM3D_SHARED_POINTERS(IGeometry)
    DREAM3D_TYPE_MACRO_SUPER(IGeometry, Observable)

    IGeometry();
    virtual ~IGeometry();

    /**
     * @brief AttributeMatrixMap_t
     */
    typedef QMap<QString, AttributeMatrix::Pointer> AttributeMatrixMap_t;

// -----------------------------------------------------------------------------
// Connectivity
// -----------------------------------------------------------------------------

    /**
     * @brief findElementsContainingVert
     * @return
     */
    virtual int findElementsContainingVert() = 0;

    /**
     * @brief getElementsContainingVert
     * @return
     */
    virtual CellDynamicList::Pointer getElementsContainingVert() = 0;

    /**
     * @brief deleteElementsContainingVert
     */
    virtual void deleteElementsContainingVert() = 0;

    /**
     * @brief findElementNeighbors
     * @return
     */
    virtual int findElementNeighbors() = 0;

    /**
     * @brief getElementNeighbors
     * @return
     */
    virtual CellDynamicList::Pointer getElementNeighbors() = 0;

    /**
     * @brief deleteElementNeighbors
     */
    virtual void deleteElementNeighbors() = 0;

// -----------------------------------------------------------------------------
// Topology
// -----------------------------------------------------------------------------

    /**
     * @brief getNumberOfTuples
     * @return
     */
    virtual size_t getNumberOfTuples() = 0;

    /**
     * @brief findElementCentroids
     * @return
     */
    virtual int findElementCentroids() = 0;

    /**
     * @brief getElementCentroids
     * @return
     */
    virtual FloatArrayType::Pointer getElementCentroids() = 0;

    /**
     * @brief deleteElementCentroids
     */
    virtual void deleteElementCentroids() = 0;

// -----------------------------------------------------------------------------
// Generic
// -----------------------------------------------------------------------------

    /**
     * @brief setName
     * @param name
     */
    virtual void setName(const QString& name) = 0;

    /**
     * @brief getName
     * @return
     */
    virtual QString getName() = 0;

    /**
     * @brief getGeometryType
     * @return
     */
    virtual unsigned int getGeometryType() = 0;

    /**
     * @brief getGeometryTypeAsString
     * @return
     */
    virtual QString getGeometryTypeAsString() = 0;

    /**
     * @brief getXdmfGridType
     * @return
     */
    virtual unsigned int getXdmfGridType() = 0;

    /**
     * @brief getUnitDimensionality
     * @return
     */
    virtual unsigned int getUnitDimensionality() = 0;

    /**
     * @brief setSpatialDimensionality
     * @param spatialDims
     */
    virtual void setSpatialDimensionality(unsigned int spatialDims) = 0;

    /**
     * @brief getSpatialDimensionality
     * @return
     */
    virtual unsigned int getSpatialDimensionality() = 0;

    /**
     * @brief writeGeometryToHDF5
     * @param parentId
     * @param writeXdmf
     * @return
     */
    virtual int writeGeometryToHDF5(hid_t parentId, bool writeXdmf) = 0;

    /**
     * @brief writeXdmf
     * @param out
     * @param dcName
     * @param hdfFileName
     * @return
     */
    virtual int writeXdmf(QTextStream& out, QString dcName, QString hdfFileName) = 0;

    /**
     * @brief readGeometryFromHDF5
     * @param parentId
     * @param preflight
     * @return
     */
    virtual int readGeometryFromHDF5(hid_t parentId, bool preflight) = 0;

    /**
     * @brief deepCopy
     * @return
     */
    virtual Pointer deepCopy() = 0;

    /**
     * @brief initializeWithZeros
     */
    virtual void initializeWithZeros() = 0;

    /**
     * @brief addAttributeMatrix
     */
    virtual void addAttributeMatrix(const QString& name, AttributeMatrix::Pointer data) = 0;

    /**
     * @brief getAttributeMatrix
     * @param name
     * @return
     */
    virtual AttributeMatrix::Pointer getAttributeMatrix(const QString& name) = 0;

    /**
     * @brief removeAttributeMatrix
     * @param name
     * @return
     */
    virtual AttributeMatrix::Pointer removeAttributeMatrix(const QString& name) = 0;

  protected:

    /**
     * @brief setElementsContaingVert
     * @param elementsContaingVert
     */
    virtual void setElementsContainingVert(CellDynamicList::Pointer elementsContainingVert) = 0;

    /**
     * @brief setElementNeighbors
     * @param elementNeighbors
     */
    virtual void setElementNeighbors(CellDynamicList::Pointer elementsNeighbors) = 0;

    /**
     * @brief setElementCentroids
     * @param elementCentroids
     */
    virtual void setElementCentroids(FloatArrayType::Pointer elementCentroids) = 0;

  private:

    QString m_Name;
    QString m_GeometryTypeName;
    unsigned int m_GeometryType;
    unsigned int m_XdmfGridType;
    unsigned int m_UnitDimensionality;
    unsigned int m_SpatialDimensionality;
    AttributeMatrixMap_t m_AttributeMatrices;

    IGeometry(const IGeometry&); // Copy Constructor Not Implemented
    void operator=(const IGeometry&); // Operator '=' Not Implemented
};

#endif /* _IGeometry_H_ */

