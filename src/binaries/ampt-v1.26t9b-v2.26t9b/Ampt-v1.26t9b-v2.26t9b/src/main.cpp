
// C++ translation of Fortran driver program for A Multi-Phase Transport model

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

// Define common blocks and variables
double xmp, xmu, alpha, rscut2, cutof2, dshadow;
double smearp, smearh, dpcoal, drcoal, ecritl;
double EFRM;
size_t nseedr;
int ihjsed;
int IAmax;
int imiss;
double BMIN, BMAX;
size_t NSEED;
std::string FRAME, PROJ, TARG;
std::string amptvn;
int EATT, JATT, NATT, NT, NP, N0, N01, N10, N11;
std::vector<double> HIPR1(100), HINT1(100);
std::vector<int> IHPR2(50), IHNT2(50);
std::vector<int> MSTU(200), MSTJ(200);
std::vector<double> PARU(200), PARJ(200);
std::vector<double> ARPAR1(100), ARINT1(100);
std::vector<int> IAPAR2(50), IAINT2(50);
int IOUT, IAEVT, IARUN, MISS;
int nevent, isoft, isflag, izpc;
int nsmbbbar, nsmmeson;
int idpert, npertd, idxsec;
int iseedp;
int NUM;
double MASSPR, MASSTA;
int ISEED, IAVOID;
double DT;
int ILAB, MANYB, NTMAX, ICOLL, INSYS, IPOT, MODE, IMOMEN, NFREQ, ICFLOW, ICRHO, ICOU, KPOTEN, KMUL;
int iap, izp, iat, izt;
int NSAV, iksdcy;
int iphidcy, ntrig, maxmiss, ipi0dcy;
int iembed, nsembd;
double pxqembd, pyqembd, xembd, yembd, psembd, tmaxembd, phidecomp;
int ishadow;
int iphirp, phiRP;

// Function prototypes
void HIDATA();
void PYDATA();
void LUDATA();
void ARDATA();
void PPBDAT();
void zpcbdt();
void HIJSET(int, std::string, std::string, std::string, int, int, int, int);
void ARTSET();
void INIZPC();
void HIJING(std::string, double, double);
void getnp();
void ARINI();
void ARINI2(int);
void ARTAN1();
void HJANA3();
void ARTMN();
void HJANA4();
void ARTAN2();
void ARTOUT(int);

int main()
{
    std::ifstream infile("input.ampt");
    std::ofstream outfile("ana/version");

    // Read input parameters
    infile >> EFRM >> FRAME >> PROJ >> TARG >> iap >> izp >> iat >> izt >> nevent >> BMIN >> BMAX >> isoft >> NTMAX >> DT >> PARJ[40] >> PARJ[41] >> ipop >> PARJ[4] >> IHPR2[5] >> IHPR2[3] >> HIPR1[13] >> HIPR1[7] >> xmu >> izpc >> alpha >> dpcoal >> drcoal >> ihjsed >> NSEED >> iseedp >> iksdcy >> iphidcy >> ipi0dcy >> ioscar >> idpert >> npertd >> idxsec >> pttrig >> maxmiss >> IHPR2[1] >> IHPR2[4] >> iembed >> pxqembd >> pyqembd >> xembd >> yembd >> nsembd >> psembd >> tmaxembd >> ishadow >> dshadow >> iphirp;

    infile.close();

    if (isoft == 1)
    {
        amptvn = "1.26t9b (Default)";
    }
    else if (isoft == 4)
    {
        amptvn = "2.26t9b (StringMelting)";
    }
    else
    {
        amptvn = "Test-Only";
    }

    std::cout << amptvn << std::endl;
    outfile << amptvn << std::endl;

    if (ihjsed == 11)
    {
        std::cout << "# Read in NSEED in HIJING at run time (e.g. 20030819):" << std::endl;
        std::cin >> nseedr;
        NSEED = nseedr;
        std::cout << "#   read in: " << NSEED << std::endl;
        outfile << "# Read in NSEED in HIJING at run time: " << NSEED << std::endl;
    }

    outfile.close();

    NSEED = 2 * NSEED + 1;
    std::srand(NSEED);

    IHPR2[9] = 1;
    ARPAR1[0] = 0.7;
    smearp = 0.0;
    IAmax = std::max(iap, iat);
    smearh = 1.2 * std::pow(IAmax, 0.3333) / (EFRM / 2.0 / 0.938);

    std::ofstream amptfile("ana/ampt.dat");
    std::ofstream zpcfile("ana/zpc.dat");

    HIJSET(EFRM, FRAME, PROJ, TARG, iap, izp, iat, izt);
    ARTSET();
    INIZPC();

    for (int J = 1; J <= nevent; J++)
    {
        IAEVT = J;
        for (int K = 1; K <= NUM; K++)
        {
            IARUN = K;
            if (IAEVT == nevent && IARUN == NUM)
            {
                IOUT = 1;
            }
            std::cout << " EVENT " << J << ", RUN " << K << std::endl;
            imiss = 0;
            do
            {
                HIJING(FRAME, BMIN, BMAX);
                IAINT2[0] = NATT;

                if (NATT == 0)
                {
                    imiss++;
                    if (imiss <= 20)
                    {
                        std::cout << "repeated event: natt=0,j,imiss=" << J << "," << imiss << std::endl;
                    }
                    else
                    {
                        std::cout << "missed event: natt=0,j=" << J << std::endl;
                        break;
                    }
                }
                else
                {
                    break;
                }
            } while (true);

            if (IHPR2[19] == 0)
                continue;

            getnp();
            ARINI();
            ARINI2(K);
        }

        ARTAN1();
        HJANA3();
        ARTMN();
        HJANA4();
        ARTAN2();
    }

    ARTOUT(nevent);

    return 0;
}
