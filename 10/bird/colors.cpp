#include <iostream>
#include <string>

#include "bird-1024.h"
#include "test.h"

using namespace std;
	
int main() {

//    cout << width << " " << height << endl;
    
    int i = 0, bit_needle = 0, LENGTH = 10;
    char *data = header_data; 
    unsigned short pixel[3];

   unsigned int line_num = 0;

   unsigned long long num = 0;

   long long COLORS[1024] = { -1 };
    
    while ( i++ < width * height ) {
        HEADER_PIXEL(data,pixel);
//cout << line_num << " : " << endl;
    num = pixel[0] * 256 * 256 + pixel[1] * 256 + pixel[2];

    unsigned short found = 0;
    for ( int i = 0 ; i < line_num ; i++ ) if ( COLORS[i] == num ) { found = 1; break; }
    
    if ( found == 0 ) {
        cout << pixel[0] << " " << pixel[1] << " " << pixel[2] << endl;
    
    found = 0;
    COLORS[line_num] = num;
    
    line_num++;
    }
    
    }
        
    //last bit is missing here. Complete this!
    
}
