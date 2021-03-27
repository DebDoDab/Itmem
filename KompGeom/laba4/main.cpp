#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct RGB {
    unsigned char R, G, B;
};

struct Pnm {
    unsigned int version;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    vector<vector<RGB>> colors;
};

enum Color_space {
    RGB_cs,
    HSL,
    HSV,
    YCbCr_601,
    YCbCr_709,
    YCoCg,
    CMY
};

void convert_to_RGB(RGB &rgb, Color_space from_cs) {
    switch (from_cs) {
        case HSL:
        case HSV: {
            double H = (rgb.R / 255.0) * 360.0;
            double S = rgb.G / 255.0;
            double L = rgb.B / 255.0;
            double H_D = H / 60;
            double C, X, m;
            if (from_cs == HSL) {
                C = (1 - abs(2 * L - 1)) * S;
                X = C * (1 - abs(fmod(H_D, 2) - 1));
                m = L - C / 2.0;
            } else {
                C = S * L;
                X = C * (1.0 - abs(fmod(H_D, 2) - 1.0));
                m = L - C;
            }

            m *= 255.0;
            if ((H_D >= 0) && (H_D <= 1)) {
                rgb.R = C * 255.0 + m;
                rgb.G = X * 255.0 + m;
                rgb.B = 0 + m;
            }
            if ((H_D > 1) && (H_D <= 2)) {
                rgb.R = X * 255.0 + m;
                rgb.G = C * 255.0 + m;
                rgb.B = 0 + m;
            }
            if ((H_D > 2) && (H_D <= 3)) {
                rgb.R = 0 + m;
                rgb.G = C * 255.0 + m;
                rgb.B = X * 255.0 + m;
            }
            if ((H_D > 3) && (H_D <= 4)) {
                rgb.R = 0 + m;
                rgb.G = X * 255.0 + m;
                rgb.B = C * 255.0 + m;
            }
            if ((H_D > 4) && (H_D <= 5)) {
                rgb.R = X * 255.0 + m;
                rgb.G = 0 + m;
                rgb.B = C * 255.0 + m;
            }
            if ((H_D > 5) && (H_D <= 6)) {
                rgb.R = C * 255.0 + m;
                rgb.G = 0 + m;
                rgb.B = X * 255.0 + m;
            }
            break;
        }
        case YCbCr_601:
        case YCbCr_709: {
            double Kr, Kg, Kb;
            if (from_cs == YCbCr_601) {
                Kr = 0.299;
                Kg = 0.587;
                Kb = 0.114;
            } else {
                Kr = 0.0722;
                Kg = 0.2126;
                Kb = 0.7152;
            }
            double Y, Cb, Cr, R, G, B;
            Y = rgb.R / 255.0;
            Cb = (rgb.G / 255.0) - 0.5;
            Cr = (rgb.B / 255.0) - 0.5;
            R = (Y + Cr * (2.0 - 2.0 * Kr));
            G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
            B = (Y + (2.0 - 2.0 * Kb) * Cb);
            R = max(min(R, 1.), 0.);
            G = max(min(G, 1.), 0.);
            B = max(min(B, 1.), 0.);
            rgb.R = R * 255.0;
            rgb.G = G * 255.0;
            rgb.B = B * 255.0;
            break;
        }
        case YCoCg: {
            double Y = rgb.R / 255.0;
            double Co = (rgb.G / 255.0) - 0.5;
            double Cg = (rgb.B / 255.0) - 0.5;
            double R = Y + Co - Cg;
            double G = Y + Cg;
            double B = Y - Co - Cg;
            R = max(min(R, 1.), 0.);
            G = max(min(G, 1.), 0.);
            B = max(min(B, 1.), 0.);
            rgb.R = R * 255.0;
            rgb.G = G * 255.0;
            rgb.B = B * 255.0;
            break;
        }
        case CMY: {
            double R = rgb.R / 255.0;
            double G = rgb.G / 255.0;
            double B = rgb.B / 255.0;
            double C = 1 - R;
            double M = 1 - G;
            double Y = 1 - B;
            rgb.R = C * 255.0;
            rgb.G = M * 255.0;
            rgb.B = Y * 255.0;
            break;
        }
    }
}

void convert_to_any(RGB& rgb, Color_space to_cs){
    double R = rgb.R / 255.0;
    double G = rgb.G / 255.0;
    double B = rgb.B / 255.0;
    switch (to_cs){
        case HSL:{
            double H, S, L;
            double MAX = max(R, max(G, B));
            double MIN = min(R, min(G, B));
            if (MAX == R && G >= B){
                H = 60 * (G - B)/(MAX - MIN);
            } else if (MAX == R && G < B){
                H = 60 * (G - B)/(MAX - MIN) + 360;
            } else if (MAX == G){
                H = 60 * (B - R)/(MAX - MIN) + 120;
            } else if (MAX == B){
                H = 60 * (R - G)/(MAX - MIN) + 240;
            } else if (MAX == MIN){
                H = 0;
            }
            S = (MAX - MIN)/(1 - abs(1- (MAX + MIN)));
            L = 0.5 * (MAX + MIN);
            rgb.R = (H / 360) * 255;
            rgb.G = S * 255;
            rgb.B = L * 255;
            break;
        }
        case HSV:{
            double H, S, V;
            double MAX = max(R, max(G, B));
            double MIN = min(R, min(G, B));
            if (MAX == R && G >= B){
                H = 60 * (G - B)/(MAX - MIN);
            } else if (MAX == R && G < B){
                H = 60 * (G - B)/(MAX - MIN) + 360;
            } else if (MAX == G){
                H = 60 * (B - R)/(MAX - MIN) + 120;
            } else if (MAX == B){
                H = 60 * (R - G)/(MAX - MIN) + 240;
            } else if (MAX == MIN){
                H = 0;
            }
            if (MAX == 0){
                S = 0;
            } else {
                S = 1 - MIN / MAX;
            }
            V = MAX;
            rgb.R = (H / 360) * 255;
            rgb.G = S * 255;
            rgb.B = V * 255;
            break;
        }
        case YCbCr_601:
        case YCbCr_709:{
            double Kr, Kg, Kb;
            if (to_cs == YCbCr_601) {
                Kr = 0.299;
                Kg = 0.587;
                Kb = 0.114;
            } else {
                Kr = 0.0722;
                Kg = 0.2126;
                Kb = 0.7152;
            }
            double Y = Kr * R + Kg * G + Kb * B;
            double Cb = 0.5 * ((B - Y) / (1.0 - Kb));
            double Cr = 0.5 * ((R - Y) / (1.0 - Kr));
            rgb.R = Y * 255.0;
            rgb.G = (Cb + 0.5)*255.0;
            rgb.B = (Cr + 0.5)*255.0;
            break;
        }
        case YCoCg:{
            double Y = R / 4 + G / 2 + B / 4;
            double Co = R / 2 - B / 2;
            double Cg = -R / 4 + G / 2 - B / 4;
            rgb.R = Y * 255.0;
            rgb.G = (Co + 0.5) * 255.0;
            rgb.B = (Cg + 0.5) * 255.0;
            break;
        }
        case CMY:{
            double C = 1 - R;
            double M = 1 - G;
            double Y = 1 - B;
            rgb.R = C * 255.0;
            rgb.G = M  * 255.0;
            rgb.B = Y * 255.0;
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    //parse input
    char *from_color_space;
    char *to_color_space;
    char *input_file_name;
    char *output_file_name;
    int input_count, output_count;
    Color_space from_cs, to_cs;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-f") {
            i++;
            from_color_space = argv[i];
            string from_color_space_str = from_color_space;
            if (from_color_space_str == "RGB") {
                from_cs = RGB_cs;
            } else if (from_color_space_str == "HSL") {
                from_cs = HSL;
            } else if (from_color_space_str == "HSV") {
                from_cs = HSV;
            } else if (from_color_space_str == "YCbCr.601") {
                from_cs = YCbCr_601;
            } else if (from_color_space_str == "YCbCr.709") {
                from_cs = YCbCr_709;
            } else if (from_color_space_str == "YCoCg") {
                from_cs = YCoCg;
            } else if (from_color_space_str == "CMY") {
                from_cs = CMY;
            } else {
                cerr << "Wrong arguments!";
                return 1;
            }
        } else if (arg == "-t") {
            i++;
            to_color_space = argv[i];
            string to_color_space_str = to_color_space;
            if (to_color_space_str == "RGB") {
                to_cs = RGB_cs;
            } else if (to_color_space_str == "HSL") {
                to_cs = HSL;
            } else if (to_color_space_str == "HSV") {
                to_cs = HSV;
            } else if (to_color_space_str == "YCbCr.601") {
                to_cs = YCbCr_601;
            } else if (to_color_space_str == "YCbCr.709") {
                to_cs = YCbCr_709;
            } else if (to_color_space_str == "YCoCg") {
                to_cs = YCoCg;
            } else if (to_color_space_str == "CMY") {
                to_cs = CMY;
            } else {
                cerr << "Wrong arguments!";
                return 1;
            }
        } else if (arg == "-i") {
            i++;
            input_count = atoi(argv[i]);
            i++;
            input_file_name = argv[i];
        } else if (arg == "-o") {
            i++;
            output_count = atoi(argv[i]);
            i++;
            output_file_name = argv[i];
        } else {
            cerr << "wrong arguments";
        }
    }

    Pnm pic;
    //read file
    if (input_count == 1) {
        FILE *input_file = fopen(input_file_name, "rb");
        if (input_file == NULL) {
            cerr << "File open error";
            return 1;
        }
        char trash;
        int rez = fscanf(input_file, "P%u\n%u %u\n%u%c", &pic.version, &pic.width, &pic.height, &pic.depth, &trash);
        if (rez != 5) {
            cerr << "Read error";
            return 1;
        }

        for (int i = 0; i < pic.height; ++i) {
            pic.colors.push_back(vector<RGB>());
            for (int j = 0; j < pic.width; ++j) {
                RGB rgb;
                rez = fscanf(input_file, "%c%c%c", &rgb.R, &rgb.G, &rgb.B);
                if (rez != 3) {
                    cerr << "Read error";
                    return 1;
                }
                pic.colors[i].push_back(rgb);
            }
        }
        fclose(input_file);
    } else {
        string input_file_name_str = input_file_name;
        input_file_name_str[input_file_name_str.size() - 2] = 'g';
        char *input_file_name1 = (char *) malloc(input_file_name_str.size() + 1);
        char *input_file_name2 = (char *) malloc(input_file_name_str.size() + 1);
        char *input_file_name3 = (char *) malloc(input_file_name_str.size() + 1);
        int k = 0;
        for (int i = 0; i < input_file_name_str.size() + 1; ++i) {
            if (input_file_name_str[i] == '.' && i > 1) {
                input_file_name1[k] = '1';
                input_file_name2[k] = '2';
                input_file_name3[k] = '3';
                k++;
            }
            input_file_name1[k] = input_file_name_str[i];
            input_file_name2[k] = input_file_name_str[i];
            input_file_name3[k] = input_file_name_str[i];
            k++;
        }
        FILE *input_file1 = fopen(input_file_name1, "rb");
        if (input_file1 == NULL) {
            cerr << "File open error";
            return 1;
        }
        FILE *input_file2 = fopen(input_file_name2, "rb");
        if (input_file2 == NULL) {
            cerr << "File open error";
            return 1;
        }
        FILE *input_file3 = fopen(input_file_name3, "rb");
        if (input_file3 == NULL) {
            cerr << "File open error";
            return 1;
        }
        char trash;
        int rez = fscanf(input_file1, "P%u\n%d %d\n%d%c", &pic.version, &pic.width, &pic.height, &pic.depth, &trash);
        if (rez != 5) {
            cerr << "Read error";
            return 1;
        }
        rez = fscanf(input_file2, "P%u\n%d %d\n%d%c", &pic.version, &pic.width, &pic.height, &pic.depth, &trash);
        if (rez != 5) {
            cerr << "Read error";
            return 1;
        }
        rez = fscanf(input_file3, "P%u\n%d %d\n%d%c", &pic.version, &pic.width, &pic.height, &pic.depth, &trash);
        if (rez != 5) {
            cerr << "Read error";
            return 1;
        }

        for (int i = 0; i < pic.height; ++i) {
            pic.colors.push_back(vector<RGB>());
            for (int j = 0; j < pic.width; ++j) {
                RGB rgb;
                int rez1 = fscanf(input_file1, "%c", &rgb.R);
                int rez2 = fscanf(input_file2, "%c", &rgb.G);
                int rez3 = fscanf(input_file3, "%c", &rgb.B);
                if (rez1 + rez2 + rez3 != 3) {
                    cerr << "Read error";
                    return 1;
                }
                pic.colors[i].push_back(rgb);
            }
        }
        fclose(input_file1);
        fclose(input_file2);
        fclose(input_file3);
    }

    //conversion to RGB
    if (from_cs != RGB_cs) {
        for (int i = 0; i < pic.height; ++i) {
            for (int j = 0; j < pic.width; ++j) {
                convert_to_RGB(pic.colors[i][j], from_cs);
            }
        }
    }

    //convert from RGB to to_color_space
    if (to_cs != RGB_cs) {
        for (int i = 0; i < pic.height; ++i) {
            for (int j = 0; j < pic.width; ++j) {
                convert_to_any(pic.colors[i][j], to_cs);
            }
        }
    }

    //write file
    if (output_count == 1) {
        pic.version = 6;
        FILE *new_file = fopen(output_file_name, "wb");
        if (new_file == NULL) {
            cerr << "File open error";
            return 1;
        }
        int rez = fprintf(new_file, "P%d\n%d %d\n%d\n", pic.version, pic.width, pic.height, pic.depth);
        if (rez != 9 + to_string(pic.width).size() + to_string(pic.height).size()) {
            cerr << "Write file error at header";
            return 1;
        }
        for (int i = 0; i < pic.height; ++i) {
            for (int j = 0; j < pic.width; ++j) {
                rez = fprintf(new_file, "%c%c%c", pic.colors[i][j].R, pic.colors[i][j].G, pic.colors[i][j].B);
                if (rez != 3) {
                    cerr << "Write file error at bytes";
                    return 1;
                }
            }
        }
        fclose(new_file);
    } else {
        pic.version = 5;
        string output_file_name_str = output_file_name;
        output_file_name_str[output_file_name_str.size() - 2] = 'g';
        char *output_file_name1 = (char *) malloc(output_file_name_str.size() + 1);
        char *output_file_name2 = (char *) malloc(output_file_name_str.size() + 1);
        char *output_file_name3 = (char *) malloc(output_file_name_str.size() + 1);
        int k = 0;
        for (int i = 0; i < output_file_name_str.size() + 1; ++i, ++k) {
            if (output_file_name_str[i] == '.' && i > 1) {
                output_file_name1[k] = '1';
                output_file_name2[k] = '2';
                output_file_name3[k] = '3';
                k++;
            }
            output_file_name1[k] = output_file_name_str[i];
            output_file_name2[k] = output_file_name_str[i];
            output_file_name3[k] = output_file_name_str[i];
        }
        FILE *new_file1 = fopen(output_file_name1, "wb");
        if (new_file1 == NULL) {
            cerr << "File open error";
            return 1;
        }
        FILE *new_file2 = fopen(output_file_name2, "wb");
        if (new_file2 == NULL) {
            cerr << "File open error";
            return 1;
        }
        FILE *new_file3 = fopen(output_file_name3, "wb");
        if (new_file3 == NULL) {
            cerr << "File open error";
            return 1;
        }
        int rez = fprintf(new_file1, "P%d\n%d %d\n%d\n", pic.version, pic.width, pic.height, pic.depth);
        if (rez != 9 + to_string(pic.width).size() + to_string(pic.height).size()) {
            cerr << "Write file error at header";
            return 1;
        }
        rez = fprintf(new_file2, "P%d\n%d %d\n%d\n", pic.version, pic.width, pic.height, pic.depth);
        if (rez != 9 + to_string(pic.width).size() + to_string(pic.height).size()) {
            cerr << "Write file error at header";
            return 1;
        }
        rez = fprintf(new_file3, "P%d\n%d %d\n%d\n", pic.version, pic.width, pic.height, pic.depth);
        if (rez != 9 + to_string(pic.width).size() + to_string(pic.height).size()) {
            cerr << "Write file error at header";
            return 1;
        }
        for (int i = 0; i < pic.height; ++i) {
            for (int j = 0; j < pic.width; ++j) {
                int rez = fprintf(new_file1, "%c", pic.colors[i][j].R);
                if (rez != 1) {
                    cerr << "Write file error at bytes";
                    return 1;
                }
                rez = fprintf(new_file2, "%c", pic.colors[i][j].G);
                if (rez != 1) {
                    cerr << "Write file error at bytes";
                    return 1;
                }
                rez = fprintf(new_file3, "%c", pic.colors[i][j].B);
                if (rez != 1) {
                    cerr << "Write file error at bytes";
                    return 1;
                }
            }
        }
        fclose(new_file1);
        fclose(new_file2);
        fclose(new_file3);
    }
    return 0;
}