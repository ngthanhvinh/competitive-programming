import os

for i in range(2,25):
	t = str(i)
	if len(t) < 2:
		t = "0" + t
	filein  = "happiness." + t + ".in"
	fileout = "happiness." + t + ".sol"
	_filein = filein.replace('happiness.', '')
	_fileout = fileout.replace('happiness.', '')
	
	os.system("mv " + filein + " " + _filein)
	os.system("mv " + fileout + " " + _fileout)