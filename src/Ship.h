#ifndef SHIP_H
#define SHIP_H


const float shipWidth = 8;
const float shipHeight = 10;
const float shipBot = -4;

const float shipX = -80;
const float shipY = -80;

const float shipCentreOffset = 11;

class Ship {
    public:
        Ship();

        ~Ship();

        int getShipHeight();
        int getShipWidth();


        int getRotation();
        void setRotation(int newRotation);

        float getShipX();
        float getShipY();

        void moveFoward(float dt);
        void moveBackward();

        void setX(float x);
        void setY(float y);

        void resetShipValues();

    private:
        float shipWidth;
        float shipHeight;
        float shipBot;

        float shipX;
        float shipY;

        //**RF to separate keyboard/input helper class later
        bool wKeyPressed;
        bool aKeyPressed;
        bool dKeyPressed;

        int rotation;
        int velocity;

        int shipFill[3];
        int shipOutline[3];


};

#endif