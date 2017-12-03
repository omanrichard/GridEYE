//
//  main.cpp
//  GridEYE Test Program
//
//  Created by Richard Oman on 12/1/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <wiringPiI2C.h>
#include <wiringPi.h>

#define PGE     0x68    // Panasonic GridEye Address
#define PCR     0x00    // Power Control Register// Normal Mode Cmd: 0x00
#define RESET   0x01    // Reset Register
#define FrRate  0x02    // Frame Rate Register//    10/default: 0x00, 1: 0x01

using namespace std;

int row, col;


//-----------------------------------------------------------------
// GridEYE Class
//-----------------------------------------------------------------
class GridEYE{
friend class video;
private:
    int FPS;        // 1 or 10 FPS
    int runtime;    // Run Time in seconds
    bool DR;        // True: TRUE, Human: FALSE
    int fd;         // File Descriptor for I2C functions

public:
    GridEYE();
    GridEYE(int address); //Hint: My board has it set at 0x68 :)
    ~GridEYE();
    
    void reset();
    void wake();
    int read( int pixAddr );
    
    void setFPS( int temp );
    void setRunTime( int newTime );

    int getfd();
    int getFPS();
};

//-----------------------------------------------------------------
// pixMask Class
//-----------------------------------------------------------------
class pixMask{
private:
	int r,g,b;

public:
	pixMask();
	~pixMask();

	void update( short temp );

	int getr();	// access r value
	int getg();	// access g value
	int getb();	// access b value
};

//-----------------------------------------------------------------
// Frame Class
//-----------------------------------------------------------------
class frame{                        //      Stores sensor data
                                    //     0  1  2  3  4  5  6  7
protected:                          // 0  [] [] [] [] [] [] [] []
    float mean;                     // 1  [] [] [] [] [] [] [] []
    short max;                      // 3  [] [] [] [] [] [] [] []
    short sensor_values[8][8];      // 4  [] [] [] [] [] [] [] []
                                    // 4  [] [] [] [] [] [] [] []
    void set_max();         // 5  [] [] [] [] [] [] [] []
    void set_mean();        // 6  [] [] [] [] [] [] [] []
    // 7  [] [] [] [] [] [] [] []
public:
    
    frame();
    frame(GridEYE* gPtr);
    ~frame();
    
    short access( short row , short col );
    short get_max();
    float get_mean();
    
    void new_max( short newMax );
    void new_mean( float newMean );
    
    void print();
    
};

//-----------------------------------------------------------------
// Video Class
//-----------------------------------------------------------------
class video{
private:
    short frameCount; // frameCount = FPS * runtime
    short FPS;
    int runtime;
    
    short max;
    float mean;
    
    vector< frame* > data;  // Storing up to 31,800 frames maximum
    
    void set_max();
    void set_mean();
    
public:
    video();
    video( GridEYE* gPtr );
    ~video();
    
    void addFrame( frame* fPtr );
    frame* getFrame( int index );
    
    void set_runtime( int val );
    short getframeCount();
    void exportVideo( string filename );
    void print(pixMask* pixPtr);
    
};

//-----------------------------------------------------------------
// Session Class
//-----------------------------------------------------------------
class session{
private:
    vector< video* > current; // session.current[vCount]
    int vCount;
    
public:
    session();
    session( video* newVid );
    ~session();
    
    void addVideo( video* newVid ); // Implement Save button
    void undoRec();                 // Implement Delete Button
    void print();
};


//-----------------------------------------------------------------
// Main
//-----------------------------------------------------------------

int main(int argc, const char * argv[]) {
    
    cout << "Program Start" << endl << endl;
    
    cout << "Session Started" << endl;
	
	pixMask* pixPtr = new pixMask();    

    GridEYE* gPtr = new GridEYE();
    cout << "GridEYE Initialized" << endl;
    
    video session( gPtr );
    cout << "Video Object created" << endl;
    
	session.print(pixPtr);
	
    session.exportVideo("PGEtest.txt");
    cout << "Video exported" << endl;
    
    cout << "Exiting Program" << endl;
    return 0;
}


//-----------------------------------------------------------------
// GridEYE Methods
//-----------------------------------------------------------------

GridEYE::GridEYE(){
    fd = wiringPiI2CSetup( PGE );
    wiringPiI2CWriteReg16(fd, PCR, 0);
}

int GridEYE::read( int pixAddr ){
    int temp = 0;
    wiringPiI2CWriteReg16( fd, pixAddr, 1 );    // Write to pixel, requests data
    temp = wiringPiI2CReadReg16( fd, pixAddr ); // Receive value from pixel
    temp = temp >> 2;                           // Thermistor has 12-bit data
                                                // Shift 4 removes precision Bits, makes short data 8-bit temperature
    return temp;
}

void GridEYE::reset(void){
    FPS = 10;
    wiringPiI2CWriteReg16( fd, 0x02, 0 ); // Resets Frame rate register to default
    DR = true;
    return;
}

int GridEYE::getfd(){
    return this->fd;
}

int GridEYE::getFPS(){
    return this->FPS;
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

void GridEYE::setRunTime( int newTime ){
    this->runtime = newTime;
}

//-----------------------------------------------------------------
// Frame Methods
//-----------------------------------------------------------------
frame::frame(){
    for( row=0 ; row < 8 ; row++ ){
        for( col=0 ; col < 8 ; col++){
            this->sensor_values[row][col] = 0;
        }
    }
    this->mean = 0;
    this->max = 0;
    return;
}

frame::frame(GridEYE* gPtr){
    int temp = 0;
    int pixAddr = 0x80;
    
    for( row = 0 ; row < 8 ; row++ ){
        for( col = 0 ; col < 8 ;  col++){
            temp = gPtr->read( pixAddr );                // Read Thermistor Data
            this->sensor_values[row][col] = (short)temp;    // Stores temp value in sensor table
            pixAddr += 2;                                   // Increment to next pixel
        }
    }
    set_max();
    set_mean();
    return;
    
    return;
}
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

void frame::print(){
    
    for( col = 0 ; col < 8 ; col++){                                        // Frame No. : 1
        cout << "\t"                                      // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
        << "[ " << this->sensor_values[col][0] << " ] "   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
        << "[ " << this->sensor_values[col][1] << " ] "   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
        << "[ " << this->sensor_values[col][2] << " ] "   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
        << "[ " << this->sensor_values[col][3] << " ] "   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
        << "[ " << this->sensor_values[col][4] << " ] "   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
        << "[ " << this->sensor_values[col][5] << " ] "   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
        << "[ " << this->sensor_values[col][6] << " ] "   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
        << "[ " << this->sensor_values[col][7] << " ] " << endl;
    }
    return;
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
    
}
video::video( GridEYE* gPtr ){
    frame* temp;
    
    frameCount = (1 * 10);
    
    for( int x = 0 ; x < frameCount ; x++){
	delayMicroseconds(500000);
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

void video::exportVideo( string filename ){
    fstream newOutput;                      // Creates/Opens new output file
    newOutput.open( filename, ios::out );
    
    newOutput << "*" << frameCount;    // Copies data from memory to file
    
    for( int x = 0; x < frameCount; x++ ){
        frame* temp = (data[x]);
        newOutput << "%" << x;                                              // Begin Packet % indicates frame number
        newOutput << "&" << temp->get_max() << "&" << temp->get_mean();     // & indicates sub-data value
        for( int y = 0; y < 8 ; y++){
            newOutput << "@" << "$" << temp->access( y, 0 )             // @ indicates row begin
            << "$" << temp->access( y, 1 )
            << "$" << temp->access( y, 2 )             // $ indicates data value
            << "$" << temp->access( y, 3 )
            << "$" << temp->access( y, 4 )
            << "$" << temp->access( y, 5 )
            << "$" << temp->access( y, 6 )
            << "$" << temp->access( y, 7 );
        }
        newOutput << "#"; // End Packet
    }
    newOutput.close( ); // Close file
    return;
}
/*/

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
/*/

void video::print(pixMask* pixPtr){
    frame* temp;
    for( int x = 0 ; x < frameCount ; x++ ){
        temp = this->data[row];
        cout << "Frame No. : " << x + 1 << endl;
	delayMicroseconds( 50000 );
        for( row = 0 ; row < 8 ; row++){               
            		cout << "\t";
		pixPtr->update( temp->access(row, 0) );
            		cout << "[ " << pixPtr->getr() << " ]\t";

            	pixPtr->update( temp->access(row, 1) );
			cout << "[ " << pixPtr->getr() << " ]\t"; 

           	pixPtr->update( temp->access(row, 2) );
			cout << "[ " << pixPtr->getr() << " ]\t"; 

		pixPtr->update( temp->access(row, 3) );
            		cout << "[ " << pixPtr->getr() << " ]\t"; 

           	pixPtr->update( temp->access(row, 4) );
			cout << "[ " << temp->access(col, 4) << " ]\t";

            	pixPtr->update( temp->access(row, 5) );	
			cout << "[ " << pixPtr->getr() << " ]\t";

            	pixPtr->update( temp->access(row, 6) );
			cout << "[ " << pixPtr->getr() << " ]\t";  
 
            	pixPtr->update( temp->access(row, 7) );	
			cout << "[ " << pixPtr->getr() << " ]" << endl;
        }
    }
}

void video::set_runtime( int val ){
    runtime = FPS * frameCount;
}

video::~video(){
    
}
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Session Methods
//-----------------------------------------------------------------
session::session(){     // Default Constructor
    this->vCount = 0;                           // Initializes video count to zero
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
    this->current.push_back( newVid );  // Append "active" recording to video stack
    this->vCount++;                     // Update video count value
}

void session::undoRec(){        // Removes "active" recording from the stack of videos
    this->current.pop_back();   // pop_back() removes last value, decrements vector size by 1
    this->vCount--;             // update video count value
}

session::~session(){}

//-----------------------------------------------------------------

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
          		G1 += 7;
          		B1 += 7;
      		}	
    
      		if(phase == 6){
        		G1 -= 7;
          		if(G1 <= 0) 
				phase = 7;
      		}
    
      		if(phase == 5){
          		R1 += 7;
          		if(R1 >= 252) 
				phase = 6;
      		}
     
     		if(phase == 4){
          		B1 -= 7;
          		if(B1 <= 0) 
				phase = 5;
      		}
    
      		if(phase == 3){
          		G1 += 7;
          		if( G1 >= 252) 
				phase = 4;
      		}
    
      		if(phase == 2){
          		R1 -= 7;
          		if( R1 <= 0) 
				phase = 3;
      		}
     
      		if(phase == 1){
           		R1 += 7;
           		B1 += 7;
           		if( R1 >= 252) 
				phase = 2;
      		}
    } // end for
}
