#!/usr/bin/env python
import sys
import numpy as np

argument_list_length = len(sys.argv)
if  argument_list_length != 2 and argument_list_length != 4:
  print " "
  print " Program returns average FWHM of the stellar profile"
  print " Usage:"
  print "   ./fwhm.py <input_data_file> [flux_min] [flux_max]"
  print " "
  print "  Important requirement:"
  print "  input data file have to be an oputput of peak program"
  print "  part of the ESO ECLIPSE package, use: peak -F -P '8 25 35'"
  print "  ZK, ver. 2017-11-14"
  print " "
  exit()


n_sd=2.7  # scaling factor for sigma-clipping
n_it=5    # number of iterations
flux_min=1000.0
flux_max=30000.0

id_r=[]
phot_data = sys.argv[1]

if argument_list_length == 4:
    flux_min = float(sys.argv[2])
    flux_max = float(sys.argv[3])

f1 = open(phot_data, 'r')
fmax, fx, fy = np.loadtxt(f1, usecols=(8,9,10), unpack=True)
f1.close()

for j in  range(len(fmax)):
  if fmax[j]<flux_min or fmax[j]>flux_max:
    id_r.append(j)
  if fx[j]<0.0 or fy[j]<0.0:
    id_r.append(j)

fx_c=np.delete(fx, id_r)
fy_c=np.delete(fy, id_r)

av_fx=np.average(fx_c)
sd_fx=np.std(fx_c)
av_fy=np.average(fy_c)
sd_fy=np.std(fy_c)

for k in range(n_it):
  fx_up_l=av_fx+(n_sd*sd_fx)
  fx_low_l=av_fx-(n_sd*sd_fx)
  fy_up_l=av_fy+(n_sd*sd_fy)
  fy_low_l=av_fy-(n_sd*sd_fy)
  for l in  range(len(fx)):
    if fx[l]>fx_up_l or fx[l]<fx_low_l:
      id_r.append(l)
    if fy[l]>fy_up_l or fy[l]<fy_low_l:
      id_r.append(l)

  fx_c=np.delete(fx, id_r)
  fy_c=np.delete(fy, id_r)

  av_fx=np.average(fx_c)
  sd_fx=np.std(fx_c)
  av_fy=np.average(fy_c)
  sd_fy=np.std(fy_c)

print "%5d %7.3f %7.3f %7.3f" % (len(fx_c), av_fx, av_fy, (av_fx+av_fy)/2.0)
