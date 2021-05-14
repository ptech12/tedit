#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
// definitions
// #define STDIN_FILENO in;
// termios struct origin_termios model
struct termios origin_termios;

// Method to disable RAW mode on exit
void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios);

}

// Method to enable RAW mode in terminal
// To turn off ECHO mode
void enableRawMode()
{
    // getting attrib for origin model 
    tcgetattr(STDIN_FILENO, &origin_termios);
    
    //disabling raw mode on exit
    atexit(disableRawMode);
    
    //making a local termios raw from origin model
    struct termios raw = origin_termios;

    // Changing control flag for ECHO and Canonical Mode
    raw.c_lflag &= ~(ECHO | ICANON);

    // setting attrib
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main()
{
    // Enabling raw mode before reading characters
    enableRawMode();
    // char variable
    char c;
    // reading character from terminal and exit on pressing q
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
    {
        // checking for control character
        if(iscntrl(c))
        {
            printf("%d\n", c);
        }else{
            // printing both its ASCII numeric code and it's character value
            printf("%d ('%c')\n", c, c);
        }
    }
    return 0;
}