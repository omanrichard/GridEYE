//
//  projectClasses.cpp
//  Project
//
//  Created by Grant Hilgert and Richard Oman on 11/11/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "projectClasses.h"
#include <wiringPiI2C.h>

#define PGE 0x68
#define PCR 0x00

using namespace std;
int row,col;

short fastVideo::playVideo(int frameNumber, int row, int col){
    int address = 0x80 + (10*2*row + 2*col);
    return videoFile[frameNumber].frame[address];
}



//-----------------------------------------------------------------
// GridEYE Constructors
//-----------------------------------------------------------------GridEYE::GridEYE(){

GridEYE::GridEYE(){
    
        fd = wiringPiI2CSetup( PGE );
        wiringPiI2CWriteReg8(fd, PCR, 0);
     
        FPS = 10;
        runtime = 10;
}
// Will remove eventually
GridEYE::GridEYE( int address ){
    FPS = 10;
    runtime = 10;
}

//-----------------------------------------------------------------
// GridEYE Methods
//-----------------------------------------------------------------
float GridEYE::read( int pixAddr ){
    int temp = 0;
    float result = 0;
    
    //temp = rand() % 90;
    
    
    wiringPiI2CWriteReg8( fd, pixAddr, 1 );     // Write to pixel, requests data
    temp = wiringPiI2CReadReg8( fd, pixAddr );  // Receive value from pixel
    wiringPiI2CWriteReg8( fd, pixAddr, 0);
                                                // Pixels have 12-bit data
    temp = (temp & 0x07FF);
    
    while( temp > 0x00 ){
        temp -= 0x04;
        result += 0.25;
    }
    
    return temp;
}

void GridEYE::reset(void){
    FPS = 10;
    runtime = 10;
        wiringPiI2CWriteReg8( fd, 0x02, 0 ); // Resets Frame rate register to default
    DR = true;
    return;
}

void GridEYE::setFD(void){
    fd = wiringPiI2CSetup( PGE );
}

int GridEYE::getfd(){
    return this->fd;
}

void GridEYE::setFPS(int temp){
    this->FPS = temp;
    
     try{
        if( temp == 1 || temp == 10 )
        throw -1;
        if( temp == 1 )
            wiringPiI2CWriteReg8( fd, 0x02, 1 );   // Sets Frame rate register to 1 FPS
        if( temp == 10 )
            wiringPiI2CWriteReg8(fd, 0x02, 0);     // Sets Frame rate register to 10 FPS
     }
     catch( int ){
         cout << "Exception Handled: invalid setting value" << endl;
     }
    
        return;
     }

GridEYE::~GridEYE(){
    
}


//-----------------------------------------------------------------
// pixMask Methods
//-----------------------------------------------------------------
pixMask::pixMask(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
    
    return;
}

pixMask::~pixMask(){}

int pixMask::getr(){
    return this->r;
}

int pixMask::getg(){
    return this->g;
}

int pixMask::getb(){
    return this->b;
}
void pixMask::lazyUpdate(float temp){
    
    int tempMask = ((temp*180)/127);
    
    switch(tempMask){
        case 0:
            this->r = 127;
            this->g = 0;
            this->b = 127;
            break;
        case 1:
            this->r = 120;
            this->g = 0;
            this->b = 127;
            break;
        case 2:
            this->r = 115;
            this->g = 0;
            this->b = 127;
            break;
        case 3:
            this->r = 110;
            this->g = 0;
            this->b = 127;
            break;
        case 4:
            this->r = 105;
            this->g = 0;
            this->b = 127;
            break;
        case 5:
            this->r = 100;
            this->g = 0;
            this->b = 127;
            break;
        case 6:
            this->r = 95;
            this->g = 0;
            this->b = 127;
            break;
        case 8:
            this->r = 80;
            this->g = 0;
            this->b = 127;
            break;
        case 9:
            this->r = 75;
            this->g = 0;
            this->b = 127;
            break;
        case 10:
            this->r = 70;
            this->g = 0;
            this->b = 127;
            break;
        case 11:
            this->r = 65;
            this->g = 0;
            this->b = 127;
            break;
        case 12:
            this->r = 60;
            this->g = 0;
            this->b = 127;
            break;
        case 13:
            this->r = 55;
            this->g = 0;
            this->b = 127;
            break;
        case 14:
            this->r = 50;
            this->g = 0;
            this->b = 127;
            break;
        case 15:
            this->r = 45;
            this->g = 0;
            this->b = 127;
            break;
        case 16:
            this->r = 40;
            this->g = 0;
            this->b = 127;
            break;
        case 17:
            this->r = 35;
            this->g = 0;
            this->b = 127;
            break;
        case 18:
            this->r = 30;
            this->g = 0;
            this->b = 127;
            break;
        case 19:
            this->r = 25;
            this->g = 0;
            this->b = 127;
            break;
        case 20:
            this->r = 20;
            this->g = 0;
            this->b = 127;
            break;
        case 21:
            this->r = 15;
            this->g = 0;
            this->b = 127;
            break;
        case 22:
            this->r = 10;
            this->g = 0;
            this->b = 127;
            break;
        case 23:
            this->r = 5;
            this->g = 0;
            this->b = 127;
            break;
        case 24:
            this->r = 0;
            this->g = 5;
            this->b = 127;
            break;
        case 25:
            this->r = 0;
            this->g = 10;
            this->b = 127;
            break;
        case 26:
            this->r = 0;
            this->g = 15;
            this->b = 127;
            break;
        case 27:
            this->r = 0;
            this->g = 20;
            this->b = 127;
            break;
        case 28:
            this->r = 0;
            this->g = 25;
            this->b = 127;
            break;
        case 29:
            this->r = 0;
            this->g = 30;
            this->b = 127;
            break;
        case 30:
            this->r = 0;
            this->g = 35;
            this->b = 127;
            break;
        case 31:
            this->r = 0;
            this->g = 40;
            this->b = 127;
            break;
        case 32:
            this->r = 0;
            this->g = 45;
            this->b = 127;
            break;
        case 33:
            this->r = 0;
            this->g = 50;
            this->b = 127;
            break;
        case 34:
            this->r = 0;
            this->g = 55;
            this->b = 127;
            break;
        case 35:
            this->r = 0;
            this->g = 60;
            this->b = 127;
            break;
        case 36:
            this->r = 0;
            this->g = 65;
            this->b = 127;
            break;
        case 37:
            this->r = 0;
            this->g = 70;
            this->b = 127;
            break;
        case 38:
            this->r = 0;
            this->g = 75;
            this->b = 127;
            break;
        case 39:
            this->r = 0;
            this->g = 80;
            this->b = 127;
            break;
        case 40:
            this->r = 0;
            this->g = 85;
            this->b = 127;
            break;
        case 41:
            this->r = 0;
            this->g = 90;
            this->b = 127;
            break;
        case 42:
            this->r = 0;
            this->g = 95;
            this->b = 127;
            break;
        case 43:
            this->r = 0;
            this->g = 100;
            this->b = 127;
            break;
        case 44:
            this->r = 0;
            this->g = 105;
            this->b = 127;
            break;
        case 45:
            this->r = 0;
            this->g = 110;
            this->b = 127;
            break;
        case 46:
            this->r = 0;
            this->g = 115;
            this->b = 127;
            break;
        case 47:
            this->r = 0;
            this->g = 120;
            this->b = 127;
            break;
        case 48:
            this->r = 0;
            this->g = 125;
            this->b = 127;
            break;
        case 49:
            this->r = 0;
            this->g = 127;
            this->b = 127;
            break;
        case 50:
            this->r = 0;
            this->g = 127;
            this->b = 125;
            break;
        case 51:
            this->r = 0;
            this->g = 127;
            this->b = 120;
            break;
        case 52:
            this->r = 0;
            this->g = 127;
            this->b = 115;
            break;
        case 53:
            this->r = 0;
            this->g = 127;
            this->b = 110;
            break;
        case 54:
            this->r = 0;
            this->g = 127;
            this->b = 105;
            break;
        case 55:
            this->r = 0;
            this->g = 127;
            this->b = 100;
            break;
        case 56:
            this->r = 0;
            this->g = 127;
            this->b = 95;
            break;
        case 57:
            this->r = 0;
            this->g = 127;
            this->b = 90;
            break;
        case 58:
            this->r = 0;
            this->g = 127;
            this->b = 85;
            break;
        case 59:
            this->r = 0;
            this->g = 127;
            this->b = 80;
            break;
        case 60:
            this->r = 0;
            this->g = 127;
            this->b = 75;
            break;
        case 61:
            this->r = 0;
            this->g = 127;
            this->b = 70;
            break;
        case 62:
            this->r = 0;
            this->g = 127;
            this->b = 65;
            break;
        case 63:
            this->r = 0;
            this->g = 127;
            this->b = 60;
            break;
        case 64:
            this->r = 0;
            this->g = 127;
            this->b = 55;
            break;
        case 65:
            this->r = 0;
            this->g = 127;
            this->b = 50;
            break;
        case 66:
            this->r = 0;
            this->g = 127;
            this->b = 45;
            break;
        case 67:
            this->r = 0;
            this->g = 127;
            this->b = 40;
            break;
        case 68:
            this->r = 0;
            this->g = 127;
            this->b = 35;
            break;
        case 69:
            this->r = 0;
            this->g = 127;
            this->b = 30;
            break;
        case 70:
            this->r = 0;
            this->g = 127;
            this->b = 25;
            break;
        case 71:
            this->r = 0;
            this->g = 127;
            this->b = 20;
            break;
        case 72:
            this->r = 0;
            this->g = 127;
            this->b = 15;
            break;
        case 73:
            this->r = 0;
            this->g = 127;
            this->b = 10;
            break;
        case 74:
            this->r = 0;
            this->g = 127;
            this->b = 5;
            break;
        case 75:
            this->r = 0;
            this->g = 127;
            this->b = 0;
            break;
        case 76:
            this->r = 5;
            this->g = 127;
            this->b = 0;
            break;
        case 77:
            this->r = 10;
            this->g = 127;
            this->b = 0;
            break;
        case 78:
            this->r = 15;
            this->g = 127;
            this->b = 0;
            break;
        case 79:
            this->r = 20;
            this->g = 127;
            this->b = 0;
            break;
        case 80:
            this->r = 25;
            this->g = 127;
            this->b = 0;
            break;
        case 81:
            this->r = 30;
            this->g = 127;
            this->b = 0;
            break;
        case 82:
            this->r = 35;
            this->g = 127;
            this->b = 0;
            break;
        case 83:
            this->r = 40;
            this->g = 127;
            this->b = 0;
            break;
        case 84:
            this->r = 45;
            this->g = 127;
            this->b = 0;
            break;
        case 85:
            this->r = 55;
            this->g = 127;
            this->b = 0;
            break;
        case 86:
            this->r = 60;
            this->g = 127;
            this->b = 0;
            break;
        case 87:
            this->r = 65;
            this->g = 127;
            this->b = 0;
            break;
        case 88:
            this->r = 70;
            this->g = 127;
            this->b = 0;
            break;
        case 89:
            this->r = 75;
            this->g = 127;
            this->b = 0;
            break;
        case 90:
            this->r = 80;
            this->g = 127;
            this->b = 0;
            break;
        case 91:
            this->r = 85;
            this->g = 127;
            this->b = 0;
            break;
        case 92:
            this->r = 90;
            this->g = 127;
            this->b = 0;;
            break;
        case 93:
            this->r = 95;
            this->g = 127;
            this->b = 0;
            break;
        case 94:
            this->r = 100;
            this->g = 127;
            this->b = 0;
            break;
        case 95:
            this->r = 105;
            this->g = 127;
            this->b = 0;
            break;
        case 96:
            this->r = 110;
            this->g = 127;
            this->b = 0;
            break;
        case 97:
            this->r = 115;
            this->g = 127;
            this->b = 0;
            break;
        case 98:
            this->r = 120;
            this->g = 127;
            this->b = 0;
            break;
        case 99:
            this->r = 125;
            this->g = 127;
            this->b = 0;
            break;
            //100
        case 100:
            this->r = 127;
            this->g = 125;
            this->b = 0;
            break;
        case 101:
            this->r = 127;
            this->g = 120;
            this->b = 0;
            break;
        case 102:
            this->r = 127;
            this->g = 115;
            this->b = 0;
            break;
        case 103:
            this->r = 127;
            this->g = 110;
            this->b = 0;
            break;
        case 104:
            this->r = 127;
            this->g = 115;
            this->b = 0;
            break;
        case 105:
            this->r = 127;
            this->g = 110;
            this->b = 0;
            break;
        case 106:
            this->r = 127;
            this->g = 105;
            this->b = 0;
            break;
        case 108:
            this->r = 127;
            this->g = 100;
            this->b = 0;
            break;
        case 109:
            this->r = 127;
            this->g = 95;
            this->b = 0;
            break;
        case 110:
            this->r = 127;
            this->g = 90;
            this->b = 0;
            break;
        case 111:
            this->r = 127;
            this->g = 85;
            this->b = 0;
            break;
        case 112:
            this->r = 127;
            this->g = 80;
            this->b = 0;
            break;
        case 113:
            this->r = 127;
            this->g = 75;
            this->b = 0;
            break;
        case 114:
            this->r = 127;
            this->g = 70;
            this->b = 0;
            break;
        case 115:
            this->r = 127;
            this->g = 65;
            this->b = 0;
            break;
        case 116:
            this->r = 127;
            this->g = 60;
            this->b = 0;
            break;
        case 117:
            this->r = 127;
            this->g = 55;
            this->b = 0;
            break;
        case 118:
            this->r = 127;
            this->g = 50;
            this->b = 0;
            break;
        case 119:
            this->r = 127;
            this->g = 45;
            this->b = 0;
            break;
        case 120:
            this->r = 127;
            this->g = 40;
            this->b = 0;
            break;
        case 121:
            this->r = 127;
            this->g = 35;
            this->b = 0;
            break;
        case 122:
            this->r = 127;
            this->g = 30;
            this->b = 0;
            break;
        case 123:
            this->r = 127;
            this->g = 25;
            this->b = 0;
            break;
        case 124:
            this->r = 127;
            this->g = 20;
            this->b = 0;
            break;
        case 125:
            this->r = 127;
            this->g = 15;
            this->b = 0;
            break;
        case 126:
            this->r = 127;
            this->g = 10;
            this->b = 0;
            break;
        case 127:
            this->r = 127;
            this->g = 5;
            this->b = 0;
            break;
        case 128:
            this->r = 127;
            this->g = 0;
            this->b = 0;
            break;
            //Phase 3
        case 129:
            this->r = 127;
            this->g = 0;
            this->b = 0;
            break;
        case 130:
            this->r = 127;
            this->g = 5;
            this->b = 5;
            break;
        case 131:
            this->r = 127;
            this->g = 10;
            this->b = 10;
            break;
        case 132:
            this->r = 127;
            this->g = 15;
            this->b = 15;
            break;
        case 133:
            this->r = 127;
            this->g = 20;
            this->b = 20;
            break;
        case 134:
            this->r = 127;
            this->g = 25;
            this->b = 25;
            break;
        case 135:
            this->r = 127;
            this->g = 30;
            this->b = 30;
            break;
        case 136:
            this->r = 127;
            this->g = 35;
            this->b = 35;
            break;
        case 137:
            this->r = 127;
            this->g = 35;
            this->b = 35;
            break;
        case 138:
            this->r = 127;
            this->g = 40;
            this->b = 40;
            break;
        case 139:
            this->r = 127;
            this->g = 45;
            this->b = 45;
            break;
        case 140:
            this->r = 127;
            this->g = 50;
            this->b = 50;
            break;
        case 141:
            this->r = 127;
            this->g = 55;
            this->b = 55;
            break;
        case 142:
            this->r = 127;
            this->g = 60;
            this->b = 60;
            break;
        case 143:
            this->r = 127;
            this->g = 65;
            this->b = 65;
            break;
        case 144:
            this->r = 127;
            this->g = 70;
            this->b = 70;
            break;
        case 145:
            this->r = 127;
            this->g = 75;
            this->b = 75;
            break;
        case 146:
            this->r = 127;
            this->g = 80;
            this->b = 80;
            break;
        case 147:
            this->r = 127;
            this->g = 85;
            this->b = 85;
            break;
        case 148:
            this->r = 127;
            this->g = 90;
            this->b = 90;
            break;
        case 149:
            this->r = 127;
            this->g = 95;
            this->b = 95;
            break;
        case 150:
            this->r = 127;
            this->g = 100;
            this->b = 100;
            break;
        case 151:
            this->r = 127;
            this->g = 105;
            this->b = 105;
            break;
        case 152:
            this->r = 127;
            this->g = 110;
            this->b = 110;
            break;
        case 153:
            this->r = 127;
            this->g = 115;
            this->b = 115;
            break;
        case 154:
            this->r = 127;
            this->g = 120;
            this->b = 120;
            break;
        case 155:
            this->r = 127;
            this->g = 125;
            this->b = 125;
            break;
        case 156:
            this->r = 130;
            this->g = 130;
            this->b = 130;
            break;
        case 157:
            this->r = 135;
            this->g = 135;
            this->b = 135;
            break;
        case 158:
            this->r = 140;
            this->g = 140;
            this->b = 140;
            break;
        case 159:
            this->r = 150;
            this->g = 150;
            this->b = 150;
            break;
        case 160:
            this->r = 155;
            this->g = 155;
            this->b = 155;
            break;
        case 161:
            this->r = 160;
            this->g = 160;
            this->b = 160;
            break;
        case 162:
            this->r = 165;
            this->g = 165;
            this->b = 165;
            break;
        case 163:
            this->r = 170;
            this->g = 170;
            this->b = 170;
            break;
        case 164:
            this->r = 175;
            this->g = 175;
            this->b = 175;
            break;
        case 165:
            this->r = 180;
            this->g = 180;
            this->b = 180;
            break;
        case 166:
            this->r = 185;
            this->g = 185;
            this->b = 185;
            break;
        case 167:
            this->r = 190;
            this->g = 190;
            this->b = 190;
            break;
        case 168:
            this->r = 195;
            this->g = 195;
            this->b = 195;
            break;
        case 169:
            this->r = 200;
            this->g = 200;
            this->b = 200;
            break;
        case 170:
            this->r = 205;
            this->g = 205;
            this->b = 205;
            break;
        case 171:
            this->r = 210;
            this->g = 210;
            this->b = 210;
            break;
        case 172:
            this->r = 215;
            this->g = 215;
            this->b = 215;
            break;
        case 173:
            this->r = 220;
            this->g = 220;
            this->b = 220;
            break;
        case 174:
            this->r = 225;
            this->g = 225;
            this->b = 225;
            break;
        case 175:
            this->r = 230;
            this->g = 230;
            this->b = 230;
            break;
        case 176:
            this->r = 235;
            this->g = 235;
            this->b = 235;
            break;
        case 177:
            this->r = 240;
            this->g = 240;
            this->b = 240;
            break;
        case 178:
            this->r = 245;
            this->g = 245;
            this->b = 245;
            break;
        case 179:
            this->r = 250;
            this->g = 250;
            this->b = 250;
            break;
        case 180:
            this->r = 255;
            this->g = 255;
            this->b = 255;
            break;
    }
       
            
      
          
       
}
void pixMask::fastUpdate( float temp ){
//Mapped data to a graph and used cos and sin to reconstruct it
//Should increases speed
//0 through 540 degrees of resoultion masked to 0 through 255 color values converted to radians by 180/PI
    int tempr = 255*cos(((540*temp)/255)*(180/3.14159));
    int tempg = -1*255*sin(2*((540*temp)/255)*(180/3.14159));
    int tempb = 255*sin(((540*temp)/255)*(180/3.14159));
    //Bound wave between 0 and 255. Clip wave below 0
    if(tempr > 0 && tempr <= 127){
        this->r = tempr;
    }
    else if(tempr < 1){
        this->r = 0;
    }
    else if(tempr > 127){
        this->r = 127;
    }
    
    if(tempg > 0 && tempr <= 127){
        this->g = tempg;
    }
    else if(tempg < 1){
        this->g = 0;
    }
    else if(tempg > 127){
        this->r = 127;
    }
    if(tempb > 0 && tempr <= 127){
        this->b = tempb;
    }
    else if(tempb < 1){
        this->b = 0;
    }
    else if(tempb > 127){
        this->r = 127;
    }
    
    this->g = -1*255*sin(((540*temp)/255)*(180/3.14159));
    this->b = 255*sin(((540*temp)/255)*(180/3.14159));
}
void pixMask::monoUpdate(float temp){
    this->r = temp;
    this->g = 0;
    this->b = 0;
}
void pixMask::update( float temp ){
    int R1 = 0;
    int G1 = 0;
    int B1 = 0;
    int phase = 1;
    
    for(int i = 0; i < 255; i++){
        if( temp >= i && temp < i+1){
            this->r = R1;
            this->g = G1;
            this->b = B1;
        }
        
        if(phase == 7){
            G1 += 15;
            B1 += 15;
        }
        
        if(phase == 6){
            G1 -= 15;
            if(G1 <= 0)
                phase = 7;
        }
        
        if(phase == 5){
            R1 += 15;
            if(R1 >= 252)
                phase = 6;
        }
        
        if(phase == 4){
            B1 -= 15;
            if(B1 <= 0)
                phase = 5;
        }
        
        if(phase == 3){
            G1 += 15;
            if( G1 >= 252)
                phase = 4;
        }
        
        if(phase == 2){
            R1 -= 15;
            if( R1 <= 0)
                phase = 3;
        }
        
        if(phase == 1){
            R1 += 15;
            B1 += 15;
            if( R1 >= 252)
                phase = 2;
        }
    } // end for
}

//----------------------------------------------------------------
// Frame Methods
//----------------------------------------------------------------
frame::frame(){
    //fastFrame newFrame;
    for( row=0 ; row < 8 ; row++ ){
        for( col=0 ; col < 8 ; col++){
            //newFrame.frame[row][col] = 0;
        }
    }
    this->mean = 0;
    this->max = 0;
    return;
}

/*
frame::frame(GridEYE &gridward){
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            //newFrame.frame[row][col] = gridward.randTemp();
            //this->sensor_values[row][col] = gridward.randTemp();  // Receive value from device, end transmission
        }
    }
    set_max();
    set_mean();
    return;
}
*/

frame::frame(GridEYE* gPtr){
    short temp = 0;
    int pixAddr = 0x80;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            temp = gPtr->read( pixAddr );                   // Read Thermistor Data
            this->sensor_values[row][col] = temp;    // Stores temp value in sensor table
            pixAddr += 2;                                   // Increment to next pixel
        }
    }
    set_max();
    set_mean();
    return;
}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Frame Methods
//-----------------------------------------------------------------
void frame::set_max(){
    short temp = 0;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            if( this->sensor_values[row][col] > temp )
                temp = this->sensor_values[row][col];
        }
    }
    this->max = temp;
}


void frame::set_mean(){
    float sum = 0;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            sum += this->sensor_values[row][col];
        }
    }
    this->mean = sum/64;
}

short frame::get_max(){
    return this->max;
}

float frame::get_mean(){
    return this->mean;
}

short frame::access( short row , short col ){
    return this->sensor_values[row][col];    //Accesses data point in data array
}

frame::~frame(){
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Video Constructors
//-----------------------------------------------------------------
video::video(){
    this->frameCount = 0;
    this->mean = 0;
    this->max = 0;
    
    cout << "Video Created" << endl;
}

video::video( GridEYE* gPtr ){
    frame* temp;
    
    frameCount = ( gPtr->FPS * gPtr->runtime );
    
    for( int x = 0 ; x < frameCount ; x++){
        if( gPtr->FPS == 10 ){
        }
        else{
        }
        temp = new frame( gPtr );       // Collect data and create frame
        this->data.push_back( temp );       // Store pointer in data Vector
    }
    //this->set_max();
    //this->set_mean();
    return;
}
//-----------------------------------------------------------------
// Video Methods
//-----------------------------------------------------------------
void video::addFrame(frame* fPtr){
    this->data.push_back(fPtr);
    this->frameCount++;
    //this->set_max();
    //this->set_mean();
}

int video::getframeCount(){
    return this->frameCount;
}

void video::setframeCount( int count ){
    this->frameCount = count;
}

void video::exportVideo( string filename ){
    frame* temp = NULL;
    fstream newOutput;                      // Creates/Opens new output file
    newOutput.open( filename, ios::out );

    newOutput << "Frame Count: " << this->frameCount
              << " Avg. Temp: "   << this->mean
              << " Max Temp: "    << this->max
              << endl;
    temp = this->getFrame(0);
    for( int x = 0 ; x < frameCount ; x++ ){
        

        newOutput << "Frame No. : " << x + 1 << endl;
        for( row = 0 ; row < 8 ; row++ ){                                        // Frame No. : 1
            newOutput << "\t"                           // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
            << "[ " << temp->access(row, 0) << " ]\t"   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
            << "[ " << temp->access(row, 1) << " ]\t"   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
            << "[ " << temp->access(row, 2) << " ]\t"   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
            << "[ " << temp->access(row, 3) << " ]\t"   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
            << "[ " << temp->access(row, 4) << " ]\t"   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
            << "[ " << temp->access(row, 5) << " ]\t"   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
            << "[ " << temp->access(row, 6) << " ]\t"   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
            << "[ " << temp->access(row, 7) << " ]\t" << endl;
        }
        temp = this->getFrame(x);
    }
    newOutput.close( ); // Close file
    return;
}

frame* video::getFrame( int frameNum ){
    return this->data[frameNum];
}

/*
void video::set_max(){
    short temp = 0;
    frame* framePtr = NULL;
    
    while(temp < this->frameCount){
        framePtr = data[temp];
        for( row = 0 ; row < 8 ; row++ ){
            for( col = 0 ; col < 8 ;  col++){
                if( framePtr->access(row,col) > temp )
                    temp = framePtr->access(row,col);
            }
        }
        temp++;
    }
    framePtr->new_max( temp );
    return;
}

void video::set_mean(){
    short temp = 0;
    float sum = 0;
    frame* framePtr = NULL;
    
    while(temp < this->frameCount){
        framePtr = data[temp];
        for( row = 0 ; row < 8 ; row++ ){
            for( col = 0 ; col < 8 ;  col++){
                sum += framePtr->get_mean();
            }
        }
        temp++;
    }
    framePtr->new_mean( sum / (64*frameCount) );
}
*/
video::~video(){
    
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Session Methods
//-----------------------------------------------------------------
session::session(){     // Default Constructor
    this->vCount = 0;                           // Initializes video count to zero
    this->current.push_back( NULL );
    cout << "Session Started" << endl << endl;
    return;
}

session::session( video* newVid ){      // constructor adds video pointer to session array
    cout << "Session Started" << endl << endl;
    try{
        if( !( this->vCount < 1 ) )
            throw -1;                       // Maybe throw error class instead, can do something later in main
        this->current.push_back( newVid );  // Adds video pointer into the array in first position
        this->vCount++;
    }
    catch( int ){
        cout << "Exception Handled" << endl;
    }
}

void session::addVideo( video* newVid ){
    if( vCount == 0 )
        this->current[0] = newVid;
    else
        this->current.push_back( newVid );  // Append "active" recording to video stack
    this->vCount++;                         // Update video count value
}

void session::undoRec(){        // Removes "active" recording from the stack of videos
    if( vCount == 0 ){
        this->current.push_back( NULL );
    }
    this->current.pop_back();   // pop_back() removes last value, decrements vector size by 1
    this->vCount--;             // update video count value

}

video* session::getVideo( int index ){
    return this->current[index];
}

session::~session(){}
//-----------------------------------------------------------------



