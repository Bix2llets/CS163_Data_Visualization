#ifndef FORM_HPP
#define FORM_HPP

#include "Form.h" // Ensure the correct case matches the actual file name

class mForm : public Form { // Ensure 'Form' is a valid base class
    private : 
        bool mode;
        int maxSize;
    public :
        mForm(Rectangle drawInfo, bool mode, int maxSize, ColorSet palette = DEF_SET) 
        : Form(drawInfo, palette), 
        mode{mode}, 
        maxSize{maxSize} {};
        virtual void recordKeyboard();
};

#endif // FORM_HPP