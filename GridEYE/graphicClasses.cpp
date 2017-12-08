//
//  graphicClasses.cpp
//  GridEYE
//
//  Created by Grant Hilgert on 12/1/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graphicClasses.h"

bool newDR = true;
int newFPS = 10;
int newruntime = 0;
//-----------------------------------------------------------------
// Interactive Object Methods
//-----------------------------------------------------------------
interactiveObject::interactiveObject(){
    if (!defaultFont.loadFromFile("sansation.ttf")) { //Loads default Font from from
        //return EXIT_FAILURE;
    }
}
//-----------------------------------------------------------------
// Terminal (Message Stack) Methods
//-----------------------------------------------------------------
terminal::terminal(int size, string text){
    for(int i = 0; i <= size; i++){                   //
        stack.push_back(" ");                         //Adds empty values to prevent crash
    }
    rootText = text;                                  //Text String that precludes print function
    
    //Sets placeholder text for each line in the terminal object
    terminalText1.setString("UNDEFINED");
    terminalText2.setString("UNDEFINED");
    terminalText3.setString("UNDEFINED");
    terminalText4.setString("UNDEFINED");
    terminalText5.setString("UNDEFINED");
    terminalText6.setString("UNDEFINED");
   
    //Sets font for each line in the terminal object
    terminalText1.setFont(defaultFont);
    terminalText2.setFont(defaultFont);
    terminalText3.setFont(defaultFont);
    terminalText4.setFont(defaultFont);
    terminalText5.setFont(defaultFont);
    terminalText6.setFont(defaultFont);
    
    //Sets Character Size for each line in the terminal object
    terminalText1.setCharacterSize(12);
    terminalText2.setCharacterSize(12);
    terminalText3.setCharacterSize(12);
    terminalText4.setCharacterSize(12);
    terminalText5.setCharacterSize(12);
    terminalText6.setCharacterSize(12);
    
    //Sets color for each line in the terminal object
    terminalText1.setFillColor(sf::Color(0,255,0));
    terminalText2.setFillColor(sf::Color(0,255,0));
    terminalText3.setFillColor(sf::Color(0,255,0));
    terminalText4.setFillColor(sf::Color(0,255,0));
    terminalText5.setFillColor(sf::Color(0,255,0));
    terminalText6.setFillColor(sf::Color(0,255,0));
    
    //Sets position for each line in the terminal object
    terminalText1.setPosition( 100 , 608);
    terminalText2.setPosition( 100 , 622);
    terminalText3.setPosition( 100 , 636);
    terminalText4.setPosition( 100 , 650);
    terminalText5.setPosition( 100 , 664);
    terminalText6.setPosition( 100 , 678);
    
    //Creates the Frame for the terminal
    terminalBackground.setSize(sf::Vector2f( 625, 94 ));
    terminalHeader.setSize(sf::Vector2f( 625, 10 ));
    
    //Sets the color for each element of the terminal frame
    terminalBackground.setFillColor(sf::Color(0,0,0,150));
    terminalHeader.setFillColor(sf::Color(255,94,20,150));

    //Sets the posotion for each element of the terminal frame
    terminalBackground.setPosition(94, 606);
    terminalHeader.setPosition(94, 596);
}

void terminal::print(string input){
    stack.insert(stack.begin(),rootText+" : "+input); //Insert text string into stack vector
}

void terminal::print(string input, string text){    //Insert text string into stack vector with non default pretext
    stack.insert(stack.begin(),text+" : "+input);
}

void terminal::setRoot(string text){    //Change the default pretext
    rootText = text;
}

void terminal::draw(sf::RenderWindow &window){
    //Set each line of the terminal text to the coropsonding position of the stack vector
    terminalText1.setString(stack[5]);
    terminalText2.setString(stack[4]);
    terminalText3.setString(stack[3]);
    terminalText4.setString(stack[2]);
    terminalText5.setString(stack[1]);
    terminalText6.setString(stack[0]);
    
    //Adds each line of the terminal text to the window object
    window.draw(terminalText1);
    window.draw(terminalText2);
    window.draw(terminalText3);
    window.draw(terminalText4);
    window.draw(terminalText5);
    window.draw(terminalText6);
    
    //Adds the terminal from to the window object
    window.draw(terminalBackground);
    window.draw(terminalHeader);
}

//-----------------------------------------------------------------
// Toolbar Methods
//-----------------------------------------------------------------
toolbar::toolbar(void){
    if (!t_settings.loadFromFile("settings.png")) {
        //return EXIT_FAILURE;
    }
    if (!t_record.loadFromFile("record.png")) {
       //return EXIT_FAILURE;
    }
    if (!t_stop.loadFromFile("stop.png")) {
        //return EXIT_FAILURE;
    }
    if (!t_play.loadFromFile("play.png")) {
        //return EXIT_FAILURE;
    }
    if (!t_trash.loadFromFile("trash.png")) {
        //return EXIT_FAILURE;
    }
    if (!t_save.loadFromFile("save.png")) {
        //return EXIT_FAILURE;
    }
    if (!t_quit.loadFromFile("gravestone.png")) {
        //return EXIT_FAILURE;
    }
    
    
    play.setTexture( t_play );
    settings.setTexture( t_settings );
    record.setTexture( t_record );
    stop.setTexture( t_stop );
    save.setTexture( t_save );
    trash.setTexture( t_trash );
    quit.setTexture( t_quit );
    
    settings.setPosition( 15, 30 );
    record.setPosition( 15, 109+15 );
    play.setPosition( 15, 188+30 );
    stop.setPosition( 15, 267+45);
    save.setPosition( 15, 346+60 );
    trash.setPosition( 15, 425+75 );
    quit.setPosition( 15, 504+90 );
    toolbarFrame.setPosition(0, 0);
    toolbarHeader.setPosition(89, 0);
    
    toolbarFrame.setFillColor(sf::Color(132, 101, 142,100));
    toolbarHeader.setFillColor(sf::Color(0, 0, 0,100));
    
    settings.scale(0.50, 0.50);
    record.scale(0.50, 0.50);
    play.scale(0.50, 0.50);
    stop.scale(0.50, 0.50);
    save.scale(0.50, 0.50);
    trash.scale(0.50, 0.50);
    quit.scale(0.50, 0.50);
    
    toolbarFrame.setSize(sf::Vector2f( 94, 700 ));
    toolbarHeader.setSize(sf::Vector2f( 5, 700 ));
    
    selection.setSize(sf::Vector2f( 89, 70 ));
    selection.setFillColor(sf::Color(0, 0, 0, 100));
    selection.setPosition(-100, -100);
    
    selectionTextBox.setSize(sf::Vector2f( 94, 20 ));
    selectionTextBox.setFillColor(sf::Color(255, 255, 255, 100));
    selectionTextBox.setPosition(-100, -100);
    
    selectionText.setString("void");
    selectionText.setCharacterSize(15);
    selectionText.setFont(defaultFont);
    selectionText.setFillColor(sf::Color(55,55,255)); //light blue
    selectionText.setPosition( -100 , -100);
    
    
    
}
//Draws toolbar
void toolbar::draw(sf::RenderWindow &window){
    //Draws Objects on display buffer
    window.draw(toolbarFrame);
    window.draw(toolbarHeader);
    window.draw(settings);
    window.draw(record);
    window.draw(stop);
    window.draw(play);
    window.draw(trash);
    window.draw(save);
    window.draw(quit);
    window.draw(selection);
    window.draw(selectionTextBox);
    window.draw(selectionText);
}
//Toolbar Mouse Events
void toolbar::event(sf::Event &toolbarEvent){
    //When mouse moves over menu item, semi transparent box is drawn over them
    if(toolbarEvent.type == sf::Event::MouseMoved){//If event is Mousedmoved type
        if(toolbarEvent.mouseMove.x > 0 && toolbarEvent.mouseMove.x < 94){//if Mouse is within toolbar
            //Settings
            if(toolbarEvent.mouseMove.y > 0 && toolbarEvent.mouseMove.y < 119){
                selection.setPosition(0, 26);
                selectionTextBox.setSize(sf::Vector2f(65, 20));
                selectionText.setString("Settings");
                selectionText.setPosition(35 , 89);
                selectionTextBox.setPosition(30,89);
            }
            //New Capture
            if(toolbarEvent.mouseMove.y > 119 && toolbarEvent.mouseMove.y < 189){
                selection.setPosition(0, 119);
                selectionTextBox.setSize(sf::Vector2f(65, 20));
                selectionText.setString("Capture");
                selectionText.setPosition( 35 , 183);
                selectionTextBox.setPosition(30,183);
                
            }
            //Play Capture
            if(toolbarEvent.mouseMove.y > 219 && toolbarEvent.mouseMove.y < 308){
                selection.setPosition(0, 219);
                selectionTextBox.setSize(sf::Vector2f( 95, 20 ));
                selectionText.setString("Play Capture");
                selectionText.setPosition( 35 , 278);
                selectionTextBox.setPosition(30,278);
            }
            //Stop Capture
            if(toolbarEvent.mouseMove.y > 308 && toolbarEvent.mouseMove.y < 402){
                selection.setPosition(0, 308);
                selectionTextBox.setSize(sf::Vector2f( 100, 20 ));
                selectionText.setString("Stop Capture");
                selectionText.setPosition( 35 , 372);
                selectionTextBox.setPosition(30,372);
            }
            //Save Capture
            if(toolbarEvent.mouseMove.y > 402 && toolbarEvent.mouseMove.y < 496){
                selection.setPosition(0, 402);
                selectionTextBox.setSize(sf::Vector2f( 100, 20 ));
                selectionText.setString("Save Capture");
                selectionText.setPosition( 35 , 466);
                selectionTextBox.setPosition(30,466);
            }
            //Delete Capture
            if(toolbarEvent.mouseMove.y > 496 && toolbarEvent.mouseMove.y < 590){
                selection.setPosition(0, 496);
                selectionTextBox.setSize(sf::Vector2f( 110, 20 ));
                selectionText.setString("Delete Capture");
                selectionText.setPosition( 35 , 560);
                selectionTextBox.setPosition(30,560);
            }
            //Ouit Program
            if(toolbarEvent.mouseMove.y > 590 && toolbarEvent.mouseMove.y < 700){
                selection.setPosition(0, 590);
                selectionTextBox.setSize(sf::Vector2f( 130, 20 ));
                selectionText.setString("Close Application");
                selectionText.setPosition( 35 , 654);
                selectionTextBox.setPosition(30,654);
            }
        }
        //Moves Selection objects offscreen when mouse exits hit box
        else if(toolbarEvent.mouseMove.x > 94){
            selectionText.setString("NULL");
            selectionText.setPosition( -100 , -100);
            selectionTextBox.setPosition(-100,-100);
            selection.setPosition(-100, -100);
        }
    }
}

void toolbar::onClick(sf::RenderWindow &window, terminal &Terminal){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){//If left button is pressed
        sf::Vector2i position = sf::Mouse::getPosition(window);//Get position of mouse
        if (position.x > 0 && position.x < 95){//Within toolbar
            //Settings
            if (position.y > 0 && position.y < 119){
                menuLayer = 1; //Change layer to settings layer
            }
            //Start Capture
            if (position.y > 119 && position.y < 189){
                Terminal.print("Starting Capture");
                menuLayer = 2;//set Capture Mode
            }
            //Play capture
            if (position.y > 189 && position.y < 308){
                Terminal.print("Entering Playback Mode");
                menuLayer = 3;//Change layer to playback
            }
            //Stop Caputre
            if (position.y >308 && position.y < 402){
                Terminal.print("Stopping Capture");
                menuLayer = 4;
            }
            //Save capture
            if (position.y > 402 && position.y < 496){
                Terminal.print("Saving Capture");
                menuLayer = 5;
            }
            //Delete capture
            if (position.y > 496 && position.y < 590){
                Terminal.print("Deleting Capture");
                menuLayer = 6;
            }
            //Exit - quit program
            if (position.y > 590 && position.y < 700){
                window.close();//Close Window
            }
        }
    }
}

int toolbar::exit(void){
    return menuLayer;
}

void toolbar::sync(int newMenuLayer){
    menuLayer = newMenuLayer;
}

settingsMenu::settingsMenu(void){
    if(!t_close.loadFromFile("cancel.png")){
        //return EXIT_FAILURE;
    }
 
    settingsExit.setTexture(t_close);
    settingsExit.setPosition(143,93);
    settingsExit.scale(0.1, 0.1);
    
    //Settings Button Position
    settingsTenFPS.setPosition(rootx+100 ,rootY+75 );   //Default
    settingsOneFPS.setPosition(rootx+325 ,rootY+75 );
    settingsMinsBox.setPosition(rootx+75 ,rootY+175 );
    settingsSecondsBox.setPosition(rootx+300 ,rootY+175 );
    settingsMinsUp.setPosition(rootx+150 ,rootY+175);
    settingsMinsDown.setPosition(rootx+150 ,rootY+200);
    settingsSecondsUp.setPosition(rootx+375 ,rootY+175 );
    settingsSecondsDown.setPosition(rootx+375 ,rootY+200 );
    settingsRangeTrue.setPosition(rootx+75 ,rootY+300 );
    settingsRangeHuman.setPosition(rootx+325 ,rootY+300 );
    settingsReset.setPosition(rootx+50 ,rootY+350 );
    settingsApply.setPosition(rootx+300 ,rootY+350 );
    settingsBackground.setPosition(-500, -500);
    settingsBackground.setPosition(rootx,rootY);    //Move settings background in place
 
    //Set Char size
    settingsFPSText.setCharacterSize(30);
    settingsFPSTextValTen.setCharacterSize(20);
    settingsFPSTextValOne.setCharacterSize(20);
    settingsCollectionText.setCharacterSize(30);
    settingsMinsText.setCharacterSize(40);
    settingsSecondsText.setCharacterSize(40);
    settingsRangeText.setCharacterSize(30);
    settingsRangeTextTrue.setCharacterSize(20);
    settingsRangeTextHuman.setCharacterSize(20);
    settingsResetText.setCharacterSize(20);
    settingsApplyText.setCharacterSize(20);
    
    //Set strings
    settingsFPSText.setString("Frames Per Second");
    settingsFPSTextValTen.setString("10 FPS");
    settingsFPSTextValOne.setString("1 FPS");
    settingsCollectionText.setString("Collection Time");
    settingsMinsText.setString("0");
    settingsSecondsText.setString("0");
    settingsRangeText.setString("Sensor Dynamic Range");
    settingsRangeTextTrue.setString("True");
    settingsRangeTextHuman.setString("Human");
    settingsResetText.setString("Reset Sensor");
    settingsApplyText.setString("Apply Settings");
    
    //Set Font
    settingsFPSText.setFont(defaultFont);
    settingsFPSTextValTen.setFont(defaultFont);
    settingsFPSTextValOne.setFont(defaultFont);
    settingsCollectionText.setFont(defaultFont);
    settingsMinsText.setFont(defaultFont);
    settingsSecondsText.setFont(defaultFont);
    settingsRangeText.setFont(defaultFont);
    settingsRangeTextTrue.setFont(defaultFont);
    settingsRangeTextHuman.setFont(defaultFont);
    settingsResetText.setFont(defaultFont);
    settingsApplyText.setFont(defaultFont);
    
    //Set Size
    settingsBackground.setSize(sf::Vector2f(500, 400 ));
    settingsTenFPS.setSize(sf::Vector2f(75, 25 ));
    settingsOneFPS.setSize(sf::Vector2f(75, 25 ));
    settingsMinsUp.setSize(sf::Vector2f(50,25 ));
    settingsMinsDown.setSize(sf::Vector2f(50,25));
    settingsSecondsUp.setSize(sf::Vector2f(50,25 ));
    settingsSecondsDown.setSize(sf::Vector2f(50,25 ));
    settingsRangeTrue.setSize(sf::Vector2f(100,25 ));
    settingsRangeHuman.setSize(sf::Vector2f(100,25 ));
    settingsReset.setSize(sf::Vector2f(150,25 ));
    settingsApply.setSize(sf::Vector2f(150, 25 ));
    settingsMinsBox.setSize(sf::Vector2f(50, 50 ));
    settingsSecondsBox.setSize(sf::Vector2f(50, 50 ));
    
    //Set fill size
    settingsBackground.setFillColor(sf::Color(255, 255, 255,150));
    settingsTenFPS.setFillColor(sf::Color(30,144,255));
    settingsOneFPS.setFillColor(sf::Color(135,206,250));
    settingsMinsUp.setFillColor(sf::Color::Green);
    settingsMinsDown.setFillColor(sf::Color::Red);
    settingsSecondsUp.setFillColor(sf::Color::Green);
    settingsSecondsDown.setFillColor(sf::Color::Red);
    settingsMinsBox.setFillColor(sf::Color::White);
    settingsSecondsBox.setFillColor(sf::Color::White);
    settingsRangeTrue.setFillColor(sf::Color(30,144,255));
    settingsRangeHuman.setFillColor(sf::Color(135,206,250));
    settingsReset.setFillColor(sf::Color(30,144,255));
    settingsApply.setFillColor(sf::Color(30,144,255));
    
    //Set Borders
    settingsTenFPS.setOutlineColor(sf::Color::White);
    settingsOneFPS.setOutlineColor(sf::Color::White);
    settingsMinsUp.setOutlineColor(sf::Color::White);
    settingsMinsDown.setOutlineColor(sf::Color::White);
    settingsSecondsUp.setOutlineColor(sf::Color::White);
    settingsSecondsDown.setOutlineColor(sf::Color::White);
    settingsMinsBox.setOutlineColor(sf::Color::White);
    settingsSecondsBox.setOutlineColor(sf::Color::White);
    settingsRangeTrue.setOutlineColor(sf::Color::White);
    settingsRangeHuman.setOutlineColor(sf::Color::White);
    settingsReset.setOutlineColor(sf::Color::White);
    settingsApply.setOutlineColor(sf::Color::White);
    
    //Settings Text Color
    settingsFPSText.setFillColor(sf::Color::Black);
    settingsFPSTextValTen.setFillColor(sf::Color::Black);
    settingsFPSTextValOne.setFillColor(sf::Color::Black);
    settingsCollectionText.setFillColor(sf::Color::Black);
    settingsMinsText.setFillColor(sf::Color::Black);
    settingsSecondsText.setFillColor(sf::Color::Black);
    settingsRangeText.setFillColor(sf::Color::Black);
    settingsRangeTextTrue.setFillColor(sf::Color::Black);
    settingsRangeTextHuman.setFillColor(sf::Color::Black);
    settingsResetText.setFillColor(sf::Color::Black);
    settingsApplyText.setFillColor(sf::Color::Black);
    
    //Settings Text Position
    settingsFPSText.setPosition(rootx+50,rootY+25 );
    settingsFPSTextValTen.setPosition(rootx+100+10 ,rootY+75 );
    settingsFPSTextValOne.setPosition(rootx+325+15 ,rootY+75 );
    settingsMinsText.setPosition(rootx+75 ,rootY+175 );
    settingsCollectionText.setPosition(rootx+50, rootY+125);
    settingsSecondsText.setPosition(rootx+300 ,rootY+175 );
    settingsRangeText.setPosition(rootx+50 ,rootY+250 );
    settingsRangeTextTrue.setPosition(rootx+75+30 ,rootY+300 );
    settingsRangeTextHuman.setPosition(rootx+325+20 ,rootY+300 );
    settingsResetText.setPosition(rootx+50+15 ,rootY+350 );
    settingsApplyText.setPosition(rootx+300+13 ,rootY+350 );
    
    //Set Selection to default
    settingsRangeHuman.setOutlineThickness(0);
    settingsRangeHuman.setFillColor(sf::Color(135,206,250));
    settingsRangeTrue.setFillColor(sf::Color(30,144,255));
    settingsRangeTrue.setOutlineThickness(2);
    settingsTenFPS.setOutlineThickness(2);
    settingsTenFPS.setFillColor(sf::Color(30,144,255));
    settingsOneFPS.setFillColor(sf::Color(135,206,250));
    settingsOneFPS.setOutlineThickness(0);
}

void settingsMenu::setDefaultRecordTime(int defaultSeconds){
    recordSeconds = defaultSeconds;
    settingsSecondsText.setString(std::to_string(recordSeconds));
}

void settingsMenu::onClick(sf::RenderWindow &window, GridEYE* gridward, terminal stackward){//Button presses
    // Colors :: Select: 30,144,255 Unselect: 135,206,250
    menuLayer = 1; //Set internal menuLayer reference
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){   //When Left Mouse is clicked
        sf::Vector2i position = sf::Mouse::getPosition(window); //Get Mouse Coordinates
        
        //Settings Exit Button
        if (position.x > 143  && position.x < 173){//Add root to this
            if (position.y > 93 && position.y < 123){//Add root to this
                menuLayer = 0;
            }}
        //10 FPS
        if (position.x > (rootx + 100)  && position.x < (rootx+175)){
            if (position.y > (rootY+ 75) && position.y < (rootY+100)){
                settingsTenFPS.setFillColor(sf::Color(30,144,255));
                settingsTenFPS.setOutlineThickness(2);
                settingsOneFPS.setFillColor(sf::Color(135,206,250));
                settingsOneFPS.setOutlineThickness(0);
                
                //sf::sleep(sf::milliseconds(50));
                newFPS = 10;
            }}
        //One FPS
        if (position.x > (rootx + 325)  && position.x < (rootx+400)){
            if (position.y > (rootY+75) && position.y < (rootY+100)){
                settingsOneFPS.setFillColor(sf::Color(30,144,255));
                settingsOneFPS.setOutlineThickness(2);
                settingsTenFPS.setFillColor(sf::Color(135,206,250));
                settingsTenFPS.setOutlineThickness(0);
                
                //sf::sleep(sf::milliseconds(50));
                newFPS = 1;
            }}
        //Minutes UP
        if (position.x > (rootx + 150)  && position.x < (rootx+200)){
            if (position.y > (rootY+175) && position.y < (rootY+200)){
                settingsMinsUp.setFillColor(sf::Color(sf::Color::Green));
                if(recordMins <= 50){
                    recordMins++;
                    newruntime += 60;
                    settingsMinsText.setString(std::to_string(recordMins));
                }
            }}
        //Minutes DOWN
        if (position.x > (rootx + 150)  && position.x < (rootx +200)){
            if (position.y > (rootY + 200) && position.y < (rootY+225)){
                settingsMinsDown.setFillColor(sf::Color(sf::Color::Red));
                if(recordMins > 0){
                    recordMins--;
                    newruntime -= 60;
                    settingsMinsText.setString(std::to_string(recordMins));
                }
            }}
        //Seconds UP
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY + 175) && position.y < (rootY+200)){
                settingsSecondsUp.setFillColor(sf::Color(sf::Color::Green));
                if(recordSeconds < 59){
                    recordSeconds++;
                    newruntime += 1;
                    if(recordSeconds > 9) settingsSecondsText.setPosition(rootx+300,rootY+175);
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
                else if(recordSeconds == 59 && recordMins < 50 ){
                    recordSeconds = 0;
                    recordMins++;
                    newruntime += 1;
                    settingsMinsText.setString(std::to_string(recordMins));
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
            }}
        //Seconds DOWN
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY+200) && position.y < (rootY+225)){
                settingsSecondsDown.setFillColor(sf::Color(sf::Color::Red));
                if(recordSeconds > 0){
                    recordSeconds--;
                    newruntime -= 1;
                    if(recordSeconds > 10) settingsSecondsText.setPosition(rootx+300+5,rootY+175);
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
                if(recordSeconds == 0){
                    recordSeconds = 59;
                    newruntime -= 1;
                    settingsSecondsText.setString(std::to_string(recordSeconds));
                }
            }}
        //Sensor TRUE
        if (position.x > (rootx + 75)  && position.x < (rootx + 175)){
            if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                settingsRangeTrue.setFillColor(sf::Color(30,144,255));
                settingsRangeTrue.setOutlineThickness(2);
                settingsRangeHuman.setFillColor(sf::Color(135,206,250));
                settingsRangeHuman.setOutlineThickness(0);
                newDR = true;
            }}
        //Sensor HUMAN
        if (position.x > (rootx + 325)  && position.x < (rootx + 425)){
            if (position.y > (rootY + 300) && position.y < (rootY + 325)){
                settingsRangeHuman.setFillColor(sf::Color(30,144,255));
                settingsRangeHuman.setOutlineThickness(2);
                settingsRangeTrue.setFillColor(sf::Color(135,206,250));
                settingsRangeTrue.setOutlineThickness(0);
                newDR = false;
            }}
        //RESET
        if (position.x > (rootx + 50)  && position.x < (rootx+200)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsReset.setFillColor(sf::Color(30,144,255));
                gridward->reset();
                settingsRangeHuman.setOutlineThickness(0);
                settingsRangeHuman.setFillColor(sf::Color(135,206,250));
                settingsRangeTrue.setFillColor(sf::Color(30,144,255));
                settingsRangeTrue.setOutlineThickness(2);
                settingsTenFPS.setOutlineThickness(2);
                settingsTenFPS.setFillColor(sf::Color(30,144,255));
                settingsOneFPS.setFillColor(sf::Color(135,206,250));
                settingsOneFPS.setOutlineThickness(0);
                recordMins = 0;
                settingsMinsText.setString(std::to_string(recordMins));
                recordSeconds = 0;
                settingsSecondsText.setString(std::to_string(recordSeconds));
                stackward.print("Reset","Grid-EYE");
                
            }}
        //APPLY
        if (position.x > (rootx + 300)  && position.x < (rootx + 450)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsApply.setFillColor(sf::Color(30,144,255));
                if( newruntime == 0 )
                    newruntime = 1;
                
                gridward->runtime = newruntime;
                gridward->FPS = newFPS;
                gridward->DR = newDR;
                
                cout << gridward->runtime << endl;
                cout << gridward->FPS << endl;
                menuLayer = 0;
            }}
    }//end button down
    //Button Release
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        //Mins UP
        if (position.x > (rootx + 150)  && position.x < (rootx+200)){
            if (position.y > (rootY+175) && position.y < (rootY+200)){
                settingsMinsUp.setFillColor(sf::Color(30,144,255));
            }}
        //Mins Down
        if (position.x > (rootx + 150)  && position.x < (rootx +200)){
            if (position.y > (rootY + 200) && position.y < (rootY+225)){
                settingsMinsDown.setFillColor(sf::Color(135,206,250));
            }}
        //Seconds up
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY + 175) && position.y < (rootY+200)){
                settingsSecondsUp.setFillColor(sf::Color(30,144,255));
            }}
        
        //Seconds down
        if (position.x > (rootx + 375)  && position.x < (rootx+425)){
            if (position.y > (rootY+200) && position.y < (rootY+225)){
                settingsSecondsDown.setFillColor(sf::Color(135,206,250));
            }}
        //Reset
        if (position.x > (rootx + 50)  && position.x < (rootx+200)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsReset.setFillColor(sf::Color(255,144,255));
            }}
        //Apply
        if (position.x > (rootx + 300)  && position.x < (rootx + 450)){
            if (position.y > (rootY + 350) && position.y < (rootY + 375)){
                settingsApply.setFillColor(sf::Color(255,255,255));
            }}
    }
}

void settingsMenu::draw(sf::RenderWindow &window){
    window.draw(settingsBackground);
    window.draw(settingsExit);
    window.draw(settingsTenFPS);
    window.draw(settingsOneFPS);
    window.draw(settingsFPSText);
    window.draw(settingsFPSTextValTen);
    window.draw(settingsFPSTextValOne);
    window.draw(settingsMinsUp);
    window.draw(settingsMinsDown);
    window.draw(settingsSecondsUp);
    window.draw(settingsSecondsDown);
    window.draw(settingsMinsBox);
    window.draw(settingsSecondsBox);
    window.draw(settingsCollectionText);
    window.draw(settingsMinsText);
    window.draw(settingsSecondsText);
    window.draw(settingsRangeTrue);
    window.draw(settingsRangeHuman);
    window.draw(settingsRangeText);
    window.draw(settingsRangeTextTrue);
    window.draw(settingsRangeTextHuman);
    window.draw(settingsReset);
    window.draw(settingsResetText);
    window.draw(settingsApply);
    window.draw(settingsApplyText);
}

int settingsMenu::exit(void){
    return menuLayer;
}

//-----------------------------------------------------------------
// Topbar Methods
//-----------------------------------------------------------------
topBar::topBar(void){
    
    //Updates Time
    time_t tempTime = time(NULL);
    clockStruct = localtime(&tempTime);
    strftime (clockTextBuffer,11,"%r",clockStruct);
    
    //Rectangle Shape Objects
    background.setSize(sf::Vector2f( 606, 75 ));
    background.setFillColor(sf::Color(0, 0, 0,50));
    background.setPosition(94, 0);
    
    header.setSize(sf::Vector2f(606, 5 ));
    header.setFillColor(sf::Color(255, 94, 20,150));
    header.setPosition(94, 75);
    
    //Text Objects
    //Mode
    modeText.setString("Booting");
    modeText.setCharacterSize(30);
    modeText.setFont(defaultFont);
    modeText.setFillColor(sf::Color::White);
    modeText.setPosition( 550 , 10);
    //Title
    titleText.setString("Panasonic Grid-EYE");
    titleText.setCharacterSize(36);
    titleText.setFont(defaultFont);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition( 109 , 10);
    //Subtitle
    subText.setString("Created by Grant Hilgert and Richard Oman");
    subText.setCharacterSize(15);
    subText.setFont(defaultFont);
    subText.setFillColor(sf::Color::Magenta);
    subText.setPosition(109,55);
    //Clock
    clockText.setString(clockTextBuffer);
    clockText.setFont(defaultFont);
    clockText.setCharacterSize(20);
    clockText.setString(clockTextBuffer);
    clockText.setFillColor(sf::Color::White);
    clockText.setPosition( 560 , 45);
}

void topBar::setMode(int newMode){
    mode = newMode;
    updateMode();
}

void topBar::updateMode(void){
    switch(mode){
        default:
            modeText.setFillColor(sf::Color::Green);
            modeText.setString("Stand-By");
            break;
        case 2:
            modeText.setFillColor(sf::Color::Red);
            modeText.setString("Recording");
            clipStart = time(NULL);
            break;
        case 3:
            modeText.setFillColor(sf::Color::Yellow);
            modeText.setString("Play Back");
            break;
        case 4:
            modeText.setFillColor(sf::Color(0,115,115));
            modeText.setString("Replay");
            break;
    }
}

void topBar::draw(sf::RenderWindow &window){
    window.draw(background);
    window.draw(header);
    window.draw(modeText);
    window.draw(titleText);
    window.draw(subText);
    window.draw(clockText);
}

void topBar::updateClock(time_t currentTime){
    elapsedTime = difftime(time(NULL), clipStart);
    switch(mode){
        default:
            clockStruct = localtime(&currentTime);                  //Stores Current Time into struct
            strftime (clockTextBuffer,11,"%r",clockStruct);         //Creates Formated String
            clockText.setString(clockTextBuffer);                   //Updates Text Object
            break;
        case 2:
            if(int(elapsedTime/60) < 10){
                if(int(fmod(elapsedTime,60)) < 10){
                    clockText.setString("0" + std::to_string(int(elapsedTime/60))+":0"+std::to_string(int(fmod(elapsedTime,60))));
                } else  clockText.setString("0" + std::to_string(int(elapsedTime/60))+":"+std::to_string(int(fmod(elapsedTime,60))));
            }
            else{
                if(int(fmod(elapsedTime,60)) < 10){
                    clockText.setString(std::to_string(int(elapsedTime/60))+":0"+std::to_string(int(fmod(elapsedTime,60))));
                } else  clockText.setString(std::to_string(int(elapsedTime/60))+":"+std::to_string(int(fmod(elapsedTime,60))));
            }
            
    }
}

//-----------------------------------------------------------------
// Playbar Methods
//-----------------------------------------------------------------
playBar::playBar(sf::Vector2f position, int scale){
    
    origin = position;
    if (!t_background.loadFromFile("audio-player.png")) {
        //return EXIT_FAILURE;
    }
    if (!t_fillBar.loadFromFile("progress.png")) {
        //return EXIT_FAILURE;
    }

    background.setTexture(t_background);
    fillBar.setTexture(t_fillBar);
    background.setPosition(position);
    background.scale(scale, scale);
    
    fillPos.x = position.x + 235;
    fillPos.y = position.y + 164;
    fillBar.setPosition(fillPos);
    fillBar.scale(1, 1);
    
    timeTextStruct = localtime(&clipEnd);
    strftime (timeTextBuffer,8,"%R",timeTextStruct);
    currentTimeText.setString(timeTextBuffer);
    endTimeText.setString(timeTextBuffer);
    
    currentTimeText.setCharacterSize(12);
    currentTimeText.setFillColor(sf::Color::White);
    currentTimeText.setFont(defaultFont);
    currentTimeText.setPosition(position.x+465,position.y+158);
    
    endTimeText.setCharacterSize(12);
    endTimeText.setFillColor(sf::Color::White);
    endTimeText.setFont(defaultFont);
    endTimeText.setPosition(position.x+510,position.y+158);
}

void playBar::setCurrentTime(void){
    
    timeTextStruct = localtime(&clipStart);
    strftime (timeTextBuffer,8,"%M:%S",timeTextStruct);
    currentTimeText.setString(timeTextBuffer);
    
    timeTextStruct = localtime(&clipEnd);
    strftime (timeTextBuffer,8,"%M:%S",timeTextStruct);
    endTimeText.setString(timeTextBuffer);
}

void playBar::draw(sf::RenderWindow &window){
    window.draw(background);
    window.draw(fillBar);
    window.draw(currentTimeText);
}

void playBar::onClick(sf::RenderWindow &window, terminal &Terminal){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){//When Left Mouse is clicked
        sf::Vector2i position = sf::Mouse::getPosition(window);//Get Mouse Coordinates
        
        //playBar playward(sf::Vector2f(35, 375),1);
        if (position.x > origin.x+190  && position.x < origin.x+230){
            if (position.y > origin.y+150  && position.y < origin.y+180) {
                Terminal.print("Replay Mode");
                playbackStart = time(NULL);
            }
        }
    }
}

void playBar::setClipStartTime(time_t start){
    clipStart = start;
}

void playBar::setClipEndTime(time_t end){
    clipEnd = end;
    playbackTime = difftime(clipEnd, clipStart);
    
    if(int(playbackTime/60) < 10){
        if(int(fmod(elapsedTime,60)) < 10){
            bufferB = "0" + std::to_string(int(playbackTime/60))+":0"+std::to_string(int(fmod(playbackTime,60)));
        } else  bufferB = "0" + std::to_string(int(playbackTime/60))+":"+std::to_string(int(fmod(playbackTime,60)));
    }
    else{
        if(int(fmod(playbackTime,60)) < 10){
            bufferB = std::to_string(int(playbackTime/60))+":0"+std::to_string(int(fmod(playbackTime,60)));
        } else  bufferB = std::to_string(int(playbackTime/60))+":"+std::to_string(int(fmod(playbackTime,60)));
    }
}

void playBar::setPlaybackStartTime(time_t start){
    playbackStart = start;
}

void playBar::setPlaybackEndTime(time_t end){

}

void playBar::playback(topBar &TopBar, terminal &Terminal, bool &playbackStatus ){
    elapsedTime = difftime(time(NULL), playbackStart);
    if(elapsedTime <= playbackTime){
        playbackStatus = true;
        
        if(int(elapsedTime/60) < 10){
            if(int(fmod(elapsedTime,60)) < 10){
            bufferA = "0" + std::to_string(int(elapsedTime/60))+":0"+std::to_string(int(fmod(elapsedTime,60)));
            } else  bufferA = "0" + std::to_string(int(elapsedTime/60))+":"+std::to_string(int(fmod(elapsedTime,60)));
        }
        else{
            if(int(fmod(elapsedTime,60)) < 10){
                bufferA =  std::to_string(int(elapsedTime/60))+":0"+std::to_string(int(fmod(elapsedTime,60)));
            } else  bufferA = std::to_string(int(elapsedTime/60))+":"+std::to_string(int(fmod(elapsedTime,60)));
        }
            
        
        currentTimeText.setString(bufferA + " / " + bufferB);
        double percent = elapsedTime/playbackTime;
        fillBar.setScale(percent, 1);
    }
    else if(playbackStatus == true){
        playbackStatus = false;
        Terminal.print("Playback Complete");
        TopBar.setMode(4);
    }
}

void playBar::record(topBar &Topbar, terminal &Terminal,  bool &recordMode, int setRecordTime){
    elapsedTime = difftime(time(NULL),clipStart);
    
    if(setRecordTime == 0){
        bufferA = "00:00";
        bufferB = "00:00";
    }
    if(elapsedTime < setRecordTime){
        if(int(elapsedTime/60) < 10){
            if(int(fmod(elapsedTime,60)) < 10){
                bufferA = "0" + std::to_string(int(elapsedTime/60))+":0"+std::to_string(int(fmod(elapsedTime,60)));
            } else  bufferA = "0" + std::to_string(int(elapsedTime/60))+":"+std::to_string(int(fmod(elapsedTime,60)));
        }
        else{
            if(int(fmod(elapsedTime,60)) < 10){
                bufferA =  std::to_string(int(elapsedTime/60))+":0"+std::to_string(int(fmod(elapsedTime,60)));
            } else  bufferA = std::to_string(int(elapsedTime/60))+":"+std::to_string(int(fmod(elapsedTime,60)));
        }
        if(int(setRecordTime/60) < 10){
            if(int(fmod(setRecordTime,60)) < 10){
                bufferB = "0" + std::to_string(int(setRecordTime/60))+":0"+std::to_string(int(fmod(setRecordTime,60)));
            } else  bufferB = "0" + std::to_string(int(setRecordTime/60))+":"+std::to_string(int(fmod(setRecordTime,60)));
        }
        else{
            if(int(fmod(setRecordTime,60)) < 10){
                bufferB =  std::to_string(int(setRecordTime/60))+":0"+std::to_string(int(fmod(setRecordTime,60)));
            } else  bufferB = std::to_string(int(setRecordTime/60))+":"+std::to_string(int(fmod(setRecordTime,60)));
        }
        fillBar.setScale(1-elapsedTime/setRecordTime,1);
    }
    else if(elapsedTime > setRecordTime && recordMode == true){
        recordMode = false;
        Topbar.setMode(0);
        Terminal.print("Recording Finished");
        fillBar.setScale(0,1);
    }
    currentTimeText.setString(bufferA + " / " + bufferB);
}



