import os

for i in range(1,41):
	t = str(i)
	if len(t) < 2:
		t = "0" + t
	filein  = "RadioTowers." + t + ".in"
	fileout = "RadioTowers." + t + ".sol"
	_filein = filein.replace('RadioTowers.', '')
	_fileout = fileout.replace('RadioTowers.', '')
	
	os.system("mv " + filein + " " + _filein)
	os.system("mv " + fileout + " " + _fileout)