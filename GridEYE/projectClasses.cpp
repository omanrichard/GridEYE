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
        wiringPiI2CWriteReg16(fd, PCR, 0);
     
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
int GridEYE::read( int pixAddr ){
    int temp = 0;
    int result = 0;
    
    //temp = rand() % 90;
    
    
    
    wiringPiI2CWriteReg16( fd, pixAddr, 1 );     // Write to pixel, requests data
    temp = wiringPiI2CReadReg16( fd, pixAddr );  // Receive value from pixel
    wiringPiI2CWriteReg16( fd, pixAddr, 0);
    
     temp = temp&0x0800;
     temp = temp >> 1;                          // Thermistor has 12-bit data
                                                // Shift 2 removes precision Bits, makes short data 8-bit temperature
    
    return temp;
}

void GridEYE::reset(void){
    FPS = 10;
    runtime = 10;
        wiringPiI2CWriteReg16( fd, 0x02, 0 ); // Resets Frame rate register to default
    DR = true;
    return;
}

void GridEYE::setFD(void){
    //fd = wiringPiI2CSetup( PGE );
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
            wiringPiI2CWriteReg16( fd, 0x02, 1 );   // Sets Frame rate register to 1 FPS
        if( temp == 10 )
            wiringPiI2CWriteReg16(fd, 0x02, 0);     // Sets Frame rate register to 10 FPS
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
void pixMask::lazyUpdate(int temp){
    
    switch(temp){
        case 0:
            this->r = 127;
            this->g = 0;
            this->b = 127;
            break;
        case 1:
            this->r = 125;
            this->g = 0;
            this->b = 127;
            break;
        case 2:
            this->r = 123;
            this->g = 0;
            this->b = 127;
            break;
        case 3:
            this->r = 121;
            this->g = 0;
            this->b = 127;
            break;
        case 4:
            this->r = 119;
            this->g = 0;
            this->b = 127;
            break;
        case 5:
            this->r = 117;
            this->g = 0;
            this->b = 127;
            break;
        case 6:
            this->r = 115;
            this->g = 0;
            this->b = 127;
            break;
        case 8:
            this->r = 113;
            this->g = 0;
            this->b = 127;
            break;
        case 9:
            this->r = 111;
            this->g = 0;
            this->b = 127;
            break;
        case 10:
            this->r = 109;
            this->g = 0;
            this->b = 127;
            break;
        case 11:
            this->r =
            this->g =
            this->b =
            break;
        case 12:
            this->r =
            this->g =
            this->b =
            break;
        case 13:
            this->r =
            this->g =
            this->b =
            break;
        case 14:
            this->r =
            this->g =
            this->b =
            break;
        case 15:
            this->r =
            this->g =
            this->b =
            break;
        case 16:
            this->r =
            this->g =
            this->b =
            break;
        case 17:
            this->r =
            this->g =
            this->b =
            break;
        case 18:
            this->r =
            this->g =
            this->b =
            break;
        case 19:
            this->r =
            this->g =
            this->b =
            break;
        case 20:
            this->r =
            this->g =
            this->b =
            break;
        case 21:
            this->r =
            this->g =
            this->b =
            break;
        case 22:
            this->r =
            this->g =
            this->b =
            break;
        case 23:
            this->r =
            this->g =
            this->b =
            break;
        case 24:
            this->r =
            this->g =
            this->b =
            break;
        case 25:
            this->r =
            this->g =
            this->b =
            break;
        case 26:
            this->r =
            this->g =
            this->b =
            break;
        case 27:
            this->r =
            this->g =
            this->b =
            break;
        case 28:
            this->r =
            this->g =
            this->b =
            break;
        case 29:
            this->r =
            this->g =
            this->b =
            break;
        case 30:
            this->r =
            this->g =
            this->b =
            break;
        case 31:
            this->r =
            this->g =
            this->b =
            break;
        case 32:
            this->r =
            this->g =
            this->b =
            break;
        case 33:
            this->r =
            this->g =
            this->b =
            break;
        case 34:
            this->r =
            this->g =
            this->b =
            break;
        case 35:
            this->r =
            this->g =
            this->b =
            break;
        case 36:
            this->r =
            this->g =
            this->b =
            break;
        case 37:
            this->r =
            this->g =
            this->b =
            break;
        case 38:
            this->r =
            this->g =
            this->b =
            break;
        case 39:
            this->r =
            this->g =
            this->b =
            break;
        case 40:
            this->r =
            this->g =
            this->b =
            break;
        case 41:
            this->r =
            this->g =
            this->b =
            break;
        case 42:
            this->r =
            this->g =
            this->b =
            break;
        case 43:
            this->r =
            this->g =
            this->b =
            break;
        case 44:
            this->r =
            this->g =
            this->b =
            break;
        case 45:
            this->r =
            this->g =
            this->b =
            break;
        case 46:
            this->r =
            this->g =
            this->b =
            break;
        case 47:
            this->r =
            this->g =
            this->b =
            break;
        case 48:
            this->r =
            this->g =
            this->b =
            break;
        case 49:
            this->r =
            this->g =
            this->b =
            break;
        case 50:
            this->r =
            this->g =
            this->b =
            break;
        case 51:
            this->r =
            this->g =
            this->b =
            break;
        case 52:
            this->r =
            this->g =
            this->b =
            break;
        case 53:
            this->r =
            this->g =
            this->b =
            break;
        case 54:
            this->r =
            this->g =
            this->b =
            break;
        case 55:
            this->r =
            this->g =
            this->b =
            break;
        case 56:
            this->r =
            this->g =
            this->b =
            break;
        case 57:
            this->r =
            this->g =
            this->b =
            break;
        case 58:
            this->r =
            this->g =
            this->b =
            break;
        case 59:
            this->r =
            this->g =
            this->b =
            break;
        case 60:
            this->r =
            this->g =
            this->b =
            break;
        case 61:
            this->r =
            this->g =
            this->b =
            break;
        case 62:
            this->r =
            this->g =
            this->b =
            break;
        case 63:
            this->r =
            this->g =
            this->b =
            break;
        case 64:
            this->r =
            this->g =
            this->b =
            break;
        case 65:
            this->r =
            this->g =
            this->b =
            break;
        case 66:
            this->r =
            this->g =
            this->b =
            break;
        case 67:
            this->r =
            this->g =
            this->b =
            break;
        case 68:
            this->r =
            this->g =
            this->b =
            break;
        case 69:
            this->r =
            this->g =
            this->b =
            break;
        case 70:
            this->r =
            this->g =
            this->b =
            break;
        case 71:
            this->r =
            this->g =
            this->b =
            break;
        case 72:
            this->r =
            this->g =
            this->b =
            break;
        case 73:
            this->r =
            this->g =
            this->b =
            break;
        case 74:
            this->r =
            this->g =
            this->b =
            break;
        case 75:
            this->r =
            this->g =
            this->b =
            break;
        case 76:
            this->r =
            this->g =
            this->b =
            break;
        case 77:
            this->r =
            this->g =
            this->b =
            break;
        case 78:
            this->r =
            this->g =
            this->b =
            break;
        case 79:
            this->r =
            this->g =
            this->b =
            break;
        case 80:
            this->r =
            this->g =
            this->b =
            break;
        case 81:
            this->r =
            this->g =
            this->b =
            break;
        case 82:
            this->r =
            this->g =
            this->b =
            break;
        case 83:
            this->r =
            this->g =
            this->b =
            break;
        case 84:
            this->r =
            this->g =
            this->b =
            break;
        case 85:
            this->r =
            this->g =
            this->b =
            break;
        case 86:
            this->r =
            this->g =
            this->b =
            break;
        case 87:
            this->r =
            this->g =
            this->b =
            break;
        case 88:
            this->r =
            this->g =
            this->b =
            break;
        case 89:
            this->r =
            this->g =
            this->b =
            break;
        case 90:
            this->r =
            this->g =
            this->b =
            break;
        case 91:
            this->r =
            this->g =
            this->b =
            break;
        case 92:
            this->r =
            this->g =
            this->b =
            break;
        case 93:
            this->r =
            this->g =
            this->b =
            break;
        case 94:
            this->r =
            this->g =
            this->b =
            break;
        case 95:
            this->r =
            this->g =
            this->b =
            break;
        case 96:
            this->r =
            this->g =
            this->b =
            break;
        case 97:
            this->r =
            this->g =
            this->b =
            break;
        case 98:
            this->r =
            this->g =
            this->b =
            break;
        case 99:
            this->r =
            this->g =
            this->b =
            break;
        //100
        case 100:
            this->r = 127;
            this->g = 0;
            this->b = 127;
            break;
        case 101:
            this->r = 125;
            this->g = 0;
            this->b = 127;
            break;
        case 102:
            this->r = 123;
            this->g = 0;
            this->b = 127;
            break;
        case 103:
            this->r = 121;
            this->g = 0;
            this->b = 127;
            break;
        case 104:
            this->r = 119;
            this->g = 0;
            this->b = 127;
            break;
        case 105:
            this->r = 117;
            this->g = 0;
            this->b = 127;
            break;
        case 106:
            this->r = 115;
            this->g = 0;
            this->b = 127;
            break;
        case 108:
            this->r = 113;
            this->g = 0;
            this->b = 127;
            break;
        case 109:
            this->r = 111;
            this->g = 0;
            this->b = 127;
            break;
        case 110:
            this->r = 109;
            this->g = 0;
            this->b = 127;
            break;
        case 111:
            this->r =
            this->g =
            this->b =
            break;
        case 112:
            this->r =
            this->g =
            this->b =
            break;
        case 113:
            this->r =
            this->g =
            this->b =
            break;
        case 114:
            this->r =
            this->g =
            this->b =
            break;
        case 115:
            this->r =
            this->g =
            this->b =
            break;
        case 116:
            this->r =
            this->g =
            this->b =
            break;
        case 117:
            this->r =
            this->g =
            this->b =
            break;
        case 118:
            this->r =
            this->g =
            this->b =
            break;
        case 119:
            this->r =
            this->g =
            this->b =
            break;
        case 120:
            this->r =
            this->g =
            this->b =
            break;
        case 121:
            this->r =
            this->g =
            this->b =
            break;
        case 122:
            this->r =
            this->g =
            this->b =
            break;
        case 123:
            this->r =
            this->g =
            this->b =
            break;
        case 124:
            this->r =
            this->g =
            this->b =
            break;
        case 125:
            this->r =
            this->g =
            this->b =
            break;
        case 126:
            this->r =
            this->g =
            this->b =
            break;
        case 127:
            this->r =
            this->g =
            this->b =
            break;
        case 128:
            this->r =
            this->g =
            this->b =
            break;
        case 129:
            this->r =
            this->g =
            this->b =
            break;
        case 130:
            this->r =
            this->g =
            this->b =
            break;
        case 131:
            this->r =
            this->g =
            this->b =
            break;
        case 132:
            this->r =
            this->g =
            this->b =
            break;
        case 133:
            this->r =
            this->g =
            this->b =
            break;
        case 134:
            this->r =
            this->g =
            this->b =
            break;
        case 135:
            this->r =
            this->g =
            this->b =
            break;
        case 136:
            this->r =
            this->g =
            this->b =
            break;
        case 137:
            this->r =
            this->g =
            this->b =
            break;
        case 138:
            this->r =
            this->g =
            this->b =
            break;
        case 139:
            this->r =
            this->g =
            this->b =
            break;
        case 140:
            this->r =
            this->g =
            this->b =
            break;
        case 141:
            this->r =
            this->g =
            this->b =
            break;
        case 142:
            this->r =
            this->g =
            this->b =
            break;
        case 143:
            this->r =
            this->g =
            this->b =
            break;
        case 144:
            this->r =
            this->g =
            this->b =
            break;
        case 145:
            this->r =
            this->g =
            this->b =
            break;
        case 146:
            this->r =
            this->g =
            this->b =
            break;
        case 147:
            this->r =
            this->g =
            this->b =
            break;
        case 148:
            this->r =
            this->g =
            this->b =
            break;
        case 149:
            this->r =
            this->g =
            this->b =
            break;
        case 150:
            this->r =
            this->g =
            this->b =
            break;
        case 151:
            this->r =
            this->g =
            this->b =
            break;
        case 152:
            this->r =
            this->g =
            this->b =
            break;
        case 153:
            this->r =
            this->g =
            this->b =
            break;
        case 154:
            this->r =
            this->g =
            this->b =
            break;
        case 155:
            this->r =
            this->g =
            this->b =
            break;
        case 156:
            this->r =
            this->g =
            this->b =
            break;
        case 157:
            this->r =
            this->g =
            this->b =
            break;
        case 158:
            this->r =
            this->g =
            this->b =
            break;
        case 159:
            this->r =
            this->g =
            this->b =
            break;
        case 160:
            this->r =
            this->g =
            this->b =
            break;
        case 161:
            this->r =
            this->g =
            this->b =
            break;
        case 162:
            this->r =
            this->g =
            this->b =
            break;
        case 163:
            this->r =
            this->g =
            this->b =
            break;
        case 164:
            this->r =
            this->g =
            this->b =
            break;
        case 165:
            this->r =
            this->g =
            this->b =
            break;
        case 166:
            this->r =
            this->g =
            this->b =
            break;
        case 167:
            this->r =
            this->g =
            this->b =
            break;
        case 168:
            this->r =
            this->g =
            this->b =
            break;
        case 169:
            this->r =
            this->g =
            this->b =
            break;
        case 170:
            this->r =
            this->g =
            this->b =
            break;
        case 171:
            this->r =
            this->g =
            this->b =
            break;
        case 172:
            this->r =
            this->g =
            this->b =
            break;
        case 173:
            this->r =
            this->g =
            this->b =
            break;
        case 174:
            this->r =
            this->g =
            this->b =
            break;
        case 175:
            this->r =
            this->g =
            this->b =
            break;
        case 176:
            this->r =
            this->g =
            this->b =
            break;
        case 177:
            this->r =
            this->g =
            this->b =
            break;
        case 178:
            this->r =
            this->g =
            this->b =
            break;
        case 179:
            this->r =
            this->g =
            this->b =
            break;
        case 180:
            this->r =
            this->g =
            this->b =
            break;
        case 181:
            this->r =
            this->g =
            this->b =
            break;
        case 182:
            this->r =
            this->g =
            this->b =
            break;
        case 183:
            this->r =
            this->g =
            this->b =
            break;
        case 184:
            this->r =
            this->g =
            this->b =
            break;
        case 185:
            this->r =
            this->g =
            this->b =
            break;
        case 186:
            this->r =
            this->g =
            this->b =
            break;
        case 187:
            this->r =
            this->g =
            this->b =
            break;
        case 188:
            this->r =
            this->g =
            this->b =
            break;
        case 189:
            this->r =
            this->g =
            this->b =
            break;
        case 190:
            this->r =
            this->g =
            this->b =
            break;
        case 191:
            this->r =
            this->g =
            this->b =
            break;
        case 192:
            this->r =
            this->g =
            this->b =
            break;
        case 193:
            this->r =
            this->g =
            this->b =
            break;
        case 194:
            this->r =
            this->g =
            this->b =
            break;
        case 195:
            this->r =
            this->g =
            this->b =
            break;
        case 196:
            this->r =
            this->g =
            this->b =
            break;
        case 197:
            this->r =
            this->g =
            this->b =
            break;
        case 198:
            this->r =
            this->g =
            this->b =
            break;
        case 199:
            this->r =
            this->g =
            this->b =
            break;
            //200
        case 200:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
        case 0:
            this->r =
            this->g =
            this->b =
            break;
    }
    
    
    
    
}
void pixMask::fastUpdate( short temp ){
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
void pixMask::monoUpdate(short temp){
    this->r = temp;
    this->g = 0;
    this->b = 0;
}
void pixMask::update( short temp ){
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



