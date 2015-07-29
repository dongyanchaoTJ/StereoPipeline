// __BEGIN_LICENSE__
//  Copyright (c) 2006-2013, United States Government as represented by the
//  Administrator of the National Aeronautics and Space Administration. All
//  rights reserved.
//
//  The NASA Vision Workbench is licensed under the Apache License,
//  Version 2.0 (the "License"); you may not use this file except in
//  compliance with the License. You may obtain a copy of the License at
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// __END_LICENSE__


/// \file stereo_gui_MainWindow.h
///
/// The Vision Workbench image viewer main window class.
///
#ifndef __STEREO_GUI_MAINWINDOW_H__
#define __STEREO_GUI_MAINWINDOW_H__

#include <QMainWindow>
#include <string>
#include <vector>

// Boost
#include <boost/program_options.hpp>

#include <vw/Math/Vector.h>
#include <vw/InterestPoint/InterestData.h>

// Forward declarations
class QAction;
class QLabel;
class QTabWidget;

namespace vw {
  namespace gui {

  class MainWidget;
  class chooseFilesDlg;

  class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(std::vector<std::string> const& images,
               std::string const& output_prefix,
               vw::Vector2i const& window_size,
               bool ignore_georef, bool hillshade, int argc, char ** argv);
    virtual ~MainWindow() {}

  private slots:
    void forceQuit(); // Ensure the program shuts down.
    void sizeToFit();
    void viewMatches();
    void hideMatches();
    void saveMatches();
    void run_stereo();
    void run_parallel_stereo();
    void shadow_threshold_tool();
    void about();

  protected:
    void keyPressEvent(QKeyEvent *event);

  private:

    void run_stereo_or_parallel_stereo(std::string const& cmd);

    void create_menus();

    // Event handlers
    void resizeEvent(QResizeEvent *);
    void closeEvent (QCloseEvent *);

    std::vector<std::string> m_images;
    std::string m_output_prefix;
    double           m_widRatio;    // ratio of sidebar to entire win wid
    MainWidget     * m_main_widget;
    std::vector<MainWidget*>  m_widgets;
    chooseFilesDlg * m_chooseFiles; // left sidebar for selecting files

    QMenu *m_file_menu;
    QMenu *m_view_menu;
    QMenu *m_matches_menu;
    QMenu *m_tools_menu;
    QMenu *m_help_menu;

    QAction *m_about_action;
    QAction *m_shadow_action;
    QAction *m_sizeToFit_action;
    QAction *m_viewMatches_action;
    QAction *m_hideMatches_action;
    QAction *m_saveMatches_action;
    QAction *m_run_stereo_action;
    QAction *m_run_parallel_stereo_action;
    QAction *m_exit_action;

    int m_argc;
    char ** m_argv;
    bool m_matches_were_loaded;
    std::vector<std::vector<vw::ip::InterestPoint> > m_matches;

  };

}} // namespace vw::gui

#endif // __STEREO_GUI_MAINWINDOW_H__
