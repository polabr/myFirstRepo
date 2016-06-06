import sys
from ROOT import gSystem
gSystem.Load("libmyFirstRepo_Muon")
from ROOT import sample

try:

    print "PyROOT recognized your class %s" % str(sample)

except NameError:

    print "Failed importing Muon..."

sys.exit(0)

