//
// Created by vadim on 7.01.21.
//
/////////////////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ШО ЗА НАХУЙ !!!!!!ПОЧЕМУ ВСЁ КРАСНОЕ????????????????????????777777 БЛЯТЬ

#ifndef LAB4_PE_H
#define LAB4_PE_H

#include <bits/stdc++.h>
#include "exceptions.h"

using namespace std;

struct Section {
    string name;
    uint32_t virtualSize = 0;
    uint32_t virtualAddress = 0;
    uint32_t sizeOfRawData = 0;
    uint32_t pointerToRawData = 0;
    uint32_t characteristics = 0;

    Section() = default;
};

class PE {
public:

    explicit PE(const string& filename) {
        this->exe = fopen(filename.c_str(), "rb");
        readFile(filename);
    }

private:

    FILE* exe;
    bool Executable = true;
    int pointerToPETable = 0;
    int sizeOfOptionalHeader = 0;
    uint16_t characteristics = 0;
    int numberOfSections = 0;
    string machineName;
    vector<Section> sections;

    static string stringToHex(uint32_t hexNum, int length = 8) {
        string temp;
        while (hexNum) {
            uint x = hexNum % 16;
            if (x < 10) {
                temp += char(x + '0');
            } else {
                temp += char(x + 'a');
            }
            hexNum /= 16;
        }
        while(temp.size() < length) {
            temp += "0";
        }
        reverse(temp.begin(), temp.end());
        return temp;
    }

    static string stringToHex(uint16_t hexNum, int length = 4) {
        string temp;
        while (hexNum) {
            int x = hexNum % 16;
            if (x < 10) {
                temp += char(x + '0');
            } else {
                temp += char(x + 'a');
            }
            hexNum /= 16;
        }
        while(temp.size() < length) {
            temp += "0";
        }
        reverse(temp.begin(), temp.end());
        return temp;
    }


    uint16_t getInt16() {
        uint16_t value = 0;
        fread(&value, 2, 1, exe);
        return value;
    }

    uint32_t getInt32(int size = 4) {
        uint32_t value = 0;
        fread(&value, size, 1, exe);
        return value;
    }

    std::string getString(int length)
    {
        std::string temp(length, 0);
        fread(&temp[0], 1, length, exe);
        return temp;
    }

    std::vector<uint8_t> getVector(int length)
    {
        std::string temps = getString(length);
        std::vector<uint8_t> temp(length);
        for (int i = 0; i < length; i++) {
            temp[i] = temps[i];
        }
        return temp;
    }

    static string getMachineName(uint16_t machine)
    {
        if (machine == 0x0) {
            return "Unknown";
        }

        if (machine == 0x1d3) {
            return "Matsushita AM33";
        }

        if(machine == 0x8664) {
            return "x64";
        }

        if(machine == 0x1c0) {
            return "ARM little endian";
        }

        if(machine == 0xaa64) {
            return "ARM64 little endian";
        }

        if(machine == 0x1c4) {
            return "ARM Thumb-2 little endian";
        }

        if(machine == 0xebc) {
            return "EFI byte code";
        }

        if(machine == 0x14c) {
            return "Intel 386 or later processors and compatible processors";
        }

        if(machine == 0x200) {
            return "Intel Itanium processor family";
        }

        if(machine == 0x9041) {
            return "Mitsubishi M32R little endian";
        }

        if(machine == 0x266) {
            return "MIPS16";
        }

        if(machine == 0x366) {
            return "MIPS with FPU";
        }

        if(machine == 0x466) {
            return "MIPS16 with FPU";
        }

        if(machine == 0x1f0) {
            return "Power PC little endian";
        }

        if(machine == 0x1f1) {
            return "Power PC with floating point support";
        }

        if(machine == 0x166) {
            return "MIPS little endian";
        }

        if(machine == 0x5032) {
            return "RISC-V 32-bit address space";
        }

        if(machine == 0x5064) {
            return "RISC-V 64-bit address space";
        }

        if(machine == 0x5128) {
            return "RISC-V 128-bit address space";
        }

        if(machine == 0x1a2) {
            return "Hitachi SH3";
        }

        if(machine == 0x1a3) {
            return "Hitachi SH3 DSP";
        }

        if(machine == 0x1a6) {
            return "Hitachi SH4";
        }

        if(machine == 0x1a8) {
            return "Hitachi SH5";
        }

        if(machine == 0x1c2) {
            return "Thumb";
        }

        if(machine == 0x169) {
            return "MIPS little-endian WCE v2";
        }

        throw exceptionPE("Don't have such architecture.");
    }

    bool checkExecutable() {
        fseek(exe, 0, SEEK_SET);
        int e_magic = getInt16();
        return e_magic == 0x5a4d;
    }

    void readPEHeader() {
        fseek(exe, this->pointerToPETable, SEEK_SET);
        int signature = getInt32();
        if (signature != 0x00004550) {
            throw exceptionPE("Not a PE file.");
        }
        int machine = getInt16();
        this->machineName = getMachineName(machine);
        this->numberOfSections = getInt16();

        fseek(exe, 12, SEEK_CUR);
        this->sizeOfOptionalHeader = getInt16();
        this->characteristics = getInt16();
    }

    void readSectionsTable() {
        fseek(exe, this->pointerToPETable + 24 + this->sizeOfOptionalHeader, SEEK_SET);
        this->sections.resize(this->numberOfSections, Section());
        for (auto& section : sections) {
            section.name = getString(8);
            section.virtualSize = getInt32();
            section.virtualAddress = getInt32();
            section.sizeOfRawData = getInt32();
            section.pointerToRawData = getInt32();
            fseek(exe, 12, SEEK_CUR);
            section.characteristics = getInt32();
        }
    }

    void readFile(const string& filename) {
        if (!checkExecutable()) {
            this->Executable = false;
        }
        fseek(exe, 0x3c, SEEK_SET);
        this->pointerToPETable = getInt32();
        readPEHeader();
        readSectionsTable();
    }

public:

    void showHeaderInfo() {
        if(this->Executable)
        {
            cout << "File is executable." << endl;
        }
        else
        {
            cout << "File is object." << endl;
        }
        cout << "Architecture:\t" << machineName << endl;
        cout << "Characteristics:\t" << "0x" + stringToHex(characteristics) << endl << endl;
    }

    void showSectionsInfo() {
        cout << "Idx\t" << "Name\t" << "Size\t\t" << "VMA\t\t\t" << "LMA\t\t\t" << "File off\t\t" << endl;
        for(int i = 0; i < this->numberOfSections; i++) {
            cout << i + 1 << "\t" << sections[i].name << "\t" << "0x" + stringToHex(sections[i].virtualSize) << "\t" << "0x" + stringToHex(sections[i].virtualAddress) << "\t" << "0x" + stringToHex(sections[i].virtualAddress) << "\t" << "0x" + stringToHex(sections[i].pointerToRawData) << endl;
            cout << "Characteristics:\t" << "0x" + stringToHex(sections[i].characteristics, 8) << endl;
        }
    }
};


#endif //LAB4_PE_H
