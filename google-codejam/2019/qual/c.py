tt = int(input())

def gcd(a, b):
	while b != 0:
		new_a = b
		new_b = a % b
		a = new_a
		b = new_b
	return a

for it in range(tt):
	# solve
	n, l = [int(x) for x in input().split()]
	prod = [int(x) for x in input().split()]

	a = []
	equals = []
	for i in range(l + 1):
		a.append(0)
	for i in range(l - 1):
		common = gcd(prod[i], prod[i + 1])
		if prod[i] != common:
			a[i] = int(prod[i] / common)
			a[i + 2] = int(prod[i + 1] / common)
		else:
			equals.append([i, i + 2])

	while True:
		found = False
		for pos1, pos2 in equals:
			if a[pos1] == 0 and a[pos2] != 0:
				a[pos1] = a[pos2]
				found = True
			if a[pos1] != 0 and a[pos2] == 0:
				a[pos2] = a[pos1]
				found = True
		if found == False:
			break

	# insert the list to the set 
	vals_set = set(a)
	# convert the set to the list 
	unique_vals = (list(vals_set))
	unique_vals.sort()

	res = ""
	for i in range(l + 1):
		index = unique_vals.index(a[i])
		res = res + chr(index + ord('A'))

	print("Case #%d: %s" % (it + 1, res))