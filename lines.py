import os
import glob

amount = 0

def lines(file):
	global amount
	for line in open(file).readlines(): amount += 1
	print(file)

def linesD(dir, fileext):
	for filename in glob.iglob(dir + '**/**', recursive=True):
		if os.path.isfile(filename):
			if filename.endswith(fileext):
				lines(filename)

linesD("rey/grey/", ".h")
linesD("rey/prey/", ".h")
print(amount)

os.system("pause")
