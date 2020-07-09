/**
 * Application Window class
 *
 * @package     CRSS
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */

#include <string>
#include <vector>
#include <ncurses.h>

#ifndef CRSS_APPLICATIONWINDOW_H
#define CRSS_APPLICATIONWINDOW_H

using namespace std;
namespace crss
{
    class ApplicationWindow
    {
    public:
        ApplicationWindow();
        ~ApplicationWindow();

        void show();
        void update();
        void clear();
        void scrollDown();
        void scrollUp();

        void setPosition(int y, int x);
        void setDimensions(int height, int width);
        void pushContent(string c);

        void increaseHighlight(int choice, int count);
        void decreaseHighlight(int choice, int count);

        WINDOW *getWindow();

    private:
        bool created;
        int y, x;
        int height, width;
        int offsetTop;
        int highlight;
        vector<string> content;
        WINDOW *win, *pad;

        bool _create();
        void _printWindow();
        void _printPad();
        void _printContent();
    };
}

#endif //CCRSS_APPLICATIONWINDOW_H