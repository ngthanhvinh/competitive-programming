import subprocess, os, re, resource, time

# Settings
# Your path to g++ compiler. Leave blank if you added it into PATH
GCC_PATH = ""
# Input / Output matching. The runner will always try to find...
INPUT_MATCH = r"in"
# ... for input files, then proceed to replace it with...
OUTPUT_MATCH = r"sol"
# ... for output files, and..
DIFF_MATCH = r"diff"
# Timeout (in seconds)
TIMEOUT = 2
# Checker mode, 0 for diff, 1 for checker file
CHECKER = 0
filename = ""


class bg:
    OK = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    BOLD = '\033[1m'
    END = '\033[0m'

def setLimits():
	resource.setrlimit(resource.RLIMIT_STACK, (268435456, 268435456))
	resource.setrlimit(resource.RLIMIT_DATA, (268435456, 268435456))
	resource.setrlimit(resource.RLIMIT_FSIZE, (52428800, 52428800))
	resource.setrlimit(resource.RLIMIT_AS, (268435456, 268435456))
	os.setsid()

def compile():
	global filename
	filename = input("Enter the code file name: ");
	if os.path.exists("%s" % filename): os.system("rm %s" % filename)
	os.system('"' + GCC_PATH + 'g++" -O2 %s.cpp -o %s' % (filename, filename))
	return os.path.exists("%s" % filename)

def run_checker(option, files):
	if (option == 0): # Call diff
		sub = subprocess.Popen("diff -wy out.txt " + files[1] + " >" + files[2], shell=True)
		diff_in, diff_err = sub.communicate()
		if (sub.returncode == 0): os.system("rm " + files[2])
		return (sub.returncode ^ 1)
	if (option == 1): # Call checker
		sub = subprocess.Popen("./checker " + files[0] + " out.txt " + files[1], shell=True)
		diff_in, diff_err = sub.communicate()
		# if (sub.returncode == 1): os.system("rm " + files[2])
		return sub.returncode

def find_files():
	reg = re.compile(r"(?P<prefix>[^a-zA-Z0-9]?)" + INPUT_MATCH + r"(?P<suffix>[^a-zA-Z0-9]?)")
	files = []
	for dirpath, dirnames, filenames in os.walk("./"):
		for f in filenames: files = files + [os.path.join(dirpath, f)]
	ret = []
	for fin in files:
		fin = fin.replace("./", "")
		if reg.search(fin):
			if not os.path.exists(reg.sub(r"\g<prefix>" + OUTPUT_MATCH + r"\g<suffix>", fin)): continue
			ret = ret + [[fin, reg.sub(r"\g<prefix>" + OUTPUT_MATCH + r"\g<suffix>", fin), reg.sub(r"\g<prefix>" + DIFF_MATCH + "\g<suffix>", fin)]]
	ret.sort()
	return ret

def run(files):
	outp = "Input: " + bg.BOLD + files[0] + bg.END + "\t Output: " + bg.BOLD + files[1] + bg.END + "\t ";
	
	code = subprocess.Popen("./" + filename + " <" + files[0] + " >out.txt 2>err.txt", shell=True, preexec_fn=setLimits)
	before_run = time.time()
	try:
		code.communicate(timeout=float(TIMEOUT))
		t = code.returncode
	except subprocess.TimeoutExpired:
		t = 124
		code.kill()
	after_run = time.time()
	time_run = after_run - before_run
	time_diff = "\tTime taken: " + bg.BOLD + "%.3fs" % time_run + bg.END
	if t is not 0:
		print(outp + bg.WARNING + ("Time Limit" if t == 124 else "Runtime Err") + bg.END + time_diff)
		return 0
	if run_checker(CHECKER, files) is 0:
		print(outp + bg.FAIL + "Wrong answer." + bg.END + time_diff)
		return 0
	else: 
		print(outp + bg.OK + "Accepted!" + bg.END + time_diff)
		return 1

if compile() is False:
	print(bg.FAIL + "Compilation Error." + bg.END)
	exit()
print(bg.OK + "Compile Successful" + bg.END)
print("Running on tests")
total = 0
correct = 0
for test in find_files():
	total = total + 1
	correct = correct + run(test)
	if (os.path.exists("out.txt")): os.system("rm out.txt")
	if (os.path.exists("err.txt")): os.system("rm err.txt")
print("Judge ended. Your score: " + bg.BOLD + "%d/%d" % (correct, total) + bg.END)
