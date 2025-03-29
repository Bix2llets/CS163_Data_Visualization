#ifndef TEXTUREBUTTON_HPP
#define TEXTUREBUTTON_HPP

#include "button.h"

// * This provides no line wrapping, only box enlargement
class TextureBox : public Button {
    private:
        Texture2D texture;
        Rectangle ori;
    private:
    Button button;
    Vector2 position;
    Vector2 dimension;
    public:
        TextureBox(Vector2 position, Vector2 dimension, Rectangle ori, Texture2D texture, std::string text = "",
            int fontSize = 20, ColorSet palette = DEF_SET)
        : button{position, dimension, text, fontSize,
                palette}, position{position}, dimension{dimension}, ori{ori}, texture{texture} {
                };
    void setDimension(Vector2 dimension);
    void setPosition(Vector2 position);
    void setTexture(Texture2D texture) { this->texture = texture; }
    void setOri(Rectangle ori) { this->ori = ori; }
    void render();
    bool isPressed() const;
};

#endif // TEXTUREBUTTON_HPP