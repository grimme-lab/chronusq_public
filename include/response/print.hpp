/* 
 *  This file is part of the Chronus Quantum (ChronusQ) software package
 *  
 *  Copyright (C) 2014-2022 Li Research Group (University of Washington)
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *  
 *  Contact the Developers:
 *    E-Mail: xsli@uw.edu
 *  
 */
#pragma once

#include <response/tbase.hpp>

#include <physcon.hpp>

namespace ChronusQ {

  template <typename T>
  void ResponseTBase<T>::printTMoments(std::ostream &out) {


    out << "\n\n\n* RESIDUE TRANSITION MOMENTS\n\n\n";

    size_t nRoots = resSettings.nRoots;
 
    double xSmall = 1e-6;



    auto printRec = [&](T x) {
      out << std::setprecision(5) << std::scientific << std::setw(15)
          << std::right << ((std::abs(x) > xSmall) ? x : 0. );
    };

    auto printDipole = [&]( T* dipole ) {

      out << "                                { X, Y, Z }\n\n";

      for( auto iSt = 0; iSt < nRoots; iSt++ ) {

        out << "    " << "n = " << std::setw(5) << std::left << iSt + 1;
        printRec(dipole[3*iSt + 0]);
        printRec(dipole[3*iSt + 1]);
        printRec(dipole[3*iSt + 2]);

        out << "\n";

      }

    };


    auto printQuadrupole = [&]( T* quadrupole ) {

      out << "                              { XX, XY, XZ }\n";
      out << "                              { YY, YZ, ZZ }\n\n";

      for( auto iSt = 0; iSt < nRoots; iSt++ ) {

        out << "    " << "n = " << std::setw(5) << std::left << iSt + 1;

        printRec(quadrupole[6*iSt + 0]);
        printRec(quadrupole[6*iSt + 1]);
        printRec(quadrupole[6*iSt + 2]);

        out << "\n" << "    " << "    " << std::setw(5) << " ";

        printRec(quadrupole[6*iSt + 3]);
        printRec(quadrupole[6*iSt + 4]);
        printRec(quadrupole[6*iSt + 5]);

        out << "\n\n";

      }

    };

    auto printOctupole = [&]( T* octupole ) {

      out << "                             { XXX, XXY, XXZ }\n";
      out << "                             { XYY, XYZ, XZZ }\n";
      out << "                             { YYY, YYZ, YZZ }\n";
      out << "                             { ZZZ           }\n\n";

      for( auto iSt = 0; iSt < nRoots; iSt++ ) {

        out << "    " << "n = " << std::setw(5) << std::left << iSt + 1;

        printRec(octupole[10*iSt + 0]);
        printRec(octupole[10*iSt + 1]);
        printRec(octupole[10*iSt + 2]);

        out << "\n" << "    " << "    " << std::setw(5) << " ";

        printRec(octupole[10*iSt + 3]);
        printRec(octupole[10*iSt + 4]);
        printRec(octupole[10*iSt + 5]);

        out << "\n" << "    " << "    " << std::setw(5) << " ";

        printRec(octupole[10*iSt + 6]);
        printRec(octupole[10*iSt + 7]);
        printRec(octupole[10*iSt + 8]);

        out << "\n" << "    " << "    " << std::setw(5) << " ";

        printRec(octupole[10*iSt + 9]);

        out << "\n\n";

      }

    };





    if( resResults.tLenElecDipole_ge ) {

      out << "  Transition Dipole Moments (Length) : < 0 | r | n > (AU)\n\n\n";

      printDipole(resResults.tLenElecDipole_ge);

      out << "\n\n\n\n";

    }


    if( resResults.tVelElecDipole_ge ) {

      out << "  Transition Dipole Moments (Velocity) : i < 0 | p | n > (AU)\n\n\n";

      printDipole(resResults.tVelElecDipole_ge);

      out << "\n\n\n\n";

    }

    if( resResults.tLenElecQuadrupole_ge ) {

      out << "  Transition Quadrupole Moments (Length) : < 0 | r_i r_j | n > (AU)\n\n\n";

      printQuadrupole(resResults.tLenElecQuadrupole_ge);

      out << "\n\n\n\n";

    }


    if( resResults.tVelElecQuadrupole_ge ) {

      out << "  Transition Quadrupole Moments (Velocity) : i < 0 | p_i r_j + r_i p_j | n > (AU)\n\n\n";

      printQuadrupole(resResults.tVelElecQuadrupole_ge);

      out << "\n\n\n\n";

    }


    if( resResults.tLenElecOctupole_ge ) {

      out << "  Transition Octupole Moments (Length) : < 0 | r_i r_j r_k | n > (AU)\n\n\n";


      printOctupole(resResults.tLenElecOctupole_ge);

      out << "\n\n\n\n";

    }



    if( resResults.tVelElecOctupole_ge ) {

      out << "  Transition Octupole Moments (Velocity) : i < 0 | p_i r_j r_k + r_i p_j r_k + r_i r_j p_k | n > (AU)\n\n\n";

      printOctupole(resResults.tVelElecOctupole_ge);

      out << "\n\n\n\n";

    }


    if( resResults.tMagDipole_ge ) {
      out << "  Transition Magnetic Moments (Length) : \n";
      out << "    i < 0 | r x p | n > (AU)\n\n\n";

      printDipole(resResults.tMagDipole_ge);

      out << "\n\n\n\n";
    }


  }


  template <typename T>
  void ResponseTBase<T>::printResObservables(std::ostream &out) {

    size_t nRoots = resSettings.nRoots;
 
    double xSmall = 1e-6;



    auto printRec = [&](T x) {
      out << std::setprecision(8) << std::scientific << std::setw(15)
          << std::right << ((std::abs(x) > xSmall) ? x : 0. );
    };


    if( resObs.rotatory_len_RM ) {

      out << "\n\n\nROTATORY STRENGTH (LENGTH) \n\n";
      out << "  * R(n) = 0.5 * Im[ < 0 | r_k | n > < n | (r x p)_k | 0 > ]\n";

      out << "\n\n\n";

      out << "   " << "    " << std::setw(5) << " " << "R(n) (10^40 erg-esu-cm / Gauss)\n\n";
      for(auto iO = 0; iO < nRoots; iO++) {

        out << "   " << "n = " << std::setw(5) << std::left << iO + 1;
        printRec(Rotatory_CGS_Length * resObs.rotatory_len_RM[iO]);
        out << "\n";

      };
      out << "\n";

    }

  };


  template <typename T>
  template <typename U>
  void ResponseTBase<T>::printRF(
    FDResponseResults<T,U> &results, std::ostream &out) {

    out << "\n\n\n* RESPONSE FUNCTIONS (POLARIZABILITIES)\n\n\n";

    size_t nOmega = fdrSettings.bFreq.size();


    // Printing Lambdas

    double xSmall = 1e-6;

    auto printRecRe = [&](U x) {
      out << std::setprecision(5) << std::scientific << std::setw(15)
          << std::right << ((std::abs(x) > xSmall) ? std::real(x) : 0. );
    };

    auto printRecIm = [&](U x) {
      out << std::setprecision(5) << std::scientific << std::setw(15)
          << std::right << ((std::abs(x) > xSmall) ? std::imag(x) : 0. );
    };



    // Helper strings
    std::string ededHelper = 
     "                         { << X; X >>, << X; Y >>, << X; Z >> }\n"
     "                         { << Y; X >>, << Y; Y >>, << Y; Z >> }\n"
     "                         { << Z; X >>, << Z; Y >>, << Z; Z >> }\n";

    std::string eqedHelper =
     "                        { << XX; X >>, << XX; Y >>, << XX; Z >> }\n"
     "                        { << XY; X >>, << XY; Y >>, << XY; Z >> }\n"
     "                        { << XZ; X >>, << XZ; Y >>, << XZ; Z >> }\n"
     "                        { << YY; X >>, << YY; Y >>, << YY; Z >> }\n"
     "                        { << YZ; X >>, << YZ; Y >>, << YZ; Z >> }\n"
     "                        { << ZZ; X >>, << ZZ; Y >>, << ZZ; Z >> }\n";


std::string eqeqHelper =
 "                        { << XX; XX >>, << XX; XY >>, << XX; XZ >>, << XX; YY >>, << XX; YZ >>, << XX; ZZ >> }\n"
 "                        { << XY; XX >>, << XY; XY >>, << XY; XZ >>, << XY; YY >>, << XY; YZ >>, << XY; ZZ >> }\n"
 "                        { << XZ; XX >>, << XZ; XY >>, << XZ; XZ >>, << XZ; YY >>, << XZ; YZ >>, << XZ; ZZ >> }\n"
 "                        { << YY; XX >>, << YY; XY >>, << YY; XZ >>, << YY; YY >>, << YY; YZ >>, << YY; ZZ >> }\n"
 "                        { << YZ; XX >>, << YZ; XY >>, << YZ; XZ >>, << YZ; YY >>, << YZ; YZ >>, << YZ; ZZ >> }\n"
 "                        { << ZZ; XX >>, << ZZ; XY >>, << ZZ; XZ >>, << ZZ; YY >>, << ZZ; YZ >>, << ZZ; ZZ >> }\n";

// 10-component octupole ordering used elsewhere in your code:
// { XXX, XXY, XXZ, XYY, XYZ, XZZ, YYY, YYZ, YZZ, ZZZ }
std::string eodeHelper =
 "                        { << XXX; X >>, << XXX; Y >>, << XXX; Z >> }\n"
 "                        { << XXY; X >>, << XXY; Y >>, << XXY; Z >> }\n"
 "                        { << XXZ; X >>, << XXZ; Y >>, << XXZ; Z >> }\n"
 "                        { << XYY; X >>, << XYY; Y >>, << XYY; Z >> }\n"
 "                        { << XYZ; X >>, << XYZ; Y >>, << XYZ; Z >> }\n"
 "                        { << XZZ; X >>, << XZZ; Y >>, << XZZ; Z >> }\n"
 "                        { << YYY; X >>, << YYY; Y >>, << YYY; Z >> }\n"
 "                        { << YYZ; X >>, << YYZ; Y >>, << YYZ; Z >> }\n"
 "                        { << YZZ; X >>, << YZZ; Y >>, << YZZ; Z >> }\n"
 "                        { << ZZZ; X >>, << ZZZ; Y >>, << ZZZ; Z >> }\n";

std::string eoeqHelper =
 "                        { << XXX; XX >>, << XXX; XY >>, << XXX; XZ >>, << XXX; YY >>, << XXX; YZ >>, << XXX; ZZ >> }\n"
 "                        { << XXY; XX >>, << XXY; XY >>, << XXY; XZ >>, << XXY; YY >>, << XXY; YZ >>, << XXY; ZZ >> }\n"
 "                        { << XXZ; XX >>, << XXZ; XY >>, << XXZ; XZ >>, << XXZ; YY >>, << XXZ; YZ >>, << XXZ; ZZ >> }\n"
 "                        { << XYY; XX >>, << XYY; XY >>, << XYY; XZ >>, << XYY; YY >>, << XYY; YZ >>, << XYY; ZZ >> }\n"
 "                        { << XYZ; XX >>, << XYZ; XY >>, << XYZ; XZ >>, << XYZ; YY >>, << XYZ; YZ >>, << XYZ; ZZ >> }\n"
 "                        { << XZZ; XX >>, << XZZ; XY >>, << XZZ; XZ >>, << XZZ; YY >>, << XZZ; YZ >>, << XZZ; ZZ >> }\n"
 "                        { << YYY; XX >>, << YYY; XY >>, << YYY; XZ >>, << YYY; YY >>, << YYY; YZ >>, << YYY; ZZ >> }\n"
 "                        { << YYZ; XX >>, << YYZ; XY >>, << YYZ; XZ >>, << YYZ; YY >>, << YYZ; YZ >>, << YYZ; ZZ >> }\n"
 "                        { << YZZ; XX >>, << YZZ; XY >>, << YZZ; XZ >>, << YZZ; YY >>, << YZZ; YZ >>, << YZZ; ZZ >> }\n"
 "                        { << ZZZ; XX >>, << ZZZ; XY >>, << ZZZ; XZ >>, << ZZZ; YY >>, << ZZZ; YZ >>, << ZZZ; ZZ >> }\n";

std::string eoeoHelper =
 "                        { XXX, XXY, XXZ, XYY, XYZ, XZZ, YYY, YYZ, YZZ, ZZZ }  (rows & cols)\n";


    // Print out a D-D Polarizability
    auto printDD = [&]( std::function<void(U)> printRec, U *dd_polar ) -> void {

      out << ededHelper << std::endl;
      for(auto iOmega = 0; iOmega < nOmega; iOmega++) {

        double omega = fdrSettings.bFreq[iOmega];
        U*     dd  = dd_polar + iOmega*9;

        out << "    " << "W(AU) = " << std::setw(8) << std::setprecision(4)
            << std::fixed << std::left << omega;

        printRec(dd[0]); printRec(dd[3]); printRec(dd[6]);

        out << "\n" << "    " << "        " << std::setw(8) << " ";
        printRec(dd[1]); printRec(dd[4]); printRec(dd[7]);

        out << "\n" << "    " << "        " << std::setw(8) << " ";
        printRec(dd[2]); printRec(dd[5]); printRec(dd[8]);

        out << "\n\n";

      }
      out << "\n\n\n\n";
    };



    // Print out a Q-D Polarizability
    auto printQD = [&]( std::function<void(U)> printRec, U* qd_polar ) -> void {
      out << eqedHelper << std::endl;
      for(auto iOmega = 0; iOmega < nOmega; iOmega++) {

        double omega = fdrSettings.bFreq[iOmega];
        U*     qd  = qd_polar + iOmega*3*6;

        out << "    " << "W(AU) = " << std::setw(8) << std::setprecision(4)
            << std::fixed << std::left << omega;

        printRec(qd[0]); printRec(qd[6]); printRec(qd[12]);

        out << "\n" << "    " << "        " << std::setw(8) << " ";
        printRec(qd[1]); printRec(qd[7]); printRec(qd[13]);

        out << "\n" << "    " << "        " << std::setw(8) << " ";
        printRec(qd[2]); printRec(qd[8]); printRec(qd[14]);

        out << "\n" << "    " << "        " << std::setw(8) << " ";
        printRec(qd[3]); printRec(qd[9]); printRec(qd[15]);

        out << "\n" << "    " << "        " << std::setw(8) << " ";
        printRec(qd[4]); printRec(qd[10]); printRec(qd[16]);

        out << "\n" << "    " << "        " << std::setw(8) << " ";
        printRec(qd[5]); printRec(qd[11]); printRec(qd[17]);

        out << "\n\n";

      }
      out << "\n\n\n\n";
    };


// Add a 6x6 printer (layout matches your EQ–ED stride pattern: row + 6*col)
auto printQQ = [&]( std::function<void(U)> printRec, U* qq_polar ) -> void {
  out << eqeqHelper << std::endl;
  for (auto iOmega = 0; iOmega < nOmega; iOmega++) {

    double omega = fdrSettings.bFreq[iOmega];
    U* qq = qq_polar + iOmega * 36; // 6 * 6 per frequency

    out << "    " << "W(AU) = " << std::setw(8) << std::setprecision(4)
        << std::fixed << std::left << omega;

    // row 0: XX vs {XX,XY,XZ,YY,YZ,ZZ}
    printRec(qq[0  + 6*0]); printRec(qq[0  + 6*1]); printRec(qq[0  + 6*2]);
    printRec(qq[0  + 6*3]); printRec(qq[0  + 6*4]); printRec(qq[0  + 6*5]);

    // rows 1..5
    auto row = [&](int r){
      out << "\n" << "    " << "        " << std::setw(8) << " ";
      printRec(qq[r + 6*0]); printRec(qq[r + 6*1]); printRec(qq[r + 6*2]);
      printRec(qq[r + 6*3]); printRec(qq[r + 6*4]); printRec(qq[r + 6*5]);
    };
    row(1); row(2); row(3); row(4); row(5);

    out << "\n\n";
  }
  out << "\n\n\n\n";
};

// 10 x 3 (EO–ED)
auto printOE = [&](std::function<void(U)> printRec, U* oe_polar) -> void {
  out << eodeHelper << std::endl;
  for (auto iOmega = 0; iOmega < nOmega; iOmega++) {
    double omega = fdrSettings.bFreq[iOmega];
    U* oe = oe_polar + iOmega * 10 * 3; // 30 per frequency
    out << "    " << "W(AU) = " << std::setw(8) << std::setprecision(4)
        << std::fixed << std::left << omega;
    auto row = [&](int r){
      if (r > 0) out << "\n" << "    " << "        " << std::setw(8) << " ";
      // columns: X(0), Y(1), Z(2)
      printRec(oe[r + 10*0]); printRec(oe[r + 10*1]); printRec(oe[r + 10*2]);
    };
    for (int r = 0; r < 10; ++r) row(r);
    out << "\n\n";
  }
  out << "\n\n\n\n";
};

// 10 x 6 (EO–EQ)
auto printOQ = [&](std::function<void(U)> printRec, U* oq_polar) -> void {
  out << eoeqHelper << std::endl;
  for (auto iOmega = 0; iOmega < nOmega; iOmega++) {
    double omega = fdrSettings.bFreq[iOmega];
    U* oq = oq_polar + iOmega * 10 * 6; // 60 per frequency
    out << "    " << "W(AU) = " << std::setw(8) << std::setprecision(4)
        << std::fixed << std::left << omega;
    auto row = [&](int r){
      if (r > 0) out << "\n" << "    " << "        " << std::setw(8) << " ";
      // columns: {XX, XY, XZ, YY, YZ, ZZ} -> col 0..5
      for (int c = 0; c < 6; ++c) printRec(oq[r + 10*c]);
    };
    for (int r = 0; r < 10; ++r) row(r);
    out << "\n\n";
  }
  out << "\n\n\n\n";
};

// 10 x 10 (EO–EO)
auto printOO = [&](std::function<void(U)> printRec, U* oo_polar) -> void {
  out << eoeoHelper << std::endl;
  for (auto iOmega = 0; iOmega < nOmega; iOmega++) {
    double omega = fdrSettings.bFreq[iOmega];
    U* oo = oo_polar + iOmega * 10 * 10; // 100 per frequency
    out << "    " << "W(AU) = " << std::setw(8) << std::setprecision(4)
        << std::fixed << std::left << omega;
    auto row = [&](int r){
      if (r > 0) out << "\n" << "    " << "        " << std::setw(8) << " ";
      for (int c = 0; c < 10; ++c) printRec(oo[r + 10*c]);
    };
    for (int r = 0; r < 10; ++r) row(r);
    out << "\n\n";
  }
  out << "\n\n\n\n";
};



    if(results.ed_ed_Polar) {

      out << "  Electric Dipole - Electric Dipole (Length) : ";
      out << "- Re [<< r_i; r_j >>] (AU)\n\n\n";


      printDD(printRecRe, results.ed_ed_Polar);

      if( std::is_same<U,dcomplex>::value ) {
        out << "  Electric Dipole - Electric Dipole (Length) : ";
        out << "- Im[<< r_i; r_j >>] (AU)\n\n\n";

        printDD(printRecIm, results.ed_ed_Polar);
      }

    }

    if(results.eq_ed_Polar) {

      out << "  Electric Quadrupole - Electric Dipole (Length) : ";
      out << "- Re[<< r_i r_j; r_k >>] (AU)\n\n\n";

      printQD(printRecRe, results.eq_ed_Polar);

      if( std::is_same<U,dcomplex>::value ) {
        out << "  Electric Quadrupole - Electric Dipole (Length) : ";
        out << "- Im[<< r_i r_j; r_k >>] (AU)\n\n\n";

        printQD(printRecIm, results.eq_ed_Polar);
      }

    }


// Finally, add the actual print block alongside the others:
if (results.eq_eq_Polar) {   // <-- adjust the field name if yours differs
  out << "  Electric Quadrupole - Electric Quadrupole (Length) : "
         "- Re[<< r_i r_j; r_k r_l >>] (AU)\n\n\n";
  printQQ(printRecRe, results.eq_eq_Polar);

  if (std::is_same<U,dcomplex>::value) {
    out << "  Electric Quadrupole - Electric Quadrupole (Length) : "
           "- Im[<< r_i r_j; r_k r_l >>] (AU)\n\n\n";
    printQQ(printRecIm, results.eq_eq_Polar);
  }
}

if (results.eo_ed_Polar) {
  out << "  Electric Octupole - Electric Dipole (Length) : "
         "- Re[<< r_i r_j r_k; r_l >>] (AU)\n\n\n";
  printOE(printRecRe, results.eo_ed_Polar);

  if (std::is_same<U,dcomplex>::value) {
    out << "  Electric Octupole - Electric Dipole (Length) : "
           "- Im[<< r_i r_j r_k; r_l >>] (AU)\n\n\n";
    printOE(printRecIm, results.eo_ed_Polar);
  }
}

if (results.eo_eq_Polar) {
  out << "  Electric Octupole - Electric Quadrupole (Length) : "
         "- Re[<< r_i r_j r_k; r_l r_m >>] (AU)\n\n\n";
  printOQ(printRecRe, results.eo_eq_Polar);

  if (std::is_same<U,dcomplex>::value) {
    out << "  Electric Octupole - Electric Quadrupole (Length) : "
           "- Im[<< r_i r_j r_k; r_l r_m >>] (AU)\n\n\n";
    printOQ(printRecIm, results.eo_eq_Polar);
  }
}

if (results.eo_eo_Polar) {
  out << "  Electric Octupole - Electric Octupole (Length) : "
         "- Re[<< r_i r_j r_k; r_l r_m r_n >>] (AU)\n\n\n";
  printOO(printRecRe, results.eo_eo_Polar);

  if (std::is_same<U,dcomplex>::value) {
    out << "  Electric Octupole - Electric Octupole (Length) : "
           "- Im[<< r_i r_j r_k; r_l r_m r_n >>] (AU)\n\n\n";
    printOO(printRecIm, results.eo_eo_Polar);
  }
}


    if(results.md_ed_Polar) {

      out << "  Magnetic Dipole - Electric Dipole (Length) : ";
      out << "Im[<< (r x p)_i; r_j >>] (AU)\n\n\n";


      printDD(printRecRe, results.md_ed_Polar);

      if( std::is_same<U,dcomplex>::value ) {
        out << "  Magnetic Dipole - Electric Dipole (Length) : ";
        out << "- Re[<< (r x p)_i; r_j >>] (AU)\n\n\n";


        printDD(printRecIm, results.md_ed_Polar);
      }

    }


    if(results.md_md_Polar) {

      out << "  Magnetic Dipole - Magnetic Dipole : ";
      out << "Im[<< (r x p)_i; (r x p)_j >>] (AU)\n\n\n";


      printDD(printRecRe, results.md_md_Polar);

      if( std::is_same<U,dcomplex>::value ) {
        out << "  Magnetic Dipole - Magnetic Dipole : ";
        out << "- Re[<< (r x p)_i; (r x p)_j >>] (AU)\n\n\n";


        printDD(printRecIm, results.md_md_Polar);
      }

    }
    

  };

  template <typename T>
  void ResponseTBase<T>::printFDObservables(std::ostream &out) {


    // FIXME: This is because only the OPA is calculated now
    if( not fdObs.opaCross_eda ) return;

    size_t nOmega = fdrSettings.bFreq.size();

    double xSmall = 1e-6;

    auto printRec = [&](double x) {
      out << std::setprecision(10) << std::scientific << std::setw(25)
          << std::right << ((std::abs(x) > xSmall) ? x : 0. );
    };

    out << "\n\n\n* OBSERVABLES \n\n\n";

    out << "  ONE-PHOTON ABSORPTION CROSS-SECTION (EDA) \n\n";
    out << "    * SIGMA(W) = 4 * PI * W / C * IM[ALPHA(-W,W)]\n"; 
    out << "    * ALPHA(-W,W) = TR[ << r; r >>(W) ]\n" ;

    out << "\n\n\n";

    out << "    " << std::right << std::setw(25) << "W"
                                << std::setw(25) << "SIGMA(W) (AU)\n";

    for(auto iOmega = 0; iOmega < nOmega; iOmega++) {

      double omega = fdrSettings.bFreq[iOmega];

      out << "    ";
      printRec(omega); printRec(-fdObs.opaCross_eda[iOmega]);
      out << "\n";

    }

    out << "\n\n\n\n";
  }

}; // namespace ChronusQ

