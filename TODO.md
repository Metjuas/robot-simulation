### Create


### Fix
segfault when clicking start after creating empty sim

CHANGE IT SO ROBOT DOES NOT CREATE NEW MAP RECTANGLE EVERY ITERATION

robot parameters

set proper min and max values for robot parameters (detection distance! so it will not look buggy)


        void setDirection(RotationDirection direction) { this->direction = direction; setSpriteRotation();}
        void setRotation(int rotation) { this->rotationAngle = rotation; setSpriteRotation();}