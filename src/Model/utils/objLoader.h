#ifndef OBJLOADER_H_
#define OBJLOADER_H_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "extstring.h"

class ObjLoader{
public:
    template<class T>
    void search_data(const std::vector<std::string> data, std::vector<T> &coordinate, const std::string &skip, bool isInt = false){
        for(auto x : data){
            if(x == skip) continue;
            if(isInt)
                coordinate.push_back(stof(x));
            else
                coordinate.push_back(stoi(x) - 1);
        }
    }

    // vertex buffer for glDrawArrays
    void create_vertex_buffer(float* vertices, float* textures, float* normals){
        buf = new float[M * 8];
        L = M * 8;
        for(int i = 0; i < 3 * M; i += 3){
            int idx = indices[i];
            int offset = i / 3 * 8;
            memcpy(buf + offset, vertices + idx * 3, 3 * sizeof(float));
            offset += 3;
            idx = indices[i + 1];
            memcpy(buf + offset, textures + idx * 2, 2 * sizeof(float));
            offset += 2;
            idx = indices[i + 2];
            memcpy(buf + offset, normals + idx * 3, 3 * sizeof(float));
        }
    }

    // unique buffer for glDrawElement
    void create_unique_vertex_buffer(float* vertices, float* textures, float* normals){
        int *ver2tex = new int[N];
        int *ver2nor = new int[N];
        for(int i = 0; i < 3 * M; i += 3){
            int vidx = indices[i];
            int tidx = indices[i + 1];
            int nidx = indices[i + 2];
            ver2tex[vidx] = tidx;
            ver2nor[vidx] = nidx;
        }
        buf = new float[N * 8];
        L = N * 8;
        for(int i = 0; i < 3 * N; i += 3){
            int offset = i / 3 * 8;
            memcpy(buf + offset, vertices + i, 3 * sizeof(float));
            offset += 3;
            memcpy(buf + offset, textures + ver2tex[i / 3], 2 * sizeof(float));
            offset += 2;
            memcpy(buf + offset, normals + ver2nor[i / 3], 3 * sizeof(float));
        }
        delete ver2tex;
        delete ver2nor;
    }

    void show_buffer(){
        for(int i = 0; i < L; i += 8){
            for(int j = 0; j < 8; j++)
                printf(" %f", buf[i + j]);
            printf("\n");
        }
    }

    void load_model(const char* path, bool drawElement = true){
        std::vector<float> ver_coords;
        std::vector<float> tex_coords;
        std::vector<float> nor_coords;
        std::vector<int> index;

        N = M = L = 0;

        std::fstream f(path, std::ios::in);
        std::string line;
        while(std::getline(f, line)){
            std::vector<std::string> values = split(line, ' ');
            if(values[0] == "v")
                search_data(values, ver_coords, "v", false);
            else if(values[0] == "vt")
                search_data(values, tex_coords, "vt", false);
            else if(values[0] == "vn")
                search_data(values, nor_coords, "vn", false);
            else if(values[0] == "f"){
                int l = values.size();
                for(int i = 1; i < l; i++){
                    std::vector<std::string> val = split(values[i], '/');
                    search_data(val, index, "f", true);
                }
            }
        }

        float *vertices = new float[ver_coords.size()];
        float *textures = new float[tex_coords.size()];
        float *normals = new float[nor_coords.size()];
        std::copy(ver_coords.begin(), ver_coords.end(), vertices);
        std::copy(tex_coords.begin(), tex_coords.end(), textures);
        std::copy(nor_coords.begin(), nor_coords.end(), normals);
        std::copy(index.begin(), index.end(), indices);
        N = ver_coords.size() / 3;
        M = index.size() / 3;

        if(drawElement)
            create_unique_vertex_buffer(vertices, textures, normals);
        else
            create_vertex_buffer(vertices, textures, normals);
    }




private:
    float *buf;
    int *indices;
    int N, M, L;

};


#endif