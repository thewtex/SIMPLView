/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
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
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
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
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "SIMPLViewUserManualDialog.h"

#include <QtCore/QFileInfo>
#include <QtCore/QDir>

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QAction>

#include <QtWebEngineWidgets/QWebEngineHistory>

#include "SIMPLib/Common/FilterManager.h"

#include "QtSupportLib/SIMPLViewHelpUrlGenerator.h"

// Include the MOC generated CPP file which has all the QMetaObject methods/data
#include "moc_SIMPLViewUserManualDialog.cpp"

SIMPLViewUserManualDialog* SIMPLViewUserManualDialog::self = NULL;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SIMPLViewUserManualDialog::SIMPLViewUserManualDialog(QWidget* parent) :
  QDialog(parent)
{
  Q_ASSERT_X(!self, "SIMPLViewUserManualDialog", "There should be only one SIMPLViewUserManualDialog object");

  setupUi(this);
  SIMPLViewUserManualDialog::self = this;

  // Create the web view
  m_WebView = new QWebEngineView(this);
  m_WebView->setObjectName(QStringLiteral("m_WebView"));
  QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(m_WebView->sizePolicy().hasHeightForWidth());
  m_WebView->setSizePolicy(sizePolicy1);
  m_WebView->setUrl(QUrl(QStringLiteral("about:blank")));
  gridLayout->addWidget(m_WebView, 2, 0, 1, 1);

  self->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

#if defined (Q_OS_MAC)
  QAction* closeAction = new QAction(this);
  closeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
  addAction(closeAction);
#endif

  connect(m_WebView, SIGNAL(loadFinished(bool)), this, SLOT(updateButtons(bool)));
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SIMPLViewUserManualDialog::~SIMPLViewUserManualDialog() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SIMPLViewUserManualDialog* SIMPLViewUserManualDialog::Instance(QWidget* parent)
{
  if (self == NULL)
  {
    self = new SIMPLViewUserManualDialog(parent);
  }
  return self;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QWebEngineView* SIMPLViewUserManualDialog::getWebView()
{
  return m_WebView;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLViewUserManualDialog::LaunchHelpDialog(QUrl url)
{
  SIMPLViewUserManualDialog* dialog = SIMPLViewUserManualDialog::Instance();
  dialog->getWebView()->load(url);

  if (dialog->isVisible() == false)
  {
    dialog->show();
  }

  dialog->activateWindow();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLViewUserManualDialog::LaunchHelpDialog(QString className)
{
  // Generate help page
  QUrl helpURL = SIMPLViewHelpUrlGenerator::generateHTMLUrl(className.toLower());
  SIMPLViewUserManualDialog::LaunchHelpDialog(helpURL);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLViewUserManualDialog::on_backBtn_pressed()
{
  m_WebView->back();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLViewUserManualDialog::on_forwardBtn_pressed()
{
  m_WebView->forward();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLViewUserManualDialog::on_refreshBtn_pressed()
{
  m_WebView->reload();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SIMPLViewUserManualDialog::updateButtons(bool ok)
{
  QWebEngineHistory* history = m_WebView->history();

  // Check forwards navigation
  if (history->canGoForward() == false)
  {
    forwardBtn->setDisabled(true);
  }
  else
  {
    forwardBtn->setEnabled(true);
  }

  // Check backwards navigation
  if (history->canGoBack() == false || history->backItem().url().toDisplayString() == "about:blank")
  {
    backBtn->setDisabled(true);
  }
  else
  {
    backBtn->setEnabled(true);
  }
}







