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
    /*
     * Parameters for the molecule.
     */
    int const natoms = 90;
    int const attyp[90] = {
        1, 6, 1,  1,  6, 1, 6, 1, 1, 1, 6, 6, 1, 6, 6, 1, 6, 1, 1, 1, 6, 1, 1,
        1, 6, 6,  6,  1, 6, 1, 6, 1, 1, 1, 6, 1, 1, 1, 6, 6, 6, 1, 6, 1, 6, 1,
        6, 1, 15, 46, 6, 8, 6, 8, 6, 8, 6, 1, 6, 1, 1, 6, 1, 1, 6, 1, 1, 6, 1,
        1, 6, 1,  1,  6, 1, 6, 1, 1, 6, 1, 1, 6, 1, 1, 6, 1, 1, 6, 1, 1};

    double const charge = 0.0;
    int const uhf = 0;
    double coord[3 * 90] = {
        -12.38718015, -0.5480217,   0.9259677,   -11.81270223, -2.1920868,
        -0.17574489,  -11.25901134, -3.69253242, 1.12249962,   -13.42464192,
        -2.84404365,  -1.28123694,  -9.62439489, -1.48532778,  -1.93886298,
        -10.2990285,  -0.02834595,  -3.25411506, -8.76645747,  -3.77379081,
        -3.49789023,  -10.31603607, -4.45409361, -4.67330229,  -8.14662603,
        -5.30825157,  -2.26956573,  -7.19420211, -3.23899722,  -4.72054554,
        -7.41907998,  -0.41385087,  -0.46487358, -6.5762604,   2.02768029,
        -0.93163689,  -7.56269946,  3.17096694,  -2.31680898,  -4.51078551,
        3.03490638,   0.34960005,   -3.75111405, 5.75989704,   -0.10960434,
        -1.84248675,  6.047136,     0.65006712,  -3.72654756,  6.45531768,
        -2.92341231,  -2.71554201,  5.03613045,  -4.01378652,  -2.79302094,
        8.27323794,   -3.17663613,  -5.64084405, 6.60460635,   -3.67174539,
        -5.56336512,  7.52490486,   1.31336235,  -5.51990133,  7.12995129,
        3.33348372,   -7.49466918,  7.26790158,  0.64061847,   -5.01345369,
        9.48833433,   1.01478501,   -3.24088695, 1.54201968,   2.12783598,
        -4.13283951,  -0.89384229,  2.69097552,  -6.20398359,  -1.84248675,
        1.37761317,   -6.8975145,   -3.71898864, 1.81225107,   -2.99144259,
        -2.40184683,  4.84715745,   -1.03746177, -1.76689755,  5.13061695,
        -4.46921145,  -1.84626621,  7.28112969,  -3.67174539,  -2.91396366,
        8.85149532,   -6.44775876,  -2.37539061, 7.05625182,   -4.37472495,
        0.16062705,   7.73466489,   -2.93475069, -5.2534494,   4.35960711,
        -2.15807166,  -5.64462351,  2.48877441,  -4.8188115,   -6.07737168,
        4.47110118,   -1.74422079,  -6.17185818, 5.76745596,   -1.13194827,
        2.61160686,   3.66418647,   1.44375372,  2.14106409,   3.21065127,
        3.1936437,    3.09348801,   4.95676179,  5.18730885,   2.69664471,
        4.73188392,   2.45853873,   4.52401362,  7.02223668,   3.8739465,
        5.22888291,   8.32237092,   -0.08125839, 5.03613045,   7.41341079,
        -0.68219253,  6.15863007,   9.01779156,  -1.85004567,  4.05725031,
        5.75422785,   -3.84371082,  4.39740171,  6.07926141,   2.56436361,
        0.32503356,   0.42140979,   0.30991572,  -2.1920868,   -2.71176255,
        2.81947716,   -2.30736033,  -5.49155538, 4.65818445,   -1.42296669,
        -6.18130683,  -0.37983573,  -5.69753595, -1.26422937,  1.16974287,
        -7.19609184,  -1.11305097,  -2.92341231, -0.6803028,   -4.12339086,
        -3.00278097,  0.75211254,   -5.73911001, 4.44842442,   2.74955715,
        -1.39084128,  5.56903431,   1.63839591,  -2.7401085,   2.65318092,
        4.42007847,   -2.94041988,  1.56469644,  5.62950567,   -1.66485213,
        1.322811,     3.23521776,   -3.99299949, 4.13661897,   6.06036411,
        -4.7999142,   2.82325662,   7.25278374,  -5.86194246,  5.12872722,
        4.84526772,   -6.14918142,  6.04146681,  7.71387786,   -3.39017562,
        7.15451778,   8.81181099,   -4.7432223,  5.03235099,   9.04613751,
        -2.16752031,  7.8045849,    6.07737168,  -1.78579485,  9.10282941,
        7.28490915,   -0.72187686,  8.93464344,  4.85849583,   -3.01789881,
        6.29469063,   4.4408655,    0.06803028,  5.25911859,   5.66730027,
        1.37194398,   7.61750163,   3.29568912,  1.16596341,   5.1778602,
        -1.60438077,  1.88973,      6.58192959,  -0.37038708,  2.78735175,
        4.09693464,   -3.36560913,  3.92685894,  2.65696038,   -4.59582336,
        3.09159828,   3.1936437,    -2.24499924, 5.41218672,   6.1794171,
        -4.99455639,  5.10038127,   5.34226671,  -6.26256522,  6.50256093,
        7.54191243,   -3.77757027,  6.07359222,  7.53246378,   -6.53657607,
        3.06514206,   9.04424778,   -7.6534065,  3.92496921,   6.19264521,
        -7.84426923,  2.18263815,   8.63417637,  -4.7810169,   1.05257961,
        9.55447488,   -5.8959576,   -0.42329952, 10.06659171,  -3.55080267,
        1.9086273,    6.55358364,   -3.16340802, -0.13795029,  7.39262376,
        -1.91051703,  -1.5495786,   5.20620615,  -4.39929144,  -1.10738178};

    double energy = 0;
};

int main(int argc, char** argv) {
    Calculator calculator;

    for (int i = 0; i < 1000; ++i) {
        calculator.calculate();
    }

    return 0;
}