#include <iostream>
#include <fstream>
#include <string>

const static int BUF_SIZE = 56;

using namespace std;

int main(int argc, char** argv)
{

    string writeTo;
    if(argc<2)
    {
        cout<< "Splits multichannel adx files into separate files, by dlohn"<<endl<<"adxsplitter <infile> ";
        return 1;
    }
    if(argc<3)
        writeTo = argv[1];
    else
        writeTo = argv[2];

    ifstream in(argv[1], ios_base::in | ios_base::binary);
    char buf[BUF_SIZE];
    in.read(buf, BUF_SIZE);

    short channels = (short)buf[7];
    short blocksize = (short)buf[5];
    short addr = (buf[2]<<8)+buf[3]+4;
    char* header = new char[addr];
    in.seekg(0, ios::beg);
    in.read(&header[0], addr);
    header[7] = 1;
    ofstream* outs = new ofstream[channels];
    for (short ch=0; ch<channels; ch++)
    {
        string s = writeTo;
        string s1 = "_";
        s1 += to_string(ch);
        s.insert(s.find_last_of('.'), s1);
        outs[ch] = ofstream(s, ios_base::out | ios_base::binary);
        outs[ch].write(&header[0], addr);
    }
    delete [] header;
    char* block = new char[blocksize]; 
    do
    {
        for (short ch=0; ch<channels; ch++)
        {
            in.read(&block[0], blocksize);
            outs[ch].write(&block[0], blocksize);
        }
    } while (in.gcount() > 0);
    delete [] block;

    for (short ch=0; ch<channels; ch++)
    {
        outs[ch].close();
    }

    in.close();

    return 0;
}
