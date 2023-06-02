#pragma once
#define CGIF_H
#include <iostream>
#include <fstream>
#include <string.h>


class cgif
{
    std::ifstream file;
    int Canva_width;
    int Canva_height;
    int Image_top;
    int Image_left;
    int Height;
    int Width;
    bool GlobalColorTab;
    int GlobalColorTable_size;
    bool LocalColorTab;
    int LocalColorTable_size;
    int GraphicControlExtension_block_size;
    int dictionary_size;
    int in_code_size;
    int  codes_number;
    bool animation;
    int animation_tam;

    char* name;
    int* devolverColor(int  pos);
    void LocalColorTabl();
    void GlobalColorTabl();
public:
    cgif(char* ImageName);
    char* get_name(){return this->name;};
    int get_Canva_width(){return this->Canva_width;};
    int get_Canva_height(){return this->Canva_height;};
    int get_Image_top(){return this->Image_top;};
    int get_Image_left(){return this->Image_left;};
    int height(){return this->Height;};
    int width(){return this->Width;};
    int get_GlobalColorTable_size(){return this->GlobalColorTable_size;};
    bool GlobalColorTable_exist(){return this->GlobalColorTab;};
    int get_LocalColorTable_size(){return this->LocalColorTable_size;};
    bool LocalColorTable_exist(){return this->LocalColorTab;};
    int get_GraphicControlExtension_block_size(){return this->GraphicControlExtension_block_size;};
    int get_Dictionary_size(){return this->dictionary_size;};





    bool type();
    std::string version();
    void header();
    void logicalScreenDescriptor();
    void GlobalColorTable();
    void GraphicControlExtension();
    void ImageDescriptor();
    void LocalColorTable();
    void ImageData();
    void interpretate();
    void sh();
    virtual ~cgif();

protected:

private:
};

// CGIF_H
