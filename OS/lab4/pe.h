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
    uint32_t pointerToRelocations = 0;
    uint16_t numberOfRelocations = 0;

    Section() = default;
};

struct RelocationPageInfo {
    uint32_t virtualAddress;
    map<int, int> relocationPageCount;

    RelocationPageInfo() = default;
};

class PE {
public:

    explicit PE(const string& filename) {
        this->exe = fopen(filename.c_str(), "rb");
        readFile(filename);
    }

private:

    FILE* exe;
    int signature = 0;
    bool Executable = true;
    int pointerToPETable = 0;
    int sizeOfOptionalHeader = 0;
    uint16_t characteristics = 0;
    int numberOfSymbols = 0;
    int numberOfSections = 0;
    int baseRelocationTableVirtualAddress = 0;
    int baseRelocationTableSize = 0;
    int pointerToSymbolTable = 0;
    int sectionAlignment = 0;
    time_t time;
    pair<string, int> machineName;
    vector<RelocationPageInfo> relocationSections;

    vector<Section> sections;

    static string stringToHex(uint32_t hexNum, int length = 8) {
        string temp;
        while (hexNum) {
            uint x = hexNum % 16;
            if (x < 10) {
                temp += char(x + '0');
            } else {
                temp += char(x - 10 + 'a');
            }
            hexNum /= 16;
        }
        while(temp.size() < length) {
            temp += "0";
        }
        reverse(temp.begin(), temp.end());
        temp = "0x" + temp;
        return temp;
    }

    static string stringToHex(uint16_t hexNum, int length = 8) {
        string temp;
        while (hexNum) {
            int x = hexNum % 16;
            if (x < 10) {
                temp += char(x + '0');
            } else {
                temp += char(x - 10 + 'a');
            }
            hexNum /= 16;
        }
        while(temp.size() < length) {
            temp += "0";
        }
        reverse(temp.begin(), temp.end());
        temp = "0x" + temp;
        return temp;
    }

    uint8_t getInt8() {
        uint8_t value = 0;
        fread(&value, 1, 1, exe);
        return value;
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
        std::string temp(length, ' ');
        fread(&temp[0], 1, length, exe);
        for (auto& c : temp) {
            if (c == 0) {
                c = ' ';
            }
        }
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

    static pair<string, int> getMachineName(uint16_t machine)
    {
        if (machine == 0x0) {
            return {"Unknown", machine};
        }

        if (machine == 0x1d3) {
            return {"Matsushita AM33", machine};
        }

        if(machine == 0x8664) {
            return {"x64", machine};
        }

        if(machine == 0x1c0) {
            return {"ARM little endian", machine};
        }

        if(machine == 0xaa64) {
            return {"ARM64 little endian", machine};
        }

        if(machine == 0x1c4) {
            return {"ARM Thumb-2 little endian", machine};
        }

        if(machine == 0xebc) {
            return {"EFI byte code", machine};
        }

        if(machine == 0x14c) {
            return {"Intel 386 or later processors and compatible processors", machine};
        }

        if(machine == 0x200) {
            return {"Intel Itanium processor family", machine};
        }

        if(machine == 0x9041) {
            return {"Mitsubishi M32R little endian", machine};
        }

        if(machine == 0x266) {
            return {"MIPS16", machine};
        }

        if(machine == 0x366) {
            return {"MIPS with FPU", machine};
        }

        if(machine == 0x466) {
            return {"MIPS16 with FPU", machine};
        }

        if(machine == 0x1f0) {
            return {"Power PC little endian", machine};
        }

        if(machine == 0x1f1) {
            return {"Power PC with floating point support", machine};
        }

        if(machine == 0x166) {
            return {"MIPS little endian", machine};
        }

        if(machine == 0x5032) {
            return {"RISC-V 32-bit address space", machine};
        }

        if(machine == 0x5064) {
            return {"RISC-V 64-bit address space", machine};
        }

        if(machine == 0x5128) {
            return {"RISC-V 128-bit address space", machine};
        }

        if(machine == 0x1a2) {
            return {"Hitachi SH3", machine};
        }

        if(machine == 0x1a3) {
            return {"Hitachi SH3 DSP", machine};
        }

        if(machine == 0x1a6) {
            return {"Hitachi SH4", machine};
        }

        if(machine == 0x1a8) {
            return {"Hitachi SH5", machine};
        }

        if(machine == 0x1c2) {
            return {"Thumb", machine};
        }

        if(machine == 0x169) {
            return {"MIPS little-endian WCE v2", machine};
        }

        throw exceptionPE("Don't have such architecture.");
    }

    string fileCharacteristics(uint32_t characteristics) {
        string result;
        map<uint16_t, string> characteristicsStrings = {
                {0x0001, "IMAGE_FILE_RELOCS_STRIPPED"},
                {0x0002, "IMAGE_FILE_EXECUTABLE_IMAGE"},
                {0x0004, "IMAGE_FILE_LINE_NUMS_STRIPPED"},
                {0x0008, "IMAGE_FILE_LOCAL_SYMS_STRIPPED"},
                {0x0010, "IMAGE_FILE_AGGRESSIVE_WS_TRIM"},
                {0x0020, "IMAGE_FILE_LARGE_ADDRESS_AWARE"},
                {0x0040, "cursed"},
                {0x0080, "IMAGE_FILE_BYTES_REVERSED_LO"},
                {0x0100, "IMAGE_FILE_32BIT_MACHINE"},
                {0x0200, "IMAGE_FILE_DEBUG_STRIPPED"},
                {0x0400, "IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP"},
                {0x0800, "IMAGE_FILE_NET_RUN_FROM_SWAP"},
                {0x1000, "IMAGE_FILE_SYSTEM"},
                {0x2000, "IMAGE_FILE_DLL"},
                {0x4000, "IMAGE_FILE_UP_SYSTEM_ONLY"},
                {0x8000, "IMAGE_FILE_BYTES_REVERSED_HI"}
        };
        for (const auto& x : characteristicsStrings) {
            if (characteristics & x.first) {
                if (!result.empty()) {
                    result += " | ";
                }
                result += x.second;
            }
        }
        return result;
    }

    string sectionCharacteristics(uint32_t characteristics) {
        string result;
        multimap<string, int> characteristicsStrings = {
                {"cursed", 0x00000000},
                {"cursed", 0x00000001},
                {"cursed", 0x00000002},
                {"cursed", 0x00000004},
                {"IMAGE_SCN_TYPE_NO_PAD", 0x00000008},
                {"cursed", 0x00000010},
                {"IMAGE_SCN_CNT_CODE", 0x00000020},
                {"IMAGE_SCN_CNT_INITIALIZED_DATA", 0x00000040},
                {"IMAGE_SCN_CNT_UNINITIALIZED_DATA", 0x00000080},
                {"IMAGE_SCN_LNK_OTHER", 0x00000100},
                {"IMAGE_SCN_LNK_INFO", 0x00000200},
                {"cursed", 0x00000400},
                {"IMAGE_SCN_LNK_REMOVE", 0x00000800},
                {"IMAGE_SCN_LNK_COMDAT", 0x00001000},
                {"IMAGE_SCN_GPREL", 0x00008000},
                {"IMAGE_SCN_MEM_PURGEABLE", 0x00020000},
                {"IMAGE_SCN_MEM_16BIT", 0x00020000},
                {"IMAGE_SCN_MEM_LOCKED", 0x00040000},
                {"IMAGE_SCN_MEM_PRELOAD", 0x00080000},
                {"IMAGE_SCN_ALIGN_1BYTES", 0x00100000},
                {"IMAGE_SCN_ALIGN_2BYTES", 0x00200000},
                {"IMAGE_SCN_ALIGN_4BYTES", 0x00300000},
                {"IMAGE_SCN_ALIGN_8BYTES", 0x00400000},
                {"IMAGE_SCN_ALIGN_16BYTES", 0x00500000},
                {"IMAGE_SCN_ALIGN_32BYTES", 0x00600000},
                {"IMAGE_SCN_ALIGN_64BYTES", 0x00700000},
                {"IMAGE_SCN_ALIGN_128BYTES", 0x00800000},
                {"IMAGE_SCN_ALIGN_256BYTES", 0x00900000},
                {"IMAGE_SCN_ALIGN_512BYTES", 0x00A00000},
                {"IMAGE_SCN_ALIGN_1024BYTES", 0x00B00000},
                {"IMAGE_SCN_ALIGN_2048BYTES", 0x00C00000},
                {"IMAGE_SCN_ALIGN_4096BYTES", 0x00D00000},
                {"IMAGE_SCN_ALIGN_8192BYTES", 0x00E00000},
                {"IMAGE_SCN_LNK_NRELOC_OVFL", 0x01000000},
                {"IMAGE_SCN_MEM_DISCARDABLE", 0x02000000},
                {"IMAGE_SCN_MEM_NOT_CACHED", 0x04000000},
                {"IMAGE_SCN_MEM_NOT_PAGED", 0x08000000},
                {"IMAGE_SCN_MEM_SHARED", 0x10000000},
                {"IMAGE_SCN_MEM_EXECUTE", 0x20000000},
                {"IMAGE_SCN_MEM_READ", 0x40000000},
                {"IMAGE_SCN_MEM_WRITE", 0x80000000}
        };
        for (const auto& x : characteristicsStrings) {
            if (characteristics & x.second) {
                if (!result.empty()) {
                    result += " | ";
                }
                result += x.first;
            }
        }
        return result;
    }

    string relocationName(uint32_t relocationType) {
        string result;
        map<pair<int, int>, string> relocationNames = {
                {{0, -1}, "IMAGE_REL_BASED_ABSOLUTE"},
                {{1, -1}, "IMAGE_REL_BASED_HIGH"},
                {{2, -1}, "IMAGE_REL_BASED_LOW"},
                {{3, -1}, "IMAGE_REL_BASED_HIGHLOW"},
                {{4, -1}, "IMAGE_REL_BASED_HIGHADJ"},
                {{5, 0x266}, "IMAGE_REL_BASED_MIPS_JMPADDR"},
                {{5, 0x366}, "IMAGE_REL_BASED_MIPS_JMPADDR"},
                {{5, 0x466}, "IMAGE_REL_BASED_MIPS_JMPADDR"},
                {{5, 0x166}, "IMAGE_REL_BASED_MIPS_JMPADDR"},
                {{5, 0x169}, "IMAGE_REL_BASED_MIPS_JMPADDR"},
                {{5, 0x1c0}, "IMAGE_REL_BASED_ARM_MOV32"},
                {{5, 0xaa64}, "IMAGE_REL_BASED_ARM_MOV32"},
                {{5, 0x1c4}, "IMAGE_REL_BASED_ARM_MOV32"},
                {{5, 0x1c2}, "IMAGE_REL_BASED_ARM_MOV32"},
                {{5, 0x5032}, "IMAGE_REL_BASED_RISCV_HIGH20"},
                {{5, 0x5064}, "IMAGE_REL_BASED_RISCV_HIGH20"},
                {{5, 0x5128}, "IMAGE_REL_BASED_RISCV_HIGH20"},
                {{6, -1}, "cursed"},
                {{7, 0x1c2}, "IMAGE_REL_BASED_THUMB_MOV32"},
                {{7, 0x5032}, "IMAGE_REL_BASED_RISCV_LOW12I"},
                {{7, 0x5064}, "IMAGE_REL_BASED_RISCV_LOW12I"},
                {{7, 0x5128}, "IMAGE_REL_BASED_RISCV_LOW12I"},
                {{8, 0x5032}, "IMAGE_REL_BASED_RISCV_LOW12S"},
                {{8, 0x5064}, "IMAGE_REL_BASED_RISCV_LOW12S"},
                {{8, 0x5128}, "IMAGE_REL_BASED_RISCV_LOW12S"},
                {{9, 166}, "IMAGE_REL_BASED_MIPS_JMPADDR16"},
                {{9, 169}, "IMAGE_REL_BASED_MIPS_JMPADDR16"},
                {{9, 266}, "IMAGE_REL_BASED_MIPS_JMPADDR16"},
                {{9, 366}, "IMAGE_REL_BASED_MIPS_JMPADDR16"},
                {{9, 466}, "IMAGE_REL_BASED_MIPS_JMPADDR16"},
                {{10, -1}, "IMAGE_REL_BASED_DIR64"}
        };
        int machine = this->machineName.second;
        if (relocationNames.count({relocationType, -1})) {
            return relocationNames[{relocationType, -1}];
        } else if (relocationNames.count({relocationType, machine})) {
            return relocationNames[{relocationType, machine}];
        } else {
            return "cursed";
        }
    }

    bool checkExecutable() {
        fseek(exe, 0, SEEK_SET);
        int e_magic = getInt16();
        return e_magic == 0x5a4d;
    }

    void readPEHeader() {
        fseek(exe, this->pointerToPETable, SEEK_SET);
        this->signature = getInt32();
        if (this->signature != 0x00004550) {
            throw exceptionPE("Not a PE file.");
        }
        int machine = getInt16();
        this->machineName = getMachineName(machine);
        this->numberOfSections = getInt16();
        this->time = getInt32();
        this->pointerToSymbolTable = getInt32();
        this->numberOfSymbols = getInt32();
        this->sizeOfOptionalHeader = getInt16();
        this->characteristics = getInt16();
    }

    int alignUp(int x, int alignment) {
        if ((x & (alignment - 1)) > 0) {
            return x & ~(alignment - 1);
        } else {
            return x;
        }
    }

    int defineSection(int rva, int sectionAlignment) {
        for (int i = 0; i < this->sections.size(); i++) {
            int start = this->sections[i].virtualAddress;
            int end = start + alignUp(this->sections[i].virtualSize, sectionAlignment);
            if (rva >= start && rva < end) {
                return i;
            }
        }
        return -1;
    }

    int rvaToOffset(int rva, int sectionAlignment) {
        int sectionIndex = defineSection(rva, sectionAlignment);
        if (sectionIndex == -1) {
            return 0;
        }
        return rva - this->sections[sectionIndex].virtualAddress + this->sections[sectionIndex].pointerToRawData;
    }

    void readOptionalHeaderRelocationsInfo() {
        fseek(exe, this->pointerToPETable + 24, SEEK_SET);
        int magicNumber = getInt16();
        if(magicNumber == 0x10b) {
            fseek(exe, 134, SEEK_CUR);
        }
        else if (magicNumber == 0x20b)
        {
            fseek(exe, 150, SEEK_CUR);
        }
        this->baseRelocationTableVirtualAddress = getInt32();
        this->baseRelocationTableSize = getInt32();
        fseek(exe, this->pointerToPETable + 24 + 32, SEEK_SET);
        this->sectionAlignment = getInt32();
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
            section.pointerToRelocations = getInt32();
            fseek(exe, 4, SEEK_CUR);
            section.numberOfRelocations = getInt16();
            fseek(exe, 2, SEEK_CUR);
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
        readOptionalHeaderRelocationsInfo();
        countRelocations();
    }

    void countRelocations() {
        int address = rvaToOffset(this->baseRelocationTableVirtualAddress, this->sectionAlignment);
        fseek(exe, address, SEEK_SET);
        int curSize = 0;
        for (int i = 0; i < this->baseRelocationTableSize; i += curSize) {
            curSize = 0;
            int pageRva = getInt32();
            int blockSize = getInt32();
            curSize += 8;

            this->relocationSections.push_back({});
            this->relocationSections.back().virtualAddress = pageRva;
            for (int j = 0; j < (blockSize - 8) / 2; j++) {
                int relocationSectionInfo = getInt16();
                curSize += 2;
                int type = (relocationSectionInfo & 0xf000) >> 12;
                int offset = relocationSectionInfo & 0x0fff;
                this->relocationSections.back().relocationPageCount[type]++;
            }
        }
    }

public:

    void showHeaderInfo() {
        if(this->Executable)
        {
            cout << "MZ check - TRUE." << endl;
        }
        else
        {
            cout << "MZ check - FALSE." << endl;
            return;
        }
        if(this->signature == 0x00004550)
        {
            cout << "Signature check - TRUE." << endl;
        }
        else
        {
            cout << "Signature check - FALSE." << endl;
            return;
        }
        cout << "Architecture:\t" << machineName.first << endl;

        cout << "Number of sections:\t" << this->numberOfSections << endl;
        cout << "Number of symbols:\t" << this->numberOfSymbols << endl;
        cout << "Time:\t" << ctime(&this->time);
        cout << "Characteristics:\t" << fileCharacteristics(characteristics) << endl << endl;
    }

    void showSectionsInfo() {
        cout << "Idx\t" << "Name\t\t" << "Size\t\t" << "VMA\t\t\t" << "File off\t" << "RawDataSize\t" << "PointerToRelocations\t" << "NumberOfRelocations" << endl;
        for(int i = 0; i < this->numberOfSections; i++) {
            cout << i + 1 << "\t" << sections[i].name << "\t";
            cout << stringToHex(sections[i].virtualSize) << "\t";
            cout << stringToHex(sections[i].virtualAddress) << "\t";
            cout << stringToHex(sections[i].pointerToRawData) << "\t";
            cout << stringToHex(sections[i].sizeOfRawData) << "\t";
            cout << stringToHex(sections[i].pointerToRelocations) << "\t\t\t\t";
            cout << sections[i].numberOfRelocations << endl;
            cout << "Characteristics:\t" << sectionCharacteristics(sections[i].characteristics) << endl;
            cout << endl;
        }
        cout << endl;
    }

    void showRelocationInfo() {
        for (const auto& x : this->relocationSections) {
            cout << "Page Address: " << stringToHex(x.virtualAddress) << "\n";
            for (const auto& y : x.relocationPageCount) {
                cout << "\t" << relocationName(y.first) << ": " << y.second << endl;
            }
        } cout << endl;
    }

    void showSymbolTableinfo() {
        if(this->pointerToSymbolTable == 0)
        {
            cout << "Symbol table is empty." << endl;
            return;
        }
    }
};


#endif //LAB4_PE_H
