#include "xtb.h"
#include <iomanip>
#include <iostream>

class Calculator {
public:
    Calculator() {
        env = xtb_newEnvironment();
        calc = xtb_newCalculator();

        // initialize results and molecule
        res = xtb_newResults();
        mol = xtb_newMolecule(env, &natoms, attyp, coord, &charge, &uhf, NULL,
                              NULL);

        xtb_setVerbosity(env, XTB_VERBOSITY_MUTED);
        xtb_loadGFN1xTB(env, mol, calc, NULL);
    }

    ~Calculator() {
        // delete ressources
        xtb_delEnvironment(&env);
        xtb_delCalculator(&calc);
        xtb_delResults(&res);
        xtb_delMolecule(&mol);
    }

    int calculate() {
        xtb_singlepoint(env, mol, calc, res);
        if (xtb_checkEnvironment(env)) {
            xtb_showEnvironment(env, NULL);
            return 1;
        }
        xtb_getEnergy(env, res, &energy);
        if (xtb_checkEnvironment(env)) {
            xtb_showEnvironment(env, NULL);
            return 1;
        }

        // update coordinates here

        return 0;
    }

private:
    xtb_TEnvironment env;
    xtb_TCalculator calc;
    xtb_TResults res;
    xtb_TMolecule mol;

    /*
     * Parameters for the molecule.
     */
    int const natoms = 31;
    int const attyp[31] = {1, 6, 1, 1, 6, 1, 6, 1, 1, 1, 6, 1, 6, 1, 1, 6,
                           1, 1, 6, 1, 6, 1, 1, 1, 6, 1, 1, 6, 1, 8, 1};
    double const charge = 0.0;
    int const uhf = 0;
    double coord[3 * 31] = {
        -0.442947496, 11.001947210, 23.53843018,  -2.236268461, 11.818985980,
        22.93889444,  -1.841717705, 13.792091510, 22.49830981,  -2.896722482,
        10.768954200, 21.29444454,  -4.133665133, 11.695821690, 25.11713090,
        -4.513283393, 9.713842463,  25.52960654,  -6.643232696, 12.675979330,
        24.06753249,  -6.497152995, 14.672778630, 23.58352390,  -8.148942688,
        12.705927690, 25.47277389,  -7.353363183, 11.592564650, 22.46591770,
        -3.249632431, 12.876986410, 27.66935330,  -4.846956553, 12.734322190,
        28.99201199,  -2.467110848, 15.660343880, 27.33890614,  -4.009123687,
        16.787220770, 26.56744596,  -0.818133300, 15.913359350, 26.13075930,
        -1.719833938, 16.708905520, 29.92782456,  -1.175383185, 18.674510890,
        29.63963875,  -3.270175176, 16.843998070, 31.30603239,  0.393734165,
        15.240980550, 31.24575662,  2.098110773,  15.276181590, 30.05626854,
        1.103721260,  16.300985820, 33.84032285,  -0.510552700, 16.227748650,
        35.11752635,  1.786206150,  18.232492740, 33.62584759,  2.541275947,
        15.177545230, 34.79620160,  -0.431661103, 12.490133300, 31.57724434,
        1.201728308,  11.377478740, 32.22095010,  -1.982252711, 12.263731930,
        32.94292201,  -1.094745099, 11.448025710, 28.96323675,  0.563579412,
        11.458509150, 27.70991388,  -1.947354387, 8.933606299,  29.46637609,
        -0.489290309, 7.918137207,  29.92393411};

    double energy = 0;
};

int main(int argc, char** argv) {
    Calculator calculator;

    for (int i = 0; i < 1000; ++i) {
        calculator.calculate();
    }

    return 0;
}