import os
import random
import numpy as np



class AMPT_Input_Generator:

    def __init__(self):
        self.defaultdict = {
             "EFRM"        : 200            ,# EFRM (sqrt(S_NN) in GeV if FRAME is CMS)
                "FRAME"    : "CMS"             ,# FRAME
                "PROJ"     : "A"             ,# PROJ
                "TARG"     : "A"             ,# TARG
                "IAP"      : 197             ,# IAP (projectile A number)
                "IZP"      : 79              ,# IZP (projectile Z number)
                "IAT"      : 197             ,# IAT (target A number)
                "IZT"      : 79              ,# IZT (target Z number)
                "NEVENT"   : 1		,# NEVNT (total number of events)
                "BMIN"     : 0.              ,# BMIN (mininum impact parameter in fm) 
                "BMAX"     : 3.5		,# BMAX (maximum impact parameter in fm, also see below)
                "ISOFT"    : 4		,# ISOFT (D=4): select Default AMPT or String Melting(see below)
                "NTMAX"    : 150		,# NTMAX: number of timesteps (D=150), see below
                "DT"       : 0.2		,# DT: timestep in fm (hadron cascade time= DT*NTMAX) (D=0.2)
                "PARJ_41"  : 0.55		,# PARJ(41): parameter a in Lund symmetric splitting function
                "PARJ_42"  : 0.15    	,# PARJ(42): parameter b in Lund symmetric splitting function
                "IPOP"     : 1	      	,# (D=1,yes;0,no) flag for popcorn mechanism(netbaryon stopping)
                "PARJ_5"   : 1.0	      	,# PARJ(5) to control BMBbar vs BBbar in popcorn (D=1.0)
                "IHPR2_6"  : 1		,# shadowing flag (Default=1,yes; 0,no)
                "IHPR2_4"  : 0		,# quenching flag (D=0,no; 1,yes)
                "HIPR1_14" : 2.0		,# quenching parameter -dE/dx (GeV/fm) in case quenching flag=1
                "HIPR1_8"  : 2.0		,# p0 cutoff in HIJING for minijet productions (D=2.0)
                "XMU"      : 2.265E0  	,# parton screening mass in fm^(-1) (D=2.265d0), see below
                "IZPC"     : 0		,# IZPC: (D=0 forward-angle parton scatterings; 100,isotropic)
                "ALPHA"    : 0.33E0		,# alpha in parton cascade (D=0.33d0), see parton screening mass
                "DPCOAL"   : 1E6		,# dpcoal in GeV
                "DRCOAL"   : 1E6		,# drcoal in fm
                "IHJSED"   : 11		,# ihjsed: take HIJING seed from below (D=0)or at runtime(11)
                "NSEED"    : 13150909	,# random seed for HIJING
                "ISEEDP"   : 8		,# random seed for parton cascade
                "IKSDCY"   : 0		,# flag for K0s weak decays (D=0,no; 1,yes)
                "IPHIDCY"  : 1		,# flag for phi decays at end of hadron cascade (D=1,yes; 0,no)
                "IPI0DCY"  : 0		,# flag for pi0 decays at end of hadron cascade (D=0,no; 1,yes)
                "IOSCAR"   : 0		,# optional OSCAR output (D=0,no; 1,yes; 2&3,more parton info)
                "IDPERT"   : 0		,# flag for perturbative deuteron calculation (D=0,no; 1or2,yes)
                "NPERTD"   : 1		,# integer factor for perturbative deuterons(>=1 & <=10000)
                "IDXSEC"   : 1		,# choice of cross section assumptions for deuteron reactions
                "PTTRIG"   : -7.		,# Pt in GeV: generate events with >=1 minijet above this value
                "MAXMISS" : 1000		,# maxmiss (D=1000): maximum # of tries to repeat a HIJING event
                "IHPR2_2"  : 3,	# flag on initial and final state radiation (D=3,both yes; 0,no)
                "IHPR2_5"  : 1,	# flag on Kt kick (D=1,yes; 0,no)
                "IEMBED"   : 0,	# flag to turn on quark pair embedding (D=0,no; 1,yes)
                "PXQEMBD"  : 7,	     # Initial Px and Py values (GeV) of the embedded quark (u or d)
                "PYQEMBD"  : 0,	
                "XEMBD"    : 0,       # Initial x & y values (fm) of the embedded back-to-back q/qbar
                "YEMBD"    : 0,
                "NSEMBD"   : 1,       # nsembd(D=0), psembd (in GeV),tmaxembd (in radian).
                "PSEMBD"   : 5, 
                "TMAXEMBD" : 0, 
                "ISHADOW"  : 0,       # Flag to enable users to modify shadowing (D=0,no; 1,yes)
                "DSHADOW"  : 1,       # Factor used to modify nuclear shadowing
                "IPHIRP"   : 0,   
        }

        self.description = {
            "EFRM"         : "# EFRM (sqrt(S_NN) in GeV if FRAME is CMS)",
                "FRAME"    : "# FRAME",
                "PROJ"     : "# PROJ",
                "TARG"     : "# TARG",
                "IAP"      : "# IAP (projectile A number)",
                "IZP"      : "# IZP (projectile Z number)",
                "IAT"      : "# IAT (target A number)",
                "IZT"      : "# IZT (target Z number)",
                "NEVENT"   : "# NEVNT (total number of events)",
                "BMIN"     : "# BMIN (mininum impact parameter in fm) ",
                "BMAX"     : "# BMAX (maximum impact parameter in fm, also see below)",
                "ISOFT"    : "# ISOFT (D=4): select Default AMPT or String Melting(see below)",
                "NTMAX"    : "# NTMAX: number of timesteps (D=150), see below",
                "DT"       : "# DT: timestep in fm (hadron cascade time= DT*NTMAX) (D=0.2)",
                "PARJ_41"  : "# PARJ(41): parameter a in Lund symmetric splitting function",
                "PARJ_42"  : "# PARJ(42): parameter b in Lund symmetric splitting function",
                "IPOP"     : "# (D=1,yes;0,no) flag for popcorn mechanism(netbaryon stopping)",
                "PARJ_5"   : "# PARJ(5) to control BMBbar vs BBbar in popcorn (D=1.0)",
                "IHPR2_6"  : "# shadowing flag (Default=1,yes; 0,no)",
                "IHPR2_4"  : "# quenching flag (D=0,no; 1,yes)",
                "HIPR1_14" : "# quenching parameter -dE/dx (GeV/fm) in case quenching flag=1",
                "HIPR1_8"  : "# p0 cutoff in HIJING for minijet productions (D=2.0)",
                "XMU"      : "# parton screening mass in fm^(-1) (D=2.265d0), see below",
                "IZPC"     : "# IZPC: (D=0 forward-angle parton scatterings; 100,isotropic)",
                "ALPHA"    : "# alpha in parton cascade (D=0.33d0), see parton screening mass",
                "DPCOAL"   : "# dpcoal in GeV",
                "DRCOAL"   : "# drcoal in fm",
                "IHJSED"   : "# ihjsed: take HIJING seed from below (D=0)or at runtime(11)",
                "NSEED"    : "# random seed for HIJING",
                "ISEEDP"   : "# random seed for parton cascade",
                "IKSDCY"   : "# flag for K0s weak decays (D=0,no; 1,yes)",
                "IPHIDCY"  : "# flag for phi decays at end of hadron cascade (D=1,yes; 0,no)",
                "IPI0DCY"  : "# flag for pi0 decays at end of hadron cascade (D=0,no; 1,yes)",
                "IOSCAR"   : "# optional OSCAR output (D=0,no; 1,yes; 2&3,more parton info)",
                "IDPERT"   : "# flag for perturbative deuteron calculation (D=0,no; 1or2,yes)",
                "NPERTD"   : "# integer factor for perturbative deuterons(>=1 & <=10000)",
                "IDXSEC"   : "# choice of cross section assumptions for deuteron reactions",
                "PTTRIG"   : "# Pt in GeV: generate events with >=1 minijet above this value",
                "MAXMISS" :  "# maxmiss (D=1000): maximum # of tries to repeat a HIJING event",
                "IHPR2_2"  : "# flag on initial and final state radiation (D=3,both yes; 0,no)",
                "IHPR2_5"  : "# flag on Kt kick (D=1,yes; 0,no)",
                "IEMBED"   : "# flag to turn on quark pair embedding (D=0,no; 1,yes)",
                "PXQEMBD"  : "",
                "PYQEMBD"  : "# Initial Px and Py values (GeV) of the embedded quark (u or d)"	,
                "XEMBD"    : "",
                "YEMBD"    : "# Initial x & y values (fm) of the embedded back-to-back q/qbar",
                "NSEMBD"   : "",
                "PSEMBD"   : "",
                "TMAXEMBD" : "# nsembd(D=0), psembd (in GeV),tmaxembd (in radian)." ,
                "ISHADOW"  : "# Flag to enable users to modify shadowing (D=0,no; 1,yes)",
                "DSHADOW"  : "# Factor used to modify nuclear shadowing",
                "IPHIRP"   : "# Flag for random orientation of reaction plane (D=0,no; 1,yes)"   ,
        }

        self.indexlist = {
                0  : "EFRM"     ,
                1  : "FRAME"    ,
                2  : "PROJ"     ,
                3  : "TARG"     ,
                4  : "IAP"      ,
                5  : "IZP"      ,
                6  : "IAT"      ,
                7  : "IZT"      ,
                8  : "NEVENT"   ,
                9  : "BMIN"     ,
                10 : "BMAX"     ,
                11 : "ISOFT"    ,
                12 : "NTMAX"    ,
                13 : "DT"       ,
                14 : "PARJ_41"  ,
                15 : "PARJ_42"  ,
                16 : "IPOP"     ,
                17 : "PARJ_5"   ,
                18 : "IHPR2_6"  ,
                19 : "IHPR2_4"  ,
                20 : "HIPR1_14" ,
                21 : "HIPR1_8"  ,
                22 : "XMU"      ,
                23 : "IZPC"     ,
                24 : "ALPHA"    ,
                25 : "DPCOAL"   ,
                26 : "DRCOAL"   ,
                27 : "IHJSED"   ,
                28 : "NSEED"    ,
                29 : "ISEEDP"   ,
                30 : "IKSDCY"   ,
                31 : "IPHIDCY"  ,
                32 : "IPI0DCY"  ,
                33 : "IOSCAR"   ,
                34 : "IDPERT"   ,
                35 : "NPERTD"   ,
                36 : "IDXSEC"   ,
                37 : "PTTRIG"   ,
                38 : "MAXMISS"  ,
                39 : "IHPR2_2"  ,
                40 : "IHPR2_5"  ,
                41 : "IEMBED"   ,
                42 : "PXQEMBD"  ,
                43 : "PYQEMBD"  ,
                44 : "XEMBD"    ,
                45 : "YEMBD"    ,
                46 : "NSEMBD"   ,
                47 : "PSEMBD"   ,
                48 : "TMAXEMBD" ,
                49 : "ISHADOW"  ,
                50 : "DSHADOW"  ,
                51 : "IPHIRP"   
                }
        
        self.typelist = {
                0  : float     ,
                1  : str    ,
                2  : str ,
                3  : str ,
                4  : int      ,
                5  : int      ,
                6  : int      ,
                7  : int      ,
                8  : int   ,
                9  : float     ,
                10 : float     ,
                11 : int    ,
                12 : int    ,
                13 : float       ,
                14 : float  ,
                15 : float  ,
                16 : int     ,
                17 : float   ,
                18 : int  ,
                19 : int  ,
                20 : float ,
                21 : float ,
                22 : float      ,
                23 : int     ,
                24 : float    ,
                25 : float   ,
                26 : float   ,
                27 : int   ,
                28 : int    ,
                29 : int   ,
                30 : int  ,
                31 : int  ,
                32 : int  ,
                33 : int   ,
                34 : int   ,
                35 : int   ,
                36 : int   ,
                37 : float   ,
                38 : int  ,
                39 : int  ,
                40 : int  ,
                41 : int   ,
                42 : float  ,
                43 : float  ,
                44 : float  ,
                45 : float  ,
                46 : int  ,
                47 : float ,
                48 : float ,
                49 : int  ,
                50 : float  ,
                51 : int   
        }

        

    def load_centrality_table(self, filename):
        
        return np.genfromtxt(filename)

    def write_input(self, 
                    directory = "input", 
                    filename = "undefined", 
                    extension = "par", 
                    generate_zpc_seed = True):
       
        
        File = open("{0}/{1}.{2}".format(directory, filename, extension), "w")
        for j, key in enumerate(self.defaultdict):
            if(j < 42 or j > 48):
                if(generate_zpc_seed == True and key == "ISEEDP"):
                    File.write("{0:<30} {1:<30s} {2:<s}\n".format(
                        random.randint(1, 99999999), 
                        "! "+key,
                        self.description[key]))
                else:
                    File.write("{0:<30} {1:<30s} {2:<s}\n".format(
                        self.defaultdict[key],
                          "! "+key,
                          self.description[key]))
            elif(j == 42):
                substring = "{0}, {1}".format(
                    list(self.defaultdict.values())[42], 
                    list(self.defaultdict.values())[43])
                File.write("{0:<30} {1:<30s} {2:<s}\n".format(
                    substring,
                    "! " + list(self.defaultdict.keys())[42] + ", " + list(self.defaultdict.keys())[43],
                    list(self.description.values())[43]))
            elif(j == 44):
                substring = "{0}, {1}".format(
                    list(self.defaultdict.values())[44], 
                    list(self.defaultdict.values())[45])
                File.write("{0:<30} {1:<30s} {2:<s}\n".format(
                    substring,
                    "! " + list(self.defaultdict.keys())[44] + ", " + list(self.defaultdict.keys())[45],
                    list(self.description.values())[45]))
            elif(j == 46):
                substring = "{0}, {1}, {2}".format(
                    list(self.defaultdict.values())[46], 
                    list(self.defaultdict.values())[47],
                    list(self.defaultdict.values())[48])
                File.write("{0:<30} {1:<30s} {2:<s}\n".format(
                    substring,
                    "! " + list(self.defaultdict.keys())[46] + ", " + list(self.defaultdict.keys())[47] + ", " + list(self.defaultdict.keys())[48],
                    list(self.description.values())[48]))
            # else:
                # print("error")
        File.close()

    def write_input_for_multiple_centralities(self, table, prefix = "undefined", input_kwargs = {}, NEVENTincluded = False):
        nc = len(table)
        lower = table[0:nc-1]
        upper = table[1:nc]
        
        for ic in range(nc-1):
            self.defaultdict["BMIN"] = lower[ic][1]
            self.defaultdict["BMAX"] = upper[ic][1]
            if(NEVENTincluded == True):
                self.defaultdict["NEVENT"] = table[ic][2]
            self.write_input(filename = prefix + "-" + f"{int(lower[ic][0]):02d}"+ "-" + f"{int(upper[ic][0]):03d}",**input_kwargs)

        self.defaultdict["BMIN"] = lower[0][1]
        self.defaultdict["BMAX"] = upper[-1][1]
        self.write_input(filename = prefix + "-" + f"{int(lower[0][0]):02d}"+ "-" + f"{int(upper[-1][0]):03d}",**input_kwargs)
        print(lower, upper)

gen = AMPT_Input_Generator()

# gen.write_input()
table = gen.load_centrality_table("utils/centrality_tables/Au-Au_200GeV.arr")

table = table[[0,1,2,4,6,8,10,12,14,16,18,20]]

gen.write_input_for_multiple_centralities(table, prefix = "AuAu@200GeV-S1-C1")

gen = AMPT_Input_Generator()

gen.defaultdict["EFRM"] = 5020
gen.defaultdict["IAP"] = 208
gen.defaultdict["IZP"] = 82
gen.defaultdict["IAT"] = 208
gen.defaultdict["IZT"] = 82
gen.defaultdict["NTMAX"] = 1000

table = gen.load_centrality_table("utils/centrality_tables/Pb-Pb_5020GeV.arr")

table = table[[0,1,2,4,6,8,10,12,14,16,18,20]]

gen.write_input_for_multiple_centralities(table, prefix = "PbPb@5.02TeV-S1-C1")

gen = AMPT_Input_Generator()
table = np.array([[0, 0, 1],
                  [5  ,3.50, 1],
[10 ,5.00, 1],
[20 ,7.20, 1],
[30 ,8.80, 1],
[40 ,10.2, 1],
[50 ,11.40, 1],
[60 ,12.50, 1],
[70 ,13.60, 1],
[80 ,14.60, 1],
[90 ,15.50, 1],
[100, 20.00, 1]])

gen.defaultdict["PARJ_41"] = 0.3
gen.defaultdict["PARJ_42"] = 0.15

gen.defaultdict["EFRM"] = 5020
gen.defaultdict["IAP"] = 208
gen.defaultdict["IZP"] = 82
gen.defaultdict["IAT"] = 208
gen.defaultdict["IZT"] = 82
gen.defaultdict["NTMAX"] = 1000

gen.write_input_for_multiple_centralities(table, prefix = "PbPb@5.02TeV-S2-C2")


gen = AMPT_Input_Generator()

gen.defaultdict["EFRM"] = 200
gen.defaultdict["IAP"] = 65
gen.defaultdict["IZP"] = 29
gen.defaultdict["IAT"] = 65
gen.defaultdict["IZT"] = 29
gen.defaultdict["NTMAX"] = 300

table = gen.load_centrality_table("utils/centrality_tables/Cu-Cu_200GeV.arr")

table = table[[0,1,2,4,6,8,10,12,14,16,18,20]]

gen.write_input_for_multiple_centralities(table, prefix = "CuCu@200GeV-S1-C1")

gen = AMPT_Input_Generator()

gen.defaultdict["EFRM"] = 5440
gen.defaultdict["IAP"] = 134
gen.defaultdict["IZP"] = 54
gen.defaultdict["IAT"] = 134
gen.defaultdict["IZT"] = 54
gen.defaultdict["NTMAX"] = 1000

table = gen.load_centrality_table("utils/centrality_tables/Xe-Xe_5440GeV.arr")

table = table[[0,1,2,4,6,8,10,12,14,16,18,20]]

gen.write_input_for_multiple_centralities(table, prefix = "XeXe@5.44TeV-S1-C1")


gen = AMPT_Input_Generator()

gen.defaultdict["EFRM"] = 2760
gen.defaultdict["IAP"] = 208
gen.defaultdict["IZP"] = 82
gen.defaultdict["IAT"] = 208
gen.defaultdict["IZT"] = 82
gen.defaultdict["NTMAX"] = 1000

table = gen.load_centrality_table("utils/centrality_tables/Pb-Pb_2760GeV.arr")

table = table[[0,1,2,4,6,8,10,12,14,16,18,20]]

gen.write_input_for_multiple_centralities(table, prefix = "PbPb@2.76TeV-S1-C1")



gen = AMPT_Input_Generator()
table = np.array([[0, 0.               , 1],
                  [5, 3.56   , 1],
                [10 , 5.15   , 1],
                [20 , 7.32   , 1],
                [30 , 9.00   , 1],
                [40 , 10.4  , 1],
                [50 ,  11.7   , 1],
                [60 , 12.8  , 1],
                [70 , 13.8  , 1],
                [80 , 14.8   , 1],
                [90 , 15.8  , 1],
                [100, 21.5 , 1]])


gen.defaultdict["EFRM"] = 193
gen.defaultdict["IAP"] = 238
gen.defaultdict["IZP"] = 92
gen.defaultdict["IAT"] = 238
gen.defaultdict["IZT"] = 92
gen.defaultdict["NTMAX"] = 1000

gen.write_input_for_multiple_centralities(table, prefix = "UU@193GeV-S1-C3")