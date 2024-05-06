#include "IOManager.h"
#include<fstream>
#include "Error.h"

bool IOManager::readFileToBuffer(string filepath, vector<unsigned char>& buffer)
{
    ifstream file(filepath, ios::binary);
    if (file.fail()) {
        perror(filepath.c_str());
        //fatalError("No se puede abrir el archivo " + filepath);
            return false;
    }

    //recorrer todo el archivo para sacar el tama�o total
    file.seekg(0, ios::end);
    int fileSize = file.tellg();

    //quitar cabezera
    file.seekg(0, ios::beg);
    fileSize -= file.tellg();

    buffer.resize(fileSize);
    file.read((char*)&(buffer[0]), fileSize);
    file.close();

    return true;
}