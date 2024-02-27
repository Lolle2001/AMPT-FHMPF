import os
class AMPT_parameters :

    def __init__(self, lengthoflist):
        self.lengthoflist = lengthoflist
        self.parameterdict = {
                "EFRM"     : [5020],     # EFRM (sqrt(S_NN) in GeV if FRAME is CMS)
                "FRAME"    : ["CMS"],    # FRAME
                "PROJ"     : ["A"],      # PROJ
                "TARG"     : ["A"],      # TARG
                "IAP"      : [208],      # IAP (projectile A number)
                "IZP"      : [82],       # IZP (projectile Z number)
                "IAT"      : [208],      # IAT (target A number)
                "IZT"      : [82],       # IZT (target Z number)
                "NEVENT"   : [100],      # NEVNT (total number of events)
                "BMIN"     : [0.],       # BMIN (mininum impact parameter in fm) 
                "BMAX"     : [20.],      # BMAX (maximum impact parameter in fm, also see below)
                "ISOFT"    : [4],        # ISOFT (D=4): select Default AMPT or String Melting(see below)
                "NTMAX"    : [1000],     # NTMAX: number of timesteps (D=150), see below
                "DT"       : [0.2],      # DT: timestep in fm (hadron cascade time= DT*NTMAX) (D=0.2)
                "PARJ_41"  : [0.3],	     # PARJ(41): parameter a in Lund symmetric splitting function
                "PARJ_42"  : [0.15],     # PARJ(42): parameter b in Lund symmetric splitting function
                "IPOP"     : [1],  	     # (D=1,yes;0,no) flag for popcorn mechanism(netbaryon stopping)
                "PARJ_5"   : [1.],       # PARJ(5) to control BMBbar vs BBbar in popcorn (D=1.0)
                "IHPR2_6"  : [1],        # shadowing flag (Default=1,yes; 0,no)
                "IHPR2_4"  : [1],        # quenching flag (D=0,no; 1,yes)
                "HIPR1_14" : [2.0],      # quenching parameter -dE/dx (GeV/fm) in case quenching flag=1
                "HIPR1_8"  : [2.0],      # p0 cutoff in HIJING for minijet productions (D=2.0)
                "XMU"      : [2.265],    # parton screening mass in fm^(-1) (D=2.265d0), see below
                "IZPC"     : [0],        # IZPC: (D=0 forward-angle parton scatterings; 100,isotropic)
                "ALPHA"    : [0.33],     # alpha in parton cascade (D=0.33d0), see parton screening mass
                "DPCOAL"   : [1E6],      # dpcoal in GeV
                "DRCOAL"   : [1E6],      # drcoal in fm
                "IHJSED"   : [11],       # ihjsed: take HIJING seed from below (D=0)or at runtime(11)
                "NSEED"    : [13150909], # random seed for HIJING
                "ISEEDP"   : [8],        # random seed for parton cascade
                "IKSDCY"   : [0],        # flag for K0s weak decays (D=0,no; 1,yes)
                "IPHIDCY"  : [1],        # flag for phi decays at end of hadron cascade (D=1,yes; 0,no)
                "IPI0DCY"  : [0],        # flag for pi0 decays at end of hadron cascade (D=0,no; 1,yes)
                "IOSCAR"   : [0],        # optional OSCAR output (D=0,no; 1,yes; 2&3,more parton info)
                "IDPERT"   : [0],        # flag for perturbative deuteron calculation (D=0,no; 1or2,yes)
                "NPERTD"   : [1],        # integer factor for perturbative deuterons(>=1 & <=10000)
                "IDXSEC"   : [1],        # choice of cross section assumptions for deuteron reactions
                "PTTRIG"   : [-7.],      # Pt in GeV: generate events with >=1 minijet above this value
                "MAXMISS"  : [1000],	 # maxmiss (D=1000): maximum # of tries to repeat a HIJING event
                "IHPR2_2"  : [3],        # flag on initial and final state radiation (D=3,both yes; 0,no)
                "IHPR2_5"  : [1],        # flag on Kt kick (D=1,yes; 0,no)
                "IEMBED"   : [0],        # flag to turn on quark pair embedding (D=0,no; 1,yes)
                "PXQEMBD"  : [7.],	     # Initial Px and Py values (GeV) of the embedded quark (u or d)
                "PYQEMBD"  : [0.],	
                "XEMBD"    : [0.],       # Initial x & y values (fm) of the embedded back-to-back q/qbar
                "YEMBD"    : [0.],
                "NSEMBD"   : [1],        # nsembd(D=0), psembd (in GeV),tmaxembd (in radian).
                "PSEMBD"   : [5.], 
                "TMAXEMBD" : [0.], 
                "ISHADOW"  : [0],        # Flag to enable users to modify shadowing (D=0,no; 1,yes)
                "DSHADOW"  : [1.],       # Factor used to modify nuclear shadowing
                "IPHIRP"   : [0]         # Flag for random orientation of reaction plane (D=0,no; 1,yes)
                }
        
    def Write(self, directory = "input", filename = "", extension = "par", runnumber = 1):
        directory = os.path.abspath(directory)
        if(runnumber >= 1):
            for j, key in enumerate(self.parameterdict):
                if(len(self.parameterdict[key])==1):
                    self.parameterdict[key] = self.parameterdict[key] *  self.lengthoflist
                print(j, key, self.parameterdict[key])    
            for i in range(self.lengthoflist):
                File = open("{0}/{1}{2}{3:03d}.{4}".format(directory, filename, runnumber, i, extension), "w")
                for j, key in enumerate(self.parameterdict):
                    if(j < 42 or j > 48):
                        File.write("{0}\n".format(self.parameterdict[key][i]))
                    elif(j == 42):
                        File.write("{0}, {1}\n".format(list(self.parameterdict.values())[42][i], list(self.parameterdict.values())[43][i]))
                    elif(j == 44):
                        File.write("{0}, {1}\n".format(list(self.parameterdict.values())[44][i], list(self.parameterdict.values())[45][i]))
                    elif(j == 46):
                        File.write("{0}, {1}, {2}\n".format(list(self.parameterdict.values())[46][i], list(self.parameterdict.values())[47][i],list(self.parameterdict.values())[48][i]))
                    else:
                        print("error")
                File.close()
                  
        else:
            print("runnumber must be greater than 1")
        

def write_job_script(runnumbers, binmin = 1, binmax = 20, filename = "ampt.job"):
    with open(filename, "w") as f:
        f.write("#!/bin/bash\n")
        for run in runnumbers:
            f.write(f"bash rampt.sh {run}.par {run} {binmin} {binmax}\n")
    f.close()


if __name__=="__main__":
    par2 = AMPT_parameters(5)
    par2.parameterdict["XMU"] = [2.265 * 0.5 ** 0.5, 2.265 * 0.25 ** 0.5, 2.265 * 0.05 ** 0.5, 2.265 * 2 ** 0.5, 2.265 * 4 ** 0.5]
    par2.parameterdict["NEVENT"] = [10]
    par2.parameterdict["BMIN"] = [8.55]
    par2.parameterdict["BMAX"] = [9.87]
    par2.parameterdict["ISOFT"] = [1]
    par2.Write(runnumber=2)

    par3 = AMPT_parameters(6)
    par3.parameterdict["HIPR1_14"] = [0, 1.5, 1.8, 2.0, 2.2, 2.4]
    par3.parameterdict["NEVENT"] = [100]
    par3.parameterdict["BMIN"] = [8.55]
    par3.parameterdict["BMAX"] = [9.87]
    par3.parameterdict["ISOFT"] = [1]
    par3.Write(runnumber=3)
    
    write_job_script([3000, 3001,3002,3003,3004,3005,2000,2001,2002,2003,2004])
    
