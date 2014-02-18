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
#ifndef _PrebuiltPipelinesDockWidget_H_
#define _PrebuiltPipelinesDockWidget_H_

#include <QtCore/QDir>
#include <QtGui/QDockWidget>



#include "DREAM3DLib/Common/FilterManager.h"

#include "DREAM3DWidgetsLib/DREAM3DWidgetsLib.h"

#include "ui_PrebuiltPipelinesDockWidget.h"


class QTreeWidget;
class QTreeWidgetItem;
class FilterListDockWidget;

class DREAM3DWidgetsLib_EXPORT  PrebuiltPipelinesDockWidget : public QDockWidget, private Ui::PrebuiltPipelinesDockWidget
{

    enum ItemType
    {
      Default_Item_Type = 0,
      Prebuilt_Item_Type = 2,
      Prebuilt_Category_Item_Type = 4
    };

    Q_OBJECT
public:
    PrebuiltPipelinesDockWidget(QWidget* parent = NULL);
    virtual ~PrebuiltPipelinesDockWidget();

    virtual void setupGui();

    void connectFilterList(FilterListDockWidget *filterListWidget);

protected:
    virtual QDir findPipelinesDirectory();
    virtual void readPipelines();
    virtual void addFiltersRecursively(QDir currentDir, QTreeWidgetItem* currentDirItem);
    virtual QStringList generateFilterListFromPipelineFile(QString path);


protected slots:
    void on_filterLibraryTree_itemClicked( QTreeWidgetItem* item, int column );
    void on_filterLibraryTree_itemChanged( QTreeWidgetItem* item, int column );
    void on_filterLibraryTree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous );
    void on_filterLibraryTree_itemDoubleClicked( QTreeWidgetItem* item, int column );

signals:

    void filterItemDoubleClicked(const QString& filterName);
    void pipelineFileActivated(const QString& filePath);

    void filterListGenerated(const QStringList& filterList);

private:
   // QListWidget* filterList;

    PrebuiltPipelinesDockWidget(const PrebuiltPipelinesDockWidget&); // Copy Constructor Not Implemented
    void operator=(const PrebuiltPipelinesDockWidget&); // Operator '=' Not Implemented


};

#endif