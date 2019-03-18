import os
from os import listdir
from os.path import isfile

FOLDER = 'out'
DIR = os.getcwd()

for file in listdir(DIR + '/' + FOLDER):
	#if isfile(file) == True: 
		newFile = file.strip('.txt')
		os.system("mv %s %s" % (DIR + '/' + FOLDER + '/' + file, DIR + '/' + newFile + '.' + FOLDER))