#include <iostream>
#include <string>

#include "kodak-1024.h"
#include "test.h"

using namespace std;

void bits2byte(int *bits, char *byte) {
    //notice ALL the work is with "*byte" not "byte" which is the address of the byte.
    *byte = 0;
    for (int i = 0; i < 8; i++) {
        *byte <<= 1;
        if (bits[i] == 1) {
            *byte |= 1;
        }
    }
}

	string trimfnc(string str) {
//		const char* typeOfWhitespaces = " \t\n\r\f\v";
		const char* typeOfWhitespaces = " ";
//		str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
		str.erase(0,str.find_first_not_of(typeOfWhitespaces));
		return str;
	}
	
int main() {
    cout << bitString(460804) << endl;

    cout << width << " " << height << endl;
    
    int i = 0, bit_needle = 0, LENGTH = 10;
    char *data = header_data; 
    unsigned short pixel[3];

    int input_bits[] = {1, 1, 0, 1, 0, 0, 1, 1};
    char output_byte; //no use to put value here, we'll override it anyway...
    bits2byte(input_bits, &output_byte);
  
    printf("%u\n",(unsigned char)output_byte);
    
    string runningString = "";
    
    FILE *fp = fopen("kodak-1024.bitmap","w");
    
    while ( i++ < width * height ) {
        HEADER_PIXEL(data,pixel);
        
        unsigned long long val = pixel[0] * 256 * 256 + pixel[1] * 256 + pixel[2];
        
        string eq_bitString = bitString(val);
        
        if ( eq_bitString == "" ) { cout << "=" << val << " " << pixel[0] << " " << pixel[1] << " " << pixel[2] << endl; cout << "Invalid colour" << endl; return 1; }
        
        runningString += eq_bitString;

//        cout << eq_bitString << endl;
        
        while ( runningString.length() >= 8 ) {
            for ( short j = 0; j < 8 ; j++ ) { input_bits[j] = (short)runningString[j] - 48; runningString[j] = ' '; }
            runningString = trimfnc(runningString);
            bits2byte(input_bits, &output_byte);
            fprintf(fp,"%c",output_byte);
        }
        //LENGTH = eq_bitString.length();
        
//        for ( short j = 0 ; j < LENGTH; j++ ) if ( eq_bitString[j] == '1' ) bit_map_set(b,i*LENGTH+j); 
        
    }
    
    while ( runningString.length() > 0 ) {
        for ( short j = 0; j < 8; j++ ) input_bits[j] = 0;
        for ( short j = 0; j < runningString.length(); j++ ) { input_bits[j] = (short)runningString[j] - 48; runningString[j] = ' '; }
            runningString = trimfnc(runningString);
            bits2byte(input_bits, &output_byte);
            fprintf(fp,"%c",output_byte);
        }
    
    fclose(fp);
    
    //last bit is missing here. Complete this!
    
}
