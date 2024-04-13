#include <string>
#include <iostream>
#include <fstream>
#include "include/json.hpp"
#include <vector>
#include <cmath>

using namespace std;

double f_en_tramo(double x0, double y0, double x1, double y1, double x){
    
    double a = (((y1-y0)/(x1-x0))*(x-x0)) + y0;

    return a;
};

double estimar_error_y(sol,x,y){

    int i = 0;
    double error = 0;

    while (i < (sol.size()-1)){

        vector<double> sub_x, sub_y;
        tie(sub_x, sub_y) = subconjunto(x, y, sol[i].first, sol[i+1].first);
        vector<double> prediccion = f_en_tramo(sol[i].first, sol[i].second, sol[i+1].first, sol[i+1].second, sub_x);
        error = error + calcular_error(prediccion, sub_y);
        i = i + 1;
    }

    return error;
    
};

// Para libreria de JSON.
using namespace nlohmann;

int main(int argc, char** argv) {
    std::string instance_name = "../../data/titanium.json";
    std::cout << "Reading file " << instance_name << std::endl;
    std::ifstream input(instance_name);

    json instance;
    input >> instance;
    input.close();

    int K = instance["n"];
    int m = 6;
    int n = 6;
    int N = 5;

    std::cout << K << std::endl;

    // Aca empieza la magia.

    // Ejemplo para guardar json.
    // Probamos guardando el mismo JSON de instance, pero en otro archivo.
    std::ofstream output("test_output.out");

    output << instance;
    output.close();

    return 0;
}
