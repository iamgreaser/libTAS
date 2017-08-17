/*
    Copyright 2015-2016 Clément Gallet <clement.gallet@ens-lyon.org>

    This file is part of libTAS.

    libTAS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libTAS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libTAS.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LINTAS_MAINWINDOW_H_INCLUDED
#define LINTAS_MAINWINDOW_H_INCLUDED

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Check_Button.H>
#include <Fl/Fl_Menu_Bar.H>
#include <Fl/Fl_Menu_Item.H>
#include <Fl/Fl_Pack.H>
#include <Fl/Fl_Radio_Round_Button.H>
#include <thread>

#include "../Context.h"
#include "EncodeWindow.h"
#include "ExecutableWindow.h"
#include "InputWindow.h"
#include "ControllerWindow.h"

class MainWindow {
    public:
        /* Implement a Singleton pattern */
        static MainWindow& getInstance()
        {
            static MainWindow instance;
            return instance;
        }

        MainWindow(MainWindow const&) = delete;
        void operator=(MainWindow const&) = delete;

        void build(Context* c);

        std::thread game_thread;
        Context *context;
        Fl_Double_Window *window;

        Fl_Menu_Bar *menu_bar;
        static Fl_Menu_Item menu_items[];

#ifdef LIBTAS_ENABLE_AVDUMPING
        EncodeWindow* encode_window;
#endif
        InputWindow* input_window;
        ExecutableWindow* executable_window;
        ControllerWindow* controller_window;

        Fl_Button *launch;
        Fl_Button *launch_gdb;

        Fl_Output *gamepath;
        Fl_Button *browsegamepath;
        Fl_Native_File_Chooser *gamepathchooser;
        Fl_Input *cmdoptions;

        Fl_Output *moviepath;
        Fl_Button *browsemoviepath;
        Fl_Native_File_Chooser *moviepathchooser;

        Fl_Check_Button *movie_recording;
        Fl_Check_Button *movie_read_only;

        Fl_Int_Input *logicalfps;

        Fl_Check_Button *pausecheck;
        Fl_Check_Button *fastforwardcheck;

        Fl_Check_Button *mutecheck;

        Fl_Output *framecount;
        Fl_Output *movie_framecount;
        Fl_Output *rerecord_count;

        Fl_Input *initial_time_sec;
        Fl_Input *initial_time_nsec;

        /* Update UI elements (mainly enable/disable) depending on
         * the game status (running/stopped), to prevent modifying values that
         * are not supposed to be modified when the game is running.
         */
        void update_status();

        /* Update UI elements, when the game is running, that may have been
         * modified by hotkeys or messages from the game.
         */
        void update_ui();

        /* Update frame count and time */
        void update_framecount_time();

        /* Update rerecord count */
        void update_rerecordcount();

        /* Update UI elements when a config file is loaded */
        void update_config();

    private:
        MainWindow() {}
        ~MainWindow();
};

/* The launch callback is exposed because the other thread may want to
 * trigger a game restart using this callback in case of PseudoSaveState
 */
Fl_Callback0 launch_cb;

void alert_dialog(void* alert_msg);

#endif
