#include <iostream>
#include <iomanip>
#include "xtb.h"

void print_energy(double energy) {
  std::cout << "Energy: ";
  std::cout << std::setprecision(14)
            << std::setw(17)
            << energy
            << std::endl;
}

void print_gradient(double* grad, const int size) {
  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  for (int i = 0; i < 3 * size; i += 3) {
    std::cout << std::setprecision(12)
              << std::setw(17) << grad[i]
              << std::setw(17) << grad[i + 1]
              << std::setw(17) << grad[i + 2]
              << std::endl;
  }
}

int main (int argc, char** argv)
{
  /*
   * Parameters for the molecule.
   */
  int const natoms = 31;
  int const attyp[31] = {1, 6, 1, 1, 6, 1, 6, 1, 1, 1, 6, 1, 6, 1, 1, 6,
                         1, 1, 6, 1, 6, 1, 1, 1, 6, 1, 1, 6, 1, 8, 1};
  double const charge = 0.0;
  int const uhf = 0;
  double const coord[3 * 31] = {
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

  int npc = 32;

  // external point charges
  double pc[32] = {0.431000, -0.664000, 0.173000, 0.020000, 0.020000, 0.020000,
                   0.431000, -0.664000, 0.173000, 0.020000, 0.020000, 0.020000,
                   0.431000, -0.664000, 0.173000, 0.020000, 0.020000, 0.020000,
                   0.431000, -0.664000, 0.173000, 0.020000, 0.020000, 0.020000,
                   0.431000, -0.664000, 0.173000, 0.020000, 0.020000, 0.020000,
                   0.431000, -0.664000};

  // coordinates of point charges
  double pccoord[3 * 32] = {
      -1.696669514,  28.11745897,  55.50995136,   -0.967547429, 28.88443423,
      54.00850230,   -0.950868672, 31.58534217,   53.92332839,  0.439341438,
      32.17158366,   52.52085582,  -0.346867500,  32.42710162,  55.70375073,
      -2.886638164,  32.14280874,  53.49308978,   26.383000520, 21.74765157,
      24.17099786,   27.036716710, 22.30632379,   22.54790876,  26.261114830,
      20.54528062,   20.65041197,  27.011658890,  18.66770536,  21.04304684,
      24.203790340,  20.57032899,  20.55244459,   26.920273440, 21.10742805,
      18.78164663,   25.713072340, 18.66022959,   28.70604561,  26.111998120,
      18.26958272,   26.95615185,  27.664033370,  16.09612865,  26.54280365,
      29.614523860,  16.44665278,  27.10468085,   26.659753370, 14.55538454,
      27.47032282,   27.860595530, 15.78003352,   24.51695451,  12.692343200,
      -11.99272547,  35.30000333,  11.005978380,  -11.84086488, 36.01217832,
      9.538990432,   -10.94052003, 33.92895508,   10.179104340, -11.53047861,
      32.06199633,   9.248569167,  -8.901943552,  33.87774529,  7.688508235,
      -11.83241211,  34.08195518,  -11.936904730, 22.39399025,  52.97048306,
      -10.467911780, 21.31627534,  53.20385904,   -8.951231490, 21.02794412,
      50.98626089,   -8.320084347, 22.92510643,   50.49100234,  -10.224293460,
      20.31250935,   49.53331363,  -7.443136243,  19.66216255,  51.30727310,
      15.373924870,  30.20492464,  53.87317117,   15.097532960, 31.53390939,
      52.63558511};

  int numbers[32] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                     7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

  // energy will live here
  double energy = 0.0;

  // gradients will live here
  double grad[3 * 31] = {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  // results will live in here
  double pcgrad[3 * 32] = {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  /*
   * All objects except for the molecular structure can be
   * constructued without other objects present.
   *
   * The construction of the molecular structure locks the
   * number of atoms, atomic number, total charge, multiplicity
   * and boundary conditions.
  **/
  xtb_TEnvironment env = xtb_newEnvironment();
  xtb_TCalculator calc = xtb_newCalculator();
  xtb_TResults res = xtb_newResults();
  xtb_TMolecule mol = xtb_newMolecule(env, &natoms, attyp, coord, &charge, &uhf, NULL, NULL);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  /*
   * Apply changes to the environment which will be respected
   * in all further API calls.
  **/
  xtb_setVerbosity(env, XTB_VERBOSITY_FULL);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  /*
   * Load a parametrisation, the last entry is a char* which can
   * be used to provide a particular parameter file.
   *
   * Otherwise the XTBPATH environment variable is used to find
   * parameter files.
   *
   * The calculator has to be reconstructed if the molecular
   * structure is reconstructed.
  **/
  xtb_loadGFN1xTB(env, mol, calc, NULL);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  xtb_setExternalCharges(env, calc, &npc, numbers, pc, pccoord);
   if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
   }

  /*
   * Actual calculation, will populate the results object,
   * the API can raise errors on failed SCF convergence or other
   * numerical problems.
   *
   * Not supported boundary conditions are usually raised here.
  **/
  xtb_singlepoint(env, mol, calc, res);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  /*
   * Query the environment for properties, an error in the environment
   * is not considered blocking for this calls and allows to query
   * for multiple entries before handling possible errors
  **/
  xtb_getEnergy(env, res, &energy);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  xtb_getPCGradient(env, res, pcgrad);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  xtb_getGradient(env, res, grad);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  print_energy(energy);
  std::cout << "GRADIENTS" << std::endl;
  print_gradient(grad, natoms);
  std::cout << "PC GRADIENTS" << std::endl;
  print_gradient(pcgrad, npc);

  xtb_releaseExternalCharges(env, calc);
  
  /*
   * deconstructor will deallocate the objects and overwrite the
   * pointer with NULL
  **/
  xtb_delResults(&res);
  xtb_delCalculator(&calc);
  xtb_delMolecule(&mol);
  xtb_delEnvironment(&env);

  return 0;
}
