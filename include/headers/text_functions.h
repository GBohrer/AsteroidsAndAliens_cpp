#ifndef TEXT_FUNCTIONS_H
#define TEXT_FUNCTIONS_H

#include "../master_header.h"


enum TextBoxId {
    Start,
    Restart,
    Exit,
    Resume,
    Menu,
    Loading,
    Completed
};

typedef struct TextBox {
    TextBoxId id;
    std::string text;
    Rectangle box;
    bool isMouseOn;

    TextBox() {}
    TextBox(TextBoxId i, std::string t, Rectangle b, bool m = false) : id(i), text(t), box(b), isMouseOn(m) {}

} TextBox;

const char * ConvertText (std::string string);
void PrintValueInGame(bool isFloat, float value, Vector2 textPos, int fontSize, Color color);
void PrintTimerInGame(float totalTime, float currentTime, Vector2 textPos, int fontSize);
//void PrintDifficultyInGame(LevelDifficulty ld, Vector2 textPos, int fontSize);

#endif