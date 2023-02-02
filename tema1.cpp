#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <time.h> 
#include <windows.h>
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"

using namespace std;
using namespace m1;

float rotateBeak, rotateBody, rotateLeftW, rotateRightW;
/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float length = 100;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    upper = 1200;
    lower = 30;

    // HEAD COORDINATES
    translateHeadX = (rand() % (upper - lower + 1)) + lower;;
    translateHeadY = 120;
    
    translateBodyX = translateHeadX - 30;
    translateBeakX = translateHeadX - 5;
    translateLeftWingX = translateHeadX - 50;
    translateRightWingX = translateHeadX + 10;
    leftBottomCorner = translateHeadX - 50;
    rightBottomCorner = translateHeadX + 50;

    translateBodyY = translateHeadY - 70;
    translateBeakY = translateHeadY + 20;
    translateLeftWingY = translateHeadY - 55;
    translateRightWingY = translateHeadY - 55;
    leftUpCorner = translateHeadY - 70;
    rightUpCorner = translateHeadY + 35;

    // SCALE SCORE FACTORS
    scaleX = 1;
    scaleY = 1;

    // ANGULAR STEP
    angularStep = 0;
    
    rotateBeak = 0;
    rotateBody = 0;
    rotateLeftW = 0;
    rotateRightW = 0;
    // ANGULAR STEP FOR LEFT WING AND RIGHT WING
    angularStepLeft = 0;
    angularStepRight = 0;
    
    livesCount = 3;
    bulletCount = 3;
    bulletLength = 10;

    duckSpeedX = 0.2;
    duckSpeedY = 0.2;
    timeSpent = 5;

    checkVertical = 1;
    checkHorizontally = 1;

    // DUCK LIVES
    isAlive = 1;

    // DUCK TOUCH THE EDGES
    touchEdgeLeftOrRight = 0;

    // DUCK DIED
    duckShot = 0;

    // DUCK SOUND
    sound = 1;
    duck_miss = 0;
    duck_hit = 0;

    speedUp = 1;
    cloudNumber = 3;
    timeSpent = 0;
    eliberateDuck = 0;
    duck_number = 0;
    duck_kill = 0;
    squareX = 475;
    squareY = 300;
    faceX = 600;
    faceY = 400;
    duck_count = 0;
    srand(time(NULL));

    // Creare dreptungi contur rata
    Mesh* outline = object2D::CreateRectangle("outline", glm::vec3(0, 0, 0), 100, 110, glm::vec3(0.5, 0.9, 0.7), false);
    AddMeshToList(outline);

    // Creare glont
    Mesh* bullet = object2D::CreateRectangle("bullet", glm::vec3(0, 0, 0), bulletLength, bulletLength * 2, glm::vec3(0, 1, 0), true);
    AddMeshToList(bullet);

    // Creare contur bara de scor
    Mesh* scoreBar = object2D::CreateRectangle("scoreBar", glm::vec3(980, 650, 0), 200, 30, glm::vec3(1, 1, 0.5), false);
    AddMeshToList(scoreBar);

    // Creare bara full de scor
    Mesh* scoreBarFull = object2D::CreateRectangle("scoreBarFull", glm::vec3(0, 0, 0), 150, 30, glm::vec3(1, 1, 0.5), true);
    AddMeshToList(scoreBarFull);

    // Creare aripa cap
    Mesh* head = object2D::CreateCircle("head", glm::vec3(0, 0, 0), 20, glm::vec3(0, 0.7, 0), true);
    AddMeshToList(head);

    // Creare aripa corp
    Mesh* body = object2D::CreateTriangle("body", glm::vec3(0, 0, 0), 60, glm::vec3(0.56, 0.27, 0.07), true);
    AddMeshToList(body);

    // Creare cioc
    Mesh* beak = object2D::CreateTriangle("beak", glm::vec3(0, 0, 0), 15, glm::vec3(0.6, 0.4, 0), true);
    AddMeshToList(beak);

    // Creare aripa stanga
    Mesh* left_wing = object2D::CreateTriangle("left_wing", glm::vec3(0, 0, 0), 40, glm::vec3(0.56, 0.27, 0.07), true);
    AddMeshToList(left_wing);

    // Creare aripa dreapta
    Mesh* right_wing = object2D::CreateTriangle("right_wing", glm::vec3(0, 0, 0), 40, glm::vec3(0.56, 0.27, 0.07), true);
    AddMeshToList(right_wing);

    // Creare aripa cap
    Mesh* head1 = object2D::CreateCircle("head1", glm::vec3(0, 0, 0), 20, glm::vec3(0.33, 0.7, 0.23), true);
    AddMeshToList(head1);

    // Creare aripa corp
    Mesh* body1 = object2D::CreateTriangle("body1", glm::vec3(0, 0, 0), 60, glm::vec3(0.56, 0.87, 0.47), true);
    AddMeshToList(body1);

    // Creare cioc
    Mesh* beak1 = object2D::CreateTriangle("beak1", glm::vec3(0, 0, 0), 15, glm::vec3(0.6, 0.4, 0.3), true);
    AddMeshToList(beak1);

    // Creare aripa stanga
    Mesh* left_wing1 = object2D::CreateTriangle("left_wing1", glm::vec3(0, 0, 0), 40, glm::vec3(0, 0.44, 0.37), true);
    AddMeshToList(left_wing1);

    // Creare aripa dreapta
    Mesh* right_wing1 = object2D::CreateTriangle("right_wing1", glm::vec3(0, 0, 0), 40, glm::vec3(0, 0.44, 0.37), true);
    AddMeshToList(right_wing1);

    // Creare aripa cap
    Mesh* head2 = object2D::CreateCircle("head2", glm::vec3(0, 0, 0), 20, glm::vec3(1, 0.7, 0.3), true);
    AddMeshToList(head2);

    // Creare aripa corp
    Mesh* body2 = object2D::CreateTriangle("body2", glm::vec3(0, 0, 0), 60, glm::vec3(0.2, 0.17, 0.77), true);
    AddMeshToList(body2);

    // Creare cioc
    Mesh* beak2 = object2D::CreateTriangle("beak2", glm::vec3(0, 0, 0), 15, glm::vec3(0.6, 0.4, 0.9), true);
    AddMeshToList(beak2);

    // Creare aripa stanga
    Mesh* left_wing2 = object2D::CreateTriangle("left_wing2", glm::vec3(0, 0, 0), 40, glm::vec3(0, 0, 0), true);
    AddMeshToList(left_wing2);

    // Creare aripa dreapta
    Mesh* right_wing2 = object2D::CreateTriangle("right_wing2", glm::vec3(0, 0, 0), 40, glm::vec3(0, 0, 0), true);
    AddMeshToList(right_wing2);

    // Creare aripa cap
    Mesh* head3 = object2D::CreateCircle("head3", glm::vec3(0, 0, 0), 20, glm::vec3(0.87, 0.22, 0.23), true);
    AddMeshToList(head3);

    // Creare aripa corp
    Mesh* body3 = object2D::CreateTriangle("body3", glm::vec3(0, 0, 0), 60, glm::vec3(0.77, 0.32, 0.17), true);
    AddMeshToList(body3);

    // Creare cioc
    Mesh* beak3 = object2D::CreateTriangle("beak3", glm::vec3(0, 0, 0), 15, glm::vec3(0.612, 0.11, 0.99), true);
    AddMeshToList(beak3);

    // Creare aripa stanga
    Mesh* left_wing3 = object2D::CreateTriangle("left_wing3", glm::vec3(0, 0, 0), 40, glm::vec3(0.21, 0.44, 0.37), true);
    AddMeshToList(left_wing3);

    // Creare aripa dreapta
    Mesh* right_wing3 = object2D::CreateTriangle("right_wing3", glm::vec3(0, 0, 0), 40, glm::vec3(0.21, 0.44, 0.37), true);
    AddMeshToList(right_wing3);

    // Creare aripa cap
    Mesh* head4 = object2D::CreateCircle("head4", glm::vec3(0, 0, 0), 20, glm::vec3(0.25, 0.87, 0.55), true);
    AddMeshToList(head4);

    // Creare aripa corp
    Mesh* body4 = object2D::CreateTriangle("body4", glm::vec3(0, 0, 0), 60, glm::vec3(0.14, 0.76, 0.77), true);
    AddMeshToList(body4);

    // Creare cioc
    Mesh* beak4 = object2D::CreateTriangle("beak4", glm::vec3(0, 0, 0), 15, glm::vec3(0.942, 0.66, 0.12), true);
    AddMeshToList(beak4);

    // Creare aripa stanga
    Mesh* left_wing4 = object2D::CreateTriangle("left_wing4", glm::vec3(0, 0, 0), 40, glm::vec3(0.18, 0.97, 0.14), true);
    AddMeshToList(left_wing4);

    // Creare aripa dreapta
    Mesh* right_wing4 = object2D::CreateTriangle("right_wing4", glm::vec3(0, 0, 0), 40, glm::vec3(0.18, 0.97, 0.14), true);
    AddMeshToList(right_wing4);

    // Creare margine stanga
    Mesh* left_edge = object2D::CreateRectangle("left_edge", glm::vec3(0, 100, 0), 10, 620, glm::vec3(0, 1, 0), true);
    AddMeshToList(left_edge);

    // Creare margine dreapta
    Mesh* right_edge = object2D::CreateRectangle("right_edge", glm::vec3(1270, 100, 0), 10, 620, glm::vec3(0, 1, 0), true);
    AddMeshToList(right_edge);

    // Creare margine sus
    Mesh* top_edge = object2D::CreateRectangle("top_edge", glm::vec3(0, 710, 0), 1280, 10, glm::vec3(0, 1, 0), true);
    AddMeshToList(top_edge);

    // Creare margine jos
    Mesh* bottom_edge = object2D::CreateRectangle("bottom_edge", glm::vec3(0, 0, 0), 1280, 150, glm::vec3(0, 1, 0), true);
    AddMeshToList(bottom_edge);

    // Creare cer
    Mesh* sky = object2D::CreateRectangle("sky", glm::vec3(0, 150, 0), 1280, 570, glm::vec3(0.5, 0.9, 0.7), true);
    AddMeshToList(sky);

    // Creare vieti
    Mesh* life = object2D::CreateCircle("life", glm::vec3(0, 0, 0), 10.0f, glm::vec3(1, 0, 0), true);
    AddMeshToList(life);

    Mesh* cloud = object2D::CreateCircle("cloud", glm::vec3(0, 0, 0), 30.0f, glm::vec3(1, 1, 1), true);
    AddMeshToList(cloud);

    Mesh* square = object2D::CreateSquare("square", glm::vec3(0, 0, 0), 250, glm::vec3(0.5, 0.9, 0.7), false);
    AddMeshToList(square);

    Mesh* face = object2D::CreateCircle("face", glm::vec3(0, 0, 0), 80, glm::vec3(1, 0.34, 0.2), false);
    AddMeshToList(face);

    Mesh* eyeL = object2D::CreateCircle("eyeL", glm::vec3(0, 0, 0), 15, glm::vec3(1, 1, 1), false);
    AddMeshToList(eyeL);

    Mesh* eyeR = object2D::CreateCircle("eyeR", glm::vec3(0, 0, 0), 15, glm::vec3(1, 1, 1), false);
    AddMeshToList(eyeR);

    Mesh* mouthL = object2D::CreateRectangle("mouthL", glm::vec3(0, 0, 0), 10, 20, glm::vec3(1, 1, 1), true);
    AddMeshToList(mouthL);

    Mesh* mouthR = object2D::CreateRectangle("mouthR", glm::vec3(0, 0, 0), 10, 20, glm::vec3(1, 1, 1), true);
    AddMeshToList(mouthR);

    Mesh* mouthC = object2D::CreateRectangle("mouthC", glm::vec3(0, 0, 0), 60, 10, glm::vec3(1, 1, 1), true);
    AddMeshToList(mouthC);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["bottom_edge"], shaders["VertexColor"], modelMatrix);

    translateBodyX = translateHeadX - 30;
    translateBeakX = translateHeadX - 5;
    translateLeftWingX = translateHeadX - 50;
    translateRightWingX = translateHeadX + 10;
    leftBottomCorner = translateHeadX - 50;
    rightBottomCorner = translateHeadX + 50;

    translateBodyY = translateHeadY - 70;
    translateBeakY = translateHeadY + 20;
    translateLeftWingY = translateHeadY - 55;
    translateRightWingY = translateHeadY - 55;
    leftUpCorner = translateHeadY - 70;
    rightUpCorner = translateHeadY + 35;

    if (livesCount == 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(570, 440);
        RenderMesh2D(meshes["eyeL"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(630, 440);
        RenderMesh2D(meshes["eyeR"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(560, 345);
        modelMatrix *= transform2D::Rotate(-M_PI / 6);
        RenderMesh2D(meshes["mouthL"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(630, 340);
        modelMatrix *= transform2D::Rotate(M_PI / 6);
        RenderMesh2D(meshes["mouthR"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(570, 360);
        RenderMesh2D(meshes["mouthC"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(faceX, faceY);
        RenderMesh2D(meshes["face"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(squareX, squareY);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        //this_thread::sleep_for(chrono::milliseconds(5000));
        /*Sleep(5);
        exit(-1);*/
    }

    if (isAlive == 1) {
        /*checkVertical = (rand() % (1 - 0 + 1));
        checkHorizontally = (rand() % (1 - 0 + 1));*/
        if (checkVertical == 1 && checkHorizontally == 1) {
            translateHeadY += duckSpeedY;
            translateHeadX += duckSpeedX;

            rotateBeak = -3.14 / 4;
            rotateBody = -3.14 / 4;
            rotateLeftW = -3.14 / 4;
            rotateRightW = -3.14 / 4;

            translateBodyX = translateHeadX - 70;
            translateBeakX = translateHeadX + 5;
            translateLeftWingX = translateHeadX - 60;
            translateRightWingX = translateHeadX - 35;
            leftBottomCorner = translateHeadX - 75;
            rightBottomCorner = translateHeadX + 25;

            translateBodyY = translateHeadY - 40;
            translateBeakY = translateHeadY + 20;
            translateLeftWingY = translateHeadY - 40;
            translateRightWingY = translateHeadY - 65;
            leftUpCorner = translateHeadY - 85;
            rightUpCorner = translateHeadY + 20;

            if (translateBeakY >= 700 || translateBodyY >= 700 || translateHeadY >= 700 ||
                translateLeftWingY >= 700 || translateRightWingY >= 700 || leftUpCorner >= 700) {
                checkVertical = 0;
            }

            if (translateBeakX >= 1250 || translateBodyX >= 1250 || translateHeadX >= 1250 ||
                translateLeftWingX >= 1250 || translateRightWingX >= 1250 || leftBottomCorner >= 1250) {
                checkHorizontally = 0;
                touchEdgeLeftOrRight++;
            }
        }

        if (checkVertical == 1 && checkHorizontally == 0) {
            translateHeadY += duckSpeedY;
            translateHeadX -= duckSpeedX;

            rotateBeak = 3.14 / 4;
            rotateBody = 3.14 / 4;
            rotateLeftW = -3.14 / 4;
            rotateRightW = -3.14 / 4;

            translateBodyX = translateHeadX + 40;
            translateBeakX = translateHeadX - 15;
            translateLeftWingX = translateHeadX + 10;
            translateRightWingX = translateHeadX + 35;
            leftBottomCorner = translateHeadX - 25;
            rightBottomCorner = translateHeadX + 75;

            translateBodyY = translateHeadY - 70;
            translateBeakY = translateHeadY + 10;
            translateLeftWingY = translateHeadY - 55;
            translateRightWingY = translateHeadY - 25;
            leftUpCorner = translateHeadY - 70;
            rightUpCorner = translateHeadY + 35;

            if (translateBeakY >= 700 || translateBodyY >= 700 || translateHeadY >= 700 ||
                translateLeftWingY >= 700 || translateRightWingY >= 700 || leftUpCorner >= 700) {
                checkVertical = 0;
            }

            if (translateBeakX <= 0 || translateBodyX <= 0 || translateHeadX <= 0 ||
                translateLeftWingX <= 0 || translateRightWingX <= 0 || leftBottomCorner <= 0) {
                checkHorizontally = 1;
                touchEdgeLeftOrRight++;
            }
        }

        if (checkVertical == 0 && checkHorizontally == 1) {
            translateHeadY -= duckSpeedY;
            translateHeadX += duckSpeedX;

            rotateBeak = 3.14 / 2;
            rotateBody = 3.14 / 2;
            rotateLeftW = -3.14 / 4;
            rotateRightW = -3.14 / 4;
            
            translateBodyX = translateHeadX - 20;
            translateBeakX = translateHeadX + 20;
            translateLeftWingX = translateHeadX - 20;
            translateRightWingX = translateHeadX - 50;
            leftBottomCorner = translateHeadX - 75;
            rightBottomCorner = translateHeadX + 25;

            translateBodyY = translateHeadY + 10;
            translateBeakY = translateHeadY - 30;
            translateLeftWingY = translateHeadY + 30;
            translateRightWingY = translateHeadY - 10;
            leftUpCorner = translateHeadY - 35;
            rightUpCorner = translateHeadY + 70;

            if (translateBeakY <= 150 || translateBodyY <= 150 || translateHeadY <= 150 ||
                translateLeftWingY <= 150 || translateRightWingY <= 150 || leftUpCorner <= 150) {
                checkVertical = 1;
            }

            if (translateBeakX >= 1250 || translateBodyX >= 1250 || translateHeadX >= 1250 ||
                translateLeftWingX >= 1250 || translateRightWingX >= 1250 || leftBottomCorner >= 1250) {
                checkHorizontally = 0;
                touchEdgeLeftOrRight++;
            }
        }

        if (checkVertical == 0 && checkHorizontally == 0) {
            translateHeadY -= duckSpeedY;
            translateHeadX -= duckSpeedX;

            rotateBeak = 3.14 / 4;
            rotateBody = 3.14 / 4;
            rotateLeftW = -3.14 / 4;
            rotateRightW = -3.14 / 4;

            translateBodyX = translateHeadX + 10;
            translateBeakX = translateHeadX - 15;
            translateLeftWingX = translateHeadX - 25;
            translateRightWingX = translateHeadX + 15;
            leftBottomCorner = translateHeadX - 50;
            rightBottomCorner = translateHeadX + 50;

            translateBodyY = translateHeadY + 20;
            translateBeakY = translateHeadY - 30;
            translateLeftWingY = translateHeadY + 25;
            translateRightWingY = translateHeadY + 25;
            leftUpCorner = translateHeadY - 30;
            rightUpCorner = translateHeadY + 75;

            if (translateBeakY <= 150 || translateBodyY <= 150 || translateHeadY <= 150 ||
                translateLeftWingY <= 150 || translateRightWingY <= 150 || leftUpCorner <= 150) {
                checkVertical = 1;
            }

            if (translateBeakX <= 0 || translateBodyX <= 0 || translateHeadX <= 0 ||
                translateLeftWingX <= 0 || translateRightWingX <= 0 || leftBottomCorner <= 0) {
                checkHorizontally = 1;
                touchEdgeLeftOrRight++;
            }
        }
    }

    else {
        translateHeadY -= speedUp;
        rotateBody = 3.14 / 4;
        rotateBeak = 3.14 / 4;

        translateBodyX = translateHeadX + 10;
        translateBeakX = translateHeadX;
        translateLeftWingX = translateHeadX - 25;
        translateRightWingX = translateHeadX + 15;
        leftBottomCorner = translateHeadX - 35;
        rightBottomCorner = translateHeadX + 50;

        translateBodyY = translateHeadY + 20;
        translateBeakY = translateHeadY - 30;
        translateLeftWingY = translateHeadY + 25;
        translateRightWingY = translateHeadY + 25;
        leftUpCorner = translateHeadY - 30;
        rightUpCorner = translateHeadY + 35;

        if (translateBeakY <= 150 || translateBodyY <= 150 || translateHeadY <= 150 ||
            translateLeftWingY <= 150 || translateRightWingY <= 150 || leftUpCorner <= 150) {
            // number = (rand() % (upper - lower + 1)) + lower
            translateHeadX = (rand() % (upper - lower + 1)) + lower;
            translateHeadY = 120;
            isAlive = 1;
            timeSpent = 0;
            bulletCount = 3;
          
            duckSpeedX = 0.5;
            duckSpeedY = 0.3;
            
            duck_count++;
           
            duck_number = (rand() % (4 - 0 + 1));

            int chance = (rand() % (100 - 1 + 1)) + 1;
            if (chance >= 0 && chance <= 30) {
                livesCount++;
            }
            if (chance >= 31 && chance <= 50) {
                bulletCount++;
            }

            duck_kill++;
        }
    }

    if (touchEdgeLeftOrRight >= 5 ||
        (bulletCount <= 0 && duckShot == 0) || 
        eliberateDuck == 1) {

        duckSpeedX = 0;
        translateHeadY += speedUp;
        if (duckSpeedY >= speedUp) {
            speedUp = duckSpeedY;
        }
        translateHeadY += speedUp * 3;
        rotateBody = 0;
        rotateBeak = 0;

        translateBodyX = translateHeadX - 30;
        translateBeakX = translateHeadX - 5;
        translateLeftWingX = translateHeadX - 50;
        translateRightWingX = translateHeadX + 10;
        leftBottomCorner = translateHeadX - 50;
        rightBottomCorner = translateHeadX + 50;

        translateBodyY = translateHeadY - 70;
        translateBeakY = translateHeadY + 20;
        translateLeftWingY = translateHeadY - 55;
        translateRightWingY = translateHeadY - 55;
        leftUpCorner = translateHeadY - 70;
        rightUpCorner = translateHeadY + 35;

        if (translateBeakY >= 700 || translateBodyY >= 700 || translateHeadY >= 700 ||
            translateLeftWingY >= 700 || translateRightWingY >= 700 || leftUpCorner >= 700) {
            // number = (rand() % (upper - lower + 1)) + lower
            touchEdgeLeftOrRight = 0;
            translateHeadX = (rand() % (upper - lower + 1)) + lower;
            translateHeadY = 120;
            bulletCount = 3;
            scaleX -= 0.02;
            timeSpent = 0;
            eliberateDuck = 0;
            livesCount--;
            duckSpeedX = 0.5;
            duckSpeedY = 0.3;
            duck_count++;
            duck_number = (rand() % (4 - 0 + 1));
            duck_miss++;
        }
    }

    modelMatrix = glm::mat3(1);

    for (int i = 0; i < livesCount; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100 + 50 * i, 650);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(325, 650);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(375, 650);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < cloudNumber; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(300 + 50 * i, 620);
        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(575, 650);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(625, 650);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < cloudNumber; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(550 + 50 * i, 620);
        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(825, 650);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(875, 650);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < cloudNumber; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(800 + 50 * i, 620);
        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["scoreBar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(980, 650);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    RenderMesh2D(meshes["scoreBarFull"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);

    for (int i = 0; i < bulletCount; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(90 + 53 * i, 600);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    duckSpeedY = duckSpeedY +  0.2 * deltaTimeSeconds;
    if (duckSpeedY >= 2) {
        duckSpeedY = duckSpeedY + 0.3 * deltaTimeSeconds;
    }


    duckSpeedX = duckSpeedX + 0.2 * deltaTimeSeconds;
    if (duckSpeedX >= 2) {
        duckSpeedX = duckSpeedX + 0.3 * deltaTimeSeconds;
    }
    
    if (duck_count >= 5) {
        duckSpeedX = duckSpeedX + 0.5 * deltaTimeSeconds;
        duckSpeedY = duckSpeedY + 0.5 * deltaTimeSeconds;
    }

    if (duck_count >= 10) {
        duckSpeedX = duckSpeedX + 0.8 * deltaTimeSeconds;
        duckSpeedY = duckSpeedY + 0.8 * deltaTimeSeconds;
    }

    if (duck_number == 0) {
        // HEAD
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateHeadX, translateHeadY);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        // BODY
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateBodyX, translateBodyY);
        modelMatrix *= transform2D::Rotate(rotateBody);
        RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

         // BEAK
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateBeakX, translateBeakY);
         modelMatrix *= transform2D::Rotate(rotateBeak);
         RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

         // LEFT WING
         angularStepLeft += 0.01;
         if (angularStepLeft >= 0.3) {
             angularStepLeft = 0;
         }
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateLeftWingX, translateLeftWingY);
         modelMatrix *= transform2D::Rotate(angularStepLeft);
         //modelMatrix *= transform2D::Rotate(rotateLeftW);
         RenderMesh2D(meshes["left_wing1"], shaders["VertexColor"], modelMatrix);

         // RIGHT WING
         angularStepRight -= 0.01;
         if (angularStepRight <= -0.3) {
             angularStepRight = 0;
         }
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateRightWingX, translateRightWingY);
         modelMatrix *= transform2D::Rotate(angularStepRight);
         //modelMatrix *= transform2D::Rotate(rotateRightW);
         RenderMesh2D(meshes["right_wing1"], shaders["VertexColor"], modelMatrix);
    }

    if (duck_number == 1) {
        // HEAD
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateHeadX, translateHeadY);
        RenderMesh2D(meshes["head1"], shaders["VertexColor"], modelMatrix);

        // BODY
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateBodyX, translateBodyY);
        modelMatrix *= transform2D::Rotate(rotateBody);
        RenderMesh2D(meshes["body1"], shaders["VertexColor"], modelMatrix);

         // BEAK
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateBeakX, translateBeakY);
         modelMatrix *= transform2D::Rotate(rotateBeak);
         RenderMesh2D(meshes["beak1"], shaders["VertexColor"], modelMatrix);

         // LEFT WING
         angularStepLeft += 0.01;
         if (angularStepLeft >= 0.3) {
             angularStepLeft = 0;
         }
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateLeftWingX, translateLeftWingY);
         modelMatrix *= transform2D::Rotate(angularStepLeft);
         RenderMesh2D(meshes["left_wing1"], shaders["VertexColor"], modelMatrix);

         // RIGHT WING
         angularStepRight -= 0.01;
         if (angularStepRight <= -0.3) {
             angularStepRight = 0;
         }
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateRightWingX, translateRightWingY);
         modelMatrix *= transform2D::Rotate(angularStepRight);
         RenderMesh2D(meshes["right_wing1"], shaders["VertexColor"], modelMatrix);

         //duck_number++;
    }

    if (duck_number == 2) {
        // HEAD
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateHeadX, translateHeadY);
        RenderMesh2D(meshes["head2"], shaders["VertexColor"], modelMatrix);

        // BODY
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateBodyX, translateBodyY);
        modelMatrix *= transform2D::Rotate(rotateBody);
        RenderMesh2D(meshes["body2"], shaders["VertexColor"], modelMatrix);

         // BEAK
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateBeakX, translateBeakY);
         modelMatrix *= transform2D::Rotate(rotateBeak);
         RenderMesh2D(meshes["beak2"], shaders["VertexColor"], modelMatrix);

         // LEFT WING
         angularStepLeft += 0.01;
         if (angularStepLeft >= 0.3) {
             angularStepLeft = 0;
         }
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateLeftWingX, translateLeftWingY);
         modelMatrix *= transform2D::Rotate(angularStepLeft);
         RenderMesh2D(meshes["left_wing2"], shaders["VertexColor"], modelMatrix);

         // RIGHT WING
         angularStepRight -= 0.01;
         if (angularStepRight <= -0.3) {
             angularStepRight = 0;
         }
         modelMatrix = glm::mat3(1);
         modelMatrix *= transform2D::Translate(translateRightWingX, translateRightWingY);
         modelMatrix *= transform2D::Rotate(angularStepRight);
         RenderMesh2D(meshes["right_wing2"], shaders["VertexColor"], modelMatrix);
    }

    if (duck_number == 3) {
        // HEAD
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateHeadX, translateHeadY);
        RenderMesh2D(meshes["head3"], shaders["VertexColor"], modelMatrix);

        // BODY
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateBodyX, translateBodyY);
        modelMatrix *= transform2D::Rotate(rotateBody);
        RenderMesh2D(meshes["body3"], shaders["VertexColor"], modelMatrix);

        // BEAK
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateBeakX, translateBeakY);
        modelMatrix *= transform2D::Rotate(rotateBeak);
        RenderMesh2D(meshes["beak3"], shaders["VertexColor"], modelMatrix);

        // LEFT WING
        angularStepLeft += 0.01;
        if (angularStepLeft >= 0.3) {
            angularStepLeft = 0;
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateLeftWingX, translateLeftWingY);
        modelMatrix *= transform2D::Rotate(angularStepLeft);
        RenderMesh2D(meshes["left_wing3"], shaders["VertexColor"], modelMatrix);

        // RIGHT WING
        angularStepRight -= 0.01;
        if (angularStepRight <= -0.3) {
            angularStepRight = 0;
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateRightWingX, translateRightWingY);
        modelMatrix *= transform2D::Rotate(angularStepRight);
        RenderMesh2D(meshes["right_wing3"], shaders["VertexColor"], modelMatrix);
    }

    if (duck_number == 4) {
        // HEAD
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateHeadX, translateHeadY);
        RenderMesh2D(meshes["head4"], shaders["VertexColor"], modelMatrix);

        // BODY
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateBodyX, translateBodyY);
        modelMatrix *= transform2D::Rotate(rotateBody);
        RenderMesh2D(meshes["body4"], shaders["VertexColor"], modelMatrix);

        // BEAK
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateBeakX, translateBeakY);
        modelMatrix *= transform2D::Rotate(rotateBeak);
        RenderMesh2D(meshes["beak4"], shaders["VertexColor"], modelMatrix);

        // LEFT WING
        angularStepLeft += 0.01;
        if (angularStepLeft >= 0.3) {
            angularStepLeft = 0;
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateLeftWingX, translateLeftWingY);
        modelMatrix *= transform2D::Rotate(angularStepLeft);
        //modelMatrix *= transform2D::Rotate(rotateLeftW);
        RenderMesh2D(meshes["left_wing4"], shaders["VertexColor"], modelMatrix);

        // RIGHT WING
        angularStepRight -= 0.01;
        if (angularStepRight <= -0.3) {
            angularStepRight = 0;
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateRightWingX, translateRightWingY);
        modelMatrix *= transform2D::Rotate(angularStepRight);
        //modelMatrix *= transform2D::Rotate(rotateRightW);
        RenderMesh2D(meshes["right_wing4"], shaders["VertexColor"], modelMatrix);
    }

    if (duck_number == 5) {
        duck_number = 0;
    }

    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["left_edge"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["right_edge"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["top_edge"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["sky"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < cloudNumber; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(300 + 50 * i, 650);
        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    }
    timeSpent += deltaTimeSeconds;
    if (timeSpent >= 20 && duckShot == 0) {
        eliberateDuck = 1;
        timeSpent = 0;
    }

    if (scaleX >= 1.30) {
        scaleX = 0;
    }

    if (scaleX <= 0) {
        scaleX = 0;
    }

    if (livesCount == 0) {
        translateHeadX = 400;
        translateHeadY = 300;

        translateBodyX = translateHeadX - 30;
        translateBeakX = translateHeadX - 5;
        translateLeftWingX = translateHeadX - 50;
        translateRightWingX = translateHeadX + 10;
        leftBottomCorner = translateHeadX - 50;
        rightBottomCorner = translateHeadX + 50;

        translateBodyY = translateHeadY - 70;
        translateBeakY = translateHeadY + 20;
        translateLeftWingY = translateHeadY - 55;
        translateRightWingY = translateHeadY - 55;
        leftUpCorner = translateHeadY - 70;
        rightUpCorner = translateHeadY + 35;

        bulletCount = 0;
    }


    // OUTLINE
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(leftBottomCorner, leftUpCorner);
    RenderMesh2D(meshes["outline"], shaders["VertexColor"], modelMatrix);
}

void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    //if (key == GLFW_KEY_SPACE)
    //{
    //    if (sound)
    //    {
    //        //sndPlaySound("duck-mad.wav", SND_ASYNC);
    //        PlaySound("duck-mad.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    //    }
    //}

    //if (key == GLFW_KEY_S)
    //{
    //    sound = !sound;
    //}
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (isAlive == 1) {
        bulletCount--;
        if (mouseX >= leftBottomCorner && mouseX <= rightBottomCorner &&
            mouseY >= (720 - rightUpCorner) && mouseY <= (720 - leftUpCorner)) {
            duckShot = 1;
            isAlive = 0;
            scaleX += 0.03;
            duck_kill++;
            if (duck_kill >= 5) {
                scaleX += 0.07;
            }
        }
        else {
            duckShot = 0;
            if (bulletCount <= 0) {
                duckShot = 0;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
