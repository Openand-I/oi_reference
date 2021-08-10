#include <iostream>
#include <fstream>

using namespace std;

string num2bitstring(unsigned long long num)
{
    unsigned long long mantissa = num;
    unsigned short remainder = 0;
    string tStr = "";
    
    while ( mantissa > 0 ) {
       remainder = mantissa % 2;
       mantissa /= 2;
       tStr.insert(0,to_string(remainder));
    }

    short leading_zeroes = 10 - tStr.length();
    
    if ( leading_zeroes > 0 ) for ( int i = 1; i <= leading_zeroes; i++ ) tStr.insert(0,"0");
    
    return tStr;
}

int check_range_of_color(int color)
{
    if ( color < 0 ) return -1;
    
    if ( color > 255 ) return 1;
    
    return 0;
}

int main() {
    cout << num2bitstring(256) << endl;
    
    fstream out_file;
    ifstream in_file;
    
   out_file.open("test_function.cpp",ios::out);  // open a file to perform write operation using file object
   if( ! out_file.is_open()) return(1);     //checking whether the file is open

   out_file<<"#include<string>\n\n#include \"test.h\"\n\nusing namespace std;\n\nstring bitString(unsigned long long num)\n{\n\tswitch(num) {\n"; //inserting text
//      newfile.close(); //close the file object
   
   in_file.open("header.txt", ios::in);
   if ( ! in_file.is_open() ) return(2);
   
   unsigned short r = 0, g = 0, b = 0;
   
   unsigned int line_num = 0;
   
   unsigned long long num = 0;
   
   long long COLORS[1024] = { -1 };
   
   while ( ! in_file.eof() ) {
    in_file >> r ; in_file >> g ; in_file >> b;  

    if ( in_file.eof() ) break;
    
    if ( check_range_of_color(r) != 0 ) return(3);
    if ( check_range_of_color(g) != 0 ) return(4);
    if ( check_range_of_color(b) != 0 ) return(5);
    
    num = r * 256 * 256 + g * 256 + b;
   
    unsigned short found = 0;
    for ( int i = 0 ; i < line_num ; i++ ) if ( COLORS[i] == num ) { found = 1; break; }
    
    if ( found == 0 ) 
        out_file << "\tcase " << num << " : " << "\t\t\treturn \"" << num2bitstring(line_num) << "\";\t\t\tbreak;\t\t" << endl;
    
    found = 0;
    COLORS[line_num] = num;
    
    line_num++;
   }
   
   out_file << "\t}\n\treturn \"\";\n}";
   
   in_file.close();
   
   out_file.close();
}
