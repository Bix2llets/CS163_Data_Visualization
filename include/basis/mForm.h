#ifndef FORM_HPP
#define FORM_HPP

#include "Form.h" 

class mForm : public Form { 
    private : 
        bool mode;
        int maxSize;
    public :
        mForm(Rectangle drawInfo, ColorSet palette = DEF_SET, bool mode = 0, int maxSize = 100) 
        : Form(drawInfo, palette), 
        mode{mode}, 
        maxSize{maxSize} {};
        virtual void recordKeyboard();
        virtual std::string getText() {
            std::string res = text;
            text = "";
            return res;
        }
        void setText(std::string text) {
            this->text = text;
        };
};

#endif // FORM_HPP