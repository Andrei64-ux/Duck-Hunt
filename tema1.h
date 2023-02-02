#pragma once

#include "components/simple_scene.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
         float cx, cy;
         float scoreX, scoreY;
         glm::mat3 modelMatrix;
         float translateX, translateY;
         float translateHeadX, translateHeadY;
         float translateBodyX, translateBodyY;
         float translateBeakX, translateBeakY;
         float translateLeftWingX, translateLeftWingY;
         float translateRightWingX, translateRightWingY;
         float scaleX, scaleY;
         float angularStep;
         float angularStepLeft;
         float angularStepRight;
         float leftBottomCorner;
         float rightBottomCorner;
         float leftUpCorner;
         float rightUpCorner;
         int livesCount;
         int bulletCount;
         int bulletLength;
         float duckSpeedX;
         float duckSpeedY;
         int checkVertical;
         int checkHorizontally;
         int touchEdgeLeftOrRight;
         int isAlive;
         int duckShot;
         int sound;
         int speedUp;
         int cloudNumber;
         float timeSpent;
         int eliberateDuck;
         int upper, lower;
         int duck_number;
         int duck_kill;
         float squareX, squareY, faceX, faceY;
         int duck_hit, duck_miss;
         int duck_count;
         int v0X, v0Y;
         //int ok1, ok2, ok3, ok4;
        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
