#ifndef TEXTUREBUTTON_HPP
#define TEXTUREBUTTON_HPP

#include "button.h"

// * This provides no line wrapping, only box enlargement
class TextureBox : public Button {
   private:
    Texture2D *texture;
    Rectangle ori;

   private:

   public:
    TextureBox(Vector2 position, Vector2 dimension, Rectangle ori,
               Texture2D *texture, ColorSet const *palette = &BUTTON_SET_1)
        : Button{position, dimension, "", 20, palette},
          ori{ori},
          texture{texture} {};
    void setTexture(Texture2D *texture) { this->texture = texture; }
    void setOri(Rectangle ori) { this->ori = ori; }
    void render();
};

#endif  // TEXTUREBUTTON_HPP